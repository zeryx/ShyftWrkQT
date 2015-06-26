TEMPLATE = app

QT += qml quick widgets \
    sql

macx:CONFIG -= app_bundle

SOURCES += main.cpp \
    src/employeedata.cpp \
    src/employeeModelMaster.cpp \
    src/schedulerdata.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML2_IMPORT_PATH = qml
# Default rules for deployment.
include(deployment.pri)

QTPLUGIN += QSQLMYSQL

HEADERS += \
    src/employeeModelMaster.h \
    src/employeedata.h \
    src/schedulerdata.h
