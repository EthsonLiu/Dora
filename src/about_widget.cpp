/**
 * DUKTO - A simple, fast and multi-platform file transfer tool for LAN users
 * Copyright (C) 2011 Emanuele Colombo
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "src/about_widget.h"
#include "src/project.h"

#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QPushButton>
#include <QApplication>
#include <QDesktopServices>

AboutWidget::AboutWidget(QWidget* parent) : QWidget(parent)
{
    setWindowTitle(tr("About"));

    QLabel* logoLabel = new QLabel(this);
    logoLabel->setPixmap(QPixmap(":/dukto.ico").scaled(80, 80));

    QLabel* titleLabel = new QLabel("Dukto", this);
    QFont titleFont;
    titleFont.setPointSize(23);
    titleLabel->setFont(titleFont);

    QLabel* builtWithQtLabel = new QLabel(this);
    builtWithQtLabel->setPixmap(QPixmap(":/built_with_qt.png").scaled(200, 60));

    QHBoxLayout* hLayout1 = new QHBoxLayout;
    hLayout1->addWidget(logoLabel);
    hLayout1->addWidget(titleLabel);
    hLayout1->addStretch();
    hLayout1->addSpacing(300);
    hLayout1->addWidget(builtWithQtLabel);

    QLabel* versionLabel = new QLabel(QString(tr("Version")) +
                                      QString(" %1 (%2)").
                                      arg(Project::applicationVersion()).
                                      arg(Project::applicationReleasedDate()),
                                      this);
    QLabel* websiteLabel = new QLabel(QString(tr("Website")) + " <a href=\"https://github.com/ethsonliu/dukto\">https://github.com/ethsonliu/dukto</a>");
    websiteLabel->setTextFormat(Qt::RichText);
    websiteLabel->setOpenExternalLinks(true);
    QLabel* authorsLabel = new QLabel(tr("Created by Emanuele Colombo, maintained by Ethson Liu."));

    QHBoxLayout* hLayout2 = new QHBoxLayout;
    hLayout2->addWidget(websiteLabel);
    hLayout2->addStretch();

    QVBoxLayout* vLayout1 = new QVBoxLayout;
    vLayout1->addWidget(versionLabel);
    vLayout1->addLayout(hLayout2);
    vLayout1->addWidget(authorsLabel);

    QPushButton* aboutQtBtn = new QPushButton("About Qt", this);
    connect(aboutQtBtn, &QPushButton::clicked, qApp, &QApplication::aboutQt);
    QPushButton* closeBtn = new QPushButton(tr("Close"), this);
    connect(closeBtn, &QPushButton::clicked, this, &AboutWidget::close);

    QHBoxLayout* hLayout3 = new QHBoxLayout;
    hLayout3->addWidget(aboutQtBtn);
    hLayout3->addStretch();
    hLayout3->addWidget(closeBtn);

    QVBoxLayout* vLayout2 = new QVBoxLayout(this);
    vLayout2->addLayout(hLayout1);
    vLayout2->addSpacing(25);
    vLayout2->addLayout(vLayout1);
    vLayout2->addSpacing(50);
    vLayout2->addLayout(hLayout3);
}
