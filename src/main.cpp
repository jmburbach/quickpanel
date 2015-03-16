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


int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	app.setApplicationName("QuickPanel");

	QCommandLineParser parser;
	parser.addHelpOption();
	parser.addPositionalArgument("path", "Path to panel directory");
	parser.process(app);

	QStringList args = parser.positionalArguments();
	if (args.isEmpty()) {
		parser.showHelp(1);
	}

	qmlRegisterType<QuickPanel::PropertyInterpolator>(
		"QuickPanel", 1, 0, "PropertyInterpolator");

	QDir panelPath(parser.positionalArguments().at(0));

	QuickPanel::QuickPanel* panel = QuickPanel::QuickPanel::create();

	try {
		panel->initPanel(panelPath);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return app.exec();
}
