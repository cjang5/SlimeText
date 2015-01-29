#include <stdio.h>     //include for printf, etc
#include <stdlib.h>    //include for standard stuff
#include <string.h>    //include for strcmp

int main(int argc, char* argv[]) {
	//Startup splash
	printf("     #  __           &\n");
	printf("      *     *     --_            *\n");
	printf(" *_- Welcome to SlimeText v0.1 -_*\n");
	printf("\"It's not as good as Sublime Text!\" *   *\n");
	printf("   @ *          *      *    \n");
	printf("   *     - #        #      * -*     $\n");
	printf("       * \n");

	//The filename
	//TODO: make sure there is a filename for now assume there always is one
	char * filename = argv[1];

	/**
	 * First we check if the file exists. 
	 * If it doesn't we create the file and open it for appending
	 */
	FILE * file = fopen(filename, "r+");

	/**
	 * If the file doesn't exist, we create a new one
	 */
	if (file == NULL) {
		printf("[SLIME TEXT]~$: Creating %s...\n", filename);
		file = fopen(filename, "w");
		fclose(file);
	}

	//open the (newly created) file
	printf("[SLIME TEXT]~$: Opening %s...\n", filename);

	/**
	 * Here we declare the CAPACITY constant which we will set to 50 for now
	 * We also create the char array 'line' which wil represent the current
	 * command in the 'shell'
	 */
	int CAPACITY = 50; //constant
	char line[CAPACITY]; //current command in line

    //check for empty file
    int EMPTY;
    fseek(file, 0, SEEK_END);
    EMPTY = ftell(file);

    /**
     * Here we rewind the file back to the beginning so that when
     * we try to print the contents or copy the contents to the local
     * array we won't find nothing
     */
    rewind(file);

	//declare a local array of char*s that will hold our file contents
	char *lines[10];
 
 	if (EMPTY <= 0) { //if the file is empty
 		//we allocate memory for the 10 lines
 		for (int i = 0; i < 10; i++)
 			lines[i] = (char *) malloc(CAPACITY);

 		//then close and reopen the file
		fclose(file);
		file = fopen(filename, "r+");
	}
	else { //otherwise, we store the contents in 'lines'
		for (int i = 0; i < 10; i++) {
			//first allocating memory
			lines[i] = (char *) malloc(CAPACITY);

			//getting each line in the file
			fgets(lines[i], CAPACITY, file);

			//and putting a nullbyte on each line (except the last one)
			if (i < 9 && strlen(lines[i]) > 1)
				lines[i][strlen(lines[i]) - 1] = 0;
		}
	}
	
	/** 
	 * Main loop
	 * This is where we can parse commands and edit the file, etc
	 */
	int RUNNING = 1;
	int CHANGES_MADE = 0;

	while (RUNNING) {
		//shell text
		printf("[SLIME TEXT]~$: ");
		
		/**
		 * Here we get the next command from stdin
		 * and we make sure to remove the hidden \n character at the end
		 * so that we can properly parse the command
		 */
		fgets(line, CAPACITY, stdin);
		line[strlen(line) - 1] = 0; //add the nullbyte

		/**
		 * Parse the command
		 * ~$ a <LINE NUMBER> "..." - Appends text to the given line number
		 * ~$ p 			        - Prints contents of the file
		 * ~$ / "..." 				- Finds given text and finds all occurences in file
		 * ~$ w 					- Writes changes to file (overwrites)
		 * ~$ q						- Quits SLIME TEXT and closes the file
		 * TODO: Add more commands
		 */
		if (!strcmp(line, "q") || !strcmp(line, "Q")) { 
			//free memory
			for (int i = 0; i < 10; i++)
				free(lines[i]);

			fclose(file);

			//exit message
			printf("[!] Exiting Slime Text...\n");

			return 0;
			//TODO: Check if there are unsaved changes
		} 
		// print the contents of the local file
		else if (!strcmp(line, "p") || !strcmp(line, "P")) { 
			//print the contents of the file
			for (int i = 0; i < 10; i++)
				if (i < 9) {
					if (!strcmp(lines[i], "\n"))
						lines[i][strlen(lines[i]) - 1] = 0;

					printf("[%d] %s\n", i+1, lines[i]);
				}
				else if (i == 9)
					printf("[10]%s\n", lines[i]);

			//end of file
			printf("[!] END OF FILE REACHED!\n");

			//go back to the beginning of the file
			rewind(file);
		}
		// Append a new line of text
		else if (line[0] == 'a') {
			/**
			 * The way appending will work is we strcat the given
			 * text to the local array of char*s and then
			 * when "write" is called we will go in order and write
			 * each line to the file
			 */
			int lineNum = 0;
			//char command = ' ';
			char * str = (char *) malloc(CAPACITY);

			//parse the command
			sscanf(line, "a %d %[^\n]", &lineNum, str);
			
			//append the given text to the appropriate line
			strcat(lines[lineNum-1], str);
		
			//indicate that changes have been made
			CHANGES_MADE = 1;
			
			//free memory
			free(str);
		}	
		// Save the file
		else if (!strcmp(line, "w") || !strcmp(line, "W")) {
			//if changes have been made, we write the changes
			if (CHANGES_MADE == 1) {
				for (int i = 0; i < 10; i++)
					if (i < 9)
						fprintf(file, "%s\n", lines[i]);
					else
						fprintf(file, "%s", lines[i]);

				printf("[SLIME TEXT]~$: CHANGES SAVED\n");

				//revert the CHANGES_MADE flag
				CHANGES_MADE = 0;
			}
			else //otherwise no need to write anything
				printf("[SLIME TEXT]~$: NO CHANGES MADE\n");
		}
		// Search for text in the file
		else if (line[0] == '/') {
			//the text we are looking for
			char * str = (char *) malloc(CAPACITY);

			//parse the command
			sscanf(line, "/ %[^\n]", str);

			/**
			 * indicator of whether we have found the string or not
			 * if found is NULL, then we know we haven't found the string
			 * But if it isn't , then we have
			 */
			char * found = (char *) malloc(CAPACITY);

			//loop through the contents, searching using strstr
			for (int i = 0; i < 10; i++) {
				found = strstr(lines[i], str);

				//if we find the string, we print what line we found it in
				if (found != NULL)
					printf("[!] \'%s\' FOUND IN LINE %d\n", str, i+1);
			}
		}

	}

	//fclose(file);

	return 0;
}










