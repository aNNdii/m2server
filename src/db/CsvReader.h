#ifndef __CSVFILE_H__
#define __CSVFILE_H__

#include <string>
#include <vector>

#if _MSC_VER
    #include <hash_map>
#else
    #include <map>
#endif

////////////////////////////////////////////////////////////////////////////////
/// \class cCsvAlias
/// \brief CSV ЖДАПА» јцБ¤ЗЯА» ¶§ №Я»эЗПґВ АОµ¦Ѕє №®Б¦ё¦ БЩАМ±в А§ЗС 
/// є°ён °ґГј.
///
/// ї№ё¦ µйѕо 0№ш ДГ·іАМ AїЎ °ьЗС і»їлА» ЖчЗФЗП°н, 1№ш ДГ·іАМ BїЎ °ьЗС і»їлА» 
/// ЖчЗФЗП°н АЦѕъґВµҐ...
///
/// <pre>
/// int a = row.AsInt(0);
/// int b = row.AsInt(1);
/// </pre>
///
/// ±Ч »зАМїЎ CїЎ °ьЗС і»їлА» ЖчЗФЗПґВ ДГ·іАМ іўѕоµз °жїм, ЗПµеДЪµщµЗѕо АЦґВ 
/// 1№шА» ГЈѕЖј­ °нГДѕЯ ЗПґВµҐ, »уґзИч їЎ·Ї°Ў №Я»эЗП±в Ѕ¬їо АЫѕчАМґЩ. 
///
/// <pre>
/// int a = row.AsInt(0);
/// int c = row.AsInt(1);
/// int b = row.AsInt(2); <-- АМ єОєРА» АПАПАМ ЅЕ°жЅбѕЯ ЗСґЩ.
/// </pre>
/// 
/// АМ єОєРА» №®АЪї­·О Гіё®ЗПёй АЇБцєёјцїЎ µйѕо°ЎґВ јц°нё¦ ѕа°ЈАМіЄё¶ БЩАП јц 
/// АЦґЩ.
////////////////////////////////////////////////////////////////////////////////

class cCsvAlias
{
private:
#if _MSC_VER
    typedef stdext::hash_map<std::string, size_t> NAME2INDEX_MAP;
    typedef stdext::hash_map<size_t, std::string> INDEX2NAME_MAP;
#else
    typedef std::map<std::string, size_t> NAME2INDEX_MAP;
    typedef std::map<size_t, std::string> INDEX2NAME_MAP;
#endif

    NAME2INDEX_MAP m_Name2Index;  ///< јї АОµ¦Ѕє ґлЅЕАё·О »зїлЗП±в А§ЗС АМё§µй
    INDEX2NAME_MAP m_Index2Name;  ///< АЯёшµИ aliasё¦ °Л»зЗП±в А§ЗС ГЯ°ЎАыАО ёК


public:
    /// \brief »эјєАЪ
    cCsvAlias() {} 

    /// \brief јТёкАЪ
    virtual ~cCsvAlias() {}


public:
    /// \brief јїА» ѕЧјјЅєЗТ ¶§, јэАЪ ґлЅЕ »зїлЗТ АМё§А» µо·ПЗСґЩ.
    void AddAlias(const char* name, size_t index);

    /// \brief ёрµз µҐАМЕНё¦ »иБ¦ЗСґЩ.
    void Destroy();

    /// \brief јэАЪ АОµ¦Ѕєё¦ АМё§Аё·О єЇИЇЗСґЩ.
    const char* operator [] (size_t index) const;

    /// \brief АМё§А» јэАЪ АОµ¦Ѕє·О єЇИЇЗСґЩ.
    size_t operator [] (const char* name) const;


private:
    /// \brief є№»з »эјєАЪ ±ЭБц
    cCsvAlias(const cCsvAlias&) {}

    /// \brief ґлАФ ї¬»кАЪ ±ЭБц
    const cCsvAlias& operator = (const cCsvAlias&) { return *this; }
};


