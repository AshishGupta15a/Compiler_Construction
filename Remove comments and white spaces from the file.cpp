#include <stdio.h>
int main()
{
    FILE *first2, *copied2;
    char str, pstr;
    int comCount= 0, spCount = 0;
    first2 = fopen("first2.txt", "r");
    if (first2 == NULL) 
	{
        printf("Error opening the file.\n");
        return 1;
    }
    copied2 = fopen("copied2.txt", "w");
    while ((str = fgetc(first2)) != EOF) 
	{
        if (str == ' ' || str == '\t' || str == '\n') 
		{
            spCount++;
        } 
		else if (str == '/' && pstr == '/') 
		{
            comCount++;
            while ((str = fgetc(first2)) != EOF && str != '\n');
        } 
		else if (str == '/' && pstr == '*') 
		{
            comCount++;
            while ((str = fgetc(first2)) != EOF) 
			{
                if (str == '*' && (str = fgetc(first2)) == '/')
                    break;
            }
        } 
        else if (str == '"') 
		{
		    fputc(str, copied2);
            while ((str = fgetc(first2)) != EOF && str != '"') 
			{
                fputc(str, copied2);
    		}
    		fputc(str,copied2);
    	}
		else 
		{
            fputc(str, copied2);
        }

        pstr = str;
    }
    fclose(first2);
    fclose(copied2);
    printf("Removed %d comments and %d white spaces.\n", comCount, spCount);
    return 0;
}

