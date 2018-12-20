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
{	char str_prompt[20];
	char str_reset[]={"Reset: Key 5"};
    int i;
    int curr_time; // 显示的时间

    if (order == 1)
    {
        curr_time = 0; //正计时
		sprintf(str_prompt,"Forward:%ds",time);
    }
    else
    {
        curr_time = time; //倒计时
		sprintf(str_prompt,"Backward:%ds",time);
    }

	lcd_init();
	display_string(0,0,str_prompt);	  	
	display_string(1,0,str_reset);


    delay(200);
    digital_display(curr_time); //显示初始值

    for (i = 0; i <= time; i++)
    {
        delay_second();             //等待1s
        digital_display(curr_time + i * order); //更新数码管显示
    }
	delay(200);
}