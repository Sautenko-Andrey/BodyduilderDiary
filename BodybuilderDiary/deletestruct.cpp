#include "deletestruct.h"
#include "ui_deletestruct.h"

enum class Size{
    WidgetWidth = 482,
    RegularModeHeight = 488,
    HideModeHeight = 120
};


DeleteStruct::DeleteStruct(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DeleteStruct)
{
    ui->setupUi(this);

    // Search line settings
    ui->searchLine->setPlaceholderText("Type here item's name");

    // Hide plain text edit widget
    ui->plainTextEdit->hide();

    // Make size for hide mode
    this->resize(
        static_cast<int>(Size::WidgetWidth),
        static_cast<int>(Size::HideModeHeight)
    );
}

DeleteStruct::~DeleteStruct()
{
    delete ui;
}
