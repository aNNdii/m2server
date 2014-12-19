#include "stdafx.h"
#include "utils.h"
#include "char.h"
#include "char_manager.h"
#include "motion.h"
#include "packet.h"
#include "buffer_manager.h"
#include "unique_item.h"
#include "wedding.h"

#define NEED_TARGET	(1 << 0)
#define NEED_PC		(1 << 1)
#define WOMAN_ONLY	(1 << 2)
#define OTHER_SEX_ONLY	(1 << 3)
#define SELF_DISARM	(1 << 4)
#define TARGET_DISARM	(1 << 5)
#define BOTH_DISARM	(SELF_DISARM | TARGET_DISARM)

struct emotion_type_s
{
	const char *	command;
	const char *	command_to_client;
	long	flag;
	float	extra_delay;
} emotion_types[] = {
	{ "Е°Ѕє",	"french_kiss",	NEED_PC | OTHER_SEX_ONLY | BOTH_DISARM,		2.0f },
	{ "»З»З",	"kiss",		NEED_PC | OTHER_SEX_ONLY | BOTH_DISARM,		1.5f },
	{ "µы±Н",	"slap",		NEED_PC | SELF_DISARM,				1.5f },
	{ "№Ъјц",	"clap",		0,						1.0f },
	{ "їН",		"cheer1",	0,						1.0f },
	{ "ёёјј",	"cheer2",	0,						1.0f },
	
	// DANCE
	{ "ґнЅє1",	"dance1",	0,						1.0f },
	{ "ґнЅє2",	"dance2",	0,						1.0f },
	{ "ґнЅє3",	"dance3",	0,						1.0f },
	{ "ґнЅє4",	"dance4",	0,						1.0f },
	{ "ґнЅє5",	"dance5",	0,						1.0f },
	{ "ґнЅє6",	"dance6",	0,						1.0f },
	// END_OF_DANCE
	{ "ГаЗП",	"congratulation",	0,				1.0f	},
	{ "їлј­",	"forgive",			0,				1.0f	},
	{ "И­іІ",	"angry",			0,				1.0f	},
	{ "АЇИ¤",	"attractive",		0,				1.0f	},
	{ "ЅЅЗД",	"sad",				0,				1.0f	},
	{ "єкІф",	"shy",				0,				1.0f	},
	{ "ААїш",	"cheerup",			0,				1.0f	},
	{ "БъЕх",	"banter",			0,				1.0f	},
	{ "±в»Э",	"joy",				0,				1.0f	},
	{ "\n",	"\n",		0,						0.0f },
	/*
	//{ "Е°Ѕє",		NEED_PC | OTHER_SEX_ONLY | BOTH_DISARM,		MOTION_ACTION_FRENCH_KISS,	 1.0f },
	{ "»З»З",		NEED_PC | OTHER_SEX_ONLY | BOTH_DISARM,		MOTION_ACTION_KISS,		 1.0f },
	{ "ІёѕИ±в",		NEED_PC | OTHER_SEX_ONLY | BOTH_DISARM,		MOTION_ACTION_SHORT_HUG,	 1.0f },
	{ "ЖчїЛ",		NEED_PC | OTHER_SEX_ONLY | BOTH_DISARM,		MOTION_ACTION_LONG_HUG,		 1.0f },
	{ "ѕо±ъµї№«",	NEED_PC | SELF_DISARM,				MOTION_ACTION_PUT_ARMS_SHOULDER, 0.0f },
	{ "ЖИВЇ",		NEED_PC	| WOMAN_ONLY | SELF_DISARM,		MOTION_ACTION_FOLD_ARM,		 0.0f },
	{ "µы±Н",		NEED_PC | SELF_DISARM,				MOTION_ACTION_SLAP,		 1.5f },

	{ "ИЦЖД¶ч",		0,						MOTION_ACTION_CHEER_01,		 0.0f },
	{ "ёёјј",		0,						MOTION_ACTION_CHEER_02,		 0.0f },
	{ "№Ъјц",		0,						MOTION_ACTION_CHEER_03,		 0.0f },

	{ "ИЈИЈ",		0,						MOTION_ACTION_LAUGH_01,		 0.0f },
	{ "Е±Е±",		0,						MOTION_ACTION_LAUGH_02,		 0.0f },
	{ "їмЗПЗП",		0,						MOTION_ACTION_LAUGH_03,		 0.0f },

	{ "ѕыѕы",		0,						MOTION_ACTION_CRY_01,		 0.0f },
	{ "ИжИж",		0,						MOTION_ACTION_CRY_02,		 0.0f },

	{ "АО»з",		0,						MOTION_ACTION_GREETING_01,	0.0f },
	{ "№ЩАМ",		0,						MOTION_ACTION_GREETING_02,	0.0f },
	{ "Б¤БЯАО»з",	0,						MOTION_ACTION_GREETING_03,	0.0f },

	{ "єсі­",		0,						MOTION_ACTION_INSULT_01,	0.0f },
	{ "ёрїе",		SELF_DISARM,					MOTION_ACTION_INSULT_02,	0.0f },
	{ "їмАЎ",		0,						MOTION_ACTION_INSULT_03,	0.0f },

	{ "°јїм¶Ч",		0,						MOTION_ACTION_ETC_01,		0.0f },
	{ "ІфґцІфґц",	0,						MOTION_ACTION_ETC_02,		0.0f },
	{ "µµё®µµё®",	0,						MOTION_ACTION_ETC_03,		0.0f },
	{ "±ЬАы±ЬАы",	0,						MOTION_ACTION_ETC_04,		0.0f },
	{ "ЖЎ",		0,						MOTION_ACTION_ETC_05,		0.0f },
	{ "»Ч",		0,						MOTION_ACTION_ETC_06,		0.0f },
	 */
};


