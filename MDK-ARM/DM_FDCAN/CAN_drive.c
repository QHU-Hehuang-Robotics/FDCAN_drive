#include "CAN_drive.h"

void FDCAN_Filter_Config(FDCAN_MsgPacket_t *packet, const FDCAN_FilterConf_t *conf)
{
    FDCAN_FilterTypeDef tmpFilter;

    tmpFilter.IdType       = CAN_STANDARD;
    tmpFilter.FilterIndex  = conf->Index;
    tmpFilter.FilterType   = conf->Type;
    tmpFilter.FilterConfig = conf->Config;
    tmpFilter.FilterID1    = conf->Id1;
    tmpFilter.FilterID2    = conf->Id2;
    tmpFilter.RxBufferIndex = 0;
    tmpFilter.IsCalibrationMsg = 0;

    HAL_FDCAN_ConfigFilter(packet->hfdcan, &tmpFilter);
}

void FDCAN_TxHeader_Init(FDCAN_MsgPacket_t *packet, uint32_t can_id)
{
    packet->TxHeader.Identifier          = can_id;
    packet->TxHeader.IdType              = CAN_STANDARD;
    packet->TxHeader.TxFrameType         = CAN_DATA_FRAME;
    packet->TxHeader.DataLength          = CAN_Length;
    packet->TxHeader.ErrorStateIndicator = CAN_ERROR_MOD;
    packet->TxHeader.BitRateSwitch       = CAN_BRS_MOD;
    packet->TxHeader.FDFormat            = CAN_MOD;
    packet->TxHeader.TxEventFifoControl  = CAN_EFC;
    packet->TxHeader.MessageMarker       = CAN_MESS;
    
    packet->State = CAN_STATE_READY;
}

void FDCAN_Init(FDCAN_MsgPacket_t *packet, FDCAN_FilterConf_t *conf,uint32_t can_id)
{
    HAL_FDCAN_Stop(packet->hfdcan);

    FDCAN_Filter_Config(packet, conf);
    
    HAL_FDCAN_ConfigGlobalFilter(packet->hfdcan, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE);

    FDCAN_TxHeader_Init(packet, can_id);

    if (HAL_FDCAN_Start(packet->hfdcan) != HAL_OK) {
        packet->State = CAN_STATE_CONFIG_ERROR;
        return;
    }
}

void FDCAN_Send_Msg(FDCAN_MsgPacket_t *packet)
{
    if (packet->State != CAN_STATE_NORMAL && packet->State != CAN_STATE_READY) {
        return;
    }
    packet->State = CAN_STATE_BUSY_TX;
    HAL_StatusTypeDef status = HAL_FDCAN_AddMessageToTxFifoQ(packet->hfdcan, &packet->TxHeader, packet->TxData);
    if (status != HAL_OK) {
        packet->State = CAN_STATE_ERROR_WARNING;
    } else {
        packet->State = CAN_STATE_NORMAL;
    }
    return;
}
