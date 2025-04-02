#pragma once
#include "searchstruct.h"
#include "customer.h"

class SearchCustomer final : public SearchStruct{
    Q_OBJECT
public:

    SearchCustomer();


private slots:
    virtual void onItemDoubleClicked() override;
    virtual void textEdited() override;
    virtual void searchItem() override;
    virtual void onClearAllButtonClicked() override;
    virtual void onShowItemsListButtonClicked() override;

private:

    virtual void fillListWidget() override;

    QMap<QString, std::shared_ptr<Customer>> m_data;
};
