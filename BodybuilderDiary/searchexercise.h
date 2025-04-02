#pragma once
#include "exercise.h"
#include "searchstruct.h"

class SearchExercise final : public SearchStruct {

    Q_OBJECT

public:

    SearchExercise();


private slots:
    virtual void onItemDoubleClicked() override;
    virtual void textEdited() override;
    virtual void searchItem() override;
    virtual void onClearAllButtonClicked() override;
    virtual void onShowItemsListButtonClicked() override;

private:

    virtual void fillListWidget() override;

    QMap<QString, std::shared_ptr<Exercise>> m_data;


};
