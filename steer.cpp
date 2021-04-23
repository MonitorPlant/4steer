#include <cstdint>
#include <mbed.h>
#include <math.h>
#include "DigitalOut.h"
#include "PinNames.h"
#include "SerialBase.h"
#include "UnbufferedSerial.h"
#include "controller.h"
#include "encoder.h"
#include "mbed.h"
#include "debugger.h"
#include "multi_motor.h"
#include "roboken/roboken.h"
#include "steer.h"
#include "xbee_debug.h"

const static float steer_zero[4] = {81, 45, 58, 32};

void Steer::init(void) {
    for(int i = 0; i < 4; i++) {
        wheel_yaw[i] = 0;
        power_drive[i] = 0;
        power_rotate[i] = 0;
    }
    x = 0;
    y = 0;
    yaw = 0;

    ex_pass = 0;
    ey_pass = 0;
    turn_pass = 0;

    enc.encoder_cons(11, 1, 2, true, false);
    enc.init();
    gyro.gyro_cons(12);
    gyro.init();
    
    for(int i = 0; i < 4; i++) {
        motor_drive[i].motor_cons(i + 1, false);
        motor_drive[i].init();
        motor_drive[i].set_power(0);
        motor_rotate[i].motor_cons(i + 5, true);
        motor_rotate[i].init();
        motor_rotate[i].set_power(0);
    }
}

void Steer::update_coord(void) {
    //角度を更新
    this->yaw = gyro.yaw();

    //回転成分を算出
    float turn = yaw * PI * ROBO_R / 180;
    
    //並行成分を算出
    float ex = (enc.get_enc1() / PULSE_MAX) * PI * ENC_2R;
    float ey = (enc.get_enc2() / PULSE_MAX) * PI * ENC_2R;
    float dex = ex - ex_pass - (turn - turn_pass);
    float dey = ey - ey_pass + (turn - turn_pass);

    //過去の値を更新
    turn_pass = turn;
    ex_pass = ex;
    ey_pass = ey;

    this->x += dex * cosf(this->yaw * PI / 180) + dey * sinf(this->yaw * PI / 180);
    this->y += dey * cosf(this->yaw * PI / 180) - dey * sinf(this->yaw * PI / 180);

    roboken::Debugger::info("x:%d y:%d yaw:%d", this->x, this->y, (int32_t)this->yaw);
    // roboken::Debugger::info("x:%d y:%d yaw:%d", enc.get_enc1(), enc.get_enc2(), (int32_t)gyro.yaw());
}

void Steer::update_steer_yaw(void) {
    static int32_t enc[4];
    static int8_t enc_counter[4] = {};
    static uint16_t enc_last[4] = {};

    uint8_t crc = 0;
    uint16_t enc_tmp[4];

    if(roboken::XbeeDebug::read_org() == 's') {
        for(int i = 0; i < 4; i++) {
            enc_tmp[i] = (roboken::XbeeDebug::read_org() << 8) + roboken::XbeeDebug::read_org();
            crc ^= (enc_tmp[i] & 0xFF00) >> 8;
            crc ^= (enc_tmp[i] & 0x00FF);
        }

        if(roboken::XbeeDebug::read_org() == crc) {
            for(int i = 0; i < 4; i++) {
                if(enc_last[i] > 3000 && enc_tmp[i] < 1000) {
                    enc_counter[i]++;
                }
                if(enc_last[i] < 1000 && enc_tmp[i] > 3000) {
                    enc_counter[i]--;
                }

                enc_last[i] = enc_tmp[i];
                enc[i] = enc_counter[i] * 4096 + enc_tmp[i];

                this->wheel_yaw[i] = ((float)enc[i] / 12288) * 360;
            }
        }
    }
    // roboken::Debugger::info( "1:%d 2:%d 3:%d 4:%d", (int32_t)wheel_yaw[0], (int32_t)wheel_yaw[1], (int32_t)wheel_yaw[2], (int32_t)wheel_yaw[3]);
}

