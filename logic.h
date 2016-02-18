#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

#define MAX 30

int checkWFF(char *logicString);
int checkOprnd(char a);
int checkOprtr(char a);
char *postfixConverter(char *input);
void copyToOutput(char *output,char a);
int priority(char opert, char top);
void heading(char *logicString,char *variables);
void truthTable(char *inputString,char *variables, int numVars);
void booleanForm(char *copyString, char *variables, int *booleans);
void binIncrement(int *booleans,int numVars);
int checkBool(char a);
void truthStack(char *copyString, int *flags);
char evaluate(char x,char y,char op);



//function to check whether input string is a WFF or not
//returns MAX if string is WFF
//else returns position of error

int checkWFF(char *logicString)
{
 int i;
 int count=0;
 
 
 //Condition to check whether first character in string is not an operand nor a NOT operator nor an opening brace
 //returns the first position as error if condition is satisfied
 
 if(!((logicString[0]>='A' && logicString[0]<='Z') || logicString[0]=='~' || logicString[0]=='('))
 	return 0;	
 
 	
 	
 //Condition to check whether last character is not an operand nor a closeing parenthesis
 //returns last position as error position if condition is satisfied
 
 for(i=1;logicString[i]!='\0';i++);	//Loop to count number of characters in input string
 if(!(checkOprnd(logicString[i-1]) || logicString[i-1]==')'))
 	return (i-1);
 		
 	
 	 
 //Loop to check the rest of input string for an error
 //Loop ends when end of input is reached
 
 for(i=1;logicString[i]!='\0';i++)
 {
 	//Condition to check if character is operand
 	//checkOprnd is a function returning TRUE if character is operand and else, FALSE
 	
 	if(checkOprnd(logicString[i]))
 	{
 		//Condition to check if previous charcter is not an operator nor an opening parenthesis
 		//present position is returned as function output if condition is satisfied
 		//checkOprtr is a function returning TRUE if character is operator and else, FALSE
 		
 		if(!(checkOprtr(logicString[i-1]) || logicString[i-1]=='('))
 			return i;
 			
 	}
 	
 	
 	//Condition to check if character is operator
 	
 	if(checkOprtr(logicString[i]))
 	{
 		//Condition to check if operator is NOT operator
 		
 		if(logicString[i]=='~')
 		{
 			//Condition to check whether previous character is not an operator nor an opening brace
 			//Returns present position as error position if condition is satisfied
 			
 			if(!(checkOprtr(logicString[i-1]) || logicString[i-1]=='('))
 				return i;
 		}
 		
 		
 		//if operator is not a NOT operator
 		
 		else
 		{	
 			//Condition to check whether previous character is not an operand nor a NOT operator
 									//nor a closing parenthesis
 			//returns present position as error position if condition is satisfied
 				
 			if(!(checkOprnd(logicString[i-1]) || logicString[i-1]=='~' || logicString[i-1]==')'))
 				return i;
 		}		
 	}
 	
 	
 	//Condition to check if character is an opening parenthesis
 	
 	if(logicString[i]=='(')
 	{
 		count++;	//Increment count for parsing check
 		
 		
 		//Condition to check if previous character is not an operator
 		//returns present position as error position if condition is true
 		
 		if(!(checkOprtr(logicString[i-1]) || logicString[i-1]=='('))
 			return i;
 	}
 	
 	
 	//Condition to check if character is an closing parenthesis
 	
 	if(logicString[i]==')')
 	{
 		count--; 	//Decrement count for parsing check
 		
 		
 		//Condition to check if previous character is not an operand
 		//returns present position as error position if condition is true
 		
 		if(!(checkOprnd(logicString[i-1]) || logicString[i-1]==')'))
 			return i;
 	}				
 			
 }
 
 
 //function returns -1 if there is parsing error
 
 if(logicString[0]=='(')	//To keep count of parenthesis
 	count++;
 	 	
 if(count!=0)
 	return -1;
 	
 	
 //If after all tests passed, no value is returned as error position, input expression is a WFF
 //MAX value is returned as a symbol that present function is indeed a WFF
 
 return MAX;

}


//Function to check if character is operand
//Returns TRUE if condition is satisfied, else returns FALSE

int checkOprnd(char a)
{
 if(a>='A' && a<='Z')
 	return 1;
 	
 return 0;

}


//Function to check if character is operator
//Returns TRUE if condition is satisfied, else returns FALSE

int checkOprtr(char a)
{
 switch(a)
 {
 	case '~': return 1;
 	
 	case '^': return 1;
 	
 	case 'v': return 1;
 	
 	case '>': return 1;
 	
 	case '=': return 1;
 	
 	default : return 0;
 }

} 				  


