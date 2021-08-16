
#include "DialogEngine.h"

//std::vector<GameItem> DialogEngine::s_gameItems;
std::vector<GameFlag> DialogEngine::s_gameFlags;
std::vector<GameFloat> DialogEngine::s_gameFloats;
std::vector<DialogEntry> DialogEngine::s_dialogEntries;
std::vector<Response> DialogEngine::s_avaliableResponses;
std::vector<std::string> DialogEngine::s_pendingFusionActions;
DialogEntry DialogEngine::s_currentDialog;
int DialogEngine::s_lastSelectedResponseIndex;
std::vector<Quest> DialogEngine::s_Quests;
bool DialogEngine::s_wasAnyQuestJustCompleted = false;
bool DialogEngine::s_wasAnyQuestJustFailed = false;
std::vector<NPC> DialogEngine::s_NPCs;
//std::map<int, std::string> DialogEngine::s_itemFixedValueMap;
int DialogEngine::s_textDuration = 150;


////////////////////////////////
//                            //
//   F I L E   L O A D I N G  // 
//                            //
//////////////////////////////// and saving...


void DialogEngine::SavePlayerFile(std::string filename)
{
	rapidjson::Document document;
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value inventoryArray(rapidjson::kArrayType);
	document.SetObject();

	rapidjson::Value object(rapidjson::kObjectType);

	SaveString(&object, "Current Companion", Inventory::s_inventoryState.currentCompanionName, allocator);
	SaveString(&object, "Equiped To Head", Inventory::s_equippedItems.m_head, allocator);
	SaveString(&object, "Equiped To Upper Body", Inventory::s_equippedItems.m_upperBody, allocator);
	SaveString(&object, "Equiped To Hands", Inventory::s_equippedItems.m_hands, allocator);
	SaveString(&object, "Equiped To Belt", Inventory::s_equippedItems.m_belt, allocator);
	SaveString(&object, "Equiped To Lower Body", Inventory::s_equippedItems.m_lowerBody, allocator);
	SaveString(&object, "Equiped To Feet", Inventory::s_equippedItems.m_feet, allocator);
	SaveString(&object, "Equiped To Equipped", Inventory::s_equippedItems.m_equipped, allocator);

	// Quests
	rapidjson::Value questArray;
	questArray.SetArray();
	for (int i = 0; i < s_Quests.size(); i++) {
		rapidjson::Value flagObject;
		flagObject.SetObject();
		SaveString(&flagObject, "Name", s_Quests[i].m_name, allocator);
		SaveString(&flagObject, "State", s_Quests[i].GetStateAsString(), allocator);
		questArray.PushBack(flagObject, allocator);
	}
	object.AddMember("Quests", questArray, allocator);

	// Values
	rapidjson::Value valuesArrau;
	valuesArrau.SetArray();
	for (int i = 0; i < s_gameFloats.size(); i++) {
		rapidjson::Value flagObject;
		flagObject.SetObject();
		SaveString(&flagObject, "Name", s_gameFloats[i].m_name, allocator);
		SaveFloat(&flagObject, "Value", s_gameFloats[i].m_value, allocator);
		valuesArrau.PushBack(flagObject, allocator);
	}
	object.AddMember("Values", valuesArrau, allocator);

	// Flags
	rapidjson::Value flagsArray;
	flagsArray.SetArray();
	for (int i = 0; i < s_gameFlags.size(); i++) {
		rapidjson::Value flagObject;
		flagObject.SetObject();
		SaveString(&flagObject, "Name", s_gameFlags[i].m_name, allocator);
		SaveInt(&flagObject, "State", s_gameFlags[i].m_state, allocator);
		flagsArray.PushBack(flagObject, allocator);
	}
	object.AddMember("Flags", flagsArray, allocator);

	// Inventory
	for (int j = 0; j < 7; j++)
	{
		rapidjson::Value inventoryArray;
		inventoryArray.SetArray();
		rapidjson::Value invSize;
		invSize.SetObject();

		PlayerInventoryItem* playerInventory = Inventory::s_playerInventory_general;

		if (j == 0) {
			playerInventory = Inventory::s_playerInventory_general;
			SaveInt(&invSize, "BagSize", Inventory::m_max_general_slots, allocator);
		}
		if (j == 1) {
			playerInventory = Inventory::s_playerInventory_consumable;
			SaveInt(&invSize, "BagSize", Inventory::m_max_consumable_slots, allocator);
		}
		if (j == 2) {
			playerInventory = Inventory::s_playerInventory_equipable;
			SaveInt(&invSize, "BagSize", Inventory::m_max_equipable_slots, allocator);
		}
		if (j == 3) {
			playerInventory = Inventory::s_playerInventory_material;
			SaveInt(&invSize, "BagSize", Inventory::m_max_material_slots, allocator);
		}
		if (j == 4) {
			playerInventory = Inventory::s_playerInventory_quest;
			SaveInt(&invSize, "BagSize", Inventory::m_max_quest_slots, allocator);
		}
		if (j == 5) {
			playerInventory = Inventory::s_playerInventory_skills;
			SaveInt(&invSize, "BagSize", Inventory::m_max_skill_slots, allocator);
		}
		if (j == 6) {
			playerInventory = Inventory::s_playerInventory_wearable;
			SaveInt(&invSize, "BagSize", Inventory::m_max_wearable_slots, allocator);
		}

		inventoryArray.PushBack(invSize, allocator);
		for (int i = 0; i < INVENTORY_SIZE_LIMIT; i++)
		{
			PlayerInventoryItem* item = &playerInventory[i];

			if (item->m_name != EMPTY_SLOT) {
				rapidjson::Value obj;
				obj.SetObject();
				SaveString(&obj, "Name", item->m_name, allocator);
				SaveInt(&obj, "Qty", item->m_quantity, allocator);
				SaveInt(&obj, "Index", i, allocator);
				inventoryArray.PushBack(obj, allocator);
			}
		}

		if (j == 0)	object.AddMember("Inventory General", inventoryArray, allocator);
		if (j == 1)	object.AddMember("Inventory Consumable", inventoryArray, allocator);
		if (j == 2)	object.AddMember("Inventory Equipable", inventoryArray, allocator);
		if (j == 3)	object.AddMember("Inventory Material", inventoryArray, allocator);
		if (j == 4)	object.AddMember("Inventory Quest", inventoryArray, allocator);
		if (j == 5)	object.AddMember("Inventory Skills", inventoryArray, allocator);
		if (j == 6)	object.AddMember("Inventory Wearable", inventoryArray, allocator);
	}

	// Companions Encountered
	rapidjson::Value companionsArray;
	companionsArray.SetArray();
	for (int i = 0; i < Inventory::s_compainions.size(); i++) {
		Companion* companion = &Inventory::s_compainions[i];
		rapidjson::Value obj;
		obj.SetObject();
		SaveString(&obj, "Name", companion->name, allocator);
		SaveString(&obj, "Type", companion->TypeAsString(), allocator);
		companionsArray.PushBack(obj, allocator);
	}
	object.AddMember("Companions Encountered", companionsArray, allocator);


	// Container States
	rapidjson::Value containersObject;
	containersObject.SetArray();
	for (Container& container : Inventory::s_containers)
	{
		rapidjson::Value object(rapidjson::kObjectType);

		SaveString(&object, "Name", container.name, allocator);
		SaveString(&object, "Icon", container.iconName, allocator);

		rapidjson::Value contentsObject;
		contentsObject.SetArray();
		for (int i = 0; i < container.contentsVector.size(); i++) {
			rapidjson::Value itemObject;
			itemObject.SetObject();
			SaveString(&itemObject, "Name", container.contentsVector[i].m_name, allocator);
			SaveInt(&itemObject, "Qty", container.contentsVector[i].m_quantity, allocator);
			contentsObject.PushBack(itemObject, allocator);
		}
		object.AddMember("Contents", contentsObject, allocator);

		containersObject.PushBack(object, allocator);
	}
	object.AddMember("Container States", containersObject, allocator);



	inventoryArray.PushBack(object, allocator);
	document.AddMember("Savefile", inventoryArray, allocator);

	// Convert JSON document to string
	rapidjson::StringBuffer strbuf;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(strbuf);
	document.Accept(writer);

	// Save it
	std::string data = strbuf.GetString();
	std::ofstream out(filename);
	out << data;
	out.close();
}

