#ifndef QUERY_MESSAGES_H
#define QUERY_MESSAGES_H

#include<QString>

namespace CustomQuery {
// For the customers table
const QString customers_query = "CREATE TABLE IF NOT EXISTS customers ("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                "full_name VARCHAR(35) UNIQUE, "
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

const QString add_exercise_query = "INSERT INTO exercises ("
                                   "name, description, type)"
                                   " VALUES"
                                   "(:i_name, :i_descr, :i_type);";


// For reading all customers
const QString read_customers_query = "SELECT "
                                     "full_name, age, sex,"
                                     " height, weight, notes "
                                     "FROM customers;";

// For reading all customers with id including
const QString read_customers_query_all = "SELECT "
                                         "full_name, age, sex,"
                                         " height, weight, notes "
                                         "FROM customers;";

// For updating a customer
const QString update_user_query = "UPDATE customers "
                                  "SET "
                                  "full_name = :i_new_name, "
                                  "age = :i_age, "
                                  "sex = :i_sex, "
                                  "height = :i_height, "
                                  "weight = :i_weight, "
                                  "notes = :i_notes "
                                  "WHERE full_name = :i_full_name;";



}// End CustomQuery namespace




#endif // QUERY_MESSAGES_H
