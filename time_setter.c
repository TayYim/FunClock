#include <reg51.h>
sbit confirm_btn = P2 ^ 5; //key6
sbit t2_btn = P2 ^ 1;      //key2
sbit t1_btn = P2 ^ 0;      //key1
extern void digital_display(int time);

/**
 * @brief Set the time object
 * 
 * @return int ��ʱʱ��(ʮ����)
 */
int set_time()
{
    int t1_previous = 0;
    int t2_previous = 0;
    // t1��λ��t2ʮλ
    int t1_count = 0;
    int t2_count = 0;
    // ��ʼ��
    t1_btn = 0;
    t2_btn = 0;
    confirm_btn = 0;
    while (1)
    {
        /* ��λ */
        if (t1_btn ^ t1_previous == 1) // ���t1״̬�����ı�
        {
            t1_previous = !t1_previous; // t1_previousȡ��
            t1_count++;                 //����t1��ֵ

            if (t1_count > 9)
            {
                t1_count = 0; //������9���0
            }
            digital_display(t1_count + t2_count * 10); //ˢ����ʾ
        }

        /* ʮλ */
        if (t2_btn ^ t2_previous == 1) // ���t2״̬�����ı�(������һ������ʱ��֪��զô����)
        {
            t2_previous = !t2_previous; // t2_previousȡ��
            t2_count++;                 //����t2��ֵ

            if (t2_count > 9)
            {
                t2_count = 0; //������9���0
            }
            digital_display(t1_count + t2_count * 10); //ˢ����ʾ
        }

        /* ����ȷ�ϰ������˳����� */
        if (confirm_btn == 1)
        {
            break;
        }
    }
    return t1_count + 10 * t2_count;
}