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
 * database.cpp
 * Database helpers
 *
 * Copyright (C) Muthu Subramanian K June 2009
 *
 */

#include <QSqlDatabase>
#include <QtGui>
#include <QSqlError>
#include <QSqlQuery>
#include "database.h"


#define N_COLUMNS 7
/**
  Current database
  ----------------
  CD/DVD Details:
  GroupName(text) -> Tablename
  DVDID(text),
  Filename(text), Filetype(extension), Size (in bytes),
  Fullpath(text), ratings(int), comments(text)
 */


QVector<QStringList> search_database_table(
                     qint64 max_results, QString groupname,
                     QString filename, QString filetype,
                     qint64 size_lessthan, qint64 size_morethan,
                     QString fullpath, qint64 ratings, QString comments
                     )
{
    QVector<QStringList> result;
    QSqlQuery query;
    QString qs;
    qint64 i;

    if(!QSqlDatabase::database().isOpen())
        return result;

    /* Check "select *" returned columns order might be different */
    qs="SELECT * from "+groupname+" where ";
    if(!filename.isEmpty())
        qs+="filename like \"%"+filename+"%\" AND ";
    if(!filetype.isEmpty())
        qs+="filetype like \"%"+filetype+"%\" AND ";
    if(!fullpath.isEmpty())
        qs+="fullpath like \"%"+fullpath+"%\" AND ";
    if(!comments.isEmpty())
        qs+="comments like \"%"+comments+"%\" AND ";
    if(size_lessthan > 0)
        qs+="size < "+QString::number(size_lessthan)+" AND ";
    if(size_morethan > 0)
        qs+="size > "+QString::number(size_morethan)+" AND ";
    qs+="ratings >= "+QString::number(ratings)+";";

    qDebug()<<qs;

    if(!query.exec(qs))
        return result;

    for(i=0;i<max_results && query.next();i++)
    {
        QStringList res;
        int j;
        res<<groupname;
        for(j=0;j<N_COLUMNS;j++)
        {
            res<<query.value(j).toString();
        }
        //qDebug()<<res;
        result.append(res);
    }
    return result;
}

QVector<QStringList> search_database(
                     qint64 max_results,
                     QString filename, QString filetype,
                     qint64 size_lessthan, qint64 size_morethan,
                     QString fullpath, qint64 ratings, QString comments
                     )
{
    QVector<QStringList> result;
    QStringList grps=get_groups();
    while(!grps.isEmpty() && max_results > 0)
    {
        QVector<QStringList> res;
        res=search_database_table(
                     max_results, grps.front(),
                     filename, filetype,
                     size_lessthan, size_morethan,
                     fullpath, ratings, comments
                     );

        grps.pop_front();
        max_results-=res.count();
        result+=res;
    }
    return result;
}

QStringList get_groups(void)
{
    QSqlDatabase db=QSqlDatabase::database();
    if(!db.isOpen()) return QStringList();
    return db.tables();
}

void close_database(void)
{
    QSqlDatabase db=QSqlDatabase::database();
    if(db.isOpen())
    {
        db.close();
    }
}

bool is_database_open(void)
{
    return QSqlDatabase::database().isOpen();
}

bool create_table(QString table)
{
    QSqlQuery query;

    if(!QSqlDatabase::database().isOpen())
        return false;

    /* Create if table doesn't already exist */
    if(!query.exec(QString("Create table ")+table+QString(" (dvdid text,"
                   "filename text, filetype text,size integer, fullpath text,"
                   "ratings integer, comments text)")))
    {
        qDebug()<<query.lastError();
        return false;
    }
    // db.commit();
    return true;
}


bool open_database(QString filename)
{
    bool ret;

    close_database();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("dvddatabase");
    db.setDatabaseName(filename);
    ret=db.open();
    if(ret)
    {
        //db.commit();
    }
    return ret;
}

bool add_to_database(QString groupname, QString dvdid,
                     QString filename, QString filetype,
                     qint64 size, QString fullpath,
                     qint64 ratings, QString comments)
{
    QSqlDatabase db = QSqlDatabase::database();
    QString qs;
    QSqlQuery query;
    if(!db.isOpen()) return false;

    qs="Insert into "+groupname+" values(";
    qs+="\""+dvdid+"\",";
    qs+="\""+filename+"\",";
    qs+="\""+filetype+"\",";
    qs+=QString::number(size)+",";
    qs+="\""+fullpath+"\",";
    qs+=QString::number(ratings)+",";
    qs+="\""+comments+"\")";
    if(!query.exec(qs))
    {
        qDebug()<<qs;
        qDebug()<<query.lastError();
        return false;
    }
    //db.commit();
    return true;
}

bool save_database(void)
{
    QSqlDatabase db = QSqlDatabase::database();
    if(!db.isOpen()) return false;
    db.commit();
	return true;
}
