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
#ifndef __valueinterpolator_hpp__
#define __valueinterpolator_hpp__

#include <vector>

#include <QObject>
#include <QQmlPropertyValueSource>
#include <QVariant>
#include <QQmlProperty>


namespace QuickPanel {


class ValueInterpolator
	: public QObject
	, public QQmlPropertyValueSource
{
	Q_OBJECT
	Q_INTERFACES(QQmlPropertyValueSource)

	Q_PROPERTY(double input READ getInputValue WRITE setInputValue);
	Q_PROPERTY(
		QVariantList interpolation READ getInterpolation WRITE setInterpolation)

	public:
		ValueInterpolator(QObject* parent=0);
		
		void setInputValue(double inputValue);
		void setInterpolation(const QVariantList& interp);
		
		double getInputValue() const { return m_inputValue; }
		const QVariantList& getInterpolation() const { return m_interpolation; }
		
		virtual void setTarget(const QQmlProperty& p) { m_target = p; }

	private:
		QQmlProperty m_target;
		double m_inputValue;
		QVariantList m_interpolation;

		struct InterpolationEntry {
			double input;
			double output;
		};
		typedef std::vector<InterpolationEntry> InterpolationTable;
		InterpolationTable m_interpolationTable;
};

} // namespace QuickPanel
#endif // __valueinterpolator_hpp__
