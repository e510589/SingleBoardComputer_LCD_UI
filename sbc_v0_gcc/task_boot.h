#ifndef TASK_BOOT_H
#define TASK_BOOT_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "config/system_config.h"
#include "link/link_tr_module.h"
#include "config/system_message_list.h"
#include "control/tr_module_ctrl.h"
#include "msghandler/tr_msg_handler.h"
#include "control/system_ctrl.h"
#include "database/db_manager.h"

class Taskboot : public QObject
{
    Q_OBJECT
public:
    explicit Taskboot(QObject *parent = 0);

    static Taskboot * creatInstance();

    static Taskboot * m_instance;

private:



signals:

    void signal_update_ui(int,QString);
    void signal_update_stacked_index(int);

public slots:

    void slot_run_task();
};

#endif // TASK_BOOT_H
