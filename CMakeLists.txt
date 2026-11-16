cmake_minimum_required(VERSION 3.28)
project(ItsRainingKanji LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(ItsRainingKanji src/main.cpp
        src/Textbox.cpp
        src/Textbox.h
        src/Word.cpp
        src/Word.h
        src/FallingWord.cpp
        src/FallingWord.h
        src/WordList.cpp
        src/WordList.h
        src/FallingWordList.cpp
        src/FallingWordList.h
        src/Button.cpp
        src/Button.h
        src/Game.cpp
        src/Game.h
)
target_compile_features(ItsRainingKanji PRIVATE cxx_std_17)

if (MSVC)
    target_compile_options(ItsRainingKanji PRIVATE /W4 /permissive-)
else()
    target_compile_options(ItsRainingKanji PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
endif ()

target_link_libraries(ItsRainingKanji PRIVATE SFML::Graphics SFML::Audio)

add_custom_command(TARGET ItsRainingKanji POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:ItsRainingKanji>/assets)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ItsRainingKanji)
