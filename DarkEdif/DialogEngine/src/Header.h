#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "vendor/rapidjson/include/rapidjson/istreamwrapper.h"
#include "vendor/rapidjson/include/rapidjson/writer.h"
#include "vendor/rapidjson/include/rapidjson/stringbuffer.h"
#include "vendor/rapidjson/include/rapidjson/ostreamwrapper.h"
#include "vendor/rapidjson/include/rapidjson/prettywriter.h"

enum class QuestState {
	INACTIVE,
	ACTIVE,
	COMPLETE,
	FAILED,
	UNDEFINED
};

enum class ConditionType {
	CONDITION_UNDEFINED,
	HAVE_ITEM,
	BOOOL,
	FLOAT_EQUAL,
	FLOAT_LESS,
	FLOAT_GREATER,
	FLOAT_LESS_OR_EQUAL,
	FLOAT_GREATER_OR_EQUAL,
	FLOAT_NOT_EQUAL,
	QUEST_REQUIREMENTS_MET,
	QUEST_FAILED,
	QUEST_COMPLETE,
	QUEST_ACTIVE,
	QUEST_INACTIVE
};

enum class ActionType {
	ACTION_UNDEFINED,
	SET_BOOL_TRUE,
	SET_BOOL_FALSE,
	SUBRACT_FLOAT,
	ADD_FLOAT,
	SET_FLOAT,
	GIVE_ITEM,
	TAKE_ITEM
};
/*
struct ResponseCondition {
public:
	std::string m_conditionName = "";
	ConditionType m_ConditionType = ConditionType::CONDITION_UNDEFINED;
	float m_conditionComparisonValue = 0;
	bool m_requiredConditionBoolState = false;
};*/

struct MyCondition {
public:
	std::string m_conditionName = "";
	ConditionType m_ConditionType = ConditionType::CONDITION_UNDEFINED;
	float m_conditionComparisonValue = 0;
	bool m_requiredConditionBoolState = false;
};


struct ResponseAction {
public:
	std::string m_name;
	ActionType m_actionType = ActionType::ACTION_UNDEFINED;
	float m_modifierValue = 0;
};

struct Response {

public:
	std::string m_text = "";
	std::vector<std::string> m_fusionActions;
	std::vector<std::string> m_CompleteQuests;
	std::vector<std::string> m_ActivateQuests;
	std::vector<std::string> m_FailQuests;
	std::vector<MyCondition> m_responseConditions;
	std::vector<ResponseAction> m_responseActions;
	bool m_isSpecialColor = false;
	int m_gotoID = -1;
};

struct DialogEntry {
public:
	int m_ID = -1;
	std::string m_imageName = "NO IMAGE";
	std::string m_text = "NO TEXT";
	std::vector<Response> m_responses;
	std::string m_npcTriggerName;
	std::vector<MyCondition> m_conditions;
};

#define INVENTORY_SIZE_LIMIT 42
//#define CONTAINER_SIZE 18
#define EMPTY_SLOT "empty"

struct PlayerInventoryItem {
	std::string m_name;
	int m_quantity;

	PlayerInventoryItem() {
		m_name = EMPTY_SLOT;
		m_quantity = 0;
	}
	PlayerInventoryItem(std::string name, int quantity) {
		m_name = name;
		m_quantity = quantity;
	}
};

struct Container {
	std::string name;
	std::string iconName;
	//PlayerInventoryItem contents[CONTAINER_SIZE];
	std::vector<PlayerInventoryItem> contentsVector;
};

/*
enum class EquipLocation {
	NOT_EQUIPPED,
	HEAD,
	UPPER_BODY,
	LOWER_BODY,
	HANDS,
	FEET,
	EQUIP_SLOT
};*/

enum ReturnValue {
	UNDEFINED,
	SUCCESS,
	FAILURE,
	OVERWEIGHT,
	COULD_NOT_FIND_CONTAINER_NAME,
	COULD_NOT_FIND_ITEM_IN_CONTAINER,
	NO_FREE_SLOTS,
	UNDEFINED_ITEM
};

enum class CompanionType {
	DONKEY,
	CAT,
	DOG
};

struct Companion {
	std::string name;
	CompanionType type;

	std::string TypeAsString()
	{
		if (type == CompanionType::CAT)
			return "CAT";
		if (type == CompanionType::DOG)
			return "DOG";
		else
			return "DONKEY";
	}
};

enum class InventoryBagType {
	GENERAL,
	WEARABLE,
	EQUIPABLE,
	MATERIAL,
	CONSUMABLE,
	QUEST,
	SKILL
};

enum class InventoryType {
	UNDEFINED,
	WEARABLE_HEAD,
	WEARABLE_UPPER_BODY,
	WEARABLE_LOWER_BODY,
	WEARABLE_BELT,
	WEARABLE_HANDS,
	WEARABLE_FEET,
	EQUIPABLE,
	MATERIAL,
	CONSUMABLE,
	GENERAL,
	QUEST,
	SKILL
};

enum ModifierType {
	NONE,
	SPEED,
	LOCK_PICKING
};

struct Modifier {
	ModifierType m_type;
	int m_value;
};

struct InventoryItemData {
	std::string m_name = "UNDEFINED";
	InventoryType m_type = InventoryType::UNDEFINED;
	float m_weight = 0;
	std::string m_description;
	int m_price;
	std::vector< Modifier> m_modifiers;
	int m_minXP = 0;
	bool m_usable = false;
};

