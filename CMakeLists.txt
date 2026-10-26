cmake_minimum_required(VERSION 3.10)
project(Calc)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR})

# Основная программа
add_executable(calc
    main.cpp
    Parser.cpp
    PluginManager.cpp
    Calculator.cpp
)

if(NOT WIN32)
    target_link_libraries(calc PRIVATE dl)
endif()

# Плагины
add_library(funcsin SHARED sin.cpp)
add_library(funcdeg SHARED deg.cpp)
add_library(funcln SHARED ln.cpp)
add_library(funcsqrt SHARED sqrt.cpp)

# Настройки для плагинов
set(PLUGIN_OUT ${CMAKE_BINARY_DIR}/plugins)
foreach(plugin funcsin funcdeg funcln funcsqrt)
    set_target_properties(${plugin} PROPERTIES
        PREFIX ""
        RUNTIME_OUTPUT_DIRECTORY ${PLUGIN_OUT}
        LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUT}
    )
endforeach()