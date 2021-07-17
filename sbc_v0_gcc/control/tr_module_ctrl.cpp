#include "tr_module_ctrl.h"

TRModuleControl * TRModuleControl::m_instance = NULL;

TRModuleControl * TRModuleControl::creatInstance()
{
    if(m_instance == NULL)
    {
        m_instance = new TRModuleControl();
        connect(m_instance,&TRModuleControl::signals_write_cmd,LinkTRModual::creatInstance(),&LinkTRModual::slot_write);
    }


    return m_instance;
}

TRModuleControl::TRModuleControl(QObject *parent) : QObject(parent)
{
    m_b_recv_data_ctrl_interface_enabled_ack = false;
    m_b_recv_save_channel_to_memory_ack = false;

}

bool TRModuleControl::open_Data_Ctrl_Interface()
{
    if(LinkTRModual::creatInstance()->isOpen())
    {
        int timout = 0;
        m_b_recv_data_ctrl_interface_enabled_ack = false;
        QByteArray pdu("!PCI,LOC,9B9E3423B8BED32CBA2517E32A61B41E433DDE81\r");
        emit signals_write_cmd(pdu);

        while(!m_b_recv_data_ctrl_interface_enabled_ack)
        {
            if(timout == 50) break;
            SystemCtrl::creatInstance()->systemDelay(50);
            timout++;
        }

        return m_b_recv_data_ctrl_interface_enabled_ack;
    }

    return false;
}

bool TRModuleControl::saveChannelToMemory(ChannelItem * item)
{
    if(LinkTRModual::creatInstance()->isOpen())
    {
        int timout = 0;
        m_b_recv_save_channel_to_memory_ack = false;
        QString cmd = "#CHN=@index@,TYP=S,NM=@name@,RXF=@freq@,TXF=@freq@,TXP=@txp@,SQM=NONE,MOD=@mod@,SQL=SVD\r";
        cmd = cmd.replace("@index@",QString::number(item->index).rightJustified(3,'0')).replace("@name@",item->channelName)
                .replace("@freq@",QString::number(item->txFreq).rightJustified(9,'0')).replace("@txp@",QString::number(item->power).rightJustified(2,'0'));

        switch (item->modulation) {
        case 0:
            cmd = cmd.replace("@mod@","LSB");
            break;
        case 1:
            cmd = cmd.replace("@mod@","USB");
            break;
        case 2:
            cmd = cmd.replace("@mod@","FM");
            break;
        case 3 :
            cmd = cmd.replace("@mod@","AM");
            break;
        case 4:
            cmd = cmd.replace("@mod@","CW");
            break;
        default:
            break;
        }

        QByteArray pdu = cmd.toUtf8();
        emit signals_write_cmd(pdu);

        while(!m_b_recv_save_channel_to_memory_ack)
        {
            if(timout == 50) break;
            SystemCtrl::creatInstance()->systemDelay(50);
            timout++;
        }

        return m_b_recv_save_channel_to_memory_ack;

    }

    return false;
}

bool TRModuleControl::setCurrentChannel(int index)
{
    if(LinkTRModual::creatInstance()->isOpen())
    {
        int timeout = 0;
        m_b_recv_set_current_channel_ack = false;

        QString cmd = "!CHN,@index@\r";
        cmd = cmd.replace("@index@",QString::number(index).rightJustified(3,'0'));

        qDebug() << cmd;

        QByteArray pdu = cmd.toUtf8();
        emit signals_write_cmd(pdu);

        while(!m_b_recv_set_current_channel_ack)
        {
            if(timeout == 50) break;
            SystemCtrl::creatInstance()->systemDelay(50);
            timeout++;
        }

        return m_b_recv_set_current_channel_ack;
    }

    return false;
}


bool TRModuleControl::updateChannelList()
{

    if(DBManager::creatInstance()->m_list_channelList.length() != 0)
    {
        for(int i = 0 ;i < DBManager::creatInstance()->m_list_channelList.length(); i++)
        {
            qDebug() << "Index:" << i ;
            if(!saveChannelToMemory(DBManager::creatInstance()->m_list_channelList.value(i)))
            {
                return false;
            }
        }

        return true;
    }

    return false;
}

void TRModuleControl::slots_recv_data_ctrl_interface_enabled_ack()
{
    m_b_recv_data_ctrl_interface_enabled_ack = true;
}

void TRModuleControl::slots_recv_save_channel_to_memory_ack()
{
    m_b_recv_save_channel_to_memory_ack = true;
}

void TRModuleControl::slots_recv_set_current_channel_ack()
{
    m_b_recv_set_current_channel_ack = true;
}

