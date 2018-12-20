#include <reg51.h>
#include <string.h> //�����ַ���������ȡ������ĸ������õ�;����strlen����

extern void delay(int i);
extern unsigned char code str_title[];

//���¶�������������ŵ�����
sbit rs = P1 ^ 0; //�ض���,rs��ƽΪ1��������,Ϊ0��ת��ָ��
sbit rw = P1 ^ 1; //����LCD������д;Ϊ1���LCD,Ϊ0��д��LCD
sbit en = P1 ^ 2; //LCD�ж�����,ENΪ�½����򽻻�ִ��,��EN = 1;����EN = 0;

/**
 * @brief ��æ�ֳ���,�����ж�LCDҺ���Ƿ�æ״̬.����������жϿ��ܻᵼ������д��LCDʧ��.
 * 
 */
void read_busy() //�޷���ֵ ������ (��)
{
    P0 = 0xff; //��0xff���͸�LCD����������
    rs = 0;    //ѡָ��
    rw = 1;    //ѡ���
    en = 1;    //ʹ�ܶ���1(�ߵ�ƽ)
    while (P0 & 0x80)
        ;   //ѭ�� (���P0��0x80��ȵĻ�) P0 & 0x80����,��P0���ߵ�8λ����������10000000�Ƚ�,
            //ȫ����ͬ����Ϊ 1<��>;æ״̬����,�����ڴ˴���ѭ������
    en = 0; //ʹ�ܶ���0(�͵�ƽ)
}

/**
 * @brief д���ݻ�ָ���ӳ���
 * 
 * @param x 
 * @param DATA 
 */
void ddata(int x, unsigned char DATA) //�޷���ֵ ������ (�������α��� x, ���峤�ַ��ͱ��� DDATA)
{
    read_busy(); //��æ�ӳ���
    P0 = DATA;   //�����æ,��Ѳ��� DDATA ��ȡ���ı�����ֵ�� ����<P0>
    rw = 0;      //��д��ѡ��Ϊ д<0>
    rs = x;      //���ݻ�ָ���ѡ��Ϊ���� <x>��ֵ, x��ֵΪ0����1;Ϊ0��ʾ���ߴ�����ǿ���LCDָ��,Ϊ1��ʾҪ��ʾ������
    en = 1;      //ʹ�ܶ���1
    en = 0;      //ʹ�ܶ���0; ����һ��ָ���γ�һ���½���,LCDʶ���½����ź����ȡ��������
}

/**
 * @brief LCD��ʼ������
 * 
 */
void lcd_init() //�޷���ֵ ������ (��)
{
    rs = 1;         //rs����Ϊ ����
    rw = 1;         //rw����Ϊ ��
    en = 1;         //en����Ϊ�ߵ�ƽ
    P0 = 0xff;      //����д��0xff
    delay(15);      //����ʱ
    ddata(0, 0x38); //������ (ָ��, ָ������)  //  0���͸�ddata�����е�x,�پ�ddata�������͸�rs,��rs����Ϊָ��;;0x38Ϊָ������
    delay(5);       //����ʱ
    ddata(0, 0x38); //0x38  ��ʾ����16*2��ʾ��5*7����8λ���ݽӿ�
    ddata(0, 0x08); //0x08  ��ʾֻ����ʾ
    ddata(0, 0x01); //0x01  ��ʾ����
    ddata(0, 0x06); //0x06  ��ʾ��ַ��1����д�����ݵ�ʱ��������
    ddata(0, 0x0c); //0x0c  ��ʾ����ʾ������ʾ���
}

/**
 * @brief ��ʾ�����ַ�
 * 
 * @param i 
 * @param j 
 * @param DDATA 
 */
void display_char(unsigned char i, unsigned char j, unsigned char DDATA) //�޷���ֵ ������ (�����ַ��β�i, �ַ��β�j, �ַ��β�DDATA)
{
    int add;
    switch (i)
    {
    case 0:
        add = 0x00; //0
        break;
    case 1:
        add = 0x40; //64
        break;
    case 2:
        add = 0x14; //20
        break;
    case 3:
        add = 0x54; //84
        break;
    default:
        add = 0x00;
    }
    add = add + 0x80;
    j = j + add;

    ddata(0, j);     //������ (ָ��, ����)
    ddata(1, DDATA); //������ (����, ����)
}

/**
 * @brief ��ʾ�ַ���
 * 
 * @param y 
 * @param x 
 * @param string 
 */
void display_string(unsigned char y, unsigned char x, unsigned char string[]) //������ ��������
{
    unsigned char j;        //��������
    unsigned char i;        //��������
    int k = 1;              //�������β���k����ֵΪ1
    i = 0;                  //i��ֵΪ0
    j = strlen(string) + x; //j = ȡ�����������x<����λ��>��ֵ,����j��ֵΪ���������һλ�ַ�����,j����ֵ��0~15֮��

    for (; k > 0;)                         //ѭ�� (��; ���k����0;��)                                                                        !
    {                                      //��                                                                                                                        !
                                           //�ж�                                                                                                                ! ���м� "!" ��ע�Ĵ������ѹ��Ϊ:
        if (x < j)                         //��� (��ǰ��ʾ����x < ���һλ�ַ�������j)                                        ! while (x < j)
        {                                  //��                                                                                                                        ! {
            display_char(y, x, string[i]); //������ (��y<0��1>�ͳ�, ��x<0~15>�ͳ�, ����[��iλ]�ͳ�)                !         display (y, x, string[i]);
            x++;                           //������1                                                                                                        !         x++;
            i++;                           //�����iλ��1                                                                                                !         i++;
        }                                  //                                                                                                        !  }
        else                               //����                                                                                                                !
        {                                  //                                                                                                        !
            k = 0;                         //k ��0,  forѭ���˳�                                                                                !
        }
    }
}

void lcd_start()
{
    lcd_init();
    delay(5);
    display_string(0, 0, str_title);
}