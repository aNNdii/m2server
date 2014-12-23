#ifndef __HEADER_BELT_INVENTORY_HELPER__
#define __HEADER_BELT_INVENTORY_HELPER__

#include "char.h"
#include "item.h"

class CBeltInventoryHelper
{
public:
	typedef BYTE	TGradeUnit;

	static TGradeUnit GetBeltGradeByRefineLevel(int level)
	{
		static TGradeUnit beltGradeByLevelTable[] = 
		{
			0,			// є§Ж®+0
			1,			// +1
			1,			// +2
			2,			// +3
			2,			// +4,
			3,			// +5
			4,			// +6,
			5,			// +7,
			6,			// +8,
			7,			// +9
		};

		if (level >= _countof(beltGradeByLevelTable))
		{
			sys_err("CBeltInventoryHelper::GetBeltGradeByRefineLevel - Overflow level (%d", level);
			return 0;
		}

		return beltGradeByLevelTable[level];
	}

	// ЗцАз є§Ж® ·№є§А» ±вБШАё·О, ѕо¶І јїµйА» АМїлЗТ јц АЦґВБц ё®ЕП
	static const TGradeUnit* GetAvailableRuleTableByGrade()
	{
		/**
			є§Ж®ґВ ГС +0 ~ +9 ·№є§А» °ЎБъ јц АЦАёёз, ·№є§їЎ µы¶у 7ґЬ°и µо±ЮАё·О ±ёєРµЗѕо АОєҐЕдё®°Ў И°јє И­ µИґЩ.
			є§Ж® ·№є§їЎ µыёҐ »зїл °ЎґЙЗС јїАє ѕЖ·Ў ±ЧёІ°ъ °°АЅ. ЗцАз µо±Ю >= И°јє°ЎґЙ µо±ЮАМёй »зїл °ЎґЙ.
			(ґЬ, ЗцАз ·№є§АМ 0АМёй №«Б¶°З »зїл єТ°Ў, °эИЈ ѕИАЗ јэАЪґВ µо±Ю)
			
				2(1)  4(2)  6(4)  8(6)
				5(3)  5(3)  6(4)  8(6)
				7(5)  7(5)  7(5)  8(6)
				9(7)  9(7)  9(7)  9(7)

			є§Ж® АОєҐЕдё®АЗ Е©±вґВ 4x4 (16Д­)
		*/

		static TGradeUnit availableRuleByGrade[BELT_INVENTORY_SLOT_COUNT] = {
			1, 2, 4, 6,
			3, 3, 4, 6,
			5, 5, 5, 6,
			7, 7, 7, 7
		};

		return availableRuleByGrade;
	}

	static bool IsAvailableCell(WORD cell, int beltGrade /*int beltLevel*/)
	{
		// ±вИ№ ¶З №ЩІс.. ѕЖіц...
		//const TGradeUnit beltGrade = GetBeltGradeByRefineLevel(beltLevel);		
		const TGradeUnit* ruleTable = GetAvailableRuleTableByGrade();

		return ruleTable[cell] <= beltGrade;
	}

	/// pcАЗ є§Ж® АОєҐЕдё®їЎ ѕЖАМЕЫАМ ЗПіЄ¶уµµ БёАзЗПґВ Бц °Л»зЗПґВ ЗФјц.
	static bool IsExistItemInBeltInventory(LPCHARACTER pc)
	{
		for (WORD i = BELT_INVENTORY_SLOT_START; i < BELT_INVENTORY_SLOT_END; ++i)
		{
			LPITEM beltInventoryItem = pc->GetInventoryItem(i);

			if (NULL != beltInventoryItem)
				return true;
		}

		return false;
	}

	/// itemАМ є§Ж® АОєҐЕдё®їЎ µйѕо°Ґ јц АЦґВ ЕёАФАОБц °Л»зЗПґВ ЗФјц. (АМ ±ФДўАє ±вИ№АЪ°Ў °бБ¤ЗФ)
	static bool CanMoveIntoBeltInventory(LPITEM item)
	{
		bool canMove = false;

		if (item->GetType() == ITEM_USE)
		{
			switch (item->GetSubType())
			{
			case USE_POTION:
			case USE_POTION_NODELAY:
			case USE_ABILITY_UP:
				canMove = true;
				break;
			}
		}

		return canMove;
	}

};

#endif //__HEADER_BELT_INVENTORY_HELPER__