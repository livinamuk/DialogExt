
#include "GameFloat.h"
#include "Quest.h"

/*
void Quest::CheckRequirements(std::vector<GameFlag>& engineFlags, std::vector<GameItem>& engineItems)
{
	// First reset to false. Because player could sell item or put it in inventory or who knows. Gotta allow.
	m_requirementsFullfiled = false;

	std::cout << "     CHECKING " << this->m_name << "\n";
	std::cout << "     " << m_requiredFlags.size() << "\n";
	std::cout << "     " << m_requiredItems.size() << "\n";

	// Check if the quest requirment flag states match the corresponding flags in the engine.
	// By looping over every frag, checking for name equality, and comparing states.
	for (GameFlag& questFlag : m_requiredFlags)
	{
		// Does the flag even exist within the engine? If not then it's a fail.
		bool found = false;
		for (GameFlag& engineFlag : engineFlags)
			if (questFlag.m_name == engineFlag.m_name)
				found = true;

		// Otherwise find it, and compare bools
		for (GameFlag& engineFlag : engineFlags)
			if (questFlag.m_name == engineFlag.m_name && questFlag.m_state != engineFlag.m_state)
				return;
	}

	// Check required items too
	for (GameItem& questItem : m_requiredItems)
	{
		bool found = false;
		for (GameItem& engineItem : engineItems)
			if (questItem.m_name == engineItem.m_name)
				found = true;

		// Bail if you never found the item
		if (!found)
			return;
	}

	// If you made it here then all requirments are met
	m_requirementsFullfiled = true;
}
*/

std::string Quest::GetStateAsString()
{
	if (m_questState == QuestState::ACTIVE) return "ACTIVE";
	if (m_questState == QuestState::INACTIVE) return "INACTIVE";
	if (m_questState == QuestState::COMPLETE) return "COMPLETE";
	if (m_questState == QuestState::FAILED) return "FAILED";
	if (m_questState == QuestState::UNDEFINED) return "UNDEFINED";
}
