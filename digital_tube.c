#include <reg51.h>

/**
 * @brief ��ʾָ��������
 * 
 * @param time ��ʱʱ��(ʮ����)
 */
void digital_display(int time)
{
    int unitPlace = time / 1 % 10;
    int decadePlace = time / 10 % 10;
	int display_time = 	 unitPlace + decadePlace * 16;
    P3 = 	  display_time;
}

/**
 * @brief ��ʼ������ܣ���ʾ00
 * 
 */
void digital_display_init()
{
    digital_display(0);
}