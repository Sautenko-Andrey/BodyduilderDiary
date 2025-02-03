#include "databasemanager.h"
#include <QFile>
#include "query_messages.h"


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

    // Create users and exercises table and indexes for them
    auto res_exercises = writeRequestToDB(CustomQuery::exercises_query);

    auto res_exercises_index =
        writeRequestToDB(CustomQuery::exercises_index_query);

    auto res_users = writeRequestToDB(CustomQuery::customers_query);

    auto res_users_indexing =
        writeRequestToDB(CustomQuery::customers_index_query);

    if(!res_exercises ||
       !res_users ||
       !res_users_indexing ||
       !res_exercises_index)
    {
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
