#ifndef __INC_ITEM_MANAGER__
#define __INC_ITEM_MANAGER__

#ifdef M2_USE_POOL
#include "pool.h"
#endif

struct CSpecialAttrInfo
{
	CSpecialAttrInfo(DWORD _apply_type, DWORD _apply_value)
		: apply_type(_apply_type), apply_value(_apply_value)
	{}
	DWORD apply_type;
	DWORD apply_value;

};

typedef std::vector<CSpecialAttrInfo> SpecialAttrInfoVector;

// special_item_group.txtїЎј­ Б¤АЗЗПґВ јУјє ±Ч·м
// type attr·О ј±ѕрЗТ јц АЦґЩ.
// АМ јУјє ±Ч·мА» АМїлЗТ јц АЦґВ °НАє special_item_group.txtїЎј­ Special typeАё·О Б¤АЗµИ ±Ч·мїЎ јУЗС UNIQUE ITEMАМґЩ.
class CSpecialAttrGroup
{
public:
	CSpecialAttrGroup(DWORD vnum)
		: m_dwVnum(vnum)
	{}

	DWORD m_dwVnum;
	std::string	m_stEffectFileName;
	SpecialAttrInfoVector m_vecAttrs;
};

struct CSpecialItemInfo
{
	DWORD vnum;
	int count;
	int rare;

	CSpecialItemInfo(DWORD _vnum, int _count, int _rare)
		: vnum(_vnum), count(_count), rare(_rare)
	{}
};

typedef std::vector<CSpecialItemInfo> ItemsVector;

class CSpecialItemGroup
{
	public:
		enum EGiveType
		{
			NONE,
			GOLD,
			EXP,
			MOB,
			SLOW,
			DRAIN_HP,
			POISON,
			MOB_GROUP,
		};

		// QUEST ЕёАФАє ДщЅєЖ® ЅєЕ©ёіЖ®їЎј­ vnum.sig_useё¦ »зїлЗТ јц АЦґВ ±Ч·мАМґЩ.
		//		ґЬ, АМ ±Ч·мїЎ µйѕо°Ў±в А§ЗШј­ґВ ITEM АЪГјАЗ TYPEАМ QUESTї©ѕЯ ЗСґЩ.
		// SPECIAL ЕёАФАє idx, item_vnum, attr_vnumА» АФ·ВЗСґЩ. attr_vnumАє А§їЎ CSpecialAttrGroupАЗ VnumАМґЩ.
		//		АМ ±Ч·мїЎ µйѕоАЦґВ ѕЖАМЕЫАє °°АМ ВшїлЗТ јц ѕшґЩ.
		enum ESIGType { NORMAL, PCT, QUEST, SPECIAL };

		CSpecialItemGroup(DWORD vnum, BYTE type=0)
			: m_dwVnum(vnum), m_bType(type)
			{}

		void AddItem(DWORD vnum, int count, int prob, int rare)
		{
			if (!prob)
				return;
			if (!m_vecProbs.empty())
				prob += m_vecProbs.back();
			m_vecProbs.push_back(prob);
			m_vecItems.push_back(CSpecialItemInfo(vnum, count, rare));
		}

		bool IsEmpty() const
		{
			return m_vecProbs.empty();
		}

		// Type Multi, Бп m_bType == PCT АО °жїм,
		// И®·ьА» ґхЗШ°ЎБц ѕК°н, µ¶ёіАыАё·О °и»кЗПї© ѕЖАМЕЫА» »эјєЗСґЩ.
		// µы¶уј­ ї©·Ї °іАЗ ѕЖАМЕЫАМ »эјєµЙ јц АЦґЩ.
		// by rtsummit
		int GetMultiIndex(std::vector <int> &idx_vec) const
		{
			idx_vec.clear();
			if (m_bType == PCT)
			{
				int count = 0;
				if (number(1,100) <= m_vecProbs[0])
				{
					idx_vec.push_back(0);
					count++;
				}
				for (uint i = 1; i < m_vecProbs.size(); i++)
				{
					if (number(1,100) <= m_vecProbs[i] - m_vecProbs[i-1])
					{
						idx_vec.push_back(i);
						count++;
					}
				}
				return count;
			}
			else
			{
				idx_vec.push_back(GetOneIndex());
				return 1;
			}
		}

