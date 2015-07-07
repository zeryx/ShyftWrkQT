TEMPLATE = app

QT += core\
    qml quick widgets \
    network

macx:CONFIG -= app_bundle

SOURCES += main.cpp \
    src/employeedata.cpp \
    src/schedulerdata.cpp \
    src/restclient.cpp \
    src/staffModel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML2_IMPORT_PATH = qml
# Default rules for deployment.
include(deployment.pri)

QTPLUGIN += QSQLMYSQL

HEADERS += \
    src/employeedata.h \
    src/schedulerdata.h \
    src/restclient.h \
    src/staffmodel.h
