#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Funçao para ordenar cartas de uma mão. Os argumentos são a mão e o número de cartas da mão */
void sortCartas(char cartas[][3], int numcartas);

/* Funçao para encontrar uma sequencia de cartas (independente do naipe) */
int IsSequence(char valor5[], int numcartas);

/* Função para desempatar maos com a mesma configuração base */
int TenTie (char mao1[][3],char mao2[][3], int numcartas);

/* Função para encontrar um par numa mão */
int FindPair (char mao[][3], int numcartas);

/* Função para encontrar dois pares numa mão */
int FindTwoPair (char mao[][3], int numcartas);

/* Função para encontrar três cartas do mesmo naipe e duas que não são par numa mão */
int FindThreeOfAKind (char mao[][3], int numcartas);

/* Função para encontrar cinco cartas de valor consecutivo que não são todas do mesmo naipe numa mão */
int FindStraight (char mao[][3], int numcartas);

/* Função para encontrar cinco cartas do mesmo naipe que não sejam uma sequência numa mão */
int FindFlush (char mao[][3], int numcartas);

/* Função para encontrar três cartas de um valor e duas de outro numa mão */
int FindFullHouse (char mao[][3], int numcartas);

/* Função para encontrar quatro cartas de igual valor numa mão */
int FindFourOfAKind (char mao[][3], int numcartas);

/* Função para encontrar uma sequência do mesmo naipe numa mão */
int FindStraightFlush (char mao[][3], int numcartas);

/* Função para encontrar um Straight Flush com as cartas mais altas (Às,Rei,Dama,Valete,Dez) numa mão */
int FindRoyalFlush (char mao[][3], int numcartas);

/* Funcao que avalia a mao */
int modo5 (char mao[][3]);

/* Funcao que avalia a melhor mao possivel em 7 cartas */
int modo7 (char mao [][3], int argc);

char melhor_mao[5][3];

