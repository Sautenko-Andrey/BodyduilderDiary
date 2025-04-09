#ifndef DELETESTRUCT_H
#define DELETESTRUCT_H

#include <QDialog>

namespace Ui {
class DeleteStruct;
}

class DeleteStruct : public QDialog
{
    Q_OBJECT

public:

    explicit DeleteStruct(QWidget *parent = nullptr);
    virtual ~DeleteStruct();

public slots:

    virtual void textEdited() = 0;

    virtual void onDeleteButtonClicked() = 0;

    virtual void enterPressed() = 0;

protected:

    Ui::DeleteStruct *ui;
};

#endif // DELETESTRUCT_H
