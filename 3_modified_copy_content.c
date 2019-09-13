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
        int fdS, fdD;	//fdS = source file descriptor		fdD = destination file descriptor

        if(3 != argc){				//check args
                printf("\n Usage : \n"); 
		return 1;
        }
        errno = 0;
        fdS = open(argv[1],O_RDONLY);			//open source readonly

	//check for errors in openning files.
        if(-1 == fdS){
                printf("\n open() source file failed with error [%s]\n",strerror(errno));
                //I did not add perror("open"); here because strerror(errno) was already provided
                return 1;
        }
	else {
                /* open() succeeded for source.*/
		fdD = open(argv[2],O_WRONLY|O_CREAT, 0666);	
		//open (or create, if necessary) destination writeonly.
		//note that in this program and in copy_content.c the destination file will have read 
		//  and write permissions when program is done executing.
		
		if(-1 == fdD){
			printf("\n open() destination file failed with error [%s]\n",strerror(errno));
        	        //I did not add perror("open"); here because strerror(errno) was already provided
        	        return 1;
		}
		else{	/*open() destination success*/	}
        }
	
	/////////////////////////////READ-WRITE/////////////
	ssize_t bytesRead = 100;				//read up to 100 chars at a time
	ssize_t bytesWritten;					
	char* storageBuffer = (char*) malloc(sizeof(char)*100);	//store up to 100 chars at a time
	
	//read up to 100 chars from source into buffer. (will be less than 100 during the last turn)
	//replace '1's with 'A's in buffer.
	//write contents of buffer into destination.
	//add 'XYZ' to destination file.
	//repeat until done reading from source.
	//check for errors.
	while(bytesRead == 100){
		bytesRead = read(fdS,storageBuffer,100);
		
		if(bytesRead == -1){	
			printf("\n read() source file failed with error: "); 
			perror("read");	
			printf("\n");
			return 1;
		}
		else{	/* Read Source Successful*/	}
		
		for(int i = 0; i < bytesRead; i++){
			if(storageBuffer[i] == '1'){
				storageBuffer[i] = 'A';	
			}
			else{}
		}

		if(bytesRead == 100){
			bytesWritten = write(fdD,storageBuffer,bytesRead);
			bytesWritten = write(fdD,"XYZ",3);
		}
		else if(bytesRead >= 0 && bytesRead < 100){
			bytesWritten = write(fdD,storageBuffer,(bytesRead-1));
			bytesWritten = write(fdD,"XYZ",3);
		}
		else if(bytesWritten == -1){	
			printf("\n write() destination file failed with error: "); 
			perror("write");	
			printf("\n");
			return 1;
		}
		else{}				
		
	}	
	
	/////////////////////////////CLOSE///////////
	//close both files and check for errors.
	//destination will have read and write permissions.
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
