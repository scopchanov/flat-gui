QT += core gui widgets

TARGET = FlatGui
TEMPLATE = lib

TRANSLATIONS = \
    translations/FlatGui_de.ts \
    translations/FlatGui_ru.ts

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
    GridWidget_p.h

RESOURCES += \
    guires.qrc
