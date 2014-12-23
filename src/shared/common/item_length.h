#ifndef __INC_METIN2_ITEM_LENGTH_H__
#define __INC_METIN2_ITEM_LENGTH_H__

enum EItemMisc
{
	ITEM_NAME_MAX_LEN			= 24,
	ITEM_VALUES_MAX_NUM			= 6,
	ITEM_SMALL_DESCR_MAX_LEN	= 256,
	ITEM_LIMIT_MAX_NUM			= 2,
	ITEM_APPLY_MAX_NUM			= 3,
	ITEM_SOCKET_MAX_NUM			= 3,
	ITEM_MAX_COUNT				= 200,
	ITEM_ATTRIBUTE_MAX_NUM		= 7,
	ITEM_ATTRIBUTE_MAX_LEVEL	= 5,
	ITEM_AWARD_WHY_MAX_LEN		= 50,

	REFINE_MATERIAL_MAX_NUM		= 5,

	ITEM_ELK_VNUM				= 50026,
};

const BYTE ITEM_SOCKET_REMAIN_SEC = 0;
enum EItemValueIdice
{
	ITEM_VALUE_DRAGON_SOUL_POLL_OUT_BONUS_IDX = 0,
	ITEM_VALUE_CHARGING_AMOUNT_IDX = 0,
	ITEM_VALUE_SECONDARY_COIN_UNIT_IDX = 0,
};
enum EItemDragonSoulSockets
{
	ITEM_SOCKET_DRAGON_SOUL_ACTIVE_IDX = 2,
	ITEM_SOCKET_CHARGING_AMOUNT_IDX = 2,
};
// Зж АМ°Е №МДЈ°Е ѕЖґПѕЯ?
// іЄБЯїЎ јТДП И®АеЗПёй ѕоВј·Б°н АМБц¶ц -_-;;;
enum EItemUniqueSockets
{
	ITEM_SOCKET_UNIQUE_SAVE_TIME = ITEM_SOCKET_MAX_NUM - 2,
	ITEM_SOCKET_UNIQUE_REMAIN_TIME = ITEM_SOCKET_MAX_NUM - 1
};

enum EItemTypes
{
    ITEM_NONE,              //0
    ITEM_WEAPON,            //1//№«±в
    ITEM_ARMOR,             //2//°©їК
    ITEM_USE,               //3//ѕЖАМЕЫ »зїл
    ITEM_AUTOUSE,           //4
    ITEM_MATERIAL,          //5
    ITEM_SPECIAL,           //6 //ЅєЖдјИ ѕЖАМЕЫ
    ITEM_TOOL,              //7
    ITEM_LOTTERY,           //8//є№±З
    ITEM_ELK,               //9//µ·
    ITEM_METIN,             //10
    ITEM_CONTAINER,         //11
    ITEM_FISH,              //12//і¬ЅГ
    ITEM_ROD,               //13
    ITEM_RESOURCE,          //14
    ITEM_CAMPFIRE,          //15
    ITEM_UNIQUE,            //16
    ITEM_SKILLBOOK,         //17
    ITEM_QUEST,             //18
    ITEM_POLYMORPH,         //19
    ITEM_TREASURE_BOX,      //20//єё№°»уАЪ
    ITEM_TREASURE_KEY,      //21//єё№°»уАЪ ї­ји
    ITEM_SKILLFORGET,       //22
    ITEM_GIFTBOX,           //23
    ITEM_PICK,              //24
    ITEM_HAIR,              //25//ёУё®
    ITEM_TOTEM,             //26//ЕдЕЫ
	ITEM_BLEND,				//27//»эјєµЙ¶§ ·ЈґэЗП°Ф јУјєАМ єЩґВ ѕа№°
	ITEM_COSTUME,			//28//ДЪЅєГх ѕЖАМЕЫ (2011ів 8їщ ГЯ°ЎµИ ДЪЅєГх ЅГЅєЕЫїл ѕЖАМЕЫ)
	ITEM_DS,				//29 //їлИҐј®
	ITEM_SPECIAL_DS,		//30 // ЖЇјцЗС їлИҐј® (DS_SLOTїЎ ВшїлЗПґВ UNIQUE ѕЖАМЕЫАМ¶у »э°ўЗПёй µК)
	ITEM_EXTRACT,			//31 ГЯГвµµ±ё.
	ITEM_SECONDARY_COIN,	//32 ?? ёнµµАь??
	ITEM_RING,				//33 №ЭБц
	ITEM_BELT,				//34 є§Ж®
};