int main(int argc, char *argv[])
{
	// Cria um array com todas as cartas do baralho, indexadas por naipe e valor
    char baralho [4][13][3] = {{"AC","2C","3C","4C","5C","6C","7C","8C","9C","TC","JC","QC","KC"},
		                       {"AE","2E","3E","4E","5E","6E","7E","8E","9E","TE","JE","QE","KE"},
		                       {"AO","2O","3O","4O","5O","6O","7O","8O","9O","TO","JO","QO","KO"},
	                           {"AP","2P","3P","4P","5P","6P","7P","8P","9P","TP","JP","QP","KP"}};

	// Cria uma mão e inicializa com strings "00"
	char mao1 [5][3] ={"00","00","00","00","00"};
	char mao2 [5][3] ={"00","00","00","00","00"};
	char mao7 [7][3] ={"00","00","00","00","00","00","00"};

	// Switch que indica o modo 1
	char modo1[] ={"-c"};

	int i=0,j=0,c=0,numerradas=0,numcertas1=0,numcertas2=0,numcertastotal=0,x=0,p=0,r=0,q=0;

    if ((argc == 12) && (strcmp(argv[1],modo1)==0))
	{
		strcpy(mao1[0],argv[2]);
		strcpy(mao1[1],argv[3]);
		strcpy(mao1[2],argv[4]);
		strcpy(mao1[3],argv[5]);
		strcpy(mao1[4],argv[6]);

		strcpy(mao2[0],argv[7]);
		strcpy(mao2[1],argv[8]);
		strcpy(mao2[2],argv[9]);
		strcpy(mao2[3],argv[10]);
		strcpy(mao2[4],argv[11]);

		sortCartas(mao1,5);
		sortCartas(mao2,5);
		/*int l;
		for(l=0;l<5;l++)
        {
            printf("Carta1:[%d] : %s\n",l,mao1[l]);
            printf("Carta2:[%d] : %s\n",l,mao2[l]);
        } */

		for(x=0;x<4;x++)
		{
			if(strcmp(mao1[x],mao1[x+1])==0 || strcmp(mao2[x],mao2[x+1])==0)
			{
				printf("-1\n");
				return 0;
			}
		}

		for(c=0;c<5;c++)
		{
			for(i=0;i<4;i++)
			{
				for(j=0;j<13;j++)
				{
					if ((strcmp(mao1[c],baralho[i][j]) != 0))
					{
						numerradas++;
					}
					else if(strcmp(mao1[c],baralho[i][j]) == 0)
					{
						numcertas1++ ;

					}
				}
			}
		}
        for(p=0;p<5;p++)
		{
			for(r=0;r<4;r++)
			{
				for(q=0;q<13;q++)
				{
					if ((strcmp(mao2[p],baralho[r][q]) != 0))
					{
						numerradas++;
					}
					else if(strcmp(mao2[p],baralho[r][q]) == 0)
					{
						numcertas2++;

					}
				}
			}
		}
       numcertastotal = (numcertas1 + numcertas2);

	if ( ((argc == 12) && numcertastotal<10) || ((argc !=7) && (argc !=9) &&(argc !=11) && (argc != 12))|| (strcmp(argv[1],modo1)!=0))  //NAO E PRECISO TESTAR ARGCX
	{
		printf("-1\n");
		return 0;
	}
	else if ((numcertastotal == 10))
    {
        int pontos1=0,pontos2=0;  //Guarda o valor de cada mão nestas variaveis para depois comparar

        pontos1 = modo5(mao1);
        pontos2 = modo5(mao2);

        /*printf("pontos1 = %d & pontos2 = %d\n",pontos1,pontos2); */
        // comparar os pontos de cada mão e dar return de quem ganha

        if(pontos1 > pontos2)
        {
            printf("1\n");
            return 0;
        }
        else if (pontos1 < pontos2)
        {
            printf("2\n");
            return 0;
        }

        else if(pontos1 == pontos2)
        {
            if(TenTie(mao1,mao2,5)==2)
            {
              printf("2\n");
              return 0;
            }
             else if(TenTie(mao1,mao2,5)==1)
            {
             printf("1\n");
             return 0;
            }
            else if(TenTie(mao1,mao2,5)==0)
            {
             printf("0\n");
             return 0;
            }
        }

    }
}
else if ((argc == 9) && (strcmp(argv[1],modo1)==0)) //MODO 7 cartas
{
        strcpy(mao7[0],argv[2]);
		strcpy(mao7[1],argv[3]);
		strcpy(mao7[2],argv[4]);
		strcpy(mao7[3],argv[5]);
		strcpy(mao7[4],argv[6]);
		strcpy(mao7[5],argv[7]);
		strcpy(mao7[6],argv[8]);

        sortCartas(mao7,7);

		for(x=0;x<6;x++)
		{
			if(strcmp(mao7[x],mao7[x+1])==0)
			{
				printf("-1\n");
				return 0;
			}
		}
		int numcertas = 0;
		for(c=0;c<7;c++)
		{
			for(i=0;i<4;i++)
			{
				for(j=0;j<13;j++)
				{
					if ((strcmp(mao7[c],baralho[i][j]) != 0))
					{
						numerradas++;
					}
					else if(strcmp(mao7[c],baralho[i][j]) == 0)
					{
						numcertas++ ;

					}
				}
			}
		}

	if (numcertas<7 || argc != 9 || (strcmp(argv[1],modo1)!=0))
	{
		printf("-1\n");
		return 0;
	}
	else if ((numcertas == 7))
    {
        modo7(mao7,argc);
        return 0;
    }
}

	else if ((argc == 7) && (strcmp(argv[1],modo1)==0))
	{
		strcpy(mao1[0],argv[2]);
		strcpy(mao1[1],argv[3]);
		strcpy(mao1[2],argv[4]);
		strcpy(mao1[3],argv[5]);
		strcpy(mao1[4],argv[6]);
		numcertas1 = 0;
		numcertas2 = 0;

		sortCartas(mao1,5);
		int l;
		for(l=0;l<5;l++)
        {
            printf("Carta[%d] : %s\n",l,mao1[l]);
        }

		for(x=0;x<4;x++)
		{
			if(strcmp(mao1[x],mao1[x+1])==0)
			{
				printf("-1\n");
				return 0;
			}
		}
        int numcertas = 0;
		for(c=0;c<5;c++)
		{
			for(i=0;i<4;i++)
			{
				for(j=0;j<13;j++)
				{
					if ((strcmp(mao1[c],baralho[i][j]) != 0))
					{
						numerradas++;
					}
					else if(strcmp(mao1[c],baralho[i][j]) == 0)
					{
						numcertas++ ;
					}
				}
			}
		}
	if (numcertas<5 || argc != 7 || (strcmp(argv[1],modo1)!=0))
	{
		printf("-1\n");
		return 0;
	}
	else if ((numcertas == 5))
    {
        printf("%d\n", modo5(mao1));
    }
        /*char naipe[6] = {"00000"}; // Ciclo para obter no vetor naipe os naipes das cartas no vetor mao1
		int t=0;
		for(t=0;t<5;t++)
        {
            naipe[t] = mao1[t][1];
            printf("Naipe carta[%d] = %c\n",t,naipe[t]);

        } */
}
	return 0;

}

// FUNÇÕES:

