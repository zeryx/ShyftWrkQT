import QtQuick 2.0

Rectangle {
    id: root
    anchors.fill: parent
    color: "red";
    Rectangle{
        color: "blue"
        height: 10
        width: 10
        anchors.top: root.top
        anchors.left: root.left
        MouseArea{
            anchors.fill: parent
            onClicked: {
                aAgLoader.source = " "
            }
        }
    }
}