enum EMetinSubTypes
{
	METIN_NORMAL,
	METIN_GOLD,
};

enum EWeaponSubTypes
{
	WEAPON_SWORD,
	WEAPON_DAGGER,
	WEAPON_BOW,
	WEAPON_TWO_HANDED,
	WEAPON_BELL,
	WEAPON_FAN,
	WEAPON_ARROW,
	WEAPON_MOUNT_SPEAR,
	WEAPON_NUM_TYPES,
};

enum EArmorSubTypes
{
	ARMOR_BODY,
	ARMOR_HEAD,
	ARMOR_SHIELD,
	ARMOR_WRIST,
	ARMOR_FOOTS,
	ARMOR_NECK,
	ARMOR_EAR,
	ARMOR_NUM_TYPES
};

enum ECostumeSubTypes
{
	COSTUME_BODY = ARMOR_BODY,			// [БЯїд!!] ECostumeSubTypes enum valueґВ  Бѕ·щє°·О EArmorSubTypesАЗ ±Ч°Н°ъ °°ѕЖѕЯ ЗФ.
	COSTUME_HAIR = ARMOR_HEAD,			// АМґВ ДЪЅєГх ѕЖАМЕЫїЎ ГЯ°Ў јУјєА» єЩАМ°ЪґЩґВ »зѕчєОАЗ їдГ»їЎ µы¶уј­ ±вБё ·ОБчА» И°їлЗП±в А§ЗФАУ.
	COSTUME_NUM_TYPES,
};

enum EDragonSoulSubType
{
	DS_SLOT1,
	DS_SLOT2,
	DS_SLOT3,
	DS_SLOT4,
	DS_SLOT5,
	DS_SLOT6,
	DS_SLOT_MAX,
};

enum EDragonSoulGradeTypes
{
	DRAGON_SOUL_GRADE_NORMAL,
	DRAGON_SOUL_GRADE_BRILLIANT,
	DRAGON_SOUL_GRADE_RARE,
	DRAGON_SOUL_GRADE_ANCIENT,
	DRAGON_SOUL_GRADE_LEGENDARY,
	DRAGON_SOUL_GRADE_MAX,

};

enum EDragonSoulStepTypes
{
	DRAGON_SOUL_STEP_LOWEST,
	DRAGON_SOUL_STEP_LOW,
	DRAGON_SOUL_STEP_MID,
	DRAGON_SOUL_STEP_HIGH,
	DRAGON_SOUL_STEP_HIGHEST,
	DRAGON_SOUL_STEP_MAX,
};
#define DRAGON_SOUL_STRENGTH_MAX 7

enum EDSInventoryMaxNum
{
	DRAGON_SOUL_INVENTORY_MAX_NUM = DS_SLOT_MAX * DRAGON_SOUL_GRADE_MAX * DRAGON_SOUL_BOX_SIZE,
};

enum EFishSubTypes
{
	FISH_ALIVE,
	FISH_DEAD,
};

enum EResourceSubTypes
{
	RESOURCE_FISHBONE,
	RESOURCE_WATERSTONEPIECE,
	RESOURCE_WATERSTONE,
	RESOURCE_BLOOD_PEARL,
	RESOURCE_BLUE_PEARL,
	RESOURCE_WHITE_PEARL,
	RESOURCE_BUCKET,
	RESOURCE_CRYSTAL,
	RESOURCE_GEM,
	RESOURCE_STONE,
	RESOURCE_METIN,
	RESOURCE_ORE,
};

enum EUniqueSubTypes
{
	UNIQUE_NONE,
	UNIQUE_BOOK,
	UNIQUE_SPECIAL_RIDE,
	UNIQUE_SPECIAL_MOUNT_RIDE,
};

