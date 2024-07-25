#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void append_log_safe(const char* file_name, const char* msg);
void read_config_safe(const char* file_name);

int main() {
	const char file_name[] = "E:\\C_Project_demo\\1.txt";
	read_config_safe(file_name);
	append_log_safe(file_name, "这是追加的文本！");
	
	
	//关闭所有的流
	int file_stream_close = _fcloseall();
	printf("\nNumber of files closed by _fcloseall:%u\n", file_stream_close);
	return 0;
}

/*读取文件所有内容
*character：
*1.const char* file_name
* reurn：void
*/
void read_config_safe(const char* file_name) {
	errno_t error_open = 0;
	errno_t error_close = 0;
	FILE* file_ptr = NULL;
	error_open = fopen_s(&file_ptr, file_name, "r");

	char error_msg[256] = { 0 };
	if (error_open != 0 || file_name == NULL) {
		//C 库函数 char *strerror(int errnum) 从内部数组中搜索错误号 errnum，并返回一个指向错误消息字符串的指针。strerror 生成的错误字符串取决于开发平台和编译器
		strerror_s(error_msg, sizeof(error_msg), error_open);
		//这里使用fpirntf()是考虑到更多的输出设备，不一定输出到屏幕
		fprintf_s(stderr, "Failed opening config file for reading: %s\n", error_msg);
		//C 库函数 void exit(int status) 立即终止调用进程。任何属于该进程的打开的文件描述符都会被关闭，该进程的子进程由进程 1 继承，初始化，且会向父进程发送一个 SIGCHLD 信号
		exit(EXIT_FAILURE);
	}
	char buffer[256] = { 0 };
	while(fgets(buffer, sizeof(buffer), file_ptr) != NULL){
	printf("%s",buffer);
	}
	
	error_close = fclose(file_ptr);
	if (error_close != 0) {
		//C 库函数 void perror(const char *str) 把一个描述性错误消息输出到标准错误 stderr。首先输出字符串 str，后跟一个冒号，然后是一个空格
		perror("error closing file");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
/*在文件内容后追加所指定的字符串
*character:const char* file_name, const char* msg
* reurn：void
*/
void append_log_safe(const char* file_name, const char* msg) {
	FILE* file_ptr = NULL;
	errno_t error_open = 0;
	errno_t error_close = 0;
	error_open = fopen_s(&file_ptr, file_name, "a");
	char error_msg[256] = { 0 };
	if (error_open != 0 || file_name == NULL) {
		strerror_s(error_msg, sizeof(error_msg), error_open);
		fprintf_s(stderr, "Failed opening config file for writing: %s\n", error_msg);
		exit(EXIT_FAILURE);
	}
	if (file_ptr == NULL) {
		printf("ERROR:file_name is NULL\n");
	}
	else {
		fprintf_s(file_ptr, "%s", msg);
		exit(EXIT_FAILURE);
	}
	error_close = fclose(file_ptr);
	if (error_close != 0) {
		perror("error closing file");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
