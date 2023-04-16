#ifndef STEAM_ACHIEVEMENTS_H
#define STEAM_ACHIEVEMENTS_H

#include <steamtypes.h>
#include <steam_api.h>
#include <steam_api_common.h>

#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }
struct Achievement_t
{
	int m_eAchievementID;
	const char* m_pchAchievementID;
	char m_rgchName[128];
	char m_rgchDescription[256];
	bool m_bAchieved;
	int m_iIconImage;
};

class CSteamAchievements
{
private:
	int64 m_iAppID; // Our current AppID
	Achievement_t* m_pAchievements; // Achievements data
	int m_iNumAchievements; // The number of Achievements
	bool m_bInitialized; // Have we called Request stats and received the callback?

public:
	CSteamAchievements(Achievement_t* Achievements, int NumAchievements);
	~CSteamAchievements();

	bool RequestStats();
	bool SetAchievement(const char* ID);

	STEAM_CALLBACK(CSteamAchievements, OnUserStatsReceived, UserStatsReceived_t, m_CallbackUserStatsReceived);
	STEAM_CALLBACK(CSteamAchievements, OnUserStatsStored, UserStatsStored_t, m_CallbackUserStatsStored);
	STEAM_CALLBACK(CSteamAchievements, OnAchievementStored,	UserAchievementStored_t, m_CallbackAchievementStored);
};

enum EAchievements
{
	ACH_WIN_ONE_GAME = 0
};

inline Achievement_t gAchievements[]
{
	_ACH_ID(ACH_WIN_ONE_GAME, "Winner")
};

inline CSteamAchievements* gSteamAchievements;

bool InitializeSteamAPI();
void CleanUpSteamResources();
#endif