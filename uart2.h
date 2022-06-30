/*
#ifndef UART2_H
#define UART2_H

#include"dbconnect.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <QString>
#include <termios.h>
#include "dbconnect.h"
#include<sys/ioctl.h>

class Uart2: public QThread
{
    Q_OBJECT
public:
    void init(int fdio, int RxLen, uint8_t RxBuff[]);
    //explicit ttyThread(QObject *parent = nullptr);

protected:
    void run();

signals:
    // 自定义信号, 传递数据
    //void curNumber(int num);

public slots:

private:
    int fdio =0;
    int RxLen=0;
    uint8_t RxBuff[1024]={0};

};

#endif // UART2_H
*/
