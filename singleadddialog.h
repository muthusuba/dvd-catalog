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
 * singleadddialog.h
 * Header file for Single-entry-dialog
 *
 * Copyright (C) Muthu Subramanian K June 2009
 *
 */
#ifndef SINGLEADDDIALOG_H
#define SINGLEADDDIALOG_H

#include <QtGui/QDialog>

namespace Ui {
    class SingleAddDialog;
}

class SingleAddDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(SingleAddDialog)
public:
    explicit SingleAddDialog(QWidget *parent = 0);
    virtual ~SingleAddDialog();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::SingleAddDialog *m_ui;
    void setDefaults(void);

private slots:
    void on_addButton_clicked();
    void on_newgroup_clicked();
    void on_buttonBox_accepted();
};

#endif // SINGLEADDDIALOG_H