void DialogEngine::LoadQuestFile(std::string filename)
{
	std::ifstream file(filename);
	std::string line;
	Quest tempQuest = Quest();
	NPC* npc = nullptr;
	//std::string npcName;
	NPCQuestData tempNPCQuestData;


	while (getline(file, line))
	{
		// Found a new Quest? Reset and store name
		if (Util::StringContains(line, "NAME:"))
		{
			// You're working on a new one Quest now so push the last one into the array.
			if (tempQuest.m_name != "UNDEFINED") {
				s_Quests.push_back(tempQuest);
				// reset for reuse
				tempQuest.m_name = "";
				tempQuest.m_description = "";
				tempQuest.m_requiredFlags.clear();
				//tempQuest.m_requiredItems.clear();
				//tempQuest.m_rewardItems.clear();
				tempQuest.m_rewardFloats.clear();
				tempQuest.m_conditions.clear();

				// add NPC quest data if this quest is associated with an NPC
				if (npc != nullptr) {
					npc->m_quests.push_back(tempNPCQuestData);
					//	std::cout << "PUSHING QUEST DATA: " << tempNPCQuestData.m_questName << "\n";
				}
				npc = nullptr;
				tempNPCQuestData = NPCQuestData();
			}
			tempQuest.m_name = Util::GetSubstringAfterColon(line);
		}

		// NPC?
		else if (Util::StringContains(line, "NPC")) {
			std::string npcName = Util::GetSubstringAfterColon(line);
			npc = GetNPCAndCreateIfItDoesntExist(npcName);
			tempNPCQuestData.m_questName = tempQuest.m_name;
			//npc->m_HasQuest = true;
		}
		// quest in world dialog ids
		else if (Util::StringContains(line, "INWORLD_DIALOG_TEXT_INACTIVE:"))
			tempNPCQuestData.m_questInWorldDialogText.inactive = Util::GetSubstringAfterColon(line);
		else if (Util::StringContains(line, "INWORLD_DIALOG_TEXT_ACTIVE:"))
			tempNPCQuestData.m_questInWorldDialogText.active = Util::GetSubstringAfterColon(line);
		else if (Util::StringContains(line, "INWORLD_DIALOG_TEXT_COMPLETED:") || Util::StringContains(line, "INWORLD_DIALOG_TEXT_COMPLETE:"))
			tempNPCQuestData.m_questInWorldDialogText.complete = Util::GetSubstringAfterColon(line);
		else if (Util::StringContains(line, "INWORLD_DIALOG_TEXT_FAILED:"))
			tempNPCQuestData.m_questInWorldDialogText.failed = Util::GetSubstringAfterColon(line);
		else if (Util::StringContains(line, "DIALOG_ID_EXP_TOO_LOW:"))
			tempNPCQuestData.m_questInWorldDialogText.expTooLow = Util::GetSubstringAfterColon(line);

		// quest dialog ids
		else if (Util::StringContains(line, "DIALOG_ID_INACTIVE:"))
			tempNPCQuestData.m_questDialogIDs.inactive = Util::StringToInt(Util::GetSubstringAfterColon(line));
		else if (Util::StringContains(line, "DIALOG_ID_ACTIVE:"))
			tempNPCQuestData.m_questDialogIDs.active = Util::StringToInt(Util::GetSubstringAfterColon(line));
		else if (Util::StringContains(line, "DIALOG_ID_COMPLETED:") || Util::StringContains(line, "DIALOG_ID_COMPLETE:"))
			tempNPCQuestData.m_questDialogIDs.complete = Util::StringToInt(Util::GetSubstringAfterColon(line));
		else if (Util::StringContains(line, "DIALOG_ID_FAILED:"))
			tempNPCQuestData.m_questDialogIDs.failed = Util::StringToInt(Util::GetSubstringAfterColon(line));
		else if (Util::StringContains(line, "DIALOG_ID_EXP_TOO_LOW:"))
			tempNPCQuestData.m_questDialogIDs.expTooLow = Util::StringToInt(Util::GetSubstringAfterColon(line));

		// Quest description
		else if (Util::StringContains(line, "DESCRIPTION:"))
			tempQuest.m_description = Util::GetSubstringAfterColon(line);

		// Requirement flag
		else if (Util::StringContains(line, "REQUIREMENT_FLAG_TRUE:"))
			tempQuest.m_requiredFlags.push_back(GameFlag(Util::GetSubstringAfterColon(line), true));

		else if (Util::StringContains(line, "REQUIREMENT_FLAG_FALSE:"))
			tempQuest.m_requiredFlags.push_back(GameFlag(Util::GetSubstringAfterColon(line), false));

		// Requirement item
		//else if (Util::StringContains(line, "REQUIREMENT_ITEM:"))
		//	tempQuest.m_requiredItems.push_back(GameItem(Util::GetSubstringAfterColon(line), 1));

		// Reward Item
		/*else if (line.substr(0, 12) == "REWARD_ITEM:")
		{
			std::string str = Util::GetSubstringAfterColon(line);
			std::string itemName = Util::GetSubstringBeforeParentheses(str);
			int quantity = (int)Util::GetFloatBetweenParentheses(str);
			if (quantity == 0)
				quantity = 1;

			tempQuest.m_rewardItems.push_back(GameItem(itemName, quantity));
			//	std::cout << " " << itemName << " [" << quantity << "]\n";
		}*/

		// Reward Float		
		else if (line.substr(0, 13) == "REWARD_VALUE:")
		{
			std::string str = Util::GetSubstringAfterColon(line);
			std::string valueName = Util::GetSubstringBeforeParentheses(str);
			float quantity = Util::GetFloatBetweenParentheses(str);

			tempQuest.m_rewardFloats.push_back(GameFloat(valueName, quantity));
			//std::cout << " " << valueName << " " << "[" << quantity << "]\n";
		}

		// Conditions
		else if (line.substr(0, 10) == "CONDITION:") {
			std::string str = Util::ToUppercase(Util::GetSubstringAfterColon(line));
			tempQuest.m_conditions.push_back(ConditionObjectFromString(str));
		}

	}

	// You're at the end of file now, if you're working with a quest you haven't added yet, do so.
	if (tempQuest.m_name != "UNDEFINED") {
		s_Quests.push_back(tempQuest);

		// add NPC quest data if this quest is associated with an NPC
		if (npc != nullptr)
			npc->m_quests.push_back(tempNPCQuestData);
	}

	file.close();
}
#pragma warning (disable : 4996)

