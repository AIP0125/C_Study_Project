#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
//游戏难度的枚举
enum GameDifficulty {
	EASY = 1,
	GENERAL = 2,
	DIFFICULTY = 3,
	CHALLENGE = 4,
};
//游戏设置内容
typedef struct GameSettings{
	float volume;
	unsigned int x;
	unsigned int y;
	enum GameDifficulty difficulty;

}GameSettings;
//读取设置声明
void loaded_game_settings(const GameSettings* settings,const char* file_name);
//
void save_game_settings(const GameSettings* settings, const char* file_name);

int main() {
	GameSettings settings = { 0.33,1920,1080,GENERAL};
	save_game_settings(&settings, "C:\\Users\\AIP01\\Desktop\\GameSettings.bin");
	GameSettings loaded_settings;
	loaded_game_settings(&loaded_settings, "C:\\Users\\AIP01\\Desktop\\GameSettings.bin");
	
	printf("volume:%0.2f\nresolution ratio: %d x %d\ngame difficulty:%d",
		loaded_settings.volume, 
		loaded_settings.x, 
		loaded_settings.y, 
		loaded_settings.difficulty);
	return 0;
}

void loaded_game_settings(const GameSettings* settings, const char* file_name) {
	FILE* file_ptr;
	errno_t err_open = fopen_s(&file_ptr, file_name, "rb");
	if (err_open != 0 || file_ptr == NULL) {
		char err_msg[256];
		strerror_s(err_msg, sizeof(err_msg), err_open);
		fprintf(stderr, "error opening file:%s", err_msg);
		exit(EXIT_FAILURE);
	}
	fread(settings,sizeof(GameSettings),1,file_ptr);
	fclose(file_ptr);
}


void save_game_settings(const GameSettings* settings, const char* file_name) {

	FILE* file_ptr;
	errno_t err_open = fopen_s(&file_ptr, file_name, "wb");
	if (err_open != 0 || file_ptr == NULL) {
		char err_msg[256];
		strerror_s(err_msg, sizeof(err_msg), err_open);
		fprintf(stderr, "error opening file:%s", err_msg);
		exit(EXIT_FAILURE);
	}
	fwrite(settings, sizeof(GameSettings), 1, file_ptr);
	fclose(file_ptr);
}
