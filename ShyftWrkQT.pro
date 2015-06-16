TEMPLATE = app

QT += qml quick widgets \
    sql

macx:CONFIG -= app_bundle

SOURCES += main.cpp \
    src/employeedata.cpp \
    src/employeeModelMaster.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

QTPLUGIN += QSQLMYSQL

HEADERS += \
    src/employeedata.h \
    src/employeeModelMaster.h
