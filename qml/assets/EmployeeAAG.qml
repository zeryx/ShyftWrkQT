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
        Text{
            id: indexNumber
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            text: m_index ? m_index : " "
        }
        Text{
            id: itemParameters
            anchors.top: indexNumber.bottom
            anchors.left: indexNumber.left
            text: m_name ? m_name : " "
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                aAgLoader.visible = false;
            }
        }
    }
}
