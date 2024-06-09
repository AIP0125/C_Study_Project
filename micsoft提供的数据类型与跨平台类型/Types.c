#include <stdio.h>
#include <stdint.h>
int main() {
	//微软提供了windows下可运行的 __int16,__int8,__int32……
	__int16 number_1 = 100;
	printf("number_1 = : %d", number_1);

	//跨平台数据类型 引入stdint.h
	int16_t max_16 = 32767;//int16 type
	int32_t max_32 = 2147483647;
	int64_t max_64 = 922337036854775807LL;
	uint16_t max_u16 = 65535;
	uint32_t max_u32 = 4294967295U;
	uint64_t max_u64 = 18446744073709551615ULL;
	printf("size of int16_t: %zu byte(s),value = %hd\n", sizeof(int16_t), max_16);
	printf("size of int32_t: %zu byte(s),value = %d\n", sizeof(int32_t), max_32);
	printf("size of int64_t: %zu byte(s),value = %lld\n", sizeof(int64_t), max_64);
	printf("size of uint16_t: %zu byte(s),value = %hu\n", sizeof(uint16_t), max_u16);
	printf("size of uint32_t: %zu byte(s),value = %u\n", sizeof(uint32_t), max_u32);
	printf("size of uint64_t: %zu byte(s),value = %llu\n", sizeof(uint64_t), max_u64);


	return 0;
}