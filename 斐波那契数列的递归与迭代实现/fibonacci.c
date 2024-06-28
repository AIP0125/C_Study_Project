#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

//쳲��������еĵ������� �� �ݹ麯������
uint32_t fibonacci_iteration(uint32_t number);//����
uint32_t fibonacci_recursion(uint32_t number);//�ݹ�
uint32_t fibonacci_tail_call(uint32_t number);//β�ݹ�

int main() {
	uint32_t number = 6;
	//�������������������Ӧֵ
	printf("number = %" PRId8 ",fibonacci_iteration = %" PRId32 "\n", number, fibonacci_iteration(number));
	printf("number = %" PRId8 ",fibonacci_recursion = %" PRId32 "\n", number, fibonacci_recursion(number));
	printf("number = %" PRId8 ",fibonacci_tail_call = %" PRId32 "\n", number, fibonacci_tail_call(number));
	return 0;
}


/*������iteration�����ظ��������̵Ļ����Ŀ��ͨ����Ϊ�˽ӽ����ҵ��������Ŀ�������ÿһ�ζԹ��̵��ظ�����Ϊһ�Ρ�����������ÿһ�ε����õ��Ľ���ᱻ������Ϊ��һ�ε����ĳ�ʼֵ*/
uint32_t fibonacci_iteration(uint32_t number) {
	uint32_t firstNumber = 0;
	uint32_t secondNumber = 1;
	//쳲���������[1,1,2,3,5,8,13,21,...],ǰ����֮�͵������ں����ֵ
	uint32_t sumNumber = 0;
	if (number == 1) {
		return 1;
	}
	for (int i = 2; i <= number; i++) {
		sumNumber = firstNumber + secondNumber;
		firstNumber = secondNumber;
		secondNumber = sumNumber;
	}
	return sumNumber;
}

/*�ݹ飨Ӣ�Recursion��������Ϊ�ݻأ�����ѧ��������ѧ�У���ָ�ں����Ķ�����ʹ�ú�������ķ������ݹ�һ�ʻ��ϳ����������������Ʒ����ظ�����Ĺ��̡����磬�����澵���໥֮�����ƽ��ʱ������Ƕ�׵�ͼ���������޵ݹ����ʽ���ֵġ�Ҳ�������Ϊ���Ҹ��ƵĹ��̡�*/
uint32_t fibonacci_recursion(uint32_t number) {

	uint32_t sumNumber = 0;

	if (number == 1||number == 2) {
		return 1;
	}
	sumNumber = fibonacci_recursion(number - 2) +fibonacci_recursion(number - 1);
	return sumNumber;
}

/*β���� ��tail call�� ָ����һ�����������һ�����Ҳ��һ�����ص��ú�������䡣�ں�����ĩβ�����صĿ����Ƕ���һ�������ĵ��ã�Ҳ�����Ƕ�������ã�������ݹ���ã�*/
uint32_t fibonacci_tail_call(uint32_t number) {

	if (number == 1 || number == 2) {
		return 1;
	}
	return fibonacci_tail_call(number - 2) + fibonacci_tail_call(number - 1);//β�ݹ�
}