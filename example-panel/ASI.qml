import QtQuick 2.3
import QtGraphicalEffects 1.0
import QuickPanel 1.0

Item {
	property var airspeed: quickpanel.getProperty('indicated_airspeed_kt')

	width: 256 * scaleFactor
	height: 256 * scaleFactor

	transform: Scale {
		xScale: scaleFactor
		yScale: scaleFactor
	}

	Image {
		id: face
		source: "images/asi/asi.png"
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
		id: asi_needle;
		Interpolation on needleAngle {
			input: airspeed.value
			interpolation: [
				[0, 0],
				[25, 16],
				[50, 24.5],
				[100, 93.5],
				[150, 139.5],
				[200, 185.5],
				[250, 224.5],
				[300, 263.5],
				[350, 301.5],
				[400, 339.5]
			]
		}
	}
	Text {
		text: airspeed.value
		x: 15
		y: 15
		color: '#ffffff'
	}
}
