cmake_minimum_required(VERSION 3.15)
project(Snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
    add_link_options(-static -static-libgcc -static-libstdc++)
endif()

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Snake ${SOURCES})

target_include_directories(Snake PRIVATE headers)

if(MSVC)
    target_compile_options(Snake PRIVATE 
        $<$<CONFIG:Release>:/O1>         
        $<$<CONFIG:Release>:/Os>          
        $<$<CONFIG:Release>:/GL>          
    )
    target_link_options(Snake PRIVATE 
        $<$<CONFIG:Release>:/LTCG>       
        $<$<CONFIG:Release>:/OPT:REF>     
        $<$<CONFIG:Release>:/OPT:ICF>     
    )
else()
    target_compile_options(Snake PRIVATE 
        $<$<CONFIG:Release>:-Os>                 
        $<$<CONFIG:Release>:-fdata-sections>    
        $<$<CONFIG:Release>:-ffunction-sections>
        $<$<CONFIG:Release>:-flto>               
    )
    target_link_options(Snake PRIVATE 
        $<$<CONFIG:Release>:-s>                  
        $<$<CONFIG:Release>:-Wl,--gc-sections>   
        $<$<CONFIG:Release>:-flto>              
    )
endif()