#ifndef SRC_DORA_WIDGET_H
#define SRC_DORA_WIDGET_H

#include "src/config.h"
#include "src/preference_widget.h"
#include "src/dora_protocol.h"

#include <QWidget>

class DoraWidget : public QWidget
{
    Q_OBJECT

public:

    explicit DoraWidget(QWidget* parent = nullptr);

public slots:

    void showPreferenceWidget();

private:

    PreferenceWidget m_preferenceWidget;
    DoraProtocol    m_doraProtocol;
};

#endif /** SRC_DORA_WIDGET_H */
