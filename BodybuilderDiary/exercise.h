#pragma once
#include "appstruct.h"
#include <QString>


enum class ExerciseType { Gym, Cardio, WarmUp };


class Exercise : public AppStruct {

public:

    Exercise() = default;

    Exercise(const QString &title, ExerciseType type,
             const QString &description);

    virtual void setStruct(const QVector<QVariant> &args) override;

    const QString& getTitle() const { return m_title; }

    const QString& getName() const { return m_title; }  // !!!Dublication

    const QString getExerciseType();

    const QString& getDescription() const { return m_description; }

    // Exercise has 3 fields + id
    static constexpr int getFieldsNum() noexcept { return 4; }


private:

    QString m_title{"Unknown"};

    ExerciseType m_type{ExerciseType::Gym};

    QString m_description{"None"};
};