int modo7 (char mao7[][3], int argc)
{
   int hand_value[22],t=0,j=0;
   char m[21][5][3];
   char melhor_mao[5][3];
   char tempocard[3];
   int tempomodule;

   strcpy(m[0][0], mao7[0]); strcpy(m[0][1],mao7[1]); strcpy(m[0][2],mao7[2]); strcpy(m[0][3],mao7[3]); strcpy(m[0][4],mao7[4]);
   hand_value[0]=modo5(m[0]);

   strcpy(m[1][0],mao7[0]); strcpy(m[1][1],mao7[1]); strcpy(m[1][2],mao7[2]); strcpy(m[1][3],mao7[3]); strcpy(m[1][4],mao7[5]);
   hand_value[1]=modo5(m[1]);

   strcpy(m[2][0],mao7[0]); strcpy(m[2][1],mao7[1]); strcpy(m[2][2],mao7[2]); strcpy(m[2][3],mao7[3]); strcpy(m[2][4],mao7[6]);
   hand_value[2]=modo5(m[2]);

   strcpy(m[3][0],mao7[0]); strcpy(m[3][1],mao7[1]); strcpy(m[3][2],mao7[2]); strcpy(m[3][3],mao7[4]); strcpy(m[3][4],mao7[5]);
   hand_value[3]=modo5(m[3]);

   strcpy(m[4][0],mao7[0]); strcpy(m[4][1],mao7[1]); strcpy(m[4][2],mao7[2]); strcpy(m[4][3],mao7[4]); strcpy(m[4][4],mao7[6]);
   hand_value[4]=modo5(m[4]);

   strcpy(m[5][0],mao7[0]); strcpy(m[5][1],mao7[1]); strcpy(m[5][2],mao7[2]); strcpy(m[5][3],mao7[5]); strcpy(m[5][4],mao7[6]);
   hand_value[5]=modo5(m[5]);

   strcpy(m[6][0],mao7[0]); strcpy(m[6][1],mao7[1]); strcpy(m[6][2],mao7[3]); strcpy(m[6][3],mao7[4]); strcpy(m[6][4],mao7[5]);
   hand_value[6]=modo5(m[6]);

   strcpy(m[7][0],mao7[0]); strcpy(m[7][1],mao7[1]); strcpy(m[7][2],mao7[3]); strcpy(m[7][3],mao7[4]); strcpy(m[7][4],mao7[6]);
   hand_value[7]=modo5(m[7]);

   strcpy(m[8][0],mao7[0]); strcpy(m[8][1],mao7[1]); strcpy(m[8][2],mao7[3]); strcpy(m[8][3],mao7[5]); strcpy(m[8][4],mao7[6]);
   hand_value[8]=modo5(m[8]);

   strcpy(m[9][0],mao7[0]); strcpy(m[9][1],mao7[2]); strcpy(m[9][2],mao7[3]); strcpy(m[9][3],mao7[4]); strcpy(m[9][4],mao7[5]);
   hand_value[9]=modo5(m[9]);

   strcpy(m[10][0],mao7[0]); strcpy(m[10][1],mao7[2]); strcpy(m[10][2],mao7[3]); strcpy(m[10][3],mao7[4]); strcpy(m[10][4],mao7[6]);
   hand_value[10]=modo5(m[10]);

   strcpy(m[11][0],mao7[0]); strcpy(m[11][1],mao7[2]); strcpy(m[11][2],mao7[3]); strcpy(m[11][3],mao7[5]); strcpy(m[11][4],mao7[6]);
   hand_value[11]=modo5(m[11]);

   strcpy(m[12][0],mao7[1]); strcpy(m[12][1],mao7[2]); strcpy(m[12][2],mao7[3]); strcpy(m[12][3],mao7[4]); strcpy(m[12][4],mao7[5]);
   hand_value[12]=modo5(m[12]);

   strcpy(m[13][0],mao7[1]); strcpy(m[13][1],mao7[2]); strcpy(m[13][2],mao7[3]); strcpy(m[13][3],mao7[4]); strcpy(m[13][4],mao7[6]);
   hand_value[13]=modo5(m[13]);

   strcpy(m[14][0],mao7[1]); strcpy(m[14][1],mao7[2]); strcpy(m[14][2],mao7[3]); strcpy(m[14][3],mao7[5]); strcpy(m[14][4],mao7[6]);
   hand_value[14]=modo5(m[14]);

   strcpy(m[15][0],mao7[2]); strcpy(m[15][1],mao7[3]); strcpy(m[15][2],mao7[4]); strcpy(m[15][3],mao7[5]); strcpy(m[15][4],mao7[6]);
   hand_value[15]=modo5(m[15]);

   strcpy(m[16][0],mao7[1]); strcpy(m[16][1],mao7[3]); strcpy(m[16][2],mao7[4]); strcpy(m[16][3],mao7[5]); strcpy(m[16][4],mao7[6]);
   hand_value[16]=modo5(m[16]);

   strcpy(m[17][0],mao7[1]); strcpy(m[17][1],mao7[2]); strcpy(m[17][2],mao7[4]); strcpy(m[17][3],mao7[5]); strcpy(m[17][4],mao7[6]);
   hand_value[17]=modo5(m[17]);

   strcpy(m[18][0],mao7[0]); strcpy(m[18][1],mao7[2]); strcpy(m[18][2],mao7[4]); strcpy(m[18][3],mao7[5]); strcpy(m[18][4],mao7[6]);
   hand_value[18]=modo5(m[18]);

   strcpy(m[19][0],mao7[0]); strcpy(m[19][1],mao7[3]); strcpy(m[19][2],mao7[4]); strcpy(m[19][3],mao7[5]); strcpy(m[19][4],mao7[6]);
   hand_value[19]=modo5(m[19]);

   strcpy(m[20][0],mao7[0]); strcpy(m[20][1],mao7[1]); strcpy(m[20][2],mao7[4]); strcpy(m[20][3],mao7[5]); strcpy(m[20][4],mao7[6]);
   hand_value[20]=modo5(m[20]);

    strcpy(melhor_mao[0], m[0][0]);
    strcpy(melhor_mao[1], m[0][1]);
    strcpy(melhor_mao[2], m[0][2]);
    strcpy(melhor_mao[3], m[0][3]);
    strcpy(melhor_mao[4], m[0][4]);


    /* for(pt=0;pt<21;pt++)
     {
         if(hand_value[pt] == 10)
         {
             //mete cartas no sitio e...
             printf("%s %s %s %s %s %d\n",m[pt][0],m[pt][1],m[pt][2],m[pt][3],m[pt][4],hand_value[pt]);
             return 10;
         }


     }*/
   int mao_mais_alta = 0;
   for(t=1; t<21; t++)
   {
       if(hand_value[t] > hand_value[mao_mais_alta])
       {
           mao_mais_alta = t;
       }
       else if(hand_value[t] == hand_value[mao_mais_alta])
       {
               if(TenTie(m[t], m[mao_mais_alta], 5)==1)
               {
                       mao_mais_alta = t;
               }
       }
   }


   strcpy(melhor_mao[0], m[mao_mais_alta][0]);
   strcpy(melhor_mao[1], m[mao_mais_alta][1]);
   strcpy(melhor_mao[2], m[mao_mais_alta][2]);
   strcpy(melhor_mao[3], m[mao_mais_alta][3]);
   strcpy(melhor_mao[4], m[mao_mais_alta][4]);

    if(argc == 9)
    {
         int modulo[] ={0,0,0,0,0}, i=0, z=0;
         char tempo[2];

       for(z=0;z<5;z++)
{
    switch(melhor_mao[z][0])
    {
    case 'A':
        if (melhor_mao[0][0] == '2' && melhor_mao[1][0] == '3' && melhor_mao[2][0] == '4' && melhor_mao[3][0] == '5')
        {
           modulo[z] = 1;
        }
        else
        {
           modulo[z] = 14;
        }
        break;
    case 'K':
        modulo[z] = 13;
        break;
    case 'Q':
        modulo[z] = 12;
        break;
    case 'J':
        modulo[z] = 11;
        break;
    case 'T':
        modulo[z] = 10;
        break;
    default:

     tempo[0] = melhor_mao[z][0];
     tempo[1] ='\0';
     modulo[z] = atoi(tempo); // Converter os valores(char) em numero inteiro
    }
  }

for(j=0;j<5;j++)
  for(i=0;i<4;i++)
  {
     if(modulo[i] < modulo[i+1])
     {
         strcpy(tempocard,melhor_mao[i+1]);
         strcpy(melhor_mao[i+1],melhor_mao[i]);
         strcpy(melhor_mao[i],tempocard);
         tempomodule = modulo[i+1];
         modulo[i+1] = modulo[i];
         modulo[i] = tempomodule;
     }
     else if(modulo[i] == modulo[i+1])
     {

     }
  }

       printf("%s %s %s %s %s %d\n",melhor_mao[0],melhor_mao[1],melhor_mao[2],melhor_mao[3],melhor_mao[4],hand_value[mao_mais_alta]);
    }

    else if (argc == 11)
    {
        printf("%s %s %s %s %s %d ",melhor_mao[0],melhor_mao[1],melhor_mao[2],melhor_mao[3],melhor_mao[4],hand_value[mao_mais_alta]);
    }




    return 0;
}

