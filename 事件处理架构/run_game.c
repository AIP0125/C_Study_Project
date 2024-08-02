#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
//事件处理框架
//1.定义事件类型和事件处理函数签名：首先我们定义游戏中可能发生的事件类型，以及，处理这些函数的签名
//2.实现是事件注册和分发机制：实现一个机制，允许为不同的类型事件注册处理函数，并且在相应的事件发生时调用这些函数
//3.定义事件处理函数：现在我们游戏每一种事件定义具体的事件处理函数
//4.在游戏中使用事件处理系统：main中注册事件处理函数，并且模拟事件的发生来演示系统的工作流程

typedef enum {
	PLAYER_ATTACK,
	PLAYER_MOVE,
	EVENT_COUNT//记录事件的总数
}GameEventType;

//处理函数的指针
typedef void (*EventHandler)(const char* playName);

//事件处理函数的数组，数组中每一个元素都是EventHandler类型的函数指针。每个元素都存储了一个指向函数的指针，它接收一个const char*类型的参数，返回void
EventHandler eventhandler[EVENT_COUNT];

//注册事件处理函数
void registerEventHandler(GameEventType eventtype, EventHandler handler);

//分发事件
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
		perror("ERROR: 枚举索引越界\n");
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