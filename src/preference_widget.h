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

/**
 * A widget to show preference.
 */
class PreferenceWidget : public QWidget
{
    Q_OBJECT

public:

    PreferenceWidget(QWidget* parent = nullptr);

protected:

    void closeEvent(QCloseEvent* event) override;

private slots:

    void updateSizes(int index);

    /**
     * To generate 8 random characters.
     */
    void generateRandomCode();

    void selectFileStorageDir();

signals:

    /**
     * If preference file is changed and resaved, you should emit this signal.
     */
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
