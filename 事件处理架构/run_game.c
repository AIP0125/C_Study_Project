#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
//�¼�������
//1.�����¼����ͺ��¼�������ǩ�����������Ƕ�����Ϸ�п��ܷ������¼����ͣ��Լ���������Щ������ǩ��
//2.ʵ�����¼�ע��ͷַ����ƣ�ʵ��һ�����ƣ�����Ϊ��ͬ�������¼�ע�ᴦ��������������Ӧ���¼�����ʱ������Щ����
//3.�����¼�������������������Ϸÿһ���¼����������¼�������
//4.����Ϸ��ʹ���¼�����ϵͳ��main��ע���¼�������������ģ���¼��ķ�������ʾϵͳ�Ĺ�������

typedef enum {
	PLAYER_ATTACK,
	PLAYER_MOVE,
	EVENT_COUNT//��¼�¼�������
}GameEventType;

//��������ָ��
typedef void (*EventHandler)(const char* playName);

//�¼������������飬������ÿһ��Ԫ�ض���EventHandler���͵ĺ���ָ�롣ÿ��Ԫ�ض��洢��һ��ָ������ָ�룬������һ��const char*���͵Ĳ���������void
EventHandler eventhandler[EVENT_COUNT];

//ע���¼�������
void registerEventHandler(GameEventType eventtype, EventHandler handler);

//�ַ��¼�
void dispatchEvent(GameEventType eventtype, const char* playerName);

void handlePlayerAttack(const char* playerName);
void handlePlayerMove(const char* playerName);
int main(void) {
	registerEventHandler(PLAYER_ATTACK,handlePlayerAttack);
	registerEventHandler(PLAYER_MOVE, handlePlayerMove);

	dispatchEvent(PLAYER_ATTACK, "Hero");
	dispatchEvent(PLAYER_MOVE, "Hero");
	return EXIT_SUCCESS;
}

void registerEventHandler(GameEventType eventtype, EventHandler handler) {
	if (eventtype < 0 || eventtype >= EVENT_COUNT) {
		perror("ERROR: ö������Խ��\n");
		exit(EXIT_FAILURE);
	}
	eventhandler[eventtype] = handler;
	
}

void dispatchEvent(GameEventType eventtype, const char* playerName) {
	if (eventhandler[eventtype] != NULL) {
		eventhandler[eventtype](playerName);
	}
}


void handlePlayerAttack(const char* playerName) {
	printf("%s attacks!\n", playerName);
}
void handlePlayerMove(const char* playerName) {
	printf("%s moves!\n", playerName);
}