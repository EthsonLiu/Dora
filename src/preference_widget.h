#ifndef SRC_PREFERENCE_WIDGET_H
#define SRC_PREFERENCE_WIDGET_H

#include <QWidget>

class PreferenceWidget : public QWidget
{
    Q_OBJECT

public:

    PreferenceWidget(QWidget* parent = nullptr);

private:

    QWidget* createGeneralWidget();

};

#endif /** SRC_PREFERENCE_WIDGET_H */
