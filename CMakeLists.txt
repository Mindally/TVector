cmake_minimum_required(VERSION 3.14)
project(TVector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(TVector
    include/TVector.h
    include/TVector.cpp
)

source_group("Source Files" FILES include/TVector.cpp)
source_group("Header Files" FILES include/TVector.h)

target_include_directories(TVector
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

add_library(TVector::TVector ALIAS TVector)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(GNUInstallDirs)
    
    install(TARGETS TVector
        EXPORT TVectorTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
    
    install(FILES include/TVector.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(EXPORT TVectorTargets
        FILE TVectorConfig.cmake
        NAMESPACE TVector::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/TVector
    )
endif()