void DialogEngine::LoadPlayerFile(std::string filename)
{
	std::string fileName = filename;
	FILE* pFile = fopen(fileName.c_str(), "rb");
	char buffer[65536];
	rapidjson::FileReadStream is(pFile, buffer, sizeof(buffer));
	rapidjson::Document document;
	document.ParseStream<0, rapidjson::UTF8<>, rapidjson::FileReadStream>(is);

	// Check for errors
	if (document.HasParseError())
		std::cout << "Error  : " << document.GetParseError() << '\n' << "Offset : " << document.GetErrorOffset() << '\n';

	const rapidjson::Value& a = document["Savefile"];
	assert(a.IsArray());

	for (rapidjson::SizeType i = 0; i < a.Size(); i++)
	{
		auto element = a[i].GetObject();

		// Quests
		auto quests = element["Quests"].GetArray();
		for (rapidjson::SizeType q = 0; q < quests.Size(); q++) {
			auto quest = quests[q].GetObject();
			std::string questName = quest["Name"].GetString();
			std::string questState = quest["State"].GetString();
			DialogEngine::SetQuestStateByString(questName, questState);
		}

		// Values		
		auto values = element["Values"].GetArray();
		for (rapidjson::SizeType q = 0; q < values.Size(); q++) {
			auto valueElement = values[q].GetObject();
			std::string name = valueElement["Name"].GetString();
			float value = valueElement["Value"].GetFloat();
			DialogEngine::SetGameFloat(name, value);
		}

		// Flags	
		auto flags = element["Flags"].GetArray();
		for (rapidjson::SizeType q = 0; q < flags.Size(); q++) {
			auto flag = flags[q].GetObject();
			std::string name = flag["Name"].GetString();
			int state = flag["State"].GetInt();
			DialogEngine::SetGameFlag(name, state);
		}

		// Inventory General
		auto inventoryGeneral = element["Inventory General"].GetArray();
		for (rapidjson::SizeType q = 0; q < inventoryGeneral.Size(); q++) {
			auto el = inventoryGeneral[q].GetObject();

			if (el.HasMember("BagSize"))
				Inventory::SetGeneralInventoryBagSize(el["BagSize"].GetInt());

			if (el.HasMember("Name")) {
				std::string itemName = el["Name"].GetString();
				int itemQty = el["Qty"].GetInt();
				int index = el["Index"].GetInt();
				Inventory::s_playerInventory_general[index].m_name = itemName;
				Inventory::s_playerInventory_general[index].m_quantity = itemQty;
			}
		}
		// Inventory Consumable
		auto inventoryConsumable = element["Inventory Consumable"].GetArray();
		for (rapidjson::SizeType q = 0; q < inventoryConsumable.Size(); q++) {
			auto el = inventoryConsumable[q].GetObject();

			if (el.HasMember("BagSize"))
				Inventory::SetConsumableInventoryBagSize(el["BagSize"].GetInt());

			if (el.HasMember("Name")) {
				std::string itemName = el["Name"].GetString();
				int itemQty = el["Qty"].GetInt();
				int index = el["Index"].GetInt();
				Inventory::s_playerInventory_consumable[index].m_name = itemName;
				Inventory::s_playerInventory_consumable[index].m_quantity = itemQty;
			}
		}
		// Inventory Equipable
		auto inventoryEquipable = element["Inventory Equipable"].GetArray();
		for (rapidjson::SizeType q = 0; q < inventoryEquipable.Size(); q++) {
			auto el = inventoryEquipable[q].GetObject();

			if (el.HasMember("BagSize"))
				Inventory::SetEquipableInventoryBagSize(el["BagSize"].GetInt());

			if (el.HasMember("Name")) {
				std::string itemName = el["Name"].GetString();
				int itemQty = el["Qty"].GetInt();
				int index = el["Index"].GetInt();
				Inventory::s_playerInventory_equipable[index].m_name = itemName;
				Inventory::s_playerInventory_equipable[index].m_quantity = itemQty;
			}
		}
		// Inventory Material
		auto inventoryMaterial = element["Inventory Material"].GetArray();
		for (rapidjson::SizeType q = 0; q < inventoryMaterial.Size(); q++) {
			auto el = inventoryMaterial[q].GetObject();

			if (el.HasMember("BagSize"))
				Inventory::SetMaterialInventoryBagSize(el["BagSize"].GetInt());

			if (el.HasMember("Name")) {
				std::string itemName = el["Name"].GetString();
				int itemQty = el["Qty"].GetInt();
				int index = el["Index"].GetInt();
				Inventory::s_playerInventory_material[index].m_name = itemName;
				Inventory::s_playerInventory_material[index].m_quantity = itemQty;
			}
		}
		// Inventory Quest
		auto inventoryQuest = element["Inventory Quest"].GetArray();
		for (rapidjson::SizeType q = 0; q < inventoryQuest.Size(); q++) {
			auto el = inventoryQuest[q].GetObject();

			if (el.HasMember("BagSize"))
				Inventory::SetQuestInventoryBagSize(el["BagSize"].GetInt());

			if (el.HasMember("Name")) {
				std::string itemName = el["Name"].GetString();
				int itemQty = el["Qty"].GetInt();
				int index = el["Index"].GetInt();
				Inventory::s_playerInventory_quest[index].m_name = itemName;
				Inventory::s_playerInventory_quest[index].m_quantity = itemQty;
			}
		}
		// Inventory Skills
		auto inventorySkills = element["Inventory Skills"].GetArray();
		for (rapidjson::SizeType q = 0; q < inventorySkills.Size(); q++) {
			auto el = inventorySkills[q].GetObject();

			if (el.HasMember("BagSize"))
				Inventory::SetSkillInventoryBagSize(el["BagSize"].GetInt());

			if (el.HasMember("Name")) {
				std::string itemName = el["Name"].GetString();
				int itemQty = el["Qty"].GetInt();
				int index = el["Index"].GetInt();
				Inventory::s_playerInventory_skills[index].m_name = itemName;
				Inventory::s_playerInventory_skills[index].m_quantity = itemQty;
			}
		}
		// Inventory Wearable
		auto inventoryWearable = element["Inventory Wearable"].GetArray();
		for (rapidjson::SizeType q = 0; q < inventoryWearable.Size(); q++) {
			auto el = inventoryWearable[q].GetObject();

			if (el.HasMember("BagSize"))
				Inventory::SetWearableInventoryBagSize(el["BagSize"].GetInt());

			if (el.HasMember("Name")) {
				std::string itemName = el["Name"].GetString();
				int itemQty = el["Qty"].GetInt();
				int index = el["Index"].GetInt();
				Inventory::s_playerInventory_wearable[index].m_name = itemName;
				Inventory::s_playerInventory_wearable[index].m_quantity = itemQty;
			}
		}

		// Companions Encountered
		auto companionsEncountered = element["Companions Encountered"].GetArray();
		for (rapidjson::SizeType q = 0; q < companionsEncountered.Size(); q++) {
			auto el = companionsEncountered[q].GetObject();
			std::string name = el["Name"].GetString();
			std::string type = el["Type"].GetString();
			if (type == "DOG")
				Inventory::NewCompanion(name, CompanionType::DOG);
			else if (type == "CAT")
				Inventory::NewCompanion(name, CompanionType::CAT);
			else if (type == "DONKEY")
				Inventory::NewCompanion(name, CompanionType::DONKEY);
		}

		// Container states
		Inventory::s_containers.clear();
		auto containers = element["Container States"].GetArray();
		for (rapidjson::SizeType q = 0; q < containers.Size(); q++)
		{
			auto el = containers[q].GetObject();
			std::string name = el["Name"].GetString();
			std::string icon = el["Icon"].GetString();
			std::vector<PlayerInventoryItem> containerContents;
			auto contents = el["Contents"].GetArray();
			for (rapidjson::SizeType j = 0; j < contents.Size(); j++)
			{
				auto itemEl = contents[j].GetObject();
				PlayerInventoryItem item;
				item.m_name = itemEl["Name"].GetString();
				item.m_quantity = itemEl["Qty"].GetInt();
				containerContents.push_back(item);
			}
			Inventory::NewContainer(name, icon, containerContents.size(), containerContents);
		}

		// Equipped
		std::string equippedToHead = element["Equiped To Head"].GetString();
		std::string equippedToUpperBody = element["Equiped To Upper Body"].GetString();
		std::string equippedToHands = element["Equiped To Hands"].GetString();
		std::string equippedToBelt = element["Equiped To Belt"].GetString();
		std::string equippedToLowerBody = element["Equiped To Lower Body"].GetString();
		std::string equippedToFeet = element["Equiped To Feet"].GetString();
		std::string equippedToEquipped = element["Equiped To Equipped"].GetString();
		Inventory::s_equippedItems.m_belt = equippedToBelt;
		Inventory::s_equippedItems.m_equipped = equippedToEquipped;
		Inventory::s_equippedItems.m_feet = equippedToFeet;
		Inventory::s_equippedItems.m_hands = equippedToHands;
		Inventory::s_equippedItems.m_head = equippedToHead;
		Inventory::s_equippedItems.m_lowerBody = equippedToLowerBody;
		Inventory::s_equippedItems.m_upperBody = equippedToUpperBody;

		// Current Companion
		std::string currentCompanion = element["Current Companion"].GetString();
		Inventory::SetCurrentCompanionByName(currentCompanion);
	}
}

