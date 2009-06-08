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
 * mainwindow.h
 * Main Window code
 *
 * Copyright (C) Muthu Subramanian K June 2009
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

const char *get_current_filename(void);

namespace Ui
{
    class MainWindow;
}

typedef struct SCANSETTINGS
{
    int min_filesize;
    QString groupid;
    QString dvdid;
}ScanSettings;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString GetCurrentFileName(void);
    void scan_directory(QString path, ScanSettings *settings);
    void refresh_groups(void);

private:
    Ui::MainWindow *ui;
    QString db_name;

private slots:
    void on_allgroups_clicked();
    void on_searchtext_returnPressed();
    void on_pushButton_3_clicked();
    void on_dvdid_returnPressed();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_actionIndex_Files_triggered();
    void on_actionSave_triggered();
    void on_actionLoad_triggered();
    void on_actionExit_triggered();
    void on_actionCreate_triggered();
    void on_searchButton_clicked();
};

#endif // MAINWINDOW_H
