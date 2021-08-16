#pragma once
#include "Util.h"

void Util::Log(std::string text)
{
    std::ofstream outfile;
    outfile.open("log.txt", std::ios_base::app); // append instead of overwrite
    outfile << text << "\n";
}

std::string Util::GetModifierTypeNameAsString(ModifierType type)
{
    if (type == ModifierType::LOCK_PICKING)
        return "LOCK_PICKING";
    else if (type == ModifierType::SPEED)
        return "SPEED";
    else
        return "UNDEFINED";
}

std::string Util::GetItemTypeAsString(InventoryType type)
{
    if (type == InventoryType::CONSUMABLE)
        return "CONSUMABLE";
    else if (type == InventoryType::EQUIPABLE)
        return "EQUIPABLE";
    else if (type == InventoryType::GENERAL)
        return "GENERAL";
    else if (type == InventoryType::MATERIAL)
        return "MATERIAL";
    else if (type == InventoryType::QUEST)
        return "QUEST";
    else if (type == InventoryType::WEARABLE_BELT)
        return "WEARABLE_BELT";
    else if (type == InventoryType::WEARABLE_FEET)
        return "WEARABLE_FEET";
    else if (type == InventoryType::WEARABLE_HANDS)
        return "WEARABLE_HANDS";
    else if (type == InventoryType::WEARABLE_HEAD)
        return "WEARABLE_HEAD";
    else if (type == InventoryType::WEARABLE_LOWER_BODY)
        return "WEARABLE_LOWER_BODY";
    else if (type == InventoryType::WEARABLE_UPPER_BODY)
        return "WEARABLE_UPPER_BODY";
    else if (type == InventoryType::SKILL)
        return "SKILL";
    else
        return "UNDEFINED";
}

CompanionType Util::GetCompanionTypeFromString(std::string type)
{
    if (CaselessEquality(type, "CAT"))
        return CompanionType::CAT;
    else if (CaselessEquality(type, "DOG"))
        return CompanionType::DOG;
    else
        return CompanionType::DONKEY;
}

InventoryType Util::GetItemTypeFromString(std::string type)
{
    if (type == "CONSUMABLE")
        return InventoryType::CONSUMABLE;
    else if (type == "EQUIPABLE")
        return InventoryType::EQUIPABLE;
    else if (type == "GENERAL")
        return InventoryType::GENERAL;
    else if (type == "MATERIAL")
        return InventoryType::MATERIAL;
    else if (type == "QUEST")
        return InventoryType::QUEST;
    else if (type == "WEARABLE_BELT")
        return InventoryType::WEARABLE_BELT;
    else if (type == "WEARABLE_FEET")
        return InventoryType::WEARABLE_FEET;
    else if (type == "WEARABLE_HANDS")
        return InventoryType::WEARABLE_HANDS;
    else if (type == "WEARABLE_HEAD")
        return InventoryType::WEARABLE_HEAD;
    else if (type == "WEARABLE_LOWER_BODY")
        return InventoryType::WEARABLE_LOWER_BODY;
    else if (type == "WEARABLE_UPPER_BODY")
        return InventoryType::WEARABLE_UPPER_BODY;
    else if (type == "SKILL")
        return InventoryType::SKILL;
    else
        return InventoryType::UNDEFINED;
}

bool Util::CaselessEquality(std::string strA, std::string strB)
{
    return ToUppercase(strA) == ToUppercase(strB);
}

std::string Util::ToUppercase(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}
std::string Util::ToLowercase(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

int Util::RandomInt(int low, int high)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator   
    std::uniform_int_distribution<> distr(low, high); // define the range
    return distr(gen);
}

int Util::StringToInt(std::string str)
{
    if (str.length() == 0)
        return 0;

    std::stringstream stringStream(str);
    int result = 0;
    stringStream >> result;
    return result;
}

float Util::StringToFloat(std::string str)
{
    if (str.length() == 0)
        return 0;

    return std::stof(str);
}

