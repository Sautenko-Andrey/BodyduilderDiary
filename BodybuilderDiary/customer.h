#pragma once
#include"appstruct.h"
#include<QString>



class Customer : public AppStruct {

public:

    Customer() = default;

    Customer(const QString &name, int age, bool gender, int height,
             int weight, const QString &notice = "");

    // Customer has 6 fields + id
    static constexpr int getFieldsNum() noexcept { return 7; }

    virtual void setStruct(const QVector<QVariant> &args) override;

private:

    QString m_name{"Unknown"};

    int m_age{18};

    bool m_gender{true};

    int m_height{170};

    int m_weight{50};

    QString m_notice{"None"};
};
