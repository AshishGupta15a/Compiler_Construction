#include <stdio.h>
#include <string.h>
void removeLeftRecursion(char prod[]) 
{
    int i, j, n, k;
    int lrec = 0;
    char a[100] = "";
    char b[100] = "";
    char alpha[100] = "";  //new non terminal
    char beta[100] = "";   //new non terminal or the epsilon
    char start_symbol[20] = "";
    n = (int)strlen(prod);
    start_symbol[0] = prod[0]; 
    for (i = 0; i < n; i++) 
	{
        if (prod[i] == '|') 
		{
            k = i;
        }
    }
    if (prod[3] == prod[0]) 
	{
        lrec = 1;
    }
    if (lrec == 1) 
	{
        int c = 0;
        k = k - 1;
        for (i = 4; i <= k; i++) 
		{
            alpha[c] = prod[i];
            c++;
        }
        c = 0;
        for (i = k + 2; i < n; i++) 
		{
            beta[c] = prod[i];
            c++;
        }
        strcat(a, start_symbol);
        strcat(a, "->");
        strcat(a, beta);
        strcat(a, start_symbol);
        strcat(a, "'");
        strcat(b, start_symbol);
        strcat(b, "'");
        strcat(b, "->");
        strcat(b, alpha);
        strcat(b, start_symbol);
        strcat(b, "'");
        strcat(b, "|e");
        printf("\n%s\n%s", a, b);
    }
    else
    {
    	printf("Hence this particular production does not contain the left recursion");
	}
}
int main() 
{
    int numProductions;
    printf("Enter the number of productions: \n");
    scanf("%d", &numProductions);
    for (int i = 0; i < numProductions; i++) 
	{
        char production[100];
        printf("\nEnter production %d: ", i + 1);
        scanf("%s", production);
        removeLeftRecursion(production);
    }
    return 0
}

