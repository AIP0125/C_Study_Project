#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void filecopy(const char* source_path, const char* target_path);

int main() {
	const char* source_path = "C:\\Users\\AIP01\\Desktop\\1.txt";
	const char* target_path = "C:\\Users\\AIP01\\Desktop\\2.txt";
	filecopy(source_path, target_path);


	return 0;
}

void filecopy(const char* source_path, const char* target_path){
	if (source_path == NULL || target_path == NULL) {
		perror("error file is NULL");
		exit(EXIT_FAILURE);
	}
	char buffer[256] = { 0 };
	FILE* source_file_ptr;
	FILE* target_file_ptr;
	errno_t err_source = fopen_s(&source_file_ptr, source_path, "rb");
	errno_t err_target = fopen_s(&target_file_ptr, target_path, "wb");
	if (err_source != 0  ) {
		char err_msg[256];
		strerror_s(err_msg, sizeof(err_msg), err_source);
		fprintf(stderr, "error opening source_file:%s", err_msg);
		_fcloseall();
	}
	else if(err_target != 0)
	{
		char err_msg[256];
		strerror_s(err_msg, sizeof(err_msg), err_target);
		fprintf(stderr, "error opening target_file:%s", err_msg);
		_fcloseall();
	}
	size_t bytes_read;
	if (source_file_ptr == NULL || target_file_ptr == NULL) {
		perror("error file position");
		exit(EXIT_FAILURE);
	}
	//C 库函数 size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) 从给定流 stream 读取数据到 ptr 所指向的数组中。
	/*	ptr -- 这是指向带有最小尺寸 size*nmemb 字节的内存块的指针。
		size -- 这是要读取的每个元素的大小，以字节为单位。
		nmemb -- 这是元素的个数，每个元素的大小为 size 字节。
		stream -- 这是指向 FILE 对象的指针，该 FILE 对象指定了一个输入流。*/
	while ((bytes_read = fread(buffer ,1 , sizeof(buffer), source_file_ptr)) > 0) {//成功读取的元素总数会以 size_t 对象返回，size_t 对象是一个整型数据类型。如果总数与 nmemb 参数不同，则可能发生了一个错误或者到达了文件末尾
		fwrite(buffer, 1, bytes_read, target_file_ptr);
	}

	puts("文件复制成功\n");
	_fcloseall();
}