#include "databasemanager.h"


DataBaseManager::~DataBaseManager()
{
    m_database.close();
}

bool DataBaseManager::prepare()
{
    m_database = QSqlDatabase::addDatabase("QSQLITE", "Connection");

    m_database.setDatabaseName(m_path_to_db);

    return (!m_database.open()) ? true : false;
}

QSqlDatabase &DataBaseManager::getDatabase()
{
    return m_database;
}
