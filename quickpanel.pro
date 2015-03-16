CONFIG += debug c++11

QT += quick widgets
TARGET = quickpanel

SOURCES = src/property.cpp \
	src/propertymanager.cpp \
	src/main.cpp \
	src/quickpanel.cpp \
	src/propertyinterpolator.cpp

HEADERS = src/property.hpp \
	src/propertymanager.hpp \
	src/quickpanel.hpp \
	src/propertyinterpolator.hpp

RESOURCES = resources.qrc
