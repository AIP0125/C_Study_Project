#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>//errno.h ͷ�ļ��п����ҵ����ָ����Ĵ������

int main(void) {
	//������һ��256���ȵĻ�����
	char buffer[256];

	//������һ���ļ���
	FILE *file_ptr = "E:\\C_Project\\�ļ���������\\text.txt";	
	
	//C ����Ա����ͨ����鷵��ֵ��Ȼ����ݷ���ֵ������ȡ�����ʵ��Ķ�����������ԱӦ���ڳ����ʼ��ʱ���� errno ����Ϊ 0������һ�����õı��ϰ�ߡ�0 ֵ��ʾ������û�д���
	errno_t err = 0;
	
	//errno_t��һ�������ͣ������ļ���Ϊ�ܶ���ܵ�ԭ��û��Ȩ�ޣ��ļ�·�������ļ������ڣ��ļ��쳣�ȴ��ļ���ʧ��
	err = fopen_s(&file_ptr, "E:\\C_Project\\�ļ���������\\text.txt", "r");	
	
	//���ִ���Ĵ���
	if (err != 0 || file_ptr == NULL) {
		// C �⺯�� void perror(const char* str) ��һ�������Դ�����Ϣ�������׼���� stderr����������ַ��������һ��ð�ţ�Ȼ����һ���ո�
		perror("error opening file");

		//EXIT_FAILURE=-1,��stdlib.h��ͷ�ļ���ͨ������£�����ɹ�ִ����һ�����������˳���ʱ������ֵ EXIT_SUCCESS�������EXIT_SUCCESS �Ǻ꣬��������Ϊ 0��
		return EXIT_FAILURE;
		
		//��������д���һ�ִ�������������˳�����ʱ�������״ֵ̬ EXIT_FAILURE��������Ϊ - 1
	}
	while (fgets(buffer, sizeof(buffer), file_ptr) != NULL){
		puts(buffer);
	}

	rewind(file_ptr);
	char ch;
	while ((ch = fgetc(file_ptr)) != EOF) {
		putchar(ch);
	}
	//�ر��ļ���
	fclose(file_ptr);

	return 0;
}