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


void addFirst(char sinyal[], list*L){
	elemen *baru;

	baru= (elemen *) malloc (sizeof (elemen));

	strcpy(baru->elmt.sinyal,sinyal);

	if((*L).first== NULL){
		baru->next= NULL;
	}else{
		baru->next= (*L).first;
	}

	(*L).first= baru;
	baru= NULL;
}

void addAfter(elemen *prev, char sinyal[], list *L){
	elemen *baru;
	baru= (elemen *) malloc (sizeof (elemen));

	strcpy(baru-> elmt.sinyal, sinyal);

	if(prev->next== NULL){
		baru->next= NULL;
	}else{
		baru->next= prev->next;
	}

	prev->next= baru;
	baru= NULL;
}

void addLast(char sinyal[], list *L){
	if((*L).first== NULL){
		/*jika list adalah list kosong */
		addFirst(sinyal, L);
	}else{
		/*jika list tidak kosong*/
		/*mencari elemen terakhir list*/
		elemen *prev= (*L).first;
		while(prev->next!= NULL){
			/*iterasi*/
			prev= prev->next;
		}
		addAfter(prev, sinyal, L);
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

void abjad(char jadi[]) {
  int i, j; /* bikin i sama j buat looping */
  for (i=0; i<strlen(jadi); i++) { /* untuk setiap huruf di string */
    if (jadi[i]== '.' || jadi[i]== '-') { /* kalo huruf nya titik ato strip */
      for (j=i; j<strlen(jadi)-1; j++) { /* untuk setiap huruf di string dimulai dari posisi huruf yang titik ato strip */
        jadi[j]= jadi[j+1]; /* ganti huruf titik ato strip sama huruf setelahnya */
      }
      /* isi j bakal jadi panjang string yang udah dikurangi 1 */
      jadi[j] = '\0'; /* ganti karakter terakhir sama simbol terminator string */
      i= 0; /* reset i biar mulai lagi dari awal loop karakternya */
    }
  }
}

void printElement(list L){
	int n=0;//variabel jumlah sinyal
	int j,k,l;//variabel iterasi
	int angka,huruf,fix,fix_h,fix_s,fix_t,filter=0;
	char jadi[100];
	// char temp[100];
	if(L.first!= NULL){
		/*jika list tidak kosong*/
		/*inisialisasi*/
		elemen *elmt= L.first;
		elemen *prev= L.first;

		n= 0;

		/*print sinyal yang diterima*/
		printf("==== Received Messages ====\n");
		while(elmt!= NULL){
			/*prosses*/
			printf("%s\n", elmt->elmt.sinyal);
			/*iterasi*/
			elmt= elmt->next;
			// n++;
		}

		/*proses mencari pesan yang terfilter*/
		elmt=L.first;
		while(elmt!= NULL){
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
					strcpy(jadi,elmt->elmt.sinyal);
					abjad(jadi);
					strcpy(elmt->elmt.sinyal,jadi);
					// printf("%s\n", elmt->elmt.sinyal);
					// total++;
					// i++;	
				}else{
					// menambah filter karena huruf lebih dari lima
					if(elmt ==(L).first){
						delFirst(&L);
					}else{
						delAfter(prev, &L);
						elmt= prev;
					}
					filter++;
					// delAfter( &L);
				}
			}else{
				if(elmt ==(L).first){
					delFirst(&L);
				}else{
					delAfter(prev, &L);
					elmt= prev;
				}
				// menambah filter karena mengandung angka
				filter++;
				// delAfter(&L);
			}
			// printf("%s\n", elmt->elmt.sinyal );
			prev= elmt;
			elmt= elmt->next;
		}


		/*print sinyal yang terfilter*/
		printf("==== Filtered Messages ====\n");
		printf("%d\n", filter);

		/*print kode yang disampaikan*/
		printf("=== Valid Messages List ===\n");
		elmt= L.first;
		while(elmt!= NULL){
			printf("%s\n", elmt->elmt.sinyal);
			elmt= elmt->next;
		}
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

