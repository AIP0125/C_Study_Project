#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
//��ʵ����Ŀ�к���ֱ��ʹ�û�����%d��%hd�ȵȣ�Ϊ����߿ɶ��ԣ�ͨ������£����ǻ�Ϊ���������������һ��ͳһ�ı�׼��ʹ�ã�inttypes.hͷ�ļ���Ϊ�����ṩ�˸�ֱ�۵ı�ʾ
int main() {

	int8_t firstNumber = INT8_MAX;
	int32_t secondNumber = INT32_MAX;
	uint64_t thirdNumber = UINT64_MAX;

	int_least8_t minNumber = 102;//least�����ж����ֽڣ�����չ
	int_fast8_t fastNumber = 20;//������8�ֽڵ�������,������ռ�ݵĿռ��Դﵽ���������ٶ�
	
	printf("int8_t : %" PRId8 "\n", firstNumber);
	printf("int8_t : %" PRId32 "\n", secondNumber);
	printf("int8_t : %" PRIu64 "\n", thirdNumber);

	return 0;
}