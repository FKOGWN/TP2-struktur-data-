#include "header.h"

void createList(list *L){
	(*L).first= NULL;
}

int countElement(list L){
	int hasil=0;

	if(L.first!= NULL){
		/*list tidak kosong*/
		elemen *elmt;

		/*inisialisasi*/
		elmt= L.first;

		while(elmt !=NULL){
			/*proses*/
			hasil= hasil+1;

			/*iterasi*/
			elmt= elmt->next;
		}
	}

	return hasil;
}


void addFirst(char sinyal[], char kode[], list*L){
	elemen *baru;

	baru= (elemen *) malloc (sizeof (elemen));

	strcpy(baru->elmt.sinyal,sinyal);
	strcpy(baru->elmt.kode,kode);

	if((*L).first== NULL){
		baru->next= NULL;
	}else{
		baru->next= (*L).first;
	}

	(*L).first= baru;
	baru= NULL;
}

void addAfter(elemen *prev, char sinyal[], char kode[], list *L){
	elemen *baru;
	baru= (elemen *) malloc (sizeof (elemen));

	strcpy(baru-> elmt.sinyal, sinyal);
	strcpy(baru-> elmt.kode,kode);

	if(prev->next== NULL){
		baru->next= NULL;
	}else{
		baru->next= prev->next;
	}

	prev->next= baru;
	baru= NULL;
}

void addLast(char sinyal[], char kode[], list *L){
	if((*L).first== NULL){
		/*jika list adalah list kosong */
		addFirst(sinyal, kode, L);
	}else{
		/*jika list tidak kosong*/
		/*mencari elemen terakhir list*/
		elemen *prev= (*L).first;
		while(prev->next!= NULL){
			/*iterasi*/
			prev= prev->next;
		}
		addAfter(prev, sinyal, kode, L);
	}
}

void delFirst(list *L){
	if((*L).first!= NULL){
		/*jika list bukan list kosong*/
		elemen *hapus= (*L).first;
		if(countElement(*L)== 1){
			(*L).first= NULL;
		}else{
			(*L).first= (*L).first->next;
			hapus->next = NULL;
		}
		free(hapus);
	}
}

void delAfter(elemen *prev, list *L){
	elemen *hapus= prev->next;

	if(hapus!= NULL){
		if(hapus->next== NULL){
			prev->next= NULL;
		}else{
			prev->next= hapus->next;
			hapus->next= NULL;
		}
		free(hapus);
	}
}

void delLast(list *L){
	if((*L).first!= NULL){
		/*jika list tidak kosong*/
		if(countElement(*L)== 1){
			/*list terdiri dari satu elemen*/
			delFirst(L);
		}else{
			/*mencari elemen terakhir list*/
			elemen *last= (*L).first;
			elemen *prev;

			while(last->next != NULL){
				/*iterasi*/
				prev= last;
				last= last->next;
			}
			delAfter(prev, L);
		}
	}
}

void delAll(list *L){
	int i;
	for(i=countElement(*L); i>=1; i--){
		/*prosses menghapus elemen list*/
		delLast(L);
	}
}

void printElement(list L){
	int n=0;//variabel jumlah sinyal
	int i,j,k,l;//variabel iterasi
	int angka,huruf,fix,fix_h,fix_s,fix_t,filter=0,total=0;
	char jadi[100][50];
	if(L.first!= NULL){
		/*jika list tidak kosong*/
		/*inisialisasi*/
		elemen *elmt= L.first;
		n= 0;

		/*print sinyal yang diterima*/
		printf("==== Received Messages ====\n");
		while(elmt!= NULL){
			/*prosses*/
			printf("%s\n", elmt->elmt.sinyal);
			/*iterasi*/
			elmt= elmt->next;
			n++;
		}

		/*proses mencari pesan yang terfilter*/
		elmt=L.first;
		for(i=0; i<n; i++){
			angka=0,huruf=0,fix=0,k=0,l=0, fix_h=0,fix_s=0,fix_t=0;
			for(j=0; j<strlen(elmt->elmt.sinyal); j++){
				// mengecek apakah ada angka atau tidak
				if(elmt->elmt.sinyal[j]>='0' && elmt->elmt.sinyal[j]<='9'){
					angka++;
				}
			}
			// jika tidak ada angka maka proses akan dilanjut
			if(angka==0){
				for(j=0; j<strlen(elmt->elmt.sinyal); j++){
					// mengecek apakah huruf lebih dari lima atau tidak
					if((elmt->elmt.sinyal[j]>='a' && elmt->elmt.sinyal[j]<='z')
						|| (elmt->elmt.sinyal[j]>='A' && elmt->elmt.sinyal[j]<='Z')){
						huruf++;
						fix_h=1;
					}
					if(elmt->elmt.sinyal[j]>='-'){
						fix_s=1;
					}
					if(elmt->elmt.sinyal[j]>='.'){
						fix_t=1;
					}
				}
				fix=fix_h+fix_t+fix_s;
				// jika ada huruf,titik dan garis sesuai aturan
				// jika huruf tidak lebih dari lima maka lanjut
				if(huruf<=5 && fix==3){
					for(j=0; j<strlen(elmt->elmt.sinyal); j++){
						if((elmt->elmt.sinyal[j]>='a' && elmt->elmt.sinyal[j]<='z')
							|| (elmt->elmt.sinyal[j]>='A' && elmt->elmt.sinyal[j]<='Z')){								
							// elmt->elmt.sinyal[j]=jadi[k][l];
							printf("%c", elmt->elmt.sinyal[j]);
							l++;
						}
					}
					printf("\n");
					total++;
					k++;
				}else{
					// menambah filter karena huruf lebih dari lima
					filter++;
				}
			}else{
				// menambah filter karena mengandung angka
				filter++;
				delAfter(L.first, &L);
			}
			elmt= elmt->next;
		}


		/*print sinyal yang terfilter*/
		printf("==== Filtered Messages ====\n");
		printf("%d\n", filter);

		/*print kode yang disampaikan*/
		printf("=== Valid Messages List ===\n");
		printf("%d\n",total );
		// for(i=0; i<total; i++){
		// 	printf("%c\n", elmt->elmt.sinyal[i]);
		// }
	}else{
		/*proses jika list kosong*/
		printf("==== Received Messages ====\n");
		printf("No signal received.\n");
		printf("==== Filtered Messages ====\n");
		printf("0\n");
		printf("=== Valid Messages List ===\n");
		printf("Return to base immediately.\n");
	}
}

