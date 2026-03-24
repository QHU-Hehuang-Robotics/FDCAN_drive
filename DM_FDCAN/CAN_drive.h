#ifndef __CAN_drive_h
#define __CAN_drive_h

#include "cmsis_os.h"
#include "cordic.h"
#include "fdcan.h"
#include "gpio.h"

typedef struct {
    uint32_t can_id;
    uint8_t* data;
    uint16_t len;
}FDCAN_TX_DATA_t;

#define CAN_TxHeaderTypeDef     FDCAN_TxHeaderTypeDef
#define CAN_STANDARD            FDCAN_STANDARD_ID
#define CAN_DATA_FRAME          FDCAN_DATA_FRAME
#define CAN_MOD                 FDCAN_CLASSIC_CAN
#define CAN_Length              FDCAN_DLC_BYTES_8
#define CAN_ERROR_MOD           FDCAN_ESI_ACTIVE
#define CAN_BRS_MOD             FDCAN_BRS_OFF
#define CAN_EFC                 FDCAN_NO_TX_EVENTS
#define CAN_MESS                0
#endif
