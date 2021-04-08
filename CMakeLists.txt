cmake_minimum_required(VERSION 2.8)

project(JOUVIN_Tanguy_Projet)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES Graphiques_fr_FR.ts Graphiques_en_US.ts)
qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

add_executable(${PROJECT_NAME}
    "main.cpp"
    graphiques.cpp
    graphiques.hpp
    graphiques.ui
    drawgraph.cpp
    drawgraph.hpp
    ressources.qrc

    ${QM_FILES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
