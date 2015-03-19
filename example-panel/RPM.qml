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
		source: "images/rpm/rpm.png"
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
		initialRotation: -162
		Interpolation on needleAngle {
			input: rpm2
			interpolation: [
				[0, 0],
				[4500, 324]
			]
		}
	}
	SharedNeedle {
		id: needle1
		source: needleSource1
		initialRotation: -162
		Interpolation on needleAngle {
			input: rpm1
			interpolation: [
				[0, 0],
				[4500, 324]
			]
		}
	}
	Text {
		text: rpm1 + "|" + rpm2
		x: 15
		y: 15
		color: '#ffffff'
	}
}
