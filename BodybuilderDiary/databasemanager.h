#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QDir>

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


private:
    DataBaseManager(){}

    QSqlDatabase m_database;

    inline static const QStringList m_query_msgs{

    };

    inline static const QString m_path_to_db{
        QDir::homePath() + "/BODYBUILDERS_DIARY_DATA/data.db"
    };

    bool createDB(const QString &db_path, const QStringList &query_msgs);

};

#endif // DATABASEMANAGER_H
