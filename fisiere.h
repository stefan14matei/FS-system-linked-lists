#ifndef ___FISIERE___
#define ___FISIERE___

void touch(Directory **curent, char *filename, char *content)
{
	File *NewFile = (File *)malloc(sizeof(File));

	NewFile->size = strlen(content);
	NewFile->data = (char *)malloc(NewFile->size + 1);
	NewFile->name = (char *)malloc(strlen(filename) + 1);
	NewFile->dir = *curent;

	strcpy(NewFile->name, filename);
	strcpy(NewFile->data, content);

	struct node *new_node = (struct node *)malloc(sizeof(struct node));

	new_node->info = (void *)NewFile;
	struct node *curent_node = (*curent)->FileList->first;

	if (curent_node == NULL) {
		(*curent)->FileList->first = new_node;
		new_node->next = NULL;
		return;
	}

	if (strcmp(((File *)curent_node->info)->name,
			  ((File *)new_node->info)->name) > 0) {
		new_node->next = curent_node;
		(*curent)->FileList->first = new_node;
		return;
	}

	while (curent_node->next != NULL) {
		if (strcmp(((File *)curent_node->next->info)->name,
				  ((File *)new_node->info)->name) > 0) {
			new_node->next = curent_node->next;
			curent_node->next = new_node;
			return;
		}
		curent_node = curent_node->next;
	}

	new_node->next = NULL;
	curent_node->next = new_node;
}

void find(Directory **curent, int max_depth, int min_size,
		  int max_size, char *subcontent, int depth)
{
	if (depth > max_depth)
		return;
	node *files = (*curent)->FileList->first;

	while (files) {
		if (((File *)files->info)->size  >= min_size &&
		   ((File *)files->info)->size <= max_size &&
		   strstr(((File *)files->info)->data, subcontent) != NULL)
			printf("%s ", ((File *)files->info)->name);
		files = files->next;
	}
	node *directories = (*curent)->DirList->first;

	while (directories) {
		Directory *new_directory = ((Directory *)directories->info);

		find(&new_directory, max_depth, min_size,
			 max_size, subcontent, depth + 1);
		directories = directories->next;
	}
}
#endif
