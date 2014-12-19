#include "stdafx.h"
#include "CsvReader.h"
#include <fstream>
#include <algorithm>

#ifndef Assert
    #include <assert.h>
    #define Assert assert
    #define LogToFile (void)(0);
#endif

namespace
{
    /// ЖДЅМїл state ї­°Е°Є
    enum ParseState
    {
        STATE_NORMAL = 0, ///< АП№Э »уЕВ
        STATE_QUOTE       ///< µыїИЗҐ µЪАЗ »уЕВ
    };

    /// №®АЪї­ БВїмАЗ °ш№йА» Б¦°ЕЗШј­ №ЭИЇЗСґЩ.
    std::string Trim(std::string str)
    {
        str = str.erase(str.find_last_not_of(" \t\r\n") + 1);
        str = str.erase(0, str.find_first_not_of(" \t\r\n"));
        return str;
    }

    /// \brief БЦѕоБш №®АеїЎ АЦґВ ѕЛЖДєЄА» ёрµО јТ№®АЪ·О №ЩІЫґЩ.
    std::string Lower(std::string original)
    {
        std::transform(original.begin(), original.end(), original.begin(), tolower);
        return original;
    }
}

////////////////////////////////////////////////////////////////////////////////
/// \brief јїА» ѕЧјјЅєЗТ ¶§, јэАЪ ґлЅЕ »зїлЗТ АМё§А» µо·ПЗСґЩ.
/// \param name јї АМё§
/// \param index јї АОµ¦Ѕє
////////////////////////////////////////////////////////////////////////////////
void cCsvAlias::AddAlias(const char* name, size_t index)
{
    std::string converted(Lower(name));

    Assert(m_Name2Index.find(converted) == m_Name2Index.end());
    Assert(m_Index2Name.find(index) == m_Index2Name.end());

    m_Name2Index.insert(NAME2INDEX_MAP::value_type(converted, index));
    m_Index2Name.insert(INDEX2NAME_MAP::value_type(index, name));
}

////////////////////////////////////////////////////////////////////////////////
/// \brief ёрµз µҐАМЕНё¦ »иБ¦ЗСґЩ.
////////////////////////////////////////////////////////////////////////////////
void cCsvAlias::Destroy()
{
    m_Name2Index.clear();
    m_Index2Name.clear();
}

////////////////////////////////////////////////////////////////////////////////
/// \brief јэАЪ АОµ¦Ѕєё¦ АМё§Аё·О єЇИЇЗСґЩ.
/// \param index јэАЪ АОµ¦Ѕє
/// \return const char* АМё§
////////////////////////////////////////////////////////////////////////////////
const char* cCsvAlias::operator [] (size_t index) const
{
    INDEX2NAME_MAP::const_iterator itr(m_Index2Name.find(index));
    if (itr == m_Index2Name.end())
    {
        Assert(false && "cannot find suitable conversion");
        return NULL;
    }

    return itr->second.c_str();
}

////////////////////////////////////////////////////////////////////////////////
/// \brief АМё§А» јэАЪ АОµ¦Ѕє·О єЇИЇЗСґЩ.
/// \param name АМё§
/// \return size_t јэАЪ АОµ¦Ѕє
////////////////////////////////////////////////////////////////////////////////
size_t cCsvAlias::operator [] (const char* name) const
{
    NAME2INDEX_MAP::const_iterator itr(m_Name2Index.find(Lower(name)));
    if (itr == m_Name2Index.end())
    {
        Assert(false && "cannot find suitable conversion");
        return 0;
    }

    return itr->second;
}

