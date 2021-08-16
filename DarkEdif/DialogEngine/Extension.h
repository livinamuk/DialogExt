#include <DarkEdif.h>
#pragma once
#include "src/DialogEngine.h"

class Extension
{
public:

#ifdef _WIN32
	RUNDATA * rdPtr;
	RunHeader * rhPtr;
#elif defined(__ANDROID__)
	RuntimeFunctions & runFuncs;
	global<jobject> javaExtPtr;
#else
	RuntimeFunctions & runFuncs;
	void * objCExtPtr;
#endif

	Edif::Runtime Runtime;

	static const int MinimumBuild = 254;
	static const int Version = 1;

	static const OEFLAGS OEFLAGS = OEFLAGS::NONE;
	static const OEPREFS OEPREFS = OEPREFS::NONE;

	static const int WindowProcPriority = 100;

#ifdef _WIN32
	Extension(RUNDATA * rdPtr, EDITDATA * edPtr, CreateObjectInfo * cobPtr);
#elif defined(__ANDROID__)
	Extension(RuntimeFunctions & runFuncs, EDITDATA * edPtr, jobject javaExtPtr);
#else
	Extension(RuntimeFunctions & runFuncs, EDITDATA * edPtr, void * objCExtPtr);
#endif
	~Extension();

	// To add items to the Fusion Debugger, just uncomment this line.
	DarkEdif::FusionDebugger FusionDebugger;
	// After enabling it, you run FusionDebugger.AddItemToDebugger() inside Extension's constructor
	// As an example:
	std::tstring exampleDebuggerTextItem;

	/*  Add any data you want to store in your extension to this class
		(eg. what you'd normally store in rdPtr in old SDKs).

		Unlike rdPtr, you can store real C++ objects with constructors
		and destructors, without having to call them manually or store
		a pointer.
	*/





	// int MyVariable;




	/*  Add your actions, conditions and expressions as real class member
		functions here. The arguments (and return type for expressions) must
		match EXACTLY what you defined in the JSON.

		Remember to link the actions, conditions and expressions to their
		numeric IDs in the class constructor (Extension.cpp)
	*/

	/// Actions

	void LoadDialogFile(TCHAR* name);
	void LoadQuestFile(TCHAR* name);
	void LoadPlayerDataFile(TCHAR* name);
	void SavePlayerDataFile(TCHAR* name);

	void ShowDialogByID(int ID);
	void SelectResponseByIndex(int index);

	void SetGameValue(TCHAR* name, float value);
	void SetGameValueMin(TCHAR* name, float value);
	void SetGameValueMax(TCHAR* name, float value);
	void AddToGameValue(TCHAR* name, float value);
	void SubtractFromValue(TCHAR* name, float value);

	void SetGameFlagToTrue(TCHAR* name);
	void SetGameFlagToFalse(TCHAR* name);
	void ToggleGameFlag(TCHAR* name);

	void GiveItem(TCHAR* name, int quanitity);
	void TakeItem(TCHAR* name, int quanitity);

	void TriggerFusionActionByName(TCHAR* name);

	void ActivateQuestByName(TCHAR* name);
	void CompleteQuestByName(TCHAR* name);
	void FailQuestByName(TCHAR* name);
	void CheckForQuestCompletion();

	void ClearAllData();

	//void CheckNPCForQuest(TCHAR* npcName);
	void CheckNPCForInworldQuestDialog(TCHAR* npcName);
	void CheckNPCForStandardDialogAndQuests(TCHAR* npcName);
	void CheckNPCForInWorldDialog(TCHAR* npcName);


	void LoadInWorldDialogFile(TCHAR* name);


	void UpdateEngine();
	void SetTextTimerDuration(int duration);


	// new with inventory 
	//{
	void LoadItemDatabase(TCHAR* filename);
	void LoadContainerDatabase(TCHAR* filename);
	void DespositItemIntoContainer(TCHAR* containerName, TCHAR* itemName, int itemQuanitity, int gridLocatiom);
	void WithdrawItemFromContainer(TCHAR* containerName, TCHAR* itemName, int itemQuanitity, int gridLocatiom);
	void SetInventoryBagGeneralSize(int size);
	void SetInventoryBagWearableSize(int size);
	void SetInventoryBagEquipableSize(int size);
	void SetInventoryBagMaterialSize(int size);
	void SetInventoryBagConsumableSize(int size);
	void SetInventoryBagQuestSize(int size);

