#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

//斐波那契数列的迭代函数 和 递归函数声明
uint32_t fibonacci_iteration(uint32_t number);//迭代
uint32_t fibonacci_recursion(uint32_t number);//递归
uint32_t fibonacci_tail_call(uint32_t number);//尾递归

int main() {
	uint32_t number = 6;
	//调用两个函数并输出对应值
	printf("number = %" PRId8 ",fibonacci_iteration = %" PRId32 "\n", number, fibonacci_iteration(number));
	printf("number = %" PRId8 ",fibonacci_recursion = %" PRId32 "\n", number, fibonacci_recursion(number));
	printf("number = %" PRId8 ",fibonacci_tail_call = %" PRId32 "\n", number, fibonacci_tail_call(number));
	return 0;
}


/*迭代（iteration）是重复反馈过程的活动，其目的通常是为了接近并且到达所需的目标或结果。每一次对过程的重复被称为一次“迭代”，而每一次迭代得到的结果会被用来作为下一次迭代的初始值*/
uint32_t fibonacci_iteration(uint32_t number) {
	uint32_t firstNumber = 0;
	uint32_t secondNumber = 1;
	//斐波那契数列[1,1,2,3,5,8,13,21,...],前两数之和等于相邻后面的值
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

/*递归（英语：Recursion），又译为递回，在数学与计算机科学中，是指在函数的定义中使用函数自身的方法。递归一词还较常用于描述以自相似方法重复事物的过程。例如，当两面镜子相互之间近似平行时，镜中嵌套的图像是以无限递归的形式出现的。也可以理解为自我复制的过程。*/
uint32_t fibonacci_recursion(uint32_t number) {

	uint32_t sumNumber = 0;

	if (number == 1||number == 2) {
		return 1;
	}
	sumNumber = fibonacci_recursion(number - 2) +fibonacci_recursion(number - 1);
	return sumNumber;
}

/*尾调用 （tail call） 指的是一个函数的最后一条语句也是一个返回调用函数的语句。在函数体末尾被返回的可以是对另一个函数的调用，也可以是对自身调用（即自身递归调用）*/
uint32_t fibonacci_tail_call(uint32_t number) {

	if (number == 1 || number == 2) {
		return 1;
	}
	return fibonacci_tail_call(number - 2) + fibonacci_tail_call(number - 1);//尾递归
}