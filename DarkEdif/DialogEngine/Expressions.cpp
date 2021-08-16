
#include "Common.h"


const TCHAR* Extension::GetCurrentDialogText()
{
	std::string str = DialogEngine::GetCurrentDialogText();
	std::tstring tstr = UTF8ToTString(str);
	return Runtime.CopyString(tstr.c_str());
}

const TCHAR* Extension::GetcurrentDialogImageName()
{
	std::string str = DialogEngine::GetCurrentDialogImageName();
	std::tstring tstr = UTF8ToTString(str);
	return Runtime.CopyString(tstr.c_str());
}

const TCHAR* Extension::GetResponseTextByIndex(int index)
{
	std::string str = DialogEngine::GetResponseTextByIndex(index);
	std::tstring tstr = UTF8ToTString(str);
	return Runtime.CopyString(tstr.c_str());
}

int Extension::GetAvaliableReponseCount()
{
	return DialogEngine::s_avaliableResponses.size();
}

float Extension::GetGameValueByName(TCHAR* name)
{
	return DialogEngine::GetGameFloat(TStringToUTF8(name));
}

const TCHAR* Extension::GetGameValueNameByIndex(int index)
{
	std::string str = DialogEngine::GetGameFloatNameByIndex(index);
	std::tstring tstr = UTF8ToTString(str);
	return Runtime.CopyString(tstr.c_str());
}

int Extension::GetTotalGameValueCount()
{
	return DialogEngine::s_gameFloats.size();
}

const TCHAR* Extension::GetGameFlagStateAsString(TCHAR* name)
{
	bool state = DialogEngine::GetGameFlagState(TStringToUTF8(name));

	if (state)
		return Runtime.CopyString(_T("TRUE"));
	else
		return Runtime.CopyString(_T("FALSE"));
}

const TCHAR* Extension::GetGameFlagNameByIndex(int index)
{
	std::string str = DialogEngine::GetGameFlagNameByIndex(index);
	std::tstring tstr = UTF8ToTString(str);
	return Runtime.CopyString(tstr.c_str());
}

int Extension::GetTotalGameFlagCount()
{
	return DialogEngine::s_gameFlags.size();
}

int Extension::GetGameItemQuantityByName(TCHAR* name)
{
	std::string str = TStringToUTF8(name);
	return Inventory::GetItemQuantity(str);
}

const TCHAR* Extension::GetFusionActionNameIndex(int index)
{
	std::string str = DialogEngine::GetFusionActionNameByIndex(index);
	std::tstring tstr = UTF8ToTString(str);
	return Runtime.CopyString(tstr.c_str());
}

int Extension::GetTotalPendingFusionActions()
{
	return DialogEngine::s_pendingFusionActions.size();
}

int Extension::GetLastSelectedResponseIndex()
{
	return DialogEngine::s_lastSelectedResponseIndex;
}

const TCHAR* Extension::GetQuestStateAsString(TCHAR* name)
{
	std::string state = DialogEngine::GetQuestStateAsString(TStringToUTF8(name));
	return Runtime.CopyString(UTF8ToTString(state).c_str());
}

const TCHAR* Extension::GetQuestNameByIndex(int index)
{
	std::string str = DialogEngine::GetQuestNameByIndex(index);
	std::tstring tstr = UTF8ToTString(str);
	return Runtime.CopyString(tstr.c_str());
}

int Extension::GetTotalQuestCount()
{
	return DialogEngine::s_Quests.size();
}

const TCHAR* Extension::GetQuestDescriptionByName(TCHAR* name)
{
	std::string state = DialogEngine::GetQuestDescription(TStringToUTF8(name));
	return Runtime.CopyString(UTF8ToTString(state).c_str());
}

int Extension::GetCurrentDialogID()
{
	return DialogEngine::s_currentDialog.m_ID;
}

int Extension::GetNPCCount()
{
	return DialogEngine::s_NPCs.size();
}

const TCHAR* Extension::GetNPCInWorldDialogStringByIndex(int index)
{
	std::string text = DialogEngine::s_NPCs[index].m_inWorldDialogString;
	return Runtime.CopyString(UTF8ToTString(text).c_str());
}

const TCHAR* Extension::GetNPCNameByIndex(int index)
{
	std::string name = DialogEngine::GetNPCNameByIndex(index);
	return Runtime.CopyString(UTF8ToTString(name).c_str());
}









// inventory new stuff

int Extension::GetInventoryBagGeneralSize()
{
	return Inventory::m_max_general_slots;
}
int Extension::GetInventoryBagWearableSize()
{
	return Inventory::m_max_wearable_slots;
}
int Extension::GetInventoryBagEquipableSize()
{
	return Inventory::m_max_equipable_slots;
}
int Extension::GetInventoryBagMaterialSize()
{
	return Inventory::m_max_material_slots;
}
int Extension::GetInventoryBagConsumableSize()
{
	return Inventory::m_max_consumable_slots;
}

int Extension::GetInventoryBagQuestsize()
{
	return Inventory::m_max_quest_slots;
}