////////////////////////////////////////////////////////////////////////////////
/// \class cCsvRow 
/// \brief CSV ЖДАПАЗ ЗС ЗаА» ДёЅ¶И­ЗС Е¬·ЎЅє
///
/// CSVАЗ ±вє» ЖчёЛАє їўјїїЎј­ єёАМґВ ЗПіЄАЗ јїА» ',' №®АЪ·О ±ёєРЗС °НАМґЩ.
/// ЗПБцёё, јї ѕИїЎ ЖЇјц №®АЪ·О ѕІАМґВ ',' №®АЪіЄ '"' №®АЪ°Ў µйѕо°Ґ °жїм, 
/// ёрѕзАМ ѕа°Ј АМ»уЗП°Ф єЇЗСґЩ. ґЩАЅАє ±Ч єЇИ­АЗ ї№АМґЩ.
/// 
/// <pre>
/// їўјїїЎј­ єёАМґВ ёрѕз | ЅЗБ¦ CSV ЖДАПїЎ µйѕо°ЎАЦґВ ёрѕз
/// ---------------------+----------------------------------------------------
/// ItemPrice            | ItemPrice
/// Item,Price           | "Item,Price"
/// Item"Price           | "Item""Price"
/// "ItemPrice"          | """ItemPrice"""
/// "Item,Price"         | """Item,Price"""
/// Item",Price          | "Item"",Price"
/// </pre>
/// 
/// АМ ї№·Ој­ ґЩАЅ°ъ °°Ає »зЗЧА» ѕЛ јц АЦґЩ.
/// - јї і»єОїЎ ',' ¶ЗґВ '"' №®АЪ°Ў µйѕо°Ґ °жїм, јї БВїмїЎ '"' №®АЪ°Ў »э±дґЩ.
/// - јї і»єОАЗ '"' №®АЪґВ 2°і·О ДЎИЇµИґЩ.
///
/// \sa cCsvFile
////////////////////////////////////////////////////////////////////////////////

class cCsvRow : public std::vector<std::string>
{
public:
    /// \brief ±вє» »эјєАЪ
    cCsvRow() {}

    /// \brief јТёкАЪ
    ~cCsvRow() {}


public:
    /// \brief ЗШґз јїАЗ µҐАМЕНё¦ int ЗьАё·О №ЭИЇЗСґЩ.
    int AsInt(size_t index) const { return atoi(at(index).c_str()); }

    /// \brief ЗШґз јїАЗ µҐАМЕНё¦ double ЗьАё·О №ЭИЇЗСґЩ.
    double AsDouble(size_t index) const { return atof(at(index).c_str()); }

    /// \brief ЗШґз јїАЗ µҐАМЕНё¦ №®АЪї­·О №ЭИЇЗСґЩ.
    const char* AsString(size_t index) const { return at(index).c_str(); }

    /// \brief ЗШґзЗПґВ АМё§АЗ јї µҐАМЕНё¦ int ЗьАё·О №ЭИЇЗСґЩ.
    int AsInt(const char* name, const cCsvAlias& alias) const {
        return atoi( at(alias[name]).c_str() ); 
    }

    /// \brief ЗШґзЗПґВ АМё§АЗ јї µҐАМЕНё¦ int ЗьАё·О №ЭИЇЗСґЩ.
    double AsDouble(const char* name, const cCsvAlias& alias) const {
        return atof( at(alias[name]).c_str() ); 
    }

    /// \brief ЗШґзЗПґВ АМё§АЗ јї µҐАМЕНё¦ №®АЪї­·О №ЭИЇЗСґЩ.
    const char* AsString(const char* name, const cCsvAlias& alias) const { 
        return at(alias[name]).c_str(); 
    }


private:
    /// \brief є№»з »эјєАЪ ±ЭБц
    cCsvRow(const cCsvRow&) {}

    /// \brief ґлАФ ї¬»кАЪ ±ЭБц
    const cCsvRow& operator = (const cCsvRow&) { return *this; }
};


