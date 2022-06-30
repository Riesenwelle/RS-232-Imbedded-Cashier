#include "iomanager.h"
#include "ui_iomanager.h"

QStandardItemModel* modeliom = new QStandardItemModel(); // 创建数据模型
extern QSqlDatabase db; // 数据库全局变量

IOManager::IOManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IOManager)
{
    ui->setupUi(this);
    //this->setFixedSize(this->width(),this->height());
    this->setAttribute(Qt::WA_StyledBackground, true); // 使继承QWidget仍能使样式表背景图生效

    ui->tv->clearSpans();
    modeliom->clear();
    // 设置表格标题行(输入数据为QStringList类型)
    QStringList qsltemp;
    qsltemp << "扫描ID" << "货物名称" << "货物价格" << "库存数量";
    modeliom->setHorizontalHeaderLabels({qsltemp});
    ui->tv->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tv->setModel(modeliom);
    //on_pbConnect_clicked();

    isin = 0;
    isConnected = 0;
    isSelected = 0;
}

IOManager::~IOManager()
{
    delete ui;
}

// 刷新
void IOManager::refresh()
{
    QString sear;
    ui->tv->clearSpans();
    modeliom->clear();
    // 设置表格标题行(输入数据为QStringList类型)
    QStringList qsltemp;
    qsltemp << "扫描ID" << "货物名称" << "货物价格" << "变更数量";
    modeliom->setHorizontalHeaderLabels({qsltemp});
    ui->tv->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    sear = "SELECT * FROM goodtemp;"; // 查询语句，需要表明变量的具体模式
    QSqlQuery query = db.exec(sear); // 获取查询结果集，存入query

    int queSize = 0;
    if (query.last()) // 获取结果集大小
        queSize = query.at() + 1;
    query.first(); // 重新定位指针到结果集首位
    query.previous(); // 如果执行query.next来获取结果集中数据，要将指针移动到首位的上一位

    // 加载queSize行数据，每行有4列数据
    for (int i = 0; i < queSize; i++)
    {
        // 跳出
        if(!query.next())
            break;
        for(int j = 0; j < 4; j++)
            modeliom->setItem(i, j, new QStandardItem(query.value(j).toString()));
    }
    ui->tv->setModel(modeliom); // 设置表格视图数据
    isSelected = 0;
    calPrice();
}

// 跳转回首页
void IOManager::on_pbBack_clicked()
{
    emit signaliomb();
}

// IO pd
void IOManager::on_rbisin_clicked(bool checked)
{
    if(checked)
        isin = 1;
    else isin = 0;
}

// connect ttyS3
// create sub-thread to receive from ttyS3
void IOManager::on_pbConnect_clicked()
{
    if(isConnected == 1)
    {
        isConnected = 0;
        thread1->terminate();

        ui->rbisin->setEnabled(1);
        refresh();
        qDebug() << "Connection:" << isConnected;
    }
    else
    {
        //执行线程
        isConnected = 1;
        thread1  = new UartThread();
        thread1->start();

        // 通过信号与槽在两个线程中传递参数
        // connect函数格式：发出信号的页面，信号，接受信号的页面（槽的所在），槽与槽函数
        connect(thread1, SIGNAL(ttySendData(QString)), this, SLOT(ttyGetData(QString)));

        ui->rbisin->setEnabled(0);
        refresh();
        qDebug() << "Connection:" << isConnected;
    }
}

// 清除输入
void IOManager::on_pbClean_clicked()
{
    ui->leChange->setText("");
}

// 删除选中
void IOManager::on_pbDele_clicked()
{
    if(isSelected == 0)
    {
        ui->lbHint->setText("Please select first!");
    }
    else
    {
        QString opt = "DELETE FROM goodtemp WHERE gtid = " + gtid + ";";
        db.exec(opt);
        isSelected = 0;
        ui->lbHint->setText("Delete complete");
    }
    refresh();
}

