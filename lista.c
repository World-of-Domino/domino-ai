#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PIECE_MAX 7
#define INF 1123

typedef struct _pecaDomino{
	int numberRight;
	int numberLeft;
	struct _pecaDomino *right;
	struct _pecaDomino *left;
}TppecaDomino;

TppecaDomino * new_list(){
	return NULL;
}

TppecaDomino * add_left(TppecaDomino * list_a, int numberRight, int numberLeft){
	TppecaDomino * new_piece = (TppecaDomino*)malloc(sizeof(TppecaDomino));
	new_piece->numberRight = numberRight;
	new_piece->numberLeft =  numberLeft;

	if(list_a == NULL){
		new_piece->right = NULL;
		new_piece->left = NULL;
		return new_piece;
	}

	new_piece->right = list_a;
	list_a->left = new_piece;
	new_piece->left = NULL;

	return new_piece;
}

TppecaDomino * add_right(TppecaDomino * list_a, int numberRight, int numberLeft){
	TppecaDomino * new_piece = (TppecaDomino*)malloc(sizeof(TppecaDomino));
	TppecaDomino * r;
	new_piece->numberRight = numberRight;
	new_piece->numberLeft = numberLeft;

	if(list_a == NULL){
		new_piece->right = NULL;
		new_piece->left = NULL;
		return new_piece;
	}

	for(r = list_a; r->right != NULL; r = r->right);

	r->right = new_piece;
	new_piece->left = r;
	new_piece->right = NULL;

	return list_a;
}

TppecaDomino * new_deck(){ //retorna uma lista com todas as peças do jogo
	int i, j;
	TppecaDomino * deck = new_list();

	for(i = 0; i <= 6; i++){
		for(j = 0; j <= i; j++){
			deck = add_left(deck, i, j);
		}
	}

	return deck;
}

void print_deck(TppecaDomino * deck){
	TppecaDomino * p;

	if(deck == NULL){
		printf("\n");
		return;
	}

	for(p = deck; p != NULL; p = p->right){
		printf(" [%d|%d] ", p->numberLeft, p->numberRight);
	}
	printf("\n");
}

int deck_size(TppecaDomino * list_a){
	int i;
	TppecaDomino * q;
	if(list_a == NULL) return 0;

	for(i = 0, q = list_a; q != NULL; q = q->right){
		i++;
	}

	return i;
}

int number_is_in(int * freq_rank, int number){//função utilizada na função frequency_rank
	//verifica se um determinado número está contido em um vetor
	int i;

	for(i = 0; i < PIECE_MAX; i++){
		if(number == freq_rank[i]) return 1;
	}
	return 0;
}

int * frequency_rank(TppecaDomino * list_a){
	//retorna um vetor com os números ordenados
	//em ordem crescente de incidência
	
	TppecaDomino * p;
	int i, j;
	int minval, minind;

	int * freq = (int*)malloc(PIECE_MAX * sizeof(int));
	//vetor com a frequência de cada número
	
	int * freq_rank = (int*)malloc(PIECE_MAX * sizeof(int));
	//vetor com a ordem decrescente de inciência
	
	memset(freq, 0, PIECE_MAX * sizeof(int));
	memset(freq_rank, -1, PIECE_MAX * sizeof(int));

	if(list_a == NULL){
		for(i = 0; i < PIECE_MAX; i++){
			freq[i] = i;
		}
		return freq;
	}

	for(p = list_a; p != NULL; p = p->right){
		if(p->numberLeft == p->numberRight){
			freq[p->numberLeft]++;
		}
		else{
			freq[p->numberLeft]++;
			freq[p->numberRight]++;
		}
	}

	for(i = 0; i < PIECE_MAX; i++){
		for(j = 0; j < PIECE_MAX; j++){
			minval = INF;
			if(!number_is_in(freq_rank, j) && freq[j] < minval){
				minval = freq[j];
				minind = j;
			}
			freq_rank[i] = minind;
		}
	}

	return freq_rank;
}

int main(void){
	TppecaDomino * a = new_deck();
	int * freq_rank = (int*)malloc(PIECE_MAX * sizeof(int));
	int i;

	print_deck(a);

	freq_rank = frequency_rank(a);

	for(i = 0; i < PIECE_MAX; i++){
		printf("%d ", freq_rank[i]);
	}
	printf("\n");


	for(i = 0; i < 123; i++){
		a = add_left(a, 3, 3);
	}
	print_deck(a);

	freq_rank = frequency_rank(a);

	for(i = 0; i < PIECE_MAX; i++){
		printf("%d ", freq_rank[i]);
	}
	printf("\n");

	return 0;
}
