import QtQuick 2.0
import QtQuick.Controls 1.2

Item{
    id: loginAssetsRoot
    opacity: 1
    objectName: "loginContext"
    signal failMessage(string msg)
    onFailMessage: {
        invalidText.text = qsTr(msg)
        failMessageObject.opacity = 1
    }
    function inputFinished(){
        if(usernameInputField.text.length >0 && passwordInputField.text.length >0 && organisationInputField.text.length >0)
        {
            initialize.setJsonConfig("username", usernameInputField.text)
            initialize.setJsonConfig("password", passwordInputField.text)
            initialize.setJsonConfig("organisation", organisationInputField.text)
            initialize.loggedInAuth.connect(mainWindowContext.loginAuth)
            mainWindowContext.authRequested()
        }
    }

    Item{
        id: failMessageObject
        anchors.top: loginButton.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        opacity:0
        height: 15
        width: 30
        Text{
            id: invalidText
            anchors.centerIn: parent
            font.family: "Abel"
            color: Qt.lighter("red")
        }
    }
    Item{
        id: organisation
        anchors.top: parent.top
        anchors.topMargin: 60
        x: parent.width/2
        height: organisationPrompt.height+30+organisationInputField.height
        width: organisationInputField.width+30

        Text{
            id: organisationPrompt
            anchors.horizontalCenter: organisation.horizontalCenter
            anchors.top: organisation.top
            text: qsTr("Company")
            font.pointSize: 25
            font.family: "Abel"
        }
        TextInput{
            id: organisationInputField
            anchors.horizontalCenter: organisationPrompt.horizontalCenter
            anchors.top: organisationPrompt.bottom
            height: 25
            width: 200
            activeFocusOnPress: true
            selectByMouse: true
            KeyNavigation.tab: usernameInputField
            BorderImage {
                id: organisationBorder
                source: "../assets/searchbox.jpg"
                anchors.fill: parent
                z:-1
            }
            Component.onCompleted: {
                text = initialize.getJsonConfig("organisation")
            }
        }
    }
    Item{
        id: username
        anchors.horizontalCenter: organisation.horizontalCenter
        anchors.top: organisation.bottom
        anchors.topMargin: 25
        height: usernamePrompt.height+30+usernameInputField.height
        width: usernameInputField.width+30
        Text{
            id: usernamePrompt
            anchors.horizontalCenter: username.horizontalCenter
            anchors.top: username.top
            text: qsTr("User Name")
            font.pointSize:25
            font.family:"Abel"
        }

        TextInput{
            id: usernameInputField
            anchors.horizontalCenter: usernamePrompt.horizontalCenter
            anchors.top: usernamePrompt.bottom
            anchors.topMargin: 30
            height: 25
            width: 200
            activeFocusOnPress: true
            selectByMouse: true
            KeyNavigation.tab: passwordInputField
            BorderImage {
                id: usernameBorder
                source: "../assets/searchbox.jpg"
                anchors.fill: parent
                z: -1
            }
            Component.onCompleted: {
                text = initialize.getJsonConfig("username")
            }
        }
    }

    Item{
        id: password
        anchors.top: username.bottom
        anchors.topMargin: 60
        anchors.horizontalCenter: username.horizontalCenter
        height: passwordPrompt.height+30+passwordInputField.height
        width: passwordInputField.width+30
        Keys.onReturnPressed: {
            loginAssetsRoot.inputFinished()
        }
        Text{
            id: passwordPrompt
            anchors.horizontalCenter: password.horizontalCenter
            anchors.top: password.top
            text: qsTr("Password")
            font.pointSize:25
            font.family:"Abel"
        }

        TextInput{
            id: passwordInputField
            anchors.horizontalCenter: passwordPrompt.horizontalCenter
            anchors.top: passwordPrompt.bottom
            anchors.topMargin: 30
            height: 25
            width: 200
            echoMode: TextInput.Password
            activeFocusOnPress: true
            selectByMouse: true
            KeyNavigation.tab: loginButton
            BorderImage {
                id: passwordBorder
                source: "../assets/searchbox.jpg"
                anchors.fill: parent
                z: -1
            }
        }
    }



    Button{
        id: loginButton
        anchors.top: password.bottom
        anchors.topMargin: 25
        anchors.horizontalCenter: password.horizontalCenter
        height: 45
        width: 45
        text:qsTr("login")
        KeyNavigation.tab: usernameInputField

        MouseArea{
            id: loginMouseArea
            anchors.fill: parent

            onReleased: loginAssetsRoot.inputFinished()
        }
    }
    CheckBox{
        id: rememberInfoCheck
        anchors.verticalCenter: loginButton.verticalCenter
        anchors.left: loginButton.right
        anchors.leftMargin: 15
        text: qsTr("remember username and password")
    }
}
