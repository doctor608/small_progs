#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include <time.h>

#define clear() for (int i = 0; i < 100; ++i) puts(""); 	
#define flush() while (getchar() != '\n');
#define MAX_NAME 32
#define MAX_BODY 140

typedef struct {
	char name[MAX_NAME];
	struct tm* timeinfo;
	char body[MAX_BODY];
} note_t;

note_t* g_notes[64];
int g_i = 0;

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

void list_notes(void)
{
	for (int i = 0; i < g_i; ++i) {
		printf("%s    %s", g_notes[i]->name, asctime(g_notes[i]->timeinfo));
	}
}

char* my_fgets(char* s, int n, FILE* stream) {
	fgets(s, n, stream);
	if (s[strlen(s) - 1] == '\n') {
		s[strlen(s) - 1] = '\0';
	}
	return s;
}

void create_newnote(void)
{
	if (g_i == 64) {
		fprintf(stderr, "Error: max number of notes\n");
		exit(1);
	}

	note_t* new_note;
	if ((new_note = malloc(sizeof(note_t))) == NULL) {
		fprintf(stderr, "Memory allocation error\n");
		exit(1);
	}

	printf("Name of note: ");
	my_fgets(new_note->name, MAX_NAME, stdin);
	
	puts("Note body:");
	char c;
	int i = 0;
	while(((c = getchar()) != '~') && (i <= MAX_BODY)) {
		new_note->body[i++] = c;
	}

	time_t rawtime;
	time(&rawtime);
	new_note->timeinfo = localtime(&rawtime);

	g_notes[g_i++] = new_note;
}

int main(void)
{
	int option;

	print_menu();
	while (option = getchar()) {
		flush();
		switch (option) {
		case '1':
			create_newnote();
			break;
		case '2':
			list_notes();
			break;
		case '3':
			break;
		case '4':
			 break;
		case 'q':
			return 0;
		}
	}

	return 0;
}
