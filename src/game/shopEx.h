#ifndef __INC_METIN_II_GAME_SHOP_SECONDARY_COIN_H__
#define __INC_METIN_II_GAME_SHOP_SECONDARY_COIN_H__
#include "typedef.h"
#include "shop.h"

struct SShopTable;
typedef struct SShopTableEx : SShopTable
{
	std::string name;
	EShopCoinType coinType;
} TShopTableEx;

class CGroupNode;

typedef std::vector <TShopTableEx> ShopTableExVector;

// И®Ае shop.
// ёнµµАьА» И­Жу·О ѕµ јц АЦ°н, ѕЖАМЕЫА» ї©·Ї ЕЗїЎ іЄґІ №иДЎЗТ јц АЦґЩ.
// ґЬ, pc јҐАє ±ёЗцЗПБц ѕКАЅ.
// Е¬¶уїН ЕлЅЕЗТ ¶§їЎ ЕЗАє pos 45 ґЬА§·О ±ёєР.
// ±вБё јҐАЗ m_itemVectorАє »зїлЗПБц ѕКґВґЩ.
class CShopEx: public CShop
{
public:
	bool			Create(DWORD dwVnum, DWORD dwNPCVnum);
	bool			AddShopTable(TShopTableEx& shopTable);

	virtual bool	AddGuest(LPCHARACTER ch,DWORD owner_vid, bool bOtherEmpire);
	virtual void	SetPCShop(LPCHARACTER ch) { return; }
	virtual bool	IsPCShop() { return false; }
	virtual int		Buy(LPCHARACTER ch, BYTE pos);
	virtual bool	IsSellingItem(DWORD itemID) { return false; }
	
	size_t			GetTabCount() { return m_vec_shopTabs.size(); }
private:
	ShopTableExVector m_vec_shopTabs;
};
typedef CShopEx* LPSHOPEX;

#endif
