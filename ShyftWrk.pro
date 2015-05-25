TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    src/employeemodel.cpp \
    src/filtermodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/employeemodel.h \
    src/filtermodel.h

DISTFILES +=
