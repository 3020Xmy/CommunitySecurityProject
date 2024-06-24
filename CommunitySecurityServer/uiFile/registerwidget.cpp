#include "registerwidget.h"
#include "ui_registerwidget.h"

registerWidget::registerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registerWidget)
{
    ui->setupUi(this);
    QDir().mkdir("data");   //创建图像保存目录
}

registerWidget::~registerWidget()
{
    delete ui;
}

/*  重置操作
*/
void registerWidget::on_clear_Button_clicked()
{
    //清除数据
    ui->path_Edit->clear();
    ui->name_Edit->clear();
    ui->phone_Edit->clear();
    ui->address_Edit->clear();
    ui->dateEdit->setDate(QDate::currentDate());
}

/*  添加图像操作
*/
void registerWidget::on_add_Img_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this);  //选择图像
    ui->path_Edit->setText(filePath);

    //显示图像
    QPixmap pixmap(filePath);
    pixmap = pixmap.scaledToWidth(ui->show_Img->width());
    ui->show_Img->setPixmap(pixmap);
}

/*  注册操作
*/
void registerWidget::on_Register_Button_clicked()
{
    //用户图像信息注册
    Detection faceObj;
    cv::Mat image = cv::imread(ui->path_Edit->text().toUtf8().data());
    int id = faceObj.handle_UserRegister(image);
    QString imgPath = QString("./data/%1.jpg").arg(ui->name_Edit->text().toUtf8().Base64Encoding);  //设置图像保存路径

    //添加用户信息至数据库
    QString sqlCode =  QString("INSERT INTO UserInfo(name, sex, birthday, address, phone, faceID, headfile)VALUES"
                               "('%1','%2','%3','%4','%5', '%6', '%7');").arg(ui->name_Edit->text())
                               .arg(ui->man_radio->isChecked() ? "男" : "女").arg(ui->dateEdit->text())
                               .arg(ui->address_Edit->text()).arg(ui->phone_Edit->text()).arg(id).arg(imgPath);
    emit request_SqlSaveUserInfo(sqlCode);
}

/*  打开摄像头操作
*/
void registerWidget::on_open_But_clicked()
{
    if(ui->open_But->text() == "打开摄像头"){
        //捕获摄像头图片
        if(capture_Obj.open("/dev/video0")){
            ui->open_But->setText("关闭摄像头");
            timer_ID = startTimer(100); //启动定时器
        }
    }else{
        killTimer(timer_ID);    //关闭定时器
        capture_Obj.release();  //关闭摄像头
        ui->open_But->setText("打开摄像头");
    }
}

/*  定时器事件
 *  event：事件
*/
void registerWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    if(capture_Obj.isOpened()){   //捕获画面数据
        capture_Obj >> save_Image;
    }

    if(save_Image.data != nullptr){
        //转换数据格式为RGB
        cv::Mat imageRGB;
        cv::cvtColor(save_Image,imageRGB,cv::COLOR_BGR2RGB);
        QImage showImg(imageRGB.data,imageRGB.cols,imageRGB.rows,imageRGB.step1(),QImage::Format_RGB888);
        QPixmap pixmap = QPixmap::fromImage(showImg);
        pixmap = pixmap.scaledToWidth(ui->show_Img->width());
        ui->show_Img->setPixmap(pixmap);
    }
}

/*  拍照操作
*/
void registerWidget::on_camera_But_clicked()
{
    if(ui->open_But->text() == "关闭摄像头"){
        //保存当前图像
        QString imgPath = QString("./data/%1.jpg").arg(ui->name_Edit->text().toUtf8().Base64Encoding);  //设置图像保存路径
        ui->path_Edit->setText(imgPath);
        cv::imwrite(imgPath.toUtf8().data(),save_Image);

        killTimer(timer_ID);    //关闭定时器
        capture_Obj.release();  //关闭摄像头
        ui->open_But->setText("打开摄像头");
    }
}
