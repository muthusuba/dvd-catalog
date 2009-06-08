/*****
    CD/DVD Management Software. Create your CD/DVD Library.
    Copyright (C) June 2009  Muthu Subramanian K <muthusuba@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
  ****/

/**
 * database.h
 * Database helpers
 *
 * Copyright (C) Muthu Subramanian K June 2009
 *
 */

#ifndef __DATABASE_H__
#define __DATABASE_H__


bool open_database(QString filename);
void close_database(void);
bool save_database(void);
bool add_to_database(QString groupname, QString dvdid,
                     QString filename, QString filetype,
                     qint64 size, QString fullpath,
                     qint64 ratings, QString comments);
bool create_table(QString table);
QStringList get_groups(void);

QVector<QStringList> search_database_table(
                     qint64 max_results, QString groupname,
                     QString filename, QString filetype,
                     qint64 size_lessthan, qint64 size_morethan,
                     QString fullpath, qint64 ratings, QString comments
                     );

QVector<QStringList> search_database(
                     qint64 max_results,
                     QString filename, QString filetype,
                     qint64 size_lessthan, qint64 size_morethan,
                     QString fullpath, qint64 ratings, QString comments
                     );


#endif // __DATABASE_H__
