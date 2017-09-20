#ifndef HELPFORM_H
#define HELPFORM_H

#include <QWidget>
#include <QMap>

namespace Ui {
class helpform;
}

class helpform : public QWidget
{
    Q_OBJECT

public:
    explicit helpform(QWidget *parent = 0);
    ~helpform();
    void addUrl(QString, QString);    
private:
    Ui::helpform *ui;
    QMap<QString, int> capmap;
};

#endif // HELPFORM_H
