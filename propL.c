#include<stdio.h>
#include<stdlib.h>
//#include"wff.h"
//#include"infixToPostfix.h"
//#include"heading.h"
//#include"truthTable.h"
#include"logic.h"

#define MAX 30

main()
{
 char *inputString;
 char *variables;
 int i,numVars,flag;
 
 inputString=(char *)malloc(MAX*sizeof(char));
 
 //Initiation of application where the instructions are printed
 system("clear");
 printf("=================================================Welcome to PropL================================================\n");
 
 printf("Operators list:\n~ : NOT\n^ : AND\nv : OR\n> : IF...THEN\n= : EQUIVALENCE\n\nInput variables in upper-case!\n\n");
 
 
 printf("Input number of variables: ");
 scanf("%d",&numVars);
 getchar();
 
 variables=(char *)malloc((numVars+1)*sizeof(char));
 
 //Taking number of variables as input
 printf("\nInput variable names:\n");
 
 //Taking variable names as input and storing them in an array
 for(i=0;i<numVars;i++)
 {
 	printf("Input variable name#%d: ",(i+1));
 	scanf("%c",&variables[i]);
 	getchar();
 }
 variables[i]='\0';
 
 
 //Next, taking as input the logic expression
 //system("clear");
 
 printf("Input logic expression:\n");
 scanf("%s",inputString);
 
 //Function to check whether input is a WFF
 flag=checkWFF(inputString);
 
 //If not a wff error message is printed and error position/nature is shown
 if(flag!=MAX)
 {
 	if(flag==-1)
 		printf("Expression is not a Well-Formed-Formula!\nERROR in parenthesis!\n");
 		
 	else
 		printf("Expression is not a Well-Formed-Formula!\nERROR in position #%d!\n",flag);
 }
 
 
 //If is a wff, truth table is generated, printed and validity/consistency of expression is shown
 else
 {
 	printf("Expression is a Well-Formed-Formula!\n\nGenerating truth-table...\n\n\n");
 	
 	//Function converts input expression infix to postfix
 	inputString=postfixConverter(inputString);
 	
 	//Function generates heading of truth table
 	heading(inputString,variables);
 	printf("\n");
 	
 	//Function to generate, print truth table and show validity/consistency of expression
 	truthTable(inputString,variables,numVars);
 }
 
 
 //The End!
 printf("\nPress ENTER to exit!\n");
 getchar();
 getchar();
 
 system("clear");
} 					
 	
