#ifndef SRC_UPDATES_CHECKING_WIDGET_H
#define SRC_UPDATES_CHECKING_WIDGET_H

#include "src/config.h"

#include <QWidget>

/**
 * A widget to check updates.
 */
class UpdatesCheckingWidget : public QWidget
{
    Q_OBJECT

public:

    UpdatesCheckingWidget(QWidget* parent = nullptr);
};

#endif /** SRC_UPDATES_CHECKING_WIDGET_H */