void DialogEngine::LoadDialogFile(std::string filename)
{
	std::ifstream file(filename);
	std::string line;
	DialogEntry tempDialogEntry = DialogEntry();

	while (getline(file, line))
	{
		// New dialog entry
		if (line[0] == '#')
		{
			// Add the last dialog entry to the vector, cause you're working on a new one now.
			if (tempDialogEntry.m_text != "NO TEXT") {
				s_dialogEntries.push_back(tempDialogEntry);
				// reset for reuse
				tempDialogEntry.m_ID = -1;
				tempDialogEntry.m_imageName = "NO IMAGE";
				tempDialogEntry.m_text = "NO TEXT";
				tempDialogEntry.m_responses.clear();
				tempDialogEntry.m_conditions.clear();
				tempDialogEntry.m_npcTriggerName = "";
			}

			// ID
			std::string ID_string = line.substr(1, line.length() - 1);
			int ID = Util::StringToInt(ID_string);
			tempDialogEntry.m_ID = ID;
		}
		// NPC Trigger
		else if (Util::StringContains(line, "NPC_TRIGGER:")) {
			tempDialogEntry.m_npcTriggerName = Util::GetSubstringAfterColon(line);
		}
		// Conitions
		else if (line.substr(0, 10) == "CONDITION:") {
			std::string str = Util::ToUppercase(Util::GetSubstringAfterColon(line));

			tempDialogEntry.m_conditions.push_back(ConditionObjectFromString(str));
		}

		// Set image name
		else if (line.substr(0, 3) == "IMG") {
			tempDialogEntry.m_imageName = line.substr(5, line.length() - 1);
		}

		// Set text
		else if (line.substr(0, 4) == "TEXT") {
			tempDialogEntry.m_text = line.substr(6, line.length() - 1);
		}

		// Add response
		else if (line.substr(0, 5) == "REPLY")
		{
			std::string wholeLine = line.substr(7, line.length() - 1);
			Response response;

			// Check for no special shit...
			if (wholeLine.find('[') == std::string::npos) {
				response.m_text = wholeLine;
			}
			// Well I guess it has some then...
			else
			{
				// First isolate the main text;
				response.m_text = wholeLine.substr(0, wholeLine.find('['));

				// Now isolate any special tags
				std::vector<std::string> tags;
				bool finished = false;
				while (!finished)
				{
					int begin = wholeLine.find('[');
					int end = wholeLine.find(']');
					std::string tag = wholeLine.substr(begin + 1, end - begin - 1);
					wholeLine = Util::RemoveFromBeginning(wholeLine, end + 1); // delete everything before the found closing tag
					tags.push_back(tag);

					if (wholeLine.find(']') == std::string::npos)
						finished = true;
				}

				// Now loop over those tags and "process" them
				for (std::string tag : tags)
				{
					std::string leftSide = Util::ToUppercase(Util::GetSubstringBeforeColon(tag));
					std::string rightSide = Util::ToUppercase(Util::GetSubstringAfterColon(tag));

					if (leftSide == "COMPLETE_QUEST")
						response.m_CompleteQuests.push_back(rightSide);

					else if (leftSide == "ACTIVATE_QUEST")
						response.m_ActivateQuests.push_back(rightSide);

					else if (leftSide == "FAIL_QUEST")
						response.m_FailQuests.push_back(rightSide);

					// Fusion actions
					else if (leftSide == "FUSION_ACTION")
						response.m_fusionActions.push_back(rightSide);

					// Engine Actions
					else if (leftSide == "ACTION")
					{
						std::string name = Util::GetSubstringBeforeEquals(rightSide);
						std::string actionRightSide = Util::ToUppercase(Util::GetSubstringAfterEquals(rightSide));
						int quantity = (int)Util::GetFloatBetweenParentheses(actionRightSide);

						ResponseAction responseAction;
						responseAction.m_name = name;

						// Give item
						if (Util::StringContains(actionRightSide, "GIVE_ITEM")) {
							if (quantity == 0)
								quantity = 1;
							responseAction.m_actionType = ActionType::GIVE_ITEM;
							responseAction.m_modifierValue = (float)quantity;
						}

						// Take item
						else if (Util::StringContains(actionRightSide, "TAKE_ITEM")) {
							if (quantity == 0)
								quantity = 99999;

							responseAction.m_actionType = ActionType::TAKE_ITEM;
							responseAction.m_modifierValue = (float)quantity;
						}

						// Bool action
						else if (actionRightSide == "TRUE")
							responseAction.m_actionType = ActionType::SET_BOOL_TRUE;
						else if (actionRightSide == "FALSE")
							responseAction.m_actionType = ActionType::SET_BOOL_FALSE;

						// Set value. You can reuse your earlier "equals detection"
						else if (Util::StringContains(rightSide, "=")) {
							responseAction.m_modifierValue = Util::StringToFloat(actionRightSide);
							responseAction.m_actionType = ActionType::SET_FLOAT;
						}
						// Add to value
						else if (Util::StringContains(rightSide, "+")) {
							name = Util::GetSubstringBeforeChar(rightSide, '+');
							responseAction.m_name = name;
							responseAction.m_modifierValue = Util::StringToFloat(Util::GetSubstringAfterChar(rightSide, '+'));
							responseAction.m_actionType = ActionType::ADD_FLOAT;
						}
						// Subtract from value
						else if (Util::StringContains(rightSide, "-")) {
							name = Util::GetSubstringBeforeChar(rightSide, '-');
							responseAction.m_name = name;
							responseAction.m_modifierValue = Util::StringToFloat(Util::GetSubstringAfterChar(rightSide, '-'));
							responseAction.m_actionType = ActionType::SUBRACT_FLOAT;
						}
						response.m_responseActions.push_back(responseAction);
					}

					// Conditions
					else if (leftSide == "CONDITION")
					{
						response.m_responseConditions.push_back(ConditionObjectFromString(rightSide));
					}

					// Special color
					else if (tag == "SPECIAL_COLOR")
						response.m_isSpecialColor = true;

					// Goto
					else if (tag.find("GOTO") != std::string::npos)
					{
						// Then find the fucking ID
						response.m_gotoID = Util::StringToInt(tag.substr(tag.find(':') + 1));
					}

				}
			}
			tempDialogEntry.m_responses.push_back(response);
		}
	}

	// Well add the dialog entry you were last processing, cause they are only added when the next one is found remember.
	if (tempDialogEntry.m_text != "NO TEXT")
		s_dialogEntries.push_back(tempDialogEntry);

	// Close the file
	file.close();
}



///////////////////////////////
//                           //
//    M I S C    S T U F F   //
//                           //
///////////////////////////////


DialogEntry DialogEngine::GetDialogByID(int ID)
{
	// Find match
	for (DialogEntry& dialogEntry : s_dialogEntries) {
		if (dialogEntry.m_ID == ID)
			return dialogEntry;
	}
	// Otherwise return an empty new one
	return DialogEntry();
}

void DialogEngine::SetCurrentDialogByID(int ID)
{
	s_currentDialog = DialogEngine::GetDialogByID(ID);

	// Determine which responses should be shown
	UpdateAvaliableResponses();
}

std::string DialogEngine::GetCurrentDialogText()
{
	return s_currentDialog.m_text;
}

std::string DialogEngine::GetCurrentDialogImageName()
{
	return s_currentDialog.m_imageName;
}

bool DialogEngine::EvaluateConditionalComparison(std::string name, ConditionType conditionType, float comparisonValue)
{
	// If item or value is not found, assume 0, and perform check...
	float objectValue = 0;

	// Otherwise, get the value
	if (Inventory::HasItem(name))
		objectValue = (float)Inventory::GetItemQuantity(name);
	if (GameFloatExists(name))
		objectValue = GetGameFloat(name);

	// Evaluate comparison
	if (conditionType == ConditionType::FLOAT_GREATER_OR_EQUAL)
		return (objectValue >= comparisonValue);

	else if (conditionType == ConditionType::FLOAT_GREATER)
		return (objectValue > comparisonValue);

	else if (conditionType == ConditionType::FLOAT_LESS_OR_EQUAL)
		return (objectValue <= comparisonValue);

	else if (conditionType == ConditionType::FLOAT_LESS)
		return (objectValue < comparisonValue);

	else if (conditionType == ConditionType::FLOAT_EQUAL)
		return (objectValue == comparisonValue);

	else if (conditionType == ConditionType::FLOAT_NOT_EQUAL)
		return (objectValue != comparisonValue);

	else return false;
}

void DialogEngine::UpdateAvaliableResponses()
{
	// Reset
	s_avaliableResponses.clear();
	//std::cout << s_currentDialog.m_responses.size() << " response count\n";
	// Get avaliable responses
	for (Response& response : s_currentDialog.m_responses)
	{
		if (IsConditionListSatisfied(response.m_responseConditions))
			s_avaliableResponses.push_back(response);
		///else
		//	std::cout << response.m_text << "WAS REJECTED\n";

	loop_exit:;
	}
}

bool DialogEngine::IsDialogOver()
{
	if (s_currentDialog.m_ID == -1)
		return true;
	else
		return false;
}

std::string DialogEngine::GetResponseTextByIndex(int index)
{
	if (index < 0 || index >= (int)s_avaliableResponses.size())
		return "out_of_range";

	return s_avaliableResponses[index].m_text;
}


void DialogEngine::SelectResponse(int index)
{
	s_lastSelectedResponseIndex = index;

	// Did something fuck up and you need to bail early?
	if (index < 0 || index >= (int)s_avaliableResponses.size())
		return;

	// Otherwise begin
	Response selectedRespone = s_avaliableResponses[index];

	// Get any fusion actions
	for (std::string fusionAction : selectedRespone.m_fusionActions) {
		AddFusionAction(fusionAction);
	}

	// Do any quest shit you need to
	for (std::string& quest : selectedRespone.m_ActivateQuests) {
		ActivateQuestByName(quest);
	}
	for (std::string& quest : selectedRespone.m_CompleteQuests)
		CompleteQuestByName(quest);
	for (std::string& quest : selectedRespone.m_FailQuests)
		FailQuestByName(quest);

	// Perform any other actions
	for (ResponseAction& responseAction : selectedRespone.m_responseActions)
	{
		// First you gotta find the GameValue based on the name.
		for (GameFloat& gameFloat : DialogEngine::s_gameFloats)
		{
			if (Util::CaselessEquality(responseAction.m_name, gameFloat.m_name))
			{
				if (responseAction.m_actionType == ActionType::SUBRACT_FLOAT) {
					gameFloat.Subract(responseAction.m_modifierValue);
				}
				else if (responseAction.m_actionType == ActionType::ADD_FLOAT) {
					gameFloat.Add(responseAction.m_modifierValue);
				}
				else if (responseAction.m_actionType == ActionType::SET_FLOAT) {
					gameFloat.SetTo(responseAction.m_modifierValue);
				}
			}
		}
		// But what if it's a BOOL
		if (responseAction.m_actionType == ActionType::SET_BOOL_TRUE) {
			DialogEngine::SetGameFlag(responseAction.m_name, true);
		}
		else if (responseAction.m_actionType == ActionType::SET_BOOL_FALSE) {
			DialogEngine::SetGameFlag(responseAction.m_name, false);
		}

		// Ok but what if it's a GameItem kinda thing
		if (responseAction.m_actionType == ActionType::GIVE_ITEM) {
			Inventory::GiveItem(responseAction.m_name, (int)responseAction.m_modifierValue);
		}
		if (responseAction.m_actionType == ActionType::TAKE_ITEM) {
			Inventory::TakeItem(responseAction.m_name, (int)responseAction.m_modifierValue);
		}
	}

	// Switch to the new dialog
	SetCurrentDialogByID(selectedRespone.m_gotoID);
}

