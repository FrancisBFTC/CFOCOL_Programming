#include "cfocol.h"

bool cont(string, string);
void IgnoreSpaces(void);
void PreInterpreter(void);


int main(int argc, char *argv[ ]){

	if(argc > 1){
     if(cont(argv[1], ".cf") || cont(argv[1], ".cfl") || cont(argv[1], ".cop")){
		
		readFile = fopen(argv[1], "r");
		if(readFile != NULL){
			
			PreInterpreter();
			
			for(int i = 0; i < 100; i++){
   				for(int j = 6; j < 100; j++){
      				Line << BottleCup[i][j];
      				
      				if(Line.str() == PRINT)
						PrintCommand(i, &j);
					else
						if(Line.str() == OPERATION)
							OperationCommand(&i, &j);
						else
							if(Line.str() == SELECTION)
								SelectionCommand(&i, &j);
							else
								if(Line.str() == SALTOCOND)
									JumpCondition(&i, &j);
								else
									if(Line.str() == RETURNS)
										ReturnCommand(&i, &j);
								
						
   				}
			}
			
		}else{
			printf("\nErro na abertura do arquivo '%s'\n\n", argv[1]);
  			return 0;
		}
  		
  		fclose(readFile);
  		
	 }else{
	 	printf("\nO arquivo nao e interpretavel pelo CFOCOL\n\n");
	 }
	}else{
		printf("\nO Interpretador espera argumentos...\n");
		printf("Nenhum arquivo pra interpretar!\n\n");
		system("pause");
	}
	 
 return 0;
}
