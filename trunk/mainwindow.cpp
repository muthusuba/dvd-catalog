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
 * mainwindow.cpp
 * Main Window code
 *
 * Copyright (C) Muthu Subramanian K June 2009
 *
 */
#include <QtGui>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"

#define DEFAULT_FILENAME "cddb.db"
#define SEARCH_MAX_RESULTS 20


/**
  Scan Directory and index files
 */
void MainWindow::scan_directory(QString path, ScanSettings *settings)
{
    //QDirIterator dir(path,QDir::NoSymLinks|QDir::NoDotAndDotDot,QDirIterator::Subdirectories);
    QDirIterator qdir(path,QDir::AllDirs|QDir::NoDotAndDotDot|QDir::NoSymLinks|QDir::Files,
                      QDirIterator::Subdirectories);

    if(qdir.hasNext())
    {
        create_table(settings->groupid);
    }
    else
    {
        qDebug()<<"Empty Directory? "+path;
    }

    while(qdir.hasNext())
    {
        qdir.next();

        QFileInfo finfo=qdir.fileInfo();
        ui->statusBar->showMessage(finfo.filePath());

        /** Add finfo entry into the database */
        add_to_database(settings->groupid, settings->dvdid,
                     finfo.fileName(), finfo.isDir()?"DIR":finfo.suffix(),
                     finfo.size(), finfo.filePath(),
                     3, "");
    }
    ui->statusBar->showMessage("Index completed:"+settings->dvdid);
    refresh_groups();
}


QString MainWindow::GetCurrentFileName(void)
{
    return db_name;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    db_name=QString::fromAscii(DEFAULT_FILENAME);
    ui->setupUi(this);
    refresh_groups();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_searchButton_clicked()
{
    //QString sql_query=ui->searchtext->text();
    //if(sql_query.isEmpty())
    //    return;
    int row=0;
    QVector<QStringList> res;
    if(!ui->allgroups->checkState())
    {
        res=search_database_table(
                     SEARCH_MAX_RESULTS, ui->dvdgroups_list->currentText(),
                     ui->filename->text(), ui->filetype->text(),
                     ui->size_lessthan->text().toULongLong(), ui->size_morethan->text().toULongLong(),
                     ui->fullpath->text(), ui->ratings->currentIndex()+1, ui->comments->text()
                     );
    }
    else
    {
        /* Search in all tables */
        res=search_database(
                     SEARCH_MAX_RESULTS,
                     ui->filename->text(), ui->filetype->text(),
                     ui->size_lessthan->text().toULongLong(), ui->size_morethan->text().toULongLong(),
                     ui->fullpath->text(), ui->ratings->currentIndex()+1, ui->comments->text()
                     );
    }

    /* Clear older results */
    ui->searchresults->clearContents();
    /* Any other better way? */
    while(ui->searchresults->rowCount())
        ui->searchresults->removeRow(0);

    /* Add the search results */
    while(!res.isEmpty())
    {
        QStringList srow;
        srow=res.front();
        res.pop_front();

        ui->searchresults->insertRow(row);
        int c=0;
        while(!srow.isEmpty())
        {
            QTableWidgetItem *eItem = new QTableWidgetItem(srow.front());
            /* Readonly, Todo: make it changable - should update the database */
            if(c<6) /* Ratings and comments, changable */
                eItem->setFlags(eItem->flags()^Qt::ItemIsEditable);
            eItem->setTextAlignment(Qt::AlignLeft);

            //qDebug()<<srow.front();
            ui->searchresults->setItem(row,c++,eItem);
            srow.pop_front();
        }
        row++;
    }
}

void MainWindow::on_actionCreate_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Create CD/DVD Database"),
                                            DEFAULT_FILENAME, tr("SQLite3 Databases (*.db)"));
    if(fileName.isEmpty())
        return;

    /** Todo: Ask for _saving_ **/

    close_database();
    /* Delete the existing file,
       New file will be created by the open_database
       function
     */
    qDebug()<<fileName;
    if(!QFile::remove(fileName))
    {
        qDebug()<<"Unable to remove:"<<fileName;
    }

    db_name=fileName;
    open_database(db_name);
}

void MainWindow::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load CD/DVD Database"),
                                            DEFAULT_FILENAME, tr("SQLite3 Databases (*.db)"));
    if(fileName.isEmpty())
        return;

    /** Todo: Ask for _saving_ **/

    db_name=fileName;
    open_database(db_name);
    refresh_groups();
}

void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::refresh_groups()
{
    QStringList grps=get_groups();

    ui->dvdgroups_list->clear();
    ui->dvdgroups_list->addItems(grps);

    ui->dvdgroups_list->setEnabled(!ui->allgroups->checkState());
}

void MainWindow::on_actionSave_triggered()
{
    save_database();
}

void MainWindow::on_actionIndex_Files_triggered()
{
    ScanSettings settings={0, ui->groupid->text(), ui->dvdid->text()};

    scan_directory(ui->path->text(), &settings);
}

void MainWindow::on_pushButton_2_clicked()
{
    on_actionIndex_Files_triggered();

    ui->dvdid->setFocus();
}

void MainWindow::on_pushButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Index a Directory/Path"),
                                            ui->path->text(), QFileDialog::ShowDirsOnly);
    if(path.isEmpty())
        return;

    ui->path->setText(path);
}

void MainWindow::on_dvdid_returnPressed()
{
    on_pushButton_2_clicked();
}

void MainWindow::on_pushButton_3_clicked()
{
    save_database();
}

void MainWindow::on_searchtext_returnPressed()
{
    on_searchButton_clicked();
}

void MainWindow::on_allgroups_clicked()
{
    refresh_groups();
}
