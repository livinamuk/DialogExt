#include "Common.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Extension.h"
#include "src/DialogEngine.h"


void Extension::LoadDialogFile(TCHAR* name)
{
	DialogEngine::LoadDialogFile(TStringToUTF8(name));
}

void Extension::LoadQuestFile(TCHAR* name)
{
	DialogEngine::LoadQuestFile(TStringToUTF8(name));
}

void Extension::LoadPlayerDataFile(TCHAR* name)
{
	DialogEngine::LoadPlayerFile(TStringToUTF8(name));
}

void Extension::SavePlayerDataFile(TCHAR* name)
{
	DialogEngine::SavePlayerFile(TStringToUTF8(name));
}

void Extension::ShowDialogByID(int ID)
{
	DialogEngine::SetCurrentDialogByID(ID);
}

void Extension::SelectResponseByIndex(int index)
{
	DialogEngine::SelectResponse(index);
}

void Extension::SetGameValue(TCHAR* name, float value)
{
	DialogEngine::SetGameFloat(TStringToUTF8(name), value);
}

void Extension::SetGameValueMin(TCHAR* name, float value)
{
	DialogEngine::SetGameFloatMin(TStringToUTF8(name), value);
}

void Extension::SetGameValueMax(TCHAR* name, float value)
{
	DialogEngine::SetGameFloatMax(TStringToUTF8(name), value);
}

void Extension::AddToGameValue(TCHAR* name, float value)
{
	DialogEngine::AddToGameFloat(TStringToUTF8(name), value);
}

void Extension::SubtractFromValue(TCHAR* name, float value)
{
	DialogEngine::SubractFromGameFloat(TStringToUTF8(name), value);
}

void Extension::SetGameFlagToTrue(TCHAR* name)
{
	DialogEngine::SetGameFlag(TStringToUTF8(name), true);
}

void Extension::SetGameFlagToFalse(TCHAR* name)
{
	DialogEngine::SetGameFlag(TStringToUTF8(name), false);
}

void Extension::ToggleGameFlag(TCHAR* name)
{
	DialogEngine::ToggleGameFlag(TStringToUTF8(name));
}

void Extension::GiveItem(TCHAR* name, int quanitity)
{
	Inventory::GiveItem(TStringToUTF8(name), quanitity);
}

void Extension::TakeItem(TCHAR* name, int quanitity)
{
	Inventory::TakeItem(TStringToUTF8(name), quanitity);
}

void Extension::TriggerFusionActionByName(TCHAR* name)
{
	DialogEngine::AddFusionAction(TStringToUTF8(name));
}

void Extension::ClearAllData()
{
	DialogEngine::ClearAllData();
}


void Extension::CheckNPCForInworldQuestDialog(TCHAR* npcName)
{
	DialogEngine::CheckNPCForInworldQuestDialog(TStringToUTF8(npcName));
}
void Extension::CheckNPCForStandardDialogAndQuests(TCHAR* npcName)
{
	DialogEngine::CheckNPCForStandardDialogAndQuests(TStringToUTF8(npcName));
}
void Extension::CheckNPCForInWorldDialog(TCHAR* npcName)
{
	DialogEngine::CheckNPCForInWorldDialog(TStringToUTF8(npcName));
}

void Extension::LoadInWorldDialogFile(TCHAR* name)
{
	DialogEngine::LoadInWorldDialogFile(TStringToUTF8(name));
}

void Extension::UpdateEngine()
{
	DialogEngine::UpdateEngine();
}

void Extension::SetTextTimerDuration(int duration)
{
	DialogEngine::SetTextDuration(duration);
}

void Extension::ActivateQuestByName(TCHAR* name)
{
	DialogEngine::ActivateQuestByName(TStringToUTF8(name));
}

void Extension::CompleteQuestByName(TCHAR* name)
{
	DialogEngine::CompleteQuestByName(TStringToUTF8(name));
}

void Extension::FailQuestByName(TCHAR* name)
{
	DialogEngine::FailQuestByName(TStringToUTF8(name));

}

void Extension::CheckForQuestCompletion()
{
	DialogEngine::CheckQuestRequirementsAndPayOuts();
}










void Extension::LoadItemDatabase(TCHAR* filename)
{
	// replace with loading from a file soon u dummy
	Inventory::LoadInventoryDatabase(TStringToUTF8(filename));
	Inventory::InitDefaults();
}

void Extension::LoadContainerDatabase(TCHAR* filename)
{
	Inventory::LoadContainerDatabase(TStringToUTF8(filename));
}

void Extension::DespositItemIntoContainer(TCHAR* containerName, TCHAR* itemName, int itemQuanitity, int gridLocatiom)
{
	Inventory::DepositItemsIntoContainer(TStringToUTF8(containerName), TStringToUTF8(itemName), itemQuanitity, gridLocatiom);
}