int Extension::GetInventoryBagSkillssize()
{
	return Inventory::m_max_skill_slots;
}


const TCHAR* Extension::GetGeneralBagItemNameByIndex(int index)
{
	if (index >= 0 && index < Inventory::m_max_general_slots)
		return Runtime.CopyString(UTF8ToTString(Inventory::s_playerInventory_general[index].m_name).c_str());
	else
		return Runtime.CopyString(UTF8ToTString("out of range").c_str());
}

const TCHAR* Extension::GetWearableBagItemNameByIndex(int index)
{
	if (index >= 0 && index < Inventory::m_max_wearable_slots)
		return Runtime.CopyString(UTF8ToTString(Inventory::s_playerInventory_wearable[index].m_name).c_str());
	else
		return Runtime.CopyString(UTF8ToTString("out of range").c_str());
}

const TCHAR* Extension::GetMaterialItemNameByIndex(int index)
{
	if (index >= 0 && index < Inventory::m_max_material_slots)
		return Runtime.CopyString(UTF8ToTString(Inventory::s_playerInventory_material[index].m_name).c_str());
	else
		return Runtime.CopyString(UTF8ToTString("out of range").c_str());
}

const TCHAR* Extension::GetConsumableBagItemNameByIndex(int index)
{
	if (index >= 0 && index < Inventory::m_max_consumable_slots)
		return Runtime.CopyString(UTF8ToTString(Inventory::s_playerInventory_consumable[index].m_name).c_str());
	else
		return Runtime.CopyString(UTF8ToTString("out of range").c_str());
}

const TCHAR* Extension::GetEquipableBagItemNameByIndex(int index)
{
	if (index >= 0 && index < Inventory::m_max_equipable_slots)
		return Runtime.CopyString(UTF8ToTString(Inventory::s_playerInventory_equipable[index].m_name).c_str());
	else
		return Runtime.CopyString(UTF8ToTString("out of range").c_str());
}

const TCHAR* Extension::GetQuestBagItemNameByIndex(int index)
{
	if (index >= 0 && index < Inventory::m_max_quest_slots)
		return Runtime.CopyString(UTF8ToTString(Inventory::s_playerInventory_quest[index].m_name).c_str());
	else
		return Runtime.CopyString(UTF8ToTString("out of range").c_str());
}

const TCHAR* Extension::GetSkillBagItemNameByIndex(int index)
{
	if (index >= 0 && index < Inventory::m_max_skill_slots)
		return Runtime.CopyString(UTF8ToTString(Inventory::s_playerInventory_skills[index].m_name).c_str());
	else
		return Runtime.CopyString(UTF8ToTString("out of range").c_str());
}

const TCHAR* Extension::GetCurrentCompanionName()
{
	return Runtime.CopyString(UTF8ToTString(Inventory::s_inventoryState.currentCompanionName).c_str());
}

const TCHAR* Extension::GetCurrentContainerName()
{
	return Runtime.CopyString(UTF8ToTString(Inventory::s_inventoryState.currentContainerName).c_str());
}

int Extension::GetSizeOfContainerByName(TCHAR* name)
{
	return Inventory::GetContainerSizeByName(TStringToUTF8(name));
}

const TCHAR* Extension::GetGeneralInventoryItemNameByIndex(int index)
{
	return Runtime.CopyString(UTF8ToTString(Inventory::s_playerInventory_general[index].m_name).c_str());
}

const TCHAR* Extension::GetWearableInventoryItemNameByIndex(int index)
{
	return Runtime.CopyString(UTF8ToTString(Inventory::s_playerInventory_wearable[index].m_name).c_str());
}

const TCHAR* Extension::GetEquipableInventoryItemNameByIndex(int index)
{
	return Runtime.CopyString(UTF8ToTString(Inventory::s_playerInventory_equipable[index].m_name).c_str());
}

const TCHAR* Extension::GetMaterialInventoryItemNameByIndex(int index)
{
	return Runtime.CopyString(UTF8ToTString(Inventory::s_playerInventory_material[index].m_name).c_str());
}

const TCHAR* Extension::GetConsumableInventoryItemNameByIndex(int index)
{
	return Runtime.CopyString(UTF8ToTString(Inventory::s_playerInventory_consumable[index].m_name).c_str());
}

const TCHAR* Extension::GetQuestInventoryItemNameByIndex(int index)
{
	return Runtime.CopyString(UTF8ToTString(Inventory::s_playerInventory_quest[index].m_name).c_str());
}

const TCHAR* Extension::GetSkillInventoryItemNameByIndex(int index)
{
	return Runtime.CopyString(UTF8ToTString(Inventory::s_playerInventory_skills[index].m_name).c_str());

}

const TCHAR* Extension::GetItemTypeAsStringByName(const TCHAR* itemName)
{
	std::string itemType = Inventory::GetItemTypeAsStringByName(TStringToUTF8(itemName));
	return Runtime.CopyString(UTF8ToTString(itemType).c_str());
}

