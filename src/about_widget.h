#ifndef SRC_ABOUT_WIDGET_H
#define SRC_ABOUT_WIDGET_H

#include "src/config.h"

#include <QWidget>

class AboutWidget : public QWidget
{
    Q_OBJECT

public:

    AboutWidget(QWidget* parent = nullptr);
};

#endif /** SRC_ABOUT_WIDGET_H */
