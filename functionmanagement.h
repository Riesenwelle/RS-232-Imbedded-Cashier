// Author: 2190400418 - xcj
// Refenrence Header Doc

/*
#ifndef FUNCTIONMANAGEMENT_H
#define FUNCTIONMANAGEMENT_H

#include <QMainWindow>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlError>
#include<QString>
#include<QDebug>

namespace Ui {
class FunctionManagement;
}

class FunctionManagement : public QMainWindow
{
    Q_OBJECT

public:
    explicit FunctionManagement(QWidget *parent = nullptr);
    ~FunctionManagement();
    void connectDatabase();
    void disconnectDatabase();
    void add();                 //商品入库
    void reduce();              //从数据库中减少出售的商品
    void estimate();            //计算总价格

private:
    Ui::FunctionManagement *ui;
    QSqlDatabase myDatabase;
    QString myDatabaseName;     //数据库名称
    QString userName;           //使用者名称
    QString userPassword;       //连接密码
    QString str_sql;            //执行语句
    QSqlQuery query;
    QString gid,gname;
    double gprice;
    int gnum;
    struct TotalPrice{
        double price;
        int num;
        struct TotalPrice *next;
    };
};

#endif // FUNCTIONMANAGEMENT_H
*/
