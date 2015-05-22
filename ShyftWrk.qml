import QtQuick 2.2
import QtQml.Models 2.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Window 2.0
import "assets" as MyAssets
import "."
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
        height: 80
        anchors.top: parent.top
        width: parent.width
        color: themeSecondary
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
    ScrollableEmployeeColumn{
        id: employeeColumn
        width: 200
        height: parent.height-banner.height
        anchors.right: parent.right
        anchors.top: banner.bottom
    }
    TabView{
        id: mainTabView
        anchors.top: banner.bottom
        anchors.right: employeeColumn.left
        anchors.left: banner.left
        anchors.bottom: parent.bottom

        Tab{
            id: shiftSchedulerTab
            title: "Shift Scheduling"
            ShiftScheduler {
                id:myShiftScheduler
                width: mainTabView.width
                anchors.top: parent.top
                anchors.topMargin: 20
                color: themePrimary
            }
        }
        Tab{
            id: employeeEditorTab
            title: "Employee Editor"
            EmployeeEditor{
                id:myEmployeeEditor
                width: mainTabView.width
                anchors.top: parent.top
                anchors.topMargin: 20
                color: themePrimary
            }
        }
        Tab{
            id: employeeViewTab
            title: "Employee Viewer"
            EmployeeViewer{
                id:myEmployeeViewer
                width: mainTabView.width
                anchors.top: parent.top
                anchors.topMargin: 20
            }
        }

        style: TabViewStyle{
            frameOverlap: 1
            tab: Rectangle{
                id: tab
                color:themeSecondary
                border.color: styleData.hovered ? "#5caa15" : "grey"
                implicitWidth: Math.max(text.width+4, 40)
                implicitHeight: 20
                radius: 1

                Text{
                    id: text
                    anchors.centerIn: parent
                    text: styleData.title
                    color: styleData.selected ? "#5caa15" : "white"
                    font.family: "abel"
                }
            }
            frame: Rectangle{ color: themePrimary}
            tabBar: Rectangle{ color: themePrimary}
        }
    }
}
