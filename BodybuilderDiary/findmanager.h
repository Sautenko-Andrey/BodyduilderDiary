#pragma once
#include "databasemanager.h"
#include "query_messages.h"
#include <QMap>
#include <concepts>
#include "appstruct.h"
#include <QListWidget>
#include <algorithm>
#include <QTextStream>



// void Find::onUserDoubleClicked()
// {
//     // Get selected cusomer
//     const auto current_item = ui->InfoListWidget->currentItem();

//     // Search a customer's data by key(name)
//     auto it = m_data.find(current_item->text());

//     if(it != m_data.end()){
//         // Make info string
//         QString info;
//         QTextStream stream(&info);

//         stream << "Age: " << (*it)->getAge()
//                << "\nHeight: " << (*it)->getHeight()
//                << "\nWeight: " << (*it)->getWeight()
//                << "\nNotes: " << (*it)->getNotice();

//         QMessageBox::information(this, (*it)->getName(), info);
//         return;
//     }
// }

template<typename T>
concept AppStructDerived = std::is_base_of_v<AppStruct, T>;

class FindManager {

    template<AppStructDerived T>
    static bool readDataFromDB(const QString &query_msg,
                               QMap<QString, std::shared_ptr<T>> &data,
                               int fields_num);

    template<AppStructDerived T>
    static void fillListWidget(QListWidget &list_widget,
                               const QMap<QString, std::shared_ptr<T>> &data);

};


template<AppStructDerived T>
static bool readDataFromDB(const QString &query_msg,
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

    return res ? true : false;
}


template<AppStructDerived T>
static void fillListWidget(QListWidget &list_widget,
                           const QMap<QString, std::shared_ptr<T>> &data)
{

    if(constexpr int zero_items{0};
        list_widget.count() == zero_items)
    {
        // Fill the list widget with customers names
        std::for_each(data.cbegin(), data.cend(),
                      [&list_widget](const auto &el)
                      {
                          list_widget.addItem(el->getName());
                      });
    }
}

