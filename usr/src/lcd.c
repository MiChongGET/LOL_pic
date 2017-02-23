#include "includes.h"



/********************************************************************
* Function��   lcd_port_init
* Description: ��ʼ��lcd����
* Input��  ��
* Output�� ��
* Return : ��
* Author:  XYD
* Others:  �����������Ҫ���òſ���������LCD

*********************************************************************/
void lcd_port_init(void)
{
	//1��������ʱ�� PD PE PG PB
	RCC->APB2ENR |= (1<<5);//��PD
	RCC->APB2ENR |= (1<<6);//��PE
	RCC->APB2ENR |= (1<<8);//��PG
	RCC->APB2ENR |= (1<<3);//��PB
	//2����������
	// �����ߣ�-----�������  ʱ��50M
	// DB0---PD14
	// DB1---PD15
	GPIOD->CRH &= 0X00FFFFFF;
	GPIOD->CRH |= 0X33000000;
	// DB2---PD0
	// DB3---PD1
	GPIOD->CRL &= 0XFFFFFF00;
	GPIOD->CRL |= 0X00000033;
	// DB4---PE7
	GPIOE->CRL &= 0X0FFFFFFF;
	GPIOE->CRL |= 0X30000000;	
	// DB5---PE8
	// DB6---PE9
	// DB7---PE10
	// DB8---PE11
	// DB9---PE12
	// DB10---PE13
	// DB11---PE14
	// DB12---PE15
	GPIOE->CRH &= 0X00000000;
	GPIOE->CRH |= 0X33333333;
	// DB13---PD8
	// DB14---PD9
	// DB15---PD10
	GPIOD->CRH &= 0XFFFFF000;
	GPIOD->CRH |= 0X00000333;
	// �����ߣ�-----�������  ʱ��50M ����Ϊ�ߵ�ƽ
	// WR��PD5
	// RD��PD4
	GPIOD->CRL &= 0XFF00FFFF;
	GPIOD->CRL |= 0X00110000;
	GPIOD->ODR |= (0X3<<4);
	// CE��PG12
	GPIOG->CRH &= ~(0XF<<(12-8)*4);
	GPIOG->CRH |= (0X1<<(12-8)*4);
	GPIOG->ODR |= (0X1<<12);
	// RS��PG0
	GPIOG->CRL &= ~(0XF<<0*4);
	GPIOG->CRL |= (0X1<<0*4);	
	GPIOG->ODR |= (0X1<<0);
	//LCD�ı��� BL--PB0 1��  ������
	GPIOB->CRL &= ~(0XF<<0*4);
	GPIOB->CRL |= (0X2<<0*4);	
	GPIOB->ODR &= ~(0X1<<0);//�رձ��⣬��LCD��ʼ������ٴ�
}


