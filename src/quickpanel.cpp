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
#include <cassert>

#include <QHostAddress>
#include <QQuickView>
#include <QDir>
#include <QtQml>

#include "quickpanel.hpp"
#include "property.hpp"
#include "propertymanager.hpp"
#include "exceptions.hpp"


namespace QuickPanel {

QuickPanel* QuickPanel::sm_singleton = 0;

QuickPanel::QuickPanel(QObject* parent)
	: QObject(parent)
	, m_propertyManager(0)
	, m_view(0)
{
	m_propertyManager = new PropertyManager();
	m_view = new QQuickView();
}

QuickPanel::~QuickPanel()
{
	delete m_view;
	delete m_propertyManager;
}

void QuickPanel::initPanel(const QDir& panelDir,
		const QHostAddress& address, unsigned short port)
{
	if (!panelDir.exists()) {
		throw IOError("Not a directory: " + panelDir.path());
	}

	QString qmlPath = panelDir.filePath("panel.qml");
	QString protocolPath = panelDir.filePath("protocol.xml");

	if (!panelDir.exists("panel.qml")) {
		throw IOError("Does not exist: " + qmlPath);
	}

	m_propertyManager->parseGenericProtocol(protocolPath);
	m_propertyManager->startListening(address, port);

	m_view->rootContext()->setContextProperty("quickpanel", this);
	m_view->setSource(qmlPath);
	m_view->show();
}

QObject* QuickPanel::getProperty(const QString& name)
{
	try {
		return m_propertyManager->getPropertyByName(name);
	}
	catch (const PropertyNotFound& e) {
		std::cerr << e.what() << std::endl;
		return 0;
	}
}

QuickPanel* QuickPanel::create(QObject* parent)
{
	if (!sm_singleton)
		sm_singleton = new QuickPanel(parent);
	return sm_singleton;
}

} // namespace QuickPanel
