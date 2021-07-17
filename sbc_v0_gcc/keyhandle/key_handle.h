#ifndef KEYHANDLE_H
#define KEYHANDLE_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QKeyEvent>
#include "control/tr_module_ctrl.h"
#include "config/system_config.h"
#include "config/system_message_list.h"

class KeyHandle : public QObject
{
    Q_OBJECT
public:
    explicit KeyHandle(QObject *parent = 0);

    static KeyHandle * m_instance;
    static KeyHandle * creatInstance();

    void page_0_handle(int);
    void page_1_handle(int);

private:

    bool m_b_is_writing;

signals:

    void signal_indicate_ui_system_log(int,QString);
    void signal_indicate_ui_update_channel(int);

public slots:
};

#endif // KEYHANDLE_H
