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
    
    target_link_libraries(db
        libthecore
        shared
        lua
        ${MYSQL_LIBRARY}
    )

elseif(UNIX)
    #if(FREEBSD)
    #    find_library(MYSQL_LIBRARY mysql ${MYSQL_LIBRARIES}) 
    #else()
    #    find_library(MYSQL_LIBRARY mysqlclient ${MYSQL_LIBRARIES})
    #endif()

    target_link_libraries(db
        libthecore
        shared
        lua
        ${MYSQL_LIBRARY}
        pthread
    )
endif()
