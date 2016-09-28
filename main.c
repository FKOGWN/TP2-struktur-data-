 #include "header.h"

int main(){
	char input[100];//variabel iteriasi
	list L;//deklarasi list L
	createList(&L);//membuat list

	scanf("%s", input);	
	while(strcmp(input,"DONE")!=0){
		if(strcmp(input,"DONE")!=0){
			addLast(input, "def", &L);
		}
		scanf("%s", input);
	}

	printElement(L);


	return 0;
}
