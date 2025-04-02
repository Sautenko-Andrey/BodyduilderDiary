#include "searchexercise.h"
#include "findmanager.h"
#include "ui_searchstruct.h"   // Important! In order to use ui*
#include <QMessageBox>


SearchExercise::SearchExercise(): SearchStruct(nullptr){

    // Showing all customers in the block
    DataBaseManager &ref_db_manager = DataBaseManager::getInstance();

    //Read data from the database and save it into QMultiMap
    bool res =
        ref_db_manager.readRequestToDB(CustomQuery::read_exercises_query_all,
                                       m_data, Exercise::getFieldsNum());

    if(!res){
        QMessageBox::warning(this, "Database error",
                             "Couldn't read customers data");
        return;
    }


    // Fill the list widget with customers names
    fillListWidget();

    // Signals and slots

    connect(ui->InfoListWidget, &QListWidget::doubleClicked,
            this, &SearchExercise::onItemDoubleClicked);
    connect(ui->searchLineEdit, &QLineEdit::textEdited,
            this, &SearchExercise::textEdited);
    connect(ui->searchLineEdit, &QLineEdit::returnPressed,
            this, &SearchExercise::searchItem);

    // Connect buttons as well
    connect(ui->clearAllButton, &QPushButton::clicked,
            this, &SearchExercise::onClearAllButtonClicked);
    connect(ui->showUsersListButton, &QPushButton::clicked,
            this, &SearchExercise::onShowItemsListButtonClicked);
}


void SearchExercise::onItemDoubleClicked(){
    // Get selected cusomer
    const auto current_item = ui->InfoListWidget->currentItem();

    // Search a customer's data by key(name)
    auto it = m_data.find(current_item->text());

    if(it != m_data.end()){
        // Make info string
        QString info;
        QTextStream stream(&info);

        stream << "Title: " << (*it)->getTitle()
               << "\nType: " << (*it)->getExerciseType()
               << "\nDescription: " << (*it)->getDescription();

        QMessageBox::information(this, (*it)->getTitle(), info);
        return;
    }
}


void SearchExercise::textEdited(){
    FindManager::textEdited(
        ui->InfoListWidget,
        ui->searchLineEdit,
        m_data,
        this
        );
}


void SearchExercise::searchItem(){
    bool res = FindManager::search(m_data,
                                   ui->searchLineEdit,
                                   ui->InfoListWidget);
    if(!res){
        QMessageBox::warning(this, "Searching result",
                             "The exercise was not found");
    }
}


void SearchExercise::onClearAllButtonClicked(){
    FindManager::onClearAllButtonClicked(
        ui->searchLineEdit,
        ui->InfoListWidget,
        m_data
        );
}


void SearchExercise::onShowItemsListButtonClicked(){
    FindManager::onShowItemsListButtonClicked(
        ui->InfoListWidget,
        m_data,
        ui->searchLineEdit
        );
}


void SearchExercise::fillListWidget(){
    FindManager::fillListWidget(
        ui->InfoListWidget,
        m_data
        );
}

