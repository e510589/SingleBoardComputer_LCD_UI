#include "task_boot.h"

Taskboot * Taskboot::m_instance = NULL;

Taskboot * Taskboot::creatInstance()
{
    if(m_instance == NULL)
    {
        m_instance = new Taskboot();
    }

    return m_instance;
}

Taskboot::Taskboot(QObject *parent) : QObject(parent)
{

}

void Taskboot::slot_run_task()
{
    int m_b_boot_successed = false;

    SystemCtrl::creatInstance()->systemDelay(10000);

    emit signal_update_ui(0,MSG_SERIAL_OPEN);

    if(global_b_serial_is_open)
    {
        emit signal_update_ui(1,MSG_OK);

        emit signal_update_ui(0,MSG_ACTIVATE_TR_CTRL_IF);

        global_b_tr_data_ctrl_interface_enabled = TRModuleControl::creatInstance()->open_Data_Ctrl_Interface();

        if(global_b_tr_data_ctrl_interface_enabled)
        {
            emit signal_update_ui(1,MSG_OK);
            emit signal_update_ui(0,MSG_LOAD_CHANNEL_DATA);

            if(DBManager::creatInstance()->isDBOpen())
            {
                qDebug() << "DB has benn opened";

                if(DBManager::creatInstance()->loadChannel())
                {
                    emit signal_update_ui(1,MSG_OK);

                    emit signal_update_ui(0,MSG_UPDATE_RADIO_CHANNEL_DATA);
                    if(TRModuleControl::creatInstance()->updateChannelList())
                    {
                        emit signal_update_ui(1,MSG_OK);

                        if(TRModuleControl::creatInstance()->setCurrentChannel(global_i_current_channel_index))
                        {
                            m_b_boot_successed = true;
                        }

                    }else {
                        emit signal_update_ui(1,MSG_FAILED);
                    }

                }else{
                    emit signal_update_ui(1,MSG_FAILED);
                }

            }else {
                emit signal_update_ui(1,MSG_FAILED);
            }


        }else {
            emit signal_update_ui(1,MSG_FAILED);
        }

    }else {
        emit signal_update_ui(1,MSG_FAILED);
    }

    if(m_b_boot_successed)
    {
        emit signal_update_ui(0,MSG_BOOT_COMPLETE);
        emit signal_update_ui(0,MSG_INDICATE_USER_ABOUT_TO_CHANGE_PAGE);
        SystemCtrl::creatInstance()->systemDelay(5000);

        emit signal_update_stacked_index(1);
    }else{
        emit signal_update_ui(0,MSG_BOOT_FAILED);
    }

}


