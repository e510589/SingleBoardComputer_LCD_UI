#ifndef CHANNELITEM2_H
#define CHANNELITEM2_H

#include <QString>


class ChannelItem
{
public:
    ChannelItem();
    ChannelItem(int,QString,int,int,int,int);

    int index;
    QString channelName;
    int txFreq;
    int rxFreq;
    int power;
    int modulation;  //   0: USB  1:LSB  2:FM  3:AM  4:CW
    int PresetSoundEnable;
    int PresetSoundAddress;
    int PresetSoundInterval;
    int PresetNextSound;
    int PresetAutoResponseBlocked;
};

#endif // CHANNELITEM2_H
