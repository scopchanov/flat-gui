cmake_minimum_required(VERSION 3.16)

project(PageTransitions VERSION 3.0.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_library(FlatGui
	NAMES FlatGui
	PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../install/${PROJECT_VERSION}/lib
)

qt_add_resources(APP_RESOURCES app/assets/resources.qrc)

add_executable(${PROJECT_NAME} ${APP_RESOURCES})
add_subdirectory(app/src)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets ${FlatGui})

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/../../install/${PROJECT_VERSION}/include/FlatGui)
