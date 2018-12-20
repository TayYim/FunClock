#include <stdio.h>
extern void delay(int i);
extern void delay_second();
extern void digital_display(int time);
extern void display_string(unsigned char y, unsigned char x, unsigned char string[]);
extern void lcd_init();

/**
 * @brief ��ʱ    
 * 
 * @param time ��ʱʱ�䣨ʮ���ƣ�
 * @param order ˳��1:����ʱ��-1:����ʱ
 */
void count_time(int time, int order)
{
    char str_prompt[20];                 //��ʾ��ʾ���ַ���
    char str_reset[] = {"Reset: Key 5"}; //��ʾȡ�����ַ���
    int i;                               //��������
    int curr_time;                       // ��ʾ��ʱ��

    if (order == 1)
    {
        curr_time = 0; //����ʱ����0��ʼ
        sprintf(str_prompt, "Forward:%ds", time);
    }
    else
    {
        curr_time = time; //����ʱ����time��ʼ
        sprintf(str_prompt, "Backward:%ds", time);
    }

    lcd_init();                       //LCD��ʼ��
    display_string(0, 0, str_prompt); //��ʾģʽ��Ϣ
    display_string(1, 0, str_reset);  //��ʾȡ����ʾ

    delay(200);
    digital_display(curr_time); //��ʾ��ʼֵ

    for (i = 0; i <= time; i++)
    {
        delay_second();                         //�ȴ�1s
        digital_display(curr_time + i * order); //�����������ʾ
    }
    delay(200);
}