		int GetOneIndex() const
		{
			int n = number(1, m_vecProbs.back());
			std::vector<int>::const_iterator it = lower_bound(m_vecProbs.begin(), m_vecProbs.end(), n);
			return std::distance(m_vecProbs.begin(), it);
		}

		int GetVnum(int idx) const
		{
			return m_vecItems[idx].vnum;
		}

		int GetCount(int idx) const
		{
			return m_vecItems[idx].count;
		}

		int GetRarePct(int idx) const
		{
			return m_vecItems[idx].rare;
		}

		bool Contains(DWORD dwVnum) const
		{
			for (DWORD i = 0; i < m_vecItems.size(); i++)
			{
				if (m_vecItems[i].vnum == dwVnum)
					return true;
			}
			return false;
		}
		
		// GroupАЗ TypeАМ SpecialАО °жїмїЎ
		// dwVnumїЎ ёЕДЄµЗґВ AttrVnumА» returnЗШБШґЩ.
		DWORD GetAttrVnum(DWORD dwVnum) const
		{
			if (CSpecialItemGroup::SPECIAL != m_bType)
				return 0;
			for (ItemsVector::const_iterator it = m_vecItems.begin(); it != m_vecItems.end(); it++)
			{
				if (it->vnum == dwVnum)
				{
					return it->count;
				}
			}
			return 0;
		}

		// GroupАЗ Sizeё¦ returnЗШБШґЩ.
		int GetGroupSize() const
		{
			return m_vecProbs.size();
		}

		DWORD m_dwVnum;
		BYTE	m_bType;
		std::vector<int> m_vecProbs;
		ItemsVector m_vecItems; // vnum, count
};

struct SMobItemGroupInfo
{
	DWORD dwItemVnum;
	int iCount;
	int iRarePct;

	SMobItemGroupInfo(DWORD dwItemVnum, int iCount, int iRarePct)
		: dwItemVnum(dwItemVnum),
		iCount(iCount),
		iRarePct(iRarePct)
	{
	}
};

typedef std::vector<int> ProbsVector;
typedef std::vector<SMobItemGroupInfo> ItemGroupInfoVector;

class CMobItemGroup
{
	public:
		CMobItemGroup(DWORD dwMobVnum, int iKillDrop, const std::string& r_stName)
			:
			m_dwMobVnum(dwMobVnum),
		m_iKillDrop(iKillDrop),
		m_stName(r_stName)
		{
		}

		int GetKillPerDrop() const
		{
			return m_iKillDrop;
		}

		void AddItem(DWORD dwItemVnum, int iCount, int iPartPct, int iRarePct)
		{
			if (!m_vecProbs.empty())
				iPartPct += m_vecProbs.back();
			m_vecProbs.push_back(iPartPct);
			m_vecItems.push_back(SMobItemGroupInfo(dwItemVnum, iCount, iRarePct));
		}

		// MOB_DROP_ITEM_BUG_FIX
		bool IsEmpty() const
		{
			return m_vecProbs.empty();
		}

		int GetOneIndex() const
		{
			int n = number(1, m_vecProbs.back());
			ProbsVector::const_iterator it = lower_bound(m_vecProbs.begin(), m_vecProbs.end(), n);
			return std::distance(m_vecProbs.begin(), it);
		}
		// END_OF_MOB_DROP_ITEM_BUG_FIX

		const SMobItemGroupInfo& GetOne() const
		{
			return m_vecItems[GetOneIndex()];
		}

	private:
		DWORD m_dwMobVnum;
		int m_iKillDrop;
		std::string m_stName;
		ProbsVector m_vecProbs;
		ItemGroupInfoVector m_vecItems;
};

struct SDropItemGroupInfo
{
	DWORD	dwVnum;
	DWORD	dwPct;
	int	iCount;

	SDropItemGroupInfo(DWORD dwVnum, DWORD dwPct, int iCount)
		: dwVnum(dwVnum), dwPct(dwPct), iCount(iCount)
	{}
};

typedef std::vector<SDropItemGroupInfo> DropItemGroupInfoVector;

class CDropItemGroup
{
	public:
	CDropItemGroup(DWORD dwVnum, DWORD dwMobVnum, const std::string& r_stName)
		:
		m_dwVnum(dwVnum),
	m_dwMobVnum(dwMobVnum),
	m_stName(r_stName)
	{
	}

