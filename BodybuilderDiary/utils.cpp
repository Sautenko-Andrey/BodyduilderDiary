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


bool checkUniqueText(const QString &text, const std::deque<QString> &data){
    for(const auto &el : data){
        if(text == el){
            return false;
        }
    }

    return true;
}


}// End namespace Utils
