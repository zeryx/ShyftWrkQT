import QtQuick 2.0
import QtQuick.Controls 1.2

Item{
    id: loginAssetsRoot
    opacity: 1
    objectName: "loginContext"
    property string m_username
    property string m_password
    property string m_organisation
    signal failMessage
    onFailMessage: {
        invalidCred.opacity = 1
    }
    function inputFinished(){
        if(loginAssetsRoot.m_username && loginAssetsRoot.m_password && loginAssetsRoot.m_organisation)
        {
            initialize.loggedInAuth.connect(mainWindowContext.loginAuth)
            mainWindowContext.authRequested(loginAssetsRoot.m_username,
                                             loginAssetsRoot.m_password,
                                             loginAssetsRoot.m_organisation)
        }
    }

    Item{
        id: invalidCred
        anchors.top: loginButton.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        opacity:0
        height: 15
        width: 30
        Text{
            id: invalidText
            anchors.centerIn: parent
            text: qsTr("Invalid username/password/organisation!")
            font.family: "Abel"
            color: Qt.lighter("red")
        }
    }

    Item{
        id: username
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
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
            onTextChanged: {loginAssetsRoot.m_username = usernameInputField.text}
            KeyNavigation.tab: passwordInputField
            BorderImage {
                id: usernameBorder
                source: "../assets/searchbox.jpg"
                anchors.fill: parent
                z: -1
            }
        }
    }

    Item{
        id: password
        anchors.top: username.bottom
        anchors.topMargin: 60
        anchors.horizontalCenter: parent.horizontalCenter
        height: passwordPrompt.height+30+passwordInputField.height
        width: passwordInputField.width+30
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
            onTextChanged: {loginAssetsRoot.m_password = passwordInputField.text}
            KeyNavigation.tab: organisationInputField
            BorderImage {
                id: passwordBorder
                source: "../assets/searchbox.jpg"
                anchors.fill: parent
                z: -1
            }

        }
    }

    Item{
        id: organisation
        anchors.top: password.bottom
        anchors.topMargin: 60
        anchors.horizontalCenter: parent.horizontalCenter
        height: organisationPrompt.height+30+organisationInputField.height
        width: organisationInputField.width+30
        Keys.onReturnPressed: {
            loginAssetsRoot.inputFinished()
        }

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
            onTextChanged: {loginAssetsRoot.m_organisation = organisationInputField.text}
            KeyNavigation.tab: loginButton
            BorderImage {
                id: organisationBorder
                source: "../assets/searchbox.jpg"
                anchors.fill: parent
                z:-1
            }
        }


    }

    Button{
        id: loginButton
        anchors.top: organisation.bottom
        anchors.topMargin: 25
        anchors.horizontalCenter: parent.horizontalCenter
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
}
