#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#ifndef WWPATH
#define WWPATH "/ilab/users/xm73/Xinyu/ww"
#endif


int main(int argc, char** argv){
	pid_t pid;
	int status;
	int mypipe[2];
	char buf[4096];
	int usererror = 0;
	for(int i = 2; i < argc; ++i){
		memset(buf,0,sizeof(buf));
		struct stat s;
		stat(argv[i],&s);
		if(s.st_mode & S_IFDIR){//it's a dir
			fprintf(stderr, "%s", "given a path of directory\n");
			usererror = 1;
			continue;
		}
		if(pipe(mypipe) == -1){
			fprintf(stderr, "%s", "error in pipe\n");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if(pid == 0){//child
			close(mypipe[0]);
			dup2(mypipe[1], 1);
			execl(WWPATH, WWPATH, argv[1], argv[i], NULL);
			exit(1);
		}
		else if(pid > 0){//parent
			if(waitpid(pid, &status, 0) == -1){
				fprintf(stderr, "%s", "error in wait\n");
				exit(EXIT_FAILURE);
			}
			else{
				close(mypipe[1]);
				int rd = read(mypipe[0], buf, sizeof(buf));
				if(rd > 0){//make sure there are some output
					if(i > 2){//skip the first file printed
						write(1, "\n", 1);//print a empty line before every non-empty output
					}
					write(1,buf, sizeof(buf));
				}
				close(mypipe[0]);
				if(WIFEXITED(status)){//terminated with exit
					if(WEXITSTATUS(status) != 0){//ww returns non zero
						usererror = 1;
						continue;
					}
				}
				else{
					usererror = 1;
					continue;
				}
			}
		}
		else{//pid is -1
			fprintf(stderr, "%s", "error in fork\n");
			exit(EXIT_FAILURE);
		}
	}
	if(usererror == 1){
		return(EXIT_FAILURE);
	}
	return 0;
}