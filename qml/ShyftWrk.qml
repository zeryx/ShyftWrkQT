import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.0
import QtQml.Models 2.1
import QtQml 2.2
import QtGraphicalEffects 1.0
ApplicationWindow{
    id: root
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
        height: root.height-banner.height
        width: root.width
        signal mainAppStarted
        property var m_model
        anchors{
            top: banner.bottom
            right: banner.right
            left: banner.left
        }
        function swapApps(source, model)
        {
            if(model)
            {
                m_model = model
            }
            else
            {
                m_model = 0
            }

            mainLoader.visible = false
            mainLoader.active = false
            mainLoader.source = source
            mainLoader.active = true
            if(source === "MenuWidgets/MainWindow.qml") //if this is the main application window, pull from HTTP
                mainAppStarted()
            mainLoader.visible = true

            return
        }

        Loader{
            id: mainLoader
            anchors.fill: parent
            source: "MenuWidgets/LoginWindow.qml"
            Behavior on visible{
                NumberAnimation {
                    target: mainLoader.item;
                    property: "opacity";
                    from:!visible; to: visible;
                    duration: 200;
                    easing.type: Easing.InOutQuad }}

        }

    }
}
