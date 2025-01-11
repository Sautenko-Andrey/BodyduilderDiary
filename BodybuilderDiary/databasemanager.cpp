#include "databasemanager.h"
#include <QSqlQuery>
#include <QDir>
#include <QFile>

#include"query_messages.h"


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
    bool result = createDB(m_path_to_db, query_msgs);

    return result ? true : false;
}

QSqlDatabase &DataBaseManager::getDatabase()
{
    return m_database;
}


/*
    Create a database from scratch if it doesn't exist
    in the user's home path. Check if the directory exists;
    if not, create it.
*/
bool DataBaseManager::createDB(const QString &db_path,
                               const QStringList &query_msgs){

    QDir dir = QFileInfo(db_path).absoluteDir();

    if(!dir.exists()){
        if(!dir.mkpath(".")){
            return false;
        }
    }

    if(!QFile::exists(db_path)){

        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

        db.setDatabaseName(db_path);

        if(!db.open()){
            return false;
        }

        for(const auto &msg : query_msgs){
            // Create the table
            QSqlQuery query;

            if(!query.exec(msg)){
                return false;
            }
        }

        db.close();
    }

    return true;
}
