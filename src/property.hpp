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
#ifndef __property_hpp__
#define __property_hpp__

#include <QObject>
#include <QString>
#include <QVariant>

namespace QuickPanel {

class Property
	: public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString name READ getName)
	Q_PROPERTY(QVariant value READ getValue NOTIFY valueChanged)

	public:
		Property(const QString& name, QObject* parent=0);
		
		const QString& getName() const { return m_name; }
		const QVariant& getValue() const { return m_value; }
		void setValue(const QVariant& value);

	signals:
		void valueChanged(const QVariant& value);

	private:
		QString m_name;
		QVariant m_value;
};

} // namespace QuickPanel
#endif // __property_hpp__
