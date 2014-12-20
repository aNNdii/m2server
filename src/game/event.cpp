/*
 *    Filename: event.c
 * Description: АМєҐЖ® °ь·Г (timed event)
 *
 *      Author: ±иЗСБЦ (aka. єсї±, Cronan), јЫїµБш (aka. myevan, єшАЪ·з)
 */
#include "stdafx.h"

#include "event_queue.h"

extern void ContinueOnFatalError();
extern void ShutdownOnFatalError();

#ifdef M2_USE_POOL
MemoryPool event_info_data::pool_;
static ObjectPool<EVENT> event_pool;
#endif

static CEventQueue cxx_q;

/* АМєҐЖ®ё¦ »эјєЗП°н ё®ЕПЗСґЩ */
LPEVENT event_create_ex(TEVENTFUNC func, event_info_data* info, long when)
{
	LPEVENT new_event = NULL;

	/* №ЭµеЅГ ґЩАЅ pulse АМ»уАЗ ЅГ°ЈАМ Бці­ ИДїЎ єОёЈµµ·П ЗСґЩ. */
	if (when < 1)
		when = 1;

#ifdef M2_USE_POOL
	new_event = event_pool.Construct();
#else
	new_event = M2_NEW event;
#endif

	assert(NULL != new_event);

	new_event->func = func;
	new_event->info	= info;
	new_event->q_el	= cxx_q.Enqueue(new_event, when, thecore_heart->pulse);
	new_event->is_processing = false;
	new_event->is_force_to_end = false;

	return (new_event);
}

/* ЅГЅєЕЫАё·О єОЕН АМєҐЖ®ё¦ Б¦°ЕЗСґЩ */
void event_cancel(LPEVENT * ppevent)
{
	LPEVENT event;

	if (!ppevent)
	{
		sys_err("null pointer");
		return;
	}

	if (!(event = *ppevent))
		return;

	if (event->is_processing)
	{
		event->is_force_to_end = true;

		if (event->q_el)
			event->q_el->bCancel = true;

		*ppevent = NULL;
		return;
	}

	// АМ№М ГлјТ µЗѕъґВ°Ў?
	if (!event->q_el)
	{
		*ppevent = NULL;
		return;
	}

	if (event->q_el->bCancel)
	{
		*ppevent = NULL;
		return;
	}

	event->q_el->bCancel = true;

	*ppevent = NULL;
}

void event_reset_time(LPEVENT event, long when)
{
	if (!event->is_processing)
	{
		if (event->q_el)
			event->q_el->bCancel = true;

		event->q_el = cxx_q.Enqueue(event, when, thecore_heart->pulse);
	}
}

/* АМєҐЖ®ё¦ ЅЗЗаЗТ ЅГ°ЈїЎ µµґЮЗС АМєҐЖ®µйА» ЅЗЗаЗСґЩ */
int event_process(int pulse)
{
	long	new_time;
	int		num_events = 0;

	// event_q Бп АМєҐЖ® ЕҐАЗ ЗмµеАЗ ЅГ°ЈєёґЩ ЗцАзАЗ pulse °Ў АыАёёй ·зЗБ№®АМ 
	// µ№Бц ѕК°Ф µИґЩ.
	while (pulse >= cxx_q.GetTopKey())
	{
		TQueueElement * pElem = cxx_q.Dequeue();

		if (pElem->bCancel)
		{
			cxx_q.Delete(pElem);
			continue;
		}

		new_time = pElem->iKey;

		LPEVENT the_event = pElem->pvData;
		long processing_time = event_processing_time(the_event);
		cxx_q.Delete(pElem);

		/*
		 * ё®ЕП °ЄАє »х·Оїо ЅГ°ЈАМёз ё®ЕП °ЄАМ 0 єёґЩ Е¬ °жїм АМєҐЖ®ё¦ ґЩЅГ ГЯ°ЎЗСґЩ. 
		 * ё®ЕП °ЄА» 0 АМ»уАё·О ЗТ °жїм event їЎ ЗТґзµИ ёЮёрё® Б¤єёё¦ »иБ¦ЗПБц ѕКµµ·П
		 * БЦАЗЗСґЩ.
		 */
		the_event->is_processing = true;

		if (!the_event->info)
		{
			the_event->q_el = NULL;
			ContinueOnFatalError();
		}
		else
		{
			//sys_log(0, "EVENT: %s %d event %p info %p", the_event->file, the_event->line, the_event, the_event->info);
			new_time = (the_event->func) (get_pointer(the_event), processing_time);
			
			if (new_time <= 0 || the_event->is_force_to_end)
			{
				the_event->q_el = NULL;
			}
			else
			{
				the_event->q_el = cxx_q.Enqueue(the_event, new_time, pulse);
				the_event->is_processing = false;
			}
		}

		++num_events;
	}

	return num_events;
}

/* АМєҐЖ®°Ў јцЗаЅГ°ЈА» pulse ґЬА§·О ё®ЕПЗШ БШґЩ */
long event_processing_time(LPEVENT event)
{
	long start_time;

	if (!event->q_el)
		return 0;

	start_time = event->q_el->iStartTime;
	return (thecore_heart->pulse - start_time);
}

/* АМєҐЖ®°Ў іІАє ЅГ°ЈА» pulse ґЬА§·О ё®ЕПЗШ БШґЩ */
long event_time(LPEVENT event)
{
	long when;

	if (!event->q_el)
		return 0;

	when = event->q_el->iKey;
	return (when - thecore_heart->pulse);
}

/* ёрµз АМєҐЖ®ё¦ Б¦°ЕЗСґЩ */
void event_destroy(void)
{
	TQueueElement * pElem;

	while ((pElem = cxx_q.Dequeue()))
	{
		LPEVENT the_event = (LPEVENT) pElem->pvData;

		if (!pElem->bCancel)
		{
			// no op here
		}

		cxx_q.Delete(pElem);
	}
}

int event_count()
{
	return cxx_q.Size();
}

void intrusive_ptr_add_ref(EVENT* p) {
	++(p->ref_count);
}

void intrusive_ptr_release(EVENT* p) {
	if ( --(p->ref_count) == 0 ) {
#ifdef M2_USE_POOL
		event_pool.Destroy(p);
#else
		M2_DELETE(p);
#endif
	}
}
