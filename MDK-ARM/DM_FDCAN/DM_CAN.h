#ifndef __DM_CAN_h
#define __DM_CAN_h

#include "main.h"
#include "CAN_drive.h"


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

void DM_Motor_Simple_Run(FDCAN_MsgPacket_t *packet, float vel, uint8_t motor_id);
void DM_Motor_Disable(FDCAN_MsgPacket_t *packet, uint8_t motor_id);
void DM_Motor_Enable(FDCAN_MsgPacket_t *packet, uint8_t motor_id);

#endif
