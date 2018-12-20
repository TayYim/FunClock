#include <stdio.h>
extern void delay(int i);
extern void delay_second();
extern void digital_display(int time);
extern void display_string(unsigned char y, unsigned char x, unsigned char string[]);
extern void lcd_init();

/**
 * @brief 计时    
 * 
 * @param time 计时时间（十进制）
 * @param order 顺序。1:正计时，-1:倒计时
 */
void count_time(int time, int order)
{
    char str_prompt[20];                 //显示提示的字符串
    char str_reset[] = {"Reset: Key 5"}; //显示取消的字符串
    int i;                               //计数变量
    int curr_time;                       // 显示的时间

    if (order == 1)
    {
        curr_time = 0; //正计时，从0开始
        sprintf(str_prompt, "Forward:%ds", time);
    }
    else
    {
        curr_time = time; //倒计时，从time开始
        sprintf(str_prompt, "Backward:%ds", time);
    }

    lcd_init();                       //LCD初始化
    display_string(0, 0, str_prompt); //显示模式信息
    display_string(1, 0, str_reset);  //显示取消提示

    delay(200);
    digital_display(curr_time); //显示初始值

    for (i = 0; i <= time; i++)
    {
        delay_second();                         //等待1s
        digital_display(curr_time + i * order); //更新数码管显示
    }
    delay(200);
}