int modo5 (char mao[][3])
{
    {
        if(FindRoyalFlush(mao,5)==10)
        {
            return 10;
        }
        else if(FindStraightFlush(mao,5)==9)
        {
            return 9;
        }
        else if(FindFourOfAKind(mao,5)==8)
        {
            return 8;
        }
        else if(FindFullHouse(mao,5)==7)
        {
            return 7;
        }
        else if(FindFlush(mao,5)==6)
        {
            return 6;
        }
        else if(FindStraight(mao,5)==5)
        {
            return 5;
        }
        else if(FindThreeOfAKind(mao,5)==4)
        {
            return 4;
        }
        else if(FindTwoPair(mao,5)==3)
        {
            return 3;
        }
		else if(FindPair(mao,5)==2)
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }
}

void sortCartas(char cartas [][3], int numcartas)
{
	int i=0,j=0;
	char temp[3];

	for(i=0;i<numcartas;i++)
		for(j=0;j<numcartas-1;j++)
			if(strcmp(cartas[j],cartas[j+1])>0)
			{
				strcpy(temp,cartas[j]);
				strcpy(cartas[j],cartas[j+1]);
				strcpy(cartas[j+1],temp);
			}
}

int IsSequence(char valor[], int numcartas)
 {
     int modulo[]={0,0,0,0,0};
     int i=0;

      for(i=0;i<numcartas;i++)
   {
     char temp[2];
     temp[0] = valor[i]; // A função atoi estava a buggar pq o argumento era um char em vez de uma string(const char*)
     temp[1] ='\0';
     modulo[i] = atoi(temp); // Converter os valores(char) em numero inteiro (os valores A,K,Q,J vão dar zero)
   }

/* TIPOS DE STRAIGHT: (Sem ligar a nipes e com os valores apos levarem sort):

A | 9 | 8 | 7 | 6 |	  | 5 |	    | 2 |    |valor[0]|
J | J | 9 | 8 | 7 |   | 6 |	    | 3 |       .
K | K | J | 9 | 8 |...| 7 | ... | 4 |       .
Q | Q | Q | J | 9 |	  | 8 |     | 5 |       .
T | T | T | T | T |	  | 9 |     | A |    |valor[4]|

MAIOR VALOR ----------> MENOR VALOR */


   if((valor [4] == 'A') && (valor [3] == '5') && (valor [2] == '4') && (valor [1] == '3') && (valor [0] == '2'))  //Para mão do tipo: AC 2C 3E 4C 5P
   {
     modulo[4] = 1;
   }
   else if((valor [4] == 'T') && (valor [3] == '9') && (valor [2] == '8') && (valor [1] == '7') && (valor [0] == '6')) //Para mao do tipo: 6P 7C 8E 9P TC
   {
       modulo[4] = 10;
   }
   else if((valor [4] == 'T') && (valor [3] == 'J') && (valor [2] == '9') && (valor [1] == '8') && (valor [0] == '7')) //Para mao do tipo: 7C 8E 9P TC JC
   {
       modulo[4] = 10;
       modulo[3] = 11;
   }
   else if((valor [4] == 'T') && (valor [3] == 'Q') && (valor [2] == 'J') && (valor [1] == '9') && (valor [0] == '8'))
   {
       modulo[4] = 10;
       modulo[3] = 12;
       modulo[2] = 11;
   }
   else if((valor [4] == 'T') && (valor [3] == 'Q') && (valor [2] == 'K') && (valor [1] == 'J') && (valor [0] == '9'))
   {
       modulo[4] = 10;
       modulo[3] = 12;
       modulo[2] = 13;
       modulo[1] = 11;
   }
   else if((valor [4] == 'T') && (valor [3] == 'Q') && (valor [2] == 'K') && (valor [1] == 'J') && (valor [0] == 'A'))
   {
       modulo[4] = 10;
       modulo[3] = 12;
       modulo[2] = 13;
       modulo[1] = 11;
       modulo[0] = 14;
   }

   int t=0,y=0,n=5,temp;   // Ordenar vetor modulo para depois testar se sao sequencia crescente


   for(t=0;t<n-1;t++)
      for(y=0;y<n-t-1;y++)
        if(modulo[y] > modulo[y+1])
           {
             temp = modulo[y];
             modulo[y] = modulo[y+1];
             modulo[y+1] = temp;
           }

   int w=0, consecutivo=0;    //Verificar se o valor de cada elemento do vetor difere do seguinte por 1

    for(w=0;w<4;w++)          // 4 vezes porque modulo tem 5 valores( comparamos 1º/2º, 2º/3º, 3º/4º, 4º/5º )
     {
       if(modulo[w] == (modulo[w+1]-1))
       {
         consecutivo++ ;
       }
     }
     if(consecutivo == 4)  //Todos os adjacentes diferem por uma unidade
     {
         return 1;
     }
     else
     {
         return 0;
     }
 }
                                             //Funções que determinam os valores dos diferentes tipos de mão