/********************************************************************
* Function��   lcd_output_data
* Description: ��LCD8080���������������
* Input��  ��
* Output�� ��
* Return : ��
* Author:  XYD
* Others:  ��Ϊ�������ݽţ���û�н���ͬһ���˿ڶ��ǽӵ�Ӳ��FSMC��������ȥ��
           �����������ģ��8080ʱ�򣬲���ֱ�Ӹ�ֵ
*********************************************************************/
void lcd_output_data(u16 data)
{
	// DB0---PD14
	// DB1---PD15
	//GPIOD->BSRR |= (1<<14);---ר���������1  д1���1
	//GPIOD->BRR |= (1<<15);---ר���������0  д1���0
	if(data&(1<<0)) GPIOD->BSRR |= (1<<14);
	else GPIOD->BRR |= (1<<14);
	if(data&(1<<1)) GPIOD->BSRR |= (1<<15);
	else GPIOD->BRR |= (1<<15);
	// DB2---PD0
	// DB3---PD1	
	if(data&(1<<2)) GPIOD->BSRR |= (1<<0);
	else GPIOD->BRR |= (1<<0);
	if(data&(1<<3)) GPIOD->BSRR |= (1<<1);
	else GPIOD->BRR |= (1<<1);	
	// DB4---PE7	
	if(data&(1<<4)) GPIOE->BSRR |= (1<<7);
	else GPIOE->BRR |= (1<<7);		
	// DB5---PE8
	// DB6---PE9
	// DB7---PE10
	// DB8---PE11
	// DB9---PE12
	// DB10---PE13
	// DB11---PE14
	// DB12---PE15
	if(data&(1<<5)) GPIOE->BSRR |= (1<<8);
	else GPIOE->BRR |= (1<<8);	
	if(data&(1<<6)) GPIOE->BSRR |= (1<<9);
	else GPIOE->BRR |= (1<<9);	
	if(data&(1<<7)) GPIOE->BSRR |= (1<<10);
	else GPIOE->BRR |= (1<<10);	
	if(data&(1<<8)) GPIOE->BSRR |= (1<<11);
	else GPIOE->BRR |= (1<<11);	
	if(data&(1<<9)) GPIOE->BSRR |= (1<<12);
	else GPIOE->BRR |= (1<<12);	
	if(data&(1<<10)) GPIOE->BSRR |= (1<<13);
	else GPIOE->BRR |= (1<<13);	
	if(data&(1<<11)) GPIOE->BSRR |= (1<<14);
	else GPIOE->BRR |= (1<<14);	
	if(data&(1<<12)) GPIOE->BSRR |= (1<<15);
	else GPIOE->BRR |= (1<<15);	
	// DB13---PD8
	// DB14---PD9
	// DB15---PD10
	if(data&(1<<13)) GPIOD->BSRR |= (1<<8);
	else GPIOD->BRR |= (1<<8);
	if(data&(1<<14)) GPIOD->BSRR |= (1<<9);
	else GPIOD->BRR |= (1<<9);	
	if(data&(1<<15)) GPIOD->BSRR |= (1<<10);
	else GPIOD->BRR |= (1<<10);		
}

/********************************************************************
* Function��   LCD_ILI9341_CMD
* Description: LCDд�����
* Input��  cmd--Ҫд������
* Output�� ��
* Return : ��
* Author:  XYD
* Others:  ��
*********************************************************************/
void LCD_ILI9341_CMD(u16 cmd)
{
	GPIOG->ODR &= ~(1<<0); //D/C = 0;//����
	GPIOG->ODR &= ~(1<<12);//CS = 0;
	GPIOD->ODR &= ~(1<<5); //WR = 0;
	
	lcd_output_data(cmd);
	GPIOD->ODR |=  (1<<5); //WR = 1;
	GPIOG->ODR |=  (1<<12);//CS = 1;
}

/********************************************************************
* Function��   LCD_ILI9341_Parameter
* Description: LCDд���ݺ���
* Input��  data--Ҫд������
* Output�� ��
* Return : ��
* Author:  XYD
* Others:  ��

*********************************************************************/
void LCD_ILI9341_Parameter(u16 data)
{
	GPIOG->ODR |=  (1<<0); //D/C = 1;//����
	GPIOG->ODR &= ~(1<<12);//CS = 0;
	GPIOD->ODR &= ~(1<<5); //WR = 0;
	
	lcd_output_data(data);
	GPIOD->ODR |=  (1<<5); //WR = 1;
	GPIOG->ODR |=  (1<<12);//CS = 1;	
}

