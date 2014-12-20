#ifndef __INC_METIN_II_GAME_CSkillManager_H__
#define __INC_METIN_II_GAME_CSkillManager_H__

#include "libpoly/Poly.h"

enum ESkillFlags
{
	SKILL_FLAG_ATTACK			= (1 << 0),	// °ш°Э ±вјъ
	SKILL_FLAG_USE_MELEE_DAMAGE		= (1 << 1),	// ±вє» №Рё® Её°ЭДЎё¦ b °ЄАё·О »зїл
	SKILL_FLAG_COMPUTE_ATTGRADE		= (1 << 2),	// °ш°Эµо±ЮА» °и»кЗСґЩ
	SKILL_FLAG_SELFONLY			= (1 << 3),	// АЪЅЕїЎ°Фёё ѕµ јц АЦАЅ
	SKILL_FLAG_USE_MAGIC_DAMAGE		= (1 << 4),	// ±вє» ё¶№э Её°ЭДЎё¦ b °ЄАё·О »зїл
	SKILL_FLAG_USE_HP_AS_COST		= (1 << 5),	// HPё¦ SPґлЅЕ ѕґґЩ
	SKILL_FLAG_COMPUTE_MAGIC_DAMAGE	= (1 << 6),
	SKILL_FLAG_SPLASH			= (1 << 7),
	SKILL_FLAG_GIVE_PENALTY		= (1 << 8),	// ѕІ°ніЄёй АбЅГµїѕИ(3ГК) 2№и µҐ№МБцё¦ №ЮґВґЩ.
	SKILL_FLAG_USE_ARROW_DAMAGE		= (1 << 9),	// ±вє» И­»м Её°ЭДЎё¦ b °ЄАё·О »зїл
	SKILL_FLAG_PENETRATE		= (1 << 10),	// №жѕо№«ЅГ
	SKILL_FLAG_IGNORE_TARGET_RATING	= (1 << 11),	// »уґл ·№АМЖГ №«ЅГ
	SKILL_FLAG_SLOW			= (1 << 12),	// ЅЅ·Оїм °ш°Э
	SKILL_FLAG_STUN			= (1 << 13),	// ЅєЕП °ш°Э
	SKILL_FLAG_HP_ABSORB		= (1 << 14),	// HP Инјц
	SKILL_FLAG_SP_ABSORB		= (1 << 15),	// SP Инјц
	SKILL_FLAG_FIRE_CONT		= (1 << 16),	// FIRE БцјУ µҐ№МБц
	SKILL_FLAG_REMOVE_BAD_AFFECT	= (1 << 17),	// іЄ»ЫИї°ъ Б¦°Е
	SKILL_FLAG_REMOVE_GOOD_AFFECT	= (1 << 18),	// іЄ»ЫИї°ъ Б¦°Е
	SKILL_FLAG_CRUSH			= (1 << 19),	// »уґл№жА» іЇёІ
	SKILL_FLAG_POISON			= (1 << 20),	// µ¶ °ш°Э
	SKILL_FLAG_TOGGLE			= (1 << 21),	// Ед±Ы
	SKILL_FLAG_DISABLE_BY_POINT_UP	= (1 << 22),	// Впѕој­ їГё± јц ѕшґЩ.
	SKILL_FLAG_CRUSH_LONG		= (1 << 23),	// »уґл№жА» ёЦё® іЇёІ
	SKILL_FLAG_WIND		= (1 << 24),	// №Щ¶ч јУјє 
	SKILL_FLAG_ELEC		= (1 << 25),	// Аь±в јУјє
	SKILL_FLAG_FIRE		= (1 << 26),	// єТ јУјє
};

enum
{
	SKILL_PENALTY_DURATION = 3,
	SKILL_TYPE_HORSE = 5,
};

enum ESkillIndexes
{
	SKILL_RESERVED = 0,

	// №«»з Аь»з °иї­
	// A
	SKILL_SAMYEON = 1,		// »пї¬Вь(јј№шєЈ±в)
	SKILL_PALBANG,		// ЖИ№жЗіїм
	// S
	SKILL_JEONGWI,		// Аь±НИҐ
	SKILL_GEOMKYUNG,		// °Л°ж
	SKILL_TANHWAN,		// ЕєИЇ°Э

	// №«»з ±в°ш °иї­
	// A
	SKILL_GIGONGCHAM = 16,	// ±в°шВь
	SKILL_GYOKSAN,		// °Э»кЕёїм
	SKILL_DAEJINGAK,		// ґлБш°ў
	// S
	SKILL_CHUNKEON,		// Гµ±ЩГЯ
	SKILL_GEOMPUNG,		// °ЛЗі

