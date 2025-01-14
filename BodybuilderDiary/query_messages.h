#ifndef QUERY_MESSAGES_H
#define QUERY_MESSAGES_H

#include<QString>

// For the customers table
const QString customers_query = "CREATE TABLE IF NOT EXISTS customers ("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                "full_name VARCHAR(35), "
                                "age INTEGER, "
                                "sex INTEGER, "
                                "height INTEGER, "
                                "weight INTEGER, "
                                "notes TEXT)";

// For adding a new customer
const QString new_customer_query = "INSERT INTO customers ("
                          "full_name, age, sex, height, weight, notes)"
                          " VALUES"
                          "(:i_full_name, :i_age, :i_sex,"
                          " :i_height, :i_weight, :i_notes)";

// For the exercise table
const QString exercises_query = "CREATE TABLE IF NOT EXISTS exercises ("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                "name VARCHAR(50), "
                                "description TEXT, "
                                "type INTEGER)";



#endif // QUERY_MESSAGES_H
