#pragma once

#include "../Header.h"
#include "../Util.h"
#include "vendor/rapidjson/include/rapidjson/document.h"
#include "vendor/rapidjson/include/rapidjson/filereadstream.h"


// Notes
/*

	1) When a new companion is encountered, a container is concreated with the same name.
	2) This is the same for containers too actually, but slitghly different. The first time you encounter a container, the program searches for it's name in the database and if it doesn't exist will add it, include it's defaul items.

	3) A companion can not have the same name as a container or shit will break; Or maybe they will just share the same space lol.
*/

struct InventoryState {
	std::string currentContainerName;
	std::string currentCompanionName;
};

class Inventory {
public:
	// functions
	static void InitDefaults();

	static void LoadInventoryDatabase(std::string filepath);
	static void SaveInventoryDatabase();

	static void LoadContainerDatabase(std::string filepath);
	static void SaveContainerDatabase();

	static void NewInventoryItem(std::string name, InventoryType type, float weight, std::string description, int price, bool usable, std::vector<Modifier> modifers);
	static void TakeItem(std::string name, int quantity);
	static ReturnValue GiveItem(std::string name, int quantity);
	static int GetItemQuantity(std::string name);
	static bool HasItem(std::string name);

	static void PrintInventoryDatabase();
	static void PrintPlayerInventoryList();
	static void PrintEquippedItems();
	static void PrintContainerContents(); // Prints all
	static void PrintContainerContents(int index);
	static void PrintContainerContents(std::string containerName);
	static void PrintCurrentContainer();

	static void EquipToHead(std::string itemName);
	static void EquipToUpperBody(std::string itemName);
	static void EquipToLowerBody(std::string itemName);
	static void EquipToHands(std::string itemName);
	static void EquipToFeet(std::string itemName);
	static void EquipToBelt(std::string itemName);
	static void EquipToEquipSlot(std::string itemName);

	static float GetCurrentTotalWeight();
	static float GetWeightByItemName(std::string name);
	static void ClearAllPlayerInventory();
	static InventoryType GetItemTypeByInventoryName(std::string name);

	static void NewContainer(std::string name, std::string iconName, int size, std::vector<PlayerInventoryItem> contents);
	static void DepositItemsIntoContainer(std::string containerName, std::string itemName, int itemQuantity, int containerSlot);
	static ReturnValue WithdrawItemsFromContainer(std::string containerName, std::string itemName, int itemQuantity, int inventorySlot);

	static void MoveContainerItem(std::string itemName, int newLocation);
	static void MoveInventoryItem(std::string itemName, int newLocation);

	//static std::string GetContainerItemNameByIndex(std::string containerName, int index);
	//static std::string GetContainerItemQuantityByIndex(std::string containerName, int index);

	static InventoryBagType GetInventoryBagTypeByItemName(std::string name);
	static PlayerInventoryItem* GetCorrespondingInventoryArrayPointerByItemName(std::string name);

	static void NewCompanion(std::string name, CompanionType type);

	static void ShowContainer();
	static void ShowCompanion();
	static void SetCurrentContainerByName(std::string name);
	static void SetCurrentCompanionByName(std::string name);
	//static int GetCurrentInventoryBagItemQuantityByindex(int index);
	//static std::string GetInventoryBagItemNameByindex(int index);

	static int GetContainerSize(std::string containerName);
	static std::string GetContainerItemNameByIndex(std::string containerName, int index);
	static int GetContainerItemQuantityByIndex(std::string containerName, int index);
	static std::string GetContainerIconName(std::string containerName);

	static int GetContainerSizeByName(std::string containerName);

	static void SetCurrentInventoryBagToGeneral();
	static void SetCurrentInventoryBagToWearable();
	static void SetCurrentInventoryBagToEquipable();
	static void SetCurrentInventoryBagToMaterial();
	static void SetCurrentInventoryBagToConsumeable();
	static void SetCurrentInventoryBagToQuest();
	static void SetCurrentInventoryBagToSkills();
	static int GetCurrentInventoryBagSize();


	static void SetGeneralInventoryBagSize(int size);
	static void SetWearableInventoryBagSize(int size);
	static void SetEquipableInventoryBagSize(int size);
	static void SetMaterialInventoryBagSize(int size);
	static void SetConsumableInventoryBagSize(int size);
	static void SetQuestInventoryBagSize(int size);
	static void SetSkillInventoryBagSize(int size);

