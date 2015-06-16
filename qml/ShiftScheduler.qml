import QtQuick 2.0
import QtQuick.Layouts 1.1
import "assets" as MyAssets
Rectangle{
    id: root
    property variant days: [qsTr("Monday"), qsTr("Tuesday"),
        qsTr("Wednesday"), qsTr("Thursday"), qsTr("Friday"), qsTr("Saturday"), qsTr("Sunday")]
    property string dstring: "Monday"
    property int ditr: 0
    //create the size of the day spinner to be the full width, with the height equal to the buttons
    width: parent.width

    Row {
        id:daySpinner
        anchors.horizontalCenter: parent.horizontalCenter
        height: selectedDay.height
        spacing: 2
        MyAssets.Clickable{
            source:"assets/icons/arrow_left.svg"
            height: selectedDay.height
            onClicked: {
                ditr--
                if(ditr<0)
                    ditr=6;
                dstring = days[ditr];
            }
        }


        Rectangle {
            id: selectedDay
            color: "grey"
            width: 200; height: 75
            radius: 5
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


        MyAssets.Clickable{
            source:"assets/icons/arrow_right.svg"
            height: selectedDay.height
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
    MyAssets.ScheduleViewingPane{
        height: parent.height - daySpinner.height
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
    }
}
