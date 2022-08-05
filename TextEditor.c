/*****************************************************
 * @author   : Rashik Shahriar Akash (202-15-3825)   *
 * @file     : qedit 1.1-stable.c                    *
 * @created  : Friday Oct 23, 2020 19:14:33 +06      *
 *****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str[100000][100000];  // <-- Main buffer to store the contents of the working file

/*typedef struct prompt
{
    char command;
    int parameter;
} prompt;*/

char defaultPrompt()
{
    char c;

    printf("\n\n");
    printf("\t/---------------------------------------------------------------\\\n");
    printf("\t|                                                               |\n");
    printf("\t|  QEdit, a CLI based line text editor. (Version 1.1 stable)    |\n");
    printf("\t|                                                               |\n");
    printf("\t|---------------------------------------------------------------|\n");
    printf("\t| Available Commands:                                           |\n");
    printf("\t|---------------------------------------------------------------|\n");
    printf("\t|                                                               |\n");
    printf("\t| 1. (O)pen an existing file                                    |\n");
    printf("\t| 2. (C)reate a new empty file                                  |\n");
    printf("\t| 3. (D)elete a file                                            |\n");
    printf("\t| 4. (E)xit the program                                         |\n");
    printf("\t|                                                               |\n");
    printf("\t|---------------------------------------------------------------|\n");
    printf("\t| Example: Enter '3', 'E', or 'e' to exit the program.          |\n");
    printf("\t\\---------------------------------------------------------------/\n\n");

    printf(" --> Enter a command: ");
    scanf("%c", &c);

    return c; // <-- Pass the command to the main program
}

char openPrompt()
{
    char c;

    printf("\n");
    printf("\t/---------------------------------------------------------------\\\n");
    printf("\t|                        Editing Mode                           |\n");
    printf("\t|---------------------------------------------------------------|\n");
    printf("\t| Available Commands :                                          |\n");
    printf("\t|---------------------------------------------------------------|\n");
    printf("\t| 1. (C)reate a new line                                        |\n");
    printf("\t| 2. (E)dit a line                                              |\n");
    printf("\t| 3. (D)elete a line                                            |\n");
    printf("\t| 4. (S)ave and return to main menu                             |\n");
    printf("\t| 5. (R)eturn to main menu without saving                       |\n");
    printf("\t|---------------------------------------------------------------|\n");
    printf("\t| Example: Enter '2', 'E', or 'e' to edit a specific line.      |\n");
    printf("\t\\---------------------------------------------------------------/\n\n");

    printf(" --> Enter a command: ");
    scanf("%c", &c);

    return c; // <-- Pass the command to the main program
}

void printFile(int lines, int max_chars, char str[lines][max_chars+1])
{
    int i;
    
    printf("/---------------------------------------------------------------------------------\\\n");
    printf("  Line |                             Content                                      \n");
    printf("\\---------------------------------------------------------------------------------/\n");

    for (i = 0; i < lines; i++)
    {
        printf("|  %-2.0d  | ", (i+1));
        printf("%s", str[i]);
    }
    printf("\\---------------------------------------------------------------------------------/\n\n");
}

void egg();