enum EUseSubTypes
{
	USE_POTION,					// 0
	USE_TALISMAN,
	USE_TUNING,
	USE_MOVE,
	USE_TREASURE_BOX,
	USE_MONEYBAG,
	USE_BAIT,
	USE_ABILITY_UP,
	USE_AFFECT,
	USE_CREATE_STONE,
	USE_SPECIAL,				// 10
	USE_POTION_NODELAY,
	USE_CLEAR,
	USE_INVISIBILITY,
	USE_DETACHMENT,
	USE_BUCKET,
	USE_POTION_CONTINUE,
	USE_CLEAN_SOCKET,
	USE_CHANGE_ATTRIBUTE,
	USE_ADD_ATTRIBUTE,
	USE_ADD_ACCESSORY_SOCKET,	// 20
	USE_PUT_INTO_ACCESSORY_SOCKET,
	USE_ADD_ATTRIBUTE2,
	USE_RECIPE,
	USE_CHANGE_ATTRIBUTE2,
	USE_BIND,
	USE_UNBIND,
	USE_TIME_CHARGE_PER,
	USE_TIME_CHARGE_FIX,				// 28
	USE_PUT_INTO_BELT_SOCKET,			// 29 є§Ж® јТДПїЎ »зїлЗТ јц АЦґВ ѕЖАМЕЫ 
	USE_PUT_INTO_RING_SOCKET,			// 30 №ЭБц јТДПїЎ »зїлЗТ јц АЦґВ ѕЖАМЕЫ (АЇґПЕ© №ЭБц ё»°н, »х·О ГЯ°ЎµИ №ЭБц ЅЅ·Ф)
};

enum EExtractSubTypes
{
	EXTRACT_DRAGON_SOUL,
	EXTRACT_DRAGON_HEART,
};

enum EAutoUseSubTypes
{
	AUTOUSE_POTION,
	AUTOUSE_ABILITY_UP,
	AUTOUSE_BOMB,
	AUTOUSE_GOLD,
	AUTOUSE_MONEYBAG,
	AUTOUSE_TREASURE_BOX
};

enum EMaterialSubTypes
{
	MATERIAL_LEATHER,
	MATERIAL_BLOOD,
	MATERIAL_ROOT,
	MATERIAL_NEEDLE,
	MATERIAL_JEWEL,
	MATERIAL_DS_REFINE_NORMAL, 
	MATERIAL_DS_REFINE_BLESSED, 
	MATERIAL_DS_REFINE_HOLLY,
};

enum ESpecialSubTypes
{
	SPECIAL_MAP,
	SPECIAL_KEY,
	SPECIAL_DOC,
	SPECIAL_SPIRIT,
};

enum EToolSubTypes
{
	TOOL_FISHING_ROD
};

enum ELotterySubTypes
{
	LOTTERY_TICKET,
	LOTTERY_INSTANT
};

enum EItemFlag
{
	ITEM_FLAG_REFINEABLE		= (1 << 0),
	ITEM_FLAG_SAVE			= (1 << 1),
	ITEM_FLAG_STACKABLE		= (1 << 2),	// ї©·Ї°і ЗХДҐ јц АЦАЅ
	ITEM_FLAG_COUNT_PER_1GOLD	= (1 << 3),
	ITEM_FLAG_SLOW_QUERY		= (1 << 4),
	ITEM_FLAG_UNUSED01		= (1 << 5),	// UNUSED
	ITEM_FLAG_UNIQUE		= (1 << 6),
	ITEM_FLAG_MAKECOUNT		= (1 << 7),
	ITEM_FLAG_IRREMOVABLE		= (1 << 8),
	ITEM_FLAG_CONFIRM_WHEN_USE	= (1 << 9),
	ITEM_FLAG_QUEST_USE		= (1 << 10),
	ITEM_FLAG_QUEST_USE_MULTIPLE	= (1 << 11),
	ITEM_FLAG_QUEST_GIVE		= (1 << 12),
	ITEM_FLAG_LOG			= (1 << 13),
	ITEM_FLAG_APPLICABLE		= (1 << 14),
};

