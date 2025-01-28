#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QDir>
#include <QVariant>
#include <QMap>
#include <QSqlQuery>
#include "appstruct.h"
#include <concepts>

using PairType = std::pair<QString, QVariant>;

// Create a concept fpr the template method (read data from database)
template<typename T>
concept DerivedFromAppStruct = std::derived_from<T, AppStruct>;

class DataBaseManager
{
public:

    DataBaseManager(const DataBaseManager &manager) = delete;
    DataBaseManager& operator=(const DataBaseManager &manager) = delete;

    ~DataBaseManager();

    static DataBaseManager& getInstance(){
        static DataBaseManager manager;
        return manager;
    }

    bool prepare();

    QSqlDatabase& getDatabase();

    bool writeRequestToDB(const QString &query_msg);
    bool writeRequestToDB(const QString &query_msg,
                   const QVector<PairType> &values);


    template<DerivedFromAppStruct T>
    bool readRequestToDB(const QString &query_msg,
                         QMap<QString, std::shared_ptr<T>> &data,
                         int fields_num);

private:

    DataBaseManager(){}

    bool createWorkFolder();

    QSqlDatabase m_database;

    inline static const QString m_path_to_db{
        QDir::homePath() + "/BODYBUILDERS_DIARY_DATA/data.db"
    };

};


// Template methods definition
template<DerivedFromAppStruct T>
bool DataBaseManager::readRequestToDB(const QString &query_msg,
                     QMap<QString, std::shared_ptr<T>> &data,
                     int fields_num){


    if(constexpr int min_fields{1};
       query_msg.isEmpty() || fields_num < min_fields)
    {
        return false;
    }

    QSqlQuery query(getDatabase());

    if(!query.exec(query_msg)){
        return false;
    }

    while(query.next()){

        QVector<QVariant> fields;
        std::shared_ptr<T> ptr_struct = std::make_shared<T>();


        for(int i{0}; i < fields_num; ++i){
            fields.push_back(query.value(i));
        }

        ptr_struct->setStruct(fields);

        // Save index as key, and other as value
        data.insert(query.value(0).toString(), ptr_struct);

    }

    return true;
}


#endif // DATABASEMANAGER_H
