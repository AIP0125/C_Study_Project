#include <stdio.h>
#include <Windows.h>
#include <stdint.h>
#include <inttypes.h>

int main() {
	const uint32_t total_steps = 50;

	puts("������,���Ժ�");

	for (uint32_t i = 0; i <= total_steps; i++) {
		printf("\r[");
		//����������
		for (uint32_t j = 0; j < i; j++)
		{
			printf("#");
		}

		for (uint32_t j = i; j < total_steps; j++) {
			printf("-");
		}
		printf("] %" PRIu32 "%%", (i * 100) / total_steps);

		Sleep(100);
	}
	printf("\n����ɣ�");
	return 0;
}