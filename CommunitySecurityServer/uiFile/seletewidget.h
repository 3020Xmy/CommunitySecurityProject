#ifndef SELETEWIDGET_H
#define SELETEWIDGET_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class seleteWidget;
}

class seleteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit seleteWidget(QWidget *parent = nullptr);
    ~seleteWidget();

private slots:
    //查询操作
    void on_pushButton_clicked();

private:
    Ui::seleteWidget *ui;
    QSqlTableModel* model_Obj;  //数据表对象
};

#endif // SELETEWIDGET_H
