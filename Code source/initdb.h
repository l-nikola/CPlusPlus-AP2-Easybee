#ifndef INITDB_H
#define INITDB_H
#include <QtSql>
#include <QMessageBox>
#include <QCoreApplication>
QSqlError initDB()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setDatabaseName("easybeebdd");
    database.setUserName("root");
    database.setPassword("");
    if (database.open()) {
        return database.lastError();
    }
    return QSqlError();
}
#endif // INITDB_H
