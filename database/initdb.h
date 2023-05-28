#ifndef INITDB_H
#define INITDB_H

#include <QtSql>

QSqlError initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("localhost");
    db.setDatabaseName("kurs_db");
    db.setUserName("root");
    db.setPassword("root");

    if (!db.open())
        return db.lastError();

    qDebug() << "Db Ok";

    return QSqlError();
}

#endif // INITDB_H
