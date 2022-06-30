#include "uart.h"

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//int fd;

Uart::Uart()
{

}

Uart::~Uart()
{

}

bool Uart::UART_Open(const char *port)
{
    //int fd = open(port, O_RDONLY | O_NOCTTY | O_NDELAY);
    int fd = open(port, O_RDONLY | O_NOCTTY);
    if (fd == 0)
    {
        qDebug() << "Can't Open Serial Port";
        return (0);
    }

    if (isatty(fd) == 0)
    {
        qDebug() << "standard input is not a terminal device";
        return (0);
    }

    return fd;
}

int Uart::UART_Set(int fd, int speed, int flow_ctrl, int databits, int stopbits, int parity)
{
    int i;
    int speed_arr[] = {B115200, B57600, B38400, B19200, B9600, B4800, B2400, B1200, B300};
    int name_arr[] = {115200, 57600, 38400, 19200, 9600, 4800, 2400, 1200, 300};
    struct termios options, old_options;

    /*tcgetattr(fd,&options)得到与fd指向对象的相关参数，并将它们保存于options,该函数,还可以测试配置是否正确，该串口是否可用等。若调用成功，函数返回值为0，若调用失败，函数返回值为1.
    */
    if (tcgetattr(fd, &old_options) != 0)
    {
        qDebug() << "SetupSerial 1";
        return (0);
    }
    memset(&options, 0, sizeof(options)); //清除参数
    //设置串口输入波特率和输出波特率
    for (i = 0; i < sizeof(speed_arr) / sizeof(int); i++)
    {
        if (speed == name_arr[i])
        {
            cfsetispeed(&options, speed_arr[i]);
            cfsetospeed(&options, speed_arr[i]);
        }
    }
    //修改控制模式，保证程序不会占用串口
    options.c_cflag |= CLOCAL;
    //修改控制模式，使得能够从串口中读取输入数据
    options.c_cflag |= CREAD;
    //设置数据流控制
    switch (flow_ctrl)
    {
    case 0: //不使用流控制
        options.c_cflag &= ~CRTSCTS;
        break;
    case 1: //使用硬件流控制
        options.c_cflag |= CRTSCTS;
        break;
    case 2: //使用软件流控制
        options.c_cflag |= IXON | IXOFF | IXANY;
        break;
    }
    //设置数据位
    options.c_cflag &= ~CSIZE; //屏蔽其他标志位 设置数据位之前一定要屏蔽
    switch (databits)
    {
    case 5:
        options.c_cflag |= CS5;
        break;
    case 6:
        options.c_cflag |= CS6;
        break;
    case 7:
        options.c_cflag |= CS7;
        break;
    case 8:
        options.c_cflag |= CS8;
        break;
    default:
        qDebug() << "Unsupported data size";
        return (0);
    }
    //设置校验位
    switch (parity)
    {
    case 'n':
    case 'N': //无奇偶校s验位。
        options.c_cflag &= ~PARENB;
        options.c_iflag &= ~INPCK;
        break;
    case 'o':
    case 'O': //设置为奇校验
        options.c_cflag |= (PARODD | PARENB);
        options.c_iflag |= INPCK;
        break;
    case 'e':
    case 'E': //设置为偶校验
        options.c_cflag |= PARENB;
        options.c_cflag &= ~PARODD;
        options.c_iflag |= INPCK;
        break;
    case 's':
    case 'S': //设置为空格
        options.c_cflag &= ~PARENB;
        options.c_cflag &= ~CSTOPB;
        break;
    default:
        qDebug() << "Unsupported parity";
        return (0);
    }
    // 设置停止位
    switch (stopbits)
    {
    case 1:
        options.c_cflag &= ~CSTOPB;
        break;
    case 2:
        options.c_cflag |= CSTOPB;
        break;
    default:
        qDebug() << "Unsupported stop bits";
        return (0);
    }
    //修改输出模式，原始数据输出
    options.c_oflag &= ~OPOST;

    //设置等待时间和最小接收字符
    options.c_cc[VTIME] = 1;// 单位是百毫秒
    options.c_cc[VMIN] = 255;

    //如果发生数据溢出，接收数据，但是不再读取
    tcflush(fd, TCIFLUSH);

    qDebug() << "finalgd";

    //激活配置 (将修改后的termios数据设置到串口中）
    if (tcsetattr(fd, TCSANOW, &options) != 0)
    {
        qDebug() << "com set error!";
        return (0);
    }
    return (1);
}

void Uart::UART_Close(int fd)
{
    close(fd);
}

/*
// 接收数据,使用read () / readLine () / readAll ()
void Uart::receive(int fd)
{
    char BUF[512] = {0};                                       // 存储转换类型后的数据
    QByteArray data = fd->readAll();                      // 读取数据

    if(!data.isEmpty())                                 // 接收到数据
    {
        QString str = ui->DataReceived->toPlainText();  // 返回纯文本
        str += tr(data);                         // 数据是一行一行传送的，要保存所有数据
        ui->receive->clear();                      // 清空之前的数据
        ui->receive->append(str);                  // 将数据放入控件中
        qDebug() << "str info: " << ui->DataReceived->toPlainText();

         // 清除之前的数据，防止追加，因为每次获取的数据不一样
        int index = str.indexOf("\r\n");                // 找到，返回索引值，找不到，返回-1
        if(index != -1)
        {
            snprintf(BUF,500,"%s", str.left(index + 2).toUtf8().data()); // QString转为char * 类型
            qDebug() << "BUF info: " << BUF;        // 数据类型转换成功
            str.remove(0,index + 2);

            // 处理获取到的数据，将其放入对应的控件中
            // .....

        }
    }
}
*/

unsigned char usartread(int fd,char *buffer,int len,unsigned char sec)
{
    fd_set  rset;
    int rv = -1;
    int nread=0;
    struct timeval timeout;
    timeout.tv_sec=sec;
    timeout.tv_usec=0;

    FD_ZERO(&rset);
    FD_SET(fd, &rset);
    rv = select(fd+1, &rset, NULL, NULL, &timeout);
    if(rv < 0)
    {
        printf("select() failed: %s\n", strerror(errno));
        return 0;
    }
    nread = read(fd, buffer, len);
    return nread;
}
