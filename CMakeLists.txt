cmake_minimum_required(VERSION 3.16)

project(ElectechInnovation VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(electech
    src/main.cpp
    src/montant_lettres.cpp
)

target_include_directories(electech PRIVATE include)
