#include <reg51.h>
#include <string.h> //�����ַ���������ȡ������ĸ������õ�;����strlen����

extern void delay(int i);
extern void delay_second();
extern void display_string(unsigned char y, unsigned char x, unsigned char string[]);
extern void digital_display(int time);
extern void digital_display_init();
extern void lcd_init();
extern void digital_display(int time);
extern int set_time();
extern void count_time(int time, int order);

// ��������
/** �����ַ��� **/
const unsigned char code str_title[] = {"Multi-Function Clock"}; // ����
const unsigned char code str_forward[] = {"Key 8: forward"};     // ����ʱ
const unsigned char code str_backward[] = {"Key 7: backward"};   // ����ʱ
const unsigned char code str_set_time[] = {"Please set time"};   // ����ʱ��
const unsigned char code str_confirm[] = {"Key 6: confirm"};     // ȷ��

/** �������� **/
sbit forward_btn = P2 ^ 7;  //key8
sbit backward_btn = P2 ^ 6; //key7
sbit confirm_btn = P2 ^ 5;  //key6
sbit reset_btn = P2 ^ 4;    //key5 (����Ҫ���ʵ��)
sbit t2_btn = P2 ^ 1;       //key2
sbit t1_btn = P2 ^ 0;       //key1

/**
 * @brief ��ʼ��������λ ??? ����û��
 * 
 */
void buttons_init()
{
  forward_btn = 0;
  backward_btn = 0;
  confirm_btn = 0;
  t2_btn = 0;
  t1_btn = 0;
}

/**
 * @brief ��ʼ������ʼ״̬
 * 
 */
void init_all()
{
  delay(15);              //����ʱ
  lcd_init();             //��ʼ��LCD
  buttons_init();         //��ʼ������
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
  int realtime;
  init_all();

  while (1) // ��ʼѭ��״̬
  {
    realtime = 0;
    if (forward_btn == 1) // ��������ʱ����
    {
      lcd_init();                         // ����
      display_string(0, 0, str_set_time); //��ʾ����ʱ����ʾ
      display_string(1, 0, str_confirm);  //��ʾȷ����ʾ

      realtime = set_time();   //����ʱ�䣬�ȴ�ȷ��
      count_time(realtime, 1); //��ʼ����ʱ
      //TODO  �������
      init_all();
    }

    if (backward_btn == 1) // ���µ���ʱ����
    {
      lcd_init();                         // ����
      display_string(0, 0, str_set_time); //��ʾ����ʱ����ʾ
      display_string(1, 0, str_confirm);  //��ʾȷ����ʾ

      realtime = set_time();    //����ʱ�䣬�ȴ�ȷ��
      count_time(realtime, -1); //��ʼ����ʱ
      //TODO  �������
      init_all();
    }
  }
}
