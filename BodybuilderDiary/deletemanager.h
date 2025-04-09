#pragma once

#include <QString>
#include "databasemanager.h"
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QMap>
#include <concepts>
#include "appstruct.h"
#include <QMessageBox>


enum class Size{
    WidgetWidth = 482,
    RegularModeHeight = 488,
    HideModeHeight = 120
};


template<typename T>
concept AppStructDerived = std::is_base_of_v<AppStruct, T>;

class DeleteManager {

public:

    bool deleteItem(const QString &del_query,
                    const QString &name)
    {

        // Make a delete query to DB
        DataBaseManager &ref_db_manager = DataBaseManager::getInstance();

        bool res =
            ref_db_manager.writeRequestToDB(del_query,
                                            {
                                                {":i_name", name}
                                            });

        return res;
    }

    //============================================================

    void toHiddenMode(QWidget *widget,
                      QPlainTextEdit *plain_text_edit,
                      QLineEdit *search_line)
    {
        if(widget == nullptr ||
           plain_text_edit == nullptr ||
           search_line == nullptr)
        {
            return;
        }

        // Make size for hide mode
        widget->resize(
            static_cast<int>(Size::WidgetWidth),
            static_cast<int>(Size::HideModeHeight)
            );

        plain_text_edit->hide();
        search_line->clear();
    }

    //===============================================================
    template<AppStructDerived T>
    bool updateView(const QMap<QString, std::shared_ptr<T>> &data,
                    const QString &read_query,
                    int fields_num,
                    QSet<QString> &all_names
                    )
    {
        // Get all updated objects names

        data.clear();

        // Read data from the database and save it into QMultiMap
        DataBaseManager &ref_db_manager = DataBaseManager::getInstance();

        bool update_res =
            ref_db_manager.readRequestToDB(read_query, data, fields_num);

        if(!update_res) return false;

        all_names.clear();

        for(auto it = data.cbegin(); it != data.cend(); ++it){
            all_names << (*it)->getName();
        }
    }


    //=============================================================

    template<AppStructDerived T>
    void prepareEnterExecution(QLineEdit *search_line,
                               QWidget *widget,
                               QPlainTextEdit *plain_text_edit,
                               QString &name,
                               const QMap<QString, std::shared_ptr<T>> &data)
    {

        // If search line is empty ignore command
        if(search_line == nullptr ||
           widget == nullptr ||
           search_line->text().isEmpty())
        {
            return;
        }


        // Make size for regular mode
        widget->resize(
                static_cast<int>(Size::WidgetWidth),
                static_cast<int>(Size::RegularModeHeight)
        );

        // Show text plain edit again
        plain_text_edit->show();

        // Get name from QLinedEdit
        name = search_line->text();

        // Find this user and get its data
        auto res = data.find(name);

        if(res == data.end()){
            QMessageBox::warning(widget,
                                 "Report",
                                 "The desired data doesn't exist");
            return;
        }
    }

};
