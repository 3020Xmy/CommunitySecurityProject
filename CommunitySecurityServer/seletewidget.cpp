#include "seletewidget.h"
#include "ui_seletewidget.h"

seleteWidget::seleteWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::seleteWidget)
{
    ui->setupUi(this);
}

seleteWidget::~seleteWidget()
{
    delete ui;
}
