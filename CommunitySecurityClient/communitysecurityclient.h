#ifndef COMMUNITYSECURITYCLIENT_H
#define COMMUNITYSECURITYCLIENT_H

#include <QTimer>
#include <QTcpSocket>
#include <opencv.hpp>
#include <QMainWindow>
#include <QJsonObject>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE

using namespace cv;
using namespace std;
namespace Ui { class CommunitySecurityClient; }
QT_END_NAMESPACE

class CommunitySecurityClient : public QMainWindow
{
    Q_OBJECT

public:
    CommunitySecurityClient(QWidget *parent = nullptr);
    ~CommunitySecurityClient();
////--------------------------------------------------摄像头操作模块--------------------------------------------------------
public:
    //初始化摄像头对象
    void handle_InitCamera();
////--------------------------------------------------级联分类器操作模块-----------------------------------------------------
public:
    //初始化级联分类器对象
    void handle_InitClassifier();
    //人脸检测
    void handle_FaceDetection(Mat& image);
    //将Mat类型数据转化为Jpg存储
    void handle_MatConvertInJpg(const Mat& image);
////--------------------------------------------------定时器操作模块---------------------------------------------------------
protected:
    //定时器事件
    void timerEvent(QTimerEvent *event);
////--------------------------------------------------心跳包操作模块---------------------------------------------------------
public:
    //初始化心跳包
    void handle_InitHeartBea();
private slots:
    //发起TCP连接
    void handle_TcpConnect();
    //暂停心跳包
    void handle_StopHeartBea();
    //启动心跳包
    void handle_StateHeartBea();
////--------------------------------------------------TCP操作模块---------------------------------------------------------
public:
    //初始化TCP链接槽函数
    void handle_InitTcpConnect();
    //处理服务器发送的数据
    void handle_ReadyDatainServer();
    //发送数据至服务器
    void handle_SendingDatainServer(QByteArray data);

private:
    Ui::CommunitySecurityClient *ui;
    int faceFlag_Obj;   //人脸标志位（判断是否为同一个人）
    QTimer heartbea_Obj;        //心跳包对象
    QTcpSocket tcpSocket_Obj;   //TCP连接对象
    VideoCapture Capture_Obj;   //摄像头对象
    CascadeClassifier classifier_Obj;//级联分类器对象

};
#endif // COMMUNITYSECURITYCLIENT_H
