// vim:ts=8 sw=4
#ifndef __INC_DB_CACHE_H__
#define __INC_DB_CACHE_H__

#include "common/cache.h"
#include "common/auction_table.h"

class CItemCache : public cache<TPlayerItem>
{
    public:
	CItemCache();
	virtual ~CItemCache();

	void Delete();
	virtual void OnFlush();
};

class CPlayerTableCache : public cache<TPlayerTable>
{
    public:
	CPlayerTableCache();
	virtual ~CPlayerTableCache();

	virtual void OnFlush();

	DWORD GetLastUpdateTime() { return m_lastUpdateTime; }
};

// MYSHOP_PRICE_LIST
/**
 * @class	CItemPriceListTableCache
 * @brief	°іАО»уБЎАЗ ѕЖАМЕЫ °Ў°ЭБ¤єё ё®ЅєЖ®їЎ ґлЗС ДіЅГ class
 * @version	05/06/10 Bang2ni - First release.
 */
class CItemPriceListTableCache : public cache< TItemPriceListTable >
{
    public:

	/// Constructor
	/**
	 * ДіЅГ ёё·б ЅГ°ЈА» јіБ¤ЗСґЩ.
	 */
	CItemPriceListTableCache(void);

	/// ё®ЅєЖ® °»ЅЕ
	/**
	 * @param [in]	pUpdateList °»ЅЕЗТ ё®ЅєЖ®
	 *
	 * ДіЅГµИ °Ў°ЭБ¤єёё¦ °»ЅЕЗСґЩ.
	 * °Ў°ЭБ¤єё ё®ЅєЖ®°Ў °Ўµж ГЎА» °жїм ±вБёїЎ ДіЅМµИ Б¤єёµйА» µЪїЎј­ єОЕН »иБ¦ЗСґЩ.
	 */
	void	UpdateList(const TItemPriceListTable* pUpdateList);

	/// °Ў°ЭБ¤єёё¦ DB їЎ ±в·ПЗСґЩ.
	virtual void	OnFlush(void);

    private:

	static const int	s_nMinFlushSec;		///< Minimum cache expire time
};
// END_OF_MYSHOP_PRICE_LIST
#ifdef __AUCTION__

class CAuctionItemInfoCache : public cache <TAuctionItemInfo>
{
public:
	typedef TWishItemInfo value_type;
	CAuctionItemInfoCache();
	virtual ~CAuctionItemInfoCache();

	void Delete();
	virtual void OnFlush();
};

class CSaleItemInfoCache : public cache <TSaleItemInfo>
{
public:
	typedef TWishItemInfo value_type;
	CSaleItemInfoCache();
	virtual ~CSaleItemInfoCache();

	void Delete();
	virtual void OnFlush();
};

class CWishItemInfoCache : public cache <TWishItemInfo>
{
public:
	typedef TWishItemInfo value_type;
	CWishItemInfoCache();
	virtual ~CWishItemInfoCache();

	void Delete();
	virtual void OnFlush();
};
#endif
#endif
