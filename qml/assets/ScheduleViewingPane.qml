import QtQuick 2.0
import QtQuick.Layouts 1.1
RowLayout
{
    id: root
    spacing: 6
    Component.onCompleted: {
        var headers = headerList
        var model = tableModel
        var temp = []
        for(var i=0; i<headers.length; i++)
        {
            var newModel = model[i]
            console.log(headers[i] + " "+ i)

            temp.push(dynamicListViews.createObject(root,
                                                    {
                                                        "model":newModel,
                                                        "headerName":headers[i]
                                                    }))
        }
        var temp =  []
        return temp

    }
    Component
    {
        id: dynamicListViews
        ListView{
            id: thisListView
            delegate: tableDelegate
            property string headerName
            header: Rectangle{
                width: 220
                height: 25
                anchors.horizontalCenter: parent.horizontalCenter
                color: "light blue"
                Text{
                    anchors.centerIn: parent
                    text: thisListView.headerName
                }

            }

            Layout.preferredHeight: root.height
            Layout.preferredWidth: 220
            spacing: 5
        }
    }


    Component{
        id: tableDelegate
        Rectangle{
            id: delRectangle
            radius: 6
            color: "white"
            height: 200
            width: 150
            Clickable{
                id: portraitText
                source: model.portrait
                smooth: true
                antialiasing: true
                anchors.top: parent.top
                anchors.margins: 5
                anchors.horizontalCenter: parent.horizontalCenter
                height: parent.height-70
                fillMode: Image.PreserveAspectFit
                overlayOpacity: 0.4
            }
            Text{
                id: nameText
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: portraitText.bottom
                text: model.name
            }
            Text{
                id: positionText
                anchors.top: nameText.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: model.position
            }
            Text{
                id:scoreText
                anchors.top: positionText.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: model.score
            }

        }

    }
    TextInput{
        objectName: "headerInput"
        property string newHeader
        signal newHeaderInput(string newHeader);
        z: 1
        id: replacableTextInput
        anchors.left: parent.left
        anchors.top: parent.top
        height: 20
        width: 40

        BorderImage {
            id: simpleBorder
            source: "searchbox.jpg"
            anchors.fill: parent

            z: -1
        }
        activeFocusOnPress: true
        onAccepted: {
            newHeader = replacableTextInput.text
            newHeaderInput(newHeader)
            replacableTextInput.text ="";
        }
    }


}
