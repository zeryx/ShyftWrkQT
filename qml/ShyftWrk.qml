import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQml.Models 2.1
import QtQml 2.2
import QtGraphicalEffects 1.0
ApplicationWindow{
    id: rootApplicationWindow
    visible: true
    width: Screen.width - 150
    height: Screen.height - 150
    minimumWidth: 480
    minimumHeight: 480
    color:themePrimary
    property color themeSecondary: Qt.darker("grey")
    property color themePrimary: "white"
    title: qsTr("ShyftWrk")
    Rectangle{
        id: banner
        height: 65
        anchors.top: parent.top
        width: parent.width
        color: themeSecondary
        z:10
        Text{
            id: bannerTextLayout
            anchors.horizontalCenter: banner.horizontalCenter
            anchors.verticalCenter: banner.verticalCenter
            width: shyftText.width+wrkText.width
            height:shyftText.height+wrkText.height
            Text{
                id: shyftText
                anchors.verticalCenter: bannerTextLayout.verticalCenter
                color:"#ffffff"
                text: "Shyft"
                font.pointSize:40
                font.family:"Abel"

            }

            Text{
                id: wrkText
                anchors.verticalCenter: bannerTextLayout.verticalCenter
                anchors.left: shyftText.right
                color: "#5caa15"
                text:" Wrk"
                font.pointSize:40
                font.family:"Abel"
            }
        }
    }
    Item{
        id: mainWindowContext
        objectName: "mainWindowContext"
        height: rootApplicationWindow.height-banner.height
        width: rootApplicationWindow.width-searchLoader.width
        anchors.right: searchLoader.left
        anchors.top: banner.bottom
        signal authRequested()
        function mainGate(bool){
            if(bool)
                swapApps("MenuWidgets/MainWindow.qml")

        }
        property var m_model
        anchors{
            top: banner.bottom
            right: banner.right
            left: banner.left
        }
        function swapApps(source, model)
        {
            if(model){
                m_model = model
            }

            else
                m_model = 0
            if(mainLoader.source == "qrc:///qml/MenuWidgets/LoginWindow.qml"){
                searchLoader.source = "ScrollableEmployeeColumn.qml"
                searchLoader.active = true
                searchLoader.visible = true
            }

            mainLoader.visible = false
            mainLoader.active = false
            if(source) // if called without a source, this would refresh whatever is loaded
                mainLoader.source = source
            else{
                searchLoader.active = false
                searchLoader.active = true
            }
            mainLoader.active = true
            mainLoader.visible = true
            return
        }

        Loader{
            id: mainLoader
            width: parent.width
            height: parent.height
            anchors.fill: parent
            source: "MenuWidgets/LoginWindow.qml"
            visible: status == Loader.Ready
            Behavior on visible{
                NumberAnimation {
                    target: mainLoader.item;
                    property: "opacity";
                    from:!visible; to: visible;
                    duration: 200;
                    easing.type: Easing.InOutQuad }}
        }
    }
    Loader{
        id: searchLoader
        width: 160
        height: parent.height-banner.height;
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        visible: false
        Behavior on visible{
            NumberAnimation {
                target: mainLoader.item;
                property: "opacity";
                from:!visible; to: visible;
                duration: 200;
                easing.type: Easing.InOutQuad }}

    }
}
