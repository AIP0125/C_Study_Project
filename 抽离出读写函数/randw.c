#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void append_log_safe(const char* file_name, const char* msg);
void read_config_safe(const char* file_name);

int main() {
	const char file_name[] = "E:\\C_Project_demo\\1.txt";
	read_config_safe(file_name);
	append_log_safe(file_name, "����׷�ӵ��ı���");
	
	
	//�ر����е���
	int file_stream_close = _fcloseall();
	printf("\nNumber of files closed by _fcloseall:%u\n", file_stream_close);
	return 0;
}

/*��ȡ�ļ���������
*character��
*1.const char* file_name
* reurn��void
*/
void read_config_safe(const char* file_name) {
	errno_t error_open = 0;
	errno_t error_close = 0;
	FILE* file_ptr = NULL;
	error_open = fopen_s(&file_ptr, file_name, "r");

	char error_msg[256] = { 0 };
	if (error_open != 0 || file_name == NULL) {
		//C �⺯�� char *strerror(int errnum) ���ڲ���������������� errnum��������һ��ָ�������Ϣ�ַ�����ָ�롣strerror ���ɵĴ����ַ���ȡ���ڿ���ƽ̨�ͱ�����
		strerror_s(error_msg, sizeof(error_msg), error_open);
		//����ʹ��fpirntf()�ǿ��ǵ����������豸����һ���������Ļ
		fprintf_s(stderr, "Failed opening config file for reading: %s\n", error_msg);
		//C �⺯�� void exit(int status) ������ֹ���ý��̡��κ����ڸý��̵Ĵ򿪵��ļ����������ᱻ�رգ��ý��̵��ӽ����ɽ��� 1 �̳У���ʼ�����һ��򸸽��̷���һ�� SIGCHLD �ź�
		exit(EXIT_FAILURE);
	}
	char buffer[256] = { 0 };
	while(fgets(buffer, sizeof(buffer), file_ptr) != NULL){
	printf("%s",buffer);
	}
	
	error_close = fclose(file_ptr);
	if (error_close != 0) {
		//C �⺯�� void perror(const char *str) ��һ�������Դ�����Ϣ�������׼���� stderr����������ַ��� str�����һ��ð�ţ�Ȼ����һ���ո�
		perror("error closing file");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
/*���ļ����ݺ�׷����ָ�����ַ���
*character:const char* file_name, const char* msg
* reurn��void
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
