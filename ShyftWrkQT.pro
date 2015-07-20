TEMPLATE = app

QT += core\
    qml quick widgets \
    network\

macx:CONFIG -= app_bundle

CONFIG += c++11

SOURCES += main.cpp \
    src/staffModel.cpp \
    src/modelClassComponents/employeedata.cpp \
    src/RESTful/staffrest.cpp \
    src/RESTful/rest.cpp \
    src/Files/configurationmanager.cpp \
    src/Files/abstract_FileManager.cpp \
    src/qmlnegotiator.cpp \
    src/manager.cpp \
    src/menuconstructor.cpp \
    src/shyftmenu.cpp \
    src/modelClassComponents/shiftdata.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML2_IMPORT_PATH = qml
# Default rules for deployment.
include(deployment.pri)

QTPLUGIN += QSQLMYSQL

HEADERS += \
    src/staffmodel.h \
    src/modelClassComponents/employeedata.h \
    src/RESTful/staffrest.h \
    src/RESTful/rest.h \
    src/Files/configurationmanager.h \
    src/Files/abstract_FileManager.h \
    src/qmlnegotiator.h \
    src/manager.h \
    src/menuconstructor.h \
    src/shyftmenu.h \
    src/modelClassComponents/shiftdata.h

QMAKE_CXXFLAGS += -g

OTHER_FILES +=
