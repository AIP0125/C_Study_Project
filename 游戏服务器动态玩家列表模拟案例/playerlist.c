#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#define TIMESTRING_SIZE 26
//�ṹ��Player���������id������
typedef struct Player {
	int id;
	char name[30];
}Player;
//����������������б�����
void updata_player_list(Player** Players,int* current_size,int new_size, Player new_player);
//���������鿴��ǰ����б��еľ�������б�
void print_playerlist(Player* playerlist,int current_size);
//��־log�ļ�¼����ģ�⣬��ʵӦ���»�ʹ�ø��Ӹ��������Ƶ���־ϵͳ
void log_info(const char* message);
void log_error(const char* message);
void log_message(const char* level, const char* message);

int main(void) {
	int current_size = 0;			//����б�ǰ���������Ϊ0
	Player* playerlist = NULL;		//����б�Ϊ��
	//��ҵĴ����ͱ�ĸ���
	Player player_1 = { 1,"glory" };
	updata_player_list(&playerlist,&current_size,current_size+1,player_1);
	Player player_2 = { 2,"��������" };
	updata_player_list(&playerlist, &current_size, current_size + 1, player_2);
	Player player_3 = { 3,"�޵б���սʿ" };
	updata_player_list(&playerlist, &current_size, current_size + 1, player_3);
	//�鿴��
	print_playerlist(playerlist,current_size);

	free(playerlist);
	return EXIT_SUCCESS;
}

void updata_player_list(Player** playerlist, int* current_size, int new_size, Player new_player) {
	Player* temp = realloc(*playerlist, new_size * sizeof(Player));//������temp��������һ��������������ڴ�
	if (temp == NULL) {

	}
	*playerlist = temp;//����б��ָ��ָ���µ��ڴ���������ʹ���˶���ָ��ʵ���������
	if (new_size < *current_size) {
		log_error("error new_size smaller than current");
	}
	if (new_size == *current_size) {
		log_error("Size no changed");
	} 
	if (new_size > *current_size) {
		(*playerlist)[*current_size] = new_player;//�������д������б�
	}

	*current_size = new_size;//���±�Ĵ�С

	log_info("Player added Successfully");
	char info_message[100];
	snprintf(info_message, sizeof(info_message), "Current player count:%d", *current_size);
	log_info(info_message);
}
void print_playerlist(Player* playerlist, int size) {
	printf("Current player:");
	for (int i = 0; i < size; i++) {
		printf("\nid:%d name:%s", playerlist[i].id, playerlist[i].name);
	}
}
void log_info(const char* message) {
	log_message("INFO", message);
	
}
void log_error(const char* message) {
	log_message("ERROR", message);
}
void log_message(const char* level, const char* message) {
	time_t now_time = time(NULL);
	char time_str[TIMESTRING_SIZE];
	if (ctime_s(time_str, sizeof(time_str), &now_time) == 0) {
	time_str[24] = '\0';

	FILE* file_ptr = NULL;
	const char* file_name = "C:\\Users\\AIP01\\Desktop\\log.txt";

	errno_t err = fopen_s(&file_ptr, file_name, "a");
	if (err != 0) {
		char err_msg[256];
		strerror_s(err_msg, sizeof(err_msg), err);
		fprintf(stderr, "error failed opening log file: %s", err_msg);
	}
	if (file_ptr == NULL) {
		perror("ERROR:file_ptr is NULL");
		exit(EXIT_FAILURE);
	}
	else
	{
		fprintf(file_ptr, "[%s] %s: %s\n",time_str,level, message);
		fclose(file_ptr);
	}
}
	else {
		FILE* file_ptr = NULL;
		const char* file_name = "C:\\Users\\AIP01\\Desktop\\log.txt";

		errno_t err = fopen_s(&file_ptr, file_name, "w");
		if (err != 0) {
			char err_msg[256];
			strerror_s(err_msg, sizeof(err_msg), err);
			fprintf(stderr, "error failed opening log file:%s ", err_msg);
		}
		if (file_ptr == NULL) {
			perror("error:file_ptr is NULL");
			exit(EXIT_FAILURE);
		}
		else
		{
			fprintf(file_ptr, "[ERROR] Failed to get current time\n");
			fclose(file_ptr);
		}
	}
}