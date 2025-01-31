#include "utils.h"

namespace Utils {

void changeLabelStyle(QLabel *label, int size, bool is_bold){

    if(label == nullptr){
        return;
    }

    if(constexpr int min_size = 1, default_size = 11; size < min_size){
        size = default_size;
    }

    label->setAlignment(Qt::AlignCenter);

    QFont font = label->font();

    if(is_bold){
        font.setBold(true);
    }

    font.setPointSize(size);

    label->setFont(font);
}



/*
void AddExercise::changeText()
{
    // Compare additional exercises with existed names
    // If name exists, warn user about it

    // Get current name
    auto current_title = ui->titleLineEdit->text();

    for(const auto &name : m_exercises_names){
        if(current_title == name){
            QMessageBox::warning(this, "Potential error",
                                 "Non-unique exercise's name");

            return;
        }
    }
}
*/

bool checkUniqueText(const QString &text, const QStringList &data){
    for(const auto &el : data){
        if(text == el){
            return false;
        }
    }

    return true;
}


}// End namespace Utils
