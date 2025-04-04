#ifndef EDITEXRCISE_H
#define EDITEXRCISE_H

#include <QDialog>

#include "exercise.h"

namespace Ui {
class EditExrcise;
}

class EditExrcise : public QDialog
{
    Q_OBJECT

public:
    explicit EditExrcise(QWidget *parent = nullptr);
    ~EditExrcise();

private slots:

    void searchExercise();

    void textEdited();

    void on_editButton_clicked();

private:
    Ui::EditExrcise *ui;

    QMap<QString, std::shared_ptr<Exercise>> m_data;

    QSet<QString> m_exerc_names;

    QString m_exerc_name;

    void hideDataWidgets();

    void showDataWidgets();
};

#endif // EDITEXRCISE_H
