#include "mysql.h"

Mysql& Mysql::getInstance()
{
    static Mysql instance;

    return instance;
}

QSqlError Mysql::addConnection(const QString name, const QString host, const QString user,
                               const QString passwd, int port, const QString dbName)
{
    QSqlError error;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", name);
    db.setHostName(host);
    db.setPort(port);
    db.setUserName(user);
    db.setPassword(passwd);

    if (!dbName.isNull()) {
        db.setDatabaseName(dbName);
        currentDatabaseName = dbName;
    }

    if (!db.open()) {
        error = db.lastError();
        QSqlDatabase::removeDatabase(name);
    }

    return error;
}

QSqlDatabase Mysql::currentConnection() const
{
    return QSqlDatabase::database(currentConnectionName);
}

void Mysql::setCurrenctDatabase(const QString databaseName)
{
    currentDatabaseName = databaseName;
    currentConnection().setDatabaseName(databaseName);
}

QVector<QString> Mysql::database()
{
    QSqlQuery query(currentConnection());

    QString databaseSql = "show databases;";
    query.exec(databaseSql);

    QVector<QString> databases;
    while (query.next()) {
        databases.append(query.value(0).toString());
    }

    return databases;
}

QVector<QString> Mysql::table()
{
    QString databaseSql = "use "+currentDatabaseName+";";

    QSqlQuery query(currentConnection());
    query.exec(databaseSql);

    QString tableSql = "show tables;";
    query.exec(tableSql);

    QVector<QString> tables;
    while (query.next()) {
        tables.append(query.value(0).toString());
    }

    return tables;
}

QVector<QString> Mysql::column()
{
    QString columnSql = "select COLUMN_NAME from information_schema.COLUMNS where TABLE_SCHEMA = :database: and TABLE_NAME = :tableName:";
    QSqlQuery query;
    query.prepare(columnSql);
    query.bindValue(0, currentDatabaseName);
    query.bindValue(1, currenctTableName);
    query.exec();

    QVector<QString> columns;
    while (query.next()) {
        columns.append(query.value(0).toString());
    }

    return columns;
}
