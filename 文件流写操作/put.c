#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void) {
	FILE* file_ptr = "E:\\C_Project\\文件流写操作\\text.txt";
	errno_t err = 0;
	//w写模式会直接覆盖掉文件内容
	err = fopen_s(&file_ptr, file_ptr, "w");
	if (err != 0 || file_ptr == NULL) {
		perror("error opening file");
		return EXIT_FAILURE;
	}

	fputc('H', file_ptr);
	fputc('i', file_ptr);
	fputs("\nThis is the second line of the written text file",file_ptr);
	fprintf(file_ptr, "try use fprintf:%d %c %s", 2, '\n', "Looks like it worked!!!");


	//在w文件操作模式下，要作错误判断较好，如下
	if (fclose(file_ptr)) {
		perror("error closing file");
		return EXIT_FAILURE;
	}
	return 0;
}