#include "key_handle.h"

KeyHandle * KeyHandle::m_instance = NULL;

KeyHandle * KeyHandle::creatInstance()
{
    if(m_instance == NULL)
    {
        m_instance = new KeyHandle();
    }

    return m_instance;
}

KeyHandle::KeyHandle(QObject *parent) : QObject(parent)
{    
    m_b_is_writing = false;
}


void KeyHandle::page_0_handle(int keycode)
{
    switch (keycode) {
    case KEY_CODE_ENTER:

        break;
    default:
        break;
    }
}

void KeyHandle::page_1_handle(int keycode)
{
    if(!m_b_is_writing)
    {
        switch (keycode) {
        case KEY_CODE_ENTER:

            break;
        case KEY_CODE_UP:

            m_b_is_writing = true;

            if(global_i_current_channel_index+1 < DBManager::creatInstance()->m_list_channelList.size())
            {
                if(TRModuleControl::creatInstance()->setCurrentChannel(global_i_current_channel_index+1)){
                    global_i_current_channel_index++;
                    emit signal_indicate_ui_update_channel(global_i_current_channel_index);
                    m_b_is_writing = false;
                    return;
                }else {
                    emit signal_indicate_ui_system_log(0,ERROR_CHANNEL_CHANGE_FAILED);
                    m_b_is_writing = false;
                }
            }else {
                if(TRModuleControl::creatInstance()->setCurrentChannel(0)){
                    global_i_current_channel_index = 0;
                    emit signal_indicate_ui_update_channel(global_i_current_channel_index);
                    m_b_is_writing = false;
                    return;
                }else {
                    emit signal_indicate_ui_system_log(0,ERROR_CHANNEL_CHANGE_FAILED);
                    m_b_is_writing = false;
                }
            }

            break;
        case KEY_CODE_DOWN:

            m_b_is_writing = true;

            if(global_i_current_channel_index > 0)
            {
                if(TRModuleControl::creatInstance()->setCurrentChannel(global_i_current_channel_index-1)){
                    global_i_current_channel_index--;
                    emit signal_indicate_ui_update_channel(global_i_current_channel_index);
                    m_b_is_writing = false;
                    return;
                }else {
                    emit signal_indicate_ui_system_log(0,ERROR_CHANNEL_CHANGE_FAILED);
                    m_b_is_writing = false;
                }
            }else {
                if(TRModuleControl::creatInstance()->setCurrentChannel(DBManager::creatInstance()->m_list_channelList.size()-1)){
                    global_i_current_channel_index = DBManager::creatInstance()->m_list_channelList.size()-1;
                    emit signal_indicate_ui_update_channel(global_i_current_channel_index);
                    m_b_is_writing = false;
                    return;
                }else {
                    emit signal_indicate_ui_system_log(0,ERROR_CHANNEL_CHANGE_FAILED);
                    m_b_is_writing = false;
                }
            }
            break;
        case KEY_CODE_LEFT:
            break;
        case KEY_CODE_RIGHT:
            break;
        case KEY_CODE_ESC:
            break;
        }
    }

}
