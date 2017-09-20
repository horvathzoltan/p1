#include "helpform.h"
#include "ui_helpform.h"

#include <QWebEngineView>
#include <QUrl>

helpform::helpform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::helpform)
{
    ui->setupUi(this);
}

helpform::~helpform()
{
    delete ui;
    qDebug() << "~helpform";
}

void helpform::addUrl(QString url, QString tabName){

    QWebEngineView *w1 = new QWebEngineView(parentWidget());

    if(!capmap.contains(tabName)){
        capmap.insert(tabName, ui->tabWidget->count());
        ui->tabWidget->addTab(w1, tabName);
        ui->tabWidget->setCurrentWidget(w1);
        w1->load(QUrl(url));
        w1->show();
    }
    else{
        ui->tabWidget->setCurrentIndex(capmap.value(tabName));
    }

}
