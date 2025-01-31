#pragma once
#include <QLabel>

namespace Utils {

/*
    Function changes style of a label
*/
void changeLabelStyle(QLabel *label, int size, bool is_bold = true);


/*
    Function search text in a container and compare it
    for uniqueness
*/
bool checkUniqueText(const QString &text, const QStringList &data);


}// End namespace Utils
