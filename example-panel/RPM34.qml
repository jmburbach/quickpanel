import QtQuick 2.3
import QuickPanel 1.0

RPM {
	property var engine3_rpm: quickpanel.getProperty('engine3_rpm')
	property var engine4_rpm: quickpanel.getProperty('engine4_rpm')
	property string needleSource1: 'images/needle_e3.png'
	property string needleSource2: 'images/needle_e4.png'
	property double rpm1: parseFloat(engine3_rpm.value)
	property double rpm2: parseFloat(engine4_rpm.value)
}
