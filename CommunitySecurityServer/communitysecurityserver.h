#ifndef COMMUNITYSECURITYSERVER_H
#define COMMUNITYSECURITYSERVER_H

#include <QThread>
#include <QDateTime>
#include <QTcpSocket>
#include <QTcpServer>
#include <QSqlRecord>
#include <QMainWindow>
#include "srcFile/sql.h"
#include <QSqlTableModel>
#include "srcFile/detection.h"
#include "uiFile/seletewidget.h"
#include "uiFile/registerwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CommunitySecurityServer; }
QT_END_NAMESPACE

class CommunitySecurityServer : public QMainWindow
{
    Q_OBJECT

public:
    CommunitySecurityServer(QWidget *parent = nullptr);
    ~CommunitySecurityServer();
////--------------------------------------------------线程操作模块--------------------------------------------------------
public:
    //初始化线程
    void handle_InitThread();
////--------------------------------------------------识别操作模块--------------------------------------------------------
public:
    //识别人脸
    void handle_IdentifyFace(QByteArray data);
public slots:
    //请求数据库查询制定的个人信息
    void handle_QueryFaceInfo(int64_t faceId);
signals:
    //请求识别模块查询信息
    void request_QueryInfo(cv::Mat& img);
    //请求数据库插入考勤信息
    void request_SqlInsertInfo(QString sqlCode);
////--------------------------------------------------TCP操作模块--------------------------------------------------------
public:
    //初始化TcpServer
    void handle_InitTcpServer();
    //处理客户端发送的数据
    void handle_ClientSendingData();
    //显示接收到的图片
    void handle_ShowReceiveImg(const QByteArray& data);
public slots:
    //新的客户端连接申请
    void handle_NewClientConnect();
////--------------------------------------------------界面操作模块--------------------------------------------------------
private slots:
    //注册用户操作
    void on_pushButton_clicked();
    //查询数据操作
    void on_pushButton_2_clicked();

private:
    Ui::CommunitySecurityServer *ui;
    sql sql_Obj;     //数据库对象
    qint64 data_Size;//读取到数据大小
    QTcpServer server_Obj;  //服务器对象
    QTcpSocket* client_Obj; //客户端对象
    seleteWidget* selete_Obj;       //查询窗口
    QSqlTableModel sqlTable_Obj;    //数据库表对象
    Detection faceDetection_Obj;    //人脸检测对象
    registerWidget* register_Obj;   //注册窗口
};
#endif // COMMUNITYSECURITYSERVER_H
