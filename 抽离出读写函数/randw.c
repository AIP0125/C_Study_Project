#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 1024

void clear_log(const char* file_name);
void append_log_safe(const char* file_name, const char* msg);
void read_config_safe(const char* file_name);
errno_t update_log(const char* file_name, const char* search_str, const char* replace_str);

int main() {
	const char file_name[] = "E:\\C_Project_demo\\1.txt";
	/*read_config_safe(file_name);
	append_log_safe(file_name, "这是追加的文本！");*/
	/*clear_log(file_name);*/
	const char* search_str = "666666666";
	const char* replace_str = "16";
	errno_t result = update_log(file_name, search_str, replace_str);
	if (result == 0) {
		printf("updata log successfully!");
		return 0;
	}
	else
	{
		char error_msg[256] = { 0 };
		strerror_s(error_msg, sizeof(error_msg), result);
		fprintf_s(stderr, "failed updata error :%s", error_msg);
	}
	//关闭所有的流
	int file_stream_close = _fcloseall();
	printf("\nNumber of files closed by _fcloseall:%u\n", file_stream_close);
	return 0;
}
	/**
	*读取文件所有内容
	*character：const char* file_name
	* reurn：void
	*/
	void read_config_safe(const char* file_name) {
		errno_t error_open = 0;
		errno_t error_close = 0;
		FILE* file_ptr = NULL;

		error_open = fopen_s(&file_ptr, file_name, "r");
		//卫语句,判断传入参数是否符合条件
		
		if (error_open != 0 || file_name == NULL) {
			char error_msg[256] = { 0 };//接收错误信息
			//C 库函数 char *strerror(int errnum) 从内部数组中搜索错误号 errnum，并返回一个指向错误消息字符串的指针。strerror 生成的错误字符串取决于开发平台和编译器
			strerror_s(error_msg, sizeof(error_msg), error_open);
			//这里使用fpirntf()是考虑到更多的输出设备，不一定输出到屏幕
			fprintf_s(stderr, "Failed opening config file for reading: %s\n", error_msg);
			//C 库函数 void exit(int status) 立即终止调用进程。任何属于该进程的打开的文件描述符都会被关闭，该进程的子进程由进程 1 继承，初始化，且会向父进程发送一个 SIGCHLD 信号
			exit(EXIT_FAILURE);
		}
		//读取文件
		char buffer[256] = { 0 };
		while (fgets(buffer, sizeof(buffer), file_ptr) != NULL) {
			printf("%s", buffer);
		}
		//检测关闭文件是否成功
		error_close = fclose(file_ptr);
		if (error_close != 0) {
			//C 库函数 void perror(const char *str) 把一个描述性错误消息输出到标准错误 stderr。首先输出字符串 str，后跟一个冒号，然后是一个空格
			perror("error closing file");
			exit(EXIT_FAILURE);
		}
	}

/**
*在文件内容后追加所指定的字符串
*character:const char* file_name, const char* msg
* reurn：void
*/
void append_log_safe(const char* file_name, const char* msg) {
	FILE* file_ptr = NULL;
	errno_t error_open = 0;
	errno_t error_close = 0;
	//打开文件
	error_open = fopen_s(&file_ptr, file_name, "a");
	
	if (error_open != 0 || file_name == NULL) {
		char error_msg[256] = { 0 };//接收打开文件发生错误的错误信息
		strerror_s(error_msg, sizeof(error_msg), error_open);
		fprintf_s(stderr, "Failed opening config file for writing: %s\n", error_msg);
		exit(EXIT_FAILURE);
	}
	//检查file_ptr是否为NULL,保证fprintf_s的安全调用
	if (file_ptr == NULL) {
		printf("ERROR:file_name is NULL\n");
	}
	else {
		fprintf_s(file_ptr, "%s", msg);
		exit(EXIT_FAILURE);
	}
	//检测关闭文件是否成功
	error_close = fclose(file_ptr);
	if (error_close != 0) {
		perror("error closing file");
		exit(EXIT_FAILURE);
	}
}

