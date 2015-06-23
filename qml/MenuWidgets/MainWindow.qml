import QtQuick 2.0
import "../"
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
    ShiftScheduler {
        id:myShiftScheduler
        anchors.top: parent.top
        anchors.right: employeeColumn.left
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        color: themePrimary
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
        source:"../assets/EmployeeAAG.qml"
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
