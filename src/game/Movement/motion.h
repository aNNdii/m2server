#ifndef __INC_GAME_MOTION_H__
#define __INC_GAME_MOTION_H__

#include "common/d3dtype.h"

enum EMotionMode
{
	MOTION_MODE_GENERAL,
	MOTION_MODE_ONEHAND_SWORD,
	MOTION_MODE_TWOHAND_SWORD,
	MOTION_MODE_DUALHAND_SWORD,
	MOTION_MODE_BOW,
	MOTION_MODE_BELL,
	MOTION_MODE_FAN,
	MOTION_MODE_HORSE,
	MOTION_MODE_MAX_NUM
};

enum EPublicMotion
{
	MOTION_NONE,                // 0 ѕшАЅ
	MOTION_WAIT,                // 1 ґл±в          (00.msa)
	MOTION_WALK,                // 2 °И±в          (02.msa)
	MOTION_RUN,                 // 3 ¶Щ±в          (03.msa)
	MOTION_CHANGE_WEAPON,       // 4 №«±в№ЩІЩ±в
	MOTION_DAMAGE,              // 5 Б¤ёйёВ±в      (30.msa)
	MOTION_DAMAGE_FLYING,       // 6 Б¤ёйіЇѕЖ°Ў±в  (32.msa)
	MOTION_STAND_UP,            // 7 Б¤ёйАПѕоіЄ±в  (33.msa)
	MOTION_DAMAGE_BACK,         // 8 ИДёйёВ±в      (34.msa)
	MOTION_DAMAGE_FLYING_BACK,  // 9 ИДёйіЇѕЖ°Ў±в  (35.msa)
	MOTION_STAND_UP_BACK,       // 10 ИДёйАПѕоіЄ±в (26.msa)
	MOTION_DEAD,                // 11 БЧ±в         (31.msa)
	MOTION_DEAD_BACK,           // 12 ИДёйБЧ±в     (37.msa)
	MOTION_NORMAL_ATTACK,		// 13 ±вє» °ш°Э
	MOTION_COMBO_ATTACK_1,		// 14 ДЮєё °ш°Э
	MOTION_COMBO_ATTACK_2,      // 15 ДЮєё °ш°Э
	MOTION_COMBO_ATTACK_3,      // 16 ДЮєё °ш°Э
	MOTION_COMBO_ATTACK_4,      // 17 ДЮєё °ш°Э
	MOTION_COMBO_ATTACK_5,      // 18 ДЮєё °ш°Э
	MOTION_COMBO_ATTACK_6,      // 19 ДЮєё °ш°Э
	MOTION_COMBO_ATTACK_7,      // 20 ДЮєё °ш°Э
	MOTION_COMBO_ATTACK_8,      // 21 ДЮєё °ш°Э
	MOTION_INTRO_WAIT,          // 22 ј±ЕГИ­ёй ґл±в
	MOTION_INTRO_SELECTED,      // 23 ј±ЕГИ­ёй ј±ЕГ
	MOTION_INTRO_NOT_SELECTED,  // 24 ј±ЕГИ­ёй єсј±ЕГ
	MOTION_SPAWN,               // 25 јТИЇ
	MOTION_FISHING_THROW,       // 26 і¬ЅГ ґшБц±в
	MOTION_FISHING_WAIT,        // 27 і¬ЅГ ґл±в
	MOTION_FISHING_STOP,        // 28 і¬ЅГ ±ЧёёµО±в
	MOTION_FISHING_REACT,       // 29 і¬ЅГ №ЭАА
	MOTION_FISHING_CATCH,       // 30 і¬ЅГ Ав±в
	MOTION_FISHING_FAIL,        // 31 і¬ЅГ ЅЗЖР
	MOTION_STOP,                // 32 ё» ёШГЯ±в
	MOTION_SPECIAL_1,           // 33 ёуЅєЕН ЅєЕі
	MOTION_SPECIAL_2,           // 34 
	MOTION_SPECIAL_3,			// 35
	MOTION_SPECIAL_4,			// 36
	MOTION_SPECIAL_5,			// 37
	PUBLIC_MOTION_END,
	MOTION_MAX_NUM = PUBLIC_MOTION_END,
};

class CMob;

class CMotion
{
	public:
		CMotion();
		~CMotion();

		bool			LoadFromFile(const char * c_pszFileName);
		bool			LoadMobSkillFromFile(const char * c_pszFileName, CMob * pMob, int iSkillIndex);

		float			GetDuration() const;
		const D3DVECTOR &	GetAccumVector() const;

		bool			IsEmpty();

	protected:
		bool			m_isEmpty;
		float			m_fDuration;
		bool			m_isAccumulation;
		D3DVECTOR		m_vec3Accumulation;
};

typedef DWORD MOTION_KEY;

#define MAKE_MOTION_KEY(mode, index)			( ((mode) << 24) | ((index) << 8) | (0) )
#define MAKE_RANDOM_MOTION_KEY(mode, index, type)	( ((mode) << 24) | ((index) << 8) | (type) )

#define GET_MOTION_MODE(key)				((BYTE) ((key >> 24) & 0xFF))
#define GET_MOTION_INDEX(key)				((WORD) ((key >> 8) & 0xFFFF))
#define GET_MOTION_SUB_INDEX(key)			((BYTE) ((key) & 0xFF))

class CMotionSet
{
	public:
		typedef std::map<DWORD, CMotion *>	TContainer;
		typedef TContainer::iterator		iterator;
		typedef TContainer::const_iterator	const_iterator;

	public:
		CMotionSet();
		~CMotionSet();

		void		Insert(DWORD dwKey, CMotion * pkMotion);
		bool		Load(const char * szFileName, int mode, int motion);

		const CMotion *	GetMotion(DWORD dwKey) const;

	protected:
		// DWORD = MOTION_KEY
		TContainer			m_map_pkMotion;
};

class CMotionManager : public singleton<CMotionManager>
{
	public:
		typedef std::map<DWORD, CMotionSet *> TContainer;
		typedef TContainer::iterator iterator;

		CMotionManager();
		virtual ~CMotionManager();

		bool			Build();

		const CMotionSet *	GetMotionSet(DWORD dwVnum);
		const CMotion *		GetMotion(DWORD dwVnum, DWORD dwKey);
		float			    GetMotionDuration(DWORD dwVnum, DWORD dwKey);

		// POLYMORPH_BUG_FIX
		float			    GetNormalAttackDuration(DWORD dwVnum);
		// END_OF_POLYMORPH_BUG_FIX

	protected:
		// DWORD = JOB or MONSTER VNUM
		TContainer		m_map_pkMotionSet;

		// POLYMORPH_BUG_FIX
		std::map<DWORD, float> m_map_normalAttackDuration;
		// END_OF_POLYMORPH_BUG_FIX
};

#endif