////////////////////////////////////////////////////////////////////////////////
/// \class cCsvFile
/// \brief CSV(Comma Seperated Values) ЖДАПА» read/writeЗП±в А§ЗС Е¬·ЎЅє
///
/// <b>sample</b>
/// <pre>
/// cCsvFile file;
///
/// cCsvRow row1, row2, row3;
/// row1.push_back("ItemPrice");
/// row1.push_back("Item,Price");
/// row1.push_back("Item\"Price");
///
/// row2.reserve(3);
/// row2[0] = "\"ItemPrice\"";
/// row2[1] = "\"Item,Price\"";
/// row2[2] = "Item\",Price\"";
///
/// row3 = "\"ItemPrice\"\"Item,Price\"Item\",Price\"";
///
/// file.add(row1);
/// file.add(row2);
/// file.add(row3);
/// file.save("test.csv", false);
/// </pre>
///
/// \todo ЖДАПїЎј­ёё АРѕоµйАП °НАМ ѕЖґП¶у, ёЮёрё® јТЅє·ОєОЕН АРґВ ЗФјцµµ 
/// АЦѕоѕЯ ЗТ µн ЗПґЩ.
////////////////////////////////////////////////////////////////////////////////

class cCsvFile
{
private:
    typedef std::vector<cCsvRow*> ROWS;

    ROWS m_Rows; ///< За ДГ·єјЗ


public:
    /// \brief »эјєАЪ
    cCsvFile() {}

    /// \brief јТёкАЪ
    virtual ~cCsvFile() { Destroy(); }


public:
    /// \brief БцБ¤µИ АМё§АЗ CSV ЖДАПА» ·ОµеЗСґЩ.
    bool Load(const char* fileName, const char seperator=',', const char quote='"');

    /// \brief °ЎБц°н АЦґВ і»їлА» CSV ЖДАПїЎґЩ АъАеЗСґЩ.
    bool Save(const char* fileName, bool append=false, char seperator=',', char quote='"') const;

    /// \brief ёрµз µҐАМЕНё¦ ёЮёрё®їЎј­ »иБ¦ЗСґЩ.
    void Destroy();

    /// \brief ЗШґзЗПґВ АОµ¦ЅєАЗ ЗаА» №ЭИЇЗСґЩ.
    cCsvRow* operator [] (size_t index);

    /// \brief ЗШґзЗПґВ АОµ¦ЅєАЗ ЗаА» №ЭИЇЗСґЩ.
    const cCsvRow* operator [] (size_t index) const;

    /// \brief ЗаАЗ °№јцё¦ №ЭИЇЗСґЩ.
    size_t GetRowCount() const { return m_Rows.size(); }


private:
    /// \brief є№»з »эјєАЪ ±ЭБц
    cCsvFile(const cCsvFile&) {}

    /// \brief ґлАФ ї¬»кАЪ ±ЭБц
    const cCsvFile& operator = (const cCsvFile&) { return *this; }
};


////////////////////////////////////////////////////////////////////////////////
/// \class cCsvTable
/// \brief CSV ЖДАПА» АМїлЗШ ЕЧАМєн µҐАМЕНё¦ ·ОµеЗПґВ °жїм°Ў ё№АєµҐ, АМ Е¬·ЎЅєґВ 
/// ±Ч АЫѕчА» Б» ґх Ѕ±°Ф ЗП±в А§ЗШ ёёµз АЇЖїё®Жј Е¬·ЎЅєґЩ.
///
/// CSV ЖДАПА» ·ОµеЗПґВ °жїм, јэАЪё¦ АМїлЗШ јїА» ѕЧјјЅєЗШѕЯ ЗПґВµҐ, CSV 
/// ЖДАПАЗ ЖчёЛАМ №ЩІоґВ °жїм, АМ јэАЪµйА» єЇ°жЗШБаѕЯЗСґЩ. АМ АЫѕчАМ ІП 
/// ЅЕ°ж БэБЯА» їд±ёЗПґВ µҐґЩ°Ў, їЎ·Ї°Ў №Я»эЗП±в Ѕ±ґЩ. ±Ч·Ї№З·О јэАЪ·О 
/// ѕЧјјЅєЗП±вєёґЩґВ №®АЪї­·О ѕЧјјЅєЗПґВ °НАМ ѕа°Ј ґАё®Бцёё іґґЩ°н ЗТ јц АЦґЩ.
///
/// <b>sample</b>
/// <pre>
/// cCsvTable table;
///
/// table.alias(0, "ItemClass");
/// table.alias(1, "ItemType");
///
/// if (table.load("test.csv"))
/// {
///     while (table.next())
///     {
///         std::string item_class = table.AsString("ItemClass");
///         int         item_type  = table.AsInt("ItemType"); 
///     }
/// }
/// </pre>
////////////////////////////////////////////////////////////////////////////////

