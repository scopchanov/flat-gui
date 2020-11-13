# MIT License

# Copyright (c) 2020 Michael Scopchanov

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

include(../../autoversion.pri)

VERSION = $$PROJECT_VERSION

QT += widgets

CONFIG += c++11
CONFIG += skip_target_version_ext
DEFINES += QT_DEPRECATED_WARNINGS

TEMPLATE    = lib
TARGET	    = $$qtLibraryTarget(FlatGui)
DESTDIR	    = ../bin
#DLLDESTDIR  = "../../../WaageScan Advanced/app/deploy"

TRANSLATIONS = \
    translations/FlatGui_de.ts \
    translations/FlatGui_fr.ts \
    translations/FlatGui_es.ts \
    translations/FlatGui_it.ts \
    translations/FlatGui_pl.ts \
    translations/FlatGui_tr.ts \
    translations/FlatGui_ru.ts \
    translations/FlatGui_bg.ts

DEFINES += FLATGUI_LIBRARY

SOURCES += \
    AbstractButton.cpp \
    AbstractDataModel.cpp \
    AbstractDecoration.cpp \
    AbstractEditor.cpp \
    AbstractValidator.cpp \
    ActionNavigate.cpp \
    Alert.cpp \
    ButtonCategory.cpp \
    DateDataModel.cpp \
    DateEditor.cpp \
    GenericForm.cpp \
    HorizontalSlide.cpp \
    LineEdit.cpp \
    ListItemAnimation.cpp \
    NavigationBar.cpp \
    PageCategories.cpp \
    PageIndicator.cpp \
    PersonNameValidator.cpp \
    PushButton.cpp \
    SearchForm.cpp \
    SlideView.cpp \
    SidePanel.cpp \
    SimpleMessage.cpp \
    Splash.cpp \
    TextDataModel.cpp \
    TextEditor.cpp \
    TimeDataModel.cpp \
    TimeEditor.cpp \
    ToolBar.cpp \
    ToolButton.cpp \
    ValidatorFactory.cpp \
    AbstractPanel.cpp \
    SplitView.cpp \
    StaticDecoration.cpp \
    DynamicDecoration.cpp \
    DateField.cpp \
    MonthPage.cpp \
    MonthView.cpp \
    SwitchBox.cpp \
    PixmapBuilder.cpp \
    TimeField.cpp \
    FancyField.cpp \
    TextField.cpp \
    AbstractField.cpp \
    DoubleValidator.cpp \
    GridWidget.cpp

HEADERS += \
    AbstractButton.h \
    AbstractDataModel.h \
    AbstractDataModel_p.h \
    AbstractDecoration.h \
    AbstractEditor.h \
    AbstractValidator.h \
    ActionNavigate.h \
    Alert.h \
    ButtonCategory.h \
    DateDataModel.h \
    DateEditor.h \
    GenericForm.h \
    GenericForm_p.h \
    HorizontalSlide.h \
    LineEdit.h \
    ListItemAnimation.h \
    NavigationBar.h \
    PageCategories.h \
    PageIndicator.h \
    PersonNameValidator.h \
    PushButton.h \
    SlideView.h \
    SearchForm.h \
    SearchForm_p.h \
    SidePanel.h \
    SimpleMessage.h \
    Splash.h \
    TextDataModel.h \
    TextEditor.h \
    TimeDataModel.h \
    TimeEditor.h \
    ToolBar.h \
    ToolButton.h \
    ValidatorFactory.h \
    AbstractPanel.h \
    SplitView.h \
    SplitView_p.h \
    NavigationBar_p.h \
    SlideView_p.h \
    StaticDecoration.h \
    DynamicDecoration.h \
    DateField.h \
    MonthPage.h \
    MonthView.h \
    SwitchBox.h \
    SwitchBox_p.h \
    PixmapBuilder.h \
    ToolButton_p.h \
    PixmapBuilder_p.h \
    DateDataModel_p.h \
    TextDataModel_p.h \
    TimeDataModel_p.h \
    AbstractEditor_p.h \
    ButtonCategory_p.h \
    PushButton_p.h \
    TimeField.h \
    FancyField.h \
    TextField.h \
    AbstractField.h \
    AbstractField_p.h \
    ActionNavigate_p.h \
    DoubleValidator.h \
    DoubleValidator_p.h \
    GridWidget.h \
    GridWidget_p.h \
    Alert_p.h

OTHER_FILES += \
    FlatGui.qdoc

RESOURCES += \
    guires.qrc
