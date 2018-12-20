#include <stdio.h>
#include <reg51.h>
#include <string.h>
extern void delay(int i);
extern void delay_second();
extern void display_char(unsigned char i, unsigned char j, unsigned char DDATA);
extern void digital_display(int time);
extern void display_string(unsigned char y, unsigned char x, unsigned char string[]);
extern void lcd_init();
extern void lcd_start();

extern unsigned char code str_reset[];
char str_prompt[20];
const int WIDTH = 20;
const char PROGRESS_MARK = '*';

sbit pause_btn = P2 ^ 2; //key3

/**
 * @brief   显示状态信息
 * 
 * @param time 
 * @param order 
 * @param current 
 */
void display_status(int time, int order, int current)
{
    char str_status[20];
    int remain;
    if (order == 1)
    {
        remain = time - current;
    }
    else
    {
        remain = current;
    }
    sprintf(str_status, "Now:%ds,Remain:%ds", current, remain);
    lcd_start();
    display_string(1, 0, str_prompt);
    display_string(2, 0, str_status);
    display_string(3, 0, str_reset);
}

/**
 * @brief 显示运行过程中的指引信息
 * 
 */
void display_instruction()
{
    lcd_start();
    display_string(1, 0, str_prompt);
    display_string(2, 0, str_reset);
}

/**
 * @brief 清除进度条
 * 
 */
void clear_progress()
{
    display_string(3, 0, "                    ");
}

/**
 * @brief 显示进度条
 * 
 * @param time 
 * @param current 
 */
void display_progress(int time, int current)
{
    int current_progress = WIDTH * current / time;
    int i;
    clear_progress();
    for (i = 0; i < current_progress; i++)
    {
        display_char(3, i, PROGRESS_MARK);
    }
}

/**
 * @brief 计时    
 * 
 * @param time 计时时间（十进制）
 * @param order 顺序。1:正计时，-1:倒计时
 */
void count_time(int time, int order)
{
    int i;
    int curr_time; // 显示的时间

    if (order == 1)
    {
        curr_time = 0; //正计时
        sprintf(str_prompt, "Forward:%ds", time);
    }
    else
    {
        curr_time = time; //倒计时
        sprintf(str_prompt, "Backward:%ds", time);
    }

    display_instruction();

    delay(200);
    digital_display(curr_time); //显示初始值

    for (i = 0; i <= time; i++)
    {
        delay_second();                         //等待1s
        digital_display(curr_time + i * order); //更新数码管显示

        display_progress(time, curr_time + i * order); //显示进度条

        /**
         * @brief 暂停
         * 
         */
        if (pause_btn == 1)
        {
            display_status(time, order, curr_time + i * order);
            while (pause_btn == 1)
                ; //pause
            display_instruction();
        }
    }
    clear_progress();
    delay(200);
}