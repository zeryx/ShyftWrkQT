import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
Rectangle{
    id: root
    anchors.fill: parent
    color: "#ffffff"

    Loader{
        id: portraitImportLoader
        signal fileChosen
        sourceComponent: undefined
        asynchronous: true
        visible: status == Loader.Ready
        onFileChosen: {portraitImportLoader.sourceComponent = portraitImport}
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
        anchors.horizontalCenter: portraitImportLoader.horizontalCenter
        anchors.top: portraitImportLoader.bottom
        anchors.topMargin: 50
        id: fileBrowseButton
        text: "Browse for image"
        onClicked: fileDialog.open()
    }

    TextField{
        anchors.top: fileBrowseButton.bottom
        anchors.horizontalCenter: root.horizontalCenter
        anchors.topMargin: 40
        width: 300
        id: nameInput
        placeholderText: "Enter Name"
        font.family: "abel"

    }
    TextField{
        anchors.top: nameInput.bottom
        anchors.horizontalCenter: root.horizontalCenter
        anchors.topMargin: 15
        width: 300
        id: positionsWorkable
        placeholderText: "Enter Positions worked"
        font.family: "abel"
    }


    FileDialog{
        id: fileDialog
        signal fileChosen
        title: "please select applicable portrait image"
        nameFilters: ["Image Files (*.jpg *.png *.gif)", "All files (*)"]
        onAccepted: {
            portraitImportLoader.fileChosen();
            fileDialog.close();
        }
        onRejected: {
            console.log("something went wrong!?")
            fileDialog.close()
        }

    }

    states: State{
        name: "expand"
        PropertyChanges {target: portraitImportLoader; height: 275; width: 150 }
    }
    transitions: Transition {
        from: "*"; to: "expand"
        NumberAnimation{
            properties: "height, width"; easing.type: Easing.InQuad; duration: 300}
    }
}

