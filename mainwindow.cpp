#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "masterdataform.h"

//#include "masterdata.h"
#include "zexception.h"
#include "globals.h"

//extern MasterData md;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ui = new Ui::MainWindow;
    ui->setupUi(this);
  // createActions();
}


void MainWindow::addWidget(QWidget *w){
    setCentralWidget(w);
}

MainWindow::~MainWindow()
{
    delete ui;

    qDeleteAll(md.zsql);
    md.zsql.clear();
    md.zsql.squeeze();
}

//void MainWindow::createActions()
//{
   // pSignalMapper = new QSignalMapper(this);
   // connect(ui->menuHelp, SIGNAL(triggered(QAction*)), this, SLOT(on_menuHelp_triggered()));
   // connect(ui->MasterDataEditorAction, SIGNAL(triggered(QAction*)), this, SLOT(on_MasterDataEditorAction_triggered()));
//}

/*void MainWindow::help()
{
    qDebug()<<"inside help qdialog";
}*/

void MainWindow::on_menuHelp_triggered()
{
     qDebug()<<"on_menuHelp_triggered";
}

void MainWindow::on_MasterDataEditorAction_triggered()
{
/*
 * if(userHasRole("MDE"))//MasterDataEditor
*/


     delete w;

     auto *w = new masterDataForm();
     QList<zListItem> sl1;

     for(int i=0;i<md.zentity.length();i++)
     {
         zTable* e = md.zentity[i];

         if(e!=nullptr)
         {
             sl1.append({e->caption, i});
         }
         else
         {
             qDebug() <<"NULL";
         }
     };


     w->setEntityList(&sl1);

     //delete sl1;

     this->addWidget(w);
}



//void MainWindow::on_pushButton_clicked()
//{
//    qDebug("aaassssdddd");
//}

/*
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
      //  QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
           qDebug() << "key " << "a" << "from" << obj;
    }
    // qDebug() << event << " from " << obj;
    return QObject::eventFilter(obj, event);
}
*/
