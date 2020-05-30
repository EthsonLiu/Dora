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

#include "src/preference_widget.h"
#include "src/project.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QStringList>
#include <QPushButton>
#include <QDateTime>
#include <QRandomGenerator>
#include <QRegExpValidator>
#include <QRegExp>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFile>
#include <QTextStream>
#include <QSettings>

PreferenceWidget::PreferenceWidget(QWidget* parent) : QWidget(parent)
{
    setWindowTitle(tr("Preference"));
    setFixedWidth(600);

    m_tabWidget = new QTabWidget(this);
    connect(m_tabWidget, &QTabWidget::currentChanged, this, &PreferenceWidget::updateSizes);
    m_tabWidget->addTab(createGeneralWidget(), tr("General"));
    m_tabWidget->addTab(createBehaviorWidget(), tr("Behavior"));

    QHBoxLayout* hLayout = new QHBoxLayout(this);
    hLayout->addWidget(m_tabWidget);
}

void PreferenceWidget::closeEvent(QCloseEvent* event)
{
    {
        QSettings setting(Project::getApplicationPreferenceIniPath(), QSettings::IniFormat);

        setting.setValue("udp_port",                m_broadcastPortSpinBox->value());
        setting.setValue("tcp_port",                m_tranferPortSpinBox->value());
        setting.setValue("lang",                    m_langComboBox->currentIndex());
        setting.setValue("history_record_days",     m_historySavedDaysSpinBox->value());
        setting.setValue("file_storage_path",       m_fileStorageLineEdit->text());
        setting.setValue("balloon_message_enabled", m_enableMessageCheckBox->isChecked());
        setting.setValue("private_lan_enabled",     m_privateGroupBox->isChecked());
        setting.setValue("private_code",            m_privateCodeLineEdit->text());
    }

    emit preferenceIniSaved();

    event->accept();
}

void PreferenceWidget::updateSizes(int index)
{
    for (int i = 0; i < m_tabWidget->count(); ++i)
    {
        if (i != index)
        {
            m_tabWidget->widget(i)->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        }
    }

    m_tabWidget->widget(index)->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    m_tabWidget->widget(index)->resize(m_tabWidget->widget(index)->minimumSizeHint());
    m_tabWidget->widget(index)->adjustSize();
    resize(minimumSizeHint());
    adjustSize();
}

