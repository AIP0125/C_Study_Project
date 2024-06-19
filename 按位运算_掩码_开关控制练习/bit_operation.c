#include <stdio.h>
#include <inttypes.h>							//提供整数输入的各种转换宏
#include <stdint.h>			
#include <stdbool.h>							//bool类型的使用需要引入这个库

void printf_binary(uint8_t number);

int main() {
	//1.>>位运算的基本案例
	//<<左移n位相当于*2的n次方，右移相当于整除2的n次方
	//直接使用位运算要比乘除运算更快
	uint8_t first_number = 0b00001101;
	printf("first_number :%" PRIu32 "\n", first_number);
	uint8_t second_number = first_number >> 2;	//second_number = 0b00000011
	printf("second_number :%" PRIu32 "\n", second_number);

	//2.bool类型的使用
	bool equal = first_number == second_number; 
	//条件表达式返回值为bool类型，在内存中表示为0或1

	//3.按位“与”运算：& （全为1时 = 1）
		//0 & 0 = 0
		//0 & 1 = 0
		//1 & 1 = 1
	//检查特定位状态：0/1
	//将一个特定位设置为0
	uint8_t switch_number = 0b00101101;
	uint8_t mask_check = 0b11111111;							//获取swich_number状态的掩码
	uint8_t mark_setting_0 = 0b11111110;						//若将最后一位设置为0的掩码
	uint8_t aftercheck_number = 0b00000000;						//接收最后检查结果
	uint8_t aftersetting_0_number = 0b00000000;					//接收最后设置结果
	aftercheck_number = switch_number & mask_check;
	aftersetting_0_number = switch_number & mark_setting_0;
	printf("switch_number = 00101101\naftercheck_number = ");	//最后结果输出
	printf_binary(aftercheck_number);
	printf("aftersetting_0_number = ");
	printf_binary(aftersetting_0_number);
	//4.按位“或”运算：| （有一个为1 = 1）
		//0 | 0 = 0
		//0 | 1 = 1
		//1 | 1 = 1
	//将特定位设置为1
	uint8_t mark_setting_1 = 0b00010000;						//若将第4位设置为1的掩码
	uint8_t aftersetting_1_number = 0b00000000;
	aftersetting_1_number = switch_number | mark_setting_1;
	printf("aftersetting_1_number = ");
	printf_binary(aftersetting_1_number);
	//5.按位“异或”运算：^
		//0 ^ 0 = 0
		//0 ^ 1 = 1
		//1 ^ 1 = 0
	//交换两数操作:时间换空间，而常规方法是空间换时间，即定义中间变量的方法
	int	a = 12;
	int b = 3;
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
	printf("a = %d\nb = %d", a, b);
	//反转操作
	//检测两数不同的位

	//6.取反：~
	return 0;
}

//此函数可以将number以二进制输出
void printf_binary(uint8_t number) {
	for (int index = 7; index >= 0; index--) {
		printf("%d", (number >> index) & 1);
	}
	putchar('\n');
}
