#include "searchcustomer.h"
#include "findmanager.h"
#include "ui_searchstruct.h"   // Important! In order to use ui*
#include <QMessageBox>


SearchCustomer::SearchCustomer(){

    // Signals and slots
    bindSignalsAndSlots();
}


void SearchCustomer::onItemDoubleClicked(){
    // Get selected cusomer
    const auto current_item = ui->InfoListWidget->currentItem();

    // Search a customer's data by key(name)
    auto it = m_data.find(current_item->text());

    if(it != m_data.end()){
        // Make info string
        QString info;
        QTextStream stream(&info);

        stream << "Age: " << (*it)->getAge()
               << "\nHeight: " << (*it)->getHeight()
               << "\nWeight: " << (*it)->getWeight()
               << "\nNotes: " << (*it)->getNotice();

        QMessageBox::information(this, (*it)->getName(), info);
        return;
    }
}


void SearchCustomer::textEdited(){
    FindManager::textEdited(
        ui->InfoListWidget,
        ui->searchLineEdit,
        m_data,
        this
    );
}


void SearchCustomer::searchItem(){
    bool res = FindManager::search(m_data,
                                   ui->searchLineEdit,
                                   ui->InfoListWidget);
    if(!res){
        QMessageBox::warning(this, "Searching result",
                             "The customer was not found");
    }
}


void SearchCustomer::onClearAllButtonClicked(){
    FindManager::onClearAllButtonClicked(
        ui->searchLineEdit,
        ui->InfoListWidget,
        m_data
    );
}


void SearchCustomer::onShowItemsListButtonClicked(){
    FindManager::onShowItemsListButtonClicked(
        ui->InfoListWidget,
        m_data,
        ui->searchLineEdit
    );
}


void SearchCustomer::fillListWidget(){
    FindManager::fillListWidget(
        ui->InfoListWidget,
        m_data
    );
}
