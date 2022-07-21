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

include(../../common/autoversion.pri)

VERSION = $$PROJECT_VERSION

QT          += widgets

CONFIG      += c++17
CONFIG      += skip_target_version_ext
DEFINES     += QT_DEPRECATED_WARNINGS

TEMPLATE    = lib
TARGET	    = $$qtLibraryTarget(FlatGui)
DESTDIR	    = ../deploy/bin

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
    AbstractField.cpp \
    AbstractPanel.cpp \
    AbstractValidator.cpp \
    Alert.cpp \
    ButtonCategory.cpp \
    DateDataModel.cpp \
    DateEditor.cpp \
    DateField.cpp \
    DoubleValidator.cpp \
    DynamicDecoration.cpp \
    FancyField.cpp \
    GenericForm.cpp \
    GridWidget.cpp \
    HorizontalSlide.cpp \
    LineEdit.cpp \
    ListItemAnimation.cpp \
    MonthView.cpp \
    NavigationBar.cpp \
    PageCategories.cpp \
    PageIndicator.cpp \
    PersonNameValidator.cpp \
    PixmapBuilder.cpp \
    SearchForm.cpp \
    SidePanel.cpp \
    SimpleMessage.cpp \
    Splash.cpp \
    StaticDecoration.cpp \
    TextDataModel.cpp \
    TextEditor.cpp \
    TextField.cpp \
    TimeDataModel.cpp \
    TimeEditor.cpp \
    TimeField.cpp \
    ToolBar.cpp \
    ValidatorFactory.cpp \
    MonthPage.cpp \
    PushButton.cpp \
    SlideView.cpp \
    SplitView.cpp \
    SwitchBox.cpp \
    ToolButton.cpp

HEADERS += \
    AbstractButton.h \
    AbstractButton_p.h \
    AbstractDataModel.h \
    AbstractDataModel_p.h \
    AbstractDecoration.h \
    AbstractEditor.h \
    AbstractEditor_p.h \
    AbstractField.h \
    AbstractField_p.h \
    AbstractPanel.h \
    AbstractValidator.h \
    Alert.h \
    Alert_p.h \
    ButtonCategory.h \
    ButtonCategory_p.h \
    DateDataModel.h \
    DateDataModel_p.h \
    DateEditor.h \
    DateField.h \
    DoubleValidator.h \
    DoubleValidator_p.h \
    DynamicDecoration.h \
    FancyField.h \
    HorizontalSlide.h \
    HorizontalSlide_p.h \
    MonthPage.h \
    MonthPage_p.h \
    PushButton.h \
    PushButton_p.h \
    SlideView.h \
    SlideView_p.h \
    SplitView.h \
    SplitView_p.h \
    SwitchBox.h \
    SwitchBox_p.h \
    ToolButton.h \
    ToolButton_p.h \
    flatgui_global.h \
    GenericForm.h \
    GenericForm_p.h \
    GridWidget.h \
    GridWidget_p.h \
    LineEdit.h \
    ListItemAnimation.h \
    MonthView.h \
    NavigationBar.h \
    NavigationBar_p.h \
    PageCategories.h \
    PageIndicator.h \
    PersonNameValidator.h \
    PixmapBuilder.h \
    PixmapBuilder_p.h \
    SearchForm.h \
    SearchForm_p.h \
    SidePanel.h \
    SimpleMessage.h \
    Splash.h \
    StaticDecoration.h \
    TextDataModel.h \
    TextEditor.h \
    TextField.h \
    TextDataModel_p.h \
    TimeDataModel.h \
    TimeDataModel_p.h \
    TimeEditor.h \
    TimeField.h \
    ToolBar.h \
    ValidatorFactory.h

PUBLIC_HEADERS += \
    AbstractButton.h \
    AbstractDataModel.h \
    AbstractDecoration.h \
    AbstractEditor.h \
    AbstractField.h \
    AbstractPanel.h \
    AbstractValidator.h \
    Alert.h \
    ButtonCategory.h \
    DateDataModel.h \
    DateEditor.h \
    DateField.h \
    DoubleValidator.h \
    DynamicDecoration.h \
    FancyField.h \
    HorizontalSlide.h \
    MonthPage.h \
    PushButton.h \
    SlideView.h \
    SplitView.h \
    SwitchBox.h \
    ToolButton.h \
    flatgui_global.h \
    GenericForm.h \
    GridWidget.h \
    LineEdit.h \
    ListItemAnimation.h \
    MonthView.h \
    NavigationBar.h \
    PageCategories.h \
    PageIndicator.h \
    PersonNameValidator.h \
    PixmapBuilder.h \
    SearchForm.h \
    SidePanel.h \
    SimpleMessage.h \
    Splash.h \
    StaticDecoration.h \
    TextDataModel.h \
    TextEditor.h \
    TextField.h \
    TimeDataModel.h \
    TimeEditor.h \
    TimeField.h \
    ToolBar.h \
    ValidatorFactory.h

OTHER_FILES += \
    FlatGui.qdocconf \
    FlatGui.qdoc

RESOURCES += \
    guires.qrc

headers.path    = $$PWD/../deploy/include
headers.files   += $$PUBLIC_HEADERS
INSTALLS       += headers
