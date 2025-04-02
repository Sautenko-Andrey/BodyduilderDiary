#include "exercise.h"

Exercise::Exercise(const QString &title, ExerciseType type,
         const QString &description)
    : m_title{title}, m_type{type}, m_description{description}
    {}


void Exercise::setStruct(const QVector<QVariant> &args) {

    m_title = args[0].toString();
    m_type = static_cast<ExerciseType>(args[1].toInt());
    m_description = args[2].toString();
}


const QString Exercise::getExerciseType(){

    switch (m_type) {
    case ExerciseType::Gym:
        return "Gym";
        break;
    case ExerciseType::Cardio:
        return "Cardio";
        break;
    case ExerciseType::WarmUp:
        return "Warm-up";
        break;
    }

    return "Gym";  // Never reaches
}
