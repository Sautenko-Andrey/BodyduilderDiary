#include "searchstruct.h"
#include "ui_searchstruct.h"

SearchStruct::SearchStruct(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SearchStruct)
{
    ui->setupUi(this);
}

SearchStruct::~SearchStruct()
{
    delete ui;
}


/*
    This function is used in derived classes only!
*/
void SearchStruct::bindSignalsAndSlots(){
    // Signals and slots

    // User double clicks on a sone line in the widget list
    connect(ui->InfoListWidget, &QListWidget::doubleClicked,
            this, &SearchStruct::onItemDoubleClicked);

    // User types something in the searching line
    connect(ui->searchLineEdit, &QLineEdit::textEdited,
            this, &SearchStruct::textEdited);

    // Search customers via Completer
    connect(ui->searchLineEdit, &QLineEdit::returnPressed,
            this, &SearchStruct::searchItem);
}
