#ifndef __INC_AFFECT_H
#define __INC_AFFECT_H

class CAffect
{
	public:
		DWORD	dwType;
		BYTE    bApplyOn;
		long    lApplyValue;
		DWORD   dwFlag;
		long	lDuration;
		long	lSPCost;

		static CAffect* Acquire();
		static void Release(CAffect* p);
};

enum EAffectTypes
{
	AFFECT_NONE,

	AFFECT_MOV_SPEED		= 200,
	AFFECT_ATT_SPEED,
	AFFECT_ATT_GRADE,
	AFFECT_INVISIBILITY,
	AFFECT_STR,
	AFFECT_DEX,			// 205
	AFFECT_CON,	
	AFFECT_INT,	
	AFFECT_FISH_MIND_PILL,

	AFFECT_POISON,
	AFFECT_STUN,		// 210
	AFFECT_SLOW,
	AFFECT_DUNGEON_READY,
	AFFECT_DUNGEON_UNIQUE,

	AFFECT_BUILDING,
	AFFECT_REVIVE_INVISIBLE,	// 215
	AFFECT_FIRE,
	AFFECT_CAST_SPEED,
	AFFECT_HP_RECOVER_CONTINUE,
	AFFECT_SP_RECOVER_CONTINUE,

	AFFECT_POLYMORPH,		// 220
	AFFECT_MOUNT,

	AFFECT_WAR_FLAG,		// 222

	AFFECT_BLOCK_CHAT,		// 223
	AFFECT_CHINA_FIREWORK,

	AFFECT_BOW_DISTANCE,	// 225
	AFFECT_DEF_GRADE,		// 226

	AFFECT_PREMIUM_START	= 500,
	AFFECT_EXP_BONUS		= 500,	// °жЗиАЗ №ЭБц
	AFFECT_ITEM_BONUS		= 501,	// µµµПАЗ Ае°©
	AFFECT_SAFEBOX		= 502,  // PREMIUM_SAFEBOX,
	AFFECT_AUTOLOOT		= 503,	// PREMIUM_AUTOLOOT,
	AFFECT_FISH_MIND		= 504,	// PREMIUM_FISH_MIND,
	AFFECT_MARRIAGE_FAST	= 505,	// їшѕУАЗ ±кЕР
	AFFECT_GOLD_BONUS		= 506,	// µ· µе·УИ®·ь 50%Бх°Ў
	AFFECT_PREMIUM_END		= 509,

	AFFECT_MALL			= 510,	// ёф ѕЖАМЕЫ їЎЖеЖ®
	AFFECT_NO_DEATH_PENALTY	= 511,	// їлЅЕАЗ °ЎИЈ (°жЗиДЎ°Ў ЖРіОЖјё¦ ЗС№ш ё·ѕЖБШґЩ)
	AFFECT_SKILL_BOOK_BONUS	= 512,	// ј±АОАЗ ±іИЖ (ГҐ јц·Г јє°ш И®·ьАМ 50% Бх°Ў)
	AFFECT_SKILL_NO_BOOK_DELAY	= 513,	// БЦѕИјъј­

	AFFECT_HAIR	= 514,	// Змѕо Иї°ъ
	AFFECT_COLLECT = 515, //јцБэДщЅєЖ® 
	AFFECT_EXP_BONUS_EURO_FREE = 516, // °жЗиАЗ №ЭБц (АЇ·ґ №цАь 14 ·№є§ АМЗП ±вє» Иї°ъ)
	AFFECT_EXP_BONUS_EURO_FREE_UNDER_15 = 517,
	AFFECT_UNIQUE_ABILITY = 518,

	AFFECT_CUBE_1,
	AFFECT_CUBE_2,
	AFFECT_CUBE_3,
	AFFECT_CUBE_4,
	AFFECT_CUBE_5,
	AFFECT_CUBE_6,
	AFFECT_CUBE_7,
	AFFECT_CUBE_8,
	AFFECT_CUBE_9,
	AFFECT_CUBE_10,
	AFFECT_CUBE_11,
	AFFECT_CUBE_12,

	AFFECT_BLEND,

	AFFECT_HORSE_NAME,
	AFFECT_MOUNT_BONUS,

	AFFECT_AUTO_HP_RECOVERY = 534,
	AFFECT_AUTO_SP_RECOVERY = 535,

