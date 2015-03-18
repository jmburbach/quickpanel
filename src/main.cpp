/* 
 * This file is part of QuickPanel <https://github.com/jmburbach/quickpanel>
 *
 * Copyright (C) 2015 Jacob Burbach <jmburbach@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 3, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>

#include <QtWidgets/QApplication>
#include <QCommandLineParser>
#include <QDir>
#include <QtQml>

#include "quickpanel.hpp"
#include "exceptions.hpp"
#include "propertyinterpolator.hpp"
#include "valueinterpolator.hpp"


int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	app.setApplicationName("QuickPanel");

	qmlRegisterType<QuickPanel::PropertyInterpolator>(
		"QuickPanel", 1, 0, "PropertyInterpolator");
	qmlRegisterType<QuickPanel::ValueInterpolator>(
		"QuickPanel", 1, 0, "Interpolation");

	QCommandLineOption addressOption(
		QStringList() << "a" << "address",
		"Address on which to listen. [localhost]",
		"address",
		"127.0.0.1"
	);
	QCommandLineOption portOption(
		QStringList() << "p" << "port",
		"Port on which to listen. [7000]",
		"port",
		"7000"
	);

	QCommandLineParser parser;
	parser.addHelpOption();
	parser.addOption(addressOption);
	parser.addOption(portOption);
	parser.addPositionalArgument("path", "Path to panel directory");
	parser.process(app);

	QStringList args = parser.positionalArguments();
	if (args.isEmpty()) {
		parser.showHelp(1);
	}

	QDir panelPath(parser.positionalArguments().at(0));

	bool ok;
	unsigned short port = parser.value(portOption).toUShort(&ok);
	if (!ok) {
		std::cerr << "Invalid port number" << std::endl << std::endl;
		parser.showHelp(1);
	}

	QHostAddress address(parser.value(addressOption));

	QuickPanel::QuickPanel* panel = QuickPanel::QuickPanel::create();

	try {
		panel->initPanel(panelPath, address, port);
	}
	catch (const std::exception& e) {
		std::cerr << std::endl << e.what() << std::endl << std::endl;
		return 1;
	}

	return app.exec();
}
