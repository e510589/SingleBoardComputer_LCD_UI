#ifndef LINK_TR_MODULE_H
#define LINK_TR_MODULE_H
#include <QByteArray>
#include <QSerialPort>
#include "linkbase.h"
#include "msghandler/tr_msg_handler.h"


class LinkTRModual : public Linkbase
{
public:


    static LinkTRModual * creatInstance();

    static LinkTRModual * m_instance;

    bool open();

    void close();

    bool isOpen();

    int write(QByteArray);

private:

    LinkTRModual();

    bool m_b_is_open;

    QSerialPort * m_serialport;

    QByteArray m_restbuffer;

    QByteArray bufferHandle(QByteArray);

signals:


public slots:

    void slot_ready_read();

    void slot_write(QByteArray);



};

#endif // LINK_TR_MODULE_H