/********************************************************************
* Function��   lcd_init
* Description: LCD��������ʼ������
* Input��  ��
* Output�� ��
* Return : ��
* Author:  XYD
* Others:  ��ʼ��������LCD�����ṩ

*********************************************************************/
void LCD_init(void)
{
	lcd_port_init();//��ʼ������
	
	
	//************* Start Initial Sequence **********//
	LCD_ILI9341_CMD(0xCF);
	LCD_ILI9341_Parameter (0x00);
	LCD_ILI9341_Parameter (0x83);
	LCD_ILI9341_Parameter (0X30);
	LCD_ILI9341_CMD(0xED);
	LCD_ILI9341_Parameter (0x64);
	LCD_ILI9341_Parameter (0x03);
	LCD_ILI9341_Parameter (0X12);
	LCD_ILI9341_Parameter (0X81);
	LCD_ILI9341_CMD(0xE8);
	LCD_ILI9341_Parameter (0x85);
	LCD_ILI9341_Parameter (0x01);
	LCD_ILI9341_Parameter (0x79);
	LCD_ILI9341_CMD(0xCB);
	LCD_ILI9341_Parameter (0x39);
	LCD_ILI9341_Parameter (0x2C);
	LCD_ILI9341_Parameter (0x00);
	LCD_ILI9341_Parameter (0x34);
	LCD_ILI9341_Parameter (0x02);
	LCD_ILI9341_CMD(0xF7);
	LCD_ILI9341_Parameter (0x20);

	LCD_ILI9341_CMD(0xEA);
	LCD_ILI9341_Parameter (0x00);
	LCD_ILI9341_Parameter (0x00);
	LCD_ILI9341_CMD(0xC0); //Power control
	LCD_ILI9341_Parameter (0x1D); //VRH[5:0]
	LCD_ILI9341_CMD(0xC1); //Power control
	LCD_ILI9341_Parameter (0x11); //SAP[2:0];BT[3:0]
	LCD_ILI9341_CMD(0xC5); //VCM control
	LCD_ILI9341_Parameter (0x33);
	LCD_ILI9341_Parameter (0x34);
	LCD_ILI9341_CMD(0xC7); //VCM control2
	LCD_ILI9341_Parameter (0Xbe);
	LCD_ILI9341_CMD(0x36); // Memory Access Control
	LCD_ILI9341_Parameter (0x00);
	LCD_ILI9341_CMD(0xB1);
	LCD_ILI9341_Parameter (0x00);
	LCD_ILI9341_Parameter (0x1B);
	LCD_ILI9341_CMD(0xB6); // Display Function Control
	LCD_ILI9341_Parameter (0x0A);
	LCD_ILI9341_Parameter (0xA2);
	LCD_ILI9341_CMD(0xF2); // 3Gamma Function Disable
	LCD_ILI9341_Parameter (0x00);
	LCD_ILI9341_CMD(0x26); //Gamma curve selected
	LCD_ILI9341_Parameter (0x01);
	LCD_ILI9341_CMD(0xE0); //Set Gamma
	LCD_ILI9341_Parameter (0x0F);
	LCD_ILI9341_Parameter (0x23);
	LCD_ILI9341_Parameter (0x1F);

	LCD_ILI9341_Parameter (0x09);
	LCD_ILI9341_Parameter (0x0f);
	LCD_ILI9341_Parameter (0x08);
	LCD_ILI9341_Parameter (0x4B);
	LCD_ILI9341_Parameter (0Xf2);
	LCD_ILI9341_Parameter (0x38);
	LCD_ILI9341_Parameter (0x09);
	LCD_ILI9341_Parameter (0x13);
	LCD_ILI9341_Parameter (0x03);
	LCD_ILI9341_Parameter (0x12);
	LCD_ILI9341_Parameter (0x07);
	LCD_ILI9341_Parameter (0x04);
	LCD_ILI9341_CMD(0XE1); //Set Gamma
	LCD_ILI9341_Parameter (0x00);
	LCD_ILI9341_Parameter (0x1d);
	LCD_ILI9341_Parameter (0x20);
	LCD_ILI9341_Parameter (0x02);
	LCD_ILI9341_Parameter (0x11);
	LCD_ILI9341_Parameter (0x07);
	LCD_ILI9341_Parameter (0x34);
	LCD_ILI9341_Parameter (0x81);
	LCD_ILI9341_Parameter (0x46);
	LCD_ILI9341_Parameter (0x06);
	LCD_ILI9341_Parameter (0x0e);
	LCD_ILI9341_Parameter (0x0c);
	LCD_ILI9341_Parameter (0x32);
	LCD_ILI9341_Parameter (0x38);
	LCD_ILI9341_Parameter (0x0F);
	
  /* ��������� */
	LCD_ILI9341_CMD(0X3A); //�趨16BPP
	LCD_ILI9341_Parameter(0X55);
	//�˳�˯��״̬
	LCD_ILI9341_CMD(0x11); // Sleep out
	Delay_ms(120);
	LCD_ILI9341_CMD(0x29); // Display on
	
  LCD_clear(0xffff);//��LCD��ɰ���
   
	GPIOB->ODR |=  (0X1<<0);//��������
	
}


