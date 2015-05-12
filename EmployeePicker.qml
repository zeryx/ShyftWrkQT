import QtQuick 2.2
import QtQuick.Controls 1.1

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: qsTr("ShyftWrk")
    menuBar: MenuBar {
        Menu {
            title: qsTr("Day")
            MenuItem {
                text: qsTr("Monday")
                onTriggered: dstring= days[0]
                }
            MenuItem {
                text: qsTr("Tuesday")
                onTriggered: dstring= days[1]
                }
        }
    }
    property variant days: [qsTr("Monday"), qsTr("Tuesday"),
        qsTr("Wednesday"), qsTr("Thursday"), qsTr("Friday"), qsTr("Saturday"), qsTr("Sunday")]
    property string dstring: "Monday"
    property int ditr: 0

    Item{
        width: parent.width
        height:backDay.width
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 5
            spacing: 2
            Rectangle {
                id: backDay
                color: "grey"
                width: bDayButton.contentWidth+2; height: 75
                Text {
                    id: bDayButton
                    anchors.centerIn: parent
                    text: qsTr("back")
                    }
                MouseArea{
                    id: bDayButtonMouseArea
                    anchors.fill: parent
                    onClicked: {

                        ditr--
                        if(ditr<0)
                        {
                            ditr=6
                        }
                        dstring = days[ditr]
                    }
                }
            }


            Rectangle {
                id: selectedDay
                color: "blue"
                width: 150; height: 75
                Text {
                    id: sDayButton
                    anchors.centerIn: parent
                    text: dstring
                }
                MouseArea {
                    id: sDayButtonMouseArea
                    //anchor all sides of the mouse area to fill the rectangle
                    anchors.fill: parent
                    onClicked: console.log(sDayButton.text + "niggers")
                }
            }


            Rectangle {
                id: forwardDay
                color: "grey"
                width: fDayButton.contentWidth+2; height: 75
                Text {
                    id: fDayButton
                    anchors.centerIn: parent
                    text: qsTr("forward")
                }
                MouseArea{
                    id: fDayButtonMouseArea
                    anchors.fill: parent
                    onClicked: {

                        ditr++
                        if(ditr>6)
                        {
                            ditr=0
                        }
                        dstring = days[ditr]
                    }
                }
            }

        }
    }

}