	AFFECT_DRAGON_SOUL_QUALIFIED = 540,
	AFFECT_DRAGON_SOUL_DECK_0 = 541,
	AFFECT_DRAGON_SOUL_DECK_1 = 542,


	AFFECT_RAMADAN_ABILITY = 300,
	AFFECT_RAMADAN_RING	   = 301,

	AFFECT_NOG_ABILITY = 302,
	AFFECT_HOLLY_STONE_POWER = 303,

	AFFECT_QUEST_START_IDX = 1000
};

enum EAffectBits
{   
	AFF_NONE,

	AFF_YMIR,
	AFF_INVISIBILITY,
	AFF_SPAWN,

	AFF_POISON,
	AFF_SLOW,
	AFF_STUN,

	AFF_DUNGEON_READY,		// ґшАьїЎј­ БШєс »уЕВ
	AFF_DUNGEON_UNIQUE,		// ґшАь АЇґПЕ© (Е¬¶уАМѕрЖ®їЎј­ ДГёµµЗБцѕКАЅ)

	AFF_BUILDING_CONSTRUCTION_SMALL,
	AFF_BUILDING_CONSTRUCTION_LARGE,
	AFF_BUILDING_UPGRADE,

	AFF_MOV_SPEED_POTION,
	AFF_ATT_SPEED_POTION,

	AFF_FISH_MIND,

	AFF_JEONGWIHON,		// Аь±НИҐ
	AFF_GEOMGYEONG,		// °Л°ж
	AFF_CHEONGEUN,		// Гµ±ЩГЯ
	AFF_GYEONGGONG,		// °ж°шјъ
	AFF_EUNHYUNG,		// АєЗь№э
	AFF_GWIGUM,			// ±Н°Л
	AFF_TERROR,			// °шЖч
	AFF_JUMAGAP,		// БЦё¶°©
	AFF_HOSIN,			// ИЈЅЕ
	AFF_BOHO,			// єёИЈ
	AFF_KWAESOK,		// ДијУ
	AFF_MANASHIELD,		// ё¶іЄЅЇµе
	AFF_MUYEONG,		// №«їµБш affect
	AFF_REVIVE_INVISIBLE,	// єОИ°ЅГ АбЅГµїѕИ №«Аы
	AFF_FIRE,			// БцјУ єТ µҐ№МБц
	AFF_GICHEON,		// ±вГµґл°ш
	AFF_JEUNGRYEOK,		// Бх·Вјъ
	AFF_TANHWAN_DASH,		// ЕєИЇ°Эїл ґЮё®±вѕоЖеЖ®
	AFF_PABEOP,			// ЖД№эјъ
	AFF_CHEONGEUN_WITH_FALL,	// Гµ±ЩГЯ
	AFF_POLYMORPH,
	AFF_WAR_FLAG1,
	AFF_WAR_FLAG2,
	AFF_WAR_FLAG3,

	AFF_CHINA_FIREWORK,
	AFF_HAIR,	// Змѕо
	AFF_GERMANY, // µ¶АП 

	AFF_BITS_MAX
};

extern void SendAffectAddPacket(LPDESC d, CAffect * pkAff);

// AFFECT_DURATION_BUG_FIX
enum AffectVariable
{
	// Affect°Ў №«ЗСґл·О µйѕо°Ў АЦѕоѕЯ ЗТ °жїм »зїл.
	// ЅГ°ЈА» °ијУ БЩАМ±в ¶§№®їЎ ёЕїм Е«°ЄАё·О №«ЗСґлё¦ їЎ№Д·№АМјЗЗФ.
	//// 24єсЖ®ґВ АыАё№З·О 25єсЖ®ё¦ »зїл.
	// ... 25єсЖ® »зїлЗСґЩ°н ЗШіх°нј± 29bit »зїлЗП°н АЦґВ ѕцГ»і­ БЦј®АМ¶х...
	// collect questїЎј­ №«ЗС ЅГ°ЈА» 60івАё·О »зїлЗП°н АЦАё№З·О, ї©±вµµ 60івАё·О ЗПАЪ.

	INFINITE_AFFECT_DURATION = 60 * 365 * 24 * 60 * 60
};
// END_AFFECT_DURATION_BUG_FIX

#endif
