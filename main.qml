import QtQuick 2.2
import QtQml.Models 2.1
import QtQuick.Controls 1.1
ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: qsTr("ShyftWrk")
    menuBar : MenuBar{
        Menu{
            title: qsTr("File")
            MenuItem{
                text: qsTr("Import")
            }
            MenuItem{
                text: qsTr("Export")
            }
            MenuItem{
                text: qsTr("Save")
            }
            MenuItem{
                text: qsTr("Exit")
                onTriggered: Qt.quit()
            }
        }
    }

    ObjectModel{
        id: menuListModel
        ShiftScheduler {
            width: menuListView.width
            anchors.top: parent.top
            anchors.topMargin: 100
        }
        EmployeeEditor{
            width: menuListView.width
            anchors.top: parent.top
            anchors.topMargin: 100
        }

    }




    ListView {
        id: menuListView

        // Anchors are set to react to window anchors
        anchors.fill: parent
        anchors.bottom: parent.bottom
        width: parent.width
        height: parent.height

        // The model contains the data
        model: menuListModel

        // Control the movement of the menu switching
        snapMode: ListView.SnapOneItem
        orientation: ListView.Horizontal
        boundsBehavior: Flickable.StopAtBounds
        flickDeceleration: 5000
        highlightFollowsCurrentItem: true
        highlightMoveDuration: 240
        highlightRangeMode: ListView.StrictlyEnforceRange
    }

    Row{
        id: labelList
        z: 1
        anchors.topMargin: 5
        spacing: 40
        anchors.horizontalCenter: parent.horizontalCenter
        width: schedulerButton.width

        Rectangle{
            id: schedulerButton
            width: schedulerButtonText.contentWidth+2
            height: schedulerButtonText.contentHeight+45
            MouseArea{
                anchors.fill: parent
                onClicked: menuListView.currentIndex=0
            }
            Text{
                id: schedulerButtonText
                text: qsTr("Shift Scheduler")
                anchors.centerIn: parent
            }
        }

        Rectangle{
            id: employeeButton
            width: employeeButtonText.contentWidth+2
            height: employeeButtonText.contentHeight+45
            MouseArea{
                anchors.fill: parent
                onClicked: menuListView.currentIndex=1
            }
            Text{
                id: employeeButtonText
                text: qsTr("Employee Managment")
                anchors.centerIn: parent
            }
        }

    }


}