int FindPair (char mao[][3], int numcartas)
{
   char valor[6] ={"00000"};
   int f=0;

   for(f=0;f<numcartas;f++) // Ciclo para obter no vetor valor os valores das cartas no vetor mao
     {
       valor[f] = mao[f][0];
     }
   if(valor[0]==valor[1]||valor[1]==valor[2]||valor[2]==valor[3]||valor[3]==valor[4])
   {
       return 2;
   }
   else
   {
       return 0;
   }
}

int FindTwoPair (char mao[][3], int numcartas)
{
   char valor[6] ={"00000"};
   int f=0;

   for(f=0;f<numcartas;f++) // Ciclo para obter no vetor valor os valores das cartas no vetor mao
     {
       valor[f] = mao[f][0];
     }
   if((valor[0]==valor[1] && valor[2]==valor[3])||
      (valor[1]==valor[2] && valor[3]==valor[4])||
      (valor[0]==valor[1] && valor[3]==valor[4]))
   {
       return 3;
   }
   else
   {
       return 0;
   }
}

int FindThreeOfAKind (char mao[][3], int numcartas)
{
   char valor[6] ={"00000"};
   int f=0;

   for(f=0;f<numcartas;f++) // Ciclo para obter no vetor valor os valores das cartas no vetor mao
     {
       valor[f] = mao[f][0];
     }
   if((valor[0]==valor[1] && valor[1]==valor[2] && valor[3] != valor[4])||
      (valor[1]==valor[2] && valor[2]==valor[3] && valor[0] != valor[4])||
      (valor[2]==valor[3] && valor[3]==valor[4] && valor[0] != valor[1]))
   {
       return 4;
   }
   else
   {
       return 0;
   }
}

int FindStraight(char mao[][3], int numcartas)
{
int j=0,f=0;
   char valor[6]={"00000"};
   char naipe[6] ={"00000"};


 for(f=0;f<numcartas;f++) // Ciclo para obter no vetor naipe os naipes das cartas no vetor mao
 {
    naipe[f] = mao[f][1];
 }

 for(j=0;j<numcartas;j++)
 {
     valor[j] = mao[j][0]; //Obter os valores da mão(char) e guardá-los no vetor valor
 }

   if(!(naipe[0]==naipe[1] && naipe[1]==naipe[2] && naipe[2]==naipe[3] && naipe[3]==naipe[4]) && (IsSequence(valor,5) == 1) )
   {
       return 5;
   }
   else
   {
       return 0;
   }
}

int FindFlush (char mao[][3], int numcartas)
{
 char naipe[6] ={"00000"};
 int f=0;

   for(f=0;f<numcartas;f++) // Ciclo para obter no vetor naipe os naipes das cartas no vetor mao
     {
       naipe[f] = mao[f][1];
     }
   if(naipe[0]==naipe[1] && naipe[1]==naipe[2] && naipe[2]==naipe[3] && naipe[3]==naipe[4])
   {
       return 6;
   }
   else
   {
       return 0;
   }
}

