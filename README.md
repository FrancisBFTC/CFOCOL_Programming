# CFOCOL_Programming
O CFOCOL é uma esolang denominada Chemical Formula of Coffe-oriented Language ou Linguagem orientada a fórmula química de café. Possui apenas 6 instruções em formato de fórmulas químicas do café e pode ser usada para "testar limites de aplicação" como na maioria das linguagens "Turing Tarpit". O CFOCOL, além de programação imperativa, cria outros conceitos de "Linguagem orientada a argumentos", onde as possíveis funcionalidades de 1 instrução pode ser descrita como argumentos numéricos. Neste repositório está armazenada Pasta de exemplos de algoritmos Cfocol, o interpretador da linguagem, arquivos de configurações e o código fonte do interpretador. Abaixo são descrito algumas funcionalidades e instruções da linguagem:

## Instruções da linguagem
  
  Existem 6 fórmulas químicas, cada uma pra um comando/instrução. Dessas 6 fórmulas: 2 são alcalóides, 2 são ácidos orgânicos, 1 é um diterpeno e 1 é um sacarone (açúcar), todos eles são umas das composições do café, veja abaixo:
  
 **Alcalóides ->**
 
    1. C8H10N4O2 -> Saída de dados (Impressão) - cafeína
    2. C7H8N4O2  -> Operações aritméticas      - teobromina
    
**Ácidos orgânicos ->**

    1. C9H8O4 -> Seleção de memória (Deslocamento) - ácido cafeico
    2. C7H6O3 -> Retorno de chamada                - ácido hidroxibenzoico 
    
 **Diterpeno e Sacarose ->**
 
    1. C20H28O3  -> salto/chamada condicional ou incondicional - cafestol
    2. C12H22O11 -> Entrada de dados                           - sacarose (açúcar)
    
    
## Procedimentos e sinais

Os Bottles (Garrafas) são os procedimentos/rotinas do CFOCOL, o Bottle (função) principal é obrigatoriamente o "cup", seguido por 2 pontos ':', assim como o Main de uma linguagem de programação de alto-nível. Todo Bottle deve abrir com ':' e finalizar com ';', dentro de cada Bottle terá instruções referenciadas pelos seus **identificadores** que são números hexadecimais para identificar uma determinada instrução. Também existem os **Bottles Secundários** que tem um sinal de referência '@' no começo, os nomes de Bottles poderão ser utilizados para ser chamados por instruções de saltos por outro Bottle, especificando também o identificador expecífico que se quer executar, veja abaixo as definições de sinais da linguagem e Bottles:

**Bottles(Procedimentos/rotinas):**
   1. Bottle principal - cup -> main.
   2. Bottles secundários - outros com @ (Ex.: @Bottle1).
 
**Identificadores:**
   1. 0000 a FFFF cada Bottle (Seguido por :)

