#include "system_ctrl.h"

SystemCtrl * SystemCtrl::m_instance = NULL;

SystemCtrl * SystemCtrl::creatInstance()
{
    if(m_instance == NULL)
    {
        m_instance = new SystemCtrl();
    }

    return m_instance;
}

SystemCtrl::SystemCtrl(QObject *parent) : QObject(parent)
{

}

void SystemCtrl::runBootProcess()
{
    global_b_serial_is_open = LinkTRModual::creatInstance()->open();
    qDebug() << QThread::currentThreadId();
    Taskboot::creatInstance()->moveToThread(&mBootThread);
    connect(&mBootThread,&QThread::started, Taskboot::creatInstance(),&Taskboot::slot_run_task);
    connect(&mBootThread,&QThread::finished, &mBootThread,&QObject::deleteLater);
    mBootThread.start();
}

void SystemCtrl::systemDelay(int delay)
{
    QEventLoop waiter;
    QTimer::singleShot(delay,&waiter,&QEventLoop::quit);
    waiter.exec();
}

