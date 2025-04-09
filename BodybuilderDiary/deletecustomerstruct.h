#pragma once

#include "deletestruct.h"
#include "customer.h"

class DeleteCustomerStruct final : public DeleteStruct
{
    Q_OBJECT
public:
    DeleteCustomerStruct();


private slots:

    virtual void textEdited() override;

    virtual void onDeleteButtonClicked() override;

    virtual void enterPressed() override;

private:
    QMap<QString, std::shared_ptr<Customer>> m_data;
};

