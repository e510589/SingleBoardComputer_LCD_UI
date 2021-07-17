#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QtSql/QtSql>
#include <QDebug>
#include <QList>
#include "config/system_config.h"
#include "item/channel_item.h"

class DBManager : public QObject
{
    Q_OBJECT
public:
    explicit DBManager(QObject *parent = 0);

   static DBManager * m_instance;

   static DBManager * creatInstance();

   QList<ChannelItem *> m_list_channelList;

   bool openDB();

   bool closeDB();

   bool isDBOpen();

   bool loadChannel();

   bool insertChannle(ChannelItem);

   bool deleteChannel(int);

   bool updateChannel(ChannelItem);


private:

   bool m_b_db_is_open;

   QSqlDatabase db;

   QSqlQuery * qry;

signals:

public slots:
};

#endif // DBMANAGER_H
