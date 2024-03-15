

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


add_executable(SwitchBox 

    main.cpp
    MainWindow.cpp
    resources.qrc
    )

target_link_libraries(SwitchBox PRIVATE Qt${QT_VERSION_MAJOR}::Widgets FlatGui)    