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
#ifndef __propertyinterpolator_hpp__
#define __propertyinterpolator_hpp__

#include <QObject>
#include <QQmlPropertyValueSource>
#include <QVariant>
#include <QQmlProperty>


namespace QuickPanel {

class Property;

class PropertyInterpolator
	: public QObject
	, public QQmlPropertyValueSource
{
	Q_OBJECT
	Q_INTERFACES(QQmlPropertyValueSource)
	Q_PROPERTY(QString propertyName READ getPropertyName WRITE setPropertyName)
	Q_PROPERTY(
		QVariantList interpolation READ getInterpolation WRITE setInterpolation)

	private slots:
		void handlePropertyValueChanged(const QVariant& value);

	public:
		PropertyInterpolator(QObject* parent=0);
		virtual void setTarget(const QQmlProperty& targetProperty);
		const QString& getPropertyName() const;
		void setPropertyName(const QString& name);
		void setInterpolation(const QVariantList& interp);
		const QVariantList& getInterpolation() const;
		

	private:
		Property* m_property;
		QString m_propertyName;
		QQmlProperty m_qmlProperty;
		QVariantList m_interpolation;
};

} // namespace QuickPanel
#endif // __propertyinterpolator_hpp__
