#include <stdio.h>
#include <inttypes.h>							//�ṩ��������ĸ���ת����
#include <stdint.h>			
#include <stdbool.h>							//bool���͵�ʹ����Ҫ���������

void printf_binary(uint8_t number);

int main() {
	//1.>>λ����Ļ�������
	//<<����nλ�൱��*2��n�η��������൱������2��n�η�
	//ֱ��ʹ��λ����Ҫ�ȳ˳��������
	uint8_t first_number = 0b00001101;
	printf("first_number :%" PRIu32 "\n", first_number);
	uint8_t second_number = first_number >> 2;	//second_number = 0b00000011
	printf("second_number :%" PRIu32 "\n", second_number);

	//2.bool���͵�ʹ��
	bool equal = first_number == second_number; 
	//�������ʽ����ֵΪbool���ͣ����ڴ��б�ʾΪ0��1

	//3.��λ���롱���㣺& ��ȫΪ1ʱ = 1��
		//0 & 0 = 0
		//0 & 1 = 0
		//1 & 1 = 1
	//����ض�λ״̬��0/1
	//��һ���ض�λ����Ϊ0
	uint8_t switch_number = 0b00101101;
	uint8_t mask_check = 0b11111111;							//��ȡswich_number״̬������
	uint8_t mark_setting_0 = 0b11111110;						//�������һλ����Ϊ0������
	uint8_t aftercheck_number = 0b00000000;						//�����������
	uint8_t aftersetting_0_number = 0b00000000;					//����������ý��
	aftercheck_number = switch_number & mask_check;
	aftersetting_0_number = switch_number & mark_setting_0;
	printf("switch_number = 00101101\naftercheck_number = ");	//��������
	printf_binary(aftercheck_number);
	printf("aftersetting_0_number = ");
	printf_binary(aftersetting_0_number);
	//4.��λ�������㣺| ����һ��Ϊ1 = 1��
		//0 | 0 = 0
		//0 | 1 = 1
		//1 | 1 = 1
	//���ض�λ����Ϊ1
	uint8_t mark_setting_1 = 0b00010000;						//������4λ����Ϊ1������
	uint8_t aftersetting_1_number = 0b00000000;
	aftersetting_1_number = switch_number | mark_setting_1;
	printf("aftersetting_1_number = ");
	printf_binary(aftersetting_1_number);
	//5.��λ��������㣺^
		//0 ^ 0 = 0
		//0 ^ 1 = 1
		//1 ^ 1 = 0
	//������������:ʱ�任�ռ䣬�����淽���ǿռ任ʱ�䣬�������м�����ķ���
	int	a = 12;
	int b = 3;
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
	printf("a = %d\nb = %d", a, b);
	//��ת����
	//���������ͬ��λ

	//6.ȡ����~
	return 0;
}

//�˺������Խ�number�Զ��������
void printf_binary(uint8_t number) {
	for (int index = 7; index >= 0; index--) {
		printf("%d", (number >> index) & 1);
	}
	putchar('\n');
}