	void SetInventoryBagSkillsSize(int size); // new

	void MoveInventoryItem(TCHAR* itemName, int gridLocatiom);
	void MoveContaineryItem(TCHAR* itemName, int gridLocatiom);
	void SetCurrentContainerByName(TCHAR* containerName);
	void SetCurrentCompanionByName(TCHAR* companionName);
	void ShowCompanionInventory();
	void ShowContainerInventory();
	void setCurrentBagToGeneral();
	void setCurrentBagToWearable();
	void setCurrentBagToEquipable();
	void setCurrentBagToMaterial();
	void setCurrentBagToConsumable();
	void setCurrentBagToQuest();

	void setCurrentBagToSkills(); // new

	void EquipToHead(TCHAR* itemName);
	void EquipToUpperBody(TCHAR* itemName);
	void EquipToLowerBody(TCHAR* itemName);
	void EquipToHands(TCHAR* itemName);
	void EquipToFeet(TCHAR* itemName);
	void EquipToBelt(TCHAR* itemName);
	void EquipToEquipSlot(TCHAR* itemName);
	void EquipItemByName(TCHAR* itemName);
	void DequipItemByName(TCHAR* itemName);
	void UseItemByName(TCHAR* itemName);

	void SetCurrentContainerToNone();
	void SetCurrentCompanionToNone();

	void AddCompanionToSaveFile(TCHAR* name, TCHAR* type);

	//}

	/// Conditions

	bool IsThereDialogToShow();
	bool IsDialogOver();
	bool IsReponseASpecialColor(int index);
	bool DoesValueExist(TCHAR* name);
	bool DoesPlayerHaveItem(TCHAR* name);
	bool IsFusionActionTriggered(TCHAR* name);
	bool IsReponseEmpty(int index);
	bool CompareDialogImageName(TCHAR* name);
	bool IsFlagTrue(TCHAR* name);
	bool IsFlagFalse(TCHAR* name);

	bool IsQuestActive(TCHAR* name);
	bool IsQuestInactive(TCHAR* name);
	//  bool AreQuestRequirementsFullfilled(TCHAR* name);
	bool IsQuestComplete(TCHAR* name);
	bool IsQuestFailed(TCHAR* name);
	bool WasAnyQuestJustCompleted();
	bool WasAnyQuestJustFailed();

	// new with inventory
	//
	bool IsCurrentBagGeneral();
	bool IsCurrentBagWearable();
	bool IsCurrentBagEquipable();
	bool IsCurrentBagMaterial();
	bool IsCurrentBagConsumable();
	bool IsCurrentBagQuest();
	bool IsCurrentBagSkills(); // new
	//
	bool IsItemUsable(TCHAR* name);
	bool IsItemWearable(TCHAR* name);
	bool IsItemEquipped(TCHAR* name);
	bool WasItemUsed(TCHAR* name);
	bool IsPlayerAtContainer();
	bool PlayerHasCompanion();
	bool PlayerHasEncounteredCompanionAlready(TCHAR* name);



	/// Expressions
	const TCHAR* GetCurrentDialogText();
	const TCHAR* GetcurrentDialogImageName();
	const TCHAR* GetResponseTextByIndex(int index);
	int GetAvaliableReponseCount();

	float GetGameValueByName(TCHAR* name);
	const TCHAR* GetGameValueNameByIndex(int index);
	int GetTotalGameValueCount();

	const TCHAR* GetGameFlagStateAsString(TCHAR* name);
	const TCHAR* GetGameFlagNameByIndex(int index);
	int GetTotalGameFlagCount();

	int GetGameItemQuantityByName(TCHAR* name);
	//const TCHAR* GetGameItemNameByIndex(int index);
   // int GetTotalGameItems();

	const TCHAR* GetFusionActionNameIndex(int index);
	int GetTotalPendingFusionActions();
	int GetLastSelectedResponseIndex();

