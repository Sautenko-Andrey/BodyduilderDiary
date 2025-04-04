// #include "find.h"
// #include "ui_find.h"
// #include "query_messages.h"
// #include "databasemanager.h"

// #include <QMessageBox>
// #include <QPushButton>
// #include <algorithm>
// #include <QTextStream>
// #include <QCompleter>

// #include "customer.h"
// #include "exercise.h"


// enum class Sizes {
//     SearchLineMinWidth = 350,
//     SearchLineMaxWidth = 500
// };

// Find::Find(FindType find_type, QWidget *parent)
//     : QDialog(parent)
//     , ui(new Ui::FindCustomer)
// {

//     ui->setupUi(this);

//     // Searching line settings
//     ui->searchLineEdit->
//         setMinimumWidth(static_cast<int>(Sizes::SearchLineMinWidth));

//     ui->searchLineEdit->
//         setMaximumWidth(static_cast<int>(Sizes::SearchLineMaxWidth));

//     // Showing all customers in the block
//     DataBaseManager &ref_db_manager = DataBaseManager::getInstance();

//     //Read data from the database and save it into QMultiMap
//     bool res =
//         ref_db_manager.readRequestToDB(CustomQuery::read_customers_query_all,
//                                            m_data, Customer::getFieldsNum());

//     if(!res){
//         QMessageBox::warning(this, "Database error",
//                                  "Couldn't read customers data");
//         return;
//     }


//     // Fill the list widget with customers names
//     fillListWidget();

//     // Signals and slots------------------------------------------------

//     // User double clicks on a sone line in the widget list
//     connect(ui->InfoListWidget, &QListWidget::doubleClicked,
//             this, &Find::onUserDoubleClicked);

//     // User types something in the searching line
//     connect(ui->searchLineEdit, &QLineEdit::textEdited,
//             this, &Find::textEdited);

//     // Search customers via Completer
//     connect(ui->searchLineEdit, &QLineEdit::returnPressed,
//             this, &Find::searchCustomer);
// }

// Find::~Find()
// {
//     delete ui;
// }


// void Find::fillListWidget(){

//     if(constexpr int zero_items{0};
//        ui->InfoListWidget->count() == zero_items)
//     {
//         // Fill the list widget with customers names
//         std::for_each(m_data.cbegin(), m_data.cend(), [this](const auto &el){

//             const auto name = el->getName();

//             ui->InfoListWidget->addItem(name);
//         });
//     }
// }

// void Find::onUserDoubleClicked()
// {
//     // Get selected cusomer
//     const auto current_item = ui->InfoListWidget->currentItem();

//     // Search a customer's data by key(name)
//     auto it = m_data.find(current_item->text());

//     if(it != m_data.end()){
//         // Make info string
//         QString info;
//         QTextStream stream(&info);

//         stream << "Age: " << (*it)->getAge()
//                << "\nHeight: " << (*it)->getHeight()
//                << "\nWeight: " << (*it)->getWeight()
//                << "\nNotes: " << (*it)->getNotice();

//         QMessageBox::information(this, (*it)->getName(), info);
//         return;
//     }
// }

// void Find::textEdited()
// {
//     ui->InfoListWidget->clear();

//     // If searching line is empty return list of names back
//     if(ui->searchLineEdit->text().isEmpty()){
//         // Fill the list widget with customers names
//         fillListWidget();
//     }

//     // Fill container with customers names
//     QStringList customers_names;

//     for(auto it = m_data.cbegin(); it != m_data.cend(); ++it){
//         customers_names << (*it)->getName();
//     }

//     // Set up QCompliter for auto completer(for user's conveniece)
//     QCompleter *completer = new QCompleter(customers_names, this);

//     // Register independency
//     completer->setCaseSensitivity(Qt::CaseInsensitive);
//     ui->searchLineEdit->setCompleter(completer);
// }

// void Find::searchCustomer()
// {
//     QString search_name = ui->searchLineEdit->text();

//     auto it = m_data.find(search_name);

//     if(it != m_data.end()){
//         // Display customer's name if it's not already displayed
//         if(constexpr int zero_items{0};
//             ui->InfoListWidget->count() == zero_items)
//         {
//             ui->InfoListWidget->addItem((*it)->getName());
//         }

//     }
//     else{
//         QMessageBox::warning(this, "Searching result",
//                              "The customer was not found");
//     }
// }

// void Find::on_clearAllButton_clicked()
// {
//     // Clear an entire searching line
//     ui->searchLineEdit->clear();

//     // Focus is back on it
//     ui->searchLineEdit->setFocus();

//     // Fill list widget again
//     fillListWidget();
// }


// void Find::on_showUsersListButton_clicked()
// {
//     ui->InfoListWidget->clear();
//     fillListWidget();
//     ui->searchLineEdit->setFocus();
// }
