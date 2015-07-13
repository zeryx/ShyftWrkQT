import QtQuick 2.0
import QtQuick.Controls 1.2
import jbQuick.Charts 1.0
import "../"
Item{
    id: root
    opacity: 1
    ScrollableEmployeeColumn{
        id: employeeColumn
        width: 160
        height: parent.height
        anchors.right: parent.right
        anchors.top: parent.top
        z:-1
    }
    Button{
        anchors.top: root.top
        anchors.topMargin: 45
        anchors.right: employeeColumn.left
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
    Rectangle{
        id: viewPanel
        height:parent.height
        width:parent.width-employeeColumn.width
        anchors.right: employeeColumn.left
        anchors.top: parent.top
        BorderImage {
            id: name
            source: "../assets/searchbox.jpg"
            width: parent.width;
            height: parent.height;
            border.left: 5; border.top: 5
            border.right: 5; border.bottom: 5
        }
        Chart{
            id: chartTest
            anchors.fill: parent
            anchors.margins: 10
            chartAnimated: true
            property var data
            chartAnimationEasing: Easing.InOutCubic
            chartAnimationDuration: 500
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
                            data: [5, 59, 80, 81, 56, 55, 40]
                        }
                    ]
                }
            }
        }
    }
}
