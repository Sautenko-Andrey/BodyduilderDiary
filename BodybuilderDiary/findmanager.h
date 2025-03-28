#pragma once
#include "databasemanager.h"
#include "query_messages.h"
#include <QMap>
#include <concepts>
#include "appstruct.h"
#include <QListWidget>
#include <algorithm>
#include <QTextStream>
#include <QCompleter>
#include <QLineEdit>




template<typename T>
concept AppStructDerived = std::is_base_of_v<AppStruct, T>;

class FindManager {

public:

    template<AppStructDerived T>
    static bool readDataFromDB(const QString &query_msg,
                               QMap<QString, std::shared_ptr<T>> &data,
                               int fields_num);


    template<AppStructDerived T>
    static void fillListWidget(QListWidget *list_widget,
                               const QMap<QString, std::shared_ptr<T>> &data);


    template<AppStructDerived T>
    static void textEdited(QListWidget *list_widget,
                    QLineEdit *search_line,
                    const QMap<QString, std::shared_ptr<T>> &data,
                    QObject *object_ptr);


    template<AppStructDerived T>
    static bool search(const QMap<QString, std::shared_ptr<T>> &data,
                const QLineEdit *search_line,
                QListWidget *list_widget);


    template<AppStructDerived T>
    static void onClearAllButtonClicked(QLineEdit *search_line,
                                  QListWidget *list_widget,
                                  const QMap<QString, std::shared_ptr<T>> &data);


    template<AppStructDerived T>
    static void onShowItemsListButtonClicked(QListWidget *list_widget,
                                       const QMap<QString, std::shared_ptr<T>> &data,
                                       QLineEdit *search_line);

};



// Template methods definition
template<AppStructDerived T>
bool FindManager::readDataFromDB(const QString &query_msg,
                           QMap<QString, std::shared_ptr<T>> &data,
                           int fields_num)
{
    // Showing all data in the block
    DataBaseManager &ref_db_manager = DataBaseManager::getInstance();

    //Read data from the database and save it into container
    bool res =
        ref_db_manager.readRequestToDB(query_msg,
                                       data,
                                       fields_num);

    return res;
}


template<AppStructDerived T>
void FindManager::fillListWidget(QListWidget *list_widget,
                           const QMap<QString, std::shared_ptr<T>> &data)
{

    if(list_widget == nullptr) return;

    if(constexpr int zero_items{0};
        list_widget->count() == zero_items)
    {
        // Fill the list widget with customers names
        std::for_each(data.cbegin(), data.cend(),
                      [&list_widget](const auto &el)
                      {
                          list_widget->addItem(el->getName());
                      });
    }
}


template<AppStructDerived T>
void FindManager::textEdited(QListWidget *list_widget,
                QLineEdit *search_line,
                const QMap<QString, std::shared_ptr<T>> &data,
                QObject *object_ptr)
{
    if(list_widget == nullptr ||
       search_line == nullptr ||
       object_ptr == nullptr) return;

    list_widget->clear();

    // If searching line is empty return list of names back
    if(search_line->text().isEmpty()){
        // Fill the list widget with customers names
        fillListWidget(list_widget, data);
    }

    // Fill container with customers names
    QStringList customers_names;

    for(auto it = data.cbegin(); it != data.cend(); ++it){
        customers_names << (*it)->getName();
    }

    // Set up QCompliter for auto completer(for user's conveniece)
    QCompleter *completer =
        new QCompleter(customers_names, object_ptr);

    // Register independency
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    search_line->setCompleter(completer);
}



template<AppStructDerived T>
bool FindManager::search(const QMap<QString, std::shared_ptr<T>> &data,
            const QLineEdit *search_line,
            QListWidget *list_widget)
{
    if(search_line == nullptr || list_widget == nullptr) return false;

    QString search_name = search_line->text();

    auto it = data.find(search_name);

    if(it != data.end()){
        // Display customer's name if it's not already displayed
        if(constexpr int zero_items{0};
            list_widget->count() == zero_items)
        {
            list_widget->addItem((*it)->getName());
        }
    }
    else{
        return false;
    }

    return true;
}



template<AppStructDerived T>
void FindManager::onClearAllButtonClicked(QLineEdit *search_line,
                              QListWidget *list_widget,
                              const QMap<QString, std::shared_ptr<T>> &data)
{

    if(search_line == nullptr || list_widget == nullptr) return;

    // Clear an entire searching line
    search_line->clear();

    // Focus is back on it
    search_line->setFocus();

    // Fill list widget again
    fillListWidget(list_widget, data);
}



template<AppStructDerived T>
void FindManager::onShowItemsListButtonClicked(QListWidget *list_widget,
                                   const QMap<QString, std::shared_ptr<T>> &data,
                                   QLineEdit *search_line)
{
    if(search_line == nullptr || list_widget == nullptr) return;

    list_widget->clear();
    fillListWidget(list_widget, data);
    search_line->setFocus();
}
