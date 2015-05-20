import QtQuick 2.0
import QtQuick.Controls 1.2
Rectangle{
    anchors.fill: parent
    color: "light grey"
    property string importSource;
    Rectangle
    {
        Image{
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            id: portraitImport
            source: importSource
        }

        TextField{
            anchors.top: portraitImport.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 15
            id: nameInput
            placeholderText: "Enter Name"
            font.family: "abel"

        }
        TextField{
            anchors.top: nameInput.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 15
            id: positionsWorkable
            placeholderText: "Enter Positions"
            font.family: "abel"
        }
    }

}