////////////////////////////////////////////////////////////////////////////////
/// \brief БцБ¤µИ АМё§АЗ CSV ЖДАПА» ·ОµеЗСґЩ.
/// \param fileName CSV ЖДАП АМё§
/// \param seperator ЗКµе єРё®АЪ·О »зїлЗТ ±ЫАЪ. ±вє»°ЄАє ','АМґЩ.
/// \param quote µыїИЗҐ·О »зїлЗТ ±ЫАЪ. ±вє»°ЄАє '"'АМґЩ.
/// \return bool №«»зИч ·ОµеЗЯґЩёй true, ѕЖґП¶уёй false
////////////////////////////////////////////////////////////////////////////////
bool cCsvFile::Load(const char* fileName, const char seperator, const char quote)
{
    Assert(seperator != quote);

    std::ifstream file(fileName, std::ios::in);
    if (!file) return false;

    Destroy(); // ±вБёАЗ µҐАМЕНё¦ »иБ¦

    cCsvRow* row = NULL;
    ParseState state = STATE_NORMAL;
    std::string token = "";
    char buf[2048+1] = {0,};

    while (file.good())
    {
        file.getline(buf, 2048);
        buf[sizeof(buf)-1] = 0;

        std::string line(Trim(buf));
        if (line.empty() || (state == STATE_NORMAL && line[0] == '#')) continue;
        
        std::string text  = std::string(line) + "  "; // ЖДЅМ lookahead ¶§№®їЎ єЩї©БШґЩ.
        size_t cur = 0;

        while (cur < text.size())
        {
            // ЗцАз ёрµе°Ў QUOTE ёрµеАП ¶§,
            if (state == STATE_QUOTE)
            {
                // '"' №®АЪАЗ Бѕ·щґВ µО °ЎБцАМґЩ.
                // 1. јї і»єОїЎ ЖЇјц №®АЪ°Ў АЦА» °жїм АМё¦ ѕЛё®ґВ јї БВїмАЗ °Н
                // 2. јї і»єОАЗ '"' №®АЪ°Ў '"' 2°і·О ДЎИЇµИ °Н
                // АМ БЯ Г№№шВ° °жїмАЗ БВГшїЎ АЦґВ °НАє CSV ЖДАПАМ Б¤»уАыАМ¶уёй, 
                // №«Б¶°З STATE_NORMALїЎ °Йё®°Ф µЗѕоАЦґЩ.
                // ±Ч·Ї№З·О ї©±вј­ °Йё®ґВ °НАє 1№шАЗ їмГш °жїміЄ, 2№ш °жїм »УАМґЩ.
                // 2№шАЗ °жїмїЎґВ №«Б¶°З '"' №®АЪ°Ў 2°іѕї іЄЕёі­ґЩ. ЗПБцёё 1№шАЗ
                // їмГш °жїмїЎґВ ѕЖґПґЩ. АМё¦ №ЩЕБАё·О ЗШј­ ДЪµеё¦ ВҐёй...
                if (text[cur] == quote)
                {
                    // ґЩАЅ №®АЪ°Ў '"' №®АЪ¶уёй, Бп ї¬јУµИ '"' №®АЪ¶уёй 
                    // АМґВ јї і»єОАЗ '"' №®АЪ°Ў ДЎИЇµИ °НАМґЩ.
                    if (text[cur+1] == quote)
                    {
                        token += quote;
                        ++cur;
                    }
                    // ґЩАЅ №®АЪ°Ў '"' №®АЪ°Ў ѕЖґП¶уёй 
                    // ЗцАзАЗ '"'№®АЪґВ јїАЗ іЎА» ѕЛё®ґВ №®АЪ¶у°н ЗТ јц АЦґЩ.
                    else
                    {
                        state = STATE_NORMAL;
                    }
                }
                else
                {
                    token += text[cur];
                }
            }
            // ЗцАз ёрµе°Ў NORMAL ёрµеАП ¶§,
            else if (state == STATE_NORMAL)
            {
                if (row == NULL)
                    row = new cCsvRow();

                // ',' №®АЪё¦ ёёіµґЩёй јїАЗ іЎАЗ АЗ№МЗСґЩ.
                // ЕдЕ«Аё·Ој­ јї ё®ЅєЖ®їЎґЩ°Ў БэѕоіЦ°н, ЕдЕ«А» ГК±вИ­ЗСґЩ.
                if (text[cur] == seperator)
                {
                    row->push_back(token);
                    token.clear();
                }
                // '"' №®АЪё¦ ёёіµґЩёй, QUOTE ёрµе·О АьИЇЗСґЩ.
                else if (text[cur] == quote)
                {
                    state = STATE_QUOTE;
                }
                // ґЩёҐ АП№Э №®АЪ¶уёй ЗцАз ЕдЕ«їЎґЩ°Ў µЎєЩАОґЩ.
                else
                {
                    token += text[cur];
                }
            }

            ++cur;
        }

        // ё¶Бцё· јїАє іЎїЎ ',' №®АЪ°Ў ѕш±в ¶§№®їЎ ї©±вј­ ГЯ°ЎЗШБаѕЯЗСґЩ.
        // ґЬ, ГіАЅїЎ ЖДЅМ lookahead ¶§№®їЎ єЩАО ЅєЖдАМЅє №®АЪ µО °іё¦ ¶ѕґЩ.
        if (state == STATE_NORMAL)
        {
            Assert(row != NULL);
            row->push_back(token.substr(0, token.size()-2));
            m_Rows.push_back(row);
            token.clear();
            row = NULL;
        }
        else
        {
            token = token.substr(0, token.size()-2) + "\r\n";
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////
/// \brief °ЎБц°н АЦґВ і»їлА» CSV ЖДАПїЎґЩ АъАеЗСґЩ.
/// \param fileName CSV ЖДАП АМё§
/// \param append trueАП °жїм, ±вБёАЗ ЖДАПїЎґЩ µЎєЩАОґЩ. falseАО °жїмїЎґВ 
/// ±вБёАЗ ЖДАП і»їлА» »иБ¦ЗП°н, »х·О ѕґґЩ.
/// \param seperator ЗКµе єРё®АЪ·О »зїлЗТ ±ЫАЪ. ±вє»°ЄАє ','АМґЩ.
/// \param quote µыїИЗҐ·О »зїлЗТ ±ЫАЪ. ±вє»°ЄАє '"'АМґЩ.
/// \return bool №«»зИч АъАеЗЯґЩёй true, їЎ·Ї°Ў »э±д °жїмїЎґВ false
////////////////////////////////////////////////////////////////////////////////
bool cCsvFile::Save(const char* fileName, bool append, char seperator, char quote) const
{
    Assert(seperator != quote);

    // Гв·В ёрµеїЎ µы¶у ЖДАПА» АыґзЗС ЗГ·Ў±Ч·О »эјєЗСґЩ.
    std::ofstream file;
    if (append) { file.open(fileName, std::ios::out | std::ios::app); }
    else { file.open(fileName, std::ios::out | std::ios::trunc); }

    // ЖДАПА» ї­Бц ёшЗЯґЩёй, falseё¦ ё®ЕПЗСґЩ.
    if (!file) return false;

    char special_chars[5] = { seperator, quote, '\r', '\n', 0 };
    char quote_escape_string[3] = { quote, quote, 0 };

    // ёрµз ЗаА» ИѕґЬЗПёйј­...
    for (size_t i=0; i<m_Rows.size(); i++)
    {
        const cCsvRow& row = *((*this)[i]);

        std::string line;

        // За ѕИАЗ ёрµз ЕдЕ«А» ИѕґЬЗПёйј­...
        for (size_t j=0; j<row.size(); j++)
        {
            const std::string& token = row[j];

            // АП№ЭАыАО('"' ¶ЗґВ ','ё¦ ЖчЗФЗПБц ѕКАє) 
            // ЕдЕ«АМ¶уёй ±ЧіЙ АъАеЗПёй µИґЩ.
            if (token.find_first_of(special_chars) == std::string::npos)
            {
                line += token;
            }
            // ЖЇјц№®АЪё¦ ЖчЗФЗС ЕдЕ«АМ¶уёй №®АЪї­ БВїмїЎ '"'ё¦ єЩї©БЦ°н,
            // №®АЪї­ і»єОАЗ '"'ё¦ µО °і·О ёёµйѕоБаѕЯЗСґЩ.
            else
            {
                line += quote;

                for (size_t k=0; k<token.size(); k++)
                {
                    if (token[k] == quote) line += quote_escape_string;
                    else line += token[k];
                }

                line += quote;
            }

            // ё¶Бцё· јїАМ ѕЖґП¶уёй ','ё¦ ЕдЕ«АЗ µЪїЎґЩ єЩї©БаѕЯЗСґЩ.
            if (j != row.size() - 1) { line += seperator; }
        }

        // ¶уАОА» Гв·ВЗСґЩ.
        file << line << std::endl;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////
/// \brief ёрµз µҐАМЕНё¦ ёЮёрё®їЎј­ »иБ¦ЗСґЩ.
////////////////////////////////////////////////////////////////////////////////
void cCsvFile::Destroy()
{
    for (ROWS::iterator itr(m_Rows.begin()); itr != m_Rows.end(); ++itr)
        delete *itr;

    m_Rows.clear();
}

////////////////////////////////////////////////////////////////////////////////
/// \brief ЗШґзЗПґВ АОµ¦ЅєАЗ ЗаА» №ЭИЇЗСґЩ.
/// \param index АОµ¦Ѕє
/// \return cCsvRow* ЗШґз За
////////////////////////////////////////////////////////////////////////////////
cCsvRow* cCsvFile::operator [] (size_t index)
{
    Assert(index < m_Rows.size());
    return m_Rows[index];
}

////////////////////////////////////////////////////////////////////////////////
/// \brief ЗШґзЗПґВ АОµ¦ЅєАЗ ЗаА» №ЭИЇЗСґЩ.
/// \param index АОµ¦Ѕє
/// \return const cCsvRow* ЗШґз За
////////////////////////////////////////////////////////////////////////////////
const cCsvRow* cCsvFile::operator [] (size_t index) const
{
    Assert(index < m_Rows.size());
    return m_Rows[index];
}

////////////////////////////////////////////////////////////////////////////////
/// \brief »эјєАЪ
////////////////////////////////////////////////////////////////////////////////
cCsvTable::cCsvTable()
: m_CurRow(-1)
{
}

////////////////////////////////////////////////////////////////////////////////
/// \brief јТёкАЪ
////////////////////////////////////////////////////////////////////////////////
cCsvTable::~cCsvTable()
{
}

////////////////////////////////////////////////////////////////////////////////
/// \brief БцБ¤µИ АМё§АЗ CSV ЖДАПА» ·ОµеЗСґЩ.
/// \param fileName CSV ЖДАП АМё§
/// \param seperator ЗКµе єРё®АЪ·О »зїлЗТ ±ЫАЪ. ±вє»°ЄАє ','АМґЩ.
/// \param quote µыїИЗҐ·О »зїлЗТ ±ЫАЪ. ±вє»°ЄАє '"'АМґЩ.
/// \return bool №«»зИч ·ОµеЗЯґЩёй true, ѕЖґП¶уёй false
////////////////////////////////////////////////////////////////////////////////
bool cCsvTable::Load(const char* fileName, const char seperator, const char quote)
{
    Destroy();
    return m_File.Load(fileName, seperator, quote);
}

////////////////////////////////////////////////////////////////////////////////
/// \brief ґЩАЅ ЗаАё·О іСѕо°ЈґЩ.
/// \return bool ґЩАЅ ЗаАё·О №«»зИч іСѕо°Ј °жїм trueё¦ №ЭИЇЗП°н, ґх АМ»у
/// іСѕо°Ґ ЗаАМ БёАзЗПБц ѕКґВ °жїмїЎґВ falseё¦ №ЭИЇЗСґЩ.
////////////////////////////////////////////////////////////////////////////////
bool cCsvTable::Next()
{
    // 20ѕп№ш Б¤µµ ИЈГвЗПёй їА№цЗГ·О°Ў АПѕоіЇЕЩµҐ...±¦Въ°ЪБц?
    return ++m_CurRow < (int)m_File.GetRowCount() ? true : false;
}

////////////////////////////////////////////////////////////////////////////////
/// \brief ЗцАз ЗаАЗ јї јэАЪё¦ №ЭИЇЗСґЩ.
/// \return size_t ЗцАз ЗаАЗ јї јэАЪ
////////////////////////////////////////////////////////////////////////////////
size_t cCsvTable::ColCount() const
{
    return CurRow()->size();
}

////////////////////////////////////////////////////////////////////////////////
/// \brief АОµ¦Ѕєё¦ АМїлЗШ int ЗьАё·О јї °ЄА» №ЭИЇЗСґЩ.
/// \param index јї АОµ¦Ѕє
/// \return int јї °Є
////////////////////////////////////////////////////////////////////////////////
int cCsvTable::AsInt(size_t index) const
{
    const cCsvRow* const row = CurRow();
    Assert(row);
    Assert(index < row->size());
    return row->AsInt(index);
}

////////////////////////////////////////////////////////////////////////////////
/// \brief АОµ¦Ѕєё¦ АМїлЗШ double ЗьАё·О јї °ЄА» №ЭИЇЗСґЩ.
/// \param index јї АОµ¦Ѕє
/// \return double јї °Є
////////////////////////////////////////////////////////////////////////////////
double cCsvTable::AsDouble(size_t index) const
{
    const cCsvRow* const row = CurRow();
    Assert(row);
    Assert(index < row->size());
    return row->AsDouble(index);
}

////////////////////////////////////////////////////////////////////////////////
/// \brief АОµ¦Ѕєё¦ АМїлЗШ std::string ЗьАё·О јї °ЄА» №ЭИЇЗСґЩ.
/// \param index јї АОµ¦Ѕє
/// \return const char* јї °Є
////////////////////////////////////////////////////////////////////////////////
const char* cCsvTable::AsStringByIndex(size_t index) const
{
    const cCsvRow* const row = CurRow();
    Assert(row);
    Assert(index < row->size());
    return row->AsString(index);
}

////////////////////////////////////////////////////////////////////////////////
/// \brief aliasё¦ ЖчЗФЗШ ёрµз µҐАМЕНё¦ »иБ¦ЗСґЩ.
////////////////////////////////////////////////////////////////////////////////
void cCsvTable::Destroy()
{
    m_File.Destroy();
    m_Alias.Destroy();
    m_CurRow = -1;
}

////////////////////////////////////////////////////////////////////////////////
/// \brief ЗцАз ЗаА» №ЭИЇЗСґЩ.
/// \return const cCsvRow* ѕЧјјЅє°Ў °ЎґЙЗС ЗцАз ЗаАМ БёАзЗПґВ °жїмїЎґВ ±Ч ЗаАЗ
/// ЖчАОЕНё¦ №ЭИЇЗП°н, ґх АМ»у ѕЧјјЅє °ЎґЙЗС ЗаАМ ѕшґВ °жїмїЎґВ NULLА» 
/// №ЭИЇЗСґЩ.
////////////////////////////////////////////////////////////////////////////////
const cCsvRow* const cCsvTable::CurRow() const
{
    if (m_CurRow < 0)
    {
        Assert(false && "call Next() first!");
        return NULL;
    }
    else if (m_CurRow >= (int)m_File.GetRowCount())
    {
        Assert(false && "no more rows!");
        return NULL;
    }

    return m_File[m_CurRow];
}

