#include "infomanager.h"
#include "ui_infomanager.h"

QStandardItemModel* modelinm = new QStandardItemModel(); // 创建数据模型
extern QSqlDatabase db; // 数据库全局变量

InfoManager::InfoManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoManager)
{
    ui->setupUi(this);
    //this->setFixedSize(this->width(),this->height());
    this->setAttribute(Qt::WA_StyledBackground, true); // 使继承QWidget仍能使样式表背景图生效

    ui->tv->clearSpans();
    modelinm->clear();
    // 设置表格标题行(输入数据为QStringList类型)
    QStringList qsltemp;
    qsltemp << "扫描ID" << "货物名称" << "货物价格" << "库存数量";
    modelinm->setHorizontalHeaderLabels({qsltemp});
    ui->tv->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tv->setModel(modelinm);

    refresh();
}

InfoManager::~InfoManager()
{
    delete ui;
}

// 跳转回首页
void InfoManager::on_pbBack_clicked()
{
    emit signalinmb();
}

// 刷新
void InfoManager::refresh()
{
    QString sear;
    ui->tv->clearSpans();
    modelinm->clear();
    // 设置表格标题行(输入数据为QStringList类型)
    QStringList qsltemp;
    qsltemp << "扫描ID" << "货物名称" << "货物价格" << "库存数量";
    modelinm->setHorizontalHeaderLabels({qsltemp});
    ui->tv->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    sear = "SELECT * FROM good ;"; // 查询语句，需要表明变量的具体模式
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
            modelinm->setItem(i, j, new QStandardItem(query.value(j).toString()));
    }
    ui->tv->setModel(modelinm); // 设置表格视图数据
    isSelected = 0;
}

// use lineEdit to change item in database
void InfoManager::on_pbSubmit_clicked()
{
    QString qschange;
    qschange = ui->leChange->text();
    QString opt1 = "UPDATE good SET ";
    QString opt2;
    switch(selectedColumn)
    {
    case 0:
        ui->lbHint->setText("Cannot convert PK gid!");
        return;
    case 1:
        opt2 = "gname = '" + qschange + "' ";
        break;
    case 2:
        opt2 = "gprice = " + qschange + " ";
        break;
    case 3:
        opt2 = "gnum = " + qschange + " ";
        break;
    }

    QString opt3 = "WHERE gid = " + gid + ";";
    db.exec(opt1+opt2+opt3);
    refresh();
}

// click to choose (x,y) & get gid
void InfoManager::on_tv_clicked(const QModelIndex &index)
{
    QAbstractItemModel *Imodel = ui->tv->model();
    QModelIndex indexTemp = Imodel->index(index.row(),0); // index.row()为所选择的行号, index.column() in the same way

    // gid : 0, gname : 1, gprice : 2, gnum : 3
    switch(index.column())
    {
    case 0:
        selectedColumn = 0;
        break;
    case 1:
        selectedColumn = 1;
        break;
    case 2:
        selectedColumn = 2;
        break;
    case 3:
        selectedColumn = 3;
        break;
    default:
        break;
    }

    gid = Imodel->data(indexTemp).toString();
    isSelected = 1;
}

// delete selected item from database
void InfoManager::on_pbDele_clicked()
{
    if(isSelected == 0)
    {
        ui->lbHint->setText("Please select first!");
    }
    else
    {
        QString opt = "DELETE FROM good WHERE gid = " + gid + ";";
        db.exec(opt);
        isSelected = 0;
        ui->lbHint->setText("Delete complete");
    }
    refresh();
}

// Clean lineEdit
void InfoManager::on_pbClean_clicked()
{
    ui->leChange->setText("");
}

// refresh
void InfoManager::on_pbRefr_clicked()
{
    refresh();
    ui->lbHint->setText("刷新成功.");
}

// a-z, simple soft-keyboard
void InfoManager::on_pbkeya_clicked()
{
    qschange = ui->leChange->text();
    qschange += "a";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyb_clicked()
{
    qschange = ui->leChange->text();
    qschange += "b";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyc_clicked()
{
    qschange = ui->leChange->text();
    qschange += "c";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyd_clicked()
{
    qschange = ui->leChange->text();
    qschange += "d";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeye_clicked()
{
    qschange = ui->leChange->text();
    qschange += "e";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyf_clicked()
{
    qschange = ui->leChange->text();
    qschange += "f";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyg_clicked()
{
    qschange = ui->leChange->text();
    qschange += "g";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyh_clicked()
{
    qschange = ui->leChange->text();
    qschange += "h";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyi_clicked()
{
    qschange = ui->leChange->text();
    qschange += "i";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyj_clicked()
{
    qschange = ui->leChange->text();
    qschange += "j";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyk_clicked()
{
    qschange = ui->leChange->text();
    qschange += "k";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyl_clicked()
{
    qschange = ui->leChange->text();
    qschange += "l";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeym_clicked()
{
    qschange = ui->leChange->text();
    qschange += "m";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyn_clicked()
{
    qschange = ui->leChange->text();
    qschange += "n";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyo_clicked()
{
    qschange = ui->leChange->text();
    qschange += "o";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyp_clicked()
{
    qschange = ui->leChange->text();
    qschange += "p";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyq_clicked()
{
    qschange = ui->leChange->text();
    qschange += "q";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyr_clicked()
{
    qschange = ui->leChange->text();
    qschange += "r";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeys_clicked()
{
    qschange = ui->leChange->text();
    qschange += "s";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyt_clicked()
{
    qschange = ui->leChange->text();
    qschange += "t";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyu_clicked()
{
    qschange = ui->leChange->text();
    qschange += "u";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyv_clicked()
{
    qschange = ui->leChange->text();
    qschange += "v";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyw_clicked()
{
    qschange = ui->leChange->text();
    qschange += "w";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyx_clicked()
{
    qschange = ui->leChange->text();
    qschange += "x";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyy_clicked()
{
    qschange = ui->leChange->text();
    qschange += "y";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkeyz_clicked()
{
    qschange = ui->leChange->text();
    qschange += "z";
    ui->leChange->setText(qschange);
}

void InfoManager::on_pbkey0_clicked()
{
    qschange = ui->leChange->text();
    qschange += "0";
    ui->leChange->setText(qschange);
}

// backspace
void InfoManager::on_pbkeyBS_clicked()
{
    qschange = ui->leChange->text();
    if(qschange != NULL)
    {
        qschange.chop(1);
        ui->leChange->setText(qschange);
    }
}
