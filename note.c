#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME 32
#define MAX_BODY 140

typedef enum {
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY,
} weekday_t;

typedef enum {
	JANUARY,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER,
} month_t;

typedef struct {
	short day;
	weekday_t weekday;
	month_t month;
	int year;
} date_t;

typedef struct {
	char name[MAX_NAME];
	date_t date;
	char body[MAX_BODY];
} note_t;


void print_menu(void)
{
	static const char* menu[] = {
		"[1] Create a new note.",
		"[2] List notes.",
		"[3] Update a note.",
		"[4] Delete a note.",
	};

	for (int i = 0; i < sizeof(menu) / sizeof(menu[0]); ++i) {
		puts(menu[i]);
	}
}

int main(void)
{
	int option;

	print_menu();
	while (option = getchar()) {
		switch (option) {
		case '1':
			printf("1!");
			break;
		case '2':
			printf("2!");
			break;
		case '3':
			printf("3!");
			break;
		case '4':
			printf("4!");
			break;
		case 'q':
			return 0;
		default:
			print_menu();
		}
		while (getchar() != '\n') ;
	}

	return 0;
}
