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

#ifndef SRC_PREFERENCE_WIDGET_H
#define SRC_PREFERENCE_WIDGET_H

#include "src/config.h"

#include <QWidget>
#include <QString>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QTabWidget>
#include <QLineEdit>
#include <QGroupBox>
#include <QCloseEvent>

enum class Lang
{
    english,
    simplifiedChinese
};

class PreferenceWidget : public QWidget
{
    Q_OBJECT

public:

    PreferenceWidget(QWidget* parent = nullptr);

protected:

    void closeEvent(QCloseEvent* event) override;

private slots:

    void updateSizes(int index);
    void generateRandomCode();
    void selectFileStorageDir();

signals:

    void preferenceIniSaved();

private:

    QWidget* createGeneralWidget();
    QWidget* createBehaviorWidget();

private:

    QTabWidget* m_tabWidget;
    QSpinBox*   m_broadcastPortSpinBox;
    QSpinBox*   m_tranferPortSpinBox;
    QSpinBox*   m_historySavedDaysSpinBox;
    QComboBox*  m_langComboBox;
    QCheckBox*  m_enableMessageCheckBox;
    QLineEdit*  m_privateCodeLineEdit;
    QLineEdit*  m_fileStorageLineEdit;
    QGroupBox*  m_privateGroupBox;

};

#endif /** SRC_PREFERENCE_WIDGET_H */
