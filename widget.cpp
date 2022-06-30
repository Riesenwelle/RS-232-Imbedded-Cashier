#include "widget.h"
#include "ui_widget.h"

//#define PORT "/dev/ttyS3"

QStandardItemModel* modelw = new QStandardItemModel(); // 创建数据模型
extern QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); // 数据库全局变量
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //this->setFixedSize(this>width(),this->height());
    this->setAttribute(Qt::WA_StyledBackground, true); // 使继承QWidget仍能使样式表背景图生效

    // connect函数格式：发出信号的页面，信号，接受信号的页面（槽的所在），槽与槽函数
    connect(iomPage,SIGNAL(signaliomb()),this,SLOT(backfromiom()));
    connect(inmPage,SIGNAL(signalinmb()),this,SLOT(backfrominm()));


    // SQLite数据库连接s
    db.setDatabaseName("SQLITE.db"); // 数据库文件名
    db.setUserName("root"); // 设置用户名
    db.setPassword("123456"); // 设置密码

    qDebug()<<db.driverName();
    qDebug()<<db.databaseName();
    qDebug()<<db.password();

    bool ok = db.open(); // 打开数据库文件
    if (ok)
    {
        ui->lbHint->setText("数据库打开成功！");
        qDebug() << QString("Database open succeeded!");
    }
    else
    {
        ui->lbHint->setText("数据库打开失败！");
        qDebug() << "Database open failed!";
    }

    // 初始化数据库
    QString opt;
    opt = "CREATE TABLE good(gid varchar(40) PRIMARY KEY NOT NULL,gname varchar(40),gprice int,gnum int);";
    db.exec(opt);
    opt = "CREATE TABLE goodtemp(gtid varchar(40) PRIMARY KEY NOT NULL,gtname varchar(40),gtprice int,gtnum int);";
    db.exec(opt);

    /*
    // auto-insert sample-items for SQL-test
    opt = "INSERT INTO good VALUES('277325073','ibm',483,100);";
    db.exec(opt);
    opt = "INSERT INTO good VALUES('433443','sun',400,200);";
    db.exec(opt);
    */
}

Widget::~Widget()
{
    delete ui;
}

// 跳转到出入库页面
void Widget::on_pbIOManager_clicked()
{
    iomPage->show();
    this->hide();
}

// 跳转到商品信息管理页面
void Widget::on_pbInfoManager_clicked()
{
    inmPage->show();
    this->hide();
}

// 从出入库页面返回
void Widget::backfromiom()
{
    this->show();
    iomPage->close();
}

// 从商品信息管理页面返回
void Widget::backfrominm()
{
    this->show();
    inmPage->close();
}

// quit
void Widget::on_pbQuit_clicked()
{
    qApp->quit();
}