bool DialogEngine::IsResponseSpecialColored(int index)
{
	if (index < 0 || index >= (int)s_avaliableResponses.size())
		return false;
	else
		return s_avaliableResponses[index].m_isSpecialColor;;
}

void DialogEngine::AddFusionAction(std::string name)
{
	s_pendingFusionActions.push_back(name);
}

bool DialogEngine::TriggerFusionAction(std::string name)
{
	for (size_t i = 0; i < s_pendingFusionActions.size(); i++)
	{
		if (Util::CaselessEquality(s_pendingFusionActions[i], name))
		{
			s_pendingFusionActions.erase(s_pendingFusionActions.begin() + i);
			return true;
		}
	}
	return false;
}

std::string DialogEngine::GetFusionActionNameByIndex(int index)
{
	if (index < 0 || index >= (int)s_pendingFusionActions.size())
		return "out_of_range";

	return s_pendingFusionActions[index];
}

bool DialogEngine::CompareDialogImageNameToString(std::string query)
{
	return (GetCurrentDialogImageName() == query);
}

void DialogEngine::ClearAllData()
{
	Inventory::ClearAllPlayerInventory();
	s_gameFlags.clear();
	s_gameFloats.clear();
	s_dialogEntries.clear();
	s_avaliableResponses.clear();
	s_pendingFusionActions.clear();
	s_Quests.clear();
	s_wasAnyQuestJustCompleted = false;
	s_wasAnyQuestJustFailed = false;
	s_currentDialog.m_ID = -1;
	s_NPCs.clear();
}

void DialogEngine::LoadInWorldDialogFile(std::string filename)
{
	std::ifstream file(filename);
	std::string line;
	std::string npcName;

	while (getline(file, line))
	{
		// Found a new Quest? Reset and store name
		if (Util::StringContains(line, "NPC:"))
		{
			npcName = Util::GetSubstringAfterColon(line);
			NPC* npc = CreateNPC(npcName);
		}

		// TEXT???
		else if (Util::StringContains(line, "TEXT:")) {
			std::string text = Util::GetSubstringAfterColon(line);
			GetNPCPointer(npcName)->m_inWorldDialogReplies.push_back(text);
		}
	}
	// Close the file
	file.close();
}



void DialogEngine::UpdateEngine()
{
	// NPC text timers
	for (NPC& npc : s_NPCs)
	{
		if (npc.m_inWorldDialogTextTimer == 0)
			npc.m_inWorldDialogString = "";
		else
			npc.m_inWorldDialogTextTimer--;
	}
}

void DialogEngine::SetTextDuration(int duration)
{
	s_textDuration = duration;
}

void DialogEngine::CheckQuestRequirementsAndPayOuts()
{
	// CHECK FOR ERRORS HERE	


	/*for (Quest& quest : s_Quests)
	{
		// If the quest is active, check if the requirments are met
		if (quest.m_questState == QuestState::ACTIVE)
			quest.CheckRequirements(s_gameFlags, s_gameItems);

		// Pay out if you haven't
		if (quest.m_questState == QuestState::COMPLETE && !quest.m_paidOut)
		{
			for (GameItem& item : quest.m_rewardItems)
				GiveItem(item.m_name, item.m_quantity);
			for (GameFloat& value : quest.m_rewardFloats)
				AddToGameFloat(value.m_name, value.m_value);
			quest.m_paidOut = true;
			s_wasAnyQuestJustCompleted = true;
		}
	}*/
}

void DialogEngine::ActivateQuestByName(std::string query)
{
	for (Quest& quest : s_Quests)
		if (Util::CaselessEquality(quest.m_name, query) && quest.m_questState == QuestState::INACTIVE) {
			quest.m_questState = QuestState::ACTIVE;
			return;
		}
}
/*
void DialogEngine::InactivateQuestByName(std::string query)
{
	for (Quest& quest : s_Quests)
		if (Util::CaselessEquality(quest.m_name, query)) {
			quest.m_questState = QuestState::INACTIVE;
			return;
		}
}*/

void DialogEngine::CompleteQuestByName(std::string query)
{
	for (Quest& quest : s_Quests)
		if (Util::CaselessEquality(quest.m_name, query) && quest.m_questState != QuestState::COMPLETE) {
			quest.m_questState = QuestState::COMPLETE;
			s_wasAnyQuestJustCompleted = true;
			return;
		}
}

void DialogEngine::FailQuestByName(std::string query)
{
	for (Quest& quest : s_Quests)
		if (Util::CaselessEquality(quest.m_name, query) && quest.m_questState != QuestState::FAILED) {
			quest.m_questState = QuestState::FAILED;
			s_wasAnyQuestJustFailed = true;
			return;
		}
}

int DialogEngine::GetQuestCount()
{
	return s_Quests.size();
}

std::string DialogEngine::GetQuestNameByIndex(int index)
{
	if (index < 0 || index >= (int)s_Quests.size())
		return "out_of_range";

	return s_Quests[index].m_name;
}

QuestState DialogEngine::GetQuestStateByIndex(int index)
{
	if (index < 0 || index >= (int)s_Quests.size())
		return QuestState::UNDEFINED;

	return s_Quests[index].m_questState;
}

bool DialogEngine::WasIfAnyQuestWasJustCompleted()
{
	if (s_wasAnyQuestJustCompleted) {
		s_wasAnyQuestJustCompleted = false;
		return true;
	}
	else
		return false;
}

bool DialogEngine::IsQuestActive(std::string query)
{
	for (Quest& quest : s_Quests)
		if (Util::CaselessEquality(quest.m_name, query))
			return (quest.m_questState == QuestState::ACTIVE);
	return false;
}

bool DialogEngine::IsQuestInactive(std::string query)
{
	for (Quest& quest : s_Quests)
		if (Util::CaselessEquality(quest.m_name, query))
			return (quest.m_questState == QuestState::INACTIVE);
	return false;
}

std::string DialogEngine::GetQuestStateAsString(std::string query)
{
	for (Quest& quest : s_Quests)
		if (Util::CaselessEquality(quest.m_name, query))
		{
			if (quest.m_questState == QuestState::ACTIVE) return "ACTIVE";
			if (quest.m_questState == QuestState::INACTIVE) return "INACTIVE";
			if (quest.m_questState == QuestState::COMPLETE) return "COMPLETE";
			if (quest.m_questState == QuestState::FAILED) return "FAILED";
			if (quest.m_questState == QuestState::UNDEFINED) return "UNDEFINED";
		}
	return "QUEST NOT FOUND";
}


std::string DialogEngine::GetQuestDescription(std::string query)
{
	for (Quest& quest : s_Quests)
		if (Util::CaselessEquality(quest.m_name, query))
			return quest.m_description;
	return "";
}

void DialogEngine::SetQuestStateByString(std::string questName, std::string questState)
{
	for (Quest& quest : s_Quests)
		if (Util::CaselessEquality(quest.m_name, questName))
		{
			if (questState == "ACTIVE")
				quest.m_questState = QuestState::ACTIVE;
			else if (questState == "INACTIVE")
				quest.m_questState = QuestState::INACTIVE;
			else if (questState == "COMPLETE")
				quest.m_questState = QuestState::COMPLETE;
			else if (questState == "FAILED")
				quest.m_questState = QuestState::FAILED;
			return;
		}
}



NPC* DialogEngine::CreateNPC(std::string name)
{
	NPC npc;
	npc.m_name = name;
	s_NPCs.push_back(npc);
	return &s_NPCs[s_NPCs.size() - 1];
}

NPC* DialogEngine::GetNPCAndCreateIfItDoesntExist(std::string name)
{
	// check if it exists already
	for (NPC& npc : s_NPCs) {
		if (Util::CaselessEquality(npc.m_name, name)) {
			return &npc;
		}
	}
	// if not create it
	return CreateNPC(name);
}

/*
NPC* DialogEngine::GetNPCPointerByFixedValue(int fixedValue)
{
	// Search for it and return pointer if you find it
	for (NPC& npc : s_NPCs) {
		if (npc.m_fixedValue == fixedValue) {
			return &npc;
		}
	}
	// Otherwise return null
	return nullptr;
}
*/
NPC* DialogEngine::GetNPCPointer(std::string name)
{
	// Search for it and return pointer if you find it
	for (NPC& npc : s_NPCs)
		if (Util::CaselessEquality(npc.m_name, name))
			return &npc;
	// Otherwise return null
	return nullptr;
}

