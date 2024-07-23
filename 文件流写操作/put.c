#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void) {
	FILE* file_ptr = "E:\\C_Project\\�ļ���д����\\text.txt";
	errno_t err = 0;
	err = fopen_s(&file_ptr, file_ptr, "w");
	if (err != 0 || file_ptr == NULL) {
		perror("error opening file");
		return EXIT_FAILURE;
	}
	fputc('H', file_ptr);
	fputc('i', file_ptr);
	fputs("\nThis is the second line of the written text file",file_ptr);
	fprintf(file_ptr, "try use fprintf:%d %c %s", 2, '\n', "Looks like it worked!!!");



	fclose(file_ptr);
	return 0;
}