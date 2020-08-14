#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <sstream>
#include <iostream>

using namespace std;

bool IsMain = false;
FILE *readFile;
char ch;
stringstream concat;
string linha;
int countMains = 0;
int countLines = 1;
int countIdent = 0;
int countChars = 0;
char BottleCup[32767][32767];
stringstream Line;
stringstream charsNum;
int memory[1000];
int stacks[1000];
int top = 0;
int selection = 0;
int lastOffset = 0;
int lastOffOp = 0;

#define PRINT 	  "C8H10N4O2 " //PRT -> saída de dados (impressão)
#define OPERATION "C7H8N4O2 "  //OP  -> Operações aritméticas
#define SELECTION "C9H8O4 "    //SEL -> Seleção de memória
#define SALTOCOND "C20H28O3 "  //JMP -> Saltos e chamadas
#define RETURNS   "C7H6O3 "    //RET -> Retorno de chamadas
#define INPUT     "C12H22O11 " //INP -> Entrada de dados

#define ClearAll(a, b, c)   *a = 101; \
						 	b.str(""); \
						   	b.clear(); \
							c.str(""); \
							c.clear(); \


	
string returnString(char *str){
	stringstream data1;
	data1 << str;
	return data1.str();
}

bool cont(string first, string second)
{
	 int pos = 0;
     pos = first.find(second);
	 
     if(pos == -1)
         return false;
     else
         return true;    
          
}

void IgnoreSpaces(){
	while(ch != '\n'){
		ch = fgetc(readFile);
		if(ch == -1 || ch == ';')
			break;
	}
	concat.str("");
	concat.clear();	
}

void PreInterpreter(){
	while((ch = fgetc(readFile)) != -1){
				concat << ch;
				linha = concat.str();
				
				if(IsMain){
					concat.str("");
					concat.clear();
					for( ; ch != ';' ; ){
					
						while(ch != '!' && ch != '\n'){
							concat << ch;
							linha = concat.str();
							
							BottleCup[countIdent][countChars] = ch;
						
							ch = fgetc(readFile);
							++countChars;
						}
						BottleCup[countIdent][countChars] = ch;
						IgnoreSpaces();	
						if(ch != ';')
							ch = fgetc(readFile);
					
						
						if(ch == '@' || ch == -1){
							cout << "Falta ';' pra finalizar o cup!" << endl;
							return;
						}
						
						
						++countIdent;
						countChars = 0;
					}
					IsMain = false;
					countIdent = 0;
					countChars = 0; 
				}
				
				if(linha == "cup:" && countMains == 0){
					IsMain = true;
					concat.str("");
					concat.clear();
					++countMains;
					IgnoreSpaces();
				}
			
				
			}
			
}

void PrintCommand(int i, int *j){	
	if(BottleCup[i][*j] == ' ')
		*j = *j + 1;
			
	while(BottleCup[i][*j] != '!'){			
		if(BottleCup[i][*j] == '%'){
			cout << endl;
			*j = *j + 1;
		}else{
			if(BottleCup[i][*j] != ','){
				cout << BottleCup[i][*j];
				*j = *j + 1;	
			}
		}
		
		if(BottleCup[i][*j] == ','){
			*j = *j + 1;
			if(BottleCup[i][*j] == ','){
				cout << BottleCup[i][*j];
				*j = *j + 1;
			}
			while(BottleCup[i][*j] != ','){
				if(BottleCup[i][*j] == '<'){
					*j = *j + 1;
					while(BottleCup[i][*j] != '>'){
						if(BottleCup[i][*j] == '$')
							cout << memory[selection];
						else 
							if(BottleCup[i][*j] == '#')
								if(lastOffOp == 0)	
									cout << memory[selection-lastOffset];
								else
									cout << memory[selection+lastOffset];
						
						*j = *j + 1;
					}
				}
				if(BottleCup[i][*j] == '$')
					cout << char(memory[selection]);	
				else
					if(BottleCup[i][*j] == '#')
						if(lastOffOp == 0)	
							cout << char(memory[selection-lastOffset]);
						else
							cout << char(memory[selection+lastOffset]);		
										
					
				*j = *j + 1;
			}
			*j = *j + 1;
		}	
						
		
	}
						
	ClearAll(j, Line, charsNum);
}

void ArgsAnalise(int *sizeNum, int *num, int *i, int *j){
	while(BottleCup[*i][*j] != ','){
		charsNum << BottleCup[*i][*j];
		*sizeNum = *sizeNum + 1;
		*j = *j + 1;
		if(BottleCup[*i][*j] == '!')
			break;
	}
	if(charsNum.str() != "$" && charsNum.str() != "#"){
		char chars[*sizeNum];
		for(int n = 0; n < *sizeNum; n++)
			chars[n] = charsNum.str()[n];
			
		*num = atoi(chars);
	}else{
		if(charsNum.str() == "#")
			if(lastOffOp == 0)	
				*num = memory[selection-lastOffset];
			else
				*num = memory[selection+lastOffset]; 
		else
			*num = memory[selection];
	}
}

