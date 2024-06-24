#include "communitysecurityclient.h"
#include "ui_communitysecurityclient.h"

#include <QDebug>

CommunitySecurityClient::CommunitySecurityClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CommunitySecurityClient)
{
    ui->setupUi(this);

    faceFlag_Obj = 0;

    handle_InitCamera();//初始化摄像头
    handle_InitClassifier();//初始化级联分类器对象
    handle_InitTcpConnect();//初始化TCP链接槽函数
    handle_InitHeartBea();  //初始化心跳包
}

CommunitySecurityClient::~CommunitySecurityClient()
{
    delete ui;
}

////--------------------------------------------------摄像头操作模块--------------------------------------------------------
/*  初始化摄像头
*/
void CommunitySecurityClient::handle_InitCamera()
{
    Capture_Obj.open("/dev/video0");
    startTimer(100);    //启动定时器
}

////--------------------------------------------------级联分类器操作模块-----------------------------------------------------
/*  人脸检测
 *  image：识别的图像数据
*/
void CommunitySecurityClient::handle_FaceDetection(Mat& image)
{
    Mat grayImage;
    cvtColor(image,grayImage,COLOR_BGR2GRAY);   //转化为灰度图提高效率

    //检测人脸位置
    std::vector<Rect> faceRect;
    classifier_Obj.detectMultiScale(grayImage,faceRect);
    if((faceRect.size() > 0) && (faceFlag_Obj >= 0)){    //读取到人脸数据
        Rect rect = faceRect.at(0);
        rectangle(image,rect,Scalar(0,0,255));
        handle_MatConvertInJpg(image);
    }
    if(faceRect.size() == 0){
        faceFlag_Obj = 0;
    }
}

/*  将Mat类型数据转化为Jpg存储
 *  image：转化的Mat数据
*/
void CommunitySecurityClient::handle_MatConvertInJpg(const Mat &image)
{
    if(faceFlag_Obj > 2){
        vector<uchar> buffer;
        imencode(".jpg",image,buffer);  //格式转换

        //发送检测数据至服务器
        handle_SendingDatainServer(QByteArray::fromRawData(reinterpret_cast<const char*>(buffer.data()), buffer.size()));
    }
    faceFlag_Obj++;
}

/*  初始化级联分类器对象
*/
void CommunitySecurityClient::handle_InitClassifier()
{
    classifier_Obj.load("../CommunitySecurityClient/ClassifierFile/haarcascade_frontalface_alt2.xml");
}

////--------------------------------------------------定时器操作模块---------------------------------------------------------
/*  定时器事件
 *  event：事件
*/
void CommunitySecurityClient::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    Mat imageData;  //捕获的图像数据
    if(Capture_Obj.grab()){
        Capture_Obj.read(imageData);
    }
    if(imageData.data == nullptr){  //未捕获到图像
        return;
    }

    handle_FaceDetection(imageData);//人脸检测

    cvtColor(imageData,imageData,COLOR_BGR2RGB);    //将捕获的图像格式转化
    QImage showImage(imageData.data,imageData.cols,imageData.rows,imageData.step1(),QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(showImage);
    ui->show_Img->setPixmap(pixmap);
}

////--------------------------------------------------心跳包操作模块---------------------------------------------------------
/*  初始化心跳包
*/
void CommunitySecurityClient::handle_InitHeartBea()
{
    heartbea_Obj.start(4000);  //启动定时器
    //定时发起连接
    connect(&heartbea_Obj,&QTimer::timeout,this,&CommunitySecurityClient::handle_TcpConnect);
}

/*  发起TCP连接
*/
void CommunitySecurityClient::handle_TcpConnect()
{
    tcpSocket_Obj.connectToHost("127.0.0.1",13020); //连接服务器
}

/*  暂停心跳包
*/
void CommunitySecurityClient::handle_StopHeartBea()
{
    qDebug() << "链接服务器成功";
    heartbea_Obj.stop();  //暂停定时器
}

/*  启动心跳包
*/
void CommunitySecurityClient::handle_StateHeartBea()
{
    qDebug() << "服务器断开";
    heartbea_Obj.start(4000);  //启动定时器
}

////--------------------------------------------------TCP操作模块---------------------------------------------------------
/*  初始化TCP链接槽函数
*/
void CommunitySecurityClient::handle_InitTcpConnect()
{
    //TCP连接成功操作
    connect(&tcpSocket_Obj,&QTcpSocket::connected,this,&CommunitySecurityClient::handle_StopHeartBea);
    //TCP连接断开操作
    connect(&tcpSocket_Obj,&QTcpSocket::disconnected,this,&CommunitySecurityClient::handle_StateHeartBea);
    //接送服务器数据操作
    connect(&tcpSocket_Obj,&QTcpSocket::readyRead,this,&CommunitySecurityClient::handle_ReadyDatainServer);
}

/*  处理服务器发送的数据
*/
void CommunitySecurityClient::handle_ReadyDatainServer()
{
    QString str = tcpSocket_Obj.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(str.toUtf8());
    QJsonObject jsonObj = jsonDoc.object(); //从JSON文档中获取JSON对象

    ui->numbe_Show->setText(jsonObj.value("ID").toString());
    ui->name_Show->setText(jsonObj.value("name").toString());
    ui->date_Show->setText(jsonObj.value("time").toString());
}

/*  发送数据至服务器
 *  data：发送的数据
*/
void CommunitySecurityClient::handle_SendingDatainServer(QByteArray data)
{
    quint64 dataSize = data.size();
    QByteArray sendingData;
    QDataStream stream(&sendingData,QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_14);    //设置数据流的版本
    stream << dataSize << data;
    tcpSocket_Obj.write(sendingData);
    faceFlag_Obj = -2;
}





