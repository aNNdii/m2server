#ifndef __HEADER_VNUM_HELPER__
#define	__HEADER_VNUM_HELPER__

/**
	АМ№М БёАзЗП°ЕіЄ ѕХАё·О ГЯ°ЎµЙ ѕЖАМЕЫ, ёч µоА» јТЅєїЎј­ ЅДє°ЗТ ¶§ ЗцАзґВ ёрµО
	ЅДє°АЪ(јэАЪ=VNum)ё¦ ЗПµеДЪµщЗПґВ №жЅДАё·О µЗѕоАЦѕој­ °Ўµ¶јєАМ ёЕїм ¶іѕоБцґВµҐ

	ѕХАё·ОґВ јТЅєёё єБµµ ѕо¶І ѕЖАМЕЫ(И¤Ає ёч)АОБц ѕЛ јц АЦ°Ф ЗПАЪґВ ЅВГ¶ґФАЗ Б¦ѕИАё·О ГЯ°Ў.

		* АМ ЖДАПАє єЇ°жАМ АжА»°НАё·О ї№»уµЗґВµҐ PCHїЎ іЦАёёй №ЩІр ¶§ё¶ґЩ АьГј ДДЖДАП ЗШѕЯЗПґП 
		АПґЬАє ЗКїдЗС cppЖДАПїЎј­ include ЗШј­ ѕІµµ·П ЗЯАЅ.

		* cppїЎј­ ±ёЗцЗПёй ДДЖДАП ~ ёµЕ©ЗШѕЯЗПґП ±ЧіЙ commonїЎ Змґхёё іЦѕъАЅ. (game, dbЗБ·ОБ§Ж® µС ґЩ »зїл ї№Б¤)

	@date	2011. 8. 29.
*/


class CItemVnumHelper
{
public:
	/// µ¶АП DVDїл єТ»зБ¶ јТИЇ±З
	static	const bool	IsPhoenix(DWORD vnum)				{ return 53001 == vnum; }		// NOTE: єТ»зБ¶ јТИЇ ѕЖАМЕЫАє 53001 АМБцёё mob-vnumАє 34001 АФґПґЩ.

	/// ¶уё¶ґЬ АМєҐЖ® ГКЅВґЮАЗ №ЭБц (їш·ЎґВ ¶уё¶ґЬ АМєҐЖ®їл ЖЇјц ѕЖАМЕЫАМѕъАёіЄ ѕХАё·О ї©·Ї №жЗвАё·О АзИ°їлЗШј­ °ијУ ѕґґЩ°н ЗФ)
	static	const bool	IsRamadanMoonRing(DWORD vnum)		{ return 71135 == vnum; }

	/// ЗТ·ОА© »зЕБ (ЅєЖеАє ГКЅВґЮАЗ №ЭБцїН µїАП)
	static	const bool	IsHalloweenCandy(DWORD vnum)		{ return 71136 == vnum; }

	/// Е©ё®Ѕєё¶Ѕє Зає№АЗ №ЭБц
	static	const bool	IsHappinessRing(DWORD vnum)		{ return 71143 == vnum; }

	/// №Я·»ЕёАО »з¶ыАЗ ЖТґшЖ® 
	static	const bool	IsLovePendant(DWORD vnum)		{ return 71145 == vnum; }
};

class CMobVnumHelper
{
public:
	/// µ¶АП DVDїл єТ»зБ¶ ёч №шИЈ
	static	bool	IsPhoenix(DWORD vnum)				{ return 34001 == vnum; }
	static	bool	IsIcePhoenix(DWORD vnum)				{ return 34003 == vnum; }
	/// PetSystemАМ °ьё®ЗПґВ ЖкАО°Ў?
	static	bool	IsPetUsingPetSystem(DWORD vnum)	{ return (IsPhoenix(vnum) || IsReindeerYoung(vnum)) || IsIcePhoenix(vnum); }

	/// 2011ів Е©ё®Ѕєё¶Ѕє АМєҐЖ®їл Жк (ѕЖ±в јш·П)
	static	bool	IsReindeerYoung(DWORD vnum)	{ return 34002 == vnum; }

	/// ¶уё¶ґЬ АМєҐЖ® єё»уїл Ижё¶(20119) .. ЗТ·ОА© АМєҐЖ®їл ¶уё¶ґЬ Ижё¶ Е¬·Р(ЅєЖеАє °°АЅ, 20219)
	static	bool	IsRamadanBlackHorse(DWORD vnum)		{ return 20119 == vnum || 20219 == vnum || 22022 == vnum; }
};

class CVnumHelper
{
};


#endif	//__HEADER_VNUM_HELPER__