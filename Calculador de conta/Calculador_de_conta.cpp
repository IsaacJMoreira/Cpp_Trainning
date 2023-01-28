#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;

/*lookup table que associa os preços aos códigos*/
float LUTprice[256] = 
{0,//ítem 0
 1.50,//água mineral s/gás (código 001)
 2.00,//água mineral c/gás (código 002)
 3.50,//refrigerante lata (código 003)
 4.00,// refrigerante lata ZERO (código 004)
 7.00,// cachorro quente simples (código 005)
 10.00,// cachorro quente completo (código 006)
 15.00,// hamburguer simples (código 007)
 20.00,// cheeseburguer simples (código 008)
 25.00,// cheeseburguer gorgonzola (código 009)
 30.00,// cheeseburguer carne 200g (código 010) 
 1000000.00//FEIJÃO PURO (código 011)
};
/*lookup table que associa os preços aos códigos*/

/*lookup table que associa os preços aos nomes*/
const char* LUTname[256] =
{ "0",//ítem 0
 "AGUA MINERAL S/GAS",//água mineral s/gás (código 001)
 "AGUA MINERAL C/GAS",//água mineral c/gás (código 002)
 "REFRIGERANTE LATA",//refrigerante lata (código 003)
 "REFRIGERANTE LATA ZERO",// refrigerante lata ZERO (código 004)
 "CACHORRO QUENTE SIMPLES",// cachorro quente simples (código 005)
 "CACHORRO QUENTTE COMPLETO",// cachorro quente completo (código 006)
 "HAMBURGUER SIMPPLES",// hamburguer simples (código 007)
 "CHEESEBURGUER SIMPLES",// cheeseburguer simples (código 008)
 "CHEESEBURGUER GORGONZOLA",// cheeseburguer gorgonzola (código 009)
 "CHEESEBURGUER 200G",// cheeseburguer carne 200g (código 010) 
 "FEIJAO PURO"//Feijão Puro (código 011)
};

/*lookup table que associa os preços aos nomes*/

#define ItemsInMenu  11

/*Variáveis globais*/
struct BillItem
{
int Code;//Guarda o código do produto
int Quantity;//Guarda o a quantidade do produto
};

BillItem Bill[50];//Declara uma array de ítens para armazenar a conta.
int BillItemCount = 0;//contador de ítens salvos na lista "Bill"
/*Variáveis globais*/

/*PROTÓTIPOS DAS FUNÇÕES COMEÇAM AQUI*/

float LocalTotal (BillItem Item);//função que calcula o total consumido por cada ítem

void PrintItemName (BillItem Item);//função que imprime, na tela, o nome do ítem

void PrintBillLine (BillItem Item);
 
void PrintBillHeader (int MESA);

void PrintBillFooter (float TOTAL);

void PrintCompleteBill(int MESA, int BillItemCount, BillItem Item[]);

int AskForInput (BillItem Item[], int& MESA);

/*PROTÓTIPOS DAS FUNÇÕES ACABAM AQUI*/

/*MAIN FUNCTION BLOCK*/
int main ()
{
   
    int NumeroMesa;
    BillItemCount = AskForInput(Bill, NumeroMesa);
    PrintCompleteBill(NumeroMesa, BillItemCount, Bill);

    return 0;
}
/*MAIN FUNCTION BLOCK*/

/*Funções*/

float LocalTotal (BillItem Item)
{
    return Item.Quantity * LUTprice[Item.Code];
}

void PrintItemName(BillItem Item)
{
    printf("%s\n",LUTname[Item.Code]);
}

//Imprime uma linha na formatação necessária   
void PrintBillLine (BillItem Item)
{
    printf("#%d - ", Item.Code);//printa "#" + código do produto + "-"
    PrintItemName(Item);//printa o nome do ítem
    printf("R$%4.2f", LUTprice[Item.Code]);
    printf("  x%d                    R$ ",Item.Quantity);//eem uma nova linha, printa quantos desse ítem foram pedidos, pula 20 espaços e printa o total local
    printf("%4.2f\n\n", LocalTotal(Item));
}

void PrintBillHeader (int MESA)
{
    const int ItensInColum = 41;
    for(int i = 0; i < ItensInColum ; i++)
    {
        printf("*");
    }
    printf("\nMESA: %d \n", MESA);
    for(int i = 0; i < ItensInColum ; i++)
    {
        printf("*");
    }
    printf("\nITEM                               TOTAL\n\n");

}

void PrintBillFooter (float TOTAL)
{
    const int ItensInColum = 41;
    for(int i = 0; i < ItensInColum ; i++)
    {
        printf("*");
    }
    printf("\n              TOTAL S/ COMISSAO R$ %4.2f", TOTAL);
    printf("\n                       COMISSAO R$ %4.2f", 0.1 * TOTAL);
    printf("\n                          TOTAL R$ %4.2f\n", 1.1 * TOTAL);
    for(int i = 0; i < ItensInColum ; i++)
    {
        printf("*");
    }

}

void PrintCompleteBill(int MESA, int BillItemCount, BillItem Item[])
{
    PrintBillHeader(MESA);
    float Total;
    for(int i = 0; i < BillItemCount; i++)
    {
        PrintBillLine(Item[i]);
        Total += LocalTotal(Item[i]);
    }
    PrintBillFooter(Total);
    
}

int AskForInput ( BillItem Item[] , int& MESA)//passando MESA por referência
{
    bool State = true;
    int ItemCount = 0, ItemCode, ItemQuantity, Response = 1;
    cout << "Digite o numero da mesa: ";
    cin >> MESA;
    do
    {
     do
     {
        cout << "Digite codigo: ";
        cin >> ItemCode;
        if( (ItemCode <= 0) || (ItemCode > ItemsInMenu ) )
        {
            printf("ERRO!  CODIGO DIGITADO INVALIDO!!\n");
        }
     }while ( (ItemCode <= 0) || (ItemCode > ItemsInMenu ) );

     printf("Item escolhido: %s\n", LUTname[ItemCode]);

     do
     {
       cout << "Digite a quantidade: ";
       cin >> ItemQuantity;
       if( ItemQuantity <= 0 )
       {
         printf("Erro! QUANTIDADE DIGITADA INVALIDA!!! \n");
       }
     } while ( ItemQuantity <= 0 );

     Item[ItemCount].Code = ItemCode;
     Item[ItemCount].Quantity = ItemQuantity;
     ItemCount++;
     
     do
     {
       cout << "Adicionar mais itens? (1 = sim | 0 = nao): ";
       cin >> Response;
       if(( Response != 0 ) && ( Response != 1))
       {
         printf("Erro! COMANDO INVALIDO!!! \n");
       }
     }while( ( Response != 0 ) && ( Response != 1) );

     State = Response;
           
    } while ( State );

    return ItemCount;
}