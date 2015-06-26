import QtQuick 2.0
import "../"
Item {
    id: mainAppRoot
    opacity: 0
    ScrollableEmployeeColumn{
        id: employeeColumn
        width: 160
        height: parent.height
        anchors.right: parent.right
        anchors.top: parent.top
        z:-1
    }
    ShiftScheduler {
        id:myShiftScheduler
        anchors.top: parent.top
        anchors.right: employeeColumn.left
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        color: themePrimary
    }
}
