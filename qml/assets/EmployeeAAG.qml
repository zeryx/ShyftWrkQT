import QtQuick 2.0
import jbQuick.Charts 1.0
Rectangle {
    id: root
    anchors.fill: parent
    color: "grey";

    Rectangle{
            id: closeAAGButton
        color: "blue"
        height: 10
        width: 10
        anchors.top: root.top
        anchors.left: root.left

        MouseArea{
            id: closeAAGMouseArea
            anchors.fill: parent
            onClicked: { aAgLoader.active = false}
        }
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
                        label: m_name,
                        fillColor: "rgba(220,220,220,0.2)",
                        strokeColor: "rgba(220,220,220,1)",
                        pointColor: "rgba(220,220,220,1)",
                        pointStrokeColor: "#24f708",
                        pointHighlightFill: "#fff",
                        pointHighlightStroke: "rgba(220,220,220,1)",
                        data: [m_score+5, m_score+59, m_score+80, m_score+81, m_score+56, m_score+55, m_score+40]
                    }
                ]
            }
        }
    }
}