int main()
{
    int i = 0, j = 0, lines = 0, max_chars = 99999;

    char command = '\0';
    int parameter = 0;
    char filename[100];
    FILE *textFile;

    while (1)
    {
        if (i != 0)
            getchar(); // <-- catches stray newline characters

        if (command == '\0')
            command = defaultPrompt();

        // Opening a File (openfile)
        // ------------------------------------------------------------------------------
        if (command == '1' || command == 'O' || command == 'o')
        {
            printf("\n --> Enter the name and path to the file: ");
            scanf("%s", &filename);

            //---------------------------------------------------------------------------
            textFile = fopen (filename,"r"); // <-- opens the file within this program in 'Read Only' mode

            if (textFile == NULL)       // <-- Checks if the file exists or not
            {
                printf("\n\n\t\t\t --> File doesn't exist! <-- \n\n");
                i = 1;
                command = '\0';
            }

            else
                {
                char dump;
                lines = 0;
                for (dump = getc(textFile); dump != EOF; dump = getc(textFile)) // <-- This loop reads every character in the file
                {
                    if (dump == '\n')       // <-- If the character is a newline then...
                    {
                        lines += 1;         // <-- ...it increases the total number of lines by 1 (which is by Default 0)
                    }
                }
                
                fclose(textFile);   // <-- Closes the file
                //---------------------------------------------------------------------------
                
                //---------------------------------------------------------------------------
                textFile = fopen (filename,"r"); // <-- opens the file within this program in 'Read Only' mode

                printf("\n\t/---------------------------------------------------------------\\\n");
                printf("\t  Opening file : %s \n", filename);
                printf("\t\\---------------------------------------------------------------/\n");

                for (i = 0; i < lines; i++)
                {
                    fgets(str[i], max_chars, textFile); // <-- Copies contents from the file 'line by line' to the buffer
                    //fgets(output array, 100000, input file)
                }

                fclose(textFile);   // <-- Closes the file
                //---------------------------------------------------------------------------

                printFile(lines, max_chars, str); // <-- Print the buffer which contains the files contents

                int catch = 1;      // <-- Flag to catch stray newlines or other characters interfering with stdin

                while(1)
                {
                    if (catch == 1)
                        getchar(); // <-- catches stray newline characters
                    catch = 0;

                    command = openPrompt();

                    // Creating a new line at the end (createline.of)
                    // ----------------------------------------------------------------------
                    if (command == '1' || command == 'C' || command == 'c')
                    {
                            if (lines == 100000)
                            {
                                printf("\t --> Max File Size Reached! <-- \n");
                                break;
                            }

                            else
                            {
                                printFile(lines, max_chars, str);
                                printf("\t/ Last line --> %s", str[lines-1]);
                                printf("\t\\ New line  --> ");
                                    getchar(); // <-- catches stray newline characters
                                fgets(str[lines], max_chars, stdin);
                                lines++;
                                printFile(lines, max_chars, str);
                                catch = 0;
                            }
                    }

                    // Edit a line (editline.of)

                    // ----------------------------------------------------------------------
                    else if (command == '2' || command == 'E' || command == 'e')
                    {
                        while(1)
                        {
                            printFile(lines, max_chars, str);
                            printf("\n --> Enter a line number to edit or 0 to return to the Editing menu: ");
                            scanf("%d", &parameter);
                            if (parameter == 0)
                            {
                                getchar(); // <-- catches stray newline characters
                                break;
                            }
                            while (parameter > 100000) // <-- When line number crosses the buffer line limit
                            {
                                printf("\n\t\t\t\t --> Out of bounds! <-- \n"); 
                                printf("\n --> Enter a line number to Edit or 0 to return to the Editing menu: ");
                                scanf("%d", &parameter); // <-- Get line number again
                            }
                            
                            parameter--; // <-- converts line number to array index

                            if (parameter > lines) // <-- If line to be edited is not the lines already there or not the line directly after the last line
                            {
                                for (i = lines; i <= parameter; i++) // <-- replace lines between the last line and currently editing line 
                                {
                                    str[i][0] = '\n'; // <-- with a newline
                                    str[i][1] = '\0'; // <-- and a null character
                                }
                            }

                            i = parameter; // <-- assigning line number to i for better code readability

                            printf("\n");
                            printf("/ Original --> %s", str[i]); // <-- i == parameter == line index to be edited
                            printf("\\  Edited  --> ");
                            getchar(); // <-- catches stray newline characters
                            fgets(str[i], max_chars, stdin);

                            if (lines <= parameter) // <-- If the line is after existing lines
                                lines = parameter + 1; // <-- increase line number by 1

                            printf("\n");
                        }
                    }

                    // Delete a line (deleteline.of)
                    // ----------------------------------------------------------------------
                    else if (command == '3' || command == 'D' || command == 'd')
                    {
                        while(1)
                        {
                            printFile(lines, max_chars, str);
                            printf("\n --> Enter a line number to Delete or 0 to return to the Editing menu: ");
                            scanf("%d", &parameter);
                            if (parameter == 0)
                            {
                                getchar(); // <-- catches stray newline characters
                                break;
                            }
                            while (parameter > lines) // <-- If the line already doesn't exist
                            {
                                printf("\n\t\t\t\t --> Invalid Line! <-- \n");
                                printf("\n --> Enter a line number to delete or 0 to return to the Editing menu: ");
                                scanf("%d", &parameter); // <-- Get a new line number
                            }

                            if (parameter == 0) // <-- If zero is entered
                                break; // <-- Return to main menu
                            
                            parameter--; // <-- line number to array index

                            printf("\n");

                            for (i = parameter; i < (lines - 1); i++)
                            {
                                for (j = 0; j < 1000; j++)
                                {
                                    str[i][j] = str[i+1][j]; // <-- Shifts lines below the deleted line to up 1 line
                                }
                            }

                            lines--; // <-- decrease line number by 1 because of deletion

                            printf("\n");
                        }
                    }

                    // Save and Return to main menu (save.of)
                    // ----------------------------------------------------------------------
                    else if (command == '4' || command == 'S' || command == 's')
                    {
                        textFile = fopen (filename,"w");

                        for (i = 0; i < lines; i++)
                        {
                            fputs(str[i],textFile); // <-- Write changes to the main file from the string buffer
                        }

                        fclose(textFile);

                        printf("\n");

                        break;
                    }

                    // Return without saving (discard.of)
                    // ----------------------------------------------------------------------
                    else if (command == '5' || command == 'R' || command == 'r')
                    {
                        printf("\n");

                        break;
                    }

                    // Invalid Command
                    // ----------------------------------------------------------------------
                    else
                    {
                        printf("\t\t\t --> Invalid Command! Try again. <-- \n");
                    }
                }

            }
        }

        // Creating a new File (createfile)
        // ------------------------------------------------------------------------------
        else if (command == '2' || command == 'C' || command == 'c')
        {

            printf("\n --> Enter the name and path to the file: ");
            scanf("%s", &filename);

            printf("\n\t/---------------------------------------------------------------\\\n");
            printf("\t  Creating file : %s \n", filename);
            printf("\t\\---------------------------------------------------------------/\n");

            // Opens the newly created file in edit mode
            // --------------------------------------------------------------------------
            int catch = 1;

            lines = 0;

            while(1)
            {
                if (catch == 1)
                    getchar(); // <-- catches stray newline characters
                catch = 0;

                command = openPrompt();

                // Creating a new line at the end (newline.cf)
                // ----------------------------------------------------------------------
                if (command == '1' || command == 'C' || command == 'c')
                {
                        if (lines == 100000)
                        {
                            printf("\t --> Max File Size Reached! <-- \n");
                            break;
                        }

                        if (lines < 1) // <-- Checks if the file has any other lines and if not
                        {
                            printf("\t First line  --> "); 
                                getchar(); // <-- catches stray newline characters
                            fgets(str[lines], max_chars, stdin); // <-- inputs the first line
                            lines++;
                            printFile(lines, max_chars, str);
                            catch = 0;
                        }

                        else
                        {
                            printFile(lines, max_chars, str);
                            printf("\t/ Last line --> %s", str[lines-1]);
                            printf("\t\\ New line  --> ");
                                getchar(); // <-- catches stray newline characters
                            fgets(str[lines], max_chars, stdin);
                            lines++;
                            printFile(lines, max_chars, str);
                            catch = 0;
                        }
                }

                // Edit a line (editline.cf)
                // ----------------------------------------------------------------------
                else if (command == '2' || command == 'E' || command == 'e')
                {
                    while(1)
                    {
                        printFile(lines, max_chars, str);
                        printf("\n --> Enter a line number to edit or 0 to return to the Editing menu: ");
                        scanf("%d", &parameter);
                        if (parameter == 0)
                        {
                                getchar(); // <-- catches stray newline characters
                            break;
                        }
                        while (parameter > 100000) // <-- When line number crosses the buffer line limit
                        {
                            printf("\n\t\t\t\t --> Out of bounds! <-- \n");
                            printf("\n --> Enter a line number to Edit or 0 to return to the Editing menu: ");
                            scanf("%d", &parameter); // <-- Get line number again
                        }
                        
                        parameter--; // <-- converts line number to array index

                        if (parameter > lines) // <-- If line to be edited is not the lines already there or not the line directly after the last line
                        {
                            for (i = lines; i <= parameter; i++) // <-- replace lines between the last line and currently editing line 
                            {
                                    str[i][0] = '\n'; // <-- with a newline
                                    str[i][1] = '\0'; // <-- and a null character
                            }
                        }

                        i = parameter; // <-- assigning line number to i for better code readability

                        printf("\n");
                        printf("/ Original --> %s", str[i]); // <-- i == parameter == line index to be edited
                        printf("\\  Edited  --> ");
                        getchar(); // <-- catches stray newline characters
                        fgets(str[i], max_chars, stdin);

                        if (lines <= parameter) // <-- If the line is after existing lines
                            lines = parameter + 1; // <-- increase line number by 1

                        printf("\n");
                    }
                }

                // Delete a line (deleteline.cf)
                // ----------------------------------------------------------------------
                else if (command == '3' || command == 'D' || command == 'd')
                {
                    while(1)
                    {
                        printFile(lines, max_chars, str);
                        printf("\n --> Enter a line number to Delete or 0 to return to the Editing menu: ");
                        scanf("%d", &parameter);
                        if (parameter == 0) // <-- If zero is entered
                        {
                            getchar(); // <-- catches stray newline characters
                            break; // <-- Return to main menu
                        }
                        while (parameter > lines) // <-- If the line already doesn't exist
                        {
                            printf("\n\t\t\t\t --> Invalid Line! <-- \n");
                            printf("\n --> Enter a line number to edit or 0 to return to the Editing menu: ");
                            scanf("%d", &parameter); // <-- Get a new line number
                        }
                        
                        printf("\n");
                        parameter--;

                        for (i = parameter; i < (lines - 1); i++)
                        {
                            for (j = 0; j < max_chars; j++)
                            {
                                str[i][j] = str[i+1][j]; // <-- Shifts lines below the deleted line to up 1 line
                            }
                        }

                        lines--; // <-- decrease line number by 1 because of deletion
                        printf("\n");
                    }
                }

                // Save and Return to main menu (save.cf)
                // ----------------------------------------------------------------------
                else if (command == '4' || command == 'S' || command == 's')
                {
                    textFile = fopen (filename,"w");

                    for (i = 0; i < lines; i++)
                    {
                        fputs(str[i],textFile); // <-- Write changes to the main file from the string buffer
                    }

                    fclose(textFile);
                    printf("\n");
                    break;
                }

                // Return without saving (discard.cf)
                // ----------------------------------------------------------------------
                else if (command == '5' || command == 'R' || command == 'r')
                {
                    printf("\n");
                    break;
                }

                // Invalid Command
                // ----------------------------------------------------------------------
                else
                {
                    printf("\t\t\t --> Invalid Command! Try again. <-- \n");
                }
            }
        }

        // Delete a fie (deletefile)
        //-------------------------------------------------------------------------------
        else if (command == '3' || command == 'D' || command == 'd')
        {
            char confirm[10];
            if (i != 0)
                getchar(); // <-- catches stray newline characters

            printf("\n --> Enter the name and filename to the file: ");
            scanf("%s", &filename);

            printf("\n\t/---------------------------------------------------------------\\\n");
            printf("\t  Deleting file : %s \n", filename);
            printf("\t\\---------------------------------------------------------------/\n");
            printf("\n");
            printf("\t  Deleting a file is permanent and cannot be undone.\n");
            printf("\t  Type \"yes\" to delete the file.\n");
            printf("\n --> Are you sure? : ");
                getchar(); // <-- catches stray newline characters
            scanf("%[^\n]%*c", confirm);

            printf("%d\n", !strcmp(confirm,"yes"));

            if (!strcmp(confirm,"yes"))
            {
                if (remove(filename) == 0) 
                    printf("\n\t\t\t\t --> File Deleted <-- \n\n\n"); 
                else
                    printf("\n\t\t --> Permission denied or File doesn't exist! <-- \n\n\n");
            }

            else
                printf("\n\t\t\t\t --> Aborted! <-- \n\n\n");
        }

        // Exit the Program
        //-------------------------------------------------------------------------------
        else if (command == '4' || command == 'E' || command == 'e')
        {
            printf("\n\t\t\t\t --> Shutting Down! <-- \n\n\n");
            return 0;
        }

        // Easter Egg??
        //-------------------------------------------------------------------------------
        else if (command == '6' || command == '9' || command == 'Q' || command == 'q')
        {
            egg();
            return 0;
        }

        // Invalid Command
        //-------------------------------------------------------------------------------
        
        else if (command == '\n' || command == ' ')
        {
            scanf("%c", &command);
        }

        else
        {
            printf("\t\t\t --> Invalid Command! Try again. <-- \n");
            command = '\0';
        }
    }

    return 0;
}

void egg()
{
    printf("\n");
    printf("\t\t<^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^>\n");
    printf("\t\t>              Congratulaions!!               <\n");
    printf("\t\t<             ------------------              >\n");
    printf("\t\t>  You have unlocked the secret easter egg!!  <\n");
    printf("\t\t< Your luck has now increased by 69 points!!! >\n");
    printf("\t\t>           Good Luck : Have Fun!!!           <\n");
    printf("\t\t<^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^>\n");
}