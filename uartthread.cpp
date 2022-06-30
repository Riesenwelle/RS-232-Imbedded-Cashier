#include "uartthread.h"

extern QSqlDatabase db; // 数据库全局变量

UartThread::UartThread()
{

}

UartThread::~UartThread()
{

}

void UartThread::run()
{
    int fd = 0;
    int RxLen = 0;
    uint8_t RxBuff[1024] = {0};

    //==========串口打开============//
    fd = open(UART_DEV ,O_RDWR|O_NOCTTY);
    if(fd<0){
      printf("COM (%s) Open Fail ! \n",UART_DEV); //必须要权限.
      return;
    }


    printf("COM (%s) Open Success ! Watting recv...\n\n",UART_DEV);
    //==========配置串口============//
    struct  termios opt;          //配置串口的属性定义在结构体struct termios中
    tcgetattr(fd, & opt);         //获取终端控制属性

    cfsetispeed(& opt, B9600);  //指定输入波特率(若不设置系统默认9600bps)
    cfsetospeed(& opt, B9600);  //指定输出波特率(若不设置系统默认9600bps)

    /* c_lflag 本地模式 */
    opt.c_cflag &= ~ INPCK;           //不启用输入奇偶检测
    opt.c_cflag |= (CLOCAL |  CREAD); //CLOCAL忽略 modem 控制线,CREAD打开接受者

    /* c_lflag 本地模式 */
    opt.c_lflag &= ~(ICANON | ECHO | ECHOE |  ISIG); //ICANON启用标准模式;ECHO回显输入字符;ECHOE如果同时设置了 ICANON，字符 ERASE 擦除前一个输入字符，WERASE 擦除前一个词;ISIG当接受到字符 INTR, QUIT, SUSP, 或 DSUSP 时，产生相应的信号

    /* c_oflag 输出模式 */
    opt.c_oflag &= ~ OPOST;             //OPOST启用具体实现自行定义的输出处理
    opt.c_oflag &= ~(ONLCR | OCRNL);    //ONLCR将输出中的新行符映射为回车-换行,OCRNL将输出中的回车映射为新行符

    /* c_iflag 输入模式 */
    opt.c_iflag &= ~(ICRNL |  INLCR);          //ICRNL将输入中的回车翻译为新行 (除非设置了 IGNCR),INLCR将输入中的 NL 翻译为 CR
    opt.c_iflag &= ~(IXON | IXOFF | IXANY);    //IXON启用输出的 XON/XOFF流控制,IXOFF启用输入的 XON/XOFF流控制,IXANY(不属于 POSIX.1；XSI) 允许任何字符来重新开始输出

    /* c_cflag 控制模式 */
    opt.c_cflag &= ~ CSIZE;     //字符长度掩码,取值为 CS5, CS6, CS7, 或 CS8,加~就是无
    opt.c_cflag |=  CS8;        //数据宽度是8bit
    opt.c_cflag &= ~ CSTOPB;    //CSTOPB设置两个停止位，而不是一个,加~就是设置一个停止位
    opt.c_cflag &= ~ PARENB;    //PARENB允许输出产生奇偶信息以及输入的奇偶校验,加~就是无校验

    /* c_cc[NCCS] 控制字符 */
    opt.c_cc[VTIME] = 0 ;   //等待数据时间(10秒的倍数),每个单位是0.1秒  若20就是2秒
    opt.c_cc[VMIN] = 0 ;    //最少可读数据,非规范模式读取时的最小字符数，设为0则为非阻塞，如果设为其它值则阻塞，直到读到到对应的数据,就像一个阀值一样，比如设为8，如果只接收到3个数据，那么它是不会返回的，只有凑齐8个数据后一齐才READ返回，阻塞在那儿
    /* new_cfg.c_cc[VMIN]   =   8;//DATA_LEN;
       new_cfg.c_cc[VTIME]  =   20;//每个单位是0.1秒  20就是2秒
       如果这样设置，就完全阻塞了，只有串口收到至少8个数据才会对READ立即返回，或才少于8个数据时，超时2秒也会有返回
       另外特别注意的是当设置VTIME后，如果read第三个参数小于VMIN ，将会将VMIN 修改为read的第三个参数*/

    /*TCIFLUSH  刷清输入队列
      TCOFLUSH  刷清输出队列
      TCIOFLUSH 刷清输入、输出队列*/
    tcflush(fd, TCIOFLUSH);         //刷串口清缓存
    tcsetattr(fd, TCSANOW, &opt);   //设置终端控制属性,TCSANOW：不等数据传输完毕就立即改变属性

    while(1)
    {
        //==========串口接收(字符串)============//
        while( ((RxLen = read(fd, RxBuff,sizeof(RxBuff))) > 0)   )
        {
            QString gtid,gtname,gtprice,gtnum;
            RxBuff[RxLen] = 0; // 结束符'\0'

            //printf("%s",RxBuff); // true output string, from printf
            //printf("uthread final:%s\n",RxBuff); // final output string

            // convert uint8_t (unsigned char*) to QString
            char *ctemp = (char *)RxBuff;
            qsttyTemp = QString(QLatin1String(ctemp));
            //qsttyTemp.chop(1); // 去掉最后一位的\n

            //qDebug() << "uthread real:" << qsttyTemp; // need to chop last \n outside this sub-thread
            emit ttySendData(qsttyTemp);

            count = 0;
         }
        // --------?-?-?--------
        // 以一定的时间间隔来更新接收数据的字节数，如果在此间隔内（比如10ms），没有接收到数据了，说明对方发送结束...?
        // 实际好像不是上面的原理, 不知道怎么就能行了
        // if不能删, 否则又不行了
        // 有点卡 (maybe 0.5s), 但是可用
        // --------?-?-?--------
        if(count >= 10)
        {
            //qDebug() << "Reiceive complete"; // no-use
            count = 0;
        }
        count++;
        sleep(1); // delay 1ms
    }
}
