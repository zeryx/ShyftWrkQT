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
    Image{
        anchors.top: daySpinner.bottom
        anchors.horizontalCenter: daySpinner.horizontalCenter
        source: "assets/sampleportrait.jpg"
        asynchronous: true
        smooth: true
        width: 100; height: 200
        fillMode: Image.PreserveAspectFit
    }
}
