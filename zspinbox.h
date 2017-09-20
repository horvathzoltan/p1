#ifndef ZSPINBOX_H
#define ZSPINBOX_H

#include <QSpinBox>
#include <QLineEdit>

class zSpinBox : public QSpinBox// integers and discrete sets
{
    Q_OBJECT
public:
    zSpinBox(QWidget* parent = 0);

    void setPlaceholderText(const QString &);
    void addAction(QAction *action, QLineEdit::ActionPosition position);
    void setInputMask(const QString &inputMask);
    void setClearButtonEnabled(bool enable);
    void setText(const QString &);
    void setCursorPosition(int i);
};

#endif // ZSPINBOX_H
