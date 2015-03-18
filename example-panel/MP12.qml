import QtQuick 2.3
import QuickPanel 1.0

MP {
	property var engine1_mp: quickpanel.getProperty('engine1_mp')
	property var engine2_mp: quickpanel.getProperty('engine2_mp')
	property string needleSource1: 'images/needle_e1.png'
	property string needleSource2: 'images/needle_e2.png'
	property double manifoldPressure1: parseFloat(engine1_mp.value)
	property double manifoldPressure2: parseFloat(engine2_mp.value)
}
