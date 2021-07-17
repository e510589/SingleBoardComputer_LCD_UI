#include "channel_item.h"

ChannelItem::ChannelItem()
{

}

ChannelItem::ChannelItem(int Index, QString name, int TxFreq, int RxFreq, int Power, int Modulation)
{
    this->index = Index;
    this->channelName = name;
    this->txFreq = TxFreq;
    this->rxFreq = RxFreq;
    this->power = Power;
    this->modulation = Modulation;
}

