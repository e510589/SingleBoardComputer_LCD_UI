#include "tr_msg_handler.h"

TRMsgHandler * TRMsgHandler::m_instance = NULL;

TRMsgHandler * TRMsgHandler::creatInstance()
{
    if(m_instance == NULL)
    {
        m_instance = new TRMsgHandler();

        connect(m_instance,&TRMsgHandler::signal_recv_data_ctrl_interface_enabled_ack, TRModuleControl::creatInstance() , &TRModuleControl::slots_recv_data_ctrl_interface_enabled_ack );
        connect(m_instance,&TRMsgHandler::signal_recv_save_channel_to_memory_ack,TRModuleControl::creatInstance(), &TRModuleControl::slots_recv_save_channel_to_memory_ack);
        connect(m_instance,&TRMsgHandler::signal_recv_set_current_channel_ack,TRModuleControl::creatInstance(),&TRModuleControl::slots_recv_set_current_channel_ack);
    }

    return m_instance;
}

TRMsgHandler::TRMsgHandler(QObject *parent) : QObject(parent)
{


}

void TRMsgHandler::handle(QString msg)
{
    qDebug() << msg;
    if(msg.contains("!VERS"))  //!VERS,6.254u-NCS,LEOPARD1,1.6,170\n\r
    {
       emit signal_recv_data_ctrl_interface_enabled_ack();

    }else if (msg.contains("!ACK")) {
        if(msg.contains("65")) // Save Channel to Memory ACK Received
        {
            emit signal_recv_save_channel_to_memory_ack();
            return;
        }else if (msg.contains("0A")) {
            emit signal_recv_set_current_channel_ack();
            return;
        }
    }
}

