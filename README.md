# CommunitySecurityProject - By Wild_Pointer

<p align="center">
  <img src ="README_IMG\logo.png"/>
</p>

<p align="center">
    <img src ="https://img.shields.io/badge/version-1.0.0.1-purple"/>
    <img src ="https://img.shields.io/badge/platform-Linux-yellow"/>
    <img src ="https://img.shields.io/badge/C%2B%2B-11-blue" />
    <img src ="https://img.shields.io/badge/framework-Qt5.14-orange"/>
    <img src ="https://img.shields.io/badge/build-Wild_Pointer-orange"/>
</p>

CommunitySecurityProject是一套基于OpenCV的社区安防系统，旨在通过开源的方式，帮助更多人了解社区安防系统，帮助更多人了解社区安防系统的实现原理，帮助更多人了解社区安防系统的应用场景。

**源码可自由下载使用，更多信息参考[个人博客](wild-pointer.top)**：


在使用CommunitySecurityProject进行二次开发（策略、模块等）的过程中有任何疑问，可通过[**QQ邮箱**](3020922258@qq.com)或者[**谷歌邮箱**](wildpointer794@gmail.com)，也欢迎在分享你的使用心得或者使用中产生的bug，方便作者后续更新迭代！


## CommunitySecurityProject介绍

社区安防系统（CommunitySecurityProject）是一个创新的、响应迅速的安全解决方案，专为社区环境量身定制。它利用OpenCV的前沿技术，如人脸识别，通过直观的接口与用户需求紧密结合。系统核心包括用户注册和人脸检测功能，旨在快速实现个性化安全应用的构建。

系统采用成熟的客户端/服务器架构，保障了应用的稳健运行和未来的扩展潜力。数据存储采用SqlLite数据库，确保数据的安全性和高效的数据管理。客户端之间的通信通过JSON格式进行，这种格式不仅简洁，而且提高了信息交换的效率。同时，系统利用TCP协议确保数据传输的可靠性和稳定性，为社区安防提供了坚实的技术支撑。

1. 项目技术栈：

    * 数据库

        * SqlLite

    * 技术栈
        * C++11

        * Qt5

        * 多线程

        * TCP协议

        * OpenCV

        * JSON格式
2. 模块设计概述：
    * 数据传输：
        * 通过QTcpSocket使用TCP协议对客户端与服务端之间的数据进行传输，并且使用JSON格式对传递的数据进行格式化操作。
    * 线程模块：
        * 针对CommunitySecurityProject项目，作者采用QThread模块，在服务端定义了多线程模块。更快的处理人脸数据的捕获以及检测功能
    * 检测模块：
        * 作者使用了OpenCV自带的特征分类器对摄像头捕获的对象进行检测，检测人脸的物体上传至服务器识别
    * 网络模块：
        * 通过定义定时器对象，为客户端定义了心跳包，防止网络等原因导致与服务端失去连接
    * 识别模块：
        * 通过调用开源识别模型SeetaFace，加载级联分类器后，对客户端上传的图片进行识别


## 环境准备

* 推荐使用Qt5.14版本进行部署
* 支持的数据库版本：SqlLite
* 支持的系统版本：Ubuntu
* 支持的C++版本：C++ 11/64位（**推荐使用C++ 11**）

## Qt模块准备

下载源码后，需要在Pro文件导入以下模块：

```
sql
```
```
network
```

**注意：源码中的Pro文件以及列举了Qt6所需的所有模块**

## 代码示例

CommunitySecurityProject采用了统一的命名和注释格式，具体可参考以下代码：

```C++
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
```
其中函数命名使用驼峰法，并且注释中带有函数参数以及默认返回值int，方便后续对异常的捕获进行诊断


## 运行示例
<p align="center">
    <img src ="README_IMG\1.gif"/>
</p>


## 作者留言
个人博客：wild-pointer.top

通过QQ邮箱联系我：3020922258@qq.com 

通过谷歌邮箱联系我：wildpointer794@gmail.com