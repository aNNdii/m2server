##
# This file is part of the enhanceMT Project.
##

file(GLOB_RECURSE sources_localdir *.cpp *.h)

SET(db_SRCS
	${db_SRCS}
	${sources_localdir}
)

include_directories(
	${CMAKE_BINARY_DIR}
	${CMAKE_SOURCE_DIR}/src
	${CMAKE_SOURCE_DIR}/src/shared
	${BOOST_INCLUDE_DIR}
	${CRYPTOPP_INCLUDE_DIRS}
	${MYSQL_INCLUDE_DIR}
	${OPENSSL_INCLUDE_DIR}
)

add_executable(db ${db_SRCS})

if(WIN32)
    find_library(MYSQL_LIBRARY mysqlclient ${MYSQL_INCLUDE_DIR}/lib)
elseif(UNIX)
    find_library(MYSQL_LIBRARY mysqlclient ${MYSQL_LIBRARIES})
endif()

#SET_TARGET_PROPERTIES(db PROPERTIES COMPILE_DEFINITIONS "${_definitions}") 
#SET_TARGET_PROPERTIES(db PROPERTIES LINK_SEARCH_END_STATIC 1)

#set(CMAKE_EXE_LINKER_FLAGS -static) 
#set(CMAKE_FIND_LIBRARY_SUFFIXES .a) 
set(CMAKE_EXE_LINK_DYNAMIC_C_FLAGS)       # remove -Wl,-Bdynamic 
set(CMAKE_EXE_LINK_DYNAMIC_CXX_FLAGS) 
set(CMAKE_SHARED_LIBRARY_C_FLAGS)         # remove -fPIC 
set(CMAKE_SHARED_LIBRARY_CXX_FLAGS) 
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)    # remove -rdynamic 
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS) 

target_link_libraries(db
	libthecore
	shared
	lua
	${MYSQL_LIBRARY}
	pthread
)
