#ifndef TRMSGHANDLER_H
#define TRMSGHANDLER_H

#include <QObject>
#include <QString>
#include <QDebug>
#include "config/system_config.h"
#include "control/tr_module_ctrl.h"

class TRMsgHandler : public QObject
{
    Q_OBJECT
public:
    explicit TRMsgHandler(QObject *parent = 0);

    static TRMsgHandler * creatInstance();

    static TRMsgHandler * m_instance;

    void handle(QString);

signals:


    void signal_recv_data_ctrl_interface_enabled_ack();
    void signal_recv_save_channel_to_memory_ack();
    void signal_recv_set_current_channel_ack();

public slots:
};

#endif // TRMSGHANDLER_H
