cmake_minimum_required(VERSION 3.16)

project(TextEncoder VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOUIC_SEARCH_PATHS resources)

set(PROJECT_SOURCES
    src/main.cpp
    src/MainWindow.cpp
    include/MainWindow.h
    resources/MainWindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TextEncoder
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        include/IEncryptionAlgorithm.h
        include/CaesarCipher.h
        src/CaesarCipher.cpp
        include/CipherFactory.h
        src/CipherFactory.cpp
        include/EncryptionService.h
        src/EncryptionService.cpp
    )
else()
    add_executable(TextEncoder
        ${PROJECT_SOURCES}
    )
endif()

target_include_directories(TextEncoder PRIVATE include)

target_link_libraries(TextEncoder PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_finalize_executable(TextEncoder)
endif()
