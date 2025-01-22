#include "customer.h"
#include <QDebug>

Customer::Customer(const QString &name, int age, bool gender, int height,
                   int weight, const QString &notice)
: m_name{name}, m_age{age}, m_gender{gender},
    m_height{height}, m_weight{weight}, m_notice{notice}
{}



void Customer::setStruct(const QVector<QVariant> &args) {
    m_name = args[0].toString();
    m_age = args[1].toInt();
    m_gender = args[2].toBool();
    m_height = args[3].toInt();
    m_weight = args[4].toInt();
    m_notice = args[5].toString();
}
