#include "MyMath.h"


/*
 * ������: fsign
 * ��  ��: ȡ���������ķ���λ
 * ��  ��: ������a
 * ��  ��: int�͵ķ���
 * ��  ��: �ⲿ����
 */
int fsign(float a)
{
	if(a>0)
		return 1;
	else if(a<0)
		return -1;
	else return 0;
}