void OperationCommand(int *i, int *j){
	*j = *j + 1;
	int num = 0;
	int sizeNum = 0;
	int count = 0;
	int op;
	int aux = 0;
	while(BottleCup[*i][*j] != '!'){			
		ArgsAnalise(&sizeNum, &num, i, j);
			
		if(count == 0){
			op = num;
		}else{
			if(count == 1){
				aux = num;
			}else{
				switch(op){
					case 0: aux += num; break;
					case 1: aux -= num; break;
					case 2: aux *= num; break;
					case 3: aux /= num; break;
					default:  break;
				}
			}
			
		}	
		
		if(op > 3)
			break;
			
		sizeNum = 0;
		charsNum.str("");
		charsNum.clear();
		count = count + 1;					
		*j = (BottleCup[*i][*j] == ',') ? *j + 1 : *j;
	}
	
	if(op > 3)
		cout << "Operacao invalida (nao conhecida)!" << endl;
	else
		memory[selection] = aux;
							
	ClearAll(j, Line, charsNum);
}

void SelectionCommand(int *i, int *j){
	*j = *j + 1;
	int num = 0;
	int sizeNum = 0;
	int count = 0;
	int op;
	while(BottleCup[*i][*j] != '!'){			
		ArgsAnalise(&sizeNum, &num, i, j);
			
		if(count == 0){
			op = num;
			lastOffOp = op;
		}else{
			lastOffset = num;
			switch(op){
				case 0: selection += num; break;
				case 1: selection -= num; break;
				default:  break;
			}
			
		}	
		
		if(op > 1)
			break;
			
		sizeNum = 0;
		charsNum.str("");
		charsNum.clear();
		count = count + 1;					
		*j = (BottleCup[*i][*j] == ',') ? *j + 1 : *j;
	}
	
	if(op > 1)
		cout << "Selecao invalida (nao conhecida)!" << endl;
						
	ClearAll(j, Line, charsNum);
}

void JumpCondition(int *i, int *j){
	*j = *j + 1;
	int num = 0;
	int sizeNum = 0;
	int count = 0;
	int op;
	int address = 0;
	bool condition = true;
	while(BottleCup[*i][*j] != '!'){
				
		ArgsAnalise(&sizeNum, &num, i, j);
				 
		if(count == 0){
			op = num;
		}else{
			if(count == 1){
				address = num;
			}else{
				switch(op){
					case 0: 
						condition = true;
					break;
					case 1: 
						condition = memory[selection] == num;
					break;
					case 2:
						condition = memory[selection] != num;
					break;
					case 3: 
						condition = memory[selection] > num;
					break;
					case 4: 
						condition = memory[selection] < num;
					break;
					case 5: 
						condition = memory[selection] >= num;
					break;
					case 6: 
						condition = memory[selection] <= num;
					break;
					case 7: 
						condition = memory[selection] & num;
					break;
					case 8: 
						condition = memory[selection] | num;
					break;
					case 9:
						condition = memory[selection] != 0;
					break;
					case 10: 
						condition = memory[selection] == 0;
					break;
					case 11: 
						condition = (lastOffOp == 0) ? memory[selection-lastOffset] == num : memory[selection+lastOffset] == num;
					break;
					case 12:
						condition = (lastOffOp == 0) ? memory[selection-lastOffset] != num : memory[selection+lastOffset] != num;
					 break;
					case 13: 
						condition = (lastOffOp == 0) ? memory[selection-lastOffset] > num : memory[selection+lastOffset] > num;
					 break;
					 case 14: 
						condition = (lastOffOp == 0) ? memory[selection-lastOffset] < num : memory[selection+lastOffset] < num;
					 break;
					 case 15: 
						condition = (lastOffOp == 0) ? memory[selection-lastOffset] >= num : memory[selection+lastOffset] >= num;
					 break;
					 case 16: 
						condition = (lastOffOp == 0) ? memory[selection-lastOffset] <= num : memory[selection+lastOffset] <= num;
					 break;
					 case 17: 
						condition = (lastOffOp == 0) ? memory[selection-lastOffset] & num : memory[selection+lastOffset] & num;
					 break;
					 case 18: 
						condition = (lastOffOp == 0) ? memory[selection-lastOffset] | num : memory[selection+lastOffset] | num;
					 break;
					 case 19:
						condition = (lastOffOp == 0) ? memory[selection-lastOffset] != 0 : memory[selection+lastOffset] != 0;
					 break;
					 case 20: 
						condition = (lastOffOp == 0) ? memory[selection-lastOffset] == 0 : memory[selection+lastOffset] == 0;
					 break;
					 case 30:
					 	condition = true;
					 	stacks[top] = *i;
					 	top = top + 1;
					 break;
					default:  break;
				}
			}
			
		}	
		
		if(op > 30)
			break;
			
		sizeNum = 0;
		charsNum.str("");
		charsNum.clear();
		count = count + 1;					
		*j = (BottleCup[*i][*j] == ',') ? *j + 1 : *j;
	}
	
	if(op > 30)
		cout << "Condicao invalida (nao conhecida)!" << endl;
	
	if(condition == true)
		*i = address - 1;
		
		
	ClearAll(j, Line, charsNum);
}

void ReturnCommand(int *i, int *j){	
	*j = *j + 1;
	int num = 0;
	int sizeNum = 0;
	int count = 0;
	int op;
	int address = 0;
	while(BottleCup[*i][*j] != '!'){
		
		ArgsAnalise(&sizeNum, &num, i, j);
				 
		if(count == 0)
			op = num;
		else
			address = num;
			
		
		if(op > 1)
			break;
			
		sizeNum = 0;
		charsNum.str("");
		charsNum.clear();
		count = count + 1;					
		*j = (BottleCup[*i][*j] == ',') ? *j + 1 : *j;
	}
	
	top = top - 1;
	if(op == 0)
		*i = stacks[top]+address;
	else
		*i = stacks[top]-address;
	
	ClearAll(j, Line, charsNum);
}




