import QtQuick 2.3
import QtGraphicalEffects 1.0
import QuickPanel 1.0

Item {
	width: 256 * scaleFactor
	height: 256 * scaleFactor
	
	transform: Scale { 
		xScale: scaleFactor
		yScale: scaleFactor 
	}

	Image {
		id: face
		source: "images/mp/manpress.png"
	}
	Image {
		id: face_lit
		source: 'images/face-lit.png'
		opacity: lighting
	}
	Blend {
		width: 256
		height: 256
		foregroundSource: face_lit
		source: face
		mode: 'lighten'
		opacity: lighting
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
