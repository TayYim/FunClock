extern void delay(int i);
extern void delay_second();
extern void digital_display(int time);

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
    }
    else
    {
        curr_time == time; //����ʱ
    }

    delay(200);
    digital_display(curr_time); //��ʾ��ʼֵ

    for (i = 0; i <= time; i++)
    {
        delay_second();             //�ȴ�1s
        curr_time += i * order;     //ʱ����� or �ݼ�
        digital_display(curr_time); //�����������ʾ
    }
}