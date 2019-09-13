#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	char* filepath = argv[1];
	int returnval;

	//check file existence and store integer in returnval.
	//returnval integer represents whether file exists or if there is an error.
	returnval = access(filepath, F_OK);

	//if returnval is 0, file exists. other values represent errors.
	if(returnval == 0){
		printf("\n %s exists\n", filepath);
	}
	else{
		//if there was an error during access of the file, 
		//  "errno" is a global variable that gets updated to a value 
		//  that corresponds to the specific type of error resulting from access attempt.
		//Two such errors are ENOENT (file doesn't exist) and EACCES (file 
		//  is not accessible/readable/writtable)
		if(errno == ENOENT){
			printf("\n %s does not exist\n", filepath);
		}
		else if(errno == EACCES){
			printf("\n %s is not accessible\n", filepath);
		}
		perror("access");
		return 0;
	}

	//check read access 
	//  similar to check file existence
	returnval = access(filepath, R_OK);

	if(returnval == 0){
		printf("\n %s is readable\n", filepath);
	}
	else{
		printf("\n %s is not readable\n", filepath);
		perror("access");	
		return 0;
	}

	//check write access
	//  similar to check file existence
	returnval = access(filepath, W_OK);

	if(returnval == 0){
		printf("\n %s is writtable\n", filepath);
	}
	else{
		printf("\n %s is not writtable\n", filepath);
		perror("access");
		return 0;
	}

	return 0;
	
}
