#include "detection.h"
#include <QDebug>

Detection::Detection(QObject *parent) : QObject(parent)
{
    seeta::ModelSetting fd_Model("../CommunitySecurityServer/model/fd_2_00.dat",seeta::ModelSetting::CPU,0);
    seeta::ModelSetting fr_Model("../CommunitySecurityServer/model/fr_2_10.dat",seeta::ModelSetting::CPU,0);
    seeta::ModelSetting pd_Model("../CommunitySecurityServer/model/pd_2_00_pts5.dat",seeta::ModelSetting::CPU,0);
    faceEngine_Obj = new seeta::FaceEngine(fd_Model,pd_Model,fr_Model);
    faceEngine_Obj->Load("./facedata.db");
}

Detection::~Detection()
{
    delete faceEngine_Obj;
}

/*  用户注册
 *  imgdata：注册的图像数据
 *  返回值：int64_t（用户ID）
*/
int64_t Detection::handle_UserRegister(cv::Mat &imgdata)
{
    //将Mat数据转换为SeeraFace数据
    SeetaImageData faceImg;
    faceImg.data = imgdata.data;
    faceImg.width = imgdata.cols;
    faceImg.height = imgdata.rows;
    faceImg.channels = imgdata.channels();
    int64_t id = faceEngine_Obj->Register(faceImg);
    if(id >= 0){
        faceEngine_Obj->Save("./facedata.db");
    }
    return id;
}

/*  查询用户信息
 *  imgdata：图像数据
 *  返回值：int（用户ID）
*/
void Detection::handle_SeleteUserData(cv::Mat& imgdata)
{
    //将Mat数据转换为SeeraFace数据
    SeetaImageData faceImg;
    faceImg.data = imgdata.data;
    faceImg.width = imgdata.cols;
    faceImg.height = imgdata.rows;
    faceImg.channels = imgdata.channels();
    float similarity = 0;
    int64_t faceId = faceEngine_Obj->Query(faceImg,&similarity);
    if(similarity > 0.7){  //查询到对应的用户信息
        emit return_QueryFaceId(faceId);
    }else{                //未查询到信息
        emit return_QueryFaceId(-1);
    }
}
