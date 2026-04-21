#include "lcd1602.h"
#include "delay.h"

static void LCD_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟
	

	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;//选择工作频率
	GPIO_Init( GPIOC, &GPIO_InitStructure );

	
	// PD0-8
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;//选择工作频率
	GPIO_Init( GPIOD, &GPIO_InitStructure );
	
}



//向GPIOD的低8位写入8位数据  接线从第几位开始就向左移几位
static void Write_Byte(u8 data)
{
	GPIO_Write(GPIOD,data);//写操作最小的建立时间为40ns
	delay_ms(10);
}


//LCD写命令
static void LCD_Write_Command(u8 cmd)
{
	//配置写入命令
	Clr_RS;
	delay_ms(10);
	Clr_RW;
	delay_ms(10);
	Set_EN;
	delay_ms(10);
	
	//写入命令操作
	
	Write_Byte(cmd);//写完操作最小延迟10ns
	delay_ms(5);
	
	//写入完毕  拉低功能引脚
	Clr_EN;
}

//LCD写数据
static void LCD_Write_Data(u8 dat)
{
	//配置写入数据
	Set_RS;
	delay_ms(10);
	Clr_RW;
	delay_ms(10);
	Set_EN;
	delay_ms(10);
	
	//写入命令操作
	
	Write_Byte(dat);//写完操作最小延迟10ns
	delay_ms(5);
	
	//写入完毕  拉低功能引脚
	Clr_EN;
}
	
//LCD初始化
void LCD_Init(void)
{
	LCD_GPIO_Init();//初始化GPIO
	
	LCD_Write_Command(0x38);	//工作方式设置（8位数据接口，两行显示，5*8点阵）
	delay_ms(5);
	
	LCD_Write_Command(0x0C);	//显示开关控制指令设置（显示开+光标不显示+光标不闪烁）
	delay_ms(5);
	/*
	0x0E显示开+光标显示+光标不闪烁
	0x0F显示开+光标显示+光标闪烁
	*/
	
	LCD_Write_Command(0x06);	//光标模式设置指令（写入数据后光标右移 显示不移动）
	delay_ms(5);
	/*
	0x07写入数据后右移+显示移动
	0x05左移+显示移动
	0x04左移+显示不移动
	*/
	
	LCD_Write_Command(0x01);	//清屏设置
	delay_ms(5);
	
	//LCD_Write_Command(0x02);//光标归为  返回屏幕左上角  不改变屏幕显示内容

}

//清屏函数
void LCD_Clear(void)
{
	LCD_Write_Command(0x01);
	delay_ms(5);
}

//设置光标坐标
void Set_Cursor(unsigned char Line,unsigned char Column)
{
	if(Line==1)
	{
		LCD_Write_Command(0x80|(Column-1));
	}
	else if(Line==2)
	{
		LCD_Write_Command(0x80|(Column-1+0x40));
	}
}

//显示字符串
void LCD_Display_Str(u8 x,u8 y,char *str)
{
	Set_Cursor(x,y);
	
	while(*str != '\0')
	{
		LCD_Write_Data(*str++);
	}
}

//显示字符函数
void LCD_Display_Char(u8 x,u8 y,char dat)
{
	Set_Cursor(x,y);
	LCD_Write_Data(dat);
}

//长数据滚动显示
/*
@str：要显示的数据
@RL： 0：向左滚动   非零：向右移动
*/
void LCD_RunDisplay(u8 x,u8 y,u8 *str,u8 RL)
{
	if(RL==0)
	{
		LCD_Write_Command(0x18);
	}
	else
		
		LCD_Write_Command(0x1C);
	
	Set_Cursor(x,y);
	
	while(*str != '\0')
	{
		LCD_Write_Data(*str++);
	}
}

