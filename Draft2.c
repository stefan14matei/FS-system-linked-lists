#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "directoare.h"
#include "fisiere.h"


int main(void)
{
	Directory *root = NULL;
	int com = 0;
	char del[4] = "\n \0";
	char command[256];
	int flag = 1;
	char clone[100];

	while (flag == 1) {
		fgets(command, 100, stdin);
		strcpy(clone, command);
		char *p = strtok(clone, del);

		if (strcmp(p, "create") == 0) {
			create_fs(&root);

		} else if (strcmp(p, "delete") == 0) {
			aux_delete(&root);
			delete_fs(&root);
			flag = 0;

		} else if (strcmp(p, "touch") == 0) {
			char filename[100];
			char content[100];

			p = strtok(NULL, del);
			strcpy(filename, p);
			p = strtok(NULL, del);
			strcpy(content, p);
			touch(&root, filename, content);

		} else if (strcmp(p, "mkdir") == 0) {
			char dirname[100];

			p = strtok(NULL, del);
			strcpy(dirname, p);
			mkdir(&root, dirname);

		} else if (strcmp(p, "ls") == 0) {
			if (com)
				printf("\n");
			com = 0;
			ls(&root);
			printf("\n");

		} else if (strcmp(p, "pwd") == 0) {
			if (com)
				printf("\n");
			com = 0;
			pwd(&root);
			printf("\n");

		} else if (strcmp(p, "cd") == 0) {
			char dirname[100];

			p = strtok(NULL, del);
			strcpy(dirname, p);
			cd(&root, dirname);

		} else if (strcmp(p, "tree") == 0) {
			if (com)
				printf("\n");
			com = 0;
			tree(&root, 0);

		} else if (strcmp(p, "rm") == 0) {
			char filename[100];

			p = strtok(NULL, del);
			strcpy(filename, p);
			rm(&root, filename);

		} else if (strcmp(p, "rmdir") == 0) {
			char dirname[100];

			p = strtok(NULL, del);
			strcpy(dirname, p);
			rmdir(&root, dirname);

		} else if (strcmp(p, "find") == 0) {
			if (com)
				printf("\n");
			com = 1;
			char subcontent[100];
			int max, min_size, max_size;

			p = strtok(NULL, del);
			max = atoi(p);
			p = strtok(NULL, del);
			min_size = atoi(p);
			p = strtok(NULL, del);
			max_size = atoi(p);
			p = strtok(NULL, del);
			strcpy(subcontent, p);
			find(&root, max, min_size, max_size, subcontent, 0);
		}
	}
	return 0;
}
