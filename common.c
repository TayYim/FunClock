/** 参数 **/
const int SECOND_PARAM = 500;

/**
 * @brief 延时函数
 * 
 * @param i 
 */
void delay(int i)
{
    int t;                        //定义整形变量 名称t
    for (; i >= 1; i--)           //循环 (空函数; 判断i是否大于或等于1; i减1<自减>) i的值是调用此函数时设定的
    {                             //若i的值大于或等于1;则进入下面一个循环
        for (t = 120; t > 1; t--) //循环 (t赋值120; 判断t的值是否大于1; t自减)
        {                         //空函数
        }
    }
}

/**
 * @brief 延时1秒
 * 
 */
void delay_second()
{
    delay(SECOND_PARAM);
}