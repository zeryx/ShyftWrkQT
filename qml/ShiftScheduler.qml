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
        z:100
        anchors.top: parent.top
        anchors.left: parent.left
        height: 75
        width: mainWindowContext.width
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
