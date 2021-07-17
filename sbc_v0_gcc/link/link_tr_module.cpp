#include "link_tr_module.h"

LinkTRModual * LinkTRModual::m_instance = NULL;

LinkTRModual * LinkTRModual::creatInstance()
{
    if(m_instance == NULL)
    {
        m_instance = new LinkTRModual();
    }

    return m_instance;
}

LinkTRModual::LinkTRModual()
{
    m_serialport = new QSerialPort();
    m_b_is_open = false;

    connect(m_serialport,&QSerialPort::readyRead,this,&LinkTRModual::slot_ready_read);
}

bool LinkTRModual::open()
{
    m_serialport->setPortName(SERIAL_DEVICE_NAME_TR_MODEULE);
    m_serialport->setBaudRate(QSerialPort::Baud115200);
    m_serialport->setDataBits(QSerialPort::Data8);
    m_serialport->setStopBits(QSerialPort::OneStop);
    m_serialport->setParity(QSerialPort::NoParity);
    m_serialport->setFlowControl(QSerialPort::NoFlowControl);

    if(m_serialport->open(QIODevice::ReadWrite))
    {
        m_b_is_open = true;
        return true;
    }

    qDebug() << m_serialport->errorString();

    return false;
}

void LinkTRModual::close()
{
    m_b_is_open = false;
    m_serialport->close();
}

bool LinkTRModual::isOpen()
{
    return m_b_is_open;

}

int LinkTRModual::write(QByteArray data)
{
    int writelength = 0;

    if(m_serialport != NULL)
    {
        if(m_serialport->isOpen())
        {
            writelength = m_serialport->write(data);
        }
    }

    return writelength;
}

void LinkTRModual::slot_write(QByteArray data)
{
//    int writelength = 0;

    if(m_serialport != NULL)
    {
        if(m_serialport->isOpen())
        {
            m_serialport->write(data);
        }
    }
}

void LinkTRModual::slot_ready_read()
{
    QByteArray byteread;
    QByteArray leopard_pdu;

    byteread = m_serialport->readAll();


    if(byteread.length() == 0)
    {
        if(m_restbuffer.length() == 0)
        {
            return;
        }
        else
        {
            leopard_pdu = bufferHandle(m_restbuffer);
        }
    }
    else
    {
        if(m_restbuffer.length()== 0)
        {

            leopard_pdu = bufferHandle(byteread);
        }
        else
        {

            m_restbuffer.append(byteread);

            leopard_pdu = bufferHandle(m_restbuffer);

        }

    }

    if(leopard_pdu.length() != 0)
    {
        QString pdu_string(leopard_pdu);

        TRMsgHandler::creatInstance()->handle(pdu_string);
    }
}

QByteArray LinkTRModual::bufferHandle(QByteArray buffer)
{
    QByteArray pdu;
    m_restbuffer.resize(0);


    int index_som = -1;
    int index_eom = -1;

    if(buffer.length() < 6)
    {
        m_restbuffer.resize(buffer.length());

        for(int i = 0; i < m_restbuffer.length() ; i ++) m_restbuffer[i] = buffer[i];
        pdu.resize(0);
        return pdu;
    }

    for(int i = 0 ; i <buffer.length() -1 ; i++)
    {
        if((buffer.at(i) == 0x21) || (buffer.at(i) == 0x23))
        {
            index_som = i;
            break;
        }
    }

    if(index_som == -1)
    {
        m_restbuffer.resize(buffer.length());
        for(int i = 0; i < m_restbuffer.length() ; i ++) m_restbuffer[i] = buffer[i];
        pdu.resize(0);
        return pdu;
    }

    for(int i = 0; i< buffer.length() ; i++)
    {
        if(buffer.at(i) == 0x0D)
        {
            index_eom = i;
            break;
        }
    }

    if((index_eom <=index_som) || (index_eom == -1))
    {
        m_restbuffer.resize(buffer.length());
        for(int i = 0; i < m_restbuffer.length() ; i ++) m_restbuffer[i] = buffer[i];
        pdu.resize(0);
        return pdu;
    }

    int l = index_eom - index_som+1;

    pdu.resize(l);

    for(int i = 0 ; i < l; i ++) pdu[i] = buffer[index_som+i];

    if((buffer.length() -(pdu.length()+index_som)) > 0)
    {
        m_restbuffer.resize(buffer.length() - (pdu.length()+index_som));

        for(int i = 0; i < m_restbuffer.length() ; i ++) m_restbuffer[i] = buffer[index_eom+1+i];

    }


    return pdu;
}