	// АЪ°ґ ѕП»м °иї­
	// A
	SKILL_AMSEOP = 31,		// ѕПЅА 
	SKILL_GUNGSIN,		// ±ГЅЕЕєїµ 
	SKILL_CHARYUN,		// Вч·ы»м 
	// S
	SKILL_EUNHYUNG,		// АєЗь№э 
	SKILL_SANGONG,		// »к°шєР

	// АЪ°ґ ±Гјц °иї­
	// A
	SKILL_YEONSA = 46,		// ї¬»з 
	SKILL_KWANKYEOK,		// °ь°Эјъ 
	SKILL_HWAJO,		// И­Б¶ЖД
	// S
	SKILL_GYEONGGONG,		// °ж°шјъ 
	SKILL_GIGUNG,		// ±в±Г

	// јц¶у °Л
	// A
	SKILL_SWAERYUNG = 61,	// јв·ЙБц 
	SKILL_YONGKWON,		// їл±ЗЖД 
	// S
	SKILL_GWIGEOM,		// ±Н°Л
	SKILL_TERROR,		// °шЖч 
	SKILL_JUMAGAP,		// БЦё¶°© 
	SKILL_PABEOB,		// ЖД№эјъ

	// јц¶у ё¶№э
	// A
	SKILL_MARYUNG = 76,		// ё¶·Й 
	SKILL_HWAYEOMPOK,		// И­ї°Жш 
	SKILL_MUYEONG,		// №«їµБш 
	// S
	SKILL_MANASHILED,		// ИжЅЕјцИЈ
	SKILL_TUSOK,		// ЕхјУё¶·Й 
	SKILL_MAHWAN,		// ё¶ИЇ°Э

	// №«ґз їлЅЕ
	// A
	SKILL_BIPABU = 91,
	SKILL_YONGBI,		// їлєс±¤»зЖД 
	SKILL_PAERYONG,		// ЖР·жіЄЗС№«
	// S
	//SKILL_BUDONG,		// єОµї№ЪєО 
	SKILL_HOSIN,		// ИЈЅЕ 
	SKILL_REFLECT,		// єёИЈ
	SKILL_GICHEON,		// ±вГµґл°ш

	// №«ґз іъЅЕ
	// A
	SKILL_NOEJEON = 106,	// іъАь·Й 
	SKILL_BYEURAK,		// є­¶ф 
	SKILL_CHAIN,		// ГјАО¶уАМЖ®ґЧ 
	// S
	SKILL_JEONGEOP,		// Б¤ѕчАО 
	SKILL_KWAESOK,		// АМµїјУµµѕч
	SKILL_JEUNGRYEOK,		// Бх·Вјъ

	// °шЕл ЅєЕі
	// 7
	SKILL_7_A_ANTI_TANHWAN = 112,
	SKILL_7_B_ANTI_AMSEOP,
	SKILL_7_C_ANTI_SWAERYUNG,
	SKILL_7_D_ANTI_YONGBI,

	// 8
	SKILL_8_A_ANTI_GIGONGCHAM,
	SKILL_8_B_ANTI_YEONSA,
	SKILL_8_C_ANTI_MAHWAN,
	SKILL_8_D_ANTI_BYEURAK,

	// єёБ¶ ЅєЕі

	SKILL_LEADERSHIP = 121,	// ЕлјЦ·В
	SKILL_COMBO	= 122,		// ї¬°и±в
	SKILL_CREATE = 123,		// Б¦Б¶
	SKILL_MINING = 124,

	SKILL_LANGUAGE1 = 126,	// ЅЕјцѕо ґЙ·В
	SKILL_LANGUAGE2 = 127,	// ГµБ¶ѕо ґЙ·В
	SKILL_LANGUAGE3 = 128,	// Бшілѕо ґЙ·В
	SKILL_POLYMORPH = 129,	// µР°©

	SKILL_HORSE			= 130,	// ЅВё¶ ЅєЕі
	SKILL_HORSE_SUMMON		= 131,	// ё» јТИЇ ЅєЕі
	SKILL_HORSE_WILDATTACK	= 137,	// і­№«
	SKILL_HORSE_CHARGE		= 138,	// µ№°Э
	SKILL_HORSE_ESCAPE		= 139,	// Е»Гв
	SKILL_HORSE_WILDATTACK_RANGE = 140,	// і­№«(И°)

