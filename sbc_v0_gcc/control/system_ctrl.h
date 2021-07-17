#ifndef SYSTEM_CTRL_H
#define SYSTEM_CTRL_H

#include <QObject>
#include <QString>
#include <QThread>
#include <QTimer>
#include <QEventLoop>
#include "config/system_config.h"

#include "task_boot.h"

class SystemCtrl : public QObject
{
    Q_OBJECT
public:
    explicit SystemCtrl(QObject *parent = 0);

    static SystemCtrl * creatInstance();

    static SystemCtrl * m_instance;

    void runBootProcess();

    void systemDelay(int);

private:

    QThread mBootThread;

signals:

public slots:
};

#endif // SYSTEM_CTRL_H
