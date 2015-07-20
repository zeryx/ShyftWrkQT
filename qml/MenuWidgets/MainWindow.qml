import QtQuick 2.0
import "../"
Item {
    id: mainAppRoot
    opacity: 0
    StaffGraph {
        id:staffGraph
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        color: themePrimary
    }
}
