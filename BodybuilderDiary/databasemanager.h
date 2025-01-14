#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QDir>
#include <QVariant>

using PairType = std::pair<QString, QVariant>;

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

    bool writeData(const QString &query_msg);
    bool writeData(const QString &query_msg,
                   const QVector<PairType> &values);

private:

    DataBaseManager(){}

    bool createWorkFolder();

    QSqlDatabase m_database;

    inline static const QString m_path_to_db{
        QDir::homePath() + "/BODYBUILDERS_DIARY_DATA/data.db"
    };

};


#endif // DATABASEMANAGER_H
