import QtQuick 2.0
import QtQuick.Controls 1.2

Item{
    id: loginAssetsRoot
    opacity: 1
    property string m_username
    property string m_password

    Item{
        id: username
        objectName: "usernameInput"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 25
        height: usernamePrompt.height+30+usernameInputField.height
        width: parent.width
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
            BorderImage {
                id: usernameBorder
                source: "../assets/searchbox.jpg"
                anchors.fill: parent

                z: -1
            }
            activeFocusOnPress: true
            onTextChanged: {loginAssetsRoot.m_username = usernameInputField.text}
        }
    }

    Item{
        id: password
        anchors.top: username.bottom
        anchors.topMargin: 60
        anchors.horizontalCenter: parent.horizontalCenter
        objectName: "passwordInput"
        height: passwordPrompt.height+30+passwordInputField.height
        width:parent.width


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
            BorderImage {
                id: passwordBorder
                source: "../assets/searchbox.jpg"
                anchors.fill: parent

                z: -1
            }
            activeFocusOnPress: true
            onTextChanged: {loginAssetsRoot.m_password = passwordInputField.text}
        }
    }

    Button{
        id: loginButton
        anchors.top: password.bottom
        anchors.topMargin: 25
        anchors.horizontalCenter: parent.horizontalCenter
        height: 45
        width: 45
        text:qsTr("login")

        MouseArea{
            anchors.fill: parent
            onReleased: {
                if(loginAssetsRoot.m_username !== " " && loginAssetsRoot.m_password !== " ")
                {
                    var mainWindowString = "MenuWidgets/MainWindow.qml"
                    mainWindowContext.swapApps(mainWindowString)
                }
            }
        }
    }
}
