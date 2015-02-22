##
# This file is part of the enhanceMT Project.
# Based on TrinityCore project cmake files.
##

# Set project name
project(enhanceMT)

# CMake policies
cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0005 OLD)
if(POLICY CMP0043)
	cmake_policy(SET CMP0043 OLD) # Disable 'Ignore COMPILE_DEFINITIONS_<Config> properties'
endif(POLICY CMP0043)

# Set macro directory
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/macros")

# Build in Release by default
set(CMAKE_BUILD_TYPE "Release")

# Set default build options and print them
include(cmake/options.cmake)

# Set platform and compiler options
include(CheckPlatform)
	
if(WIN32)
    set(EXTERN_DIR ${CMAKE_SOURCE_DIR}/Extern)
    
    set(ENV{BOOST_ROOT} ${EXTERN_DIR}/boost-1_57)
    set(ENV{BOOST_LIBRARYDIR} ${EXTERN_DIR}/boost-1_57/lib)

    set(CRYPTOPP_INCLUDE_DIRS ${EXTERN_DIR}/cryptopp/include)
    set(MYSQL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/shared/libmysql/6.0.2/win32)
    set(OPENSSL_INCLUDE_DIR ${EXTERN_DIR}/OpenSSL-Win32/include)
    
    set(MYSQL_LIBRARIES ${CMAKE_SOURCE_DIR}/src/shared/libmysql/6.0.2/win32/lib)
    
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 18.0)
        set(CRYPTOPP_LIBRARY_DIR ${EXTERN_DIR}/cryptopp/lib)
        set(OPENSSL_LIBRARIES ${EXTERN_DIR}/OpenSSL-Win32/lib)
    else()
        set(CRYPTOPP_LIBRARY_DIR ${EXTERN_DIR}/cryptopp/lib/vs12)
        set(OPENSSL_LIBRARIES ${EXTERN_DIR}/OpenSSL-Win32/lib/vs12)
    endif()
elseif(UNIX)
    set(OPENSSL_EXPECTED_VERSION 1.0.1)
    find_package(OpenSSL REQUIRED)

	if(FREEBSD)
		set(GENERIC_INCLUDE /usr/local/include)
		set(GENERIC_LIBRARY /usr/local/lib)
	else()
		set(GENERIC_INCLUDE /usr/include)
		set(GENERIC_LIBRARY /usr/lib)
	endif()

	set(CRYPTOPP_INCLUDE_DIRS ${GENERIC_INCLUDE})
	set(CRYPTOPP_LIBRARY_DIR ${GENERIC_LIBRARY})

	include(FindMySQL)
endif()

# Boost
include(ConfigureBoost)
set(BOOST_INCLUDE_DIR ${Boost_INCLUDE_DIRS})

link_directories(
	${Boost_LIBRARY_DIRS}
	${CRYPTOPP_LIBRARY_DIR}
	${MYSQL_LIBRARY}
	${OPENSSL_LIBRARIES}
)

# Print out the results before continuing
include(cmake/showoptions.cmake)

# Add core sources
add_subdirectory(src)
