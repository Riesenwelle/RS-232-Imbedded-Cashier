#ifndef UARTTHREAD_H
#define UARTTHREAD_H

#include "dbconnect.h"
#include <stdlib.h>
#include  <fcntl.h>
#include  "stdio.h"
#include  "termios.h"
#include  "unistd.h"
#include  "limits.h"
#include  <stdint.h>
#include  "time.h"
 //===================
#include <sys/select.h>
#include <sys/time.h>
 //===================

#define   UART_DEV   "/dev/ttyS3" // 根据电脑插入的串口号定义

class UartThread : public QThread
{
    Q_OBJECT

    //定义虚函数run()用来执行线程
protected:
    void run();

private:

signals:
    void ttySendData(QString ttyData);

public:
    UartThread();
    ~UartThread();
    int count = 0;
    QString qsttyTemp;
};

#endif // UARTTHREAD_H
