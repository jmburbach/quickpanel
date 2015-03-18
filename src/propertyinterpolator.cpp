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

#include "propertyinterpolator.hpp"
#include "propertymanager.hpp"
#include "property.hpp"
#include "exceptions.hpp"
#include "quickpanel.hpp"


namespace QuickPanel {


PropertyInterpolator::PropertyInterpolator(QObject* parent)
	: QObject(parent)
	, m_property(0)
	, m_propertyName("")
{
}

const QString& PropertyInterpolator::getPropertyName() const
{
	return m_propertyName;
}

void PropertyInterpolator::setPropertyName(const QString& name)
{
	QuickPanel* qp = QuickPanel::getSingleton();
	PropertyManager* mgr = qp->getPropertyManager();

	if (m_property) {
		m_property->disconnect(m_property, 0, this, 0);
	}

	try {
		m_property = mgr->getPropertyByName(name);
		m_propertyName = name;
		connect(m_property, SIGNAL(valueChanged(const QVariant&)),
				this, SLOT(handlePropertyValueChanged(const QVariant&)));
	}
	catch (const PropertyNotFound& e) {
		std::cerr << e.what() << std::endl;
		m_property = 0;
		m_propertyName = "";
	}
}

const QVariantList& PropertyInterpolator::getInterpolation() const
{
	return m_interpolation;
}

void PropertyInterpolator::setInterpolation(const QVariantList& interp)
{
	if (interp.size() < 2) {
		std::cerr 
			<< "interpolation value must be an array with at least two entries"
			<< std::endl;
		return;
	}

	for (const QVariant& variant : interp) {
		if (!variant.canConvert<QVariantList>()) {
			std::cerr <<
			   	"interpolation value should be an array of two element arrays"
				<< std::endl;
			return;
		}
		
		QSequentialIterable iterable = variant.value<QSequentialIterable>();
		if (iterable.size() != 2) {
			std::cerr <<
			   	"interpolation value should be an array of two element arrays"
				<< std::endl;
			return;
		}

		QVariant input = iterable.at(0);
		QVariant output = iterable.at(1);
		if (!(input.canConvert<double>() && output.canConvert<double>())) {
			std::cerr << "interpolation values must be numberic" << std::endl;
			return;
		}
	}

	m_interpolation = interp;
}

void PropertyInterpolator::setTarget(const QQmlProperty& target)
{
	m_qmlProperty = target;
}

void PropertyInterpolator::handlePropertyValueChanged(const QVariant& newValue)
{
	if (!m_qmlProperty.isValid())
		return;

	if (!newValue.canConvert<double>()) {
		std::cerr <<
		   	"Cannot interpolate non numeric values" << std::endl;
		return;
	}

	double value = newValue.toDouble();
	double interpValue = 0;

	for (int i=0; i < m_interpolation.size() - 1; ++i) {
		QVariantList entry0 = m_interpolation.at(i).toList();
		double in0 = entry0.at(0).toDouble();
		double out0 = entry0.at(1).toDouble();

		QVariantList entry1 = m_interpolation.at(i+1).toList();
		double in1 = entry1.at(0).toDouble();
		double out1 = entry1.at(1).toDouble();

		if (value >= in0 && value <= in1) {
			double diffValue = value - in0;
			double diffInputs = in1 - in0;
			double t = diffValue / diffInputs;
			interpValue =  out0 + t * (out1 - out0);
		}
	}
	m_qmlProperty.write(interpValue);
}

} // namespace QuickPanel