void Extension::WithdrawItemFromContainer(TCHAR* containerName, TCHAR* itemName, int itemQuanitity, int gridLocatiom)
{
	Inventory::WithdrawItemsFromContainer(TStringToUTF8(containerName), TStringToUTF8(itemName), itemQuanitity, gridLocatiom);
}

void Extension::SetInventoryBagGeneralSize(int size)
{
	Inventory::m_max_general_slots = size;
}
void Extension::SetInventoryBagWearableSize(int size)
{
	Inventory::m_max_wearable_slots = size;
}
void Extension::SetInventoryBagEquipableSize(int size)
{
	Inventory::m_max_equipable_slots = size;
}
void Extension::SetInventoryBagMaterialSize(int size)
{
	Inventory::m_max_material_slots = size;
}
void Extension::SetInventoryBagConsumableSize(int size)
{
	Inventory::m_max_consumable_slots = size;
}
void Extension::SetInventoryBagQuestSize(int size)
{
	Inventory::m_max_quest_slots = size;
}
void Extension::SetInventoryBagSkillsSize(int size)
{
	Inventory::m_max_skill_slots = size;
}
void Extension::MoveInventoryItem(TCHAR* itemName, int gridLocatiom)
{
	Inventory::MoveInventoryItem(TStringToUTF8(itemName), gridLocatiom);
}
void Extension::MoveContaineryItem(TCHAR* itemName, int gridLocatiom)
{
	Inventory::MoveContainerItem(TStringToUTF8(itemName), gridLocatiom);
}
void Extension::SetCurrentContainerByName(TCHAR* containerName)
{
	Inventory::SetCurrentContainerByName(TStringToUTF8(containerName));
}
void Extension::SetCurrentCompanionByName(TCHAR* companionName)
{
	Inventory::SetCurrentCompanionByName(TStringToUTF8(companionName));
}
void Extension::ShowCompanionInventory()
{
	Inventory::ShowCompanion();
}
void Extension::ShowContainerInventory()
{
	Inventory::ShowContainer();
}
void Extension::setCurrentBagToGeneral()
{
	Inventory::SetCurrentInventoryBagToGeneral();
}
void Extension::setCurrentBagToWearable()
{
	Inventory::SetCurrentInventoryBagToWearable();
}
void Extension::setCurrentBagToEquipable()
{
	Inventory::SetCurrentInventoryBagToEquipable();
}
void Extension::setCurrentBagToMaterial()
{
	Inventory::SetCurrentInventoryBagToMaterial();
}
void Extension::setCurrentBagToConsumable()
{
	Inventory::SetCurrentInventoryBagToConsumeable();
}
void Extension::setCurrentBagToQuest()
{
	Inventory::SetCurrentInventoryBagToQuest();
}

void Extension::setCurrentBagToSkills()
{
	Inventory::SetCurrentInventoryBagToSkills();
}

void Extension::EquipToHead(TCHAR* itemName)
{
	std::string item = TStringToUTF8(itemName);
	Inventory::EquipToHead(item);
}

void Extension::EquipToUpperBody(TCHAR* itemName)
{
	std::string item = TStringToUTF8(itemName);
	Inventory::EquipToUpperBody(item);
}

void Extension::EquipToLowerBody(TCHAR* itemName)
{
	std::string item = TStringToUTF8(itemName);
	Inventory::EquipToLowerBody(item);
}

void Extension::EquipToHands(TCHAR* itemName)
{
	std::string item = TStringToUTF8(itemName);
	Inventory::EquipToHands(item);
}

void Extension::EquipToFeet(TCHAR* itemName)
{
	std::string item = TStringToUTF8(itemName);
	Inventory::EquipToFeet(item);
}

void Extension::EquipToBelt(TCHAR* itemName)
{
	std::string item = TStringToUTF8(itemName);
	Inventory::EquipToBelt(item);
	//	Inventory::s_equippedItems.m_belt = "Utility Belt";
}

void Extension::EquipToEquipSlot(TCHAR* itemName)
{
	std::string item = TStringToUTF8(itemName);
	Inventory::EquipToEquipSlot(item);
}

void Extension::EquipItemByName(TCHAR* itemName)
{
	std::string item = TStringToUTF8(itemName);
	Inventory::EquipItemByName(item);
}

void Extension::DequipItemByName(TCHAR* itemName)
{
	std::string item = TStringToUTF8(itemName);
	Inventory::DequipItemByName(item);
}

void Extension::UseItemByName(TCHAR* itemName)
{
	std::string item = TStringToUTF8(itemName);
	Inventory::UseItem(item);
}

void Extension::SetCurrentContainerToNone()
{
	Inventory::SetCurrentContainerToNone();
}

void Extension::SetCurrentCompanionToNone()
{
	Inventory::SetCurrentCompanionToNone();
}

void Extension::AddCompanionToSaveFile(TCHAR* name, TCHAR* type)
{
	std::string naame = TStringToUTF8(name);
	std::string tyype = TStringToUTF8(type);
	Inventory::AddCompanionToSaveFile(naame, tyype);
}
