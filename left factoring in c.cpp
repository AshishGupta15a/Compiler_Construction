#include<stdio.h>
#include<string.h>
int main()
{
    char a[20],part1[20],part2[20],b[20],c[20],d[20];
    int i,j=0,k=0,l=0,pos;
    printf("Enter Production : A->");
    gets(a);
    for(i=0;a[i]!='|';i++,j++)
        part1[j]=a[i];
    part1[j]='\0';
    for(j=++i,i=0;a[j]!='\0';j++,i++)
        part2[i]=a[j];
    part2[i]='\0';
    for(i=0;i<strlen(part1)||i<strlen(part2);i++){
        if(part1[i]==part2[i]){
            b[k]=part1[i];
            k++;
            pos=i+1;
        }
    }
    for(i=pos,j=0;part1[i]!='\0';i++,j++){
        c[j]=part1[i];
    }
    c[j++]='|';
    for(i=pos;part2[i]!='\0';i++,j++){
        c[j]=part2[i];
    }
    b[k]='X';
    b[++k]='\0';
    c[j]='\0';
    printf("\nGrammar Without Left Factoring : : \n");
    printf(" A->%s",b);
    printf("\n X->%s\n",c);
}
