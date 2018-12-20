#include <reg51.h>
sbit forward_btn = P2 ^ 7;  //key8
sbit backward_btn = P2 ^ 6; //key7
sbit t2_btn = P2 ^ 1;      //key2
sbit t1_btn = P2 ^ 0;      //key1
extern void digital_display(int time);

/**
 * @brief Set the time object
 *
 * @param order 顺序。1:正计时，-1:倒计时
 * 
 * @return int 计时时间(十进制)
 */
int set_time(int order)
{
    int t1_previous = t1_btn;
    int t2_previous = t2_btn;
    // t1个位，t2十位
    int t1_count = 0;
    int t2_count = 0;

    while (1)
    {
        /* 个位 */
        if (t1_btn ^ t1_previous == 1) // 如果t1状态发生改变
        {
            t1_previous = !t1_previous; // t1_previous取反
            t1_count++;                 //更新t1数值

            if (t1_count > 9)
            {
                t1_count = 0; //若超过9则归0
            }
            digital_display(t1_count + t2_count * 10); //刷新显示
        }

        /* 十位 */
        if (t2_btn ^ t2_previous == 1) // 如果t2状态发生改变(和上面一样，暂时不知道咋么复用)
        {
            t2_previous = !t2_previous; // t2_previous取反
            t2_count++;                 //更新t2数值

            if (t2_count > 9)
            {
                t2_count = 0; //若超过9则归0
            }
            digital_display(t1_count + t2_count * 10); //刷新显示
        }

        /* 按下确认按键后退出设置 */
        if (order==1 & forward_btn==0)
        {
            break;
        }
		if (order==-1 & backward_btn==0)
        {
            break;
        }

    }
    return t1_count + 10 * t2_count;
}