/*
    · 出入库判断使用radioButton，选中为入库，否则为出库；

    · 出库（结账）：
        · 先扫码得到id，若id匹配不上现有任何id，则新建一个gtid外其他项为默认的商品记录,
            在仓库表里新增该数据元素；
        · 若匹配上现有id，则在tableView中显示该id对应good表内的数据项；
        · 实验箱按键输入变更数量，默认为1；
        · 按确认键提交变更到good表。

    · 入库：
        · 先扫码得到id，若id匹配不上现有任何id，则新建一个gtid外其他项为默认的商品记录,
            在仓库表里新增该数据元素；
        · 若匹配上现有id，则在tableView中显示该id对应good表内的数据项；
        · 实验箱按键输入变更数量，默认为1；
        · 按确认键提交变更到good表。
*/

void IOManager::ttyGetData(QString ttyData)
{
    bool pp = 0; // 匹配
    gtid = ttyData.simplified(); // remove \n, also keep its structure
    qDebug() << "iom receive and fix:" << gtid;

    // id匹配, SQL search DB
    QString opt = "SELECT * FROM good;";
    QSqlQuery query = db.exec(opt);

    int queSize = 0;
    if (query.last()) // 获取结果集大小
        queSize = query.at() + 1;
    query.first(); // 重新定位指针到结果集首位
    query.previous(); // 如果执行query.next来获取结果集中数据，要将指针移动到首位的上一位

    // 加载queSize行数据
    for (int i = 0; i < queSize; i++)
    {
        // 跳出
        if(!query.next())
            break;
        // 匹配上现有id
        if(query.value(0) == gtid)
        {;
            gtname = query.value(1).toString();
            gtprice = query.value(2).toString();
            gtnum = query.value(3).toString();
            // 尝试新增, gtnum=0
            opt = "INSERT INTO goodtemp VALUES ('" + gtid + "','" + gtname + "'," + gtprice + ", 0);";
            db.exec(opt);
            // 扫一次则gtnum+1
            opt = "UPDATE goodtemp SET gtnum = gtnum + 1 WHERE gtid = '" + gtid + "';";
            db.exec(opt);
            pp = 1;
            break;
        }
    }
    // 匹配不上现有任何id
    if(pp == 0)
    {
        // 出库, output error hint
        if(isin == 0)
        {
            qDebug() << "ERR: ID not exist in storage!";
        }
        //入库,新建一个gtid外其他项为默认的商品记录
        else
        {
            QString opt = "INSERT INTO goodtemp VALUES ('" + gtid + "','default',0,0);";
            db.exec(opt);
        }
    }
    refresh();
}

// click to choose (x,0) & get selected_gtid/gtname/gtprice/gtnum
void IOManager::on_tv_clicked(const QModelIndex &index)
{
    QAbstractItemModel *Imodel = ui->tv->model();
    QModelIndex indexTemp;
    // index.row()为所选择的行号, index.column() in the same way
    indexTemp = Imodel->index(index.row(),0);
    selected_gtid = Imodel->data(indexTemp).toString();
    indexTemp = Imodel->index(index.row(),1);
    selected_gtname = Imodel->data(indexTemp).toString();
    indexTemp = Imodel->index(index.row(),2);
    selected_gtprice = Imodel->data(indexTemp).toString();
    indexTemp = Imodel->index(index.row(),3);
    selected_gtnum = Imodel->data(indexTemp).toString();
    isSelected = 1;
}

// num -= 1
void IOManager::on_pbkeyDown_clicked()
{
    QString opt;
    QSqlQuery query;
    opt = "SELECT gtnum FROM goodtemp WHERE gtid = '"+ gtid +"';";
    query = db.exec(opt);
    query.first();
    if(query.value(0).toInt()<=0)
        ui->lbHint->setText("Cannot decrease number below 0!");
    else
    {
        opt = "UPDATE goodtemp SET gtnum = gtnum - 1 WHERE gtid = '" + selected_gtid + "';";
        db.exec(opt);
        refresh();
    }
}

// num += 1
void IOManager::on_pbkeyUp_clicked()
{
    QString opt = "UPDATE goodtemp SET gtnum = gtnum + 1 WHERE gtid = '" + selected_gtid + "';";
    db.exec(opt);
    refresh();
}

// input 0
void IOManager::on_pbkey0_clicked()
{
    qschange = ui->leChange->text();
    qschange += "0";
    ui->leChange->setText(qschange);
}

