#ifndef DETECTION_H
#define DETECTION_H

#include <QObject>
#include <opencv.hpp>
#include <seeta/FaceEngine.h>

//检测模块
class Detection : public QObject
{
    Q_OBJECT
public:
    explicit Detection(QObject *parent = nullptr);
    ~Detection();

public slots:
    //用户注册
    int64_t handle_UserRegister(cv::Mat& imgdata);
    //查询用户信息
    void handle_SeleteUserData(cv::Mat& imgdata);
signals:
    //返回检测到的人脸ID
    void return_QueryFaceId(int64_t id);

signals:

private:
    seeta::FaceEngine* faceEngine_Obj;

};

#endif // DETECTION_H
