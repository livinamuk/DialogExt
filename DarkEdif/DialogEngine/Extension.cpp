#include "Common.h"


///
/// EXTENSION CONSTRUCTOR/DESTRUCTOR
///

#ifdef _WIN32
Extension::Extension(RUNDATA * _rdPtr, EDITDATA * edPtr, CreateObjectInfo * cobPtr) :
	rdPtr(_rdPtr), rhPtr(_rdPtr->rHo.AdRunHeader), Runtime(&_rdPtr->rHo), FusionDebugger(this)
#elif defined(__ANDROID__)
Extension::Extension(RuntimeFunctions & runFuncs, EDITDATA * edPtr, jobject javaExtPtr) :
	runFuncs(runFuncs), javaExtPtr(javaExtPtr, "javaExtPtr in Extension"), Runtime(runFuncs, this->javaExtPtr), FusionDebugger(this)
#else
Extension::Extension(RuntimeFunctions & runFuncs, EDITDATA * edPtr, void * objCExtPtr) :
	runFuncs(runFuncs), objCExtPtr(objCExtPtr), Runtime(runFuncs, this->objCExtPtr), FusionDebugger(this)
#endif
{
	/*
		Link all your action/condition/expression functions to their IDs to match the
		IDs in the JSON here
	*/



	LinkAction(0, LoadDialogFile);
	LinkAction(1, LoadQuestFile);
	LinkAction(2, LoadPlayerDataFile);
	LinkAction(3, LoadInWorldDialogFile);
	LinkAction(4, SavePlayerDataFile);

	LinkAction(5, ShowDialogByID);
	LinkAction(6, SelectResponseByIndex);
	LinkAction(7, SetGameValue);
	LinkAction(8, SetGameValueMin);
	LinkAction(9, SetGameValueMax);
	LinkAction(10, AddToGameValue);
	LinkAction(11, SubtractFromValue);
	LinkAction(12, SetGameFlagToTrue);
	LinkAction(13, SetGameFlagToFalse);
	LinkAction(14, ToggleGameFlag);

	//LinkAction(15, RegisterItemFixedValue);	 you need to remove the json
	LinkAction(16, GiveItem);
	LinkAction(17, TakeItem);
	//LinkAction(18, PickedUpFusionItem);		 you need to remove the json

	LinkAction(19, TriggerFusionActionByName);

	LinkAction(20, ActivateQuestByName);
	LinkAction(21, CompleteQuestByName);
	LinkAction(22, FailQuestByName);
	LinkAction(23, CheckForQuestCompletion);

	//LinkAction(24, RegisterNPCFixedValue);		you need to remove the json
	LinkAction(25, CheckNPCForStandardDialogAndQuests);
	LinkAction(26, CheckNPCForInWorldDialog);
	LinkAction(27, SetTextTimerDuration);
	LinkAction(28, CheckNPCForInworldQuestDialog);
	//LinkAction(29, CheckNPCForStandardDialog); delete meeeeeeeeeeeeeeeeee too

	LinkAction(30, ClearAllData);
	LinkAction(31, UpdateEngine);





	// inventory
	LinkAction(32, LoadItemDatabase);
	LinkAction(33, DespositItemIntoContainer);
	LinkAction(34, WithdrawItemFromContainer);
	LinkAction(35, MoveInventoryItem);
	LinkAction(36, MoveContaineryItem);
	LinkAction(37, SetInventoryBagGeneralSize);
	LinkAction(38, SetInventoryBagWearableSize);
	LinkAction(39, SetInventoryBagEquipableSize);
	LinkAction(40, SetInventoryBagMaterialSize);
	LinkAction(41, SetInventoryBagConsumableSize);
	LinkAction(42, SetInventoryBagQuestSize);
	LinkAction(43, ShowContainerInventory);
	LinkAction(44, ShowCompanionInventory);
	LinkAction(45, setCurrentBagToGeneral);
	LinkAction(46, setCurrentBagToWearable);
	LinkAction(47, setCurrentBagToEquipable);
	LinkAction(48, setCurrentBagToMaterial);
	LinkAction(49, setCurrentBagToConsumable);
	LinkAction(50, setCurrentBagToQuest);
	LinkAction(51, SetCurrentContainerByName);
	LinkAction(52, SetCurrentCompanionByName);
	LinkAction(53, EquipToHead);
	LinkAction(54, EquipToUpperBody);
	LinkAction(55, EquipToLowerBody);
	LinkAction(56, EquipToFeet);
	LinkAction(57, EquipToHands);
	LinkAction(58, EquipToBelt);
	LinkAction(59, EquipToEquipSlot);

	LinkAction(60, SetInventoryBagSkillsSize);
	LinkAction(61, setCurrentBagToSkills);
	LinkAction(62, EquipItemByName);
	LinkAction(63, DequipItemByName);
	LinkAction(64, UseItemByName);

	LinkAction(65, SetCurrentContainerToNone);
	LinkAction(66, SetCurrentCompanionToNone);
	LinkAction(67, LoadContainerDatabase);
	LinkAction(68, AddCompanionToSaveFile);

	

	LinkCondition(0, IsThereDialogToShow);
	LinkCondition(1, IsDialogOver);
	LinkCondition(2, IsReponseASpecialColor);
	LinkCondition(3, DoesValueExist);
	LinkCondition(4, DoesPlayerHaveItem);
	LinkCondition(5, IsFusionActionTriggered);
	LinkCondition(6, IsReponseEmpty);
	LinkCondition(7, CompareDialogImageName);
	LinkCondition(8, IsFlagTrue);
	LinkCondition(9, IsFlagFalse);
	//
	LinkCondition(10, IsQuestActive);
	LinkCondition(11, IsQuestInactive);
	//LinkCondition(12, AreQuestRequirementsFullfilled);
	LinkCondition(13, IsQuestComplete);
	LinkCondition(14, IsQuestFailed);
	LinkCondition(15, WasAnyQuestJustCompleted);
	LinkCondition(16, WasAnyQuestJustFailed);

	// inventory        
	LinkCondition(17, IsCurrentBagGeneral);
	LinkCondition(18, IsCurrentBagWearable);
	LinkCondition(19, IsCurrentBagEquipable);
	LinkCondition(20, IsCurrentBagMaterial);
	LinkCondition(21, IsCurrentBagConsumable);
	LinkCondition(22, IsCurrentBagQuest);
	LinkCondition(23, IsItemUsable);
	LinkCondition(24, IsItemWearable);
	LinkCondition(25, IsItemEquipped);
	LinkCondition(26, WasItemUsed);
	LinkCondition(27, IsCurrentBagSkills);
	LinkCondition(28, IsPlayerAtContainer);
	LinkCondition(29, PlayerHasCompanion);
	LinkCondition(30, PlayerHasEncounteredCompanionAlready);
	



	LinkExpression(0, GetCurrentDialogText);
	LinkExpression(1, GetcurrentDialogImageName);
	LinkExpression(2, GetResponseTextByIndex);
	LinkExpression(3, GetAvaliableReponseCount);
	LinkExpression(4, GetLastSelectedResponseIndex);
	LinkExpression(5, GetCurrentDialogID);
	LinkExpression(6, GetGameValueByName);
	LinkExpression(7, GetGameValueNameByIndex);
	LinkExpression(8, GetTotalGameValueCount);
	LinkExpression(9, GetGameFlagStateAsString);
	LinkExpression(10, GetGameFlagNameByIndex);
	LinkExpression(11, GetTotalGameFlagCount);
	LinkExpression(12, GetGameItemQuantityByName);

	LinkExpression(13, GetResponseTextByIndex);	// dummy. delete m ee.
	LinkExpression(14, GetAvaliableReponseCount);	// dummy . delete meee
//	LinkExpression(13, GetGameItemNameByIndex);
//	LinkExpression(14, GetTotalGameItems);
	LinkExpression(15, GetFusionActionNameIndex);
	LinkExpression(16, GetTotalPendingFusionActions);
	//
	LinkExpression(17, GetQuestNameByIndex);
	LinkExpression(18, GetQuestStateAsString);
	LinkExpression(19, GetQuestDescriptionByName);
	LinkExpression(20, GetTotalQuestCount);

	LinkExpression(21, GetNPCCount);
	LinkExpression(22, GetNPCInWorldDialogStringByIndex);
	LinkExpression(23, GetNPCNameByIndex);  // dummy. delete m ee.


	// Inventory
	LinkExpression(24, GetInventoryBagGeneralSize);
	LinkExpression(25, GetInventoryBagWearableSize);
	LinkExpression(26, GetInventoryBagEquipableSize);
	LinkExpression(27, GetInventoryBagMaterialSize);
	LinkExpression(28, GetInventoryBagConsumableSize);
	LinkExpression(29, GetInventoryBagQuestsize);

	LinkExpression(30, GetGeneralBagItemNameByIndex);
	LinkExpression(31, GetWearableBagItemNameByIndex);
	LinkExpression(32, GetMaterialItemNameByIndex);
	LinkExpression(33, GetConsumableBagItemNameByIndex);
	LinkExpression(34, GetEquipableBagItemNameByIndex);
	LinkExpression(35, GetQuestBagItemNameByIndex);

	LinkExpression(36, GetCurrentCompanionName);
	LinkExpression(37, GetCurrentContainerName);
	LinkExpression(38, GetSizeOfContainerByName);

	LinkExpression(39, GetItemTypeAsStringByName);
	LinkExpression(40, GetItemWeightByName);
	LinkExpression(41, GetItemDescriptionByName);
	LinkExpression(42, GetItemNumberOfModifierEffectsByName);
	LinkExpression(43, GetItemModiferEffectNameByIndex);
	LinkExpression(44, GetItemModiferEffectValueByIndex);
	LinkExpression(45, GetCurrentBagItemNameByIndex);
	LinkExpression(46, GetCurrentBagIteQuantityByIndex);
	LinkExpression(47, GetCurrentBagSize);

	LinkExpression(48, GetCurrentContainerName);
	LinkExpression(49, GetContainerSize);
	LinkExpression(50, GetContainerItemNameByIndex);
	LinkExpression(51, GetContainerItemQuanityByIndex);
	LinkExpression(52, GetContainerIconName);

	LinkExpression(53, GetItemNameEquippedToHead);
	LinkExpression(54, GetItemNameEquippedToUpperBody);
	LinkExpression(55, GetItemNameEquippedToLowerBody);
	LinkExpression(56, GetItemNameEquippedToFeet);
	LinkExpression(57, GetItemNameEquippedToHands);
	LinkExpression(58, GetItemNameEquippedToBelt);
	LinkExpression(59, GetItemNameEquippedToEquipSlot);
	LinkExpression(60, GetCurrentWeight);
	LinkExpression(61, GetMaxWeight);
	LinkExpression(62, GetInventoryBagSkillssize);
	LinkExpression(63, GetSkillBagItemNameByIndex);
	LinkExpression(64, GetItemPositionInInventoryByItemName);
	LinkExpression(65, GetItemPositionInContainerByItemName);
	
	/*
		This is where you'd do anything you'd do in CreateRunObject in the original SDK

		It's the only place you'll get access to edPtr at runtime, so you should transfer
		anything from edPtr to the extension class here.

	*/

	// Don't use "this" inside these lambda functions, always ext.
	// There can be nothing in the [] section of the lambda.
	// If you're not sure about lambdas, you can remove this debugger stuff without any side effects;
	// it's just an example of how to use the debugger. You can view it in Fusion itself to see.
	FusionDebugger.AddItemToDebugger(
		// reader function for your debug item
		[](Extension *ext, std::tstring &writeTo) {
			writeTo = _T("My text is: ") + ext->exampleDebuggerTextItem;
		},
		// writer function (can be null if you don't want user to be able to edit it in debugger)
		[](Extension *ext, std::tstring &newText)
		{
			ext->exampleDebuggerTextItem = newText;
			return true; // accept the changes
		}, 500, NULL
	);

}

