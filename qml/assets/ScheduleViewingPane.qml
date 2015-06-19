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
            temp.push(dynamicListViews.createObject(root,
                                                    {
                                                        "model":newModel,
                                                        "headerName":headers[i]
                                                    }))
        }
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
                width: 100
                height: 25
                radius: 2
                anchors.horizontalCenter: parent.horizontalCenter
                color: "light blue"
                Text{
                    id: headerText
                    anchors.centerIn: parent
                    text: qsTr(thisListView.headerName)
                }

            }

            Layout.preferredHeight: root.height
            Layout.preferredWidth: 155
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
            z:1
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
                text: qsTr(model.name)
            }
            Text{
                id: positionText
                anchors.top: nameText.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr(model.position)
            }
            Text{
                id:scoreText
                anchors.top: positionText.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: model.score
            }

        }

    }
}
