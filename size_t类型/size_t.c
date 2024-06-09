#include <stdio.h>

/*size_t的全称应该是size type，就是说“一种用来记录大小的数据类
 型”。 通常我们用sizeof(XXX)操作，这个操作所得到的结果就是
size_t类型*/
//sizeof() 使用%zu输出
int main() {
	printf("Size of short : %zu byte(s)\n", sizeof(short));

	printf("Size of int : %zu byte(s)\n", sizeof(int));

	printf("Size of unsigned : %zu byte(s)\n", sizeof(unsigned));

	printf("Size of unsigned long : %zu byte(s)\n", sizeof(unsigned long));

	printf("Size of long long : %zu byte(s)\n", sizeof(long long));
	//在32位平台下，int型和long型是一致的，都是占用4个字节。 long long 是8个字
	// 节。 在64位平台下，int型是占用4个字节，而long和long long都是占用8个字节
	// 的
	return 0;
}

