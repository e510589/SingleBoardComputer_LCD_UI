#ifndef GENERALTRMODULECONTROL_H
#define GENERALTRMODULECONTROL_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include "link/link_tr_module.h"
#include "item/channel_item.h"
#include "control/system_ctrl.h"
#include "database/db_manager.h"

class TRModuleControl : public QObject
{
    Q_OBJECT
public:
    explicit TRModuleControl(QObject *parent = 0);

    static TRModuleControl * creatInstance();

    static TRModuleControl * m_instance;

    bool open_Data_Ctrl_Interface();

    bool saveChannelToMemory(ChannelItem *);

    bool updateChannelList();

    bool setCurrentChannel(int);


private:

    bool m_b_recv_data_ctrl_interface_enabled_ack;
    bool m_b_recv_save_channel_to_memory_ack;
    bool m_b_recv_set_current_channel_ack;



signals:

    void signals_write_cmd(QByteArray);


public slots:

    void slots_recv_data_ctrl_interface_enabled_ack();
    void slots_recv_save_channel_to_memory_ack();
    void slots_recv_set_current_channel_ack();
};

#endif // GENERALTRMODULECONTROL_H