std::string Util::RemoveFromBeginning(std::string str, int numberOfCharacters)
{
    return str.substr(numberOfCharacters, str.length() - 1);
}

std::string Util::GetSubstringBetweenQuotes(std::string str)
{
    std::string substringAfterFirstQuote = str.substr(str.find('"') + 1);
    return substringAfterFirstQuote.substr(0, substringAfterFirstQuote.find('"'));
}


std::string Util::GetSubstringAfterChar(std::string str, char c)
{
    return RemoveWhitespace(str.substr(str.find(c) + 1));
}

std::string Util::GetSubstringBeforeChar(std::string str, char c)
{
    int index = str.find(c);

    if (index == -1)
        return "";
    else
        return RemoveWhitespace(str.substr(0, index));
}

std::string Util::GetSubstringBeforeSubstring(std::string str, std::string query)
{
    int index = str.find(query);

    if (index == -1)
        return "";
    else
        return RemoveWhitespace(str.substr(0, index));
}

std::string Util::GetSubstringBeforeParentheses(std::string query)
{
    int index = query.find("(");
    if (index == -1) return query;
    else return query.substr(0, index);
}

std::string Util::GetSubstringAfterSubstring(std::string str, std::string query)
{
    return RemoveWhitespace(str.substr(str.find(query) + query.length()));
}


std::string Util::GetSubstringAfterEquals(std::string str)
{
    std::string substringAfterFirstQuote = str.substr(str.find('"') + 1);
    return RemoveWhitespace(str.substr(str.find("=") + 1));
}

std::string Util::GetSubstringAfterColon(std::string str)
{
    return RemoveWhitespace(str.substr(str.find(':') + 1));
}

std::string Util::GetSubstringBeforeColon(std::string str)
{
    int index = str.find(':');

    if (index == -1)
        return "";
    else
        return RemoveWhitespace(str.substr(0, index));
}

std::string Util::GetSubstringBeforeEquals(std::string str)
{
    int index = str.find('=');

    if (index == -1)
        return "";
    else
        return RemoveWhitespace(str.substr(0, index));
}

std::string Util::GetSubstringAfterSecondQuote(std::string str)
{
    std::string substringAfterFirstQuote = str.substr(str.find('"') + 1);
    return RemoveWhitespace(substringAfterFirstQuote.substr(substringAfterFirstQuote.find('"') + 1));
}

std::string Util::RemoveWhitespace(std::string str)
{
    return trim(str);
}

std::string Util::GetOperator(std::string str)
{
    std::string cleanStr = RemoveWhitespace(str);

    if (cleanStr[0] == '+')
        return "+";
    else if (cleanStr[0] == '-')
        return "-";
    else if (cleanStr[0] == 'x')
        return "x";
    else if (cleanStr.substr(0, 2) == "<=")
        return "<=";
    else if (cleanStr.substr(0, 2) == ">=")
        return ">=";
    else if (cleanStr.substr(0, 2) == "==")
        return "==";
    else if (cleanStr.substr(0, 2) == "!=")
        return "!=";
    else
        return "";
}

float Util::GetValueAfterOperator(std::string str)
{
    std::string cleanStr = RemoveWhitespace(str);
    std::string opperatorStr = GetOperator(cleanStr);
    std::string valueStr = cleanStr.substr(opperatorStr.length());
    std::string cleanValueStr = RemoveWhitespace(valueStr);

    if (cleanValueStr.length() == 0)
        return 0.0f;

    return std::stof(cleanValueStr);
}

bool Util::StringContains(std::string str, std::string query)
{
    if (str.find(query) != std::string::npos)
        return true;
    else
        return false;
}

float Util::GetFloatBetweenParentheses(std::string query)
{
    int left = query.find("(");
    int right = query.find(")");

    if (left == -1 || right == -1)
        return 0;

    if (left == right - 1)
        return 0;

    return StringToFloat(query.substr(left + 1, right - left + 1));
}