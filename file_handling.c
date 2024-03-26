#include<stdio.h>
#include<string.h>
void copyFile(const char *first_file, const char *copied_file) 
{
    FILE *firstfile, *copiedfile;
    char a;
    int count=0;
    firstfile = fopen("first_file.txt", "r");
    copiedfile = fopen("copied_file.txt", "w");
    if (firstfile == NULL || copiedfile == NULL) 
	{
        printf("Error opening files.\n");                         
        return;
        
    }
    while ((a = fgetc(firstfile)) != EOF) {
        fputc(a,copiedfile);//EOF stands for end of file
		if(a==' ')
    	{
    		count++;
		}		
    }
    if(a==' ')
    {
    	count++;
	}
    printf("File copied successfully.\n");
    printf("The number of token used in this program is :%d",count + 1);
    fclose(firstfile);
    fclose(copiedfile);
}
int main() 
{
    copyFile("first_file.txt", "copied_file.txt");
	return 0;
}

