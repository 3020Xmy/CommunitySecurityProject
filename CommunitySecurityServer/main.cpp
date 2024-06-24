#include "communitysecurityserver.h"

#include <opencv.hpp>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //注册自定义类型
    qRegisterMetaType<cv::Mat>("cv::Mat");
    qRegisterMetaType<cv::Mat>("cv::Mat&");
    qRegisterMetaType<int64_t>("int64_t");
    CommunitySecurityServer w;
    w.show();
    return a.exec();
}
