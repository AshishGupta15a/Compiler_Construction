#include<stdio.h>
#include<string.h>
int main()
{
	char a;
	FILE* first_file=fopen("first_file.txt","r");
	FILE* copy_file=fopen("copied_file.txt","w");
	
	a=fgetc("first_file"); 
	while(a!= EOF)
	{   
        fputc(a,copy_file);
        a=fgetc(first_file);
    }
	
	fclose(first_file);
	fclose(copy_file);
	printf("the file has been copied successfully");
	return 0;
	
}
