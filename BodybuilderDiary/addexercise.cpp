#include "addexercise.h"
#include "ui_addexercise.h"
#include "utils.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "query_messages.h"

AddExercise::AddExercise(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddExercise)
{
    ui->setupUi(this);

    // const QStringList exercises_types_names {
    //     "Gym", "Cardio", "Warm-up"
    // };

    ui->typeComboBox->addItems(m_exercises_types_names);

    // Make all labels bold and with font 12
    constexpr int font_size{12};
    Utils::changeLabelStyle(ui->titleLabel, font_size);
    Utils::changeLabelStyle(ui->typeLabel, font_size);
    Utils::changeLabelStyle(ui->descriptionLabel, font_size);

    // Get all exrcises names
    auto &ref_db_manager = DataBaseManager::getInstance();
    QSqlQuery query(ref_db_manager.getDatabase());

    if(!query.exec("SELECT name FROM exercises;")){
        QMessageBox::warning(this, "Database error",
                                 "Couldn't load all exercises titles");
        return;
    }
    else{
        while(query.next()){
            m_names.emplace_back(query.value(0).toString());
        }
    }

    // Signals and slots
    connect(ui->titleLineEdit, &QLineEdit::textChanged,
            this, &AddExercise::changeText);
}

AddExercise::~AddExercise()
{
    delete ui;
}



void AddExercise::changeText()
{
    // Compare additional exercises with existed names
    // If name exists, warn user about it

    // Get current name
    auto current_title = ui->titleLineEdit->text();

    auto unique_res = Utils::checkUniqueText(current_title,
                                             m_names);
    if(!unique_res){
        QMessageBox::warning(this, "Potential error",
                             "Non-unique exercise's name");
        return;
    }
}


void AddExercise::on_addPushButton_clicked()
{
    const QString &title = ui->titleLineEdit->text();
    const QString &descr = ui->descriptionPlainTextEdit->toPlainText();

    // Check if the title is empty string
    if(title.isEmpty()){
        return;
    }

    // Trim title and description
    const QString clean_title = title.trimmed();
    const QString clean_descr = descr.trimmed();

    // Save data into the databse
    auto &ref_db_manager = DataBaseManager::getInstance();

    auto res =
        ref_db_manager.writeRequestToDB(CustomQuery::add_exercise_query,
                {
                    {":i_name", clean_title},
                    {":i_descr", clean_descr},
                    {":i_type", ui->typeComboBox->currentIndex()}
                });

    if(!res){
        QMessageBox::warning(this, "Database error",
                             "Couldn't save a new exercise.\n"
                             "Probably exercise with this name already exists.\n"
                             "HINT! Make name unique.");
        return;
    }
    else{
        QMessageBox::information(this, "Adding a new exercise", "Done!");
    }

    // Close the dialog window
    this->accept();
}

