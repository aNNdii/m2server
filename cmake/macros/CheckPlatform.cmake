##
# This file is part of the enhanceMT Project.
##

# Include global settings
include("${CMAKE_SOURCE_DIR}/cmake/platform/settings.cmake")

# Include platform settings
if(WIN32)
    include("${CMAKE_SOURCE_DIR}/cmake/platform/win/settings.cmake")
elseif(UNIX)
    include("${CMAKE_SOURCE_DIR}/cmake/platform/unix/settings.cmake")
endif()
