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

void FDCAN_FilterHeader_Init(FDCAN_MsgPacket_t *packet, uint8_t index, uint32_t type, uint32_t config, uint32_t id1, uint32_t id2)
{
    if (packet->hfdcan == NULL) return;

    packet->FilterHeader.IdType       = CAN_STANDARD;
    packet->FilterHeader.FilterIndex  = index;
    packet->FilterHeader.FilterType   = type;
    packet->FilterHeader.FilterConfig = config;
    packet->FilterHeader.FilterID1    = id1;
    packet->FilterHeader.FilterID2    = id2;
    packet->FilterHeader.RxBufferIndex = 0;
    packet->FilterHeader.IsCalibrationMsg = 0;

    if (HAL_FDCAN_ConfigFilter(packet->hfdcan, &packet->FilterHeader) != HAL_OK) {
        packet->State = CAN_STATE_CONFIG_ERROR;
        return;
    }
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

