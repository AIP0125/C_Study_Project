#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#pragma execution_character_set("utf-8");
void read_config_safe(const char* file_name);
int main() {
	read_config_safe("E:\\C_Project_demo\\1.txt");
}


void read_config_safe(const char* file_name) {
	errno_t err = 0;
	FILE* file_ptr = NULL;
	err = fopen_s(&file_ptr, file_name, "r");

	char error_msg[256] = { 0 };
	if (err != 0 || file_name == NULL) {
		//C 库函数 char *strerror(int errnum) 从内部数组中搜索错误号 errnum，并返回一个指向错误消息字符串的指针。strerror 生成的错误字符串取决于开发平台和编译器
		strerror_s(error_msg, sizeof(error_msg), err);
		//这里使用fpirntf()是考虑到更多的输出设备，不一定输出到屏幕
		fprintf(stderr, "Failed opening config file for reading: %s\n", error_msg);
		//C 库函数 void exit(int status) 立即终止调用进程。任何属于该进程的打开的文件描述符都会被关闭，该进程的子进程由进程 1 继承，初始化，且会向父进程发送一个 SIGCHLD 信号
		exit(EXIT_FAILURE);
	}
	char buffer[256] = { 0 };
	while(fgets(buffer, sizeof(buffer), file_ptr) != NULL){
	printf("%s",buffer);
	}
	errno_t close_err = 0;
	close_err = fclose(file_ptr);
	if (close_err != 0) {
		perror("error closing file");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
