import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
Rectangle{
    id: root
    anchors.fill: parent
    color: "#ffffff"

    Loader{
        id: imageImportLoader
        signal fileChosen
        sourceComponent: portraitImport
        active: false
        asynchronous: true
        visible: status == Loader.Ready
        onFileChosen: {active=true;}
        anchors.top: root.top
        anchors.topMargin: 50
        anchors.horizontalCenter: root.horizontalCenter
        height: 0
        width: 0
    }
    Component{
        id: portraitImport
        Image{
            id: portraitImage
            antialiasing: true
            cache: true
            fillMode: Image.PreserveAspectFit
            source:fileDialog.fileUrl
            smooth: true
            Component.onCompleted: {root.state = 'expand'}
        }
    }

    Button{
        id: fileBrowseButton
        anchors.horizontalCenter: imageImportLoader.horizontalCenter
        anchors.top: imageImportLoader.bottom
        anchors.topMargin: 50
        text: qsTr("Browse for image")
        onClicked: fileDialog.open()
    }

    TextField{
        id: nameField
        anchors.verticalCenter: imageImportLoader.verticalCenter
        anchors.right: root.right
        anchors.rightMargin: 25
        width: 300
        placeholderText: qsTr("Enter Name")
        font.family: "abel"
        opacity: 0
    }
    TextField{
        id: positionsField
        anchors.top: nameField.bottom
        anchors.horizontalCenter: nameField.horizontalCenter
        anchors.topMargin: 15
        width: 300
        placeholderText: qsTr("Enter Positions worked")
        font.family: "abel"
        opacity: 0
    }

    Button{
        id: acceptButton
        objectName: "acceptNewPerson"
        anchors.top: positionsField.bottom
        anchors.horizontalCenter: positionsField.horizontalCenter
        anchors.topMargin: 10
        property var m_portrait
        property var m_name
        property var m_positions
        signal addPerson(var portrait, var name, var position, var resturant)
        height:40
        width:100
        opacity: 0
        Text{
            anchors.centerIn: parent
            text: qsTr("Accept")
            font.family: "abel"

        }
        onClicked: {
            if(positionsField.text.length > 0 && nameField.text.length > 0 && imageImportLoader.active === true) // if every field has text
            {
                m_name = nameField.text;
                m_positions = positionsField.text
                m_portrait = fileDialog.fileUrl
                acceptButton.addPerson(m_portrait, m_name, m_positions)
                console.log("field was clicked")
            }
        }
    }


    FileDialog{
        id: fileDialog
        signal fileChosen
        title: "please select applicable portrait image"
        nameFilters: ["Image Files (*.jpg *.png *.gif)", "All files (*)"]
        onAccepted: { imageImportLoader.fileChosen(); fileDialog.close();}
        onRejected: {fileDialog.close()}

    }

    states: State{
        name: "expand"
        PropertyChanges {target: imageImportLoader; height: 275; width: 150 }
    }
    transitions: Transition {
        from: "*"; to: "expand"
        NumberAnimation{properties: "height, width"; easing.type: Easing.InQuad; duration: 300}
        NumberAnimation { targets: [positionsField, nameField, acceptButton]; properties: "opacity"; from:0; to:1; duration: 1000 }
    }
}

