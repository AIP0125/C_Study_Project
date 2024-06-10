#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
//在实际项目中很少直接使用基本的%d，%hd等等，为了提高可读性，通常情况下，我们会为数据类型输出定义一个统一的标准来使用；inttypes.h头文件就为我们提供了更直观的表示
int main() {

	int8_t firstNumber = INT8_MAX;
	int32_t secondNumber = INT32_MAX;
	uint64_t thirdNumber = UINT64_MAX;

	printf("int8_t : %" PRId8 "\n", firstNumber);
	printf("int8_t : %" PRId32 "\n", secondNumber);
	printf("int8_t : %" PRIu64 "\n", thirdNumber);

	return 0;
}