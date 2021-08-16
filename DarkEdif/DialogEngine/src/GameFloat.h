#pragma once
#include <string>
#include <vector>

class GameFloat {
public:
    // Fields
    std::string m_name;
    float m_value;
    float m_min = -99999;
    float m_max = 99999;

    // Methods
    GameFloat(std::string name, float value);
    void SetTo(float value);
    void Add(float value);
    void Subract(float value);
    void SetMin(float value);
    void SetMax(float value);
    void LimitWithinRange();
}; 
 
