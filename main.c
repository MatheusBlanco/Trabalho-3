/*
Alunos-Matrícula:
 Marcos Nery Borges Junior - 17/0017885
 Matheus Salles Blanco - 16/0138400
 Gabriel Braga Mendes - 15/0126077
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct elem{
    
    char nome[101];
    char num[11];
    char end[101];
    unsigned int cep;
    char dnas[11];
    struct elem *prox;
    struct elem *ant;
    
    };
typedef struct elem Lista;

Lista *insereOrden(char nome[101], char num[11], char end[101], unsigned int cep, char dnas[11], Lista *L);
Lista *preencher(Lista *L);
void salvarLista(Lista *L);
Lista *inserir(Lista *L);
Lista *remover(char nome[101],Lista *L);
Lista *removerPorNome(Lista *L);
void imprimePorNome(Lista *L);
void imprimeOrdem(Lista *L);


int main(){
    
    

    
    Lista *listaContatos;
    int op;
    listaContatos = NULL;
    listaContatos = preencher(listaContatos);
    
        do{
        
        printf("Digite o valor da opcao desejada\n1 Inserir novo registro\n2 Remover registro\n3 Procurar registro\n4 Vizualizar registros\n0 Sair\n");
        scanf("%d",&op);
        switch(op){
            
            case 1:
               listaContatos= inserir(listaContatos);
            break;
            
            case 2:
               listaContatos = removerPorNome(listaContatos);
            break;
            
            case 3:
               imprimePorNome(listaContatos);
             
             break;
            case 4:
              imprimeOrdem(listaContatos);
         
            break;     
            }
        }while(op);
        
        salvarLista(listaContatos);
        
     return 0;
}
Lista *insereOrden(char nome[101], char num[11], char end[101], unsigned int cep, char dnas[11], Lista *L){
    
    Lista *elem;
    Lista *aux;
    elem = (Lista *)malloc(sizeof(Lista));
    if(elem == NULL){
         printf("Alocacao dinamica falhou");
         exit(1);
        
        }
    
    strncpy(elem->nome, nome, (sizeof elem->nome) - 1);
    elem->nome[100] = '\0';
    strncpy(elem->num, num, (sizeof elem->num) - 1);
    elem->num[10] = '\0';
    strncpy(elem->end, end, (sizeof elem->end) - 1);
    elem->end[100] = '\0';
    elem->cep = cep;
    strncpy(elem->dnas, dnas, (sizeof elem->dnas) - 1);
    elem->dnas[10] = '\0';
   
       if(L==NULL){
        
          
        elem->prox=NULL;
        elem->ant = NULL;
          return elem;
        
        }
        else{
            
            for(aux=L;aux!=NULL;aux=aux->prox){
               
              
                if(strcmp(elem->nome,aux->nome)<1){
                    

                      if(aux->ant==NULL){
                          
                           elem->prox = aux;
                           elem->ant = NULL;
                           aux->ant = elem;
                           return elem;
                          
                          }
                      elem->prox = aux;
                      elem->ant = aux->ant;
                      (aux->ant)->prox = elem;
                      aux->ant = elem;
                          
                      return L;
                          
                          
                      
                      
                }
                
                
                if(aux->prox==NULL){
                    
                     aux->prox = elem;
                     elem->prox = NULL;
                     elem->ant = aux;
                     return L;
                    
                    
                    
                    }

                
            }
            
        
        }
    
    return NULL;
}
Lista *preencher(Lista *L){
    

    char nome[101];
    char num[11];
    char end[101];
    unsigned int cep;
    char dnas[11];
    char temp; 
    FILE *fp;  
  
     fp = fopen("contatos.txt","a+"); 
     if (fp==NULL) { 
         printf("Falha.\n"); 
         exit(1); } 
         
     while(!feof(fp)){  
        fscanf(fp,"%[^\n]\n%[^\n]\n%[^\n]\n%u\n%[^\n]\n%c\n",nome,num,end,&cep,dnas,&temp);
        L = insereOrden(nome,num,end,cep,dnas,L);
     
     }
     fclose(fp);
     
     
     return L;
    
    }

void salvarLista(Lista *L){
    Lista *elem;
    FILE *fp;  
    fp = fopen("contatos.txt","w"); 
    if (fp==NULL) { 
            printf("Falha.\n"); 
            exit(1); } 
            
            
    for(elem = L; elem !=NULL;elem=elem->prox){
        
      fprintf(fp,"%s\n%s\n%s\n%u\n%s\n%c\n",elem->nome,elem->num,elem->end,elem->cep,elem->dnas,'$');
 
    
    } 
 fclose(fp); 
    
}   
Lista *inserir(Lista *L){
    
    char nome[101];
    char nutemp[10];
    char num[11];
    char end[101];
    unsigned int cep;
    char dntemp[9];
    char dnas[11];
    int i,j=0;
    
    printf("Digite o nome:\n");
    scanf(" %[^\n]",nome);
    printf("Digite o numero de telefone:\n");
    scanf("%s",nutemp);
    printf("Digite o endereco:\n");
    scanf(" %[^\n]", end);
    printf("Digite o CEP:\n");
    scanf("%u",&cep);
    printf("Digite a data de nascimento:\n");
    scanf("%s",dntemp);
    for(i=0;i<11;i++){
        if(i==2 || i== 5){dnas[i] = '\\'; }
        else{dnas[i] = dntemp[j];j++;}
    }
    j=0;
    for(i=0;i<11;i++){
        
        if(i==5){num[i] = '-';}
        else{num[i] = nutemp[j];j++;}
        
    }
    
    
    L = insereOrden(nome,num,end,cep,dnas,L);
    printf("%s\n%s\n%s\n%u\n%s\n",nome,num,end,cep,dnas);
    
    return L;
    }
Lista *remover(char nome[101],Lista *L){
    
    Lista *pi = L;

    if(!strcmp(L->nome,nome)){
        
        
        (L->prox)->ant = NULL;
        pi = L->prox; 
        free(L);
        return pi;        
    }


    while(L->prox!=NULL){
        
        if(!strcmp(L->nome,nome)){
                   
                (L->ant)->prox = L->prox;
                (L->prox)->ant = L->ant;
                free(L);
                return pi;
        }
            
       L=L->prox;      
    } 


    (L->ant)->prox = NULL;
    free(L);
    return pi;
    
}

Lista *removerPorNome(Lista *L){
     
     char nome[101];
     printf("Digite o nome no registro a ser deletado:\n");
     scanf(" %[^\n]",nome);
      L = remover(nome,L);
    
    
     return L;
    }

void imprimePorNome(Lista *L){
    
   char nome[101];
   printf("Digite o nome a ser pesquisado:\n");
   scanf(" %[^\n]",nome); 
    
    
   Lista *elem;
   for(elem = L; elem!=NULL;elem=elem->prox){
       
         if(!strcmp(elem->nome,nome)){
              printf("%s\n%s\n%s\n%u\n%s\n",elem->nome,elem->num,elem->end,elem->cep,elem->dnas);
              break;
              }
       
       }
       

  
}

void imprimeOrdem(Lista *L){

  Lista *elem;
   for(elem = L; elem!=NULL;elem=elem->prox){
       
    
        printf("%s\n%s\n%s\n%u\n%s\n",elem->nome,elem->num,elem->end,elem->cep,elem->dnas);
       
       }
 
    
}