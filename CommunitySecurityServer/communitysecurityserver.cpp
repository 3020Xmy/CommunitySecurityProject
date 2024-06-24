#include "communitysecurityserver.h"
#include "ui_communitysecurityserver.h"

CommunitySecurityServer::CommunitySecurityServer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CommunitySecurityServer)
{
    ui->setupUi(this);

    data_Size = 0;
    register_Obj = nullptr;
    sqlTable_Obj.setTable("UserInfo");   //绑定表格

    handle_InitThread();    //初始化线程
    handle_InitTcpServer(); //初始化TcpServer
}

CommunitySecurityServer::~CommunitySecurityServer()
{
    delete ui;
}

////--------------------------------------------------线程操作模块--------------------------------------------------------
/*  初始化线程
*/
void CommunitySecurityServer::handle_InitThread()
{
    QThread* thread_Obj = new QThread();
    //将检测操作放到线程中处理
    faceDetection_Obj.moveToThread(thread_Obj);
    thread_Obj->start();    //启动线程
    connect(this,&CommunitySecurityServer::request_QueryInfo,&faceDetection_Obj,&Detection::handle_SeleteUserData);
    connect(&faceDetection_Obj,&Detection::return_QueryFaceId,this,&CommunitySecurityServer::handle_QueryFaceInfo);
}

////--------------------------------------------------识别操作模块--------------------------------------------------------
/*  请求数据库查询制定的个人信息
 *  faceId：人脸ID
*/
void CommunitySecurityServer::handle_QueryFaceInfo(int64_t faceId)
{
    QString str = "";
    if(faceId < 0){
        str = QString("{\"employeeID\":,\"name\":,\"department\":,\"time\":}");
        client_Obj->write(str.toUtf8());
        return;
    }
    //设置过滤器
    sqlTable_Obj.setFilter(QString("faceID=%1").arg(faceId));

    //查询数据
    sqlTable_Obj.select();
    if(sqlTable_Obj.rowCount() == 1){   //查询到数据
        QSqlRecord record = sqlTable_Obj.record(0);
        str = QString("{\"ID\":\"%1\",\"name\":\"%2\",\"department\":\"软件\",\"time\":\"%3\"}")
              .arg(record.value("ID").toString()).arg(record.value("name").toString())
              .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh::mm::ss"));
        QString sqlCode = QString("INSERT INTO AttendanceInfo (employeeID) VALUES ('%1');")
                          .arg(record.value("ID").toString());
        if(sql_Obj.handle_InsertAttendanceInfo(sqlCode)){   //插入考勤信息
            client_Obj->write(str.toUtf8());    //发送数据至客户端
        }
    }

}

/*  识别人脸
 *  data：接收到的数据
 *  返回值：int（用户ID）
*/
void CommunitySecurityServer::handle_IdentifyFace(QByteArray data)
{
    cv::Mat readImg;    //接收到的图像数据
    std::vector<uchar> decode;
    decode.resize(data.size());
    memcpy(decode.data(),data.data(),data.size());

    //格式转换
    readImg = cv::imdecode(decode,cv::IMREAD_COLOR);
    emit request_QueryInfo(readImg);
}

////--------------------------------------------------TCP操作模块--------------------------------------------------------
/*  初始化TcpServer
*/
void CommunitySecurityServer::handle_InitTcpServer()
{
    //新的客户端连接操作
    connect(&server_Obj,&QTcpServer::newConnection,this,&CommunitySecurityServer::handle_NewClientConnect);

    server_Obj.listen(QHostAddress::Any,13020);
}

/*  新的客户端连接申请
*/
void CommunitySecurityServer::handle_NewClientConnect()
{
    //获取当前新的客户端连接套接字
    client_Obj = server_Obj.nextPendingConnection();
    //客户端发送数据操作
    connect(client_Obj,&QTcpSocket::readyRead,this,&CommunitySecurityServer::handle_ClientSendingData);

}

/*  处理客户端发送的数据
*/
void CommunitySecurityServer::handle_ClientSendingData()
{
    QDataStream stream(client_Obj); //绑定套接字到数据流中
    stream.setVersion(QDataStream::Qt_5_14);

    if(data_Size == 0){ //读取数据大小
        if(client_Obj->bytesAvailable() < (qint64)sizeof(data_Size)){   //读取的字节数小于8字节
            return;
        }
        stream >> data_Size;
    }else{
        if(client_Obj->bytesAvailable() < data_Size){   //图片数据未发送
            return;
        }
        //读取到图片数据
        QByteArray buffer;
        stream >> buffer;
        data_Size = 0;
        if(buffer.size() == 0){ //读取数据失败
            return;
        }
        handle_ShowReceiveImg(buffer); //显示接收到的图片
        handle_IdentifyFace(buffer);   //识别人脸
    }
}

/*  显示接收到的图片
 *  data：接收到的数据
*/
void CommunitySecurityServer::handle_ShowReceiveImg(const QByteArray &data)
{
    QPixmap pixmap;
    pixmap.loadFromData(data,"jpg");
    pixmap = pixmap.scaled(ui->show_Img->size());   //设置图像大小
    ui->show_Img->setPixmap(pixmap);
}

////--------------------------------------------------界面操作模块--------------------------------------------------------
/*  注册用户操作
*/
void CommunitySecurityServer::on_pushButton_clicked()
{
    if(register_Obj != nullptr){
        delete register_Obj;
        register_Obj = nullptr;
    }
    register_Obj = new registerWidget(nullptr);
    register_Obj->show();

    connect(register_Obj,&registerWidget::request_SqlSaveUserInfo,&sql_Obj,&sql::handle_AddUserInfo);
}

/*  查询数据操作
*/
void CommunitySecurityServer::on_pushButton_2_clicked()
{
    if(selete_Obj != nullptr){
        delete selete_Obj;
        selete_Obj = nullptr;
    }
    selete_Obj = new seleteWidget(nullptr);
    selete_Obj->show();
}
