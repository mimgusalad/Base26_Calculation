#include <stdio.h>
#define STRING_SIZE 12800
#define PARAM_SIZE 100
#define DEPTH_SIZE 127

int CharToInt(char ch) {
	if (ch == '+') {
		return -1;
	}
	else if (ch == '-') {
		return -2;
	}
	else if (ch >= 'A' && ch <= 'Z') {
		return ch - 'A';
	}
	else {
		return -3;
	}
}

char IntToChar(int num) {
	if (num == -1) {
		return '+';
	}
	else if (num == -2) {
		return '-';
	}
	else if (num >= 0 && num <= 25) {
		return 'A' + num;
	}
	else {
		return '\0';
	}
}

void test_main(char answer[STRING_SIZE], const char question[STRING_SIZE]) {

	//int arr[PARAM_SIZE][DEPTH_SIZE] = { 0 };
	//int arrtemp[DEPTH_SIZE] = { 0 };
	//int arr_temp2[DEPTH_SIZE] = {0};

	char arr[PARAM_SIZE][DEPTH_SIZE + 1] = {'+'};
	int index[PARAM_SIZE];
	char temp[STRING_SIZE] = {};

//	printf("%s\n\n", question);

	//arr[row][0] = 부호
	//arr[row][1] = 마지막 숫자 인덱스

	int i = 0;
	int row = 0;
	int col = 1;
	int reset = 0;
	while (i < STRING_SIZE) {
		char letter = question[i];
		if (letter == '+' || letter == '-') {
			index[row] = col-1;
			row++; col = 0;
			arr[row][0] = letter;
		}
		else {
			arr[row][col] = letter;
		}
		col++;i++;
		temp[i] = 'A';

		if (letter == NULL) {
			index[row] = col-1;
			reset = row+1;
			break;
		}
	}

	for (int row = reset; row < PARAM_SIZE; row++) {
		index[row] = 0;
	}


	for (int row = 0; row <= reset; row++) {
		printf("row=%d\n", row);
		for (int col = 0; col < DEPTH_SIZE; col++) {
			printf("col[%d] = %c\n", col, arr[row][col]);
		}
		printf("\t end-index = %d\n\n", index[row]);
	}


	for (int row = 40; row < 41; row++) {
		for (int col = DEPTH_SIZE; col >= 1; col--) {
			int carry = 0;
			int borrow = 0;
			if (arr[row][0] == '+') {
				// addition 
				temp[0] = arr[row][0];
				int sum = CharToInt(temp[col]) + carry - 26;
				if (index[row] - 1 >= 1) sum += CharToInt(arr[row][index[row] - 1]);				
				if (sum >= 0) carry = 1;
				else {
					sum += 26;
					carry = 0;
				}

				temp[col] = IntToChar(sum);

				//printf("index=%d, arr[row][index] = %c, temp[col] = %c\n", index[row]-1, arr[row][index[row]-1], temp[col]);
			}
			else {
				//subtration
				int sub = CharToInt(arr[row][index[row]]) - CharToInt(temp[col]) - borrow;
				if (sub < 0) {
					borrow = 1;
					sub += 26;
				}
				else {
					borrow = 0;
				}

				temp[col] = IntToChar(sub);
			}
			index[row]--;
		}
	}
	for (int i = 0; i < DEPTH_SIZE; i++) {
		printf("%c", temp[i]);
	}
	return;
}