//Function to convert a given string in infix form to a string in postfix form
char *postfixConverter(char *input)
{
 char *output;
 STACK *stackHead;
 int i;
 char *topOp,*popped;
 
 //Counts how many characters there are atmost in the input string to determine size of output string
 for(i=0;input[i]!='\0';i++);
 i++;
 
 //Creating space for the output string
 output=(char *)malloc(i*sizeof(char));
 output[0]='\0';
 
 stackHead=createStack();
 
 //Loop to create postfix output string
 for(i=0;input[i]!='\0';i++)
 {
 	//if character is an operand, copy to output string
 	if(checkOprnd(input[i]))
 		copyToOutput(output,input[i]);
 		
 				
 	else if(checkOprtr(input[i]))
 	{
		//if stack is empty, push operator into the empty stack
 		if(!stackCount(stackHead))
 			stackHead=push(stackHead,&input[i]);
 		
 		//stack is non-empty	
 		else
 		{
 			//stacktop operator is stored in variable topOp
 			topOp=(char *)stackTop(stackHead);
 			
 			//pop the stack till the stacktop operator is of lower priority than present operator
 			//or till stack becomes empty, during which there is nothing to pop
 			//copy the popped character to output one after another
 			while(stackCount(stackHead)!=0 && !priority(input[i],*topOp))
 			{
 				popped=(char *)pop(&stackHead);
 				
 				copyToOutput(output,*popped);
 				
 				topOp=(char *)stackTop(stackHead);
 			}
 			
 			//once present character is of higher prioirity, push it into the stack
 			stackHead=push(stackHead,&input[i]);
 		}		
 				 
 	}
 	
 	
 	//if character is opening brace push it into stack independant of stackTop
 	else if(input[i]=='(')
 		stackHead=push(stackHead,&input[i]);
 	
 	//if character is closing brace
 	//keep popping stack and copying to output till opening brace is not reached
 	//and then pop opening brace
 	else if(input[i]==')')
 	{
 		topOp=(char *)stackTop(stackHead);
 		
 		while(*topOp!='(')
 		{	
 			popped=pop(&stackHead);
 			
 			copyToOutput(output,*popped);
 			
 			topOp=(char *)stackTop(stackHead);
 		}
 		
 		pop(&stackHead);
 		
 	}
 }
 
 //pop remaining operators in stack one by one till stack is empty and copy to output
 while(stackCount(stackHead))
 {
 	popped=pop(&stackHead);
 	
 	copyToOutput(output,*popped);
 }
 
 //terminate output string by using a NULL character
 copyToOutput(output,'\0');
 
 
 stackHead=destroyStack(stackHead);
 
 return output;
} 					



//function to copy character to output string
void copyToOutput(char *output,char a)
{
 int i=0;
 
 //loop to take i to the first blank position
 while(output[i]!='\0')
 	i++;
 	
 //assigns position i to character a
 //then increments i	
 output[i++]=a;
 
 //assigns position i to NULL
 output[i]='\0';
} 	


