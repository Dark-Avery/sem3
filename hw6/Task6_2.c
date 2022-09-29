#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/********************************************************************************/

void Check_Var(FILE** Input_Stream, int* Ok_For_Empty, int* Am_Of_Str_In_One_Iter, int* Start, int a)
{
    
}

/********************************************************************************/

int BLOCK_Print(FILE** From_Where_Write, int Amount, int Skip_All_Empty)
{
    char* String_To_Write = NULL;
    char Symbol_To_Add_In_String;
    char ok;
    int Len_Of_String;
    if (!feof(*From_Where_Write))
    {
        for (int i = 0; i < Amount; i++)
        {
            Len_Of_String = 0;
            while (!feof(*From_Where_Write))
            {
            	Symbol_To_Add_In_String = fgetc(*From_Where_Write);
            	if (Symbol_To_Add_In_String == '\n' || feof(*From_Where_Write)) { break; }
            	Len_Of_String += 1;
            	String_To_Write = realloc(String_To_Write, Len_Of_String);
            	String_To_Write[Len_Of_String - 1] = Symbol_To_Add_In_String;
	    	}
	    	if (String_To_Write == NULL) 
	    	{ 
	    		if (feof(*From_Where_Write)) { return 0; }
	    		puts("");
	    		if (Skip_All_Empty && !Len_Of_String)//if skip_flag = 1 and last prinded string was empty, then we must skip all
			    {
			    	while (Symbol_To_Add_In_String == '\n' && !feof(*From_Where_Write))
			    	{
			    		Symbol_To_Add_In_String = fgetc(*From_Where_Write);
			    	}//all empty skiped
			    	if (feof(*From_Where_Write)) { return 0; }
			    	fseek(*From_Where_Write, -1, SEEK_CUR);// we read 1 extra sym so go back on 1 position in a file
				}
	    	}
	    	else 
	    	{
				String_To_Write = realloc(String_To_Write, Len_Of_String + 1);
				String_To_Write[Len_Of_String] = 0;
				puts(String_To_Write);
			    free(String_To_Write);
			    String_To_Write = NULL;
			}
	    	if (feof(*From_Where_Write)) { return 0; }//if eof*/
        } 
        return 1;//if !eof
    }
    return 0; //if eof
}

/********************************************************************************/

int skip(FILE** Where_Skip, int How_Many_Skip)
{
    char inter_to_skip;
    for (int i = 1; i < How_Many_Skip; i++)
    {
        inter_to_skip = fgetc(*Where_Skip); //get first (<\n> or another char)
        while (inter_to_skip != '\n') { inter_to_skip = fgetc(*Where_Skip); } //get all till </n>
        if (feof(*Where_Skip)) // if reach end of file
        {
            return 0;
        }
    }
    return 1;
}
/********************************************************************************/

int main(int argc, char** argv) 
{
    if (argc < 2)
    {
        puts("To few arguments for command My_more!");
        return 0;
    }
    else if (argc > 5)
    {
        puts("To much arguments for command My_more!");
        return 0;
    }
    
    puts("|-----------------------------------------------------------------|");
    puts("|---Switching the terminal to a non-canonical mode of operation---|");
    puts("|-----------------------------------------------------------------|");
    puts("|---Press <space> for new portion of strings. For end press <q>---|");
    puts("|-----------------------------------------------------------------|");
    
/*************************************************************************/
    
    static struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt); // сохранение текущего режима
    newt = oldt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // изменение 

/********************************************************************************/

    char c = 0;
    int Ok_For_Empty_Strings = 0;
    int Amount_Of_Strings_In_One_Iteration = 10;
    int Start_Writing_Strings = 1;
    FILE* Input_File_Stream;
    
    for (int i = 1; i < argc; i++)
    {
        if (i == argc - 1) { Input_File_Stream = fopen(argv[i], "r"); }
        else if (!(strcmp(argv[i], "-s"))) { Ok_For_Empty_Strings = 1; }
        else if (!strncmp(argv[i], "-", 1)) { Amount_Of_Strings_In_One_Iteration = atoi(argv[i] + 1); }
        else if (!strncmp(argv[i], "+", 1)) { Start_Writing_Strings = atoi(argv[i] + 1); }
    }
    if (skip(&Input_File_Stream, Start_Writing_Strings))
    { // if some strings left in file then write them
        while ((c != 'q') && !feof(Input_File_Stream))
        {
            if (BLOCK_Print(&Input_File_Stream, Amount_Of_Strings_In_One_Iteration, Ok_For_Empty_Strings))
            {
                c = getchar();
            }
            else { break; }
        }
    }
    else { puts("!!!NOT ENOUGH STRINGS IN A FILE!!!"); }
    fclose(Input_File_Stream);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // восстановление исходного режима
    return 0;
}