int FindFullHouse (char mao[][3], int numcartas)
{
    char valor[6] ={"00000"};
    int f=0;

    for(f=0;f<numcartas;f++) // Ciclo para obter no vetor valor os valores das cartas no vetor mao
     {
       valor[f] = mao[f][0];
     }
   if(((valor[0]==valor[1] && valor[1]==valor[2]) && valor[3]==valor[4]) ||
       ((valor[2]==valor[3] && valor[3]==valor[4]) && valor[0]==valor[1]))
   {
       return 7;
   }
   else
   {
       return 0;
   }
}

int FindFourOfAKind (char mao[][3], int numcartas)
{
    char valor[6] ={"00000"};
    int f=0;

    for(f=0;f<numcartas;f++) // Ciclo para obter no vetor valor os valores das cartas no vetor mao
     {
       valor[f] = mao[f][0];
     }
   if((valor[0]==valor[1] && valor[1]==valor[2] && valor[2]==valor[3]) ||
      (valor[1]==valor[2] && valor[2]==valor[3] && valor[3]==valor[4]))
   {
       return 8;
   }
   else
   {
       return 0;
   }
}

 int FindStraightFlush (char mao[][3], int numcartas)
{
   int j=0,f=0;
   char valor[6]={"00000"};
   char naipe[6] ={"00000"};


 for(f=0;f<numcartas;f++) // Ciclo para obter no vetor naipe os naipes das cartas no vetor mao
 {
    naipe[f] = mao[f][1];
 }

 for(j=0;j<numcartas;j++)
 {
     valor[j] = mao[j][0]; //Obter os valores da mão(char) e guardá-los no vetor valor
 }

   if(((naipe[0]==naipe[1]) && (naipe[1]==naipe[2]) && (naipe[2]==naipe[3]) && (naipe[3]==naipe[4])) && (IsSequence(valor,5) == 1) )
   {
       return 9;
   }
   else
   {
       return 0;
   }
}

