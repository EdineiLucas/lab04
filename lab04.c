#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ULTIMO_BIT (sizeof(int) * 8-1)
#define INSOLUVEL (1<<ULTIMO_BIT)

typedef struct subconjuntos{
    int quant;
    int val;
}Subcnj;

int n, w, s=0, mask_solv = 0, ultimo_bit = ULTIMO_BIT;
Subcnj * w_linha;

int define_solucao(int subs_in, int posicao, int lista_negra){
    if(posicao >= w){
        if(lista_negra == s){
            return subs_in;
        }else{
            return INSOLUVEL;
        }
    }

    int sub_dentro0 = INSOLUVEL;
    int sub_dentro1 = INSOLUVEL;

    sub_dentro0 = define_solucao(subs_in, posicao+1, lista_negra);

    subs_in = subs_in | (1<<posicao);
    if((lista_negra & w_linha[posicao].val) == 0){
        lista_negra = lista_negra | w_linha[posicao].val;
        sub_dentro1 = define_solucao(subs_in, posicao+1, lista_negra);
    }

    if(sub_dentro0 != INSOLUVEL){
        return sub_dentro0;
    }else{
        return sub_dentro1;
    }
}

int quantos_zeros(int bit_mask){
    int count=0, last = ULTIMO_BIT;
    for(int i = 0; i<= last; ++i){
        if((bit_mask & (1<<i)) != 0){
            count ++;
        }
    }
    return count;
}

int main (){

    scanf("%d", &n);
    scanf("%d", &w);

    w_linha = calloc (w, sizeof(Subcnj)); 
    
    for(int i = 0; i < n; ++i){
        s = s | (1<<i);
    }

    for (int i = 0; i<w ; ++i){ 
        w_linha[i].val = 0;
    }

    for (int i = 0; i<w; ++i){
        scanf("%d", &w_linha[i].quant);
        for (int elementos = 0; elementos < w_linha[i].quant; ++elementos){ 
        int valor;
        scanf("%d", &valor);
        w_linha[i].val = w_linha[i].val | (1<<valor);
        }
    }

    mask_solv = define_solucao(0,0,0);


    if(mask_solv == INSOLUVEL){
        printf("Insoluvel");
    }else{
    printf("%d\n", quantos_zeros(mask_solv));

    for(int i = 0; i <= ultimo_bit; ++i){
        if((mask_solv & (1<<i)) != 0){
            printf("%d", w_linha[i].quant);
            for(int j = 0; j<= ultimo_bit; ++j){
                if ((w_linha[i].val & (1<<j)) !=0){
                    printf(" %d", j);
                }
                
            }
            printf("\n");
        }

    }
    }

    return 0;
}