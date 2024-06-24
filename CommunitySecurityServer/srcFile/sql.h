#ifndef SQL_H
#define SQL_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlDatabase>

class sql : public QObject
{
    Q_OBJECT
public:
    explicit sql(QObject *parent = nullptr);
    ~sql();

public:
    //初始化数据库
    void handle_InitSqlDataBase();
    //创建员工信息表
    void handle_CreateUserInfoTable();
    //创建考勤信息表
    void handle_CreateAttendanceInfoTable();
    //插入考勤信息
    bool handle_InsertAttendanceInfo(QString sqlCode);

public slots:
    //添加用户信息
    void handle_AddUserInfo(QString sqlCode);

private:

};

#endif // SQL_H
