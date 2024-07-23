#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>//errno.h 头文件中可以找到各种各样的错误代码

int main(void) {
	//定义了一个256长度的缓存区
	char buffer[256];

	//定义了一个文件流
	FILE *file_ptr = "E:\\C_Project\\文件流读操作\\text.txt";	
	
	//C 程序员可以通过检查返回值，然后根据返回值决定采取哪种适当的动作。开发人员应该在程序初始化时，把 errno 设置为 0，这是一种良好的编程习惯。0 值表示程序中没有错误
	errno_t err = 0;
	
	//errno_t是一错误类型，比如文件因为很多可能的原因，没有权限，文件路径错误，文件不存在，文件异常等打开文件流失败
	err = fopen_s(&file_ptr, "E:\\C_Project\\文件流读操作\\text.txt", "r");	
	
	//出现错误的处理
	if (err != 0 || file_ptr == NULL) {
		// C 库函数 void perror(const char* str) 把一个描述性错误消息输出到标准错误 stderr。首先输出字符串，后跟一个冒号，然后是一个空格
		perror("error opening file");

		//EXIT_FAILURE=-1,在stdlib.h的头文件中通常情况下，程序成功执行完一个操作正常退出的时候会带有值 EXIT_SUCCESS。在这里，EXIT_SUCCESS 是宏，它被定义为 0。
		return EXIT_FAILURE;
		
		//如果程序中存在一种错误情况，当您退出程序时，会带有状态值 EXIT_FAILURE，被定义为 - 1
	}
	while (fgets(buffer, sizeof(buffer), file_ptr) != NULL){
		puts(buffer);
	}

	rewind(file_ptr);
	char ch;
	while ((ch = fgetc(file_ptr)) != EOF) {
		putchar(ch);
	}
	//关闭文件流
	fclose(file_ptr);

	return 0;
}