import QtQuick 2.4
import jbQuick.Charts 1.0
import ShyftMenu 1.0
Rectangle {
    id: root
    Item{
        id: shyftContainer
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        height: 45
        width: 100
    }
    Loader{
        id: pivotChart
        sourceComponent: chartComponent
        active: false
        anchors.top: shyftContainer.bottom
        anchors.left: parent.left
        property var chartValues: [30, 19, 29, 26, 32.1, 44, 46]
        width:parent.width
        height: parent.height-shyftContainer.height-15

    }
    Component{
        id: chartComponent
        Chart{
            id: performanceChart
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
                            data: pivotChart.chartValues
                        }
                    ]
                }
            }
        }
    }
}