void PreferenceWidget::generateRandomCode()
{
    QRandomGenerator generator(static_cast<quint32>(QDateTime::currentSecsSinceEpoch()));

    static const char candidates[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static int candidatesSize = sizeof(candidates);

    QString code;

    for (int i = 0; i < 8; ++i)
    {
        code += candidates[generator.bounded(0, candidatesSize - 1)];
    }

    m_privateCodeLineEdit->setText(code);
}

void PreferenceWidget::selectFileStorageDir()
{
    QString storageDir = QFileDialog::getExistingDirectory(this,
                                                           tr("Select Directory"),
                                                           m_fileStorageLineEdit->text(),
                                                           QFileDialog::ShowDirsOnly);
    if (storageDir.isEmpty() == false)
        m_fileStorageLineEdit->setText(storageDir);
}

QWidget* PreferenceWidget::createGeneralWidget()
{
    QWidget* generalWidget = new QWidget;

    QGroupBox* portGroupBox    = new QGroupBox(tr("Port (Restart required)"), generalWidget);
    QLabel* broadcastPortLabel = new QLabel(tr("Broadcast port:"), portGroupBox);
    QLabel* tranferPortLabel   = new QLabel(tr("Tranfer port:"), portGroupBox);
    m_broadcastPortSpinBox     = new QSpinBox(portGroupBox);
    m_tranferPortSpinBox       = new QSpinBox(portGroupBox);
    m_broadcastPortSpinBox->setRange(0, 62235);
    m_tranferPortSpinBox->setRange(0, 62235);
    m_broadcastPortSpinBox->setValue(4644);
    m_tranferPortSpinBox->setValue(4644);
    QHBoxLayout* hLayout1 = new QHBoxLayout(portGroupBox);
    hLayout1->addWidget(broadcastPortLabel);
    hLayout1->addWidget(m_broadcastPortSpinBox);
    hLayout1->addStretch();
    hLayout1->addWidget(tranferPortLabel);
    hLayout1->addWidget(m_tranferPortSpinBox);

    QGroupBox* langGroupBox = new QGroupBox(tr("Language (Restart required)"), generalWidget);
    QLabel* langLabel       = new QLabel(tr("Language:"), this);
    m_langComboBox          = new QComboBox(this);
    m_langComboBox->addItems(QStringList() <<
                             QString::fromLocal8Bit("English") <<
                             QString::fromLocal8Bit("简体中文"));
    QHBoxLayout* hLayout2 = new QHBoxLayout(langGroupBox);
    hLayout2->addWidget(langLabel);
    hLayout2->addWidget(m_langComboBox);
    hLayout2->addStretch();

    QGroupBox* historyGroupBox    = new QGroupBox(tr("History"), generalWidget);
    QLabel* historySavedDaysLabel = new QLabel(tr("Max days of history record:"), historyGroupBox);
    m_historySavedDaysSpinBox     = new QSpinBox(historyGroupBox);
    m_historySavedDaysSpinBox->setValue(30);
    m_historySavedDaysSpinBox->setRange(0, 365);
    QHBoxLayout* hLayout3 = new QHBoxLayout(historyGroupBox);
    hLayout3->addWidget(historySavedDaysLabel);
    hLayout3->addWidget(m_historySavedDaysSpinBox);
    hLayout3->addStretch();

    QGroupBox*   fileStorageGroupBox = new QGroupBox(tr("File Storage"), generalWidget);
    QLabel*      pathLabel           = new QLabel(tr("Path:"), fileStorageGroupBox);
    QPushButton* selectBtn           = new QPushButton(tr("Select"), fileStorageGroupBox);
    m_fileStorageLineEdit            = new QLineEdit(fileStorageGroupBox);
    m_fileStorageLineEdit->setText(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    m_fileStorageLineEdit->setFocusPolicy(Qt::NoFocus);
    connect(selectBtn, &QPushButton::clicked, this, &PreferenceWidget::selectFileStorageDir);
    QHBoxLayout* hLayout4 = new QHBoxLayout(fileStorageGroupBox);
    hLayout4->addWidget(pathLabel);
    hLayout4->addWidget(m_fileStorageLineEdit);
    hLayout4->addWidget(selectBtn);

    QVBoxLayout* vLayout1 = new QVBoxLayout(generalWidget);
    vLayout1->addWidget(portGroupBox);
    vLayout1->addWidget(langGroupBox);
    vLayout1->addWidget(historyGroupBox);
    vLayout1->addWidget(fileStorageGroupBox);

    return generalWidget;
}

QWidget* PreferenceWidget::createBehaviorWidget()
{
    QWidget* behaviorWidget = new QWidget;

    QGroupBox* systemTrayGroupBox = new QGroupBox(tr("System Tray"), behaviorWidget);
    m_enableMessageCheckBox       = new QCheckBox(tr("Enable balloon messages if received files or text"), systemTrayGroupBox);
    m_enableMessageCheckBox->setChecked(true);
    QHBoxLayout* hLayout1 = new QHBoxLayout(systemTrayGroupBox);
    hLayout1->addWidget(m_enableMessageCheckBox);
    hLayout1->addStretch();

    m_privateGroupBox              = new QGroupBox(tr("Enable Private LAN"), behaviorWidget);
    QLabel* privateCodeLabel       = new QLabel(tr("Private code:"), m_privateGroupBox);
    m_privateCodeLineEdit          = new QLineEdit(m_privateGroupBox);
    QPushButton* generateBtn       = new QPushButton(tr("Generate"), m_privateGroupBox);
    QRegExpValidator* regValidator = new QRegExpValidator(QRegExp("[A-Za-z0-9]{8}"), m_privateCodeLineEdit);
    QLabel* tipLabel               = new QLabel(tr("*This allows people with the same private code to form a private LAN with you."),
                                                m_privateGroupBox);
    m_privateCodeLineEdit->setValidator(regValidator);
    m_privateCodeLineEdit->setPlaceholderText(tr("only support 8 digits or letters"));
    m_privateGroupBox->setCheckable(true);
    m_privateGroupBox->setChecked(false);
    tipLabel->setEnabled(false);
    connect(generateBtn, &QPushButton::clicked, this, &PreferenceWidget::generateRandomCode);
    QHBoxLayout* hLayout2 = new QHBoxLayout;
    hLayout2->addWidget(privateCodeLabel);
    hLayout2->addWidget(m_privateCodeLineEdit);
    hLayout2->addWidget(generateBtn);
    QVBoxLayout* vLayout1 = new QVBoxLayout(m_privateGroupBox);
    vLayout1->addLayout(hLayout2);
    vLayout1->addWidget(tipLabel);

    QVBoxLayout* mainLayout = new QVBoxLayout(behaviorWidget);
    mainLayout->addWidget(systemTrayGroupBox);
    mainLayout->addWidget(m_privateGroupBox);

    return behaviorWidget;
}
