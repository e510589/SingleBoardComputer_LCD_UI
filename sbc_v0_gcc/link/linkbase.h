#ifndef LINKBASE_H
#define LINKBASE_H

#include <QObject>
#include <QDebug>
#include <QByteArray>

#include "config/system_config.h"

class Linkbase : public QObject
{
    Q_OBJECT
public:
    explicit Linkbase(QObject *parent = 0);

    virtual bool open();

    virtual void close();

    virtual bool isOpen();

    virtual int write(QByteArray);

private:

    bool m_b_is_open;

signals:



public slots:

    virtual void slot_ready_read();
    virtual void slot_write(QByteArray);
};

#endif // LINKBASE_H
