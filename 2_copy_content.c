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
        int fdS, fdD;	//fdS = source file descriptor		fdD = destination file decriptor
        
	if(3 != argc){				//command and rwo arguments necessary
                printf("\n Usage : \n"); 
		return 1;
        }
        errno = 0;
        fdS = open(argv[1],O_RDONLY);		//only read source file
	
	//check for errors in openning the files
        if(-1 == fdS){
                printf("\n open() source file failed with error [%s]\n",strerror(errno));
                //I did not add perror("open"); here because strerror(errno) was already provided
                return 1;
        }
	else {
                /* open() succeeded for source.*/
		fdD = open(argv[2],O_WRONLY|O_CREAT, 0666);	
		//write to destination file (and create it if it doesnt exist)
		if(-1 == fdD){
			printf("\n open() destination file failed with error [%s]\n",strerror(errno));
                	//I did not add perror("open"); here because strerror(errno) was already provided
                	return 1;
		}
		else{	/*open succeeded for destination*/	}

        }
	
	/////////////////////////////READ-WRITE/////////////
	ssize_t bytesRead = 100;		// read 100 chars at a time
	ssize_t bytesWritten;			
	
	char* storageBuffer = (char*) malloc(sizeof(char)*100);	
	//storage for reading/writing up to 100 chars at a time
	
	//read 100 chars at a time from the source file into the buffer.
	//write 100 chars at a time from buffer to the destination file.
	//last pass of the above two steps will likely be with less than 100 chars.
	//if bytes Read or Written are either -1, there was an error.
	while(bytesRead == 100){
		bytesRead = read(fdS,storageBuffer,100);
		
		if(bytesRead == -1){	
			printf("\n read() source file failed with error: "); 
			perror("read");	
			printf("\n");
			return 1;
		}
		else{	/* Read Source Successful*/	}
		
		bytesWritten = write(fdD,storageBuffer,bytesRead);
		if(bytesWritten == -1){	
			printf("\n write() destination file failed with error: "); 
			perror("write");	
			printf("\n");
			return 1;
		}
		else{	/* Write Destination Successful*/	}

	}	

	/////////////////////////////CLOSE////////////

	//close both files when done and check for errors in closing
        int closeErrorS = close(fdS);
	if(closeErrorS == -1){
		printf("\n close() source file failed with error: ");
		perror("close");
		printf("\n");
		return 1;
	}
        else{   /* Close() Source Successful*/ 	}

	int closeErrorD = close(fdD);
        if(closeErrorD == -1){
                printf("\n close() destination file failed with error: ");
                perror("close");
                printf("\n");
                return 1;
        }
	else{   /* Close() Destination Successful*/ 	}


        return 0;
}