//Function to compare priority of present operator over stackTop operator
//returns 1 if priority is higher
//returns 0 if not
int priority(char opert, char top)
{
 //if stackTop is opening brace, always give higher priority to any operator
 if(top=='(')
 	return 1;
 	
 //priority order in ascending order is =(EQUIAVALENCE) , >(IF...THEN) , ^(AND) , v(OR) , ~(NOT)
 //which fortunately is in ascending order in the ASCII as well	
 return ((opert-top)>0);
} 		
 			
 			
//Function to print the heading of the truth table
void heading(char *logicString,char *variables)
{
 int opCount=0,i,j;
 
 char **inters;
 char *var1,*var2;
 STACK *stackHead=createStack();
 
 
 //Loop to count number of operators so as to assess number of intermediates 
 for(i=0;logicString[i]!='\0';i++)
 {
 	if(checkOprtr(logicString[i]))
 		opCount++;
 }		
 
 //inters is an array to store the names of the intermediate variables
 inters=(char **)malloc(opCount*sizeof(char *));
 for(i=0;i<opCount;i++)
 {
 	//each name has 2 characters and a NULL string terminator
 	inters[i]=(char *)malloc(3*sizeof(char));
 	
 	//The names are in the sequence A1,A2,...,A9 , B1,B2,...,B9 , ...
 	inters[i][0]='A' + (i/9);
 	inters[i][1]='0' + (i%9)+1;
 	inters[i][2]='\0';
 }
 
 //Print the input variable names
 for(i=0;variables[i]!='\0';i++)
 	printf("%c ",variables[i]);
 
 printf("| ");		
 
 
 //Loop in which stack is used to evaluate postfix expressions in the usual way
 //except in this case, no mathematical or logic formulation is done, rather the expressions are printed
 for(i=0;logicString[i]!='\0';i++)
 {
 	if(checkOprnd(logicString[i]))
 	{
 		stackHead=push(stackHead,&logicString[i]);
 		
 	}		
 		
 	else if(checkOprtr(logicString[i]))
 	{
 		if(logicString[i+1]=='\0')
 			printf("|");
 			
 		if(logicString[i]=='~')
 		{
 			var2=(char *)pop(&stackHead);
 			
 			if(*(var2+1)>='0' && *(var2+1)<='9')
 				printf(" %s=(~%s)  ",inters[j],var2);
 				
 			else
 				printf("  %s=(~%c)  ",inters[j],*(var2));
 				
 			stackHead=push(stackHead,inters[j]);
 			
 			j++;
 		}
 		
 		else
 		{
 			var2=(char *)pop(&stackHead);
 			var1=(char *)pop(&stackHead);
 			
 			if(*(var2+1)>='0' && *(var2+1)<='9')
 			{
 				if(*(var1+1)>='0' && *(var1+1)<='9')
 					printf("%s=(%s%c%s) ",inters[j],var1,logicString[i],var2);

 				else
 					printf(" %s=(%c%c%s) ",inters[j],*(var1),logicString[i],var2);
 			}	
 				
 			else
 			{
 				if(*(var1+1)>='0' && *(var1+1)<='9')
 					printf(" %s=(%s%c%c) ",inters[j],var1,logicString[i],*(var2));
 				
 				else
 					printf(" %s=(%c%c%c)  ",inters[j],*(var1),logicString[i],*(var2));
 			}
 			
 			stackHead=push(stackHead,inters[j]);
 			
 			j++;
 		}
 	}
 	
 }
 
 printf("\n");
 
 for(i=0;i<opCount;i++)
 	free(inters[i]);
 	
 free(inters);
 
 stackHead=destroyStack(stackHead);

} 			
 		


//Function to generate the truth table and assess the logic expression
void truthTable(char *inputString,char *variables,int numVars)
{
 int i,count=0,loopEnd=1,flags[2];
 char a;
 int *booleans;
 char copyString[MAX];
 
 booleans=(int *)malloc(numVars*sizeof(char));
 
 //The array booleans stores the boolean values, T/F of the variables during a particular truth table evaluation
 //they are initiated as all F
 for(i=0;i<numVars;i++)
 	booleans[i]=0; 	
 
 //loopEnd determines when all possible boolean combinations of the variables have been evaluated in the truth
 //													 table
 for(i=0;i<numVars;i++)
 	loopEnd*=2;
 	
 //flags[0] is 1 if all outputs are false
 //flags[1] is 1 if all outputs are true
 //they are initiated thus
 //then if any are untrue, the corresponding flag is turned down to 0	
 flags[0]=1;
 flags[1]=1;	
 	
 
 //Master loop in which input variables are assigned booleans and evaluated
 //evaluations are also in boolean and the corresponding values are printed under the intermediates 	
 for(count=0;count<loopEnd;count++)
 {
 	//The logic string is copied to a copyString
 	//all operations are done on the copyString and the inputString is kept intact
 	for(i=0;inputString[i]!='\0';i++)
 		copyString[i]=inputString[i];
 	copyString[i]='\0';
 
 
 	//Function to replace the variables in the copyString by the corresponding boolean values
 	booleanForm(copyString,variables,booleans);
 	
 	//Loop to print the boolean values of the input variables
 	for(i=0;variables[i]!='\0';i++)
 	{
 		if(booleans[i])
 			printf("T ");
 			
 		else
 			printf("F ");
 	}
 	printf("| ");
 	
 	//Function in which the copyString with the boolean values and operators in postfix are taken
 	//the expression is evaluated and the intermediates and outputs are printed
 	truthStack(copyString,flags);
 	
 	printf("\n");
 	
 	//Function in which the array storing the boolean values of the variables for this loop is stored
 	//is changed so as to increment the binary expression, (e.g. 100 to 101)
 	binIncrement(booleans,numVars);
 }
 
 
 if(flags[0]==0 && flags[1]==0)
 	printf("\n\nPropositional Logic statement is NOT VALID but CONSISTENT!\n");
 	
 else if(flags[0]==1)
 	printf("\n\nPropositional Logic statement is INCONSISTENT!\n");
 	
 else if(flags[1]==1)
 	printf("\n\nPropositional Logic statement is VALID!\n");
 		
 free(variables);
 free(booleans);

}