	const DropItemGroupInfoVector& GetVector()
	{
		return m_vec_items;
	}

	void AddItem(DWORD dwItemVnum, DWORD dwPct, int iCount)
	{
		m_vec_items.push_back(SDropItemGroupInfo(dwItemVnum, dwPct, iCount));
	}

	private:
	DWORD m_dwVnum;
	DWORD m_dwMobVnum;
	std::string m_stName;
	DropItemGroupInfoVector m_vec_items;
};

struct SLevelItemGroupInfo
{
	DWORD dwVNum;
	DWORD dwPct;
	int iCount;

	SLevelItemGroupInfo(DWORD dwVnum, DWORD dwPct, int iCount)
		: dwVNum(dwVnum), dwPct(dwPct), iCount(iCount)
	{ }
};

typedef std::vector<SLevelItemGroupInfo> LevelItemGroupInfoVector;

class CLevelItemGroup
{
	private :
		DWORD m_dwLevelLimit;
		std::string m_stName;
		LevelItemGroupInfoVector m_vec_items;

	public :
		CLevelItemGroup(DWORD dwLevelLimit)
			: m_dwLevelLimit(dwLevelLimit)
		{}

		DWORD GetLevelLimit() { return m_dwLevelLimit; }

		void AddItem(DWORD dwItemVnum, DWORD dwPct, int iCount)
		{
			m_vec_items.push_back(SLevelItemGroupInfo(dwItemVnum, dwPct, iCount));
		}

		const LevelItemGroupInfoVector& GetVector()
		{
			return m_vec_items;
		}
};

struct SThiefGroupInfo
{
	DWORD	dwVnum;
	DWORD	dwPct;
	int	iCount;

	SThiefGroupInfo(DWORD dwVnum, DWORD dwPct, int iCount)
		: dwVnum(dwVnum), dwPct(dwPct), iCount(iCount)
	{}
};

typedef std::vector<SThiefGroupInfo> ItemThiefGroupInfoVector;

class CBuyerThiefGlovesItemGroup
{
	public:
	CBuyerThiefGlovesItemGroup(DWORD dwVnum, DWORD dwMobVnum, const std::string& r_stName)
		:
		m_dwVnum(dwVnum),
	m_dwMobVnum(dwMobVnum),
	m_stName(r_stName)
	{
	}

	const ItemThiefGroupInfoVector& GetVector()
	{
		return m_vec_items;
	}

	void AddItem(DWORD dwItemVnum, DWORD dwPct, int iCount)
	{
		m_vec_items.push_back(SThiefGroupInfo(dwItemVnum, dwPct, iCount));
	}

	private:
	DWORD m_dwVnum;
	DWORD m_dwMobVnum;
	std::string m_stName;
	ItemThiefGroupInfoVector m_vec_items;
};

class ITEM;

typedef std::map<DWORD, int> ItemToSpecialGroupMap;
typedef std::map<DWORD, CDropItemGroup*> pkDropItemGroupMap;
typedef std::map<DWORD, CLevelItemGroup*> pkLevelItemGroupMap;
typedef std::map<DWORD, CMobItemGroup*> pkMobItemGroupMap;
typedef std::map<DWORD, CBuyerThiefGlovesItemGroup*> pkGloveItemGroupMap;
typedef std::map<DWORD, DWORD> EtcItemDropProbMap;
typedef std::map<DWORD, DWORD> ItemRefineFromMap;
typedef std::map<DWORD, CSpecialItemGroup*> SpecialItemGroupMap;
typedef std::map<DWORD, CSpecialAttrGroup*> SpecialAttrGroupMap;
typedef std::map<DWORD, LPITEM> ItemMap;

class ITEM_MANAGER : public singleton<ITEM_MANAGER>
{
	public:
		ITEM_MANAGER();
		virtual ~ITEM_MANAGER();

		bool                    Initialize(TItemTable * table, int size);
		void			Destroy();
		void			Update();	// ёЕ ·зЗБё¶ґЩ єОёҐґЩ.
		void			GracefulShutdown();

		DWORD			GetNewID();
		bool			SetMaxItemID(TItemIDRangeTable range); // ГЦґл °нАЇ ѕЖАМµрё¦ БцБ¤
		bool			SetMaxSpareItemID(TItemIDRangeTable range);

