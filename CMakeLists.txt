cmake_minimum_required(VERSION 3.20)
project(PassForge VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(passforge
    main.cpp
    Engines.cpp
    Entropy.cpp
    Facade.cpp
    Generator.cpp
    Hash.cpp
    PasswordPolicy.cpp
    PoolAnalyzer.cpp
    PoolBuilder.cpp
    PoolCompatibility.cpp
)

if(WIN32)
    target_link_libraries(passforge PRIVATE bcrypt)
endif()