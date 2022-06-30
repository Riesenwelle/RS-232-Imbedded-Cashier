# RS-232-Imbedded-Cashier
---
基于IMX6的简单的收银系统，扫描条码，在ARM架构嵌入式Linux下运行；使用Qt/C++编写。  
Simple cashier based on IMX6, scanning barcode, imbedded Linux with ARM architechture; Write in Qt/C++.  
---
## 一些注意点：  
> + 使用的RS-232串口为: /dev/ttyS3  
> + 串口波特率设置为: B9600  
> + 使用的条码扫描枪为: Easytech STK-888  
> + 配置手册可见: [https://www.docin.com/p-743441628.html](https://www.docin.com/p-743441628.html)  
> + 使用SQLite3数据库进行数据的存取  
> + 由于实验箱自带1-9硬按键输入，软键盘中没有设置数字1-9  
> + 答案是 HITWH 的嵌入式课设