std::set<std::pair<DWORD, DWORD> > s_emotion_set;

ACMD(do_emotion_allow)
{
	if ( ch->GetArena() )
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("ґл·ГАеїЎј­ »зїлЗПЅЗ јц ѕшЅАґПґЩ."));
		return;
	}

	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
		return;

	DWORD	val = 0; str_to_number(val, arg1);
	s_emotion_set.insert(std::make_pair(ch->GetVID(), val));
}

bool CHARACTER_CanEmotion(CHARACTER& rch)
{
	// °бИҐЅД ёКїЎј­ґВ »зїлЗТ јц АЦґЩ.
	if (marriage::WeddingManager::instance().IsWeddingMap(rch.GetMapIndex()))
		return true;

	// ї­Б¤АЗ °Ўёй ВшїлЅГ »зїлЗТ јц АЦґЩ.
	if (rch.IsEquipUniqueItem(UNIQUE_ITEM_EMOTION_MASK))
		return true;

	if (rch.IsEquipUniqueItem(UNIQUE_ITEM_EMOTION_MASK2))
		return true;

	return false;
}

ACMD(do_emotion)
{
	int i;
	{
		if (ch->IsRiding())
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("ё»А» Еє »уЕВїЎј­ °ЁБ¤ЗҐЗцА» ЗТ јц ѕшЅАґПґЩ."));
			return;
		}
	}

	for (i = 0; *emotion_types[i].command != '\n'; ++i)
	{
		if (!strcmp(cmd_info[cmd].command, emotion_types[i].command))
			break;

		if (!strcmp(cmd_info[cmd].command, emotion_types[i].command_to_client))
			break;
	}

	if (*emotion_types[i].command == '\n')
	{
		sys_err("cannot find emotion");
		return;
	}

	if (!CHARACTER_CanEmotion(*ch))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("ї­Б¤АЗ °ЎёйА» ВшїлЅГїЎёё ЗТ јц АЦЅАґПґЩ."));
		return;
	}

	if (IS_SET(emotion_types[i].flag, WOMAN_ONLY) && SEX_MALE==GET_SEX(ch))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("ї©АЪёё ЗТ јц АЦЅАґПґЩ."));
		return;
	}

	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	LPCHARACTER victim = NULL;

	if (*arg1)
		victim = ch->FindCharacterInView(arg1, IS_SET(emotion_types[i].flag, NEED_PC));

	if (IS_SET(emotion_types[i].flag, NEED_TARGET | NEED_PC))
	{
		if (!victim)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("±Ч·± »з¶чАМ ѕшЅАґПґЩ."));
			return;
		}
	}

	if (victim)
	{
		if (!victim->IsPC() || victim == ch)
			return;

		if (victim->IsRiding())
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("ё»А» Еє »уґлїН °ЁБ¤ЗҐЗцА» ЗТ јц ѕшЅАґПґЩ."));
			return;
		}

		long distance = DISTANCE_APPROX(ch->GetX() - victim->GetX(), ch->GetY() - victim->GetY());

		if (distance < 10)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("іК№« °Ў±оАМ АЦЅАґПґЩ."));
			return;
		}

		if (distance > 500)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("іК№« ёЦё® АЦЅАґПґЩ"));
			return;
		}

		if (IS_SET(emotion_types[i].flag, OTHER_SEX_ONLY))
		{
			if (GET_SEX(ch)==GET_SEX(victim))
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("АМјє°ЈїЎёё ЗТ јц АЦЅАґПґЩ."));
				return;
			}
		}

		if (IS_SET(emotion_types[i].flag, NEED_PC))
		{
			if (s_emotion_set.find(std::make_pair(victim->GetVID(), ch->GetVID())) == s_emotion_set.end())
			{
				if (true == marriage::CManager::instance().IsMarried( ch->GetPlayerID() ))
				{
					const marriage::TMarriage* marriageInfo = marriage::CManager::instance().Get( ch->GetPlayerID() );

					const DWORD other = marriageInfo->GetOther( ch->GetPlayerID() );

					if (0 == other || other != victim->GetPlayerID())
					{
						ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("АМ ЗаµїАє »уИЈµїАЗ ЗПїЎ °ЎґЙ ЗХґПґЩ."));
						return;
					}
				}
				else
				{
					ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("АМ ЗаµїАє »уИЈµїАЗ ЗПїЎ °ЎґЙ ЗХґПґЩ."));
					return;
				}
			}

			s_emotion_set.insert(std::make_pair(ch->GetVID(), victim->GetVID()));
		}
	}

	char chatbuf[256+1];
	int len = snprintf(chatbuf, sizeof(chatbuf), "%s %u %u", 
			emotion_types[i].command_to_client,
			(DWORD) ch->GetVID(), victim ? (DWORD) victim->GetVID() : 0);

	if (len < 0 || len >= (int) sizeof(chatbuf))
		len = sizeof(chatbuf) - 1;

	++len;  // \0 №®АЪ ЖчЗФ

	TPacketGCChat pack_chat;
	pack_chat.header = HEADER_GC_CHAT;
	pack_chat.size = sizeof(TPacketGCChat) + len;
	pack_chat.type = CHAT_TYPE_COMMAND;
	pack_chat.id = 0;
	TEMP_BUFFER buf;
	buf.write(&pack_chat, sizeof(TPacketGCChat));
	buf.write(chatbuf, len);

	ch->PacketAround(buf.read_peek(), buf.size());

	if (victim)
		sys_log(1, "ACTION: %s TO %s", emotion_types[i].command, victim->GetName());
	else
		sys_log(1, "ACTION: %s", emotion_types[i].command);
}