/*
void DialogEngine::RegisterNPC(std::string name, int fixedValue)
{
	for (NPC& npc : s_NPCs)
		if (Util::CaselessEquality(npc.m_name, name)) {
			npc.m_fixedValue = fixedValue;
			return;
		}

	// If it doesn't already exist then u gotta create it.
	NPC npc;
	npc.m_name = name;
	npc.m_fixedValue = fixedValue;
	s_NPCs.push_back(npc);
}
*/
/*
void DialogEngine::RegisterItem(std::string name, int fixedValue)
{
	s_itemFixedValueMap.insert({ fixedValue, name });
}
*/
/*
void DialogEngine::PickedUpFusionItem(int fixedValue)
{
	if (s_itemFixedValueMap.find(fixedValue) == s_itemFixedValueMap.end()) {
		return;
	}
	else {
		std::string itemName = s_itemFixedValueMap[fixedValue];
		Inventory::GiveItem(itemName, 1);
	}
}*/

MyCondition DialogEngine::ConditionObjectFromString(std::string str)
{
	MyCondition condition;
	if (Util::StringContains(str, "==")) {

		condition.m_conditionName = Util::GetSubstringBeforeSubstring(str, "==");
		std::string conditionParameter = Util::GetSubstringAfterSubstring(str, "==");

		// Bool
		if (conditionParameter == "TRUE") {
			condition.m_requiredConditionBoolState = true;
			condition.m_ConditionType = ConditionType::BOOOL;
		}
		else if (conditionParameter == "FALSE") {
			condition.m_requiredConditionBoolState = false;
			condition.m_ConditionType = ConditionType::BOOOL;
		}
		// Quest requirements met
		else if (conditionParameter == "FULLFILLED") {
			condition.m_requiredConditionBoolState = true;
			condition.m_ConditionType = ConditionType::QUEST_REQUIREMENTS_MET;
		}
		else if (conditionParameter == "NOT_FULLFILLED") {
			condition.m_requiredConditionBoolState = false;
			condition.m_ConditionType = ConditionType::QUEST_REQUIREMENTS_MET;
		}
		// Item check							
		else if (conditionParameter == "HAVE_ITEM") {
			condition.m_ConditionType = ConditionType::HAVE_ITEM;
			condition.m_requiredConditionBoolState = true;
		}
		else if (conditionParameter == "NO_ITEM") {
			condition.m_ConditionType = ConditionType::HAVE_ITEM;
			condition.m_requiredConditionBoolState = false;
		}
		// Quset
		else if (conditionParameter == "ACTIVE") {
			condition.m_ConditionType = ConditionType::QUEST_ACTIVE;
			condition.m_requiredConditionBoolState = true;
		}
		else if (conditionParameter == "INACTIVE") {
			condition.m_ConditionType = ConditionType::QUEST_INACTIVE;
			condition.m_requiredConditionBoolState = true;
		}
		else if (conditionParameter == "COMPLETE" || conditionParameter == "COMPLETED") {
			condition.m_ConditionType = ConditionType::QUEST_COMPLETE;
			condition.m_requiredConditionBoolState = true;
		}
		else if (conditionParameter == "FAILED") {
			condition.m_ConditionType = ConditionType::QUEST_FAILED;
			condition.m_requiredConditionBoolState = true;
		}
		// Well if not then it's a float equality comparison
		else {
			//std::cout << "CONDQUEST: " << str << "\n";
			condition.m_ConditionType = ConditionType::FLOAT_EQUAL;
			condition.m_conditionComparisonValue = Util::StringToFloat(conditionParameter);
		}
	}
	// not equal
	else if (Util::StringContains(str, "!=")) {

		condition.m_conditionName = Util::GetSubstringBeforeSubstring(str, "!=");
		std::string conditionParameter = Util::GetSubstringAfterSubstring(str, "!=");
		// items
		if (conditionParameter == "HAVE_ITEM") {
			condition.m_ConditionType = ConditionType::HAVE_ITEM;
			condition.m_requiredConditionBoolState = false;
		}
		else if (conditionParameter == "NO_ITEM") {
			condition.m_ConditionType = ConditionType::HAVE_ITEM;
			condition.m_requiredConditionBoolState = true;
		}
		// Quset
		else if (conditionParameter == "ACTIVE") {
			condition.m_ConditionType = ConditionType::QUEST_ACTIVE;
			condition.m_requiredConditionBoolState = false;
		}
		else if (conditionParameter == "INACTIVE") {
			condition.m_ConditionType = ConditionType::QUEST_INACTIVE;
			condition.m_requiredConditionBoolState = false;
		}
		else if (conditionParameter == "COMPLETE" || conditionParameter == "COMPLETED") {
			condition.m_ConditionType = ConditionType::QUEST_COMPLETE;
			condition.m_requiredConditionBoolState = false;
		}
		else if (conditionParameter == "FAILED") {
			condition.m_ConditionType = ConditionType::QUEST_FAILED;
			condition.m_requiredConditionBoolState = false;
		}
		// floats. (it must be)
		else {
			condition.m_ConditionType = ConditionType::FLOAT_NOT_EQUAL;
			condition.m_conditionComparisonValue = Util::StringToFloat(Util::GetSubstringAfterSubstring(str, "!="));
		}
	}
	// this is all floats
	else if (Util::StringContains(str, "<=")) {

		condition.m_ConditionType = ConditionType::FLOAT_LESS_OR_EQUAL;
		condition.m_conditionName = Util::GetSubstringBeforeSubstring(str, "<=");
		condition.m_conditionComparisonValue = Util::StringToFloat(Util::GetSubstringAfterSubstring(str, "<="));
	}
	else if (Util::StringContains(str, ">=")) {

		condition.m_ConditionType = ConditionType::FLOAT_GREATER_OR_EQUAL;
		condition.m_conditionName = Util::GetSubstringBeforeSubstring(str, ">=");
		condition.m_conditionComparisonValue = Util::StringToFloat(Util::GetSubstringAfterSubstring(str, ">="));
	}
	else if (Util::StringContains(str, "<")) {

		condition.m_ConditionType = ConditionType::FLOAT_LESS;
		condition.m_conditionName = Util::GetSubstringBeforeSubstring(str, "<");
		condition.m_conditionComparisonValue = Util::StringToFloat(Util::GetSubstringAfterSubstring(str, "<"));
	}
	else if (Util::StringContains(str, ">")) {

		condition.m_ConditionType = ConditionType::FLOAT_GREATER;
		condition.m_conditionName = Util::GetSubstringBeforeSubstring(str, ">");
		condition.m_conditionComparisonValue = Util::StringToFloat(Util::GetSubstringAfterSubstring(str, ">"));
	}
	return condition;
}

/* THIS COULD BE IMPORTANT BUT FOR NOW DELETING */
bool DialogEngine::IsConditionListSatisfied(std::vector<MyCondition>& conidtionList)
{
	// Check if all conditions are met
	for (MyCondition& responseCondition : conidtionList)
	{
		// Bool conditions
		if (responseCondition.m_ConditionType == ConditionType::BOOOL)
		{
			//std::cout << "MADE IT HERE\n";
			//std::cout << "checking flag: [" << responseCondition.m_conditionName << "] with state " << responseCondition.m_requiredConditionBoolState << " and actual state is " << DialogEngine::GetGameFlagState(responseCondition.m_conditionName) << "\n";

			if (responseCondition.m_requiredConditionBoolState != DialogEngine::GetGameFlagState(responseCondition.m_conditionName))
				return false;
		}
		// Quest conditions
		/*else if (responseCondition.m_ConditionType == ConditionType::QUEST_REQUIREMENTS_MET)
		{
			if (responseCondition.m_requiredConditionBoolState != DialogEngine::AreQuestRequirementsFullfilled(responseCondition.m_conditionName))
				return false;
		}*/
		// Could be an item check
		else if (responseCondition.m_ConditionType == ConditionType::HAVE_ITEM)
		{
			//std::cout << "FOUND A HAVE_ITEM " << responseCondition.m_conditionName << " with state " << responseCondition.m_requiredConditionBoolState << " and actual state is " << Inventory::HasItem(responseCondition.m_conditionName) << "\n";
			if (responseCondition.m_requiredConditionBoolState != Inventory::HasItem(responseCondition.m_conditionName))
				//if (!DialogEngine::HasItem(responseCondition.m_conditionName))
				return false;
		}
		// Could be an quest check
		else if (responseCondition.m_ConditionType == ConditionType::QUEST_COMPLETE)
		{
			Quest* quest = GetQuestByName(responseCondition.m_conditionName);
			if (responseCondition.m_requiredConditionBoolState != (quest->m_questState == QuestState::COMPLETE))
				return false;
		}
		else if (responseCondition.m_ConditionType == ConditionType::QUEST_FAILED)
		{
			Quest* quest = GetQuestByName(responseCondition.m_conditionName);
			if (responseCondition.m_requiredConditionBoolState != (quest->m_questState == QuestState::FAILED))
				return false;
		}
		else if (responseCondition.m_ConditionType == ConditionType::QUEST_ACTIVE)
		{
			Quest* quest = GetQuestByName(responseCondition.m_conditionName);
			if (responseCondition.m_requiredConditionBoolState != (quest->m_questState == QuestState::ACTIVE))
				return false;
		}
		else if (responseCondition.m_ConditionType == ConditionType::QUEST_INACTIVE)
		{
			Quest* quest = GetQuestByName(responseCondition.m_conditionName);
			if (responseCondition.m_requiredConditionBoolState != (quest->m_questState == QuestState::INACTIVE))
				return false;
		}
		// Must be a value or item comparison
		else
		{
			std::string name = responseCondition.m_conditionName;
			ConditionType type = responseCondition.m_ConditionType;
			float value = responseCondition.m_conditionComparisonValue;

			if (!DialogEngine::EvaluateConditionalComparison(name, type, value)) {
				//std::cout << "FAILED CHECK: " << response.m_text << "\n";
				return false;
			}
		}
	}
	return true;
}

