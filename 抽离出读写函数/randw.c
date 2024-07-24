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
		//C �⺯�� char *strerror(int errnum) ���ڲ���������������� errnum��������һ��ָ�������Ϣ�ַ�����ָ�롣strerror ���ɵĴ����ַ���ȡ���ڿ���ƽ̨�ͱ�����
		strerror_s(error_msg, sizeof(error_msg), err);
		//����ʹ��fpirntf()�ǿ��ǵ����������豸����һ���������Ļ
		fprintf(stderr, "Failed opening config file for reading: %s\n", error_msg);
		//C �⺯�� void exit(int status) ������ֹ���ý��̡��κ����ڸý��̵Ĵ򿪵��ļ����������ᱻ�رգ��ý��̵��ӽ����ɽ��� 1 �̳У���ʼ�����һ��򸸽��̷���һ�� SIGCHLD �ź�
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
