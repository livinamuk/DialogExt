#pragma once

#include "Header.h"
#include "Util.h"
//#include "GameItem.h"
#include "GameFlag.h"
#include "GameFloat.h"
#include "Quest.h"
#include "NPC.h"
#include "Inventory/Inventory.h"

class DialogEngine {
public:

	// Static Variables
	//static std::vector<GameItem> s_gameItems;
	static std::vector<GameFlag> s_gameFlags;
	static std::vector<GameFloat> s_gameFloats;
	static std::vector<DialogEntry> s_dialogEntries;
	static std::vector<Response> s_avaliableResponses;
	static std::vector<std::string> s_pendingFusionActions;
	static DialogEntry s_currentDialog;
	static int s_lastSelectedResponseIndex;
	static std::vector<Quest> s_Quests;
	static bool s_wasAnyQuestJustCompleted;
	static bool s_wasAnyQuestJustFailed;
	static std::vector<NPC> s_NPCs;
	static int s_textDuration;
	//static std::map<int, std::string> s_itemFixedValueMap;

	// Static functions
	static void LoadPlayerFile(std::string filename);
	static void LoadDialogFile(std::string filename);
	static void SavePlayerFile(std::string filename);
	static void LoadQuestFile(std::string filename);
	static void LoadInWorldDialogFile(std::string filename);

	static void SetGameFlag(std::string flagName, bool state);
	static bool GetGameFlagState(std::string flagName);
	static void ToggleGameFlag(std::string flagName);
	static std::string GetGameFlagNameByIndex(int index);
	static bool DoesFlagExist(std::string name);


	static void SetGameFloat(std::string name, float value);
	static void SetGameFloatMin(std::string name, float value);
	static void SetGameFloatMax(std::string name, float value);
	static void AddToGameFloat(std::string name, float value);
	static void SubractFromGameFloat(std::string name, float value);
	static float GetGameFloat(std::string flagName);
	static bool GameFloatExists(std::string name);
	static std::string GetGameFloatNameByIndex(int index);

	static DialogEntry GetDialogByID(int ID);
	static void SetCurrentDialogByID(int ID);
	static std::string GetCurrentDialogText();
	static std::string GetCurrentDialogImageName();
	static bool IsDialogOver();
	static std::string GetResponseTextByIndex(int index);

	static bool EvaluateConditionalComparison(std::string name, ConditionType conditionType, float comparisonValue);
	static void UpdateAvaliableResponses();
	static void SelectResponse(int index); // Evaluates everything updates s_currentDialog
	static bool IsResponseSpecialColored(int index);

	static void AddFusionAction(std::string name);
	static bool TriggerFusionAction(std::string name); // Returns true if fusion action name was found, and then deletes it
	static std::string GetFusionActionNameByIndex(int index);
	static bool CompareDialogImageNameToString(std::string query);

	static void ClearAllData();
	static void UpdateEngine();
	static void SetTextDuration(int duration);

	// Quests 
	static void CheckQuestRequirementsAndPayOuts();
	static void ActivateQuestByName(std::string query);
	static void CompleteQuestByName(std::string query);
	static void FailQuestByName(std::string query);
	static int GetQuestCount();
	static std::string GetQuestNameByIndex(int index);
	static QuestState GetQuestStateByIndex(int index);
	static bool WasIfAnyQuestWasJustCompleted();
	static bool WasIfAnyQuestWasJustFailed();
	static bool IsQuestActive(std::string query);
	static bool IsQuestInactive(std::string query);
	//static bool AreQuestRequirementsFullfilled(std::string query);
	static bool IsQuestCompleted(std::string query);
	static bool IsQuestFailed(std::string query);
	static std::string GetQuestStateAsString(std::string query);
	static std::string GetQuestDescription(std::string query);
	static void SetQuestStateByString(std::string questName, std::string questState);
	//static void InactivateQuestByName(std::string query);
	//static NPC* GetNPCPointer(std::string name);\
		
	// NPC abstraction
	static NPC* CreateNPC(std::string name);
	static NPC* GetNPCAndCreateIfItDoesntExist(std::string name);
	static NPC* GetNPCPointer(std::string name);

	//static int GetNextQuestDialogIDFromNPCName(std::string npcName);

	//static void CheckNPCForQuest(std::string npcName);
	static void CheckNPCForInworldQuestDialog(std::string npcName);
	static void CheckNPCForStandardDialogAndQuests(std::string npcName);
	static void CheckNPCForInWorldDialog(std::string npcName);

	//static std::string GetQuestInWorldDialogFromNPCName(std::string npcName);
	//static std::string GetRandomNPCInWorldDialogFromNPCName(std::string npcName);


	//static void CheckNPCQuestDialog(int fixedValue);
//static void CheckNPCInWorldDialog(int fixedValue);
//static void CheckNPCInWorldQuestDialogText(int fixedValue);
//static void CheckNPCStandardDialogText(int fixedValue);

	static std::string GetNPCNameByIndex(int index);

	//static NPC* GetNPCPointerByFixedValue(int fixedValue);
	//static void RegisterNPC(std::string name, int fixedValue);
	//static int GetQuestDialogIDFromNPCFixedValue(int fixedValue);


	//static std::string GetRandomInWorldDialogFromNPCFixedValue(int fixedValue);
	static Quest* GetQuestByName(std::string name);





	//static int CheckNPCForQuest(std::string npcName);
	//static void CheckNPCQuestDialog(int fixedValue);
	//static void CheckNPCInWorldDialog(int fixedValue);
	//static void CheckNPCInWorldQuestDialogText(int fixedValue);
	//static void CheckNPCStandardDialogText(int fixedValue);
	//static std::string GetNPCInWorldDialogStringByIndex(int index);
	//static int GetNPCFixedValueByIndex(int index);

	// Item abstraction
	//static void RegisterItem(std::string name, int fixedValue);
	//static void PickedUpFusionItem(int fixedValue);

	static MyCondition ConditionObjectFromString(std::string line);
	static bool IsConditionListSatisfied(std::vector<MyCondition>& conidtionList);

private:
	static void SaveString(rapidjson::Value* object, std::string elementName, std::string string, rapidjson::Document::AllocatorType& allocator);
	static void SaveFloat(rapidjson::Value* object, std::string elementName, float number, rapidjson::Document::AllocatorType& allocator);
	static void SaveInt(rapidjson::Value* object, std::string elementName, int number, rapidjson::Document::AllocatorType& allocator);
	static std::string InventoryTypeToString(InventoryType query);
	//static std::string InventoryTypeToString(InventoryType query);
	static std::string ModiferTypeToString(ModifierType query);
};



// NOTES.
// - you should make all checks case insensitive
// - you should remove all STRINGS. yes.
// - you should not allow the creation of items/flags/values if the name has been used already elsewhere
// - display helpful error messages somehow when text document cannot be read.
// - you should probably add traits...

// EXTENSION DEV NOTES
// - You have updated the string to int/float functions. Remember to update in other solution. Have you?
