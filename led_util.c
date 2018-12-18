#include <reg51.h>
#include <string.h> //后面字符串函数中取得数组的个数中用到;调用strlen函数

extern void delay(int i);

//重新定义各个控制引脚的名称
sbit rs = P1 ^ 0; //重定义,rs电平为1则传送数据,为0则转送指令
sbit rw = P1 ^ 1; //控制LCD读或者写;为1则读LCD,为0则写入LCD
sbit en = P1 ^ 2; //LCD行动控制,EN为下降沿则交互执行,即EN = 1;跟着EN = 0;

/**
 * @brief 读忙字程序,用于判断LCD液晶是否忙状态.如果不进行判断可能会导致数据写入LCD失败.
 * 
 */
void read_busy() //无返回值 函数名 (空)
{
    P0 = 0xff; //把0xff发送给LCD的数据总线
    rs = 0;    //选指令
    rw = 1;    //选择读
    en = 1;    //使能端置1(高电平)
    while (P0 & 0x80)
        ;   //循环 (如果P0和0x80相等的话) P0 & 0x80相与,即P0总线的8位二进制数与10000000比较,
            //全部相同则结果为 1<真>;忙状态成立,程序在此处死循环相与
    en = 0; //使能端置0(低电平)
}

/**
 * @brief 写数据或指令子程序
 * 
 * @param x 
 * @param DATA 
 */
void ddata(int x, unsigned char DATA) //无返回值 函数名 (定义整形变量 x, 定义长字符型变量 DDATA)
{
    read_busy(); //读忙子程序
    P0 = DATA;   //如果不忙,则把参数 DDATA 获取到的变量赋值给 总线<P0>
    rw = 0;      //读写端选择为 写<0>
    rs = x;      //数据或指令端选择为参数 <x>的值, x的值为0或者1;为0表示总线传输的是控制LCD指令,为1表示要显示的数据
    en = 1;      //使能端置1
    en = 0;      //使能端置0; 接上一条指令形成一个下降沿,LCD识别到下降沿信号则读取总线内容
}

/**
 * @brief LCD初始化函数
 * 
 */
void lcd_init() //无返回值 函数名 (空)
{
    rs = 1;         //rs设置为 数据
    rw = 1;         //rw设置为 读
    en = 1;         //en设置为高电平
    P0 = 0xff;      //总线写入0xff
    delay(15);      //长延时
    ddata(0, 0x38); //函数名 (指令, 指令内容)  //  0发送给ddata函数中的x,再经ddata函数发送给rs,即rs设置为指令;;0x38为指令内容
    delay(5);       //短延时
    ddata(0, 0x38); //0x38  表示设置16*2显示，5*7点阵，8位数据接口
    ddata(0, 0x08); //0x08  表示只开显示
    ddata(0, 0x01); //0x01  表示清屏
    ddata(0, 0x06); //0x06  表示地址加1，当写入数据的时候光标右移
    ddata(0, 0x0c); //0x0c  表示开显示，不显示光标
}

/**
 * @brief 显示单个字符
 * 
 * @param i 
 * @param j 
 * @param DDATA 
 */
void display_char(unsigned char i, unsigned char j, unsigned char DDATA) //无返回值 函数名 (定义字符形参i, 字符形参j, 字符形参DDATA)
{
    if (i) //如果 (i的值为1<真>)
    {
        j = j + 0x40; //第二行起始地址加上列数为字符显示地址 //则把j加0x40后的值赋给j;;等同于j += 0x40        ,
    }
    j = j + 0x80;    //同上,0x80指第一行首列的地址,若if语句有效, 则最终j=  第二行首字母的地址
    ddata(0, j);     //函数名 (指令, 内容)
    ddata(1, DDATA); //函数名 (数据, 内容)
}

/**
 * @brief 显示字符串
 * 
 * @param y 
 * @param x 
 * @param string 
 */
void display_string(unsigned char y, unsigned char x, unsigned char string[]) //函数名 参数定义
{
    unsigned char j;        //参数定义
    unsigned char i;        //参数定义
    int k = 1;              //定义整形参数k并赋值为1
    i = 0;                  //i赋值为0
    j = strlen(string) + x; //j = 取数组个数加上x<首列位置>的值,最终j的值为数组中最后一位字符的列,j最终值在0~15之间

    for (; k > 0;)                         //循环 (空; 如果k大于0;空)                                                                        !
    {                                      //则                                                                                                                        !
                                           //判断                                                                                                                ! 所有加 "!" 备注的代码可以压缩为:
        if (x < j)                         //如果 (当前显示列数x < 最后一位字符的列数j)                                        ! while (x < j)
        {                                  //则                                                                                                                        ! {
            display_char(y, x, string[i]); //函数名 (行y<0或1>送出, 列x<0~15>送出, 数组[第i位]送出)                !         display (y, x, string[i]);
            x++;                           //列数加1                                                                                                        !         x++;
            i++;                           //数组第i位加1                                                                                                !         i++;
        }                                  //                                                                                                        !  }
        else                               //否则                                                                                                                !
        {                                  //                                                                                                        !
            k = 0;                         //k 置0,  for循环退出                                                                                !
        }
    }
}