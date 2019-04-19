#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	DIR *dp;			//Directory Pointer. For directory's information.
	struct dirent *dent;					//For directory's information.
	
	if(argc != 2) {	//Check Arguments
		printf("Argument Error! \n");
		exit(1);
	}
	
	if(mkdir(argv[1]) == -1){	//Make Directory
		perror(argv[1]);
		exit(1);
	}
	
	if((dp = opendir(argv[1])) == NULL) {	//Check Directory File and OPEN...
		perror("opendir");
		exit(1);
	}
	
	if(chdir(argv[1]) == -1){	//Change Directory
		perror(argv[1]);
		exit(1);
	}
	
	return 0;
}