/*
int DialogEngine::GetQuestDialogIDFromNPCFixedValue(int fixedValue)
{
	// First you gotta get the NPC
	NPC* npc = GetNPCPointerByFixedValue(fixedValue);
	if (!npc)
		return -1;

	// Iterate over each quest and stop at the first one that passes the condition list
	for (NPCQuestData& questData : npc->m_quests)
	{
		Quest* quest = GetQuestByName(questData.m_questName);

		if (IsConditionListSatisfied(quest->m_conditions))
		{
			if (quest->m_questState == QuestState::ACTIVE && questData.m_questDialogIDs.active != -1)
				return questData.m_questDialogIDs.active;
			else if (quest->m_questState == QuestState::INACTIVE && questData.m_questDialogIDs.inactive != -1)
				return questData.m_questDialogIDs.inactive;
			else if (quest->m_questState == QuestState::FAILED && questData.m_questDialogIDs.failed != -1)
				return questData.m_questDialogIDs.failed;
			else if (quest->m_questState == QuestState::COMPLETE && questData.m_questDialogIDs.complete != -1)
				return questData.m_questDialogIDs.complete;
		}
	}
	std::cout << "NONE PASSED\n";
	return -1;
}
*/



/*
int DialogEngine::GetNextQuestDialogIDFromNPCName(std::string npcName)
{
	for (NPC& npc : s_NPCs) {
		if (npc.m_name == npcName)
		{
			// Iterate over each quest and stop at the first one that passes the condition list
			for (NPCQuestData& questData : npc.m_quests)
			{
				Quest* quest = GetQuestByName(questData.m_questName);

				if (IsConditionListSatisfied(quest->m_conditions))
				{
					if (quest->m_questState == QuestState::ACTIVE && questData.m_questDialogIDs.active != -1)
						return questData.m_questDialogIDs.active;
					else if (quest->m_questState == QuestState::INACTIVE && questData.m_questDialogIDs.inactive != -1)
						return questData.m_questDialogIDs.inactive;
					else if (quest->m_questState == QuestState::FAILED && questData.m_questDialogIDs.failed != -1)
						return questData.m_questDialogIDs.failed;
					else if (quest->m_questState == QuestState::COMPLETE && questData.m_questDialogIDs.complete != -1)
						return questData.m_questDialogIDs.complete;
				}
			}
			std::cout << "NONE PASSED\n";
			return -1;
		}
	}
	// Otherwise return nothing
	return -1;
}*/
/*
void DialogEngine::DisplayStandardFromNPCName(std::string npcName)
{
	// First you gotta get the NPC
	NPC* npc = GetNPCPointer(npcName);
	if (!npc)
		return;

	// Now iterate over the dialog entries and find the first that satisfies all conditions
	for (DialogEntry& dialogEntry : s_dialogEntries)
	{
		// Find matching name
		if (Util::CaselessEquality(dialogEntry.m_npcTriggerName, npc->m_name))
		{
			//std::cout << "dialog: " << dialogEntry.m_ID << " " << dialogEntry.m_conditions.size() << " conditions" << "\n";

			// BAIL if condition not met
			for (MyCondition& responseCondition : dialogEntry.m_conditions)
			{
				// Bool conditions
				if (responseCondition.m_ConditionType == ConditionType::BOOOL) {


					//	std::cout << "bool: " << dialogEntry.m_ID << "\n";

					if (responseCondition.m_requiredConditionBoolState != DialogEngine::GetGameFlagState(responseCondition.m_conditionName))
						goto loop_exit;
				}
				// Quest conditions
				else if (responseCondition.m_ConditionType == ConditionType::QUEST_REQUIREMENTS_MET) {
					if (responseCondition.m_requiredConditionBoolState != DialogEngine::AreQuestRequirementsFullfilled(responseCondition.m_conditionName))
						goto loop_exit;
				}
				// Could be an item check
				else if (responseCondition.m_ConditionType == ConditionType::HAVE_ITEM) {
					if (responseCondition.m_requiredConditionBoolState != Inventory::HasItem(responseCondition.m_conditionName))
						goto loop_exit;
				}
				// Must be a value or item comparison
				else
				{
					std::string name = responseCondition.m_conditionName;
					ConditionType type = responseCondition.m_ConditionType;
					float value = responseCondition.m_conditionComparisonValue;

					if (!DialogEngine::EvaluateConditionalComparison(name, type, value))
						goto loop_exit;
				}
			}
			// It's good then
			SetCurrentDialogByID(dialogEntry.m_ID);
			return;
		}
	loop_exit:;
	}
}

*/
void DialogEngine::CheckNPCForInworldQuestDialog(std::string npcName)
{
	// First you gotta get the NPC
	NPC* npc = GetNPCPointer(npcName);
	if (!npc)
		return;

	// Iterate over each quest and stop at the first one that passes the condition list
	for (NPCQuestData& questData : npc->m_quests)
	{
		Quest* quest = GetQuestByName(questData.m_questName);

		if (quest)
		{
			if (quest->m_questState == QuestState::ACTIVE && questData.m_questInWorldDialogText.active != "") {
				npc->m_inWorldDialogString = questData.m_questInWorldDialogText.active;
				npc->m_inWorldDialogTextTimer = s_textDuration;
				return;
			}
			else if (quest->m_questState == QuestState::INACTIVE && questData.m_questInWorldDialogText.inactive != "") {
				npc->m_inWorldDialogString = questData.m_questInWorldDialogText.inactive;
				npc->m_inWorldDialogTextTimer = s_textDuration;
				return;
			}
			else if (quest->m_questState == QuestState::FAILED && questData.m_questInWorldDialogText.failed != "") {
				npc->m_inWorldDialogString = questData.m_questInWorldDialogText.failed;
				npc->m_inWorldDialogTextTimer = s_textDuration;
				return;
			}
			else if (quest->m_questState == QuestState::COMPLETE && questData.m_questInWorldDialogText.complete != "") {
				npc->m_inWorldDialogString = questData.m_questInWorldDialogText.complete;
				npc->m_inWorldDialogTextTimer = s_textDuration;
				return;
			}
		}
	}
	return;
}


void DialogEngine::CheckNPCForStandardDialogAndQuests(std::string npcName)
{
	/////
	// Search for standard dialog first
	/////

	// Iterate over the dialog entries and find the first that satisfies all conditions
	for (DialogEntry& dialogEntry : s_dialogEntries)
	{
		if (Util::CaselessEquality(dialogEntry.m_npcTriggerName, npcName))
		{
			for (MyCondition& responseCondition : dialogEntry.m_conditions) {
				// Bool conditions
				if (responseCondition.m_ConditionType == ConditionType::BOOOL)
				{
					if (responseCondition.m_requiredConditionBoolState != DialogEngine::GetGameFlagState(responseCondition.m_conditionName))
						goto loop_exit;
				}
				// Quest conditions
				/*else if (responseCondition.m_ConditionType == ConditionType::QUEST_REQUIREMENTS_MET) {
					if (responseCondition.m_requiredConditionBoolState != DialogEngine::AreQuestRequirementsFullfilled(responseCondition.m_conditionName))
						goto loop_exit;
				}*/
				// Could be an item check
				else if (responseCondition.m_ConditionType == ConditionType::HAVE_ITEM) {
					if (responseCondition.m_requiredConditionBoolState != Inventory::HasItem(responseCondition.m_conditionName))
						goto loop_exit;
				}
				// Must be a value or item comparison
				else
				{
					std::string name = responseCondition.m_conditionName;
					ConditionType type = responseCondition.m_ConditionType;
					float value = responseCondition.m_conditionComparisonValue;

					if (!DialogEngine::EvaluateConditionalComparison(name, type, value))
						goto loop_exit;
				}
			}
			// It's good then
			SetCurrentDialogByID(dialogEntry.m_ID);
			return;
		}
	loop_exit:;
	}

	/////
	// now check for quests
	/////

	for (NPC& npc : s_NPCs) {
		if (npc.m_name == npcName)
		{
			// Iterate over each quest and stop at the first one that passes the condition list
			for (NPCQuestData& questData : npc.m_quests)
			{
				Quest* quest = GetQuestByName(questData.m_questName);

				//if (IsConditionListSatisfied(quest->m_conditions))
				{
					if (quest->m_questState == QuestState::ACTIVE && questData.m_questDialogIDs.active != -1) {
						SetCurrentDialogByID(questData.m_questDialogIDs.active);
						return;
					}
					else if (quest->m_questState == QuestState::INACTIVE && questData.m_questDialogIDs.inactive != -1) {
						SetCurrentDialogByID(questData.m_questDialogIDs.inactive);
						return;
					}
					else if (quest->m_questState == QuestState::FAILED && questData.m_questDialogIDs.failed != -1) {
						SetCurrentDialogByID(questData.m_questDialogIDs.failed);
						return;
					}
					else if (quest->m_questState == QuestState::COMPLETE && questData.m_questDialogIDs.complete != -1) {
						SetCurrentDialogByID(questData.m_questDialogIDs.complete);
						return;
					}
				}
			}
		}
	}
}

