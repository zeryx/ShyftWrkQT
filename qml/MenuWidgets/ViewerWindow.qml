import QtQuick 2.0
import "../"
Item{
    id: root
    opacity: 1
    ScrollableEmployeeColumn{
        id: employeeColumn
        width: 160
        height: parent.height
        anchors.right: parent.right
        anchors.top: parent.top
        z:-1
    }
    Rectangle{
        id: viewPanel
        height: 500
        width: 500
        anchors.centerIn: parent
        BorderImage {
            id: name
            source: "../assets/searchbox.jpg"
            width: parent.width;
            height: parent.height;
            border.left: 5; border.top: 5
            border.right: 5; border.bottom: 5
        }
        Loader{
            id: portraitLoader
            height: 200
            width: 200
            sourceComponent: portraitComponent
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Component{
        id: portraitComponent
        Image{
            id: portraitImage
            anchors.fill: parent
            antialiasing: true
            cache: true
            fillMode: Image.Stretch
            smooth: true
            Component.onCompleted: {
                if(mainWindowContext.m_model)
                {
                    portraitImage.source = mainWindowContext.m_model.portrait
                }
            }
        }
    }
}