/*
��������LCD_Dispaly_Point
����������u16 x u16 y   u16 color
          Ҫ��ʾ������   ��ɫ
��������ֵ����
�������ܣ�ʵ��LCD����
*/
void LCD_Display_Point(u16 x,u16 y,u16 color)
{
	//2A  x���� ������
	LCD_ILI9341_CMD(0X2A); 
	LCD_ILI9341_Parameter(x>>8);//��ʼx����
	LCD_ILI9341_Parameter(x);
	LCD_ILI9341_Parameter(x>>8);//��ֹx����
	LCD_ILI9341_Parameter(x);
	//2B  y���� ������
	LCD_ILI9341_CMD(0X2B); 
	LCD_ILI9341_Parameter(y>>8);//��ʼy����
	LCD_ILI9341_Parameter(y);
	LCD_ILI9341_Parameter(y>>8);
	LCD_ILI9341_Parameter(y);
	//2C  ��ɫֵ
	LCD_ILI9341_CMD(0X2C); 
	LCD_ILI9341_Parameter(color);
	
}

/*
��������LCD_clear
����������    u16 color
             ��ɫ
��������ֵ����
�������ܣ�ʵ��LCD����
*/
void LCD_clear(u16 color)
{
	u32 i;
	//2A  x���� ������
	LCD_ILI9341_CMD(0X2A); 
	LCD_ILI9341_Parameter(0>>8);//��ʼx����
	LCD_ILI9341_Parameter(0);
	LCD_ILI9341_Parameter(319>>8);//��ֹx����
	LCD_ILI9341_Parameter(319);
	//2B  y���� ������
	LCD_ILI9341_CMD(0X2B); 
	LCD_ILI9341_Parameter(0>>8);//��ʼy����
	LCD_ILI9341_Parameter(0);
	LCD_ILI9341_Parameter(479>>8);
	LCD_ILI9341_Parameter(479);
	//2C  ��ɫֵ
	LCD_ILI9341_CMD(0X2C); 
	for(i=0;i<320*480;i++)
	{
	 LCD_ILI9341_Parameter(color);
	}
		
}

/*
������;LCD_Dishz
���������� u16 x u16 y  u16 color u16 backcolor  const u8 *str
            ��ʼ����    ������ɫ    ������ɫ        ���ֵ�����ָ��
��������ֵ:��
�������ܣ���LCD������������ʾ16*16�����ص�ĺ���
*/
void LCD_Dishz(u16 x,u16 y,u16 color,u16 backcolor,const u8 *str)
{
	u8 i,j;
	u16 temp;//��ʾһ�е�ȡģֵ
	// 2A  X���� 
	LCD_ILI9341_CMD(0X2A); 
	LCD_ILI9341_Parameter(x>>8);//��ʼx����
	LCD_ILI9341_Parameter(x);
	LCD_ILI9341_Parameter((x+15)>>8);//��ֹx����
	LCD_ILI9341_Parameter((x+15));
	
	//2B y ����
	LCD_ILI9341_CMD(0X2B); 
	LCD_ILI9341_Parameter(y>>8);//��ʼx����
	LCD_ILI9341_Parameter(y);
	LCD_ILI9341_Parameter((y+15)>>8);//��ֹx����
	LCD_ILI9341_Parameter((y+15));
	
	// 2C ��ɫ
	LCD_ILI9341_CMD(0X2C);
	for(i=0;i<16;i++)//16��
	{
		temp =str[2*i] <<8 |str[2*i+1];//ÿһ��
		for(j=0;j<16;j++)
		{
			if(temp &(0x8000>>j)) //������ɫ
			{
				LCD_ILI9341_Parameter(color);
			}
			else //������ɫ
			{
				LCD_ILI9341_Parameter(backcolor);
			}
		}
	}
	
}



