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
#ifndef __quickpanel_hpp__
#define __quickpanel_hpp__

#include <QObject>
#include <QHostAddress>

class QDir;
class QQuickView;

namespace QuickPanel {

class Property;
class PropertyManager;

class QuickPanel
	: public QObject
{
	Q_OBJECT

	public:
		~QuickPanel();

		void initPanel(const QDir& panelDir,
			const QHostAddress& address, unsigned short port);

		Q_INVOKABLE QObject* getProperty(const QString& path);

		static QuickPanel* create(QObject* parent=0);
		static QuickPanel* getSingleton() { return sm_singleton; }

		PropertyManager* getPropertyManager() const { return m_propertyManager; }

	private:
		PropertyManager* m_propertyManager;
		QQuickView* m_view;

		static QuickPanel* sm_singleton;
		
		QuickPanel(QObject* parent=0);
};

} // namespace QuickPanel
#endif // __quickpanel_hpp__