void Steer::cal_power(int16_t diff_x, int16_t diff_y, float diff_yaw) {
    float diff_yaw_x[4];
    float diff_yaw_y[4];
    int8_t power_x[4];
    int8_t power_y[4];

    for(int i = 0; i < 4; i++) {
        diff_yaw_x[i] = diff_yaw * cosf(45 + 90 * i);
        diff_yaw_y[i] = diff_yaw * sinf(45 + 90 * i);
        power_x[i] = diff_x + diff_yaw_x[i];
        power_y[i] = diff_y + diff_yaw_y[i];
        this->wheel_yaw[i] = atanf(power_y[i] / power_x[i]);
        this->power_drive[i] = sqrtf(power_x[i] * power_x[i] + power_y[i] + power_y[i]);

        this->power_drive[i] /= 2;
        IN_RANGE(this->power_drive[i], 10, 30);
    }
}

//ステアを回転
void Steer::rotate_steer(float yaw1, float yaw2, float yaw3, float yaw4) {
    const int8_t power_max_rotate[4] = {90, 90, 90, 90};
    const int8_t power_min_rotate[4] = {6, 7, 7, 7};
    const int8_t power_max_drive[4] = {53, 53, 53, 53};
    const int8_t power_min_drive[4] = {4, 3, 3, 3};

    float goal_wheel_yaw[4] = {yaw1, yaw2, yaw3, yaw4};
    float diff_wheel_yaw[4];
    float power_percent[4];
    int8_t power_rotate[4];
    int8_t power_drive[4];

    for(int i = 0; i < 4; i++) {
        goal_wheel_yaw[i] += steer_zero[i];
    }

    do {
        update_coord();
        update_steer_yaw();

        for(int i = 0; i < 4; i++) {
            diff_wheel_yaw[i] = goal_wheel_yaw[i] - wheel_yaw[i];
            if(ABS(diff_wheel_yaw[i]) < 3) {
                power_percent[i] = 0;
            }
            else {
                power_percent[i] = (float)diff_wheel_yaw[i] / 150;
            }
            IN_RANGE(power_percent[i], 0.1f, 0.90f);

            power_rotate[i] = power_percent[i] * power_max_rotate[i];
            power_drive[i] = power_percent[i] * power_max_drive[i];
            IN_RANGE(power_rotate[i], power_min_rotate[i], power_max_rotate[i]);
            IN_RANGE(power_drive[i], power_min_drive[i], power_max_drive[i]);
        }
        for(int i = 0; i < 4; i++) {
            motor_drive[i].set_power(power_drive[i]);
            motor_rotate[i].set_power(power_rotate[i]);
        }
        // roboken::Debugger::info("%d %d %d %d", power_rotate[0], power_rotate[1], power_rotate[2], power_rotate[3]);
    } while(power_percent[0] != 0 && power_percent[1] != 0 && power_percent[2] != 0 && power_percent[3] != 0);
}

void Steer::auto_move(int32_t goal_x, int32_t goal_y, float goal_yaw, uint8_t time) {
    //開始時の各座標を記憶
    int32_t start_x = this->x;
    int32_t start_y = this->y;
    float start_yaw = this->yaw;
    //開始時の各座標ごとの差を記憶
    int32_t start_diff_x = goal_x - this->x;
    int32_t start_diff_y = goal_y - this->y;
    float start_diff_yaw = goal_yaw - this->yaw;
    //移動完了までの割合
    float move_percent = 0;
    //移動完了フラグ
    bool move_finish = false;

    //初期の位相を合わせる
    cal_power(start_diff_x, start_diff_y, start_diff_yaw);
    rotate_steer(wheel_yaw[0], wheel_yaw[1], wheel_yaw[2], wheel_yaw[3]);

    //時間制御用タイマー
    Timer move_timer;
    if(time != 0) {
        move_timer.start();
        move_timer.reset();
    }

    do {
        if(time != 0) {
            move_percent = time / move_timer.read();
        }
        if(time == 0 || move_percent >= 1) {
            move_percent = 1;
        }

        update_coord();
        update_steer_yaw();
        cal_power((start_x + start_diff_x * move_percent) - x, (start_y + start_diff_y * move_percent) - y, (start_yaw + start_diff_yaw * move_percent) - yaw);

        rotate_steer(wheel_yaw[0], wheel_yaw[1], wheel_yaw[2], wheel_yaw[3]);

        for(int i = 0; i < 4; i++) {
            if(power_drive[i] == 0 ) {
                move_finish = true;
            }
            if(power_rotate[i] == 0) {
                move_finish = true;
            }
        }

        // motor_drive[0].set_power(wheel_power[0]);
    } while(move_percent < 1 && move_finish== false);

    move_timer.stop();
}

void Steer::manual_move(int8_t power_x, int8_t power_y, int8_t power_yaw) {

}
