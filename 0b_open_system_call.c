#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h> 
#include <errno.h>
#include <unistd.h>	//necessary for close() or else you get a warning
int main(int argc, char *argv[])
{ 
	int fd; 
	if(2 != argc){ 
		printf("\n Usage : \n"); return 1;
	} 
	errno = 0; 
	
	//open a file in read-only mode or create a file in read-only mode if it doesn't already exist.
	fd = open(argv[1],O_RDONLY|O_CREAT);

	//if fd (file descriptor) is equal to -1, there was an error. otherwise, success.
	if(-1 == fd){ 
		printf("\n open() failed with error [%s]\n",strerror(errno)); 
		//I did not add perror("open"); here because steerror(errno) was already provided
		return 1;
	} 
	else { 
		printf("\n Open() Successful\n");
		/* open() succeeded, now one can do read operations on the file opened
		since we opened it in read-only mode. Also once done with processing, the file needs to be
		closed.*/

		//close file. if closeError is equal to -1, there was an error. otherwise, success.
		int closeError = close(fd);
		if(closeError == -1){
			printf("\n close() failed with error: ");
			perror("close");
			printf("\n");
			return 1;
		}
		else{	printf("\n Close() Successful\n");}
	} 

	return 0;
}
