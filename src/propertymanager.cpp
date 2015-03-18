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

#include "property.hpp"
#include "propertymanager.hpp"
#include "exceptions.hpp"

#include <QUdpSocket>
#include <QXmlStreamReader>
#include <QFile>
#include <QByteArray>

namespace QuickPanel {

PropertyManager::PropertyManager(QObject* parent)
	: QObject(parent)
{
	m_socket = new QUdpSocket(this);
}

void PropertyManager::parseGenericProtocol(const QString& path)
{
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly)) {
		throw IOError("Could not open file: " + path);
	}

	QXmlStreamReader xml(&file);

	for (;;) {
		xml.readNext();

		if (xml.atEnd())
			break;

		if (xml.isStartElement() && xml.name() == "output") {
			parseGenericOutput(xml);
			break;
		}
	}

	if (xml.hasError())
		throw ParseError("Error parsing protocol: " + xml.errorString());
}

void PropertyManager::parseGenericOutput(QXmlStreamReader& xml)
{
	for (;;) {
		xml.readNext();

		if (xml.atEnd())
			return;

		if (xml.isEndElement() && xml.name() == "output")
			return;

		if (xml.isStartElement() && xml.name() == "chunk")
			parseGenericChunk(xml);
	}
}

void PropertyManager::parseGenericChunk(QXmlStreamReader& xml)
{
	QString name;
	QString node;

	for (;;) {
		xml.readNext();

		if (xml.atEnd())
			return;

		if (xml.isEndElement() && xml.name() == "chunk")
			break;

		if (xml.isStartElement()) {
			if (xml.name() == "name") {
				name = xml.readElementText();
			}
			else if (xml.name() == "node") {
				node = xml.readElementText();
			}
		}
	}

	if (node.isEmpty()) 
		throw ParseError("Protocol contains output chunk without node.");

	if (name.isEmpty())
		name = node;

	Property* p = new Property(name, this);
	m_propertyList.push_back(p);
	m_propertyMap.insert(name, p);

	std::cout << "Added property " << node.toStdString() << " as " 
		<< name.toStdString() << std::endl;
}

void PropertyManager::startListening(const QHostAddress& address, quint16 port)
{
	if (!m_socket->bind(address, port))
		throw IOError("Error binding socket: " + m_socket->errorString());
	connect(m_socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

void PropertyManager::readPendingDatagrams()
{
	QByteArray datagram;
	while (m_socket->hasPendingDatagrams()) {
		datagram.resize(m_socket->pendingDatagramSize());
		m_socket->readDatagram(datagram.data(), datagram.size());
		processDatagram(datagram);
	}
}

void PropertyManager::processDatagram(const QByteArray& datagram)
{
	QList<QByteArray> values = datagram.split(',');

	size_t nvalues = static_cast<size_t>(values.size());
	size_t nprops = static_cast<size_t>(m_propertyList.size());

	if (nprops != nvalues) {
		std::cerr << "WARNING:" << std::endl
			<< "  Number of values received differs from number of properties available!"
		   	<< std::endl
			<< "  Did you use different protocol files for flightgear and quickpanel?"
			<< std::endl;
	}

	size_t i, count = std::min(nvalues, nprops);
	for (i=0; i < count; ++i) {
		m_propertyList[i]->setValue(values[i]);
	}
}

Property* PropertyManager::getPropertyByName(const QString& name)
{
	PropertyMap::iterator it, end = m_propertyMap.end();
	if ((it = m_propertyMap.find(name)) == end) {
		throw PropertyNotFound("No such property: " + name);
	}
	return it.value();
}

} // namespace QuickPanel
