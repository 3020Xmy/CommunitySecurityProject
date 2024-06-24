#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QDir>
#include <QWidget>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QSqlDatabase>
#include "srcFile/detection.h"

namespace Ui {
class registerWidget;
}

class registerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit registerWidget(QWidget *parent = nullptr);
    ~registerWidget();

private slots:
    //重置操作
    void on_clear_Button_clicked();
    //添加图像操作
    void on_add_Img_clicked();
    //注册操作
    void on_Register_Button_clicked();
    //打开摄像头操作
    void on_open_But_clicked();
    //拍照操作
    void on_camera_But_clicked();

protected:
    void timerEvent(QTimerEvent *event);
signals:
    //请求数据库保存用户注册信息
    void request_SqlSaveUserInfo(QString sqlCode);
private:
    Ui::registerWidget *ui;
    int timer_ID;   //定时器ID
    cv::Mat save_Image; //保存的图像
    cv::VideoCapture capture_Obj;   //摄像头对象
};

#endif // REGISTERWIDGET_H
