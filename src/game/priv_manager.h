#ifndef __PRIV_MANAGER_H
#define __PRIV_MANAGER_H

/// ±жµе єёіКЅє µҐАМЕН
struct SPrivGuildData
{
	int		value;		///< єёіКЅє јцДЎ
	time_t	end_time_sec;	///< БцјУ ЅГ°Ј
};

typedef std::map<DWORD, int> PrivCharMap;
typedef std::map<DWORD, SPrivGuildData> PrivGuildMap;

/**
 * @version 05/06/08	Bang2ni - Guild privilege °ь·Г ЗФјц БцјУ ЅГ°Ј ГЯ°Ў
 * 			          RequestGiveGuildPriv, GiveGuildPriv ЗФјц ЗБ·ОЕдЕёАЩ јцБ¤
 * 			          m_aPrivGuild ЕёАЩ јцБ¤
 * 			          ±ёБ¶Гј SPrivGuildData, ёв№ц ЗФјц GetPrivByGuildEx ГЯ°Ў
 */
class CPrivManager : public singleton<CPrivManager>
{
	public:
		CPrivManager();

		void RequestGiveGuildPriv(DWORD guild_id, BYTE type, int value, time_t dur_time_sec);
		void RequestGiveEmpirePriv(BYTE empire, BYTE type, int value, time_t dur_time_sec);
		void RequestGiveCharacterPriv(DWORD pid, BYTE type, int value);

		void GiveGuildPriv(DWORD guild_id, BYTE type, int value, BYTE bLog, time_t end_time_sec);
		void GiveEmpirePriv(BYTE empire, BYTE type, int value, BYTE bLog, time_t end_time_sec);
		void GiveCharacterPriv(DWORD pid, BYTE type, int value, BYTE bLog);

		void RemoveGuildPriv(DWORD guild_id, BYTE type);
		void RemoveEmpirePriv(BYTE empire, BYTE type);
		void RemoveCharacterPriv(DWORD pid, BYTE type);

		int GetPriv(LPCHARACTER ch, BYTE type);
		int GetPrivByEmpire(BYTE bEmpire, BYTE type);
		int GetPrivByGuild(DWORD guild_id, BYTE type);
		int GetPrivByCharacter(DWORD pid, BYTE type);

	public:
		struct SPrivEmpireData
		{
			int m_value;
			time_t m_end_time_sec;
		};

		SPrivEmpireData* GetPrivByEmpireEx(BYTE bEmpire, BYTE type);

		/// ±жµе єёіКЅє µҐАМЕНё¦ ѕтѕоїВґЩ.
		/**
		 * @param [in]	dwGuildID ѕтѕоїГ ±жµеАЗ ID
		 * @param [in]	byType єёіКЅє ЕёАЩ
		 * @return	ґл»у ±жµеАЗ ±жµе єёіКЅє µҐАМЕНАЗ ЖчАОЕН, ЗШґзЗПґВ єёіКЅє ЕёАЩ°ъ ±жµеАЗ ID їЎ ґлЗШ єёіКЅє µҐАМЕН°Ў ѕшА» °жїм NULL
		 */
		const SPrivGuildData*	GetPrivByGuildEx( DWORD dwGuildID, BYTE byType ) const;

	private:
		SPrivEmpireData m_aakPrivEmpireData[MAX_PRIV_NUM][EMPIRE_MAX_NUM];
		PrivGuildMap m_aPrivGuild[MAX_PRIV_NUM];
		PrivCharMap m_aPrivChar[MAX_PRIV_NUM];
};
#endif
