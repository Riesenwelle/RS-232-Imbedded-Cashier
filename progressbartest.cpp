#include "progressbartest.h"
#include "ui_progressbartest.h"

ProgressBarTest::ProgressBarTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgressBarTest)
{
    ui->setupUi(this);
    //this->setFixedSize(this->width(),this->height());
     progressBarValue = 50; // GUI test
}

ProgressBarTest::~ProgressBarTest()
{
    delete ui;
}

// add 1% to progressBar for GUI test
void ProgressBarTest::on_pbDown_clicked()
{
    progressBarValue--;
    ui->progressBar->setValue(progressBarValue);
}

// minus 1% from progressBar for GUI test
void ProgressBarTest::on_pbUp_clicked()
{
    progressBarValue++;
    ui->progressBar->setValue(progressBarValue);
}

// 跳转回首页
void ProgressBarTest::on_pbBack_clicked()
{
    emit signalpbtb();
}
