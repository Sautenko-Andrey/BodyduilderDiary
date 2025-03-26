#ifndef FINDEXERCISE_H
#define FINDEXERCISE_H

#include "findcustomer.h"

namespace Ui {
class FindExercise;
}

class FindExercise : public FindCustomer
{

public:
    explicit FindExercise(QWidget *parent = nullptr);
    ~FindExercise();

private:
    Ui::FindExercise *ui;
};

#endif // FINDEXERCISE_H
