extern void delay(int i);
extern void delay_second();
extern void digital_display(int time);

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
    }
    else
    {
        curr_time == time; //倒计时
    }

    delay(200);
    digital_display(curr_time); //显示初始值

    for (i = 0; i <= time; i++)
    {
        delay_second();             //等待1s
        curr_time += i * order;     //时间递增 or 递减
        digital_display(curr_time); //更新数码管显示
    }
}