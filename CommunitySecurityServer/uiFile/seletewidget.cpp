#include "seletewidget.h"
#include "ui_seletewidget.h"

seleteWidget::seleteWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::seleteWidget)
{
    ui->setupUi(this);

    model_Obj = new QSqlTableModel();   //初始化数据表对象
}

seleteWidget::~seleteWidget()
{
    delete ui;
}

/*  查询操作
*/
void seleteWidget::on_pushButton_clicked()
{
    if(ui->emp_Rbtn->isChecked()){
        model_Obj->setTable("UserInfo");
    }else if(ui->att_Rbtn->isChecked()){
        model_Obj->setTable("AttendanceInfo");
    }

    //查询数据
    model_Obj->select();
    ui->tableView->setModel(model_Obj);
}
