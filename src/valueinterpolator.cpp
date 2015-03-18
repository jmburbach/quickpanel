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

#include "valueinterpolator.hpp"
#include "exceptions.hpp"


namespace QuickPanel {


ValueInterpolator::ValueInterpolator(QObject* parent)
	: QObject(parent)
	, m_inputValue(0)
{
}

void ValueInterpolator::setInputValue(double value)
{
	double output = value;
	m_inputValue = value;
	
	if (!m_target.isValid())
		return;

	if (m_interpolationTable.empty()) {
		m_target.write(output);
		return;
	}

	for (size_t i=0; i < m_interpolationTable.size() - 1; ++i) {
		const InterpolationEntry& entry0 = m_interpolationTable[i];
		const InterpolationEntry& entry1 = m_interpolationTable[i+1];

		if (value >= entry0.input && value <= entry1.input) {
			double diffValue = value - entry0.input;
			double diffInputs = entry1.input - entry0.input;
			double t = diffValue / diffInputs;
			output =  entry0.output + t * (entry1.output - entry0.output);
		}
	}

	m_target.write(output);
}

void ValueInterpolator::setInterpolation(const QVariantList& interp)
{
	if (interp.size() < 2) {
		std::cerr 
			<< "interpolation value must be an array with at least two entries"
			<< std::endl;
		return;
	}

	InterpolationTable table(interp.size());

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
	
		InterpolationEntry entry;
		entry.input = input.toDouble();
		entry.output = output.toDouble();
		table.push_back(entry);
	}

	m_interpolation = interp;
	m_interpolationTable = table;
}

} // namespace QuickPanel
