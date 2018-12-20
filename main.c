#include <reg51.h>
#include <string.h> //后面字符串函数中取得数组的个数中用到;调用strlen函数

extern void delay(int i);   //延时函数
extern void delay_second(); //延时1秒
//LCD显示字符串函数
extern void display_string(unsigned char y, unsigned char x, unsigned char string[]);
extern void digital_display(int time);       //数码管显示函数
extern void digital_display_init();          //数码管初始化函数
extern void lcd_init();                      //LCD初始化函数
extern int set_time(int order);              //设置时间函数
extern void count_time(int time, int order); //计时函数

// 声明常量
/** 定义字符串 **/
const unsigned char code str_title[] = {"Multi-Function Clock"}; // 标题
const unsigned char code str_forward[] = {"Key 8: forward"};     // 正计时
const unsigned char code str_backward[] = {"Key 7: backward"};   // 倒计时
const unsigned char code str_set_time[] = {"Please set time"};   // 设置时间
const unsigned char code str_confirm[] = {"Repress to confirm"}; // 确认
const unsigned char code str_complete[] = {"Time's up!"};        // complete

/** 按键配置 **/
sbit forward_btn = P2 ^ 7;  //key8
sbit backward_btn = P2 ^ 6; //key7
sbit confirm_btn = P2 ^ 5;  //key6
sbit reset_btn = P2 ^ 4;    //key5 (不需要软件实现)
sbit pause_btn = P2 ^ 2;    //key3(暂停)
sbit t2_btn = P2 ^ 1;       //key2
sbit t1_btn = P2 ^ 0;       //key1
sbit beep = P1 ^ 3;         //蜂鸣器

/**
 * @brief 蜂鸣器奏响
 * 
 */
void do_beep()
{
  int i, j;
  for (i = 0; i < 500; i++) //时间长短
  {
    for (j = 0; j < 300; j++) //频率高低，数值越大音调越低
    {
      beep = ~beep; //取反
    }
  }
  for (i = 0; i < 500; i++) //时间长短
  {
    for (j = 0; j < 200; j++) //频率高低，数值越大音调越低
    {
      beep = ~beep; //取反
    }
  }
  for (i = 0; i < 500; i++) //时间长短
  {
    for (j = 0; j < 80; j++) //频率高低，数值越大音调越低
    {
      beep = ~beep; //取反
    }
  }
}

/**
 * @brief 初始化至初始状态
 * 
 */
void init_all()
{
  delay(15);              //长延时
  lcd_init();             //初始化LCD
  digital_display_init(); //初始化数码管

  display_string(0, 0, str_forward);  //显示正计时提示
  display_string(1, 0, str_backward); //显示倒计时提示
}

/**
 * @brief 主函数
 * 
 */
void main()
{
  int realtime; //用户输入的时间

  lcd_init();                      //初始化LCD
  display_string(0, 0, str_title); //显示欢迎页面

  delay(2000); //延迟等待

  init_all(); //进入系统

  while (1) // 开始循环状态
  {
    realtime = 0;         //重置为0
    if (forward_btn == 1) // 按下正计时开关
    {
      lcd_init();                         // 清屏
      display_string(0, 0, str_set_time); //显示设置时间提示
      display_string(1, 0, str_confirm);  //显示确认提示

      realtime = set_time(1);  //设置时间，等待确认
      count_time(realtime, 1); //开始正计时
      lcd_init();
      display_string(0, 0, str_complete); //显示计时结束
      do_beep();                          //响蜂鸣器
      delay(2000);                        //延迟等待
      init_all();                         //重置
    }

    if (backward_btn == 1) // 按下倒计时开关
    {
      lcd_init();                         // 清屏
      display_string(0, 0, str_set_time); //显示设置时间提示
      display_string(1, 0, str_confirm);  //显示确认提示

      realtime = set_time(-1);  //设置时间，等待确认
      count_time(realtime, -1); //开始倒计时
      lcd_init();
      display_string(0, 0, str_complete); //显示计时结束
      do_beep();                          //响蜂鸣器
      delay(2000);                        //延迟等待
      init_all();                         //重置
    }
  }
}
