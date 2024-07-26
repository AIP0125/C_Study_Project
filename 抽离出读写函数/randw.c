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
	append_log_safe(file_name, "����׷�ӵ��ı���");*/
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
	//�ر����е���
	int file_stream_close = _fcloseall();
	printf("\nNumber of files closed by _fcloseall:%u\n", file_stream_close);
	return 0;
}
	/**
	*��ȡ�ļ���������
	*character��const char* file_name
	* reurn��void
	*/
	void read_config_safe(const char* file_name) {
		errno_t error_open = 0;
		errno_t error_close = 0;
		FILE* file_ptr = NULL;

		error_open = fopen_s(&file_ptr, file_name, "r");
		//�����,�жϴ�������Ƿ��������
		
		if (error_open != 0 || file_name == NULL) {
			char error_msg[256] = { 0 };//���մ�����Ϣ
			//C �⺯�� char *strerror(int errnum) ���ڲ���������������� errnum��������һ��ָ�������Ϣ�ַ�����ָ�롣strerror ���ɵĴ����ַ���ȡ���ڿ���ƽ̨�ͱ�����
			strerror_s(error_msg, sizeof(error_msg), error_open);
			//����ʹ��fpirntf()�ǿ��ǵ����������豸����һ���������Ļ
			fprintf_s(stderr, "Failed opening config file for reading: %s\n", error_msg);
			//C �⺯�� void exit(int status) ������ֹ���ý��̡��κ����ڸý��̵Ĵ򿪵��ļ����������ᱻ�رգ��ý��̵��ӽ����ɽ��� 1 �̳У���ʼ�����һ��򸸽��̷���һ�� SIGCHLD �ź�
			exit(EXIT_FAILURE);
		}
		//��ȡ�ļ�
		char buffer[256] = { 0 };
		while (fgets(buffer, sizeof(buffer), file_ptr) != NULL) {
			printf("%s", buffer);
		}
		//���ر��ļ��Ƿ�ɹ�
		error_close = fclose(file_ptr);
		if (error_close != 0) {
			//C �⺯�� void perror(const char *str) ��һ�������Դ�����Ϣ�������׼���� stderr����������ַ��� str�����һ��ð�ţ�Ȼ����һ���ո�
			perror("error closing file");
			exit(EXIT_FAILURE);
		}
	}

/**
*���ļ����ݺ�׷����ָ�����ַ���
*character:const char* file_name, const char* msg
* reurn��void
*/
void append_log_safe(const char* file_name, const char* msg) {
	FILE* file_ptr = NULL;
	errno_t error_open = 0;
	errno_t error_close = 0;
	//���ļ�
	error_open = fopen_s(&file_ptr, file_name, "a");
	
	if (error_open != 0 || file_name == NULL) {
		char error_msg[256] = { 0 };//���մ��ļ���������Ĵ�����Ϣ
		strerror_s(error_msg, sizeof(error_msg), error_open);
		fprintf_s(stderr, "Failed opening config file for writing: %s\n", error_msg);
		exit(EXIT_FAILURE);
	}
	//���file_ptr�Ƿ�ΪNULL,��֤fprintf_s�İ�ȫ����
	if (file_ptr == NULL) {
		printf("ERROR:file_name is NULL\n");
	}
	else {
		fprintf_s(file_ptr, "%s", msg);
		exit(EXIT_FAILURE);
	}
	//���ر��ļ��Ƿ�ɹ�
	error_close = fclose(file_ptr);
	if (error_close != 0) {
		perror("error closing file");
		exit(EXIT_FAILURE);
	}
}

/**
*��������ļ�����
* character:const char* file_name
* return void
*/
void clear_log(const char* file_name) {
	FILE* file_ptr = NULL;
	errno_t error_open = 0;
	errno_t error_close = 0;
	//���ļ�,ͬʱ��Ϊ��w�ļ�����ģʽ,�ļ��ᱻ���
	error_open = fopen_s(&file_ptr, file_name, "w");
	//���ļ�������
	char error_msg[256] = { 0 };//���մ��ļ���������Ĵ�����Ϣ
	if (error_open != 0 || file_name == NULL) {
		strerror_s(error_msg, sizeof(error_msg), error_open);
		fprintf_s(stderr, "Failed opening config file: %s\n", error_msg);
		exit(EXIT_FAILURE);
	}
	//���ر��ļ��Ƿ�ɹ�
	error_close = fclose(file_ptr);
	if (error_close != 0) {
		perror("Error closing file");
		exit(EXIT_FAILURE);
	}
}

