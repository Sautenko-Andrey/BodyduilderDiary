#ifndef SEARCHSTRUCT_H
#define SEARCHSTRUCT_H

#include <QDialog>

namespace Ui {
class SearchStruct;
}

class SearchStruct : public QDialog
{
    Q_OBJECT

public:
    explicit SearchStruct(QWidget *parent = nullptr);
    virtual ~SearchStruct();


public slots:
    virtual void onItemDoubleClicked() = 0;
    virtual void textEdited() = 0;
    virtual void searchItem() = 0;
    virtual void onClearAllButtonClicked() = 0;
    virtual void onShowItemsListButtonClicked() = 0;

protected:
    Ui::SearchStruct *ui;

private:
    virtual void fillListWidget() = 0;
};

#endif // SEARCHSTRUCT_H
