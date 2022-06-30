#ifndef UART_H
#define UART_H

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

#define PORT "/dev/ttyS3"

class Uart
{
public:
    class MyThread:public QThread
    {
    protected:
       void run()
       {
           //reiceive();
       }
    };
    Uart();
    ~Uart();
    bool UART_Open(const char* port);
    int UART_Set(int fd, int speed, int flow_ctrl, int databits, int stopbits, int parity);
    void UART_Close(int fd);
    unsigned char usartread(int fd,char *buffer,int len,unsigned char sec);
};

#endif // UART_H