/**
*用来清空文件内容
* character:const char* file_name
* return void
*/
void clear_log(const char* file_name) {
	FILE* file_ptr = NULL;
	errno_t error_open = 0;
	errno_t error_close = 0;
	//打开文件,同时因为是w文件操作模式,文件会被清空
	error_open = fopen_s(&file_ptr, file_name, "w");
	//打开文件错误检查
	char error_msg[256] = { 0 };//接收打开文件发生错误的错误信息
	if (error_open != 0 || file_name == NULL) {
		strerror_s(error_msg, sizeof(error_msg), error_open);
		fprintf_s(stderr, "Failed opening config file: %s\n", error_msg);
		exit(EXIT_FAILURE);
	}
	//检测关闭文件是否成功
	error_close = fclose(file_ptr);
	if (error_close != 0) {
		perror("Error closing file");
		exit(EXIT_FAILURE);
	}
}

/**
* 用来替换文件内指定行的内容
* character:const char* file_name, const char* search_str, const char* replace_str
* return errno_t
*/
errno_t update_log(const char* file_name, const char* search_str, const char* replace_str) {
	
	//卫语句，检查传入参数是否合法
	if (file_name == NULL || search_str == NULL || replace_str == NULL) {
		return EINVAL;//返回无效参数错误
	}
	FILE* file_ptr = NULL;
	long position = 0;//用来记录文件指针当前的位置
	int found = 0;//记录字符串是否匹配的状态
	char buffer[BUFFERSIZE] = { 0 };//定义了读取文件的缓冲区
	//打开文件
	errno_t error_open = fopen_s(&file_ptr, file_name, "r+");
	//打开文件错误处理
	if (error_open != 0 || file_name == NULL) {
		char error_msg[256] = { 0 };//接收打开文件发生错误的错误信息
		strerror_s(error_msg, sizeof(error_msg), error_open);
		fprintf_s(stderr, "Failed opening config file for writing: %s\n", error_msg);
		exit(EXIT_FAILURE);
	}
	
	while (fgets(buffer,BUFFERSIZE,file_ptr) != NULL)
	{
		//C 库函数 char *strstr(const char *haystack, const char *needle) 在字符串 haystack 中查找第一次出现字符串 needle 的位置，不包含终止符 '\0'
		//找到匹配的行并记录文件指针位置
		if (strstr(buffer, search_str) != NULL) {
			position = ftell(file_ptr) - (long)strlen(buffer) - 1;
			found = 1;
			break;
		}
	}
	if (found) {	
		//判断要替换的字符串长度是否会溢出
		size_t search_str_len = strlen(search_str);
		size_t replace_str_len = strlen(replace_str);
		if (search_str_len > BUFFERSIZE-1 || replace_str_len > BUFFERSIZE-1) {
			fclose(file_ptr);
			return ERANGE;//返回错误码，表示字符串长度超出范围
		}
		fseek(file_ptr, position, SEEK_SET);//回到匹配字符串初始位置
		//C 库函数 void *memset(void *str, int c, size_t n) 用于将一段内存区域设置为指定的值
		// memset() 函数将指定的值 c 复制到 str 所指向的内存区域的前 n 个字节中，这可以用于将内存块清零或设置为特定值
		// 在一些情况下，需要快速初始化大块内存为零或者特定值，memset() 可以提供高效的实现
		// 在清空内存区域或者为内存区域赋值时，memset() 是一个常用的工具函数
		memset(buffer, ' ', strlen(buffer) - 1);
		buffer[strlen(buffer) - 1] = '\n';
		fseek(file_ptr, position, SEEK_SET);//回到匹配字符串初始位置
		//C 库函数 int fputs(const char *str, FILE *stream) 把字符串写入到指定的流stream中，但不包括空字符
		fputs(buffer, file_ptr);//清空行内容
		fseek(file_ptr, position, SEEK_SET);
		int result = fputs(replace_str, file_ptr);//写入替换的字符
		if (result == EOF) {
			fclose(file_ptr);
			return errno;
		}
	}
	else
	{
		fclose(file_ptr);
		return ENOENT;//返回未找到的匹配项
	}
	fclose(file_ptr);
	return 0;
}


