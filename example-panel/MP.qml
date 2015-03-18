import QtQuick 2.3

import "qrc:js/util.js" as Util
import QuickPanel 1.0

Item {
	property double scaleFactor: 1.0
	property var interpolation: [
		[0, -8],
		[2, -6],
		[10, 0],
		[50, 200],
		[75, 337.5]
	]
	
	width: 256 * scaleFactor
	height: 256 * scaleFactor
	
	transform: Scale { 
		xScale: scaleFactor
		yScale: scaleFactor 
	}

	Image {
		id: mp_face
		source: "images/mp/manpress.png"
	}
	SharedNeedle {
		id: needle2
		source: needleSource2
		initialRotation: -100
		Interpolation on needleAngle {
			input: manifoldPressure2
			interpolation: [
				[0, 0],
				[15, 25],
				[20, 50],
				[30, 100],
				[40, 150],
				[50, 200],
				[60, 255],
				[70, 310]
			]
		}
	}
	SharedNeedle {
		id: needle1
		source: needleSource1
		initialRotation: -100
		Interpolation on needleAngle {
			input: manifoldPressure1
			interpolation: [
				[0, 0],
				[15, 25],
				[20, 50],
				[30, 100],
				[40, 150],
				[50, 200],
				[60, 255],
				[70, 310]
			]
		}
	}
	Text {
		text: manifoldPressure1 + "|" + manifoldPressure2
		x: 15
		y: 15
		color: '#ffffff'
	}
}
