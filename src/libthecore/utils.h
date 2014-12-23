#ifndef __INC_LIBTHECORE_UTILS_H__
#define __INC_LIBTHECORE_UTILS_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#define SAFE_FREE(p)		{ if (p) { free( (void *) p);		(p) = NULL;  } }
#define SAFE_DELETE(p)		{ if (p) { delete (p);			(p) = NULL;  } }
#define SAFE_DELETE_ARRAY(p)	{ if (p) { delete[] (p);		(p) = NULL;  } }
#define SAFE_RELEASE(p)		{ if (p) { (p)->Release();		(p) = NULL;  } }

#define LOWER(c)	(((c)>='A'  && (c) <= 'Z') ? ((c)+('a'-'A')) : (c))
#define UPPER(c)	(((c)>='a'  && (c) <= 'z') ? ((c)+('A'-'a')) : (c))

#define str_cmp strcasecmp
#define STRNCPY(dst, src, len)          do {strncpy(dst, src, len); dst[len] = '\0'; } while(0)

    extern char *	str_dup(const char * source);	// ёЮёрё® ЗТґз ЗШј­ source є№»з ЗС°Е ё®ЕП
    extern void		printdata(const unsigned char * data, int bytes); // dataё¦ hex¶ы ascii·О Гв·В (ЖРЕ¶ єРј® µоїЎ ѕІАУ)
    extern int		filesize(FILE * fp);	// ЖДАП Е©±в ё®ЕП

#define core_dump()	core_dump_unix(__FILE__, __LINE__)
    extern void		core_dump_unix(const char *who, WORD line);	// ДЪѕоё¦ °­Б¦·О ґэЗБ

#define TOKEN(string) if (!str_cmp(token_string, string))
    // src = ЕдЕ« : °Є
    extern void		parse_token(char * src, char * token, char * value);

    extern void		trim_and_lower(const char * src, char * dest, size_t dest_size);

    // №®АЪї­А» јТ№®АЪ·О
    extern void		lower_string(const char * src, char * dest, size_t dest_len);

    // arg1АМ arg2·О ЅГАЫЗПґВ°Ў? (ґлјТ№®АЪ ±ёє°ЗПБц ѕКАЅ)
    extern int		is_abbrev(char *arg1, char *arg2);

    // aїН bАЗ ЅГ°ЈАМ ѕуё¶іЄ ВчАМіЄґВБц ё®ЕП
    extern struct timeval *	timediff(const struct timeval *a, const struct timeval *b);

    // aАЗ ЅГ°ЈїЎ bАЗ ЅГ°ЈА» ґхЗШ ё®ЕП
    extern struct timeval *	timeadd(struct timeval *a, struct timeval *b);

    // ЗцАз ЅГ°Ј curr_tmАё·О єОЕН days°Ў Бці­ іЇА» ё®ЕП
    extern struct tm *		tm_calc(const struct tm *curr_tm, int days);

    extern int MAX(int a, int b); // µСБЯїЎ Е« °ЄА» ё®ЕП
    extern int MIN(int a, int b); // µСБЯїЎ АЫАє °ЄА» ё®ЕП
    extern int MINMAX(int min, int value, int max); // ГЦјТ ГЦґл °ЄА» ЗФІІ єс±іЗШј­ ё®ЕП

    extern int		number_ex(int from, int to, const char *file, int line); // fromАё·О єОЕН to±оБцАЗ ·Јґэ °Є ё®ЕП
#define number(from, to) number_ex(from, to, __FILE__, __LINE__)

	float	fnumber(float from, float to);

    extern void		thecore_sleep(struct timeval * timeout);	// timeoutёёЕ­ ЗБ·ОјјЅє Ѕ¬±в
    extern DWORD	thecore_random();				// ·Јґэ ЗФјц

    extern float	get_float_time();
    extern DWORD	get_dword_time();
    
    extern size_t enhance_strlcpymt(char* dst, const char* src, size_t size);

    extern char *	time_str(time_t ct);

#define CREATE(result, type, number)  do { \
	if (!((result) = (type *) calloc ((number), sizeof(type)))) { \
		sys_err("calloc failed [%d] %s", errno, strerror(errno)); \
		abort(); } } while(0)

#define RECREATE(result,type,number) do { \
	if (!((result) = (type *) realloc ((result), sizeof(type) * (number)))) { \
		sys_err("realloc failed [%d] %s", errno, strerror(errno)); \
		abort(); } } while(0)

    // Next їН Prev °Ў АЦґВ ё®ЅєЖ®їЎ ГЯ°Ў
#define INSERT_TO_TW_LIST(item, head, prev, next)   \
    if (!(head))                                    \
    {                                               \
	head         = item;                        \
	    (head)->prev = (head)->next = NULL;         \
    }                                               \
    else                                            \
    {                                               \
	(head)->prev = item;                        \
	    (item)->next = head;                    \
	    (item)->prev = NULL;                    \
	    head         = item;                    \
    }

#define REMOVE_FROM_TW_LIST(item, head, prev, next)	\
    if ((item) == (head))           			\
    {                               			\
	if (((head) = (item)->next))			\
	    (head)->prev = NULL;    			\
    }                    				\
    else                 				\
    {                    				\
	if ((item)->next)				\
	    (item)->next->prev = (item)->prev;		\
							\
	if ((item)->prev)				\
	    (item)->prev->next = (item)->next;		\
    }


#define INSERT_TO_LIST(item, head, next)            \
    (item)->next = (head);                      \
	(head) = (item);                            \

#define REMOVE_FROM_LIST(item, head, next)          \
	if ((item) == (head))                       \
	    head = (item)->next;                     \
	else                                        \
	{                                           \
	    temp = head;                            \
		\
		while (temp && (temp->next != (item)))  \
		    temp = temp->next;                  \
			\
			if (temp)                               \
			    temp->next = (item)->next;          \
	}                                           \

#ifndef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3)                                      \
                ((DWORD)(BYTE) (ch0       ) | ((DWORD)(BYTE) (ch1) <<  8) | \
                 ((DWORD)(BYTE) (ch2) << 16) | ((DWORD)(BYTE) (ch3) << 24))
#endif // defined(MAKEFOURCC)

#ifdef __cplusplus
}
#endif	// __cplusplus

// _countof for gcc/g++
#if !defined(_countof)
#if !defined(__cplusplus)
#define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#else
extern "C++"
{
	    template <typename _CountofType, size_t _SizeOfArray>
			        char (*__countof_helper(_CountofType (&_Array)[_SizeOfArray]))[_SizeOfArray];
#define _countof(_Array) sizeof(*__countof_helper(_Array))
}
#endif
#endif

#ifdef _WIN32
extern void gettimeofday(struct timeval* t, struct timezone* dummy);
#endif

#endif	// __INC_UTILS_H__
