// Author: 2190400418 - xcj
// Refenrence Cpp Doc

/*
#include "functionmanagement.h"

#include <QString>

FunctionManagement::FunctionManagement(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FunctionManagement)
{
    ui->setupUi(this);
    connectDatabase();
}

FunctionManagement::~FunctionManagement()
{
    disconnectDatabase();
    delete ui;
}
void FunctionManagement::connectDatabase()
{
    myDatabase.addDatabase("QSQLLITE","first");
    myDatabase.setDatabaseName(myDatabaseName);
    myDatabase.setUserName(userName);
    myDatabase.setPassword(userPassword);
    if(!myDatabase.open()){
        qDebug() << "Error: Failed to connect database." << myDatabase.lastError();
    }
    else{
       qDebug()<<"connect sucess!"<<endl;
    }
}
void FunctionManagement::disconnectDatabase()
{
    myDatabase.close();
}

void FunctionManagement::add()          //商品入库
{
    //得到需要更改的商品的名称，数量
    //  名称      价格      数量
    //  good：仓库表，包含数据项：
    //  gid：扫描仪得到的ID；主码
    //  gname：货物名称
    //  gprice：货物价格
    //  gnum：货物库存数量

    //判断数据库中是否有该商品
    bool check=false;
    //int num=0;
    int addnum=0;                       //此次入库数量
    str_sql="select * from good";
    query.exec(str_sql);
    while(query.next()){
        if(query.value("gid").toString()==gid){
            check=true;
            gnum=query.value("gnum").toInt();
            break;
        }
    }
    if(check)                           //更改库中商品的数量
    {
        gnum=addnum+gnum;
        //QString s=QString::number(gnum);
        str_sql="updata good set gnum = "+QString::number(gnum)+" where gid = "+gid;
        query.exec(str_sql);
    }
    else{
        str_sql="insert into good values ( "+gid+","+gname+","+QString::number(gprice,'f',2)+","+QString::number(addnum)+" )";
        query.exec(str_sql);
    }
}

void FunctionManagement::reduce()       //商品出库
{
    int reducenum=0;
    str_sql="select * from good";
    query.exec(str_sql);
    while (query.next()) {
        if(query.value(gid).toString()==gid){
            gnum=query.value("gnum").toInt();
            break;
        }
    }
    gnum-=reducenum;
    //QString s=QString::number(gnum);
    str_sql="updata good set gnum = "+QString::number(gnum)+" where gid = "+gid;
}

void FunctionManagement::estimate()     //计算商品价格
{

}
*/
