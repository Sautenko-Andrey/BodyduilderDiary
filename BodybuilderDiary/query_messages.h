#ifndef QUERY_MESSAGES_H
#define QUERY_MESSAGES_H

#include<QString>
#include<QStringList>


// Namespace making these messages private
namespace {

// For the customers table
const QString customers_query = "CREATE TABLE IF NOT EXISTS customers ("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                "full_name VARCHAR(35), "
                                "age INTEGER, "
                                "sex INTEGER, "
                                "height INTEGER, "
                                "weight INTEGER, "
                                "notes TEXT)";

// For the exercise table
const QString exercises_query = "CREATE TABLE IF NOT EXISTS exercises ("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                "name VARCHAR(50), "
                                "description TEXT, "
                                "type INTEGER)";

}



const QStringList query_msgs{
    customers_query,
    exercises_query
};


#endif // QUERY_MESSAGES_H
