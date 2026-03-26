#ifndef __CAN_DRIVE_H
#define __CAN_DRIVE_H

#include "main.h"

#define FDCAN_MOD 

#ifdef FDCAN_MOD

typedef struct {
    uint32_t can_id;
    uint8_t* data;
    uint16_t len;
} FDCAN_TX_DATA_t;

typedef struct {
    uint8_t  Index;      // 过滤器索引 (0-127)
    uint32_t Type;       // 模式 (MASK / RANGE / DUAL)
    uint32_t Config;     // 去向 (FIFO0 / FIFO1 / REJECT)
    uint32_t Id1;        // 参数1 (目标ID 或 起始ID)
    uint32_t Id2;        // 参数2 (掩码 或 结束ID)
} FDCAN_FilterConf_t;

typedef enum {
    CAN_STATE_IDLE = 0,      // 空闲
    CAN_STATE_READY,         // 就绪
    CAN_STATE_STARTING,      // 启动中
    CAN_STATE_NORMAL,        // 正常运行
    CAN_STATE_BUSY_TX,       // 发送忙
    CAN_STATE_BUSY_RX,       // 接收忙
    CAN_STATE_SLEEP,         // 睡眠
    CAN_STATE_ERROR_WARNING, // 错误警告 (>96)
    CAN_STATE_ERROR_PASSIVE, // 被动错误 (>127)
    CAN_STATE_BUS_OFF,       // 总线离线
    CAN_STATE_CONFIG_ERROR,  // 配置错误
    CAN_STATE_TIMEOUT        // 超时
} CAN_State_t;

typedef struct {
    FDCAN_HandleTypeDef* hfdcan;
    CAN_State_t              State;
    FDCAN_TxHeaderTypeDef    TxHeader;
    FDCAN_RxHeaderTypeDef    RxHeader;
    FDCAN_FilterTypeDef      FilterHeader;
    __attribute__((aligned(4))) uint8_t Data[64];
} FDCAN_MsgPacket_t;

#define CAN_STANDARD            FDCAN_STANDARD_ID
#define CAN_EXTENDED            FDCAN_EXTENDED_ID
#define CAN_DATA_FRAME          FDCAN_DATA_FRAME
#define CAN_MOD                 FDCAN_CLASSIC_CAN
#define CAN_Length              FDCAN_DLC_BYTES_8

#define CAN_ERROR_MOD           FDCAN_ESI_ACTIVE
#define CAN_BRS_MOD             FDCAN_BRS_OFF
#define CAN_EFC                 FDCAN_NO_TX_EVENTS
#define CAN_MESS                0


#define CAN_FILTER_MASK         FDCAN_FILTER_MASK
#define CAN_FILTER_RANGE        FDCAN_FILTER_RANGE
#define CAN_FILTER_DUAL         FDCAN_FILTER_DUAL
#define CAN_FIFO0               FDCAN_FILTER_TO_RXFIFO0
#define CAN_FIFO1               FDCAN_FILTER_TO_RXFIFO1
#define CAN_REJECT_UNMATCHED    FDCAN_REJECT
#define CAN_REJECT_REMOTE       FDCAN_FILTER_REMOTE
#define CAN_MASK_ALL            0x000
#define CAN_MASK_EXACT          0x7FF

#define CAN_START(h)    do { \
    HAL_FDCAN_Start(h); \
    HAL_FDCAN_ActivateNotification(h, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0); \
    HAL_FDCAN_ActivateNotification(h, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0); \
} while(0)



#endif /* FDCAN_MOD */
#endif /* __CAN_DRIVE_H */
