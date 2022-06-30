#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "dbconnect.h"
//#include "uart.h"
//#include "uart2.h"
#include "progressbartest.h"
#include "iomanager.h"
#include "infomanager.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

signals:
    void signaliomg();

    void signalinmg();

private slots:
    void on_pbIOManager_clicked();

    void on_pbInfoManager_clicked();

    void backfromiom();

    void backfrominm();

    void on_pbQuit_clicked();

private:
    Ui::Widget *ui;
    IOManager *iomPage = new IOManager;
    InfoManager *inmPage = new InfoManager;
};

#endif // WIDGET_H
