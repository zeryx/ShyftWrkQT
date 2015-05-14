import QtQuick 2.0

Rectangle{
    //In this window there are two major functions, the day spinner and the employee portrait table.
    property variant days: [qsTr("Monday"), qsTr("Tuesday"),
        qsTr("Wednesday"), qsTr("Thursday"), qsTr("Friday"), qsTr("Saturday"), qsTr("Sunday")]
    property string dstring: "Monday"
    property int ditr: 0
    //create the size of the day spinner to be the full width, with the height equal to the buttons
    width: parent.width
    Row {
        id:daySpinner
        anchors.horizontalCenter: parent.horizontalCenter
        height: backDay.height
        spacing: 2
        // the colors and widths will be replaced with style sheet
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
            width: 120; height: 75
            Text {
                id: sDayButton
                anchors.centerIn: parent
                text: dstring
            }
            MouseArea {
                id: sDayButtonMouseArea
                //anchor all sides of the mouse area to fill the rectangle
                anchors.fill: parent
                onClicked: employeeRowModel.append({
                                                         "name": days[ditr],
                                                         "score":"help"
                                                     })
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
    ListModel{
        id:employeeRowModel
    }

    Row{
        anchors.top: daySpinner.bottom
        anchors.horizontalCenter: daySpinner.horizontalCenter
        anchors.topMargin: 10
        spacing: 5
        Repeater{
            anchors.top: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            Component{
                id:rowDelegate
                Rectangle{
                    width:150; height: 50
                    Text{text: name; anchors.horizontalCenter: parent.horizontalCenter; id: nametest}
                    Text{ text: score; anchors.horizontalCenter: parent.horizontalCenter; anchors.top: nametest.bottom}
                }
            }
            model: employeeRowModel
            delegate: rowDelegate
            focus: true
//            Repeater{
//                anchors.top: parent.bottom
//                Component{
//                    id: columnDelegate
//                    Rectangle{
//                        width: 150; height: 50
//                        Text{text:
//                    }
//                }
//            }

        }
    }
}