class cCsvTable
{
public :
    cCsvFile  m_File;   ///< CSV ЖДАП °ґГј
private:
    cCsvAlias m_Alias;  ///< №®АЪї­А» јї АОµ¦Ѕє·О єЇИЇЗП±в А§ЗС °ґГј
    int       m_CurRow; ///< ЗцАз ИѕґЬ БЯАО За №шИЈ


public:
    /// \brief »эјєАЪ
    cCsvTable();

    /// \brief јТёкАЪ
    virtual ~cCsvTable();


public:
    /// \brief БцБ¤µИ АМё§АЗ CSV ЖДАПА» ·ОµеЗСґЩ.
    bool Load(const char* fileName, const char seperator=',', const char quote='"');

    /// \brief јїА» ѕЧјјЅєЗТ ¶§, јэАЪ ґлЅЕ »зїлЗТ АМё§А» µо·ПЗСґЩ.
    void AddAlias(const char* name, size_t index) { m_Alias.AddAlias(name, index); }

    /// \brief ґЩАЅ ЗаАё·О іСѕо°ЈґЩ.
    bool Next();

    /// \brief ЗцАз ЗаАЗ јї јэАЪё¦ №ЭИЇЗСґЩ.
    size_t ColCount() const;

    /// \brief АОµ¦Ѕєё¦ АМїлЗШ int ЗьАё·О јї°ЄА» №ЭИЇЗСґЩ.
    int AsInt(size_t index) const;

    /// \brief АОµ¦Ѕєё¦ АМїлЗШ double ЗьАё·О јї°ЄА» №ЭИЇЗСґЩ.
    double AsDouble(size_t index) const;

    /// \brief АОµ¦Ѕєё¦ АМїлЗШ std::string ЗьАё·О јї°ЄА» №ЭИЇЗСґЩ.
    const char* AsStringByIndex(size_t index) const;

    /// \brief јї АМё§А» АМїлЗШ int ЗьАё·О јї°ЄА» №ЭИЇЗСґЩ.
    int AsInt(const char* name) const { return AsInt(m_Alias[name]); }

    /// \brief јї АМё§А» АМїлЗШ double ЗьАё·О јї°ЄА» №ЭИЇЗСґЩ.
    double AsDouble(const char* name) const { return AsDouble(m_Alias[name]); }

    /// \brief јї АМё§А» АМїлЗШ std::string ЗьАё·О јї°ЄА» №ЭИЇЗСґЩ.
    const char* AsString(const char* name) const { return AsStringByIndex(m_Alias[name]); }

    /// \brief aliasё¦ ЖчЗФЗШ ёрµз µҐАМЕНё¦ »иБ¦ЗСґЩ.
    void Destroy();


private:
    /// \brief ЗцАз ЗаА» №ЭИЇЗСґЩ.
    const cCsvRow* const CurRow() const;

    /// \brief є№»з »эјєАЪ ±ЭБц
    cCsvTable(const cCsvTable&) {}

    /// \brief ґлАФ ї¬»кАЪ ±ЭБц
    const cCsvTable& operator = (const cCsvTable&) { return *this; }
};

#endif //__CSVFILE_H__
