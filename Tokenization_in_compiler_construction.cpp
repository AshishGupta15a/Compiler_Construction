#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int isKeyword(char * word) 
{
  	char keywords[][50] = {"int","float","char","if","else","while","for","return"};
	int i;
	for (i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) 
	{
		if (strcmp(keywords[i], word) == 0) 
		{
	    	return 1;
	    }
	}
	return 0;
}
int main()
{
	char a, arr[50];
	char str,pstr;
	FILE * file;
	int opcount = 0, spcount = 0, kycount = 0, idfcount = 0, constcount = 0, ltcount = 0, comCount=0;
	
	file = fopen("First.txt", "r");
	if (file == NULL) 
	{
		printf("Error opening file\n");
	    exit(0);
	}
	while ((a = fgetc(file)) != EOF) 
	{
		    if (str == '/' && pstr == '/') 
			{
            	comCount++;
            	while ((str = fgetc(file)) != EOF && str != '\n');
        	} 
			else if (str == '/' && pstr == '*') 
			{
            	comCount++;
            	while ((str = fgetc(file)) != EOF) 
				{
                	if (str == '*' && (str = fgetc(file)) == '/')
                    break;
            	}
        	} 
			else if (a == '+' || a == '-' || a == '*' || a == '/') 
			{
		    	opcount++;
		    } 
			else if (a == ';' || a == ',' || a == '{' || a == '}' || a == '(' || a == ')') 
			{
		        spcount++;
		    } 
			else if (isalpha(a) || a == '_') 
			{
		        int i = 0;
		        while (isalnum(a) || a == '_') 
				{
		        	arr[i++] = a;
		            a = fgetc(file);
		        }
		        arr[i] = '\0';
		        fseek(file, -1, SEEK_CUR);
		        if (isKeyword(arr)) 
				{
		          kycount++;
		        } 
				else 
				{
		          idfcount++;
		        }
		    } 
			else if (isdigit(a)) 
			{
		        int i = 0;
		        while (isdigit(a) || a == '.') 
				{
		          arr[i++] = a;
		          a = fgetc(file);
		        }
		        arr[i] = '\0';
		        fseek(file, -1, SEEK_CUR);
		        constcount++;
		    }
		
	}
	printf("the number of operator are: %d\n", opcount);
	printf("the number of special character are: %d\n", spcount);
	printf("the number of keyword are: %d\n", kycount);
	printf("the number of identifier are: %d\n", idfcount);
	printf("the number of spaces are: %d\n",spcount);
	printf("the number of constant are: %d\n", constcount);
	printf("the number of literal are: %d\n", ltcount);
	printf("The number of comments are:%d\n",comCount);
	fclose(file);
	return 0;
}
