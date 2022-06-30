/*
#include "uart2.h"

void Uart2::run()
{
    qDebug() << "当前线程对象的地址: " << QThread::currentThread();

    while (true)
    {
            //==========串口接收(字符串)============//
             while( ((RxLen = read(fdio, RxBuff,sizeof(RxBuff))) > 0)   )
             {
                 RxBuff[RxLen] = 0;
                 printf( "%s",RxBuff);
             }
             QThread::sleep(0);
    }

    qDebug() << "run() 执行完毕, 子线程退出...";
}

void Uart2::init(int fdio, int RxLen, uint8_t RxBuff[])
{
    this->fdio = fdio;
    this->RxLen = RxLen;
    this->RxBuff = RxBuff;
}
*/
