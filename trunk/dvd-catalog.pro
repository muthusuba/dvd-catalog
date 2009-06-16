# -------------------------------------------------
# Project created by QtCreator 2009-05-31T10:27:43
# -------------------------------------------------
# CD/DVD Management Software. Create your CD/DVD Library.
# Copyright (C) June 2009 Muthu Subramanian K <muthusuba@gmail.com>
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>
QT += sql \
    -qt-sql-sqlite
TARGET = dvd-catalog
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    database.cpp \
    singleadddialog.cpp
HEADERS += mainwindow.h \
    database.h \
    singleadddialog.h
FORMS += mainwindow.ui \
    singleadddialog.ui
