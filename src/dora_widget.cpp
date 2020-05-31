#include "src/dora_widget.h"

#include <QIcon>

DoraWidget::DoraWidget(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Dora");
    setWindowIcon(QIcon(":/dora.png"));

    connect(&m_preferenceWidget, &PreferenceWidget::preferenceIniSaved,
            &m_doraProtocol, &DoraProtocol::initializeFromPreferenceIni);
}

void DoraWidget::showPreferenceWidget()
{
    m_preferenceWidget.show();
}
