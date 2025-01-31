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

    ExerciseType getExerciseType() { return m_type; }

    const QString& getDescription() const { return m_description; }


private:

    QString m_title{"Unknown"};

    ExerciseType m_type{ExerciseType::Gym};

    QString m_description{"None"};
};
