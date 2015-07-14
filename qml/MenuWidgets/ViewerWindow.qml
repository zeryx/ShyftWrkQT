import QtQuick 2.0
import QtQuick.Controls 1.2
import jbQuick.Charts 1.0
import "../"
Item{
    id: root
    opacity: 1
    Button{
        id: backbutton
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
    Item{
        id: viewPanel
        height:parent.height
        width: parent.width - backbutton.width-15
        anchors.left: parent.left
        anchors.top: parent.top
        Rectangle{
            id: performanceObj
            width: parent.width/2
            height: parent.height/2
            anchors.top: parent.top
            anchors.left: parent.left
            Text{
                id: performanceText
                anchors.top: parent.top
                anchors.topMargin: 30
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Performance")
                font.family: "abel"
            }

            Chart{
                id: performanceChart
                anchors.top: performanceText.top
                anchors.topMargin: 25
                anchors.left: parent.left
                height: parent.height-performanceText.height-15
                width: parent.width
                property var data
                chartType: Charts.ChartType.LINE
                Component.onCompleted: {
                    chartData = {
                        labels: ["January", "February", "March", "April", "May", "June", "July"],
                        datasets: [
                            {
                                label: mainWindowContext.m_model.name,
                                fillColor: "rgba(220,220,220,0.2)",
                                strokeColor: "rgba(220,220,220,1)",
                                pointColor: "rgba(220,220,220,1)",
                                pointStrokeColor: "#24f708",
                                pointHighlightFill: "#fff",
                                pointHighlightStroke: "rgba(220,220,220,1)",
                                data: [30, 19, 29, 26, 32.1, 44, 46]
                            }
                        ]
                    }
                }
            }
        }
        Rectangle{
            id: synergyObj
            width: parent.width/2
            height: parent.height/2
            anchors.top: parent.top
            anchors.right: parent.right
            Text{
                id: synergyText
                anchors.top: parent.top
                anchors.topMargin: 30
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Synergy")
                font.family: "abel"
            }

            Chart{
                id: synergyChart
                anchors.top: synergyText.top
                anchors.topMargin: 25
                anchors.left: parent.left
                height: parent.height-synergyText.height-15
                width: parent.width
                property var data
                chartType: Charts.ChartType.LINE
                Component.onCompleted: {
                    chartData = {
                        labels: ["January", "February", "March", "April", "May", "June", "July"],
                        datasets: [
                            {
                                label: mainWindowContext.m_model.name,
                                fillColor: "rgba(220,220,220,0.2)",
                                strokeColor: "rgba(110,340,190,1)",
                                pointColor: "rgba(220,220,220,1)",
                                pointStrokeColor: "#24f708",
                                pointHighlightFill: "#fff",
                                pointHighlightStroke: "rgba(220,220,220,1)",
                                data: [5, 59, 80, 81, 56, 55, 40]
                            }
                        ]
                    }
                }
            }
        }
    }
}