	SKILL_ADD_HP	=	141,			// БхЗч
	SKILL_RESIST_PENETRATE	=	142,	// Г¶Ел

	GUILD_SKILL_START = 151,
	GUILD_SKILL_EYE = 151,
	GUILD_SKILL_BLOOD = 152,
	GUILD_SKILL_BLESS = 153,
	GUILD_SKILL_SEONGHWI = 154,
	GUILD_SKILL_ACCEL = 155,
	GUILD_SKILL_BUNNO = 156,
	GUILD_SKILL_JUMUN = 157,
	GUILD_SKILL_TELEPORT = 158,
	GUILD_SKILL_DOOR = 159,
	GUILD_SKILL_END = 162,

	GUILD_SKILL_COUNT = GUILD_SKILL_END - GUILD_SKILL_START + 1,

};

class CSkillProto
{
	public:
		char	szName[64];
		DWORD	dwVnum;			// №шИЈ

		DWORD	dwType;			// 0: АьБчѕч, 1: №«»з, 2: АЪ°ґ, 3: јц¶у, 4: №«ґз
		BYTE	bMaxLevel;		// ГЦґл јц·Гµµ
		BYTE	bLevelLimit;		// ·№є§Б¦ЗС
		int	iSplashRange;		// ЅєЗГ·ЎЅ¬ °Её® Б¦ЗС

		BYTE	bPointOn;		// ѕоµрїЎ °б°ъ°ЄА» Аыїл ЅГЕ°ґВ°Ў? (Её°ЭДЎ, MAX HP, HP REGEN µоµоµо)
		CPoly	kPointPoly;		// °б°ъ°Є ёёµеґВ °шЅД

		CPoly	kSPCostPoly;		// »зїл SP °шЅД
		CPoly	kDurationPoly;		// БцјУ ЅГ°Ј °шЅД
		CPoly	kDurationSPCostPoly;	// БцјУ SP °шЅД
		CPoly	kCooldownPoly;		// ДрґЩїо ЅГ°Ј °шЅД
		CPoly	kMasterBonusPoly;	// ё¶ЅєЕНАП ¶§ єёіКЅє °шЅД
		CPoly	kSplashAroundDamageAdjustPoly;	// ЅєЗГ·ЎЅ¬ °ш°ЭАП °жїм БЦА§ АыїЎ°Ф АФИчґВ µҐ№МБц °ЁјТ єсАІ

		DWORD	dwFlag;			// ЅєЕіїЙјЗ
		DWORD	dwAffectFlag;		// ЅєЕіїЎ ёВАє °жїм АыїлµЗґВ Affect

		BYTE	bLevelStep;		// ЗС№шїЎ їГё®ґВµҐ ЗКїдЗС ЅєЕі ЖчАОЖ® јц
		DWORD	preSkillVnum;		// №иїмґВµҐ ЗКїдЗС АМАьїЎ №иїцѕЯЗТ ЅєЕі
		BYTE	preSkillLevel;		// АМАьїЎ №иїцѕЯЗТ ЅєЕіАЗ ·№є§

		long	lMaxHit;

		BYTE	bSkillAttrType;

		// 2Вч Аыїл
		BYTE	bPointOn2;		
		CPoly	kPointPoly2;		
		CPoly	kDurationPoly2;		
		DWORD	dwFlag2;			
		DWORD	dwAffectFlag2;		

		DWORD   dwTargetRange;

		bool	IsChargeSkill()
		{
			return dwVnum == SKILL_TANHWAN || dwVnum == SKILL_HORSE_CHARGE; 
		}

		// 3Вч Аыїл
		BYTE bPointOn3;
		CPoly kPointPoly3;
		CPoly kDurationPoly3;

		CPoly kGrandMasterAddSPCostPoly;

		void SetPointVar(const std::string& strName, double dVar);
		void SetDurationVar(const std::string& strName, double dVar);
		void SetSPCostVar(const std::string& strName, double dVar);
};

typedef std::map<DWORD, CSkillProto *> SkillProtoMap;

class CSkillManager : public singleton<CSkillManager>
{
	public:
		CSkillManager();
		virtual ~CSkillManager();

		bool Initialize(TSkillTable * pTab, int iSize);
		CSkillProto * Get(DWORD dwVnum);
		CSkillProto * Get(const char * c_pszSkillName);

	protected:
		SkillProtoMap m_map_pkSkillProto;
};

#endif
