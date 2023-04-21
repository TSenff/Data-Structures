#include <conjunto.h>



sset* init_sset(int size){
	sset *s = malloc(size)
	return ;
}
sset* sset_copia(sset *a);
sset* free_sset(int size);

int  sset_insere(sset *a, int i);
int  sset_remove(sset *a, int i);

sset* sset_uniao(int size);
sset* sset_interseccao(int size);
sset* sset_complemento(int size);

unsigned int sset_cardinalidade();

int sset_pertence(sset *a, int i);
int sset_contido(sset *a, sset *b);
int sset_vazio(sset *a);
int sset_identico(sset *a, sset *b);

void print(sset *a);

#endif