int FindRoyalFlush (char mao[][3], int numcartas)
{
   int i=0,j=0;
   char valor[6]={"00000"};
   char naipe[6]={"00000"};

 for(j=0;j<numcartas;j++)
 {
     valor[j] = mao[j][0]; //Obter os valores da mão(char) e guardá-los no vetor valor
 }

 for(i=0;i<numcartas;i++)
 {
     naipe[i] = mao[i][1]; //Obter os valores da mão(char) e guardá-los no vetor valor
 }

     if(((valor[0] == 'A') && (valor[1] == 'J') && (valor[2] == 'K') && (valor[3] == 'Q') && (valor[4] == 'T')) &&
        ((naipe[0] == naipe[1]) && (naipe[1] == naipe[2]) && (naipe[2] == naipe[3]) && (naipe[3] == naipe[4])))
     {
         return 10;
     }

     else
     {
         return 0;
     }
  }

  //Função para desempatar duas maos com a mesma configuração base
  int TenTie (char mao1[][3],char mao2[][3], int numcartas)
  {
      int i=0,j=0,z=0;
      int modulo1[]={0,0,0,0,0};
      int modulo2[]={0,0,0,0,0};
      char valor1[]={"00000"};
      char valor2[]={"00000"};
      char tempo1[2];
      char tempo2[2];

     for(j=0;j<numcartas;j++)
 {
     valor1[j] = mao1[j][0]; //Obter os valores da mão1(char) e guardá-los no vetor valor
 }

   for(i=0;i<numcartas;i++)
 {
     valor2[i] = mao2[i][0]; //Obter os valores da mão2(char) e guardá-los no vetor valor
 }

 for(z=0;z<5;z++)
{
    switch(valor1[z])
    {
    case 'A':
        if (valor1[0] == '2' && valor1[1] == '3' && valor1[2] == '4' && valor1[3] == '5')
        {
           modulo1[z] = 1;
        }
        else
        {
           modulo1[z] = 14;
        }
        break;
    case 'K':
        modulo1[z] = 13;
        break;
    case 'Q':
        modulo1[z] = 12;
        break;
    case 'J':
        modulo1[z] = 11;
        break;
    case 'T':
        modulo1[z] = 10;
        break;
    default:

     tempo1[0] = valor1[z];
     tempo1[1] ='\0';
     modulo1[z] = atoi(tempo1); // Converter os valores(char) em numero inteiro
    }
  }
int s=0;
for(s=0;s<5;s++)
{
    switch(valor2[s])
    {
    case 'A':
        if (valor2[0] == '2' && valor2[1] == '3' && valor2[2] == '4' && valor2[3] == '5')
        {
           modulo2[s] = 1;
           break;
        }
        else
        {
           modulo2[s] = 14;
           break;
        }
        break;
    case 'K':
        modulo2[s] = 13;
        break;
    case 'Q':
        modulo2[s] = 12;
        break;
    case 'J':
        modulo2[s] = 11;
        break;
    case 'T':
        modulo2[s] = 10;
        break;
    default:

     tempo2[0] = valor2[s];
     tempo2[1] ='\0';
     modulo2[s] = atoi(tempo2); // Converter os valores(char) em numero inteiro

    }
}     //os vetores modulo ja têm o valor de cada carta em inteiro, mas ainda falta ordenar(ordem crescente) os seus valores

int t=0,y=0,n=5,temp;   // Ordenar vetor modulo para depois poder comparar cada elemento relativamente à outra mão


   for(t=0;t<n-1;t++)
      for(y=0;y<n-t-1;y++)
        if(modulo1[y] > modulo1[y+1])
           {
             temp = modulo1[y];
             modulo1[y] = modulo1[y+1];
             modulo1[y+1] = temp;
           }

       /*a =0;
           for(a=0;a<5;a++)
   {
       printf("MODULO1[%d]: %d\n",a,modulo1[a]);
   } */
   //printf("\n");
    t=0;
    y=0;
    temp =0;
    n=5;
     for(t=0;t<n-1;t++)
      for(y=0;y<n-t-1;y++)
        if(modulo2[y] > modulo2[y+1])
           {
             temp = modulo2[y];
             modulo2[y] = modulo2[y+1];
             modulo2[y+1] = temp;
           }


    /*int a=0;
           for(a=0;a<5;a++)
   {
       printf("MODULO2[%d]: %d\n",a,modulo2[a]);
       printf("MODULO1[%d]: %d\n",a,modulo1[a]);
   } */
   int d=0;
   int modulotemp[] = {0,0,0,0,0};

if((FindFourOfAKind(mao1,5)==8)) // vetores do tipo X 4 4 4 4 estão prontos a ser comparados
      {
          if((modulo1[0] == modulo1[1]) && (modulo1[1] == modulo1[2]) && (modulo1[2] == modulo1[3]))
          {
             modulotemp[0] = modulo1[4];

             modulo1[4] = modulo1[3];
             modulo1[3] = modulo1[2];
             modulo1[2] = modulo1[1];
             modulo1[1] = modulo1[0];
             modulo1[0] = modulotemp[0];
          }
          if((modulo2[0] == modulo2[1]) && (modulo2[1] == modulo2[2]) && (modulo2[2] == modulo2[3]))
          {
             modulotemp[0] = modulo2[4];

             modulo2[4] = modulo2[3];
             modulo2[3] = modulo2[2];
             modulo2[2] = modulo2[1];
             modulo2[1] = modulo2[0];
             modulo2[0] = modulotemp[0];
          }

          if((modulo1[4] > modulo2[4]))
           {
           return 1;
           }
          else if (modulo1[4] < modulo2[4])
          {
              return 2;
          }
          else
          {
              if (modulo1[0] > modulo2[0])
              {
                  return 1;
              }
              else if (modulo1[0] < modulo2[0])
              {
                  return 2;
              }
          }

          return 0;
      }
   else if((FindFullHouse(mao1,5)==7)) //Caso que desempata 2 FullHouse, vetores do tipo P P 3 3 3 estão prontos a ser comparados
      {
          if((modulo1[0] == modulo1[1]) && (modulo1[0] == modulo1[1]))
           {
             modulotemp[0] = modulo1[3]; //guardar os valores do par no vetor temporario
             modulotemp[1] = modulo1[4];

             modulo1[4] = modulo1[2];    //reposicionar o trio no fim do vetor modulo
             modulo1[3] = modulo1[1];
             modulo1[2] = modulo1[0];
             modulo1[0] = modulotemp[0]; //recolocar o par no inicio do vetor modulo
             modulo1[1] = modulotemp[1];

           }
           if((modulo2[0] == modulo2[1]) && (modulo2[1] == modulo2[2]))
           {
             modulotemp[0] = modulo2[3]; //guardar os valores do par no vetor temporario
             modulotemp[1] = modulo2[4];

             modulo2[4] = modulo2[2];    //reposicionar o trio no fim do vetor modulo
             modulo2[3] = modulo2[1];
             modulo2[2] = modulo2[0];
             modulo2[0] = modulotemp[0]; //recolocar o par no inicio do vetor modulo
             modulo2[1] = modulotemp[1];
           }
        if(((modulo1[4] > modulo2[4])) || ((modulo1[4] == modulo2[4]) && (modulo1[0] > modulo2[0])) )
        {
            return 1;
        }
        else if((modulo1[4] == modulo2[4]) && (modulo1[0] == modulo2[0]))
        {
            return 0;
        }
        else
        {
            return 2;
        }
      }

       else if((FindTwoPair(mao1,5)==3)) // X P P P' P' esta pronto a ser comparado
    {

      if((modulo1[0] == modulo1[1]) && (modulo1[3] == modulo1[4])) // P P X P' P'
      {
          modulotemp[0] = modulo1[2];

          modulo1[2] = modulo1[1];
          modulo1[1] = modulo1[0];
          modulo1[0] = modulotemp[0];
      }
      else if((modulo1[0] == modulo1[1]) && (modulo1[2] == modulo1[3])) // P P P' P' X
      {
          modulotemp[0] = modulo1[4];

          modulo1[4] = modulo1[3];
          modulo1[3] = modulo1[2];
          modulo1[2] = modulo1[1];
          modulo1[1] = modulo1[0];
          modulo1[0] = modulotemp[0];
      }
      // Organizar modulo2
      if((modulo2[0] == modulo2[1]) && (modulo2[3] == modulo2[4])) // P P X P' P'
      {
          modulotemp[0] = modulo2[2];

          modulo2[2] = modulo2[1];
          modulo2[1] = modulo2[0];
          modulo2[0] = modulotemp[0];
      }
      else if((modulo2[0] == modulo2[1]) && (modulo2[2] == modulo2[3])) // P P P' P' X
      {
          modulotemp[0] = modulo2[4];

          modulo2[4] = modulo2[3];
          modulo2[3] = modulo2[2];
          modulo2[2] = modulo2[1];
          modulo2[1] = modulo2[0];
          modulo2[0] = modulotemp[0];
      }
      /* int a =0;
      for(a=0;a<5;a++)
      {
          printf("valor1[%d] : %d\n",a,modulo1[a]);
          printf("valor2[%d] : %d\n",a,modulo2[a]);
      } */

      if((modulo1[4] > modulo2[4]) ||
        ((modulo1[4] == modulo2[4]) && (modulo1[2] > modulo2[2])) ||
        ((modulo1[4] == modulo2[4]) && (modulo1[2] == modulo2[2]) && (modulo1[0] > modulo2[0])))
      {
          return 1;
      }
      else if((modulo1[4] == modulo2[4]) && (modulo1[2] == modulo2[2]) && (modulo1[0] == modulo2[0]))
        {
            return 0;
        }
      else
      {
          return 2;
      }
    }

    else if((FindPair(mao1,5)==2)) //Para o caso X X X P P o vetor modulo estará pronto a ser comparado
     {
         if((modulo1[0] == modulo1[1])) // P P X X X
         {
             modulotemp[0] = modulo1[2];  //Salvaguardar valores para depois reposicionar
             modulotemp[1] = modulo1[3];
             modulotemp[2] = modulo1[4];

             modulo1[3] = modulo1[0];    //Colocar nas 2 ultimas posiçoes o par e nas 3 primeiras os restantes valores por ordem crescente
             modulo1[4] = modulo1[1];
             modulo1[2] = modulotemp[2];
             modulo1[1] = modulotemp[1];
             modulo1[0] = modulotemp[0];
         }
         else if((modulo1[1] == modulo1[2])) // X P P X X  // 5E 7P TO AC 7O ---- 5E 7O 7P AC TC --- 5 7 7 10 14 --- 4 10 14 7 7
         {
             modulotemp[0] = modulo1[3];
             modulotemp[1] = modulo1[4];

             modulo1[3] = modulo1[1];
             modulo1[4] = modulo1[2];
             modulo1[1] = modulotemp[0];
             modulo1[2] = modulotemp[1];
         }
         else if(modulo1[2] == modulo1[3]) // X X P P X
         {
             modulotemp[0] = modulo1[4];

             modulo1[3] = modulo1[2];
             modulo1[4] = modulo1[3];
             modulo1[2] = modulotemp[0];
         }
    //Organizar modulo2
    if((modulo2[0] == modulo2[1])) // P P X X X ----      3 9 10 8 8
         {
             modulotemp[0] = modulo2[2];  //Salvaguardar valores para depois reposicionar
             modulotemp[1] = modulo2[3];
             modulotemp[2] = modulo2[4];

             modulo2[3] = modulo2[0];    //Colocar nas 2 ultimas posiçoes o par e nas 3 primeiras os restantes valores por ordem crescente
             modulo2[4] = modulo2[1];
             modulo2[2] = modulotemp[2];
             modulo2[1] = modulotemp[1];
             modulo2[0] = modulotemp[0];
         }
         else if((modulo2[1] == modulo2[2])) // X P P X X
         {
             modulotemp[0] = modulo2[3];
             modulotemp[1] = modulo2[4];

             modulo2[3] = modulo2[1];
             modulo2[4] = modulo2[2];
             modulo2[1] = modulotemp[0];
             modulo2[2] = modulotemp[1];
         }
         else if(modulo2[2] == modulo2[3]) // X X P P X
         {
             modulotemp[0] = modulo2[4];

             modulo2[3] = modulo2[2];
             modulo2[4] = modulo2[3];
             modulo2[2] = modulotemp[0];
         }

    if(modulo1[4] > modulo2[4])     /* 5 10 13 7 7  vs 3 9 10 8 8 */
    {
        return 1;
    }
    else if(modulo2[4]> modulo1[4])
    {
        return 2;
    }
    else if((modulo1[4] == modulo2[4]) && (modulo1[3] == modulo2[3]))
    {
    for(d=2;d>=0;d--)
     {
     if(modulo1[d] > modulo2[d])
      {
        return 1;
      }
     else if(modulo1[d] < modulo2[d])
      {
        return 2;
      }
     }
    }
   else
   {
       return 0;
   }
  /* int a =0;
      for(a=0;a<5;a++)
      {
          printf("valor1[%d] : %d\n",a,modulo1[a]);
          printf("valor2[%d] : %d\n",a,modulo2[a]);
      } */

}

  else
{
   for(d=4;d>=0;d--)
     {
       if(modulo1[d] > modulo2[d])
       {
           return 1;
       }
       else if(modulo1[d] < modulo2[d])
       {
           return 2;
       }
    }
}
 return 0;
}






