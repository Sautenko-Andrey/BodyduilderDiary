#ifndef ADDEXERCISE_H
#define ADDEXERCISE_H

#include <QDialog>

namespace Ui {
class AddExercise;
}

class AddExercise : public QDialog
{
    Q_OBJECT

public:
    explicit AddExercise(QWidget *parent = nullptr);
    ~AddExercise();

private slots:

    void changeText();

    void on_addPushButton_clicked();

private:
    Ui::AddExercise *ui;

    inline static const QStringList m_exercises_types_names {
        "Gym", "Cardio", "Warm-up"
    };

    QStringList m_exercises_names;
};

#endif // ADDEXERCISE_H
