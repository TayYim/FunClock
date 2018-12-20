#include <reg51.h>
#include <string.h> //�����ַ���������ȡ������ĸ������õ�;����strlen����

extern void delay(int i);   //��ʱ����
extern void delay_second(); //��ʱ1��
//LCD��ʾ�ַ�������
extern void display_string(unsigned char y, unsigned char x, unsigned char string[]);
extern void digital_display(int time);       //�������ʾ����
extern void digital_display_init();          //����ܳ�ʼ������
extern void lcd_init();                      //LCD��ʼ������
extern int set_time(int order);              //����ʱ�亯��
extern void count_time(int time, int order); //��ʱ����

// ��������
/** �����ַ��� **/
const unsigned char code str_title[] = {"Multi-Function Clock"}; // ����
const unsigned char code str_forward[] = {"Key 8: forward"};     // ����ʱ
const unsigned char code str_backward[] = {"Key 7: backward"};   // ����ʱ
const unsigned char code str_set_time[] = {"Please set time"};   // ����ʱ��
const unsigned char code str_confirm[] = {"Repress to confirm"}; // ȷ��
const unsigned char code str_complete[] = {"Time's up!"};        // complete

/** �������� **/
sbit forward_btn = P2 ^ 7;  //key8
sbit backward_btn = P2 ^ 6; //key7
sbit confirm_btn = P2 ^ 5;  //key6
sbit reset_btn = P2 ^ 4;    //key5 (����Ҫ���ʵ��)
sbit pause_btn = P2 ^ 2;    //key3(��ͣ)
sbit t2_btn = P2 ^ 1;       //key2
sbit t1_btn = P2 ^ 0;       //key1
sbit beep = P1 ^ 3;         //������

/**
 * @brief ����������
 * 
 */
void do_beep()
{
  int i, j;
  for (i = 0; i < 500; i++) //ʱ�䳤��
  {
    for (j = 0; j < 300; j++) //Ƶ�ʸߵͣ���ֵԽ������Խ��
    {
      beep = ~beep; //ȡ��
    }
  }
  for (i = 0; i < 500; i++) //ʱ�䳤��
  {
    for (j = 0; j < 200; j++) //Ƶ�ʸߵͣ���ֵԽ������Խ��
    {
      beep = ~beep; //ȡ��
    }
  }
  for (i = 0; i < 500; i++) //ʱ�䳤��
  {
    for (j = 0; j < 80; j++) //Ƶ�ʸߵͣ���ֵԽ������Խ��
    {
      beep = ~beep; //ȡ��
    }
  }
}

/**
 * @brief ��ʼ������ʼ״̬
 * 
 */
void init_all()
{
  delay(15);              //����ʱ
  lcd_init();             //��ʼ��LCD
  digital_display_init(); //��ʼ�������

  display_string(0, 0, str_forward);  //��ʾ����ʱ��ʾ
  display_string(1, 0, str_backward); //��ʾ����ʱ��ʾ
}

/**
 * @brief ������
 * 
 */
void main()
{
  int realtime; //�û������ʱ��

  lcd_init();                      //��ʼ��LCD
  display_string(0, 0, str_title); //��ʾ��ӭҳ��

  delay(2000); //�ӳٵȴ�

  init_all(); //����ϵͳ

  while (1) // ��ʼѭ��״̬
  {
    realtime = 0;         //����Ϊ0
    if (forward_btn == 1) // ��������ʱ����
    {
      lcd_init();                         // ����
      display_string(0, 0, str_set_time); //��ʾ����ʱ����ʾ
      display_string(1, 0, str_confirm);  //��ʾȷ����ʾ

      realtime = set_time(1);  //����ʱ�䣬�ȴ�ȷ��
      count_time(realtime, 1); //��ʼ����ʱ
      lcd_init();
      display_string(0, 0, str_complete); //��ʾ��ʱ����
      do_beep();                          //�������
      delay(2000);                        //�ӳٵȴ�
      init_all();                         //����
    }

    if (backward_btn == 1) // ���µ���ʱ����
    {
      lcd_init();                         // ����
      display_string(0, 0, str_set_time); //��ʾ����ʱ����ʾ
      display_string(1, 0, str_confirm);  //��ʾȷ����ʾ

      realtime = set_time(-1);  //����ʱ�䣬�ȴ�ȷ��
      count_time(realtime, -1); //��ʼ����ʱ
      lcd_init();
      display_string(0, 0, str_complete); //��ʾ��ʱ����
      do_beep();                          //�������
      delay(2000);                        //�ӳٵȴ�
      init_all();                         //����
    }
  }
}
