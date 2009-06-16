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
 * singleadddiaalog.cpp
 * Dialog to input single cd/dvd entries.
 *
 * Copyright (C) Muthu Subramanian K June 2009
 *
 */
#include "singleadddialog.h"
#include "ui_singleadddialog.h"
#include "database.h"
#include <QDebug>
#include <QMessageBox>

#define DEFAULT_RATING      3

SingleAddDialog::SingleAddDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::SingleAddDialog)
{
    m_ui->setupUi(this);

    setDefaults();
}

SingleAddDialog::~SingleAddDialog()
{
    delete m_ui;
}

void SingleAddDialog::setDefaults(void)
{
    QStringList grps=get_groups();

    /** Populate the Group ID list */
    m_ui->groupid->clear();
    m_ui->groupid->addItems(grps);

    /** Select the default rating */
    m_ui->rating->setCurrentIndex(DEFAULT_RATING-1);

    /** Enable to disable the text/list */
    on_newgroup_clicked();
}

void SingleAddDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void SingleAddDialog::on_buttonBox_accepted()
{

}

void SingleAddDialog::on_newgroup_clicked()
{
    if(m_ui->newgroup->checkState())
    {
        m_ui->groupid_text->setEnabled(true);
        m_ui->groupid->setEnabled(false);
    }
    else
    {
        m_ui->groupid_text->setEnabled(false);
        m_ui->groupid->setEnabled(true);
    }
    return;
}

void SingleAddDialog::on_addButton_clicked()
{
    QString grpid;
    if(m_ui->newgroup->checkState())
        grpid=m_ui->groupid_text->text();
    else
        grpid=m_ui->groupid->currentText();

    /** Add entry into the database */
    add_to_database(grpid, m_ui->dvdid->text(),
             m_ui->filename->text(), m_ui->filetype->text(),
             0, "",
             m_ui->rating->currentIndex()+1, m_ui->comments->toPlainText());

    QMessageBox msgBox;
    msgBox.setText("Created: "+m_ui->filename->text()+" entry...");
    msgBox.exec();
}
