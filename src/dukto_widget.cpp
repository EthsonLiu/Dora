#include "dukto_widget.h"

#include <QIcon>

DuktoWidget::DuktoWidget(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Dukto");
    setWindowIcon(QIcon(":/dukto.ico"));
}
