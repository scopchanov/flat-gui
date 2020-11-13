QT += widgets

TARGET = sidebar
TEMPLATE = app

SOURCES += \
        main.cpp \
        MainWindow.cpp

HEADERS += \
        MainWindow.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../bin/ -lFlatGui
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../bin/ -lFlatGuid

INCLUDEPATH += $$PWD/../../../src
DEPENDPATH += $$PWD/../../../src
