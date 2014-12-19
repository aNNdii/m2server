#ifndef __INC_METIN_II_GAME_SHOP_H__
#define __INC_METIN_II_GAME_SHOP_H__

enum
{
	SHOP_MAX_DISTANCE = 1000
};

class CGrid;

/* ---------------------------------------------------------------------------------- */
class CShop
{
	public:
		typedef struct shop_item
		{
			DWORD	vnum;		// ѕЖАМЕЫ №шИЈ
			long	price;		// °Ў°Э
			BYTE	count;		// ѕЖАМЕЫ °іјц

			LPITEM	pkItem;
			int		itemid;		// ѕЖАМЕЫ °нАЇѕЖАМµр

			shop_item()
			{
				vnum = 0;
				price = 0;
				count = 0;
				itemid = 0;
				pkItem = NULL;
			}
		} SHOP_ITEM;

		CShop();
		~CShop();

		bool	Create(DWORD dwVnum, DWORD dwNPCVnum, TShopItemTable * pItemTable);
		void	SetShopItems(TShopItemTable * pItemTable, BYTE bItemCount);

		virtual void	SetPCShop(LPCHARACTER ch);
		virtual bool	IsPCShop()	{ return m_pkPC ? true : false; }

		// °ФЅєЖ® ГЯ°Ў/»иБ¦
		virtual bool	AddGuest(LPCHARACTER ch,DWORD owner_vid, bool bOtherEmpire);
		void	RemoveGuest(LPCHARACTER ch);

		// №°°З ±ёАФ
		virtual int	Buy(LPCHARACTER ch, BYTE pos);

		// °ФЅєЖ®їЎ°Ф ЖРЕ¶А» єёії
		void	BroadcastUpdateItem(BYTE pos);

		// ЖЗёЕБЯАО ѕЖАМЕЫАЗ °№јцё¦ ѕЛ·ББШґЩ.
		int		GetNumberByVnum(DWORD dwVnum);

		// ѕЖАМЕЫАМ »уБЎїЎ µо·ПµЗѕо АЦґВБц ѕЛ·ББШґЩ.
		virtual bool	IsSellingItem(DWORD itemID);

		DWORD	GetVnum() { return m_dwVnum; }
		DWORD	GetNPCVnum() { return m_dwNPCVnum; }

	protected:
		void	Broadcast(const void * data, int bytes);

	protected:
		DWORD				m_dwVnum;
		DWORD				m_dwNPCVnum;

		CGrid *				m_pGrid;

		typedef TR1_NS::unordered_map<LPCHARACTER, bool> GuestMapType;
		GuestMapType m_map_guest;
		std::vector<SHOP_ITEM>		m_itemVector;	// АМ »уБЎїЎј­ Гл±ЮЗПґВ №°°Зµй

		LPCHARACTER			m_pkPC;
};

#endif 
