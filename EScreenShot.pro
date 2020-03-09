QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CFLAGS				+=	-Wno-deprecated-copy
CFLAGS				+=	-Wno-unused-parameter
CFLAGS				+=	-Wno-reorder

QMAKE_CXXFLAGS		+=	-std=c++11 $${CFLAGS}
QMAKE_CFLAGS		+=	-std=gnu11 $${CFLAGS}

CONFIG += c++11

DESTDIR				+=	release
MOC_DIR				+=	release
OBJECTS_DIR			+=	release
DEPENDPATH			+=	release
RCC_DIR				+=	release
UI_DIR				+=	release

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += src

SOURCES += \
    src/main.cpp \
    src/widget.cpp \
	src/setting.cpp \
	src/editor.cpp \
	src/layer.cpp \
	src/view.cpp \
	src/action.cpp \
	src/undo_redo.cpp

HEADERS += \
    src/widget.h \
	src/setting.h \
	src/editor.h \
	src/layer.cpp \
	src/view.h \
	src/action.h \
	src/undo_redo.h

FORMS += \
    src/widget.ui \
	src/editor.ui

RESOURCES +=	res/resources.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
