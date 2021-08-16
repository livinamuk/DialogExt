
#include "GameFloat.h"

GameFloat::GameFloat(std::string name, float value) {
    m_name = name;
    m_value = value;
}

// Arithmetic
void GameFloat::SetTo(float value) {
    m_value = value;
    LimitWithinRange();
}

void GameFloat::Add(float value) {
    m_value += value;
    LimitWithinRange();
}

void GameFloat::Subract(float value) {
    m_value -= value;
    LimitWithinRange();
}

void GameFloat::SetMin(float value) {
    m_min = value;
    LimitWithinRange();
}

void GameFloat::SetMax(float value) {
    m_max = value;
    LimitWithinRange();
}

void GameFloat::LimitWithinRange()
{
    if (m_value < m_min)
        m_value = m_min;
    if (m_value > m_max)
        m_value = m_max;
}