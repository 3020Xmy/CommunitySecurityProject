#ifndef SELETEWIDGET_H
#define SELETEWIDGET_H

#include <QWidget>

namespace Ui {
class seleteWidget;
}

class seleteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit seleteWidget(QWidget *parent = nullptr);
    ~seleteWidget();

private:
    Ui::seleteWidget *ui;
};

#endif // SELETEWIDGET_H
