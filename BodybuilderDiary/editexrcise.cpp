#include "editexrcise.h"
#include "ui_editexrcise.h"

#include "databasemanager.h"
#include "query_messages.h"
#include "utils.h"

#include <QMessageBox>
#include <QCompleter>

enum class Size{
    WidgetWidth = 482,
    RegularModeHeight = 488,
    HideModeHeight = 120
};


EditExrcise::EditExrcise(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditExrcise)
{
    ui->setupUi(this);

    // Reserve memory for exercises names
    constexpr int possible_exerc_num{100};
    m_exerc_names.reserve(possible_exerc_num);

    // Main widget settings
    this->resize(
        static_cast<int>(Size::WidgetWidth),
        static_cast<int>(Size::HideModeHeight)
    );

    // Search line settings
    ui->searchLine->setPlaceholderText("Type here exercise's title");

    ui->typeComboBox->addItems({"Gym", "Cardio", "Warm-Up"});

    // Hide empty widgets
    hideDataWidgets();

    // Get reference on the database
    auto &ref_db_manager = DataBaseManager::getInstance();

    // Read data from the database and save it into QMultiMap
    auto res = ref_db_manager.readRequestToDB(CustomQuery::read_exercises_query_all,
                                              m_data,
                                              Exercise::getFieldsNum());

    if(!res){
        QMessageBox::warning(this, "Database error",
                             "Couldn't read exercises data");
        return;
    }

    // Signals and slots
    // Search customers via Completer
    connect(ui->searchLine, &QLineEdit::returnPressed,
            this, &EditExrcise::searchExercise);

    // User types something in the searching line
    connect(ui->searchLine, &QLineEdit::textEdited,
            this, &EditExrcise::textEdited);
}

EditExrcise::~EditExrcise()
{
    delete ui;
}


void EditExrcise::hideDataWidgets(){

    ui->titleLabel->hide();
    ui->titleLineEdit->hide();
    ui->descriptionLabel->hide();
    ui->descriptionTextEdit->hide();
    ui->editButton->hide();
    ui->typeComboBox->hide();
}


void EditExrcise::showDataWidgets(){

    // Make all widgets visible
    ui->titleLabel->show();
    ui->titleLineEdit->show();
    ui->descriptionLabel->show();
    ui->descriptionTextEdit->show();
    ui->editButton->show();
    ui->typeComboBox->show();
}


void EditExrcise::searchExercise(){

    // If search line is empty ignore command
    if(ui->searchLine->text().isEmpty()){
        return;
    }

    // Resize widget
    this->resize(
        static_cast<int>(Size::WidgetWidth),
        static_cast<int>(Size::RegularModeHeight)
    );

    // Make all widgets visible and disable
    showDataWidgets();

    // Get target name
    m_exerc_name = ui->searchLine->text();

    // Show user in the database
    auto it = m_data.find(m_exerc_name);

    if(it != m_data.end()){
        // Title found
        // Fill widgets with exercise's data

        // Title
        ui->titleLineEdit->setText((*it)->getTitle());

        // Type
        if((*it)->getExerciseType() == "Gym"){
            ui->typeComboBox->setCurrentIndex(0);
        }
        else if((*it)->getExerciseType() == "Cardio"){
            ui->typeComboBox->setCurrentIndex(1);
        }
        else{
            ui->typeComboBox->setCurrentIndex(2);
        }

        // Description
        ui->descriptionTextEdit->setText((*it)->getDescription());
    }
}


void EditExrcise::textEdited(){

    // Call the tamplate function from Utils module.
    Utils::textEdited(m_data, m_exerc_names, ui->searchLine, this);
}

void EditExrcise::on_editButton_clicked()
{
    // make an update query to db
    auto &ref_db_manager = DataBaseManager::getInstance();

    int exerc_type = 0;   // Gym

    if(ui->typeComboBox->currentText() == "Cardio"){
        exerc_type = 1;
    }
    else if(ui->typeComboBox->currentText() == "Warm-Up"){
        exerc_type = 2;
    }

    auto result =
        ref_db_manager.writeRequestToDB(CustomQuery::update_exerc_query,
                {
                    {":i_new_name", ui->titleLineEdit->text()},
                    {":i_type", exerc_type},
                    {":i_descr", ui->descriptionTextEdit->toPlainText()}
                });

    if (!result){
        QMessageBox::warning(this, "Database error",
                             "Couldn't save changes");
        return;
    }

    QMessageBox::information(this, "Edit report",
                             "Changes have been saved!");

    // Clean searching line, hide info widgets and resize dialog widget
    ui->searchLine->clear();

    hideDataWidgets();

    this->resize(
        static_cast<int>(Size::WidgetWidth),
        static_cast<int>(Size::HideModeHeight));

    // Get all updated exercises titles

    m_data.clear();

    // Read data from the database and save it into QMultiMap
    auto update_res = ref_db_manager.readRequestToDB(CustomQuery::read_exercises_query_all,
                                                     m_data,
                                                     Exercise::getFieldsNum());

    if(!update_res){
        QMessageBox::warning(this, "Database error",
                             "Couldn't read updated exercises data");
        return;
    }

    m_exerc_names.clear();

    for(auto it = m_data.cbegin(); it != m_data.cend(); ++it){
        m_exerc_names << (*it)->getTitle();
    }
}

