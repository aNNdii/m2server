/**
 *
 * @file	TrafficProfiler.h
 * @brief	TrafficProfiler class definition file
 * @author	Bang2ni
 * @version	05/07/07 Bang2ni - First release.
 * 
 */

#ifndef _METIN_II_TRAFFICPROFILER_H_
#define _METIN_II_TRAFFICPROFILER_H_

/**
 * @class	TrafficProfiler
 * @brief	Network I/O traffic А» ЖРЕ¶ ґЬА§·О ГшБ¤ЗПґВ profiler.
 * @author	Bang2ni
 * @version	05/07/07 Bang2ni - First release.
 *
 * ЅГ°Јґл є°·О Network I/O АЗ traffic А» ЖРЕ¶ ґЬА§·О ГшБ¤ЗП°н, Text file ЗьЕВ·О єё°нј­ё¦ АЫјєЗСґЩ.
 */
class TrafficProfiler : public singleton< TrafficProfiler >
{
	public:

		/// I/O №жЗв
		enum IODirection {
			IODIR_INPUT	= 0,	///< Input
			IODIR_OUTPUT,	///< Output
			IODIR_MAX
		};

	public:

		/// Constructor
		TrafficProfiler( void );

		/// Destructor
		~TrafficProfiler( void );

		/// Profiling їЎ ЗКїдЗС ГК±вИ­ё¦ ЗСґЩ.
		/**
		 * @param [in]	dwFlushCycle Flush БЦ±в. ГК ґЬА§АМґЩ.
		 * @param [in]	pszLogFileName Profiling log file АЗ АМё§
		 * @return	false АП °жїм profiling log file А» open ЗПБц ёшЗЯґЩ.
		 *
		 * profiling log file А» open(»эјє) ЗСґЩ.
		 */
		bool	Initialize( DWORD dwFlushCycle, const char* pszLogFileName );

		/// Profiling А» А§ЗШ АьјЫµЖ°ЕіЄ АьјЫ ЗТ Packet А» Report ЗСґЩ.
		/**
		 * @param [in]	dir Profiling ЗТ Packet АЗ №жЗв
		 * @param [in]	byHeader Packet Змґх
		 * @param [in]	dwSize Packet АЗ ГС size
		 * @return	Initialize µЗБц ѕКѕТґЩёй false ё¦ №ЭИЇЗСґЩ.
		 *
		 * Packet їЎ ЗШґзЗПґВ size ё¦ ґ©АыЅГЕІґЩ.
		 * Initialize АМИДіЄ ГЦ±Щ Flush µИ АМИДїЎ Flush БЦ±в ёёЕ­ ЅГ°ЈАМ ИеёҐ ИД ИЈГвµИґЩёй Report АМИД Flush ЗСґЩ.
		 */
		bool	Report( IODirection dir, BYTE byHeader, DWORD dwSize )
		{
			ComputeTraffic( dir, byHeader, dwSize );
			if ( (DWORD)(time( NULL ) - m_tmProfileStartTime) >= m_dwFlushCycle )
				return Flush();
			return true;
		}

		/// ЗцАз±оБц Report µИ і»їлА» ЖДАПїЎ ѕґґЩ.
		/**
		 * @return	Initialize µЗБц ѕКѕТґЩ.
		 */
		bool	Flush( void );

	private:

		/// Profling їЎ °ь·ГµИ variables ё¦ ГК±вИ­ ЗСґЩ.
		void	InitializeProfiling( void );

		/// Report µИ Packet АЗ traffic ё¦ °и»кЗСґЩ.
		/**
		 * @param [in]	dir Profiling ЗТ Packet АЗ №жЗв
		 * @param [in]	byHeader Packet Змґх
		 * @param [in]	dwSize Packet АЗ ГС size
		 */
		void	ComputeTraffic( IODirection dir, BYTE byHeader, DWORD dwSize )
		{

			TrafficInfo& rTrafficInfo = m_aTrafficVec[ dir ][ byHeader ];

			m_dwTotalTraffic += dwSize;
			m_dwTotalPacket += !rTrafficInfo.second;

			rTrafficInfo.first += dwSize;
			rTrafficInfo.second++;
		}

		/// Traffic info type.
		/**
		 * first: ґ©АыµИ ГС size
		 * second: АМ packet АМ АьјЫµИ ИЅјц
		 */
		typedef std::pair< DWORD, DWORD >	TrafficInfo;

		/// Traffic info vector.
		typedef std::vector< TrafficInfo >	TrafficVec;

		FILE*		m_pfProfileLogFile;	///< Profile log file pointer
		DWORD		m_dwFlushCycle;		///< Flush БЦ±в
		time_t		m_tmProfileStartTime;	///< ЗБ·ОЖДАПА» ЅГАЫЗС ЅГ°Ј. Flush µЙ ¶§ё¶ґЩ Update µИґЩ.
		DWORD		m_dwTotalTraffic;	///< Report µИ ГС Traffic їл·®
		DWORD		m_dwTotalPacket;	///< Report µИ ГС Packet јц
		TrafficVec	m_aTrafficVec[ IODIR_MAX ];	///< Report µИ Traffic А» АъАеЗТ vectorАЗ №иї­. °ў №жЗвё¶ґЩ vector ё¦ °ЎБшґЩ.
};

#endif // _METIN_II_TRAFFICPROFILER_H_
