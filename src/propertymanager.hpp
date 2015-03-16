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
#ifndef __propertymanager_hpp__
#define __propertymanager_hpp__

#include <vector>

#include <QObject>
#include <QHash>

class QUdpSocket;
class QFile;
class QXmlStreamReader;
class QHostAddress;

namespace QuickPanel {

class Property;

class PropertyManager
	: public QObject
{
	Q_OBJECT

	public:
		PropertyManager(QObject* parent=0);

		/**
		 * Parse a generic protocol xml file to discover and prepare
		 * properties which will be available to the system.
		 *
		 * throws: IOError ParseError
		 */
		void parseGenericProtocol(const QString& path);

		/**
		 * Start listening on address and port for incoming data packets.
		 */
		void startListening(const QHostAddress& address, quint16 port);

		/**
		 * Return a property with the given name.
		 *
		 * throws: PropertyNotFound 
		 */
		Property* getPropertyByName(const QString& name);

	private slots:
		/**
		 * Called when there are datagrams ready to be read.
		 */
		void readPendingDatagrams();

	private:
		void parseGenericOutput(QXmlStreamReader& xml);
		void parseGenericChunk(QXmlStreamReader& xml);

		/**
		 * Called with datagram received to parse property data
		 * and dispatch values to system properties.
		 */
		void processDatagram(const QByteArray& datagram);

		/**
		 * Store properties in a std vector as they are discovered in the
		 * generic protocol. Effictively putting them in same order as they
		 * will be received off the network. So first property belongs to first
		 * value, and so on.
		 */
		typedef std::vector<Property*> PropertyList;
		PropertyList m_propertyList;

		/**
		 * We also store properties in a hash map so they can easily be
		 * retrieved by names.
		 */
		typedef QHash<QString, Property*> PropertyMap;
		PropertyMap m_propertyMap;

		QUdpSocket* m_socket;
};

} // namespace QuickPanel
# endif // __propertymanager_hpp__
