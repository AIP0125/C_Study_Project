#include <stdio.h>

int main() {
	char grade = 0;
	unsigned int score = 44;
	grade = (score >= 90 )? 'A' :
			(score >= 90)  ? 'B' :
			(score >= 90)  ? 'C' : 'D';

	if(grade != 0){
		printf("score = %u,grade = %c \n", score, grade);
	}
	else {
		printf("error!");
	}


	return 0;
}