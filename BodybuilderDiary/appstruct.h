#pragma once
#include <QVariant>
#include <QVector>


// Interface for all upcoming structures (customer, exercise, coach, etc.)
class AppStruct {

public:

    virtual ~AppStruct() = default;

    virtual void setStruct(const QVector<QVariant> &args) = 0;

};
