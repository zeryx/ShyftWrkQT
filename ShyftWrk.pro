TEMPLATE = app

QT += qml quick widgets \
    sql


SOURCES += main.cpp \
    src/employeedata.cpp \
    src/employeeModelList.cpp \
    src/employeemodeltable.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

QTPLUGIN += QSQLMYSQL

HEADERS += \
    src/employeedata.h \
    src/employeeModelList.h \
    src/employeemodeltable.h
