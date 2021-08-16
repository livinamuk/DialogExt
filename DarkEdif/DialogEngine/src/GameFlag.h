#pragma once
#include <string>
#include <vector>

class GameFlag {
public:
    // Fields
    std::string m_name;
    bool m_state;

    // Methods
    GameFlag(std::string name, bool state);
    void Toggle();
}; 
 