	const TCHAR* GetQuestStateAsString(TCHAR* name);
	const TCHAR* GetQuestNameByIndex(int index);
	int GetTotalQuestCount();
	const TCHAR* GetQuestDescriptionByName(TCHAR* name);

	//const TCHAR* GetCurrentInWorldDialogString();
	int GetCurrentDialogID();

	// int Get_FixedValueTimer_TimerByFixedValue(int fixedValue);
	int GetNPCCount();
	const TCHAR* GetNPCInWorldDialogStringByIndex(int index);

	const TCHAR* GetNPCNameByIndex(int index);
	// int Get_FixedValueTimer_TimerByIndex(int index);



	 /// new with inventory
	int GetInventoryBagGeneralSize();
	int GetInventoryBagWearableSize();
	int GetInventoryBagEquipableSize();
	int GetInventoryBagMaterialSize();
	int GetInventoryBagConsumableSize();
	int GetInventoryBagQuestsize();
	int GetInventoryBagSkillssize(); // new

	const TCHAR* GetGeneralBagItemNameByIndex(int index);
	const TCHAR* GetWearableBagItemNameByIndex(int index);
	const TCHAR* GetMaterialItemNameByIndex(int index);
	const TCHAR* GetConsumableBagItemNameByIndex(int index);
	const TCHAR* GetEquipableBagItemNameByIndex(int index);
	const TCHAR* GetQuestBagItemNameByIndex(int index);
	const TCHAR* GetSkillBagItemNameByIndex(int index);  // new

	const TCHAR* GetCurrentCompanionName();
	const TCHAR* GetCurrentContainerName();
	int GetSizeOfContainerByName(TCHAR* name);
	const TCHAR* GetGeneralInventoryItemNameByIndex(int index);
	const TCHAR* GetWearableInventoryItemNameByIndex(int index);
	const TCHAR* GetEquipableInventoryItemNameByIndex(int index);
	const TCHAR* GetMaterialInventoryItemNameByIndex(int index);
	const TCHAR* GetConsumableInventoryItemNameByIndex(int index);
	const TCHAR* GetQuestInventoryItemNameByIndex(int index);

	const TCHAR* GetSkillInventoryItemNameByIndex(int index); // new

	const TCHAR* GetItemTypeAsStringByName(const TCHAR* itemName);
	float GetItemWeightByName(const TCHAR* itemName);
	const TCHAR* GetItemDescriptionByName(const TCHAR* itemName);
	int GetItemNumberOfModifierEffectsByName(const TCHAR* itemName);
	const TCHAR* GetItemModiferEffectNameByIndex(const TCHAR* itemName, int effectIndex);
	int GetItemModiferEffectValueByIndex(const TCHAR* itemName, int effectIndex);
	const TCHAR* GetCurrentBagItemNameByIndex(int index);
	int GetCurrentBagIteQuantityByIndex(int index);
	int GetCurrentBagSize();

	int GetContainerSize(const TCHAR* containerName);
	const TCHAR* GetContainerItemNameByIndex(const TCHAR* containerName, int index);
	int GetContainerItemQuanityByIndex(const TCHAR* containerName, int index);
	const TCHAR* GetContainerIconName(const TCHAR* containerName);

	const TCHAR* GetItemNameEquippedToHead();
	const TCHAR* GetItemNameEquippedToUpperBody();
	const TCHAR* GetItemNameEquippedToLowerBody();
	const TCHAR* GetItemNameEquippedToFeet();
	const TCHAR* GetItemNameEquippedToHands();
	const TCHAR* GetItemNameEquippedToBelt();
	const TCHAR* GetItemNameEquippedToEquipSlot();

	float GetCurrentWeight();
	float GetMaxWeight();

	int GetItemPositionInInventoryByItemName(const TCHAR* itemName);
	int GetItemPositionInContainerByItemName(const TCHAR* itemName);





	/* These are called if there's no function linked to an ID */

	void Action(int ID);
	long Condition(int ID);
	long Expression(int ID);




	/*  These replace the functions like HandleRunObject that used to be
		implemented in Runtime.cpp. They work exactly the same, but they're
		inside the extension class.
	*/

	REFLAG Handle();
	REFLAG Display();

	short Pause();
	short Continue();
};