Extension::~Extension()
{

}


REFLAG Extension::Handle()
{
	/*
		If your extension will draw to the MMF window you should first
		check if anything about its display has changed :

			if (rdPtr->roc.rcChanged)
			  return REFLAG::DISPLAY;
			else
			  return REFLAG::NONE;

		You will also need to make sure you change this flag yourself
		to 1 whenever you want to redraw your object

		If your extension won't draw to the window, but it still needs
		to do something every MMF loop use :

			return REFLAG::NONE;

		If you don't need to do something every loop, use :

			return REFLAG::ONE_SHOT;

		This doesn't mean this function can never run again. If you want MMF
		to handle your object again (causing this code to run) use this function:

			Runtime.Rehandle();

		At the end of the loop this code will run

	*/

	// Will not be called next loop
	return REFLAG::ONE_SHOT;
}


REFLAG Extension::Display()
{
	/*
		If you return REFLAG_DISPLAY in Handle() this routine will run.
	*/

	// Ok
	return REFLAG::DISPLAY;
}

short Extension::Pause()
{

	// Ok
	return 0;
}

short Extension::Continue()
{

	// Ok
	return 0;
}


// These are called if there's no function linked to an ID

void Extension::Action(int ID)
{

}

long Extension::Condition(int ID)
{
	return false;
}

long Extension::Expression(int ID)
{
	return 0;
}


