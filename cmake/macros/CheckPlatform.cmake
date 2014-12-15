##
# This file is part of the enhanceMT Project.
##

# Include global settings
include("${CMAKE_SOURCE_DIR}/cmake/platform/settings.cmake")

if (${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
    set(FREEBSD TRUE)
endif()

# Include platform settings
if (WIN32)
    include("${CMAKE_SOURCE_DIR}/cmake/platform/win/settings.cmake")
elseif (UNIX)
    if (FREEBSD)
        include("${CMAKE_SOURCE_DIR}/cmake/platform/freebsd/settings.cmake")
    else()
        include("${CMAKE_SOURCE_DIR}/cmake/platform/unix/settings.cmake")
    endif()
endif()
