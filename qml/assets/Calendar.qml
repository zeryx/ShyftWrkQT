import QtQuick 2.0
import QtQuick.Controls 1.3
Rectangle {
id: root
property var currentlySelectedDate;

Text{
    id: dateText
    anchors.fill: parent
    color: themePrimary
    anchors.horizontalCenter: parent.horizontalCenter
    text: !currentlySelectedDate? "Set a date, partner." : currentlySelectedDate.toLocaleDateString()
}

    Loader{
        id: calendarLoader
        height: 500
        width: 500
        anchors.top: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        sourceComponent: calendarComponent
        Component.onCompleted: { visible = false}
    }

    MouseArea {
        id: sDayButtonMouseArea
        //anchor all sides of the mouse area to fill the rectangle
        anchors.fill: parent
        onClicked: {
            calendarLoader.visible = (calendarLoader.visible === false ? true : false)
        }
    }

    Component{
        id: calendarComponent
        Calendar{
            id: calendarInst
            weekNumbersVisible: true
            onClicked: {
                currentlySelectedDate = date;
            }
        }
    }
}
