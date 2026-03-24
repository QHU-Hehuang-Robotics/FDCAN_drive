#include "CAN_drive.h"


void CAN_TxHeader_Init(FDCAN_TX_DATA_t data,CAN_TxHeaderTypeDef DM_TxHeaderTypeDef)
{
    DM_TxHeaderTypeDef.Identifier           = data.can_id;
    DM_TxHeaderTypeDef.IdType               = CAN_STANDARD;
    DM_TxHeaderTypeDef.TxFrameType          = CAN_DATA_FRAME;
    DM_TxHeaderTypeDef.DataLength           = CAN_Length;
    DM_TxHeaderTypeDef.ErrorStateIndicator  = CAN_ERROR_MOD;
    DM_TxHeaderTypeDef.BitRateSwitch        = CAN_BRS_MOD;
    DM_TxHeaderTypeDef.FDFormat             = CAN_MOD;
    DM_TxHeaderTypeDef.TxEventFifoControl   = CAN_EFC;
    DM_TxHeaderTypeDef.MessageMarker        = CAN_MESS;
}

