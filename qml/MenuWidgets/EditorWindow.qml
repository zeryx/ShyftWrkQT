import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
Item{
    id: root
    opacity: 1
    property url cachedImageSource
    Button{
        anchors.top: root.top
        anchors.topMargin: 45
        anchors.right: root.right
        anchors.rightMargin: 10
        height: 40
        width: 75
        onClicked: {
            var returnString = "MenuWidgets/MainWindow.qml"
            mainWindowContext.swapApps(returnString)
        }
        Text{
            anchors.centerIn: parent
            text: "Back"
            font.family: "abel"
        }
    }

    Loader{
        id: imageImportLoader
        signal fileChosen
        sourceComponent: placeholderComponent
        onFileChosen: {
            active = false;
            sourceComponent = portraitComponent
            active=true;
        }
        anchors.top: root.top
        anchors.topMargin: 50
        anchors.horizontalCenter: root.horizontalCenter
        width: 200
        height: 200
        Component.onCompleted: {
            if(mainWindowContext.m_model)
            {
                active = false;
                root.cachedImageSource = mainWindowContext.m_model.portrait
                sourceComponent = cachedComponent;
                active = true;
                nameField.text = mainWindowContext.m_model.name
                positionsField.text = mainWindowContext.m_model.position
            }
        }
    }
    Component{
        id: portraitComponent
        Image{
            id: portraitImage
            anchors.fill: parent
            antialiasing: true
            cache: true
            fillMode: Image.Stretch
            source:fileDialog.fileUrl
            smooth: true
        }
    }

    Component{
        id: placeholderComponent
        BorderImage {
            id: frame
            source: "../assets/searchbox.jpg"
            anchors.fill: parent
            border.left: 5; border.top: 5
            border.right: 5; border.bottom: 5
            Text{
                anchors.centerIn: parent
                text: qsTr("drag employee here \nto edit")
            }
        }
    }

    Component{
        id: cachedComponent
        Image{
            id: cachedImage
            anchors.fill: parent
            antialiasing: true
            cache: true
            fillMode: Image.Stretch
            source:root.cachedImageSource
            smooth: true
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
    }
    TextField{
        id: positionsField
        anchors.top: nameField.bottom
        anchors.horizontalCenter: nameField.horizontalCenter
        anchors.topMargin: 15
        width: 300
        placeholderText: qsTr("Enter Positions worked")
        font.family: "abel"
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
                console.log("field was clicked")
            }
        }
    }


    FileDialog{
        id: fileDialog
        signal fileChosen
        title: qsTr("please select applicable portrait image")
        nameFilters: ["Image Files (*.jpg *.png *.gif)", "All files (*)"]
        onAccepted: { imageImportLoader.fileChosen(); fileDialog.close();}
        onRejected: {fileDialog.close()}

    }

}

