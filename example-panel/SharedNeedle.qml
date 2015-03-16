import QtQuick 2.3

Image {
	property double needleAngle: 0.0
	property double initialRotation: 0.0

	source: "images/needle.png"

	transform: [
		Translate {
			x: 124
			y: 23
		},
		Rotation {
			origin.x: 130
			origin.y: 128
			angle: initialRotation;
		},
		Rotation {
			origin.x: 130
			origin.y: 128
			angle: needleAngle
		}
	]
}
