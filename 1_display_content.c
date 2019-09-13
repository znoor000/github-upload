#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>     //necessary for close() or else you get a warning
#include <stdlib.h>	//necessary in order to use malloc()
int main(int argc, char *argv[])
{
	///////////////////////////////OPEN///////////
        int fd;
        if(2 != argc){
                printf("\n Usage : \n"); 
		return 1;
        }
        errno = 0;
        fd = open(argv[1],O_RDONLY);
        if(-1 == fd){
                printf("\n open() failed with error [%s]\n",strerror(errno));
                //I did not add perror("open"); here because strerror(errno) was already provided
                return 1;
        }
        else {
                /* open() succeeded, now one can do read operations on the file opened
                since we opened it in read-only mode. Also once done with processing, the file needs to be
                closed.*/
        }
	
	/////////////////////////////READ/////////////
	int bytesRead = 100;					//will read bytes 100 at a time.
	char* storageBuffer = (char*) malloc(sizeof(char)*100);	//need a buffer to store characters  
								//  before printing.
	
	while(bytesRead == 100){
		bytesRead = read(fd,storageBuffer,100);
		
		if(bytesRead == -1){	
			printf("\n read() failed error: "); 
			perror("read");	
			printf("\n");
			return 1;
		}
		else{	/* Read Successful*/	}
		
		printf("%.*s", bytesRead, storageBuffer);
		//print 100 characters at a time from file using a buffer.
		//will end when reads less than 100 characters - it will 
		//  print those last characters and stop reading. or unless 
		//  there is an error.
	}
	printf("\n");	
	free(storageBuffer);		//it is good to clear the memory

	/////////////////////////////CLOSE////////////
        int closeError = close(fd);
        if(closeError == -1){
                printf("\n close() failed with error: ");
                perror("close");
                printf("\n");
                return 1;
        }
        else{   /* Close() Successful*/ 	}
	// close the file after reading and printing it to screen

        return 0;
}
