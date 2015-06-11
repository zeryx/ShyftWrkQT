import QtQuick 2.0
import QtQuick.Controls 1.2
Rectangle{
id: root
radius: 5
    TableView{
        id: schedulerTableView
        itemDelegate: tableDelegate
        resources:
        {
            var headerData = headers
            var temp = []
            for(var i=0; i<headerData.length; i++)
            {
                var role  = headerData[i]
                temp.push(columnComponent.createObject(schedulerTableView, { "role": role, "title": role}))
                console.log("column #" + i + " is named : " + role);
            }
            return temp
        }
        model: baseTableModel
        anchors.fill: root

    }

    Component
    {
        id: columnComponent
        TableViewColumn{width: 220 }
    }


    Component{
        id: tableDelegate
        Rectangle{
            id: delRectangle
            height: 250
            z:0
            Clickable{
                id: portraitText
                source: portrait
                smooth: true
                antialiasing: true
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                height: 150
                fillMode: Image.PreserveAspectFit
                overlayOpacity: 0.4
            }
            Text{
                id: nameText
                text: name
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: portraitText.bottom
            }
            Text{
                id: positionText
                anchors.top: nameText.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: position
            }
            Text{
                id:scoreText
                anchors.top: positionText.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: score
            }
        }

    }

}
