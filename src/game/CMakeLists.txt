##
# This file is part of the enhanceMT Project.
##

file(GLOB_RECURSE sources_localdir *.cpp *.c *.h)

# If not FreeBSD
if (NOT FREEBSD)
	list(REMOVE_ITEM sources_localdir ${CMAKE_CURRENT_SOURCE_DIR}/FileMonitor_FreeBSD.h)
	list(REMOVE_ITEM sources_localdir ${CMAKE_CURRENT_SOURCE_DIR}/FileMonitor_FreeBSD.cpp)
endif()
	
SET(game_SRCS
	${game_SRCS}
	${sources_localdir}
)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/Arena
	${CMAKE_CURRENT_SOURCE_DIR}/Auction
	${CMAKE_CURRENT_SOURCE_DIR}/Battle
	${CMAKE_CURRENT_SOURCE_DIR}/Castle
	${CMAKE_CURRENT_SOURCE_DIR}/Commands
	${CMAKE_CURRENT_SOURCE_DIR}/Entities
	${CMAKE_CURRENT_SOURCE_DIR}/Entities/Character
	${CMAKE_CURRENT_SOURCE_DIR}/Entities/Horse
	${CMAKE_CURRENT_SOURCE_DIR}/Entities/Pet
	${CMAKE_CURRENT_SOURCE_DIR}/Guilds
	${CMAKE_CURRENT_SOURCE_DIR}/Items
	${CMAKE_CURRENT_SOURCE_DIR}/Logs
	${CMAKE_CURRENT_SOURCE_DIR}/LuaEngine
	${CMAKE_CURRENT_SOURCE_DIR}/Movement
	${CMAKE_CURRENT_SOURCE_DIR}/Quests
	${CMAKE_CURRENT_SOURCE_DIR}/Server
	${CMAKE_CURRENT_SOURCE_DIR}/Server/Protocol
	${CMAKE_SOURCE_DIR}/src
	${CMAKE_SOURCE_DIR}/src/shared
	${CMAKE_SOURCE_DIR}/src/shared/libxtrap
	${CMAKE_SOURCE_DIR}/src/lua
	${BOOST_INCLUDE_DIR}
	${CRYPTOPP_INCLUDE_DIRS}
	${MYSQL_INCLUDE_DIR}
	${OPENSSL_INCLUDE_DIR}
)

add_executable(game ${game_SRCS})

if(WIN32)
	find_library(MYSQL_LIBRARY mysqlclient ${MYSQL_INCLUDE_DIR}/lib)
	find_library(CRYPTOPP_LIBRARY cryptlib ${CRYPTOPP_LIBRARY_DIR})
	find_library(LIBDEVIL_LIBRARY DevIL-1.7.8 ${CMAKE_SOURCE_DIR}/src/shared/libdevil/win32/lib)

	include_directories(${CMAKE_SOURCE_DIR}/src/shared/libdevil)

	target_link_libraries(
		game
		libthecore
		shared
		lua
		${CRYPTOPP_LIBRARY}
		${MYSQL_LIBRARY}
		${Boost_LIBRARIES}
		${LIBDEVIL_LIBRARY}
	)
elseif(UNIX)
	if(FREEBSD)
		find_library(MYSQL_LIBRARY mysql ${MYSQL_LIBRARIES})
	else()
		find_library(MYSQL_LIBRARY mysqlclient ${MYSQL_LIBRARIES})
	endif()

	find_library(CRYPTOPP_LIBRARY libcryptopp.a ${CRYPTOPP_LIBRARY_DIR})
	find_package(DevIL REQUIRED)
	include_directories(${IL_INCLUDE_DIRS})
	link_directories(${IL_LIBRARIES})
	link_directories(${ILU_LIBRARIES})
	link_directories(${ILUT_LIBRARIES})

	target_link_libraries(
		game
		libthecore
		shared
		lua
		pthread
		md
		${CRYPTOPP_LIBRARY}
		${MYSQL_LIBRARY}
		${Boost_LIBRARIES}
		${IL_LIBRARIES}
		${ILU_LIBRARIES}
		${ILUT_LIBRARIES}
		jpeg
		png
		tiff
		mng
	)
endif()

add_dependencies(game lua)
