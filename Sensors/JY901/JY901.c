#include "JY901.h"
#include <string.h>

struct SGyro 		JY901_Gyro;
struct SAngle 	JY901_Angle;

void GetDataFromJY901(unsigned char ucData)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	
	ucRxBuffer[ucRxCnt++]=ucData;
	
	if (ucRxBuffer[0]!=0x55) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) { return;}//���ݲ���11�����򷵻�
	else
	{
		switch(ucRxBuffer[1])
		{
			case 0x52:	JY901_Gyro.w[0]=((short)ucRxBuffer[3]<<8|ucRxBuffer[2]);    //   ������
			            JY901_Gyro.w[1]=((short)ucRxBuffer[5]<<8|ucRxBuffer[4]);    //   ��ת��
									JY901_Gyro.w[2]=((short)ucRxBuffer[7]<<8|ucRxBuffer[6]);    //   ƫ����
									break;
			case 0x53:	JY901_Angle.Angle[0]=((short)ucRxBuffer[3]<<8|ucRxBuffer[2]);    //  ������
			            JY901_Angle.Angle[1]=((short)ucRxBuffer[5]<<8|ucRxBuffer[4]);    //  ��ת��
									JY901_Angle.Angle[2]=((short)ucRxBuffer[7]<<8|ucRxBuffer[6]);    //  ƫ����
									break;
		}
		ucRxCnt=0;
	}
}