/*
������;LCD_Dis24X24hz
���������� u16 x u16 y  u16 color u16 backcolor  const u8 *str
            ��ʼ����    ������ɫ    ������ɫ        ���ֵ�����ָ��
��������ֵ:��
�������ܣ���LCD������������ʾ24*24�����ص�ĺ���
*/
void LCD_Dis24X24hz(u16 x,u16 y,u16 color,u16 backcolor,const u8 *str)
{
	u8 i,j;
	u32 temp;//��ʾһ�е�ȡģֵ
	// 2A  X���� 
	LCD_ILI9341_CMD(0X2A); 
	LCD_ILI9341_Parameter(x>>8);//��ʼx����
	LCD_ILI9341_Parameter(x);
	LCD_ILI9341_Parameter((x+23)>>8);//��ֹx����
	LCD_ILI9341_Parameter((x+23));
	
	//2B y ����
	LCD_ILI9341_CMD(0X2B); 
	LCD_ILI9341_Parameter(y>>8);//��ʼx����
	LCD_ILI9341_Parameter(y);
	LCD_ILI9341_Parameter((y+23)>>8);//��ֹx����
	LCD_ILI9341_Parameter((y+23));
	
	// 2C ��ɫ
	LCD_ILI9341_CMD(0X2C);
	for(i=0;i<24;i++)//16��
	{
		temp =str[3*i] <<16 |str[3*i+1]<<8 |str[3*i+2];//ÿһ��
		for(j=0;j<24;j++)
		{
			if(temp &(0x800000>>j)) //������ɫ
			{
				LCD_ILI9341_Parameter(color);
			}
			else //������ɫ
			{
				LCD_ILI9341_Parameter(backcolor);
			}
		}
	}
	
}

/*
������;LCD_Pic
����������u16 x u16 y  u16 width u16 high const u8 *str
           ͼƬ��ʼ����  ��       ��        ͼƬ����ָ��
��������ֵ����
�������ܣ���ʾһ��ͼƬ
*/
void LCD_Pic(u16 x,u16 y,u16 width,u16 high,const u8 *str)
{
	u16 i,j;
	u16 color;
	//2A  X����
	LCD_ILI9341_CMD(0X2A); 
	LCD_ILI9341_Parameter(x>>8);//��ʼx����
	LCD_ILI9341_Parameter(x);
	LCD_ILI9341_Parameter((x+width-1)>>8);//��ֹx����
	LCD_ILI9341_Parameter((x+width-1));
	// 2B Y����
	LCD_ILI9341_CMD(0X2B); 
	LCD_ILI9341_Parameter(y>>8);//��ʼx����
	LCD_ILI9341_Parameter(y);
	LCD_ILI9341_Parameter((y+high-1)>>8);//��ֹx����
	LCD_ILI9341_Parameter((y+high-1));
	// 2C ��ɫ
	LCD_ILI9341_CMD(0X2C);
	for(i=0;i<high;i++)//��
	{
		for(j=0;j<width;j++)//��
		{
		 color =str[width*2*i+j*2] |str[width*2*i+j*2+1]<<8;
			LCD_ILI9341_Parameter(color);
		}
	}
}






