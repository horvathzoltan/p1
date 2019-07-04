//#include "zitemeditorfactory.h"
#include "zspinbox.h"
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDateTimeEdit>
#include <QCheckBox>
#include <QLabel>

#include <QAction>

#include "globals.h"
#include <QDesktopServices>
#include <QUrl>
#include <math.h>
#include "helpform.h"

QWidget* zItemEditorFactory::createEditor(int type, QWidget *parent) const {
  switch (type) {
      case QVariant::UInt:
      case QVariant::Int:{
        zSpinBox *sb = new zSpinBox(parent);
        sb->setPlaceholderText("abcd");
        //if(v.isValid())
        //  le->setValue(v.toInt());
        return sb;
        }
      default:
        return QItemEditorFactory::createEditor(type, parent);
  }
}

QVariant zItemEditorFactory::getEditorValue(QWidget* w){
    if(QLineEdit *le = qobject_cast<QLineEdit *>(w)){ return QVariant(le->text()); }
    else if(zSpinBox *le = qobject_cast<zSpinBox *>(w)){ return QVariant(le->value()); }
    else if(QDoubleSpinBox *le = qobject_cast<QDoubleSpinBox *>(w)){ return QVariant(le->value());  }
    else if(QDateTimeEdit *le = qobject_cast<QDateTimeEdit *>(w)){  return QVariant(le->dateTime());    }
    else if(QCheckBox *le = qobject_cast<QCheckBox *>(w)){ return QVariant(le->checkState());     }
    else if(QLabel *le = qobject_cast<QLabel *>(w)){ return QVariant(le->text()); }
    else return QVariant();
}

void zItemEditorFactory::initEditor(QWidget* w, zTablerow* f, int flag, QVariant v){

    QString placeholder = f->placeholder;
    if(f->isRequired){
        if(!placeholder.isEmpty())
            placeholder += " ";
        placeholder += "<Required>";
    }

    if((flag & DefaultFlag) && f->defaultValue.isValid())
        v = f->defaultValue;

    QAction *helpAction = nullptr;
    if(!f->help.isEmpty()){
        helpAction = new QAction(QIcon(":/ic_help_black_18px.svg"), "help"); //help-contents, help-about
        //helpAction = new QAction(QIcon::fromTheme("help-about"), "help"); //help-contents, help-about
        helpAction->setData(f->help);
        }

    QAction *defaultAction = nullptr;
    if(v.isValid()){//
        //defaultAction = new QAction(QIcon::fromTheme("edit-paste"), "default"); //help-contents, help-about
        defaultAction = new QAction(QIcon(":/ic_settings_backup_restore_black_18px.svg"), "default"); //emblem-default
        defaultAction->setData(v);
        //helpAction->setData(f->help);
        }

    QAction *deleteAction = nullptr;
    if(!f->isRequired){
        deleteAction = new QAction(QIcon(":/ic_delete_black_18px.svg"), "delete");
        }

    w->setFixedWidth(300);

    if(QLineEdit *le = qobject_cast<QLineEdit *>(w)){ //szöveges editor     
        le->setFrame(true);

        if(!placeholder.isEmpty())
            le->setPlaceholderText(placeholder);
        if(!f->mask.isEmpty())
            le->setInputMask(f->mask+";_");
        if(v.isValid())
            le->setText(v.toString());

        //le->setClearButtonEnabled(!f->isRequired);

        if(deleteAction){
            le->addAction(deleteAction, QLineEdit::TrailingPosition);
            QAction::connect(deleteAction, &QAction::triggered, [le,deleteAction]{onDeleteActionTriggered(le);});
        }
        if(helpAction){
            le->addAction(helpAction, QLineEdit::TrailingPosition);
            QAction::connect(helpAction, &QAction::triggered, [helpAction, f]{onHelpActionTriggered(helpAction->data().toString(), f->caption);});
            }
        if(defaultAction){
            le->addAction(defaultAction, QLineEdit::TrailingPosition);
            QAction::connect(defaultAction, &QAction::triggered, [le,defaultAction]{onDefaultActionTriggered(le, defaultAction->data());});
            }        
        }
    else if(zSpinBox *le = qobject_cast<zSpinBox *>(w)){ //int editor
        le->setFrame(true);

        le->setMinimum(0);
        le->setMaximum(INT32_MAX);
        //le->lineEdit();
        if(!placeholder.isEmpty())
            le->setPlaceholderText(placeholder);
        if(!f->mask.isEmpty())
            le->setInputMask(f->mask+";_");
        if(v.isValid())
            le->setValue(v.toInt());
        //le->setClearButtonEnabled(!f->isRequired);
        if(deleteAction){
            le->addAction(deleteAction, QLineEdit::TrailingPosition);
            QAction::connect(deleteAction, &QAction::triggered, [le,deleteAction]{onDeleteActionTriggered(le);});
        }
        if(helpAction){
            le->addAction(helpAction, QLineEdit::TrailingPosition);
            QAction::connect(helpAction, &QAction::triggered, [helpAction, f]{onHelpActionTriggered(helpAction->data().toString(), f->caption);});
            }        
        if(defaultAction){
            le->addAction(defaultAction, QLineEdit::TrailingPosition);
            QAction::connect(defaultAction, &QAction::triggered, [le,defaultAction]{onDefaultActionTriggered(le, defaultAction->data());});
            }
        }
    // short, long, longlong
    else if(QDoubleSpinBox *le = qobject_cast<QDoubleSpinBox *>(w)){  //double editor
        if(v.isValid())
            le->setValue(v.toDouble());
        }
    else if(QDateTimeEdit *le = qobject_cast<QDateTimeEdit *>(w)){  //datetime editor
        if(v.isValid())
            le->setDateTime(v.toDateTime());
    }
    //QDateEdit, time
    else if(QCheckBox *le = qobject_cast<QCheckBox *>(w)){  //datetime editor
        if(v.isValid()) //
            le->setChecked(v.toBool());
    }
    //QCheckBox
    else if(QLabel *le = qobject_cast<QLabel *>(w)){ //labeles editor
        if(v.isValid())
            le->setText(v.toString());
        }

    if(!f->tooltip.isEmpty()){
        w->setToolTip(f->tooltip);
        }

    return;
}

void zItemEditorFactory::onHelpActionTriggered(QString url, QString caption){
    //qDebug() << "onHelpActionTriggered: " << url;

    if(zif.hf == nullptr){
        zif.hf = new helpform(0);
        zif.hf->resize(1024,768);
        zif.hf->show();
    }
    zif.hf->addUrl(url, caption);
}
/*
Default
*/

void zItemEditorFactory::onDefaultActionTriggered(QLineEdit *w, QVariant v){
    auto i = v.toString();
    int l = i.length();

    w->setText(i);
    w->setCursorPosition(l);
}

void zItemEditorFactory::onDefaultActionTriggered(zSpinBox *w, QVariant v){
    int i = v.toInt();
    int l = i > 0 ? static_cast<int>(log10(static_cast<double>(i))+1) : 1;

    w->setValue(i);
    w->setCursorPosition(l);
}

/*
Delete
*/

void zItemEditorFactory::onDeleteActionTriggered(QLineEdit *w){
    w->setText("");
    w->setCursorPosition(0);
}

void zItemEditorFactory::onDeleteActionTriggered(zSpinBox *w){
    w->setText("");
    w->setCursorPosition(0);
}

