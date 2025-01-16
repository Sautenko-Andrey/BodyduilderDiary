#include "databasemanager.h"
#include <QFile>


DataBaseManager::~DataBaseManager()
{
    m_database.close();
}


/*
    Prepearing database for work.
    This function creates databse and tables.
*/
bool DataBaseManager::prepare()
{
    if(!createWorkFolder()){
        return false;
    }

    // Open the database
    m_database = QSqlDatabase::addDatabase("QSQLITE","Connection");
    m_database.setDatabaseName(m_path_to_db);

    if(!m_database.open()){
        return false;
    }
    return true;
}


QSqlDatabase &DataBaseManager::getDatabase()
{
    return m_database;
}


bool DataBaseManager::writeRequestToDB(const QString &query_msg)
{
    if(query_msg.isEmpty()){
        return false;
    }

    // Create a query
    QSqlQuery query(getDatabase());

    if(query.exec(query_msg)){
        return true;
    }

    return false;
}

bool DataBaseManager::writeRequestToDB(const QString &query_msg,
                                const QVector<PairType> &values)
{
    if(query_msg.isEmpty() || values.isEmpty()){
        return false;
    }

    // Create a query
    QSqlQuery query(getDatabase());

    query.prepare(query_msg);

    for(const auto &value : values){
        query.bindValue(value.first, value.second);
    }

    if(query.exec()){
        return true;
    }

    return false;
}


/*
    Function creates a working directory
    where the databse will be exist
*/
bool DataBaseManager::createWorkFolder(){

    QDir dir = QFileInfo(m_path_to_db).absoluteDir();

    if(!dir.exists()){
        if(!dir.mkpath(".")){
            return false;
        }
    }

    if(!QFile::exists(m_path_to_db)){

        QFile databse_file(m_path_to_db);

        if(!databse_file.open(QIODevice::WriteOnly)){
            return false;
        }

        databse_file.close();
    }

    return true;
}
