#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define clear() for (int i = 0; i < 100; ++i) puts("");
#define flush() while (getchar() != '\n');
#define array_size(arr) sizeof(arr) / sizeof(arr[0])

#define MAX_NAME 32
#define MAX_BODY 140
#define MAX_NOTES 64
#define END_OF_INPUT '~'
#define NEW_LINE '~'

typedef struct {
	int id;
	time_t time;
	char name[MAX_NAME];
	char body[MAX_BODY];
} note_t;

note_t* g_notes[MAX_NOTES];
int g_i = 0;

void print_menu(void) {
	static const char* menu[] = {
		"[1] Create a new note.",
		"[2] List notes.",
		"[3] Update a note.",
		"[4] Delete a note.",
	};

	for (size_t i = 0; i < array_size(menu); ++i) {
		puts(menu[i]);
	}
}

void list_notes(void) {
	char buffer[25];

	if (g_i == 0) {
		printf("There are no notes\n");
		return;
	}

	puts("---------------------------------------------------------------------");
	printf("| %-3s | %-32s | %-23s  |\n", "id", "name", "date");
	puts("---------------------------------------------------------------------");

	for (int i = 0; i < g_i; ++i) {
		strcpy(buffer, ctime(&g_notes[i]->time));
		buffer[array_size(buffer) - 1] = '\0';
		printf("| %-3d | %-32s | %-23s |\n", g_notes[i]->id, g_notes[i]->name, buffer);
		puts("---------------------------------------------------------------------");
	}
}

char* my_fgets(char* s, int n, FILE* stream) {
	fgets(s, n, stream);
	if (s[strlen(s) - 1] == '\n') {
		s[strlen(s) - 1] = '\0';
	}
	return s;
}

void create_note(void)
{
	if (g_i == MAX_NOTES) {
		fprintf(stderr, "Error: max number of notes\n");
		exit(1);
	}

	note_t* new_note;
	if ((new_note = malloc(sizeof(note_t))) == NULL) {
		fprintf(stderr, "Memory allocation error\n");
		exit(1);
	}

	new_note->id = (g_i == 0) ? 1 : g_notes[g_i - 1]->id + 1;

	printf("Name of note: ");
	my_fgets(new_note->name, MAX_NAME, stdin);
	
	puts("Note body:");
	char c;
	int i = 0;
	while(((c = getchar()) != END_OF_INPUT) && (i <= MAX_BODY)) {
		new_note->body[i++] = c;
	}

	new_note->time = time(NULL);
	g_notes[g_i++] = new_note;

	FILE* out;
	if (access("notes.csv", F_OK) == -1) {
		out = fopen("notes.csv", "w");
		fprintf(out, "id,name,time,body\n");
	} else {
		out = fopen("notes.csv", "a");
	}

	char buffer[MAX_BODY];
	strcpy(buffer, new_note->body);
	for (int i = 0; buffer[i] != '\0'; ++i) {
		if (buffer[i] == '\n') {
			buffer[i] = NEW_LINE;
		}
	}
	fprintf(out, "%d,%s,%ld,%s\n", new_note->id, new_note->name, new_note->time, buffer);
	fclose(out);
}

int main(void)
{
	int option;

	print_menu();
	while ((option = getchar())) {
		flush();
		switch (option) {
		case '1':
			create_note();
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
