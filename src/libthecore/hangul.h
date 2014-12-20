#ifndef __INC_LIBTHECORE_HANGUL_H__
#define __INC_LIBTHECORE_HANGUL_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#ifdef _WIN32
#define isdigit iswdigit
#define isspace iswspace
#endif

#define ishan(ch)       (((ch) & 0xE0) > 0x90)
#define ishanasc(ch)    (isascii(ch) || ishan(ch))
#define ishanalp(ch)    (isalpha(ch) || ishan(ch))
#define isnhdigit(ch)   (!ishan(ch) && isdigit(ch))
#define isnhspace(ch)   (!ishan(ch) && isspace(ch))

    extern const char *	first_han(const BYTE * str);	// Г№№шВ° µО ±ЫАЪАЗ ёрАЅ(¤Ў¤¤¤§)А» »МѕЖ °Ў/іЄ/ґЩ/..ё¦ ё®ЕПЗСґЩ.
    extern int		check_han(const char * str);	// ЗС±ЫАМёй true ЅєЖ®ёµ АьєО ГјЕ©
    extern int		is_hangul(const BYTE * str);	// ЗС±ЫАМёй true (2№ЩАМЖ®ёё ГјЕ©)
    extern int		under_han(const void * orig);	// №ЮД§АМ АЦАёёй true

#define UNDER(str)	under_han(str)

#ifdef __cplusplus
};
#endif

#endif
