/** ���� **/
const int SECOND_PARAM = 500;

/**
 * @brief ��ʱ����
 * 
 * @param i 
 */
void delay(int i)
{
    int t;                        //�������α��� ����t
    for (; i >= 1; i--)           //ѭ�� (�պ���; �ж�i�Ƿ���ڻ����1; i��1<�Լ�>) i��ֵ�ǵ��ô˺���ʱ�趨��
    {                             //��i��ֵ���ڻ����1;���������һ��ѭ��
        for (t = 120; t > 1; t--) //ѭ�� (t��ֵ120; �ж�t��ֵ�Ƿ����1; t�Լ�)
        {                         //�պ���
        }
    }
}

/**
 * @brief ��ʱ1��
 * 
 */
void delay_second()
{
    delay(SECOND_PARAM);
}