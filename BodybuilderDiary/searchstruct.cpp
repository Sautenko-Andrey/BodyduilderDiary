#include "searchstruct.h"
#include "ui_searchstruct.h"

enum class Sizes {
    SearchLineMinWidth = 350,
    SearchLineMaxWidth = 500
};

SearchStruct::SearchStruct(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SearchStruct)
{
    ui->setupUi(this);

    // Searching line settings
    ui->searchLineEdit->
        setMinimumWidth(static_cast<int>(Sizes::SearchLineMinWidth));

    ui->searchLineEdit->
        setMaximumWidth(static_cast<int>(Sizes::SearchLineMaxWidth));
}

SearchStruct::~SearchStruct()
{
    delete ui;
}
