#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

void array_display(int32_t* array_p, int32_t array_size);

int main() {
	int32_t numbers[10] = { 11,22,33,44,55,66,77,88,99,100 };
	size_t numbers_size = sizeof(numbers) / sizeof(int32_t);
	int32_t* ptr = numbers;
	array_display(numbers, numbers_size);
	
	return 0;
};
/*以array = { element element element……}的形式输出数组
*
*/
void array_display(int32_t *array_p,int32_t array_size) {

	printf("numbers = { ");
	for (int index = 0; index < array_size; ++index) {
		printf("%" PRId32 " ", *(array_p + index));
	}
	printf(" }\n");
}