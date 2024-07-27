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
	//C �⺯�� size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) �Ӹ����� stream ��ȡ���ݵ� ptr ��ָ��������С�
	/*	ptr -- ����ָ�������С�ߴ� size*nmemb �ֽڵ��ڴ���ָ�롣
		size -- ����Ҫ��ȡ��ÿ��Ԫ�صĴ�С�����ֽ�Ϊ��λ��
		nmemb -- ����Ԫ�صĸ�����ÿ��Ԫ�صĴ�СΪ size �ֽڡ�
		stream -- ����ָ�� FILE �����ָ�룬�� FILE ����ָ����һ����������*/
	while ((bytes_read = fread(buffer ,1 , sizeof(buffer), source_file_ptr)) > 0) {//�ɹ���ȡ��Ԫ���������� size_t ���󷵻أ�size_t ������һ�������������͡���������� nmemb ������ͬ������ܷ�����һ��������ߵ������ļ�ĩβ
		fwrite(buffer, 1, bytes_read, target_file_ptr);
	}

	puts("�ļ����Ƴɹ�\n");
	_fcloseall();
}