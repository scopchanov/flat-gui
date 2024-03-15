

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


aux_source_directory(. SRC_FILES)

add_library(FlatGui STATIC  
    ${SRC_FILES}
    guires.qrc
)

message(${SRC_FILES})

target_link_libraries(FlatGui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_compile_definitions(FlatGui PRIVATE FLATGUI_LIBRARY)

target_include_directories(FlatGui PUBLIC ./)