#include "preference_widget.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTabWidget>

PreferenceWidget::PreferenceWidget(QWidget* parent) : QWidget(parent)
{
    setWindowTitle(tr("Preference"));

    QTabWidget* tabWidget = new QTabWidget(this);
    tabWidget->addTab(createGeneralWidget(), tr("General"));

    QHBoxLayout* hLayout = new QHBoxLayout(this);
    hLayout->addWidget(tabWidget);
    setLayout(hLayout);
}

QWidget* PreferenceWidget::createGeneralWidget()
{
    QWidget* generalWidget = new QWidget;

    QGroupBox* portGroupBox = new QGroupBox(tr("Port"), generalWidget);

    QVBoxLayout* vLayout = new QVBoxLayout(generalWidget);
    vLayout->addWidget(portGroupBox);

    return generalWidget;
}
