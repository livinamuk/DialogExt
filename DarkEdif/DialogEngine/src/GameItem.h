#pragma once
#include <string>
#include <vector>

    class GameItem {
    public:
        // Fields
        std::string m_name;
        int m_quantity;

        // Methods
        GameItem(std::string name, int quantity);
    };
