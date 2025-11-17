QT += widgets

CONFIG += C++23

TEMPLATE = app

SOURCES += \
	app/src/FileHandler.cpp \
	app/src/MainWindow.cpp \
	app/src/Page.cpp \
	app/src/main.cpp

HEADERS += \
	app/src/FileHandler.h \
	app/src/MainWindow.h \
	app/src/Page.h

RESOURCES += \
	app/assets/resources.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../install/3.0.0/lib/ -lFlatGui
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../install/3.0.0/lib/ -lFlatGuid
else:unix: LIBS += -L$$PWD/../../install/3.0.0/lib/ -lFlatGui

INCLUDEPATH += $$PWD/../../install/3.0.0/include/FlatGui
DEPENDPATH += $$PWD/../../install/3.0.0/include/FlatGui
