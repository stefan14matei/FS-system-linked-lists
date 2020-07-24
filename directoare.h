#ifndef ___DIRECTOARE___
#define ___DIRECTOARE___

void create_fs(Directory **root)
{
	(*root) = (Directory *)malloc(sizeof(Directory));
	(*root)->DirList = (list *)malloc(sizeof(list));
	(*root)->FileList = (list *)malloc(sizeof(list));
	(*root)->name = (char *)malloc(sizeof("/"));

	strcpy((*root)->name, "/");

	(*root)->parentDir = NULL;
	(*root)->FileList->first = NULL;
	(*root)->DirList->first = NULL;

}



void mkdir(Directory **curent, char *filename)
{
	Directory *NewDir = (Directory *)malloc(sizeof(Directory));

	NewDir->FileList = (struct list *)malloc(sizeof(struct list));
	NewDir->DirList = (struct list *)malloc(sizeof(struct list));
	NewDir->DirList->first = NULL;
	NewDir->FileList->first = NULL;
	NewDir->parentDir = *curent;
	NewDir->name = (char *)malloc(strlen(filename) + 1);

	strcpy(NewDir->name, filename);

	struct node *new_node = (struct node *)malloc(sizeof(struct node));

	new_node->info = (void *)NewDir;
	struct node *curent_node = (*curent)->DirList->first;

	if (curent_node == NULL) {
		(*curent)->DirList->first = new_node;
		new_node->next = NULL;
		return;
	}

	if (strcmp(((Directory *)curent_node->info)->name,
			  ((Directory *)new_node->info)->name) > 0) {
		new_node->next = curent_node;
		(*curent)->DirList->first = new_node;
		return;
	}

	while (curent_node->next != NULL) {
		if (strcmp(((Directory *)curent_node->next->info)->name,
				  ((Directory *)new_node->info)->name) > 0) {
			new_node->next = curent_node->next;
			curent_node->next = new_node;
			return;
		}
		curent_node = curent_node->next;
	}
	new_node->next = NULL;
	curent_node->next = new_node;
}

void ls(Directory **curent)
{
	node *browse = (*curent)->FileList->first;

	while (browse) {
		printf("%s ", ((File *)browse->info)->name);
		browse = browse->next;
	}
	browse = (*curent)->DirList->first;
	while (browse) {
		printf("%s ", ((Directory *)browse->info)->name);
		browse = browse->next;
	}
}

void pwd(Directory **curent)
{
	if ((*curent)->parentDir) {
		Directory *parent = (*curent)->parentDir;

		pwd(&parent);
		if (parent->parentDir)
			printf("/%s", (*curent)->name);
		else
			printf("%s", (*curent)->name);
	} else
		printf("/");
}

void cd(Directory **curent, char *dirname)
{
	if (strcmp(dirname, "..") == 0) {
		(*curent) = (*curent)->parentDir;
		return;
	}
	node *curent_node = (*curent)->DirList->first;

	if (curent_node) {
		while (curent_node->next != NULL) {
			if (strcmp(((Directory *)curent_node->info)->name,
					  dirname) == 0) {
				(*curent) = ((Directory *)curent_node->info);
				return;
			}
			curent_node = curent_node->next;
		}
		if (strcmp(((Directory *)curent_node->info)->name,
				   dirname) == 0) {
			(*curent) = ((Directory *)curent_node->info);
			return;
		}
	}
	printf("Cannot move to '%s': No such directory!\n", dirname);
}

void tree(Directory **curent, int depth)
{
	int i;

	for (i = 1; i <= depth; i++)
		printf("    ");
	printf("%s\n", (*curent)->name);

	node *files = (*curent)->FileList->first;

	while (files) {
		for (i = 0; i <= depth; i++)
			printf("    ");
		printf("%s\n", ((File *)files->info)->name);
		files = files->next;
	}

	node *directories = (*curent)->DirList->first;

	while (directories) {
		tree(((Directory **)(&(directories->info))), depth + 1);
		directories = directories->next;
	}
}

void rm(Directory **curent, char *filename)
{
	node *files = (*curent)->FileList->first;

	if (files) {
		if (strcmp(((File *)files->info)->name, filename) == 0) {
			(*curent)->FileList->first = files->next;
			free(((File *)files->info)->name);
			free(((File *)files->info)->data);
			free(((File *)files->info));
			free(files);
			return;
		}
		while (files->next) {
			if (strcmp(((File *)files->next->info)->name,
					   filename) == 0) {
				node *del = files->next;

				if (files->next->next)
					files->next = files->next->next;
				else
					files->next = NULL;
				free(((File *)del->info)->name);
				free(((File *)del->info)->data);
				free(((File *)del->info));
				free(del);
				return;
			}
			files = files->next;
		}
	}
	printf("Cannot remove '%s': No such file!\n", filename);
}

void rmdir(Directory **curent, char *Directory_name)
{
	node *directories = (*curent)->DirList->first;
	node *del = NULL;

	if (directories) {
		if (strcmp(((Directory *)directories->info)->name,
				  Directory_name) == 0) {
			(*curent)->DirList->first = directories->next;
			del = directories;
		} else
			while (directories->next) {
				if (strcmp(((Directory *)directories
							->next->info)->name,
						   Directory_name) == 0) {
					del = directories->next;
					directories->next =
					directories->next->next;
					break;
				}
				directories = directories->next;
			}
	}
	if (del == NULL) {
		printf("Cannot remove '%s': No such directory!\n",
			   Directory_name);
		return;
	}

	Directory *directory = ((Directory *)del->info);
	node *files = directory->FileList->first;

	while (files) {
		node *del_file = files;

		files = files->next;
		rm(&directory, ((File *)del_file->info)->name);
	}

	node *browse = directory->DirList->first;

	while (browse) {
		node *del_directory = browse;

		browse = browse->next;
		rmdir(&directory, ((Directory *)del_directory->info)->name);
	}

	free(directory->name);
	free(directory->FileList);
	free(directory->DirList);
	free(directory);
	free(del);
}
void delete_fs(Directory **root)
{
	free((*root)->name);
	free((*root)->FileList);
	free((*root)->DirList);
	free((*root));
}
void aux_delete(Directory **root)
{
	while ((*root)->parentDir)
		cd(root, "..");

	node *files = (*root)->FileList->first;

	while (files) {
		node *del_file = files;

		files = files->next;

		rm(root, ((File *)del_file->info)->name);
	}

	node *browse = (*root)->DirList->first;

	while (browse) {
		node *del_directory = browse;

		browse = browse->next;

		rmdir(root, ((Directory *)del_directory->info)->name);
	}

}
#endif
