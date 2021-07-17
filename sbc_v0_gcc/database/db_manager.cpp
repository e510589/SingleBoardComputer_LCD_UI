#include "db_manager.h"

DBManager * DBManager::m_instance = NULL;

DBManager * DBManager::creatInstance()
{
    if(m_instance == NULL)
    {
        m_instance = new DBManager();
    }

    return m_instance;
}

DBManager::DBManager(QObject *parent) : QObject(parent)
{
    m_b_db_is_open = false;
}

bool DBManager::openDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DB_PATH);

    if(db.open())
    {
        m_b_db_is_open = true;
        qry = new QSqlQuery(db);
        return true;
    }

    qDebug() << db.lastError();

    return false;

}

bool DBManager::isDBOpen()
{
    return m_b_db_is_open;
}

bool DBManager::loadChannel()
{

    if(db.isOpen())
    {
        if(qry->exec("select * from ChannelTable"))
        {
            while(qry->next())
            {
                ChannelItem  * item = new ChannelItem;
                item->index = qry->value(0).toInt();
                item->channelName = qry->value(10).toString();
                item->txFreq = qry->value(6).toInt();
                item->rxFreq = qry->value(7).toInt();
                item->power = qry->value(8).toInt();
                item->modulation = qry->value(9).toInt();

                m_list_channelList << item;

            }

            return true;
        }
    }

    qDebug() << db.lastError();

    return false;
}

bool DBManager::insertChannle(ChannelItem item)
{
    if(db.isOpen())
    {
        qry->prepare("insert into ChannelTable values(?,?,?,?,?,?,?,?,?,?,?)");
        qry->bindValue(0,item.index);
        qry->bindValue(1,item.PresetSoundEnable);
        qry->bindValue(5,item.PresetAutoResponseBlocked);
        qry->bindValue(6,item.rxFreq);
        qry->bindValue(7,item.txFreq);
        qry->bindValue(8,item.power);
        qry->bindValue(9,item.modulation);
        qry->bindValue(10,item.channelName);

        if(qry->exec())
        {
            return true;
        }

        return false;

    }

    return false;
}

bool DBManager::deleteChannel(int index)
{
    if(db.isOpen())
    {
        qry->prepare("delete from ChannelTable where ChannelIndex  = ?");
        qry->addBindValue(index);

        if(qry->exec())
        {
            return true;
        }

        return false;
    }

    return false;
}

bool DBManager::updateChannel(ChannelItem item)
{
    if(db.isOpen())
    {
        qry->prepare("update ChannelTable set PresetSoundEnable = ?, PresetAutoResponseBlocked = ?, RxFrequency = ?, TxFrequency = ?, TXPower = ?, TXRxMode = ?, ChannelName = ? where ChannelIndex = ?");
        qry->bindValue(0,item.PresetSoundEnable);
        qry->bindValue(1,item.PresetAutoResponseBlocked);
        qry->bindValue(2,item.rxFreq);
        qry->bindValue(3,item.txFreq);
        qry->bindValue(4,item.power);
        qry->bindValue(5,item.modulation);
        qry->bindValue(6,item.channelName);
        qry->bindValue(7,item.index);

        if(qry->exec())
        {
            return true;
        }

        return false;
    }

    return false;
}

bool DBManager::closeDB()
{
    db.close();

    if(!db.isOpen())
    {
        m_b_db_is_open = false;
    }

    return false;
}
