#include "DM_CAN.h"
#include <string.h>
/**
 * @brief  简易速度控制 (使电机转起来)
 * @param  packet: 驱动包指针
 * @param  vel: 目标速度 (单位: rad/s，正数顺时针，负数逆时针)
 * @param  motor_id: 电机ID (默认为 1，除非你改过寄存器 0x0A)
 */
void DM_Motor_Simple_Run(FDCAN_MsgPacket_t *packet, float vel, uint8_t motor_id)
{
    // 速度模式的 ID 偏移量是 0x200
    packet->TxHeader.Identifier = 0x200 + motor_id; 
    packet->TxHeader.DataLength = FDCAN_DLC_BYTES_4; // 速度模式只需要 4 字节
    
    // 直接将 float 的内存拷贝到发送数组 (STM32默认就是小端)
    memcpy(packet->TxData, &vel, 4);
    
    // 调用你之前写好的发送函数
    FDCAN_Send_Msg(packet);
}


/**
 * @brief  使能电机
 * @param  motor_id: 电机设定ID (接收ID)
 */
void DM_Motor_Enable(FDCAN_MsgPacket_t *packet, uint8_t motor_id)
{
    packet->TxHeader.Identifier = motor_id;      // 直接使用基础 ID
    packet->TxHeader.DataLength = FDCAN_DLC_BYTES_8;
    
    // 达妙标准使能序列: 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF 0xFC
    packet->TxData[0] = 0xFF;
    packet->TxData[1] = 0xFF;
    packet->TxData[2] = 0xFF;
    packet->TxData[3] = 0xFF;
    packet->TxData[4] = 0xFF;
    packet->TxData[5] = 0xFF;
    packet->TxData[6] = 0xFF;
    packet->TxData[7] = 0xFC;
    
    FDCAN_Send_Msg(packet);
}

/**
 * @brief  失能电机 (停止控制并释放转子)
 */
void DM_Motor_Disable(FDCAN_MsgPacket_t *packet, uint8_t motor_id)
{
    packet->TxHeader.Identifier = motor_id;
    packet->TxHeader.DataLength = FDCAN_DLC_BYTES_8;
    
    // 达妙标准失能序列: 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF 0xFD
    packet->TxData[0] = 0xFF;
    packet->TxData[1] = 0xFF;
    packet->TxData[2] = 0xFF;
    packet->TxData[3] = 0xFF;
    packet->TxData[4] = 0xFF;
    packet->TxData[5] = 0xFF;
    packet->TxData[6] = 0xFF;
    packet->TxData[7] = 0xFD;
    
    FDCAN_Send_Msg(packet);
}
