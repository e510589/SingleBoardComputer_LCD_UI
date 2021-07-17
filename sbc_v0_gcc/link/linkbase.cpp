#include "linkbase.h"

Linkbase::Linkbase(QObject *parent) : QObject(parent)
{

}

bool Linkbase::open()
{
    return false;
}

void Linkbase::close()
{

}

bool Linkbase::isOpen()
{
    return m_b_is_open;
}

int Linkbase::write(QByteArray pdu)
{

    return pdu.length();
}

void Linkbase::slot_ready_read()
{

}

void Linkbase::slot_write(QByteArray data)
{
    data.clear();
}