//std::string DialogEngine::GetRandomNPCInWorldDialogFromNPCName(std::string npcName)
void DialogEngine::CheckNPCForInWorldDialog(std::string npcName)
{
	// First you gotta get the NPC
	NPC* npc = GetNPCPointer(npcName);

	if (npc)
	{
		// Find a random in world dialog text if there is any
		if (npc->m_inWorldDialogReplies.size() > 1) {

			npc->m_inWorldDialogString = npc->m_inWorldDialogReplies[0]; // store it
			npc->m_inWorldDialogReplies.erase(npc->m_inWorldDialogReplies.begin() + 0); // erase it
			int randomIndex = Util::RandomInt(1, (int)npc->m_inWorldDialogReplies.size()); // get random index
			npc->m_inWorldDialogReplies.insert(npc->m_inWorldDialogReplies.begin() + randomIndex, npc->m_inWorldDialogString); // reinsert it
			npc->m_inWorldDialogTextTimer = s_textDuration;


			//	Util::Log("timer: " + std::to_string(npc->m_inWorldDialogTextTimer));
			//	Util::Log("text:  " + npc->m_inWorldDialogString);
			return;// npc->m_inWorldDialogString; // return it


		}
		else if (npc->m_inWorldDialogReplies.size() == 1)
		{
			npc->m_inWorldDialogString = npc->m_inWorldDialogReplies[0]; // store it
			npc->m_inWorldDialogTextTimer = s_textDuration;
			//	Util::Log("no fucking text to display");
			return;// npc->m_inWorldDialogString; // return it
		}
	}
	return;// "";
}


std::string DialogEngine::GetNPCNameByIndex(int index)
{
	if (index < 0 || index >= (int)s_NPCs.size())
		return "NPC index out of range";
	else
		return s_NPCs[index].m_name;;
}

Quest* DialogEngine::GetQuestByName(std::string name)
{
	for (Quest& quest : s_Quests)
		if (Util::CaselessEquality(quest.m_name, name))
			return &quest;

	return nullptr;
}


/*
bool DialogEngine::AreQuestRequirementsFullfilled(std::string query)
{
	for (Quest& quest : s_Quests)
		if (quest.m_name == query)
			return (quest.m_requirementsFullfiled);
	return false;

}*/

bool DialogEngine::IsQuestCompleted(std::string query)
{
	for (Quest& quest : s_Quests)
		if (quest.m_name == query)
			return (quest.m_questState == QuestState::COMPLETE);
	return false;
}

bool DialogEngine::IsQuestFailed(std::string query)
{
	for (Quest& quest : s_Quests)
		if (quest.m_name == query)
			return (quest.m_questState == QuestState::FAILED);
	return false;
}

bool DialogEngine::WasIfAnyQuestWasJustFailed()
{
	if (s_wasAnyQuestJustFailed) {
		s_wasAnyQuestJustFailed = false;
		return true;
	}
	else
		return false;
}



///////////////////
//               //
//  F L O A T S  //
//               //
///////////////////


void DialogEngine::SetGameFloat(std::string name, float value)
{
	// check if float exists
	for (GameFloat& gameValue : s_gameFloats) {

		if (Util::CaselessEquality(gameValue.m_name, name)) {
			gameValue.SetTo(value);
			return;
		}
	}
	// Otherwise create it
	s_gameFloats.push_back(GameFloat(name, value));
}

bool DialogEngine::DoesFlagExist(std::string name)
{
	for (GameFlag& flag : s_gameFlags)
		if (Util::CaselessEquality(flag.m_name, name))
			return true;
	return false;
}

void DialogEngine::SetGameFloatMin(std::string name, float value)
{
	for (GameFloat& gameValue : s_gameFloats)
		if (Util::CaselessEquality(gameValue.m_name, name)) {
			gameValue.SetMin(value);
			return;
		}
}

void DialogEngine::SetGameFloatMax(std::string name, float value)
{
	for (GameFloat& gameValue : s_gameFloats)
		if (Util::CaselessEquality(gameValue.m_name, name)) {
			gameValue.SetMax(value);
			return;
		}
}

void DialogEngine::AddToGameFloat(std::string name, float value)
{
	for (GameFloat& gameValue : s_gameFloats)
		if (Util::CaselessEquality(gameValue.m_name, name)) {
			gameValue.m_value += value;
			return;
		}
}

void DialogEngine::SubractFromGameFloat(std::string name, float value)
{
	for (GameFloat& gameValue : s_gameFloats)
		if (Util::CaselessEquality(gameValue.m_name, name)) {
			gameValue.m_value -= value;
			return;
		}
}


float DialogEngine::GetGameFloat(std::string name)
{
	// Look for the fucking flag
	for (GameFloat& gamevalue : s_gameFloats) {
		if (Util::CaselessEquality(gamevalue.m_name, name)) {
			return gamevalue.m_value;
		}
	}
	// returns negative nine nine nine nine nine if flag not found
	return -99999;
}


bool DialogEngine::GameFloatExists(std::string name)
{
	for (GameFloat& value : s_gameFloats)
		if (Util::CaselessEquality(value.m_name, name))
			return true;
	return false;
}

std::string DialogEngine::GetGameFloatNameByIndex(int index)
{
	if (index < 0 || index >= (int)s_gameFloats.size())
		return "out_of_range";

	return s_gameFloats[index].m_name;
}

/////////////////
//             //
//  F L A G S  //
//             //
/////////////////


void DialogEngine::SetGameFlag(std::string flagName, bool state)
{
	flagName = Util::ToUppercase(flagName);

	// check if flag exists
	for (GameFlag& gameFlag : s_gameFlags) {

		//  if (TCharCompare(gameFlag.m_name.c_str(), flagName)) {
		if (gameFlag.m_name == flagName) {
			gameFlag.m_state = state;
			return;
		}
	}
	// Otherwise create it
	s_gameFlags.push_back(GameFlag(flagName, state));
}

bool DialogEngine::GetGameFlagState(std::string flagName)
{
	// Look for the fucking flag
	for (GameFlag& gameFlag : s_gameFlags) {
		if (gameFlag.m_name == flagName) {
			return gameFlag.m_state;
		}
	}
	// returns false if flag not found
	return false;
}

void DialogEngine::ToggleGameFlag(std::string flagName)
{
	// Look for the fucking flag
	for (GameFlag& gameFlag : s_gameFlags) {
		if (gameFlag.m_name == flagName) {
			gameFlag.Toggle();
		}
	}
}

std::string DialogEngine::GetGameFlagNameByIndex(int index)
{
	if (index < 0 || index >= (int)s_gameFlags.size())
		return "out_of_range";

	return s_gameFlags[index].m_name;
}



void DialogEngine::SaveString(rapidjson::Value* object, std::string elementName, std::string string, rapidjson::Document::AllocatorType& allocator)
{
	rapidjson::Value name(elementName.c_str(), allocator);
	rapidjson::Value value(rapidjson::kObjectType);
	value.SetString(string.c_str(), static_cast<rapidjson::SizeType>(string.length()), allocator);
	object->AddMember(name, value, allocator);
}

void DialogEngine::SaveFloat(rapidjson::Value* object, std::string elementName, float number, rapidjson::Document::AllocatorType& allocator)
{
	rapidjson::Value name(elementName.c_str(), allocator);
	rapidjson::Value value(rapidjson::kObjectType);
	value.SetFloat(number);
	object->AddMember(name, value, allocator);
}

void DialogEngine::SaveInt(rapidjson::Value* object, std::string elementName, int number, rapidjson::Document::AllocatorType& allocator)
{
	rapidjson::Value name(elementName.c_str(), allocator);
	rapidjson::Value value(rapidjson::kObjectType);
	value.SetInt(number);
	object->AddMember(name, value, allocator);
}