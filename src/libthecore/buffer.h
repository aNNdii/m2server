/*
 *    Filename: buffer.h
 * Description: Buffer Гіё® ёрµв
 *
 *      Author: ±иЗСБЦ (aka. єсї±, Cronan), јЫїµБш (aka. myevan, єшАЪ·з)
 */
#ifndef __INC_LIBTHECORE_BUFFER_H__
#define __INC_LIBTHECORE_BUFFER_H__

#define SAFE_BUFFER_DELETE(buf)		{ if(buf != NULL) { buffer_delete(buf); buf = NULL; } }

    typedef struct buffer	BUFFER;
    typedef struct buffer *	LPBUFFER;

    struct buffer
    {
	struct buffer * next;

	char *          write_point;
	int             write_point_pos;

	const char *    read_point;
	int             length;

	char *          mem_data;
	int             mem_size;

	long            flag;
    };

	extern LPBUFFER	buffer_new(int size);				// »х №цЖЫ »эјє
    extern void		buffer_delete(LPBUFFER buffer);					// №цЖЫ »иБ¦
    extern void		buffer_reset(LPBUFFER buffer);					// №цЖЫ ±жАМµйА» ГК±вИ­

    extern DWORD	buffer_size(LPBUFFER buffer);					// №цЖЫїЎ іІАє ±жАМ
    extern int		buffer_has_space(LPBUFFER buffer);				// ѕµ јц АЦґВ ±жАМё¦ ё®ЕП

    extern void		buffer_write (LPBUFFER& buffer, const void* src, int length);	// №цЖЫїЎ ѕґґЩ.
    extern void		buffer_read(LPBUFFER buffer, void * buf, int bytes);		// №цЖЫїЎј­ АРґВґЩ.
    extern BYTE		buffer_get_byte(LPBUFFER buffer);
    extern WORD		buffer_get_word(LPBUFFER buffer);
    extern DWORD	buffer_get_dword(LPBUFFER buffer);

    // buffer_proceed ЗФјцґВ buffer_peekАё·О АР±вїл ЖчАОЕНё¦ ё®ЕП №ЮѕЖј­ ѕµ ЗКїд°Ў
    // АЦА» ¶§ Гіё®°Ў іЎіЄёй ѕуё¶іЄ Гіё®°Ў іЎіµґЩ°н ЕлєёЗШѕЯ ЗТ ¶§ ѕґґЩ. 
    // (buffer_read, buffer_get_* ЅГё®БоАЗ °жїмїЎґВ ѕЛѕЖј­ Гіё®µЗБцёё peekАё·О Гіё®ЗЯА»
    //  ¶§ґВ ±Ч·ё°Ф µЙ јц°Ў ѕшАё№З·О)
    extern const void *	buffer_read_peek(LPBUFFER buffer);				// АРґВ А§ДЎё¦ ё®ЕП
    extern void		buffer_read_proceed(LPBUFFER buffer, int length);		// lengthёёЕ­АЗ Гіё®°Ў іЎіІ

    // ё¶Вщ°ЎБц·О write_peekАё·О ѕІ±в А§ДЎё¦ ѕтѕоїВ ґЩАЅ ѕуё¶іЄ ЅиіЄ ЕлєёЗТ ¶§
    // buffer_write_proceedё¦ »зїлЗСґЩ.
    extern void *	buffer_write_peek(LPBUFFER buffer);				// ѕІґВ А§ДЎё¦ ё®ЕП
    extern void		buffer_write_proceed(LPBUFFER buffer, int length);		// lengthёё Бх°Ў ЅГЕІґЩ.

    extern void		buffer_adjust_size(LPBUFFER & buffer, int add_size);		// add_sizeёёЕ­ ГЯ°ЎЗТ Е©±вё¦ И®єё
#endif
