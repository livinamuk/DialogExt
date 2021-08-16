#pragma once
#include "Header.h"

struct QuestDialogIDs
{
    int active = -1;
    int inactive = -1;
    int complete = -1;
    int failed = -1;
    int expTooLow = -1;
};

struct QuestInWorldDialogText
{
    std::string active;
    std::string inactive;
    std::string complete;
    std::string failed;
    std::string expTooLow;
};

struct NPCQuestData {
    std::string m_questName = "UNDEFINED";
    QuestDialogIDs m_questDialogIDs;
    QuestInWorldDialogText m_questInWorldDialogText;
};

class NPC {
public:
    // Fields
    std::string m_name = "UNDEFINED";

    //bool m_HasQuest = false;

    // quest shit
    std::vector<NPCQuestData> m_quests;

    int m_dialogID = -1;
    std::vector<std::string> m_inWorldDialogReplies;

    std::string m_inWorldDialogString;
    int m_inWorldDialogTextTimer = -1;
    int m_fixedValue = -1;
};