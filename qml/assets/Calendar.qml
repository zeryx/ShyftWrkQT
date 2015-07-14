import QtQuick 2.4
import QtQuick.Controls 1.3
Rectangle
{
    id: root
    property date currentlySelectedDate
    anchors.horizontalCenter: parent.horizontalCenter
    Canvas {
        id: canvas
        height: 25
        width: 100
        anchors.left: parent.left
        anchors.leftMargin: banner.width/2-50
        anchors.top: parent.top
        property int triWidth: 100
        property int triHeight: 25
        property color strokeStyle: themeSecondary
        property int lineWidth: 0
        property bool fill: true
        property bool stroke: true
        property real alpha: 1.0
        antialiasing: true

        onLineWidthChanged:requestPaint();
        onFillChanged:requestPaint();
        onStrokeChanged:requestPaint();
        onScaleChanged:requestPaint();

        signal clicked()

        onPaint:  {
            var ctx = getContext("2d");
            ctx.save();
            ctx.clearRect(0,0,canvas.width, canvas.height);
            ctx.strokeStyle = canvas.strokeStyle;
            ctx.lineWidth = canvas.lineWidth
            ctx.fillStyle = themeSecondary
            ctx.globalAlpha = canvas.alpha
            ctx.lineJoin = "bevel";
            ctx.beginPath();

            // put rectangle in the middle
            // draw the rectangle
            ctx.moveTo(triWidth/2,triHeight ); // top of triangle
            ctx.lineTo(0, 0);
            ctx.lineTo(triWidth,0);

            ctx.closePath();
            if (canvas.fill)
                ctx.fill();
            if (canvas.stroke)
                ctx.stroke();
            ctx.restore();
        }
        Component.onCompleted: requestPaint()
        MouseArea {
            id: sDayButtonMouseArea
            //anchor all sides of the mouse area to fill the rectangle
            anchors.fill: parent
            onReleased: {
                calendarLoader.visible = (calendarLoader.visible === false ? true : false)
            }
        }
    }

    Text{
        id: dateText
        anchors.left: canvas.right
        anchors.top: root.top
        anchors.topMargin: 10
        color: themeSecondary
        text: root.currentlySelectedDate.toLocaleDateString() ? root.currentlySelectedDate.toLocaleDateString() : "Set a date, partner."
    }

    Loader{
        id: calendarLoader
        height: 500
        width: 500
        anchors.top: canvas.bottom
        anchors.horizontalCenter: canvas.horizontalCenter
        sourceComponent: calendarComponent
        Component.onCompleted: { visible = false}
    }


    Component{
        id: calendarComponent
        Calendar{
            id: calendarInst
            weekNumbersVisible: true
            onClicked: {
                root.currentlySelectedDate = date;
            }
            onDoubleClicked: {
                currentlySelectedDate = date;
                calendarLoader.visible = false
            }
        }
    }
}
