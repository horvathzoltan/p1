#ifndef ZITEMEDITORFACTORY_H
#define ZITEMEDITORFACTORY_H

#include <QItemEditorFactory>
#include <zfield.h>
#include "zspinbox.h"
#include "helpform.h"

class zItemEditorFactory : public QItemEditorFactory
{    
public:
  helpform *hf;

  zItemEditorFactory() { hf = nullptr; }
  QWidget* createEditor(int type, QWidget *parent) const;
  static QVariant getEditorValue(QWidget* w);

  static void initEditor(QWidget*, zField*, int, QVariant);

  static void onHelpActionTriggered(QString, QString);

  static void onDefaultActionTriggered(QLineEdit *w, QVariant v);
  static void onDefaultActionTriggered(zSpinBox *w, QVariant v);

  static void onDeleteActionTriggered(QLineEdit *w);
  static void onDeleteActionTriggered(zSpinBox *w);

  enum InitFlags
  {
      DefaultFlag = 1 << 0,
      Proba1Flag = 1 << 1,
      Proba2Flag = 1 << 2
  };
};

#endif // ZITEMEDITORFACTORY_H