		// DelayedSave: ѕо¶°ЗС ·зЖѕ і»їЎј­ АъАеА» ЗШѕЯ ЗТ БюА» ё№АМ ЗПёй АъАе
		// Дхё®°Ў іК№« ё№ѕЖБц№З·О "АъАеА» ЗСґЩ" ¶у°н ЗҐЅГёё ЗШµО°н Аб±с
		// (ї№: 1 frame) ИДїЎ АъАеЅГЕІґЩ.
		void			DelayedSave(LPITEM item);
		void			FlushDelayedSave(LPITEM item); // Delayed ё®ЅєЖ®їЎ АЦґЩёй Бцїм°н АъАеЗСґЩ. Іч±и Гіё®ЅГ »зїл µК.
		void			SaveSingleItem(LPITEM item);

		LPITEM                  CreateItem(DWORD vnum, DWORD count = 1, DWORD dwID = 0, bool bTryMagic = false, int iRarePct = -1, bool bSkipSave = false);
#ifndef DEBUG_ALLOC
		void DestroyItem(LPITEM item);
#else
		void DestroyItem(LPITEM item, const char* file, size_t line);
#endif
		void			RemoveItem(LPITEM item, const char * c_pszReason=NULL); // »зїлАЪ·О єОЕН ѕЖАМЕЫА» Б¦°Е

		LPITEM			Find(DWORD id);
		LPITEM                  FindByVID(DWORD vid);
		TItemTable *            GetTable(DWORD vnum);
		bool			GetVnum(const char * c_pszName, DWORD & r_dwVnum);
		bool			GetVnumByOriginalName(const char * c_pszName, DWORD & r_dwVnum);

		bool			GetDropPct(LPCHARACTER pkChr, LPCHARACTER pkKiller, OUT int& iDeltaPercent, OUT int& iRandRange);
		bool			CreateDropItem(LPCHARACTER pkChr, LPCHARACTER pkKiller, std::vector<LPITEM> & vec_item);

		bool			ReadCommonDropItemFile(const char * c_pszFileName);
		bool			ReadEtcDropItemFile(const char * c_pszFileName);
		bool			ReadDropItemGroup(const char * c_pszFileName);
		bool			ReadMonsterDropItemGroup(const char * c_pszFileName);
		bool			ReadSpecialDropItemFile(const char * c_pszFileName);
		
		// convert name -> vnum special_item_group.txt
		bool			ConvSpecialDropItemFile();
		// convert name -> vnum special_item_group.txt

		DWORD			GetRefineFromVnum(DWORD dwVnum);

		static void		CopyAllAttrTo(LPITEM pkOldItem, LPITEM pkNewItem);		// pkNewItemАё·О ёрµз јУјє°ъ јТДП °ЄµйА» ёс»зЗПґВ ЗФјц.


		const CSpecialItemGroup* GetSpecialItemGroup(DWORD dwVnum);
		const CSpecialAttrGroup* GetSpecialAttrGroup(DWORD dwVnum);

		const std::vector<TItemTable> & GetTable() { return m_vec_prototype; }

		// CHECK_UNIQUE_GROUP
		int			GetSpecialGroupFromItem(DWORD dwVnum) const { ItemToSpecialGroupMap::const_iterator it = m_ItemToSpecialGroup.find(dwVnum); return (it == m_ItemToSpecialGroup.end()) ? 0 : it->second; }
		// END_OF_CHECK_UNIQUE_GROUP

	protected:
		int                     RealNumber(DWORD vnum);
		void			CreateQuestDropItem(LPCHARACTER pkChr, LPCHARACTER pkKiller, std::vector<LPITEM> & vec_item, int iDeltaPercent, int iRandRange);

	protected:
		typedef std::map<DWORD, LPITEM> ITEM_VID_MAP;		

		std::vector<TItemTable>		m_vec_prototype;
		std::vector<TItemTable*> m_vec_item_vnum_range_info;
		ItemRefineFromMap		m_map_ItemRefineFrom;
		int				m_iTopOfTable;

