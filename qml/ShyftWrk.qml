import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.0
import QtQml.Models 2.1
import QtQml 2.2
import QtQuick.Controls.Styles 1.2
import "assets" as MyAssets
import QtGraphicalEffects 1.0

import "."
ApplicationWindow{
    id: root
    visible: true
    width: Screen.width - 150
    height: Screen.height - 150
    minimumWidth: 480
    minimumHeight: 480
    color:themePrimary
    property color themeSecondary: Qt.darker("grey")
    property color themePrimary: "white"
   title: qsTr("ShyftWrk")
    Rectangle{
        id: banner
        height: 65
        anchors.top: parent.top
        width: parent.width
        color: themeSecondary
        z:10
        Text{
            id: bannerTextLayout
            anchors.horizontalCenter: banner.horizontalCenter
            anchors.verticalCenter: banner.verticalCenter
            width: shyftText.width+wrkText.width
            height:shyftText.height+wrkText.height
            Text{
                id: shyftText
                anchors.verticalCenter: bannerTextLayout.verticalCenter
                color:"#ffffff"
                text: "Shyft"
                font.pointSize:40
                font.family:"Abel"

            }

            Text{
                id: wrkText
                anchors.verticalCenter: bannerTextLayout.verticalCenter
                anchors.left: shyftText.right
                color: "#5caa15"
                text:" Wrk"
                font.pointSize:40
                font.family:"Abel"
            }
        }
    }
    Item{
        id: mainWindowContext
        height: root.height-banner.height
        width: root.width
        anchors{
            top: banner.bottom
            right: banner.right
            left: banner.left
        }
        function swapApps()
        {
            loginLoader.visible = false
            mainAppLoader.visible = true
            loginLoader.active = false
            loginLoader.destroy()
            return
        }
//        states: [
//            State{
//                name: "LoginDestroyed"

//            },
//            State{
//                name: "mainAppVisible"
//            }

//        ]
        Loader{
            id: loginLoader
            anchors.fill: parent
            sourceComponent: loginAssetsComponent
            Behavior on visible{
                NumberAnimation {
                    target: loginLoader.item;
                    property: "opacity";
                    from: 1; to: 0;
                    duration: 200;
                    easing.type: Easing.InOutQuad }}
            Component{
                id: loginAssetsComponent
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
                                id: simpleBorder
                                source: "assets/searchbox.jpg"
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
                                source: "assets/searchbox.jpg"
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

                        onClicked: {
                            if(loginAssetsRoot.m_username !== " " && loginAssetsRoot.m_password !== " ")
                            {
                                mainWindowContext.swapApps()
                            }
                        }
                    }
                }
            }
        }
        Loader{
            id: mainAppLoader
            height: parent.height
            width: parent.width
            anchors.fill: parent
            sourceComponent: mainAppComponent
            visible: false
            Behavior on visible {NumberAnimation {
                    target: mainAppLoader.item;
                    property: "opacity";
                    from: 0; to: 1;
                    duration: 200;
                    easing.type: Easing.InOutQuad }}
            Component{
                id: mainAppComponent
                Item {
                    id: mainAppRoot
                    opacity: 0
                    ScrollableEmployeeColumn{
                        id: employeeColumn
                        width: 160
                        height: parent.height
                        anchors.right: parent.right
                        anchors.top: parent.top
                        z:-1
                    }
                    TabView{
                        id: mainTabView
                        anchors.top: parent.top
                        anchors.right: employeeColumn.left
                        anchors.left: parent.left
                        anchors.bottom: parent.bottom

                        Tab{
                            id: shiftSchedulerTab
                            title: qsTr("Shift Scheduling")
                            ShiftScheduler {
                                id:myShiftScheduler
                                width: mainTabView.width
                                anchors.top: parent.top
                                anchors.topMargin: 5
                                color: themePrimary
                            }
                        }
                        Tab{
                            id: employeeEditorTab
                            title: qsTr("Employee Editor")
                            EmployeeEditor{
                                id:myEmployeeEditor
                                width: mainTabView.width
                                anchors.top: parent.top
                                anchors.topMargin: 20
                                color: themePrimary
                            }
                        }
                        Tab{
                            id: employeeViewTab
                            title: qsTr("Employee Viewer")
                            EmployeeViewer{
                                id:myEmployeeViewer
                                width: mainTabView.width
                                anchors.top: parent.top
                                anchors.topMargin: 20
                            }
                        }

                        style: TabViewStyle{
                            frameOverlap: 1
                            tab: Rectangle{
                                id: tab
                                color:themeSecondary
                                border.color: styleData.hovered ? "#5caa15" : "grey"
                                implicitWidth: Math.max(text.width+4, 40)
                                implicitHeight: 20
                                radius: 1

                                Text{
                                    id: text
                                    anchors.centerIn: parent
                                    text: styleData.title
                                    color: styleData.selected ? "#5caa15" : "white"
                                    font.family: "abel"
                                }
                            }
                            frame: Rectangle{ color: themePrimary}
                            tabBar: Rectangle{ color: themePrimary}
                        }
                    }

                    Loader{
                        id: aAgLoader
                        signal timeToLoad(var index, var name, var score)
                        property var m_index
                        property var m_name
                        property var m_score
                        height: 350
                        width: 350
                        anchors.right: employeeColumn.left
                        anchors.top: parent.top
                        anchors.topMargin: 35
                        asynchronous: true
                        source:"assets/EmployeeAAG.qml"
                        active: false

                        onTimeToLoad: {
                            if(active)
                            {
                                m_index = index
                                m_name = name
                                m_score = score
                                active = false // fix this with a second loader layer
                                active = true
                            }

                            if(index !== m_index)
                            {
                                m_index = index
                                m_name = name
                                m_score = score
                                active = true
                            }

                        }
                    }
                }
            }
        }
    }
}
