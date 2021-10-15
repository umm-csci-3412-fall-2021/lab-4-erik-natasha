#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static int num_dirs, num_regular;

bool is_dir(const char* path) {
  /*
   * Use the stat() function (try "man 2 stat") to determine if the file
   * referenced by path is a directory or not.  Call stat, and then use
   * S_ISDIR to see if the file is a directory. Make sure you check the
   * return value from stat() in case there is a problem, e.g., maybe the
   * the file doesn't actually exist.
   */
	//Create a buffer
	printf("we are at the start of is_dir %s", path);
	struct stat buf;
	//Store metadata about the file the path points to
	if(stat(path, &buf) != 0){
		return NULL;
	}

	//Store whether the file is a directory
	bool isDirectory = S_ISDIR(buf.st_mode);

//	free(&buf);

	return isDirectory;
}

/* 
 * I needed this because the multiple recursion means there's no way to
 * order them so that the definitions all precede the cause.
 */
void process_path(const char*);

void process_directory(const char* path) {
  /*
   * Update the number of directories seen, use opendir() to open the
   * directory, and then use readdir() to loop through the entries
   * and process them. You have to be careful not to process the
   * "." and ".." directory entries, or you'll end up spinning in
   * (infinite) loops. Also make sure you closedir() when you're done.
   *
   * You'll also want to use chdir() to move into this new directory,
   * with a matching call to chdir() to move back out of it when you're
   * done.
   */
printf("we are in process_directory %s", path);
	struct dirent *file;
	chdir(path);
	DIR* currentDir = opendir(path);
	while((file=readdir(currentDir))){
		char* fileName = file->d_name;
		if(strcmp(fileName, ".") != 0 || strcmp(fileName, "..") != 0){
	//		process_path(strcat(path, fileName));
			process_path(fileName);
		}
	}
	closedir(currentDir);
	chdir("..");
}

void process_file(const char* path) {
  /*
   * Update the number of regular files.
   */
	num_regular++;
}

void process_path(const char* path) {
  if (is_dir(path)) {
    process_directory(path);
  } else {
    process_file(path);
  }
}

int main (int argc, char *argv[]) {
	printf("we are at the start of main %s", argv[1]);
  // Ensure an argument was provided.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  process_path(argv[1]);

  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
