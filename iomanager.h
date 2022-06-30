#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <QWidget>
#include "dbconnect.h"
#include "uart.h"
// #include "uart2.h"
#include "uartthread.h"

namespace Ui {
class IOManager;
}

class IOManager : public QWidget//, public QThread
{
    Q_OBJECT

signals:
    void signaliomb();

public:
    explicit IOManager(QWidget *parent = 0);
    ~IOManager();

private slots:
    void on_pbBack_clicked();

    void on_rbisin_clicked(bool checked);

    void on_pbConnect_clicked();

    void on_pbkey0_clicked();

    void on_pbClean_clicked();

    void on_pbDele_clicked();

    void ttyGetData(QString ttyData);

    void on_pbkeyDown_clicked();

    void on_pbkeyUp_clicked();

    void on_tv_clicked(const QModelIndex &index);

    void on_pbChangeNum_clicked();

    void on_pbSubmit_clicked();

    void on_pbkeyBS_clicked();

private:
    Ui::IOManager *ui;
    bool isConnected;
    bool isSelected;
    bool isin = 0; // 1 = i, 0 = o; default : 0

    QString gtid,gtname,gtnum,gtprice;
    QString selected_gtid,selected_gtname,selected_gtprice,selected_gtnum;

    UartThread* thread1;

    int fdio;
    int RxLen=0;
    uint8_t RxBuff[1024]={0};
    void* receive(void* data);
    void refresh();
    void calPrice();
    QString qschange;
};

#endif // IOMANAGER_H
