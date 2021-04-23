#include <cstdint>
#include <mbed.h>
#include <math.h>
#include "DigitalOut.h"
#include "PinNames.h"
#include "SerialBase.h"
#include "controller.h"
#include "encoder.h"
#include "mbed.h"
#include "debugger.h"
#include "multi_motor.h"
#include "roboken/roboken.h"

#ifndef STEER_H
#define STEER_H

#define PI (float)acosf(-1)
#define ABS(n) (n>=0?n:-(n))
#define PULSE_MAX (float)48
#define ENC_2R (float)60
// #define ROBO_R (float)223.05
#define ROBO_R (float)180
#define IN_RANGE(n,min,max) (n=((n>max)?max:(n<-(max))?-(max):(-(min)<n&&n<0)?-(min):(0<n&&n<min)?min:n))

class Steer {
private:
    //センサーとモーター
    roboken::Encoder enc;
    roboken::Gyro gyro;
    roboken::Motor motor_rotate[4];
    roboken::Motor motor_drive[4];

    //各モーターの出力
    int8_t power_drive[4];
    int8_t power_rotate[4];


    int32_t ex_pass;
    int32_t ey_pass;
    float turn_pass;

    void update_steer_yaw(void); //各ステアの操舵の角度を取得
    void cal_power(int16_t diff_x, int16_t diff_y, float diff_yaw); //各軸の差を受け取り、ステアの出力と角度を計算
public:
    //ロボットの状態
    int32_t x;
    int32_t y;
    float yaw;
    //4ステのモーターの出力変数
    float wheel_yaw[4];

    void init(void); //初期化
    void update_coord(void); //ロボットの座標を取得
    void rotate_steer(float yaw1, float yaw2, float yaw3, float yaw4); //ステアを回転だけする
    void auto_move(int32_t goal_x, int32_t goal_y, float goal_yaw, uint8_t time = 0); //座標指定して移動
    void manual_move(int8_t power_x, int8_t power_y, int8_t power_yaw); //各軸の出力ごとの指定で移動
};

#endif /* STEER_H */
