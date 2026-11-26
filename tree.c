#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>


unsigned int walkp[64] = {0};
unsigned int nd = 0;
unsigned int nf = 0;

int listdir(const char *path, unsigned int walk) {
	struct dirent *dentry;
	struct dirent *dentry1;
	DIR *dptr = opendir(path);
	DIR *dptr1 = opendir(path);

	if(dptr == NULL) {
		printf("\nERROR: %s\n", strerror(errno));
		return -1;
	}
	
	unsigned int counter = 0;
	//unsigned int index = 0;
	while(dentry1 = readdir(dptr1)) {
		if(!(strcmp(dentry1->d_name, ".") == 0) && !(strcmp(dentry1->d_name, "..") == 0)) {
			counter++;
			//printf("a");
		}
	}
	closedir(dptr1);
	
	unsigned int index = 0;
	//unsigned int *wptr = &walkp[0];
	while(dentry = readdir(dptr)) {
		if(!(strcmp(dentry->d_name, ".") == 0) && !(strcmp(dentry->d_name, "..") == 0)) {
			//dentry->d_type!=10?nf++:printf("");
			nf++;
			index++;
			for(int i = 0; i < walk; i++) {
				walkp[i+1]==1?printf("    "):printf("│   ");
				//printf("%d",walkp[i]);
				unsigned int walkp[64] = {0};
			}
			//printf("");
			//printf("├── ");
			index==counter?printf("└── "):printf("├── ");
			printf("%s\n",dentry->d_name);
			//printf("\t%d\n",dentry->d_type);
			if(dentry->d_type == 4) {
				nd++;	
				//printf("\n");
				//for(int i = 0; i <= walk; i++) {
				//	printf("\t");
				//}
				char *cpath = malloc((strlen(path)+1) + 1 + strlen(dentry->d_name));
				strcpy(cpath, path);
			
				char *wpath = strcat(cpath, dentry->d_name);
				wpath = strcat(wpath, "/");
				
				walk++;
				//walk >= 1?printf("│"):printf("");
				//printf("%s\n", wpath);
				if(index == counter) {
					walkp[walk] = 1;
					//printf("%d",walkp[walk]);
				}
				listdir(wpath, walk);
				if(index==counter)
					walkp[walk] = 0;
				walk--;
				

				free(cpath);
			}	
			
		}
		//printf("\n");
	}
	closedir(dptr);
	return 0;
}


int main(int argc, char *argv[]) {
	
	if(argc == 1) {
		char cwd[4096];
		printf(getcwd(cwd, sizeof(cwd)));	
		listdir(getcwd(cwd, sizeof(cwd)), 0);
		printf("\n%d directories, %d files\n", nd, nf-nd);
		return 0;
	}	
	
	
	for(int i = 1; i < argc; i++) {
		printf(argv[i]);
		listdir(argv[i], 0);
		printf("\n%d directories, %d files\n", nd, nf-nd);
	}
	return 0;
}
