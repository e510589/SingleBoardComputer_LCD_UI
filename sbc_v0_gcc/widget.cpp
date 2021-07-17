#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    KeyHandle::creatInstance();
    ui->setupUi(this);
    ui->label_system_log->setVisible(false);

    ui->stackedWidget->setFocus();// the direction key won't trigger ketPressEvent if you didn't set focus on stackwidget

    ui->textBrowser_boot->append("Welcome PRC-506 Radio...\n\r");
    ui->stackedWidget->setCurrentIndex(global_i_page_index);
    connect(Taskboot::creatInstance(),&Taskboot::signal_update_ui,this,&Widget::slot_update_text_browser);
    connect(Taskboot::creatInstance(),&Taskboot::signal_update_stacked_index,this,&Widget::slot_update_stacked_widget);
    connect(KeyHandle::creatInstance(),&KeyHandle::signal_indicate_ui_update_channel,this,&Widget::slot_update_channel_info);
    connect(KeyHandle::creatInstance(),&KeyHandle::signal_indicate_ui_system_log,this,&Widget::slot_update_system_log);
    DBManager::creatInstance()->openDB();
    SystemCtrl::creatInstance()->runBootProcess();

}

Widget::~Widget()
{
    qDebug() << "123546";
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent * event)
{    
    switch (global_i_page_index) {
    case 0:
        KeyHandle::creatInstance()->page_0_handle(event->key());
        break;
    case 1:
        KeyHandle::creatInstance()->page_1_handle(event->key());
        break;
    case 2:
        break;
    default:
        break;
    }

}

void Widget::slot_update_text_browser(int mode,QString msg)
{
    switch (mode) {
    case 0:

        ui->textBrowser_boot->append(msg);

        break;
    case 1 :

        ui->textBrowser_boot->insertPlainText(msg);

        break;
    }
}

void Widget::slot_update_stacked_widget(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
    global_i_page_index=index;
}

void Widget::slot_update_system_log(int visibal_time,QString msg)
{
    ui->label_system_log->setText(msg);
    ui->label_system_log->setVisible(true);

    if(visibal_time > 0)
    {
        SystemCtrl::creatInstance()->systemDelay(visibal_time);
        ui->label_system_log->setVisible(false);
    }
}

void Widget::slot_update_channel_info(int index)
{
    updateChannelInfo(index);
}



void Widget::on_stackedWidget_currentChanged(int arg1)
{

    switch (arg1) {
    case 0:

        break;

    case 1:

        updateChannelInfo(global_i_current_channel_index);

        break;

    default:
        break;
    }
}

void Widget::updateChannelInfo(int ch_index)
{
    ui->label_ch_index->setText(QString::number(DBManager::creatInstance()->m_list_channelList.value(ch_index)->index).rightJustified(3,'0'));
    ui->label_ch_name->setText(DBManager::creatInstance()->m_list_channelList.value(ch_index)->channelName);
    ui->label_freq->setText(QString::number(DBManager::creatInstance()->m_list_channelList.value(ch_index)->txFreq).rightJustified(9,'0'));
    ui->label_mod->setText(getModulationType(DBManager::creatInstance()->m_list_channelList.value(ch_index)->modulation));
    ui->label_power->setText(getModulationType(DBManager::creatInstance()->m_list_channelList.value(ch_index)->power));
    ui->label_vswr->setText("x.xxx");
    ui->label_tune_state->setText("NOT TUNE");
}

QString Widget::getModulationType(int mode)
{
    QString local_s_mode = "";
    switch (mode) {
    case 0:
        local_s_mode = "LSB";
        break;
    case 1:
        local_s_mode = "USB";
        break;
    case 2:
        local_s_mode = "FM";
        break;
    case 3 :
        local_s_mode = "AM";
        break;
    case 4:
        local_s_mode = "CW";
        break;
    default:
        break;
    }

    return local_s_mode;
}

QString Widget::getPowerLevel(int level)
{

    if(level >= 10)
    {
        return "HIGH";
    }else if(level <10){
        return "LOW";
    }

    return "ERROR";
}
