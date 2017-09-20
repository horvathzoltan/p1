#include "zspinbox.h"
//#include <QLineEdit>

zSpinBox::zSpinBox(QWidget* parent) : QSpinBox(parent){}

void zSpinBox::setPlaceholderText(const QString &str){
    this->lineEdit()->setPlaceholderText(str);
}

void zSpinBox::addAction(QAction *a, QLineEdit::ActionPosition p){
    this->lineEdit()->addAction(a, p);
}

void zSpinBox::setInputMask(const QString &inputMask){
    this->lineEdit()->setInputMask(inputMask);
}

void zSpinBox::setClearButtonEnabled(bool enable){
    this->lineEdit()->setClearButtonEnabled(enable);    
}

void zSpinBox::setText(const QString &str){
    this->lineEdit()->setText(str);
}

void zSpinBox::setCursorPosition(int i){
    this->lineEdit()->setCursorPosition(i);
}
