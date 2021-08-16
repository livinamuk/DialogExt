
#include "GameFlag.h"

GameFlag::GameFlag(std::string name, bool state) {
    m_name = name;
    m_state = state;
}

void GameFlag::Toggle()
{
    m_state = !m_state;
}

  
