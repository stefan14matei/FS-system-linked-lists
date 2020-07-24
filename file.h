#ifndef __FILE_H__
#define __FILE_H__

typedef struct Directory {
	char *name;

	struct list *FileList;

	struct list *DirList;

	struct Directory *parentDir;
} Directory;


typedef struct list {
	struct node *first;
} list;

typedef struct node {
	void *info;

	struct node *next;
} node;


typedef struct File {
	char *name;

	int size;

	char *data;

	Directory *dir;
} File;

#endif /* __FILE_H__ */
