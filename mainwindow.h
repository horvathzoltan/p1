#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSignalMapper>
//#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addWidget(QWidget *w);

private:
    Ui::MainWindow *ui;
    //void createActions();
    QSignalMapper *pSignalMapper;
    QWidget *w = nullptr;
private slots:
    void on_MasterDataEditorAction_triggered();
    void on_menuHelp_triggered();
    //void on_pushButton_clicked();

/*protected:
     bool eventFilter(QObject *obj, QEvent *event);*/
};

#endif // MAINWINDOW_H
