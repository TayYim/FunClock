#include <reg51.h>
#include <string.h> //�����ַ���������ȡ������ĸ������õ�;����strlen����

// ��������
/** �����ַ��� **/
const unsigned char code str_title[] = {"Multi-Function Clock"}; // ����
const unsigned char code str_forward[] = {"Key 8: forward"};     // ����ʱ
const unsigned char code str_backward[] = {"Key 7: backward"};   // ����ʱ
const unsigned char code str_set_time[] = {"Please set time"};   // ����ʱ��
const unsigned char code str_confirm[] = {"Key 6: confirm"};     // ȷ��

/** ���� **/
const int SECOND_PARAM = 120;

//���¶�������������ŵ�����
sbit rs = P1 ^ 0; //�ض���,rs��ƽΪ1��������,Ϊ0��ת��ָ��
sbit rw = P1 ^ 1; //����LCD������д;Ϊ1���LCD,Ϊ0��д��LCD
sbit en = P1 ^ 2; //LCD�ж�����,ENΪ�½����򽻻�ִ��,��EN = 1;����EN = 0;

/** �������� **/
sbit forward_btn = P2 ^ 7;  //key8
sbit backward_btn = P2 ^ 6; //key7
sbit confirm_btn = P2 ^ 5;  //key6
sbit reset_btn = P2 ^ 4;    //key5 (����Ҫ���ʵ��)
sbit t2_btn = P2 ^ 1;       //key2
sbit t1_btn = P2 ^ 0;       //key1

/**
 * @brief ��ʱ����
 * 
 * @param i 
 */
void delay(int i)
{
  int t;                      //�������α��� ����t
  for (; i >= 1; i--)         //ѭ�� (�պ���; �ж�i�Ƿ���ڻ����1; i��1<�Լ�>) i��ֵ�ǵ��ô˺���ʱ�趨��
  {                           //��i��ֵ���ڻ����1;���������һ��ѭ��
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
    ;     //ѭ�� (���P0��0x80��ȵĻ�) P0 & 0x80����,��P0���ߵ�8λ����������10000000�Ƚ�,
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
  if (i) //��� (i��ֵΪ1<��>)
  {
    j = j + 0x40; //�ڶ�����ʼ��ַ��������Ϊ�ַ���ʾ��ַ //���j��0x40���ֵ����j;;��ͬ��j += 0x40        ,
  }
  j = j + 0x80;    //ͬ��,0x80ָ��һ�����еĵ�ַ,��if�����Ч, ������j=  �ڶ�������ĸ�ĵ�ַ
  ddata(0, j);     //������ (ָ��, ����)
  ddata(1, DDATA); //������ (����, ����)
}

/**
 * @brief ��ʾ�ַ���
 * 
 * @param y 
 * @param x 
 * @param shuzu0 
 */
void display_string(unsigned char y, unsigned char x, unsigned char shuzu0[]) //������ ��������
{
  unsigned char j;        //��������
  unsigned char i;        //��������
  int k = 1;              //�������β���k����ֵΪ1
  i = 0;                  //i��ֵΪ0
  j = strlen(shuzu0) + x; //j = ȡ�����������x<����λ��>��ֵ,����j��ֵΪ���������һλ�ַ�����,j����ֵ��0~15֮��

  for (; k > 0;)                     //ѭ�� (��; ���k����0;��)                                                                        !
  {                                  //��                                                                                                                        !
                                     //�ж�                                                                                                                ! ���м� "!" ��ע�Ĵ������ѹ��Ϊ:
    if (x < j)                       //��� (��ǰ��ʾ����x < ���һλ�ַ�������j)                                        ! while (x < j)
    {                                //��                                                                                                                        ! {
      display_char(y, x, shuzu0[i]); //������ (��y<0��1>�ͳ�, ��x<0~15>�ͳ�, ����[��iλ]�ͳ�)                !         display (y, x, shuzu0[i]);
      x++;                           //������1                                                                                                        !         x++;
      i++;                           //�����iλ��1                                                                                                !         i++;
    }                                //                                                                                                        !  }
    else                             //����                                                                                                                !
    {                                //                                                                                                        !
      k = 0;                         //k ��0,  forѭ���˳�                                                                                !
    }
  }
}

/**
 * @brief ��ʼ��������λ
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
 * @brief ��ʾָ��������
 * 
 * @param time ��ʱʱ�䣨��λ+ʮλ*16��
 */
void digital_display(int time)
{
  P3 = time;
}

/**
 * @brief ��ʼ������ܣ���ʾ00
 * 
 */
void digital_display_init()
{
  digital_display(0);
}

/**
 * @brief Set the time object
 * 
 * @return int ��ʱʱ�䣨��λ+ʮλ*16��
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
      digital_display(t1_count + 16 * t2_count); //ˢ����ʾ
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
      digital_display(t1_count + 16 * t2_count); //ˢ����ʾ
    }

    /* ����ȷ�ϰ������˳����� */
    if (confirm_btn == 1)
    {
      break;
    }
  }
  return t1_count + 16 * t2_count;
}

/**
 * @brief ��ʱ    
 * 
 * @param time ��ʱʱ�䣨��λ+ʮλ*16��
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
    curr_time == -1; //����ʱ
  }

  delay(15);
  digital_display(curr_time); //��ʾ��ʼֵ

  for (i = 0; i <= time; i++)
  {
    delay_second();             //�ȴ�1s
    curr_time += i * order;     //ʱ����� or �ݼ�
    digital_display(curr_time); //�����������ʾ
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
  int time;
  init_all();

  while (1) // ��ʼѭ��״̬
  {
    time = 0;
    if (forward_btn == 1) // ��������ʱ����
    {
      lcd_init();                         // ����
      display_string(0, 0, str_set_time); //��ʾ����ʱ����ʾ
      display_string(1, 0, str_confirm);  //��ʾȷ����ʾ

      time = set_time();   //����ʱ�䣬�ȴ�ȷ��
      count_time(time, 1); //��ʼ����ʱ
      //TODO  �������
      init_all();
    }

    if (backward_btn == 1) // ���µ���ʱ����
    {
      lcd_init();                         // ����
      display_string(0, 0, str_set_time); //��ʾ����ʱ����ʾ
      display_string(1, 0, str_confirm);  //��ʾȷ����ʾ

      time = set_time();    //����ʱ�䣬�ȴ�ȷ��
      count_time(time, -1); //��ʼ����ʱ
      //TODO  �������
      init_all();
    }
  }
}
