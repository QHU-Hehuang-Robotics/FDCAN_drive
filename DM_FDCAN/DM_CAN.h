#ifndef __DM_CAN_h
#define __DM_CAN_h

#include "CAN_drive.h"
#include "cmsis_os.h"
#include "cordic.h"
#include "fdcan.h"
#include "gpio.h"

typedef enum {
    STATE_MOTOR_OFF,      // 未使能
    STATE_MOTOR_ENABLING, // 正在使能
    STATE_MOTOR_READY,    // 准备就绪（进入控制模式）
    STATE_MOTOR_RUNNING,  // 运行中
    STATE_MOTOR_ERROR,    // 故障状态
    STATE_MOTOR_STOPPING  // 正在停止
} DM_State_t;

typedef struct {
    uint32_t can_id;      // 电机接收 ID (默认 0x01)
    uint32_t master_id;   // 主机接收 ID
    DM_State_t state;     // 当前状态
    float target_pos;     // 目标位置
    float target_vel;     // 目标速度
} DM_Motor_t;

#endif
