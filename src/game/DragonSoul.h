#ifndef __INC_METIN_II_GAME_DRAGON_SOUL_H__
#define __INC_METIN_II_GAME_DRAGON_SOUL_H__

#include "common/length.h"

class CHARACTER;
class CItem;

class DragonSoulTable;

class DSManager : public singleton<DSManager>
{
public:
	DSManager();
	~DSManager();
	bool	ReadDragonSoulTableFile(const char * c_pszFileName);

	void	GetDragonSoulInfo(DWORD dwVnum, OUT BYTE& bType, OUT BYTE& bGrade, OUT BYTE& bStep, OUT BYTE& bRefine) const;
	// fixme : titempos·О
	WORD	GetBasePosition(const LPITEM pItem) const;
	bool	IsValidCellForThisItem(const LPITEM pItem, const TItemPos& Cell) const;
	int		GetDuration(const LPITEM pItem) const;
	
	// їлИҐј®А» №ЮѕЖј­ ЖЇБ¤ їлЅЙА» ГЯГвЗПґВ ЗФјц
	bool	ExtractDragonHeart(LPCHARACTER ch, LPITEM pItem, LPITEM pExtractor = NULL);

	// ЖЇБ¤ їлИҐј®(pItem)А» АеєсГўїЎј­ Б¦°ЕЗТ ¶§їЎ јє°ш ї©єОё¦ °бБ¤ЗП°н, 
	// ЅЗЖРЅГ єО»к№°А» БЦґВ ЗФјц.(єО»к№°Ає dragon_soul_table.txtїЎ Б¤АЗ)
	// DestCellїЎ invalidЗС °ЄА» іЦАёёй јє°ш ЅГ, їлИҐј®А» єу °ш°ЈїЎ АЪµї ГЯ°Ў.
	// ЅЗЖР ЅГ, їлИҐј®(pItem)Ає deleteµК.
	// ГЯГвѕЖАМЕЫАМ АЦґЩёй ГЯГв јє°ш И®·ьАМ pExtractor->GetValue(0)%ёёЕ­ Бх°ЎЗФ.
	// єО»к№°Ає ѕрБ¦іЄ АЪµї ГЯ°Ў.
	bool	PullOut(LPCHARACTER ch, TItemPos DestCell, IN OUT LPITEM& pItem, LPITEM pExtractor = NULL);

	// їлИҐј® ѕч±Ч·№АМµе ЗФјц
	bool	DoRefineGrade(LPCHARACTER ch, TItemPos (&aItemPoses)[DRAGON_SOUL_REFINE_GRID_SIZE]);
	bool	DoRefineStep(LPCHARACTER ch, TItemPos (&aItemPoses)[DRAGON_SOUL_REFINE_GRID_SIZE]);
	bool	DoRefineStrength(LPCHARACTER ch, TItemPos (&aItemPoses)[DRAGON_SOUL_REFINE_GRID_SIZE]);
	
	bool	DragonSoulItemInitialize(LPITEM pItem);

	bool	IsTimeLeftDragonSoul(LPITEM pItem) const;
	int		LeftTime(LPITEM pItem) const;
	bool	ActivateDragonSoul(LPITEM pItem);
	bool	DeactivateDragonSoul(LPITEM pItem, bool bSkipRefreshOwnerActiveState = false);
	bool	IsActiveDragonSoul(LPITEM pItem) const;
private:
	void	SendRefineResultPacket(LPCHARACTER ch, BYTE bSubHeader, const TItemPos& pos);

	// ДіёЇЕНАЗ їлИҐј® µ¦А» »мЖмєё°н, И°јєИ­ µИ їлИҐј®АМ ѕшґЩёй, ДіёЇЕНАЗ їлИҐј® И°јє »уЕВё¦ off ЅГЕ°ґВ ЗФјц.
	void	RefreshDragonSoulState(LPCHARACTER ch);

	DWORD	MakeDragonSoulVnum(BYTE bType, BYTE grade, BYTE step, BYTE refine);
	bool	PutAttributes(LPITEM pDS);
	bool	RefreshItemAttributes(LPITEM pItem);

	DragonSoulTable*	m_pTable;
};

#endif
