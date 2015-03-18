import QtQuick 2.3
import QuickPanel 1.0

MP {
	property var engine3_mp: quickpanel.getProperty('engine3_mp')
	property var engine4_mp: quickpanel.getProperty('engine4_mp')
	property string needleSource1: 'images/needle_e3.png'
	property string needleSource2: 'images/needle_e4.png'
	property double manifoldPressure1: parseFloat(engine3_mp.value)
	property double manifoldPressure2: parseFloat(engine4_mp.value)
}