//Function to replace the variables in the copyString by their corresponding boolean values
void booleanForm(char *copyString, char *variables, int *booleans)
{
 int i,j,k;
 
 for(i=0;copyString[i]!='\0';i++)
 {
 	//if character is an operand, replace it by the corresonding boolean value
 	//then go through the rest of the string and if the same variable occurs anywhere else, 
 	//replace it by the boolean
 	if(checkOprnd(copyString[i]))
 	{
 		//loop to find the first variable character
 		for(j=0;;j++)
 		{
 			if(copyString[i]==variables[j])
 				break;
 		}
 		
 		//replace the variable in the copyString by the corresponding boolean
 		copyString[i]='0'+booleans[j];
 		
 		//loop to go through the rest of the loop and replace the same variable if it occurs anywhere
 		for(k=i+1;copyString[k]!='\0';k++)
 		{
 			if(copyString[k]==copyString[i])
 				copyString[k]='0'+booleans[j];
 		}
 	}
 }
}

//Function to increment array containing the boolean values (e.g. 100 to 101)
void binIncrement(int *booleans,int numVars)
{
 int i;
 
 //Loop starts from right side of array, if bit is 0, it is turned to 1
 //else if bit is 1, it is turned to 0 and the next left bit is sent into the loop
 //this is the basic algorithm for binary addition
 for(i=numVars-1;i>=0;i--)
 {
 	if(booleans[i]==0)
 	{
 		booleans[i]=1;
 		break;
 	}
 	
 	else
 		booleans[i]=0;
 }
 
} 				


//Function to check if character is 0 or 1 
int checkBool(char a)
{
 if(a=='0' || a=='1')
 	return 1;
 	
 else
 	return 0;
}


//Function which evaluates a given postfix expression of booleans and prints the outputs and intermediates
//for truth table		 
void truthStack(char *copyString, int *flags)
{
 STACK *stackHead=createStack();
 int i;
 char *var1,*var2;
 
 //Master loop to run till end of postfix boolean expression is reached
 for(i=0;copyString[i]!='\0';i++)
 {
 	//if present character is a boolean operand, push to stack
 	if(checkBool(copyString[i]))
 		stackHead=push(stackHead,&copyString[i]);
 	
 	//if character is an operator	
 	else if(checkOprtr(copyString[i]))
 	{
 		if(copyString[i+1]=='\0')
 			printf("|");
 		
 		//if operator is NOT operator then pop the stacktop element once,
 		//evaluate the boolean operation and push output to stack and print it in truth table	
 		if(copyString[i]=='~')
 		{
 			var2=(char *)pop(&stackHead);
 			
 			if(*var2=='0')
 			{
 				*var2='1';
 				
 				printf("     T     ");
 			}
 			
 			else if(*var2=='1')
 			{
 				*var2='0';
 				
 				printf("     F     ");
 			}
 			
 			stackHead=push(stackHead,var2);
 		}
 		
 		//If operator is a binary operator top two stack elements are popped, evaluated
 		//and output is pushed to stack and printed in truth table
 		else
 		{
 			var2=(char *)pop(&stackHead);
 			var1=(char *)pop(&stackHead);
 			
 			//Function to evaluate binary operations on booleans
 			*var2=evaluate(*var1,*var2,copyString[i]);
 			
 			if(*var2=='0')
 				printf("     F     ");
 				
 			else if(*var2=='1')
 				printf("     T     ");
 				
 			stackHead=push(stackHead,var2);
 		}
 	}
 }
 
 var2=(char *)pop(&stackHead);
 
 //if outcome is false, set valid flag to 0
 if(*var2=='0')
 	flags[1]=0;
 
 //if outcome is true, set inconsistent flag to 0	
 if(*var2=='1')
 	flags[0]=0;
 
 stackHead=destroyStack(stackHead);
 
}


//Function to perform binary operations AND,OR,IF...THEN,EQUIVALENCE on two input bits
char evaluate(char x,char y,char op)
{
 switch(op)
 {
 	case '^': if(x=='0' || y=='0')
 		  	return '0';
 		  	
 		  else
 		  	return '1';	
 		  	
 	case 'v': if(x=='1' || y=='1')
 		  	return '1';
 		  	
 		  else
 		  	return '0';	
 		  	
 	case '>': if(x=='1' && y=='0')
 			return '0';
 		  
 		  else
 		  	return '1';		  		  	 	 				
 										
  	case '=': if(x==y)
  			return '1';
  			
  		  else
  		  	return '0';
 }
}  		  		 			