// 替换数量
void IOManager::on_pbChangeNum_clicked()
{
    QString numTemp = ui->leChange->text();
    if(numTemp < 0)
        ui->lbHint->setText("Cannot set number below 0!");
    else
    {
        QString opt = "UPDATE goodtemp SET gtnum = " + numTemp + " WHERE gtid = '" + selected_gtid + "';";
        db.exec(opt);
        refresh();
    }
}

// submit goodtemp to good
/*
入库：
· 对已存在的商品：根据gtnum改变其gnum;
· 对不存在的商品：创建新商品，设置gname=default, gprice=0, gnum=gtnum.
出库：
· 对已存在的商品：根据gtnum改变其gnum;
· 对不存在的商品：不存在可能性.
*/
void IOManager::on_pbSubmit_clicked()
{
    QString opt = "SELECT * FROM goodtemp;";
    QSqlQuery query = db.exec(opt);

    int queSize = 0;
    if (query.last()) // 获取结果集大小
        queSize = query.at() + 1;
    query.first(); // 重新定位指针到结果集首位
    query.previous(); // 如果执行query.next来获取结果集中数据，要将指针移动到首位的上一位

    // 加载queSize行数据
    for (int i = 0; i < queSize; i++)
    {
        // 跳出
        if(!query.next())
            break;
        // get gtid,gtname,gtprice,gtnum & operate
        gtid = query.value(0).toString();
        gtname = query.value(1).toString();
        gtprice = query.value(2).toString();
        gtnum = query.value(3).toString();
        // in
        if(isin == 1)
        {
            opt = "INSERT INTO good VALUES ('" + gtid + "','default',0," + gtnum + ");";
            db.exec(opt);
            opt = "UPDATE good SET gnum = gnum + " + gtnum + " WHERE gid = '" + gtid + "';";
            db.exec(opt);
        }
        // out
        else
        {
            opt = "SELECT gnum FROM good WHERE gid = '" + gtid + "';";
            QSqlQuery query2 = db.exec(opt);
            query2.first();

            // 判断是否超出库存
            int numCompare = (query2.value(0).toInt()) - gtnum.toInt();
            if(numCompare<0)
            {
                ui->lbHint->setText("ERR: not enough goods for" + gtid + "!");
                qDebug() << "ERR: not enough goods for" << gtid << "!";
                continue;
            }

            opt = "UPDATE good SET gnum = gnum - " + gtnum + " WHERE gid = '" + gtid + "';";
            db.exec(opt);
        }
    }

    // recreate table goodtemp & refresh
    opt = "DROP TABLE goodtemp;";
    db.exec(opt);
    opt = "CREATE TABLE goodtemp(gtid varchar(40) PRIMARY KEY NOT NULL,gtname varchar(40),gtprice int,gtnum int);";
    db.exec(opt);
    refresh();
}

// 计算goodtemp总价格
void IOManager::calPrice()
{
    QString opt = "SELECT gtprice,gtnum FROM goodtemp;";
    QSqlQuery query = db.exec(opt);
    int sum = 0;
    int sumTemp;
    QString qssumTemp;

    int queSize = 0;
    if (query.last()) // 获取结果集大小
        queSize = query.at() + 1;
    query.first(); // 重新定位指针到结果集首位
    query.previous(); // 如果执行query.next来获取结果集中数据，要将指针移动到首位的上一位

    // 加载queSize行数据
    for (int i = 0; i < queSize; i++)
    {
        // 跳出
        if(!query.next())
            break;
        sumTemp = (query.value(0).toInt()) * (query.value(1).toInt()); // get gtprice , price x num
        qssumTemp = QString::number(sumTemp);
        qDebug() << qssumTemp;
        // 累加计算goodtemp总价格
        sum += sumTemp;
    }
    qDebug() << sum;
    ui->lbSum->setText("总计金额：" + QString::number(sum));
}

// backspace
void IOManager::on_pbkeyBS_clicked()
{
    qschange = ui->leChange->text();
    if(qschange != NULL)
    {
        qschange.chop(1);
        ui->leChange->setText(qschange);
    }
}