	static int GetGeneralInventoryBagSize();
	static int GetWearableInventoryBagSize();
	static int GetEquipableInventoryBagSize();
	static int GetMaterialInventoryBagSize();
	static int GetConsumableInventoryBagSize();
	static int GetQuestInventoryBagSize();
	static int GetSkillInventoryBagSize();

	static bool IsGeneralInventoryBagOpen();
	static bool IsWearableInventoryBagOpen();
	static bool IsEquipableInventoryBagOpen();
	static bool IsMaterialInventoryBagOpen();
	static bool IsConsumableInventoryBagOpen();
	static bool IsQuestInventoryBagOpen();
	static bool IsSkillInventoryBagOpen();

	static std::string GetItemDescriptionByName(std::string name);
	static int GetItemNumberOfModifierEffectsByName(std::string name);
	static std::string GetItemModiferEffectNameByIndex(std::string name, int index);
	static int GetItemModiferEffectValueByIndex(std::string name, int index);
	static std::string GetItemTypeAsStringByName(std::string itemName);
	static std::string GetCurrentContainerItemNameByIndex(int index);
	static int GetCurrentContainerItemQuantityByIndex(int index);

	static std::string GetCurrentBagItemNameByIndex(int index);
	static int GetCurrentBagIteQuantityByIndex(int index);

	static std::string GetCurrentContainerName();
	static std::string GetCurrentCompanionName();

	static int GetItemPositionInInventoryByItemName(std::string itemName);
	static int GetItemPositionInContainerByItemName(std::string itemName);

	static bool IsItemWearable(std::string itemName);
	static bool IsItemUsable(std::string itemName);
	static bool IsItemEquipped(std::string itemName);
	static void EquipItemByName(std::string itemName);
	static void DequipItemByName(std::string itemName);
	static void UseItem(std::string itemName);
	static bool WasItemUsed(std::string itemName);

	static void SetCurrentContainerToNone();
	static void SetCurrentCompanionToNone();
	static bool IsPlayerAtContainer();
	static bool PlayerHasCompanion();

	static bool PlayerHasEncounteredCompanionAlready(std::string name);
	static void AddCompanionToSaveFile(std::string name, std::string type);


	static Container* p_displayedContainer;

	////////////////
	// varaibles //

	static InventoryState s_inventoryState;

	static std::vector<Companion> s_compainions;
	//static std::string s_currentCompanionName;
	//static std::string s_currentContainerName;

	static std::vector<std::string> s_pendingUsedItems;

	static std::vector<InventoryItemData> s_InventoryDatabase;

	static InventoryBagType s_currentInventoryBagType;
	static PlayerInventoryItem* p_currentInventory;
	static PlayerInventoryItem s_playerInventory_wearable[];
	static PlayerInventoryItem s_playerInventory_equipable[];
	static PlayerInventoryItem s_playerInventory_material[];
	static PlayerInventoryItem s_playerInventory_consumable[];
	static PlayerInventoryItem s_playerInventory_general[];
	static PlayerInventoryItem s_playerInventory_quest[];
	static PlayerInventoryItem s_playerInventory_skills[];

	static std::vector<Container> s_containers;

	static int m_max_wearable_slots;
	static int m_max_equipable_slots;
	static int m_max_material_slots;
	static int m_max_consumable_slots;
	static int m_max_general_slots;
	static int m_max_quest_slots;
	static int m_max_skill_slots;

	static float s_maxWeight;

	struct EquippedItems {
		std::string m_head;
		std::string m_upperBody;
		std::string m_lowerBody;
		std::string m_hands;
		std::string m_feet;
		std::string m_equipped;
		std::string m_belt;
	};
	static EquippedItems s_equippedItems;


private:
	static void SaveString(rapidjson::Value* object, std::string elementName, std::string string, rapidjson::Document::AllocatorType& allocator);
	static void SaveFloat(rapidjson::Value* object, std::string elementName, float number, rapidjson::Document::AllocatorType& allocator);
	static void SaveInt(rapidjson::Value* object, std::string elementName, int number, rapidjson::Document::AllocatorType& allocator);
	static std::string InventoryTypeToString(InventoryType query);
	//static std::string InventoryTypeToString(InventoryType query);
	static std::string ModiferTypeToString(ModifierType query);
};
