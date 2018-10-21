TEMPLATE = app

QT += location

SOURCES += main.cpp \
    backend.cpp \
    datapoint.cpp \
    datatrack.cpp \
    datafull.cpp \
    visualpoint.cpp \
    visualtrack.cpp

RESOURCES += qml.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/location/minimal_map
INSTALLS += target

HEADERS += \
    backend.h \
    datapoint.h \
    datatrack.h \
    datafull.h \
    visualpoint.h \
    visualtrack.h

CONFIG+=qml_debug