		ITEM_VID_MAP			m_VIDMap;			///< m_dwVIDCount АЗ °ЄґЬА§·О ѕЖАМЕЫА» АъАеЗСґЩ.
		DWORD				m_dwVIDCount;			///< АМіај® VID°Ў ѕЖґП¶у ±ЧіЙ ЗБ·ОјјЅє ґЬА§ АЇґПЕ© №шИЈґЩ.
		DWORD				m_dwCurrentID;
		TItemIDRangeTable	m_ItemIDRange;
		TItemIDRangeTable	m_ItemIDSpareRange;

		TR1_NS::unordered_set<LPITEM> m_set_pkItemForDelayedSave;
		ItemMap		m_map_pkItemByID;
		EtcItemDropProbMap		m_map_dwEtcItemDropProb;
		pkDropItemGroupMap m_map_pkDropItemGroup;
		SpecialItemGroupMap m_map_pkSpecialItemGroup;
		SpecialItemGroupMap m_map_pkQuestItemGroup;
		SpecialAttrGroupMap m_map_pkSpecialAttrGroup;
		pkMobItemGroupMap m_map_pkMobItemGroup;
		pkLevelItemGroupMap		m_map_pkLevelItemGroup;
		pkGloveItemGroupMap m_map_pkGloveItemGroup;

		// CHECK_UNIQUE_GROUP
		ItemToSpecialGroupMap		m_ItemToSpecialGroup;
		// END_OF_CHECK_UNIQUE_GROUP
	
	private:
		// µ¶АПїЎј­ ±вБё ДіЅГ ѕЖАМЕЫ°ъ °°Бцёё, ±іИЇ °ЎґЙЗС ДіЅГ ѕЖАМЕЫА» ёёµзґЩ°н ЗПї©,
		// їАё®БціО ѕЖАМЕЫїЎ ±іИЇ ±ЭБц ЗГ·Ў±Чёё »иБ¦ЗС »х·Оїо ѕЖАМЕЫµйА» ёёµйѕо,
		// »х·Оїо ѕЖАМЕЫ ґлїЄА» ЗТґзЗПїґґЩ.
		// №®Б¦ґВ »х·Оїо ѕЖАМЕЫµµ їАё®БціО ѕЖАМЕЫ°ъ °°Ає Иї°ъё¦ і»ѕЯЗПґВµҐ,
		// ј­№ц°З, Е¬¶у°З, vnum ±в№ЭАё·О µЗѕоАЦѕо
		// »х·Оїо vnumА» БЛґЩ ј­№цїЎ »х·О ґЩ №ЪѕЖѕЯЗПґВ ѕИЕё±оїо »уИІїЎ ёВґкѕТґЩ.
		// ±Ч·Ўј­ »х vnumАЗ ѕЖАМЕЫАМёй, ј­№цїЎј­ µ№ѕЖ°Ґ ¶§ґВ їАё®БціО ѕЖАМЕЫ vnumАё·О №ЩІгј­ µ№°н ЗП°н,
		// АъАеЗТ ¶§їЎ є»·Ў vnumАё·О №ЩІгБЦµµ·П ЗСґЩ.
		// АМё¦ А§ЗШ їАё®БціО vnum°ъ »х·Оїо vnumА» ї¬°бЅГДСБЦґВ ёКА» ёёµк.
		typedef std::map <DWORD, DWORD> TMapDW2DW;
		TMapDW2DW	m_map_new_to_ori;

	public:	
		DWORD	GetMaskVnum(DWORD dwVnum);
		std::map<DWORD, TItemTable>  m_map_vid;
		std::map<DWORD, TItemTable>&  GetVIDMap() { return m_map_vid; }
		std::vector<TItemTable>& GetVecProto() { return m_vec_prototype; }	
		
		const static int MAX_NORM_ATTR_NUM = 5;
		const static int MAX_RARE_ATTR_NUM = 2;
		bool ReadItemVnumMaskTable(const char * c_pszFileName);
	private:
#ifdef M2_USE_POOL
		ObjectPool<CItem> pool_;
#endif
};

#ifndef DEBUG_ALLOC
#define M2_DESTROY_ITEM(ptr) ITEM_MANAGER::instance().DestroyItem(ptr)
#else
#define M2_DESTROY_ITEM(ptr) ITEM_MANAGER::instance().DestroyItem(ptr, __FILE__, __LINE__)
#endif

#endif