/**
* �����滻�ļ���ָ���е�����
* character:const char* file_name, const char* search_str, const char* replace_str
* return errno_t
*/
errno_t update_log(const char* file_name, const char* search_str, const char* replace_str) {
	
	//����䣬��鴫������Ƿ�Ϸ�
	if (file_name == NULL || search_str == NULL || replace_str == NULL) {
		return EINVAL;//������Ч��������
	}
	FILE* file_ptr = NULL;
	long position = 0;//������¼�ļ�ָ�뵱ǰ��λ��
	int found = 0;//��¼�ַ����Ƿ�ƥ���״̬
	char buffer[BUFFERSIZE] = { 0 };//�����˶�ȡ�ļ��Ļ�����
	//���ļ�
	errno_t error_open = fopen_s(&file_ptr, file_name, "r+");
	//���ļ�������
	if (error_open != 0 || file_name == NULL) {
		char error_msg[256] = { 0 };//���մ��ļ���������Ĵ�����Ϣ
		strerror_s(error_msg, sizeof(error_msg), error_open);
		fprintf_s(stderr, "Failed opening config file for writing: %s\n", error_msg);
		exit(EXIT_FAILURE);
	}
	
	while (fgets(buffer,BUFFERSIZE,file_ptr) != NULL)
	{
		//C �⺯�� char *strstr(const char *haystack, const char *needle) ���ַ��� haystack �в��ҵ�һ�γ����ַ��� needle ��λ�ã���������ֹ�� '\0'
		//�ҵ�ƥ����в���¼�ļ�ָ��λ��
		if (strstr(buffer, search_str) != NULL) {
			position = ftell(file_ptr) - (long)strlen(buffer) - 1;
			found = 1;
			break;
		}
	}
	if (found) {	
		//�ж�Ҫ�滻���ַ��������Ƿ�����
		size_t search_str_len = strlen(search_str);
		size_t replace_str_len = strlen(replace_str);
		if (search_str_len > BUFFERSIZE-1 || replace_str_len > BUFFERSIZE-1) {
			fclose(file_ptr);
			return ERANGE;//���ش����룬��ʾ�ַ������ȳ�����Χ
		}
		fseek(file_ptr, position, SEEK_SET);//�ص�ƥ���ַ�����ʼλ��
		//C �⺯�� void *memset(void *str, int c, size_t n) ���ڽ�һ���ڴ���������Ϊָ����ֵ
		// memset() ������ָ����ֵ c ���Ƶ� str ��ָ����ڴ������ǰ n ���ֽ��У���������ڽ��ڴ�����������Ϊ�ض�ֵ
		// ��һЩ����£���Ҫ���ٳ�ʼ������ڴ�Ϊ������ض�ֵ��memset() �����ṩ��Ч��ʵ��
		// ������ڴ��������Ϊ�ڴ�����ֵʱ��memset() ��һ�����õĹ��ߺ���
		memset(buffer, ' ', strlen(buffer) - 1);
		buffer[strlen(buffer) - 1] = '\n';
		fseek(file_ptr, position, SEEK_SET);//�ص�ƥ���ַ�����ʼλ��
		//C �⺯�� int fputs(const char *str, FILE *stream) ���ַ���д�뵽ָ������stream�У������������ַ�
		fputs(buffer, file_ptr);//���������
		fseek(file_ptr, position, SEEK_SET);
		int result = fputs(replace_str, file_ptr);//д���滻���ַ�
		if (result == EOF) {
			fclose(file_ptr);
			return errno;
		}
	}
	else
	{
		fclose(file_ptr);
		return ENOENT;//����δ�ҵ���ƥ����
	}
	fclose(file_ptr);
	return 0;
}


