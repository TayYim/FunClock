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
 * @brief   ��ʾ״̬��Ϣ
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
 * @brief ��ʾ���й����е�ָ����Ϣ
 * 
 */
void display_instruction()
{
    lcd_start();
    display_string(1, 0, str_prompt);
    display_string(2, 0, str_reset);
}

/**
 * @brief ���������
 * 
 */
void clear_progress()
{
    display_string(3, 0, "                    ");
}

/**
 * @brief ��ʾ������
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
 * @brief ��ʱ    
 * 
 * @param time ��ʱʱ�䣨ʮ���ƣ�
 * @param order ˳��1:����ʱ��-1:����ʱ
 */
void count_time(int time, int order)
{
    int i;
    int curr_time; // ��ʾ��ʱ��

    if (order == 1)
    {
        curr_time = 0; //����ʱ
        sprintf(str_prompt, "Forward:%ds", time);
    }
    else
    {
        curr_time = time; //����ʱ
        sprintf(str_prompt, "Backward:%ds", time);
    }

    display_instruction();

    delay(200);
    digital_display(curr_time); //��ʾ��ʼֵ

    for (i = 0; i <= time; i++)
    {
        delay_second();                         //�ȴ�1s
        digital_display(curr_time + i * order); //�����������ʾ

        display_progress(time, curr_time + i * order); //��ʾ������

        /**
         * @brief ��ͣ
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