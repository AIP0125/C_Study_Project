#include <stdio.h>

/*size_t��ȫ��Ӧ����size type������˵��һ��������¼��С��������
 �͡��� ͨ��������sizeof(XXX)����������������õ��Ľ������
size_t����*/
//sizeof() ʹ��%zu���
int main() {
	printf("Size of short : %zu byte(s)\n", sizeof(short));

	printf("Size of int : %zu byte(s)\n", sizeof(int));

	printf("Size of unsigned : %zu byte(s)\n", sizeof(unsigned));

	printf("Size of unsigned long : %zu byte(s)\n", sizeof(unsigned long));

	printf("Size of long long : %zu byte(s)\n", sizeof(long long));
	//��32λƽ̨�£�int�ͺ�long����һ�µģ�����ռ��4���ֽڡ� long long ��8����
	// �ڡ� ��64λƽ̨�£�int����ռ��4���ֽڣ���long��long long����ռ��8���ֽ�
	// ��
	return 0;
}