float Extension::GetItemWeightByName(const TCHAR* itemName)
{
	return Inventory::GetWeightByItemName(TStringToUTF8(itemName));
}

const TCHAR* Extension::GetItemDescriptionByName(const TCHAR* itemName)
{
	return Runtime.CopyString(UTF8ToTString(Inventory::GetItemDescriptionByName(TStringToUTF8(itemName))).c_str());
}

int Extension::GetItemNumberOfModifierEffectsByName(const TCHAR* itemName)
{
	return Inventory::GetItemNumberOfModifierEffectsByName(TStringToUTF8(itemName));
}
const TCHAR* Extension::GetItemModiferEffectNameByIndex(const TCHAR* itemName, int effectIndex)
{
	return Runtime.CopyString(UTF8ToTString(Inventory::GetItemModiferEffectNameByIndex(TStringToUTF8(itemName), effectIndex)).c_str());
}

int Extension::GetItemModiferEffectValueByIndex(const TCHAR* itemName, int effectIndex)
{
	return Inventory::GetItemModiferEffectValueByIndex(TStringToUTF8(itemName), effectIndex);
}

const TCHAR* Extension::GetCurrentBagItemNameByIndex(int index)
{
	return Runtime.CopyString(UTF8ToTString(Inventory::GetCurrentBagItemNameByIndex(index)).c_str());
}
int  Extension::GetCurrentBagIteQuantityByIndex(int index)
{
	return Inventory::GetCurrentBagIteQuantityByIndex(index);
}

int Extension::GetCurrentBagSize()
{
	if (Inventory::IsGeneralInventoryBagOpen())
		return Inventory::m_max_general_slots;
	else if (Inventory::IsConsumableInventoryBagOpen())
		return Inventory::m_max_consumable_slots;
	else if (Inventory::IsEquipableInventoryBagOpen())
		return Inventory::m_max_equipable_slots;
	else if (Inventory::IsMaterialInventoryBagOpen())
		return Inventory::m_max_material_slots;
	else if (Inventory::IsWearableInventoryBagOpen())
		return Inventory::m_max_wearable_slots;
	else if (Inventory::IsQuestInventoryBagOpen())
		return Inventory::m_max_quest_slots;
	else if (Inventory::IsSkillInventoryBagOpen())
		return Inventory::m_max_skill_slots;
	else return -1;
}


int Extension::GetContainerSize(const TCHAR* containerName)
{
	return Inventory::GetContainerSize(TStringToUTF8(containerName));
}
const TCHAR* Extension::GetContainerItemNameByIndex(const TCHAR* containerName, int index)
{
	return Runtime.CopyString(UTF8ToTString(Inventory::GetContainerItemNameByIndex(TStringToUTF8(containerName), index)).c_str());
}

int Extension::GetContainerItemQuanityByIndex(const TCHAR* containerName, int index)
{
	return Inventory::GetContainerItemQuantityByIndex(TStringToUTF8(containerName), index);
}

const TCHAR* Extension::GetContainerIconName(const TCHAR* containerName)
{
	return Runtime.CopyString(UTF8ToTString(Inventory::GetContainerIconName(TStringToUTF8(containerName))).c_str());
}

const TCHAR* Extension::GetItemNameEquippedToHead()
{
	return Runtime.CopyString(UTF8ToTString(Inventory::s_equippedItems.m_head).c_str());
}
const TCHAR* Extension::GetItemNameEquippedToUpperBody()
{
	return Runtime.CopyString(UTF8ToTString(Inventory::s_equippedItems.m_upperBody).c_str());
}
const TCHAR* Extension::GetItemNameEquippedToLowerBody()
{
	return Runtime.CopyString(UTF8ToTString(Inventory::s_equippedItems.m_lowerBody).c_str());
}
const TCHAR* Extension::GetItemNameEquippedToFeet()
{
	return Runtime.CopyString(UTF8ToTString(Inventory::s_equippedItems.m_feet).c_str());
}
const TCHAR* Extension::GetItemNameEquippedToHands()
{
	return Runtime.CopyString(UTF8ToTString(Inventory::s_equippedItems.m_hands).c_str());
}
const TCHAR* Extension::GetItemNameEquippedToBelt()
{
	return Runtime.CopyString(UTF8ToTString(Inventory::s_equippedItems.m_belt).c_str());
}
const TCHAR* Extension::GetItemNameEquippedToEquipSlot()
{
	return Runtime.CopyString(UTF8ToTString(Inventory::s_equippedItems.m_equipped).c_str());
}

float Extension::GetCurrentWeight()
{
	return Inventory::GetCurrentTotalWeight();
}

float Extension::GetMaxWeight()
{
	return Inventory::s_maxWeight;
}

int Extension::GetItemPositionInInventoryByItemName(const TCHAR* itemName)
{
	return Inventory::GetItemPositionInInventoryByItemName(TStringToUTF8(itemName));
}

int Extension::GetItemPositionInContainerByItemName(const TCHAR* itemName)
{
	return Inventory::GetItemPositionInContainerByItemName(TStringToUTF8(itemName));
}
