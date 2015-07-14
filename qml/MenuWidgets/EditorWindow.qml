import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import "../"
Item{
    id: root
    opacity: 1
    property string cachedImageSource
    property string mode
    Button{
        anchors.top: root.top
        anchors.topMargin: 45
        anchors.right: parent.right
        anchors.rightMargin: 10
        height: 40
        width: 75
        MouseArea{
            anchors.fill: parent
            onReleased: {
                var returnString = "MenuWidgets/MainWindow.qml"
                mainWindowContext.swapApps(returnString)
            }
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
            if(mainWindowContext.m_model) //if this window was made by edit person, auto-populate edit params
            {
                active = false;
                root.cachedImageSource = mainWindowContext.m_model.portrait
                sourceComponent = cachedComponent;
                active = true;
                firstNameField.text = mainWindowContext.m_model.name
                positionsField.text = mainWindowContext.m_model.position
                uidField.text = mainWindowContext.m_model.uid
                uidField.readOnly = true
                root.mode = "edit"
            }
            else{
                root.mode = "new"
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
        MouseArea{
            anchors.fill: parent
            onReleased: fileDialog.open()
        }
    }

    TextField{
        id: firstNameField
        anchors.verticalCenter: imageImportLoader.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 25
        width: 300
        placeholderText: qsTr("Enter first name.")
        font.family: "abel"
    }

    TextField{
        id: lastNameField
        anchors.top: firstNameField.bottom
        anchors.topMargin: 15
        anchors.horizontalCenter: firstNameField.horizontalCenter
        width: 300
        placeholderText: qsTr("Enter last name.")
        font.family: "abel"
    }

    TextField{
        id: uidField
        anchors.top: lastNameField.bottom
        anchors.topMargin: 15
        anchors.horizontalCenter: lastNameField.horizontalCenter
        width: 300
        placeholderText: qsTr("Enter shyft id, if applicable.")
        font.family: "abel"
    }

    TextField{
        id: positionsField
        anchors.top: uidField.bottom
        anchors.horizontalCenter: lastNameField.horizontalCenter
        anchors.topMargin: 15
        width: 300
        placeholderText: qsTr("Enter positions, separated by commas")
        font.family: "abel"
    }

    Button{
        id: acceptButton
        objectName: "acceptNewPerson"
        anchors.top: positionsField.bottom
        anchors.horizontalCenter: positionsField.horizontalCenter
        anchors.topMargin: 10
        property string m_portrait
        property string m_fname
        property string m_lname
        property string m_positions
        property string m_uid: "" // can be null
        signal modifyPerson
        onModifyPerson: {
            mainWindowContext.swapApps("MenuWidgets/MainWindow.qml")
        }

        height:40
        width:100
        Text{
            anchors.centerIn: parent
            text: qsTr("Accept")
            font.family: "abel"
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                if(positionsField.text.length > 0 &&
                        firstNameField.text.length > 0 &&
                        lastNameField.text.length > 0 &&
                        imageImportLoader.active === true) // if every major field has stuff
                {
                    var portraitstr = root.cachedImageSource.replace("http://www.shyftwrk.com", "..")
                    console.log(portraitstr)
                    masterModel.setJson("first name", firstNameField.text)
                    masterModel.setJson("last name", lastNameField.text)
                    masterModel.setJson("positions", positionsField.text)
                    masterModel.setJson("portrait", portraitstr.toString())
                    masterModel.setJson("uid", uidField.text);
                    masterModel.setJson("mode", root.mode)
                    acceptButton.modifyPerson.connect(masterModel.alterStaff)
                    acceptButton.modifyPerson()
                }
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

