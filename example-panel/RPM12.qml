import QtQuick 2.3
import QuickPanel 1.0

RPM {
	property var engine1_rpm: quickpanel.getProperty('engine1_rpm')
	property var engine2_rpm: quickpanel.getProperty('engine2_rpm')
	property string needleSource1: 'images/needle_e1.png'
	property string needleSource2: 'images/needle_e2.png'
	property double rpm1: parseFloat(engine1_rpm.value)
	property double rpm2: parseFloat(engine2_rpm.value)
}
