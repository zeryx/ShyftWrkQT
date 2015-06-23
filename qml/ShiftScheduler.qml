import QtQuick 2.0
import QtQuick.Layouts 1.1
import "assets" as MyAssets
Rectangle{
    id: root

    property string dstring: "Monday"
    property int ditr: 0
    //create the size of the day spinner to be the full width, with the height equal to the buttons
    width: parent.width

    MyAssets.Calendar {
        id: daySelector
        color: themeSecondary
        width: 200; height: 25
        z:100
        anchors.horizontalCenter: root.horizontalCenter
    }
    MyAssets.ScheduleViewingPane{
        height: parent.height - daySelector.height-20
        z:1
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.bottom: parent.bottom
    }
}
