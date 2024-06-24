#include "sql.h"

#include <QDebug>

sql::sql(QObject *parent) : QObject(parent)
{
    handle_InitSqlDataBase();    //初始化数据库
    handle_CreateUserInfoTable();//创建员工信息表
    handle_CreateAttendanceInfoTable(); //创建考勤表
}

sql::~sql()
{

}

/*  初始化数据库
*/
void sql::handle_InitSqlDataBase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("server.db");
    if(!db.open()){ //数据库打开失败
        qDebug() << db.lastError().text();
        return;
    }
}

/*  创建员工信息表
*/
void sql::handle_CreateUserInfoTable()
{
    QString sqlCode = "create table if not exists UserInfo("
                      " ID integer primary key autoincrement,"
                      " name varchar(256),"
                      " sex varchar(32),"
                      " birthday text,"
                      " address text,"
                      " phone text,"
                      " faceID integer unique,"
                      " headfile text);";

    QSqlQuery query;
    if(!query.exec(sqlCode)){
        QMessageBox::warning(nullptr, "警告", query.lastError().text(), QMessageBox::Ok);
        return;
    }
}

/*  创建考勤信息表
*/
void sql::handle_CreateAttendanceInfoTable()
{
    QString sqlCode = "create table if not exists AttendanceInfo("
                      " attendaceID integer primary key autoincrement,"
                      " employeeID integer,"
                      " attendaceTime TimeStamp NOT NULL DEFAULT CURRENT_TIMESTAMP);";
    QSqlQuery query;
    if(!query.exec(sqlCode)){
        QMessageBox::warning(nullptr, "警告", query.lastError().text(), QMessageBox::Ok);
        return;
    }
}

/*  插入考勤信息
 *  sqlCode：执行的Sql语句
*/
bool sql::handle_InsertAttendanceInfo(QString sqlCode)
{
    QSqlQuery query;
    if(!query.exec(sqlCode)){
        QString str = QString("考勤信息插入失败：%1").arg(query.lastError().text());
        QMessageBox::warning(nullptr, "警告", str, QMessageBox::Ok);
        return false;
    }else{
        return true;
    }
}

/*  添加用户信息
 *  sqlCode：执行的Sql语句
*/
void sql::handle_AddUserInfo(QString sqlCode)
{
    QSqlQuery query;
    if(!query.exec(sqlCode)){
        QString str = QString("添加信息失败：%1").arg(query.lastError().text());
        QMessageBox::warning(nullptr, "警告", str, QMessageBox::Ok);
        return;
    }else{
        QMessageBox::information(nullptr,"提示","添加用户信息成功！！！",QMessageBox::Ok);
    }
}
