#pragma once
#include <QLabel>
#include <deque>
#include "appstruct.h"
#include <QCompleter>
#include <QLineEdit>

namespace Utils {

/*
    Function changes style of a label
*/
void changeLabelStyle(QLabel *label, int size, bool is_bold = true);


/*
    Function search text in a container and compare it
    for uniqueness
*/
bool checkUniqueText(const QString &text, const std::deque<QString> &data);


/*
    Concept for the AppStruct derived classes
*/
template<typename T>
concept AppStructDerived = std::is_base_of_v<AppStruct, T>;

template<AppStructDerived T>
void textEdited(QMap<QString, std::shared_ptr<T>> &data,
                QSet<QString> &names,
                QLineEdit *search_line,
                QObject *parent)
{

    if(search_line == nullptr || parent == nullptr){
        return;
    }

    // Get all struct names/titles

    for(auto it = data.cbegin(); it != data.cend(); ++it){
        names << (*it)->getName();
    }

    QStringList titles =
        QStringList(names.begin(), names.end());

    // Set up QCompliter for auto completer(for user's conveniece)
    QCompleter *completer = new QCompleter(titles, parent);

    // Register independency
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    search_line->setCompleter(completer);
}


}// End namespace Utils
