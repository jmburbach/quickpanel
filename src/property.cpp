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
#include <stdexcept>

#include "property.hpp"

namespace QuickPanel {

Property::Property(const QString& name, QObject* parent)
	: QObject(parent)
	, m_name(name)
	, m_value(-1)
{
}

void Property::setValue(const QVariant& value) 
{
	if (value == m_value)
		return;

   	m_value = value;
	emit valueChanged(value);
}

} // namespace QuickPanel
