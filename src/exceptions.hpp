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
#ifndef __exceptions_hpp__
#define __exceptions_hpp__

#include <stdexcept>
#include <string>

#include <QString>

namespace QuickPanel {

class Error 
	: public std::exception 
{
	public:
		Error(const QString& msg) : m_msg(msg.toStdString()) {}
		Error(const char* msg) : m_msg(msg) {}
		Error(const std::string& msg) : m_msg(msg) {}

		virtual const char* what() const noexcept { return m_msg.c_str(); }

	protected:
		std::string m_msg;
};

class IOError : public Error { using Error::Error; };
class ParseError : public Error { using Error::Error; };
class PropertyNotFound : public Error { using Error::Error; };

} // namespace QuickPanel
#endif // __exceptions_hpp__
