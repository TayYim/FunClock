#include <reg51.h>
sbit confirm_btn = P2 ^ 5; //key6
sbit t2_btn = P2 ^ 1;      //key2
sbit t1_btn = P2 ^ 0;      //key1
extern void digital_display(int time);

/**
 * @brief Set the time object
 * 
 * @return int 计时时间(十进制)
 */
int set_time()
{
    int t1_previous = 0;
    int t2_previous = 0;
    // t1个位，t2十位
    int t1_count = 0;
    int t2_count = 0;
    // 初始化
    t1_btn = 0;
    t2_btn = 0;
    confirm_btn = 0;
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
        if (confirm_btn == 1)
        {
            break;
        }
    }
    return t1_count + 10 * t2_count;
}