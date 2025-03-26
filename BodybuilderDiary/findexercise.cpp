#include "findexercise.h"
#include "ui_findexercise.h"

FindExercise::FindExercise(QWidget *parent)
    : FindCustomer(parent)
    , ui(new Ui::FindExercise)
{
    ui->setupUi(this);
}

FindExercise::~FindExercise()
{
    delete ui;
}
