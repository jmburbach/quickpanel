import QtQuick 2.3
import QuickPanel 1.0
import "qrc:js/util.js" as Util

Item {
	property var airspeed: quickpanel.getProperty('indicated_airspeed_kt')
	property double scaleFactor: 1.0

	width: 256 * scaleFactor
	height: 256 * scaleFactor

	transform: Scale {
		xScale: scaleFactor
		yScale: scaleFactor
	}

	Image {
		id: asi_face
		source: "images/asi/asi.png"
	}
	SharedNeedle {
		id: asi_needle;
		PropertyInterpolator on needleAngle {
			propertyName: 'indicated_airspeed_kt'
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
