#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "masterdataform.h"

//#include "masterdata.h"
#include "zexception.h"
#include "globals.h"
#include "common/logger/log.h"

//extern MasterData md;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ui = new Ui::MainWindow;
    ui->setupUi(this);
    pSignalMapper = nullptr;
  // createActions();
}


void MainWindow::addWidget(QWidget *w){
    setCentralWidget(w);
}

MainWindow::~MainWindow()
{
    delete ui;

    //qDeleteAll(md.zsql);
    //md.zsql.clear();
    //md.zsql.squeeze();
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
    zTrace();
}

// TODO be kell léptetni a mókust
// ha debug, és a gép a fejlesztői listában van, akkor ő a devel
// amúgy feljön az ablak, és beírja
// de ha ő a devel, akkor 3-tól visszaszámol és belép
// tudni kell ki az user
// tudni kell, mi a joga - nem a string kellene, hanem valamilyen szabály (pl helyettesítés figyelembevételével)
// tudni kell, milyen művelet van megnyitva - ha ez, akkor nem kell csinálni semmit

// egy project - egy menü - amiben a project műveletei vannak - pl a project törzsadat-szerkesztője
// a projectben műveleteket lehet végezni, ezek folyamatok
void MainWindow::on_MasterDataEditorAction_triggered()
{

    if(!md.user.hasRole(QStringLiteral("user"))) return;

    delete w;
    this->addWidget(new masterDataForm());
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