**Sinais(sem aspas):**
   1.  ';'  -> finalização de Bottles
   2.  '!'  -> Finalização de instruções
   3.  '%'  -> quebra de linha em exibição
   4.  ','  -> concatenação de posições de memória
   5.  '@'  -> identificador de bottles secundários
   6.  '_'  -> acesso de identificadores por Bottles
   7.  ':'  -> atribuição de instruções em identificadores e Bottles
   8.  '$'  -> valor da posição atual de memória
   9.  '#'  -> valor da última posição deslocada
   10. '<>' -> exibição de inteiros das posições
   
   ## Funcionalidades do CFOCOL
   
   Em CFOCOL, além das instruções, é preciso conhecer os **argumentos**, já que a maior parte das funcionalidades de cada instrução são programadas pelos argumentos. Na linguagem CFOCOL, argumentos são números separados por vírgula que cada instrução pode utilizar, são esses números que define a funcionalidade daquela instrução, um exemplo é a teobromina _C7H8N4O2_, que é uma instrução de operações aritméticas, ela contém o 1ª argumento reservado para o tipo de operação, veja os tipos possíveis:
   
   Nª 0 - Adição <br>
   Nª 1 - Subtração <br>
   Nª 2 - Multiplicação <br>
   Nª 3 - Divisão <br>
   
   **Exemplos:**
   
      C7H8N4O2 0,2,1!  -> isto soma 2 + 1 e armazena o resultado em memória
      C7H8N4O2 1,2,1!  -> isto subtrai 2 - 1 e armazena o resultado em memória
      C7H8N4O2 2,2,1!  -> isto multiplica 2 * 1 e armazena o resultado em memória
      C7H8N4O2 3,2,1!  -> isto divide 2 / 1 e armazena o resultado em memória
      
 O mínimo de quantidade de argumentos em algumas instruções são 3, no entanto, em algumas instruções, como o de **deslocamento de memória**, o mínimo é apenas 2. Porém, pode ser utilizado mais de 3 argumentos para as operações aritméticas, Exemplos:
      
      C7H8N4O2 0,2,1,3,4! -> O resultado da soma em memória será 10
      C7H8N4O2 2,2,2,4,2! -> O resultado da multiplicação em memória será 32
      
 Então, já deu pra perceber que do 2ª argumento para frente é relacionado aos números que serão operados, o tipo de operação é determinada pelo 1ª argumento, assim como as fórmulas químicas tradicionais que conhecemos que tem suas representações numéricas separadas por vírgulas.
 No lugar de números, os argumentos também podem ser **Endereços**, que são chamadas de **Posições**. Existem 2 possíveis posições que podem ser acessadas simultaneamente: '$' e '#' (sem aspas). 
 
 O símbolo de dólar '$' representa a **posição atual** selecionada pela instrução _C9H8O4_, que é um ácido hidroxibenzóico para seleção e deslocamento de memória, enquanto que o símbolo de tralha '#' representa a **última posição** selecionada antes da posição atual e este símbolo se dar o nome de **último deslocamento**.
 No entanto, quando o programa começa, a 1ª posição selecionada por padrão é 0, logo, todo o programa pode-se basear apenas nesta posição, descartando o símbolo de último deslocamento. Quando uma operação aritmética é feita, mesmo que nenhuma posição é selecionada, o resultado desta operação é armazenada na posição 0 de memória, porém se uma nova posição for deslocada, a próxima operação armazenará o resultado nesta nova posição, e aí, o valor armazenado da posição anterior é recuperada pelo símbolo '#' e o valor da posição atual é recuperado pelo símbolo '$', veja 2 exemplos:
 
 **Exemplo 1:**
    
        C7H8N4O2 0,$,1! -> Considerando que o valor da posição de memória 0 é 0, logo, 0 + 1 = 1
        C7H8N4O2 0,$,3! -> Considerando que o valor da posição de memória 0 é 1, logo, 1 + 3 = 4
        C7H8N4O2 2,$,2! -> Considerando que o valor da posição de memória 0 é 4, logo, 4 * 2 = 16
        
        O valor final da posição 0 é 16.
  
  **Exemplo 2(seguindo o exemplo anterior):**
        
        C9H8O4 0,1!     -> 0 é operação de soma para deslocamento, logo, desloca +1 posição na memória
        C7H8N4O2 0,$,2! -> Considerando que o valor da posição de memória 1 é 0, logo, 0 + 2 = 2 
        C9H8O4 1,1!     -> 1 é operação de subtração para deslocamento, logo, desloca -1 posição na memória
        C7H8N4O2 1,$,1! -> Considerando que o valor da posição de memória 0 é 16, logo, 16 - 1 = 15
        C7H8N4O2 0,$,#! -> Considerando que $ é 15 e # (último deslocamento) é 2, logo, 15 + 2 = 17
        
        O valor final da posição atual (0) é 17 -> recuperado por $
        O valor final da posição anterior (1) é 2 -> recuperado por #
        
  O Ácido orgânico _C9H8O4_ é uma instrução para deslocamento de memória. Antes dela ser utilizada, a posição atual da memória é 0, porém, após ser utilizada, a posição pode assumir qualquer valor, exemplo: O 1ª argumento desta instrução pode ser 0 ou 1, 0 para soma de deslocamento e 1 para subtração de deslocamento; O 2ª argumento está relacionado ao número de operação para deslocamento, se for 1, deslocará 1 posição na memória, se for 2, 2 posições na memória, se for 5, vai deslocar 5 posições na memória, etc... o deslocamento irá pra frente se o 1ª argumento for 0 e o deslocamento irá pra trás se o 1ª argumento for 1. No entanto, só é possível utilizar o máximo de 2 argumentos nesta instrução, diferente de outras instruções que utiliza de 3 argumentos pra mais. No momento que a instrução de deslocamento é utilizada, a devida posição é selecionada, permitindo que operações aritméticas agem em cima destas posições, incluindo saltos condicionais/incondicionais. 
  
  Já que em CFOCOL não existem variáveis, a intenção é testar até onde será o limite das aplicações utilizando apenas 2 endereços simultaneamente por vez, então vamos dar um exemplo de várias seleções de memória:
  
       C9H8O4 0,5!  -> $ referencía o valor da posição 5
       C9H8O4 1,4!  -> $ referencía o valor da posição 1 (5-4=1) e # referencía o valor da posição 5
       C9H8O4 0,3!  -> $ referencía o valor da posição 4 (1+3=4) e # referencía o valor da posição 1
       C9H8O4 1,4!  -> $ referencía o valor da posição 0 (4-4=0) e # referencía o valor da posição 4
        
  
   Considerando este exemplo, '$' sempre vai referenciar a posição cujo resultado da posição é igual a posição anterior calculada com o número de posição atual (exceto na 1ª vez que o deslocamento é acionado), enquanto que '#' vai referenciar a mesma posição que '$' assumía anteriormente. Mas vamos considerar que queremos fazer uma operação e utilizar o resultado como um deslocamento, isso é possível, veja nos seguintes exemplos:
   
        C9H8O4 0,5!  -> $ referencía o valor da posição 5
        C7H8N4O2 0,$,2! -> soma o valor da posição 5 (0) + 2 e $ referencía o valor 2
        C9H8O4 0,$!  -> $ referencía o valor da posição 7, pois 5 + 2 = 7
        C9H8O4 1,#!  -> $ referencía o valor da posição 5, pois 7 - 2 = 5 (# = 2)
        C7H8N4O2 0,$,3! -> soma o valor da posição 5 (2) + 3 e $ referencía o valor 5
        C9H8O4 1,$!  -> $ referencía o valor da posição 0, pois 5 - 5 = 0
        
        Resultado final: $ = 0 (valor e posição)
                         # = 5 (valor e posição)
                         
                         
       