enum EItemAntiFlag
{
	ITEM_ANTIFLAG_FEMALE	= (1 << 0), // ї©јє »зїл єТ°Ў
	ITEM_ANTIFLAG_MALE		= (1 << 1), // іІјє »зїл єТ°Ў
	ITEM_ANTIFLAG_WARRIOR	= (1 << 2), // №«»з »зїл єТ°Ў
	ITEM_ANTIFLAG_ASSASSIN	= (1 << 3), // АЪ°ґ »зїл єТ°Ў
	ITEM_ANTIFLAG_SURA		= (1 << 4), // јц¶у »зїл єТ°Ў 
	ITEM_ANTIFLAG_SHAMAN	= (1 << 5), // №«ґз »зїл єТ°Ў
	ITEM_ANTIFLAG_GET		= (1 << 6), // БэА» јц ѕшАЅ
	ITEM_ANTIFLAG_DROP		= (1 << 7), // №цё± јц ѕшАЅ
	ITEM_ANTIFLAG_SELL		= (1 << 8), // ЖИ јц ѕшАЅ
	ITEM_ANTIFLAG_EMPIRE_A	= (1 << 9), // A Б¦±№ »зїл єТ°Ў
	ITEM_ANTIFLAG_EMPIRE_B	= (1 << 10), // B Б¦±№ »зїл єТ°Ў
	ITEM_ANTIFLAG_EMPIRE_C	= (1 << 11), // C Б¦±№ »зїл єТ°Ў
	ITEM_ANTIFLAG_SAVE		= (1 << 12), // АъАеµЗБц ѕКАЅ
	ITEM_ANTIFLAG_GIVE		= (1 << 13), // °Е·Ў єТ°Ў
	ITEM_ANTIFLAG_PKDROP	= (1 << 14), // PKЅГ ¶іѕоБцБц ѕКАЅ
	ITEM_ANTIFLAG_STACK		= (1 << 15), // ЗХДҐ јц ѕшАЅ
	ITEM_ANTIFLAG_MYSHOP	= (1 << 16), // °іАО »уБЎїЎ їГё± јц ѕшАЅ
	ITEM_ANTIFLAG_SAFEBOX	= (1 << 17), // Гў°нїЎ іЦА» јц ѕшАЅ
};

enum EItemWearableFlag
{
	WEARABLE_BODY	= (1 << 0),
	WEARABLE_HEAD	= (1 << 1),
	WEARABLE_FOOTS	= (1 << 2),
	WEARABLE_WRIST	= (1 << 3),
	WEARABLE_WEAPON	= (1 << 4),
	WEARABLE_NECK	= (1 << 5),
	WEARABLE_EAR	= (1 << 6),
	WEARABLE_UNIQUE	= (1 << 7),
	WEARABLE_SHIELD	= (1 << 8),
	WEARABLE_ARROW	= (1 << 9),
	WEARABLE_HAIR	= (1 << 10),
	WEARABLE_ABILITY		= (1 << 11),
	WEARABLE_COSTUME_BODY	= (1 << 12),
};

enum ELimitTypes
{
	LIMIT_NONE,

	LIMIT_LEVEL,
	LIMIT_STR,
	LIMIT_DEX,
	LIMIT_INT,
	LIMIT_CON,

	/// Вшїл ї©єОїН »у°ь ѕшАМ ЅЗЅГ°ЈАё·О ЅГ°Ј Вч°Ё (socket0їЎ јТёк ЅГ°ЈАМ №ЪИы: unix_timestamp ЕёАФ)
	LIMIT_REAL_TIME,						

	/// ѕЖАМЕЫА» ёЗ ГіАЅ »зїл(И¤Ає Вшїл) ЗС јш°ЈєОЕН ё®ѕуЕёАУ ЕёАМёУ ЅГАЫ 
	/// ГЦГК »зїл АьїЎґВ socket0їЎ »зїл°ЎґЙЅГ°Ј(ГКґЬА§, 0АМёй ЗБ·ОЕдАЗ limit value°Є »зїл) °ЄАМ ѕІї©АЦґЩ°Ў 
	/// ѕЖАМЕЫ »зїлЅГ socket1їЎ »зїл ИЅјц°Ў №ЪИч°н socket0їЎ unix_timestamp ЕёАФАЗ јТёкЅГ°ЈАМ №ЪИы.
	LIMIT_REAL_TIME_START_FIRST_USE,

	/// ѕЖАМЕЫА» Вшїл БЯАП ¶§ёё »зїл ЅГ°ЈАМ Вч°ЁµЗґВ ѕЖАМЕЫ
	/// socket0їЎ іІАє ЅГ°ЈАМ ГКґЬА§·О №ЪИы. (ѕЖАМЕЫ ГЦГК »зїлЅГ ЗШґз °ЄАМ 0АМёй ЗБ·ОЕдАЗ limit value°ЄА» socket0їЎ є№»з)
	LIMIT_TIMER_BASED_ON_WEAR,

	LIMIT_MAX_NUM
};

enum EAttrAddonTypes
{
	ATTR_ADDON_NONE,
	// positive values are reserved for set
	ATTR_DAMAGE_ADDON = -1,
};

enum ERefineType
{
	REFINE_TYPE_NORMAL,
	REFINE_TYPE_NOT_USED1,
	REFINE_TYPE_SCROLL,
	REFINE_TYPE_HYUNIRON,
	REFINE_TYPE_MONEY_ONLY,
	REFINE_TYPE_MUSIN,
	REFINE_TYPE_BDRAGON,
};

#endif
