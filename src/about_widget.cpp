#include "src/about_widget.h"
#include "src/project.h"

#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QPushButton>
#include <QApplication>
#include <QDesktopServices>
#include <QDateTime>

AboutWidget::AboutWidget(QWidget* parent) : QWidget(parent)
{
    setWindowTitle(tr("About"));
    setFixedSize(650, 300);

    QLabel* logoLabel = new QLabel(this);
    logoLabel->setPixmap(QPixmap(":/dora.png").scaled(40, 40));

    QLabel* titleLabel = new QLabel("Dora", this);
    QFont titleFont;
    titleFont.setPointSize(23);
    titleLabel->setFont(titleFont);

    QHBoxLayout* hLayout1 = new QHBoxLayout;
    hLayout1->addWidget(logoLabel);
    hLayout1->addWidget(titleLabel);
    hLayout1->addStretch();

    QLabel* versionLabel = new QLabel(QString(tr("Version")) +
                                      QString(" %1 (%2)").
                                      arg(Project::getApplicationVersion()).
                                      arg(Project::getApplicationReleasedDate()),
                                      this);
    QLabel* websiteLabel = new QLabel(QString(tr("Website")) + " <a href=\"https://github.com/ethsonliu/dora\">https://github.com/ethsonliu/dora</a>");
    websiteLabel->setTextFormat(Qt::RichText);
    websiteLabel->setOpenExternalLinks(true);
    QString personalInfo = "";
    QLabel* authorsLabel = new QLabel(QString(tr("Copyright")) +
                                      QString(" 2020-%1, ").arg(QDateTime::currentDateTime().toString("yyyy")) +
                                      QString(tr("created by Ethson Liu.")));

    QHBoxLayout* hLayout2 = new QHBoxLayout;
    hLayout2->addWidget(websiteLabel);
    hLayout2->addStretch();

    QVBoxLayout* vLayout1 = new QVBoxLayout;
    vLayout1->addWidget(versionLabel);
    vLayout1->addLayout(hLayout2);
    vLayout1->addWidget(authorsLabel);

    QPushButton* aboutQtBtn = new QPushButton("About Qt", this);
    connect(aboutQtBtn, &QPushButton::clicked, qApp, &QApplication::aboutQt);
    QPushButton* closeBtn = new QPushButton(tr("Close"), this);
    connect(closeBtn, &QPushButton::clicked, this, &AboutWidget::close);

    QHBoxLayout* hLayout3 = new QHBoxLayout;
    hLayout3->addWidget(aboutQtBtn);
    hLayout3->addStretch();
    hLayout3->addWidget(closeBtn);

    QVBoxLayout* vLayout2 = new QVBoxLayout(this);
    vLayout2->addLayout(hLayout1);
    vLayout2->addSpacing(25);
    vLayout2->addLayout(vLayout1);
    vLayout2->addSpacing(50);
    vLayout2->addLayout(hLayout3);
}
