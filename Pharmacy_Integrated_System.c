#include <stdio.h>		// Penggunaan library stdio untuk input dan output
#include <stdlib.h>		// Penggunaan library stdlib untuk memory allocation
#include <string.h>		// Penggunaan library string untuk function string compare

// Struct dengan tipe jenis Medicine untuk menyimpan data obat-obatan
typedef struct{
	char name[20];
	int quantity;
	int dayExp;
	int monthExp;
	int yearExp;
	int num;
}Medicine;

// Struct dengan tipe jenis data Patient untuk menyimpan data terkait pasien
typedef struct{
	char name[20];
	int age;
	char birthDate[10];
}Patient;

// Prototype Start untuk menampilkan opening program
void Start();
// Prototype login sebagai admin atau user
int Login();
// Prototype menu untuk menampilkan menu pelanggan
void MenuPelanggan();
// Prototype menu untuk menampilkan menu admin
void MenuAdmin();

// func main sebagai func utama jalannya program 
int main(){
	Medicine *med;
	Patient *user;
	int access;
	
	//untuk mengalokasikan ruang sesuai dengan jumlah alokasi memori yang digunakan
	med = (Medicine*) calloc (15, sizeof(Medicine));
	user = (Patient*) calloc (15, sizeof(Patient));
	//untuk memberikan informasi jika memory untuk pointer tidak tercukupi
	if(med == NULL || user == NULL){
		printf("Error! Memory Not Allocated");
		exit(0);
	}
	
	// Memulai program dengan menampilkan opening start 
//	Start();
	// Memanggil func Login untuk menentukan sebagai admin atau pelanggan
	access = Login();
	
	// Akses ke menu sebagai admin atau pelanggan
	if (access == 1){
		MenuAdmin(user, med);
	} else{
		MenuPelanggan(user, med);
	}
	
	// membersihkan memori dynamic yang digunakan
	free(med);
	free(user);
	return 0;
}

// Func Start sebagai function opening yang akan muncul saat pertama kali program dijalankan
void Start(){
	int i; 				// deklarasi variabel integer

	printf("!--- Untuk Interface Maksimal Silakan Full Screen Lalu Tekan ENTER ---!");
	getchar();			// memanggil function getchar
	system("CLS");		// Membersihkan layar
	Sleep(800);			// menjeda program selama 0.8 detik

	// mengeprint opening
	printf("\n\n\n\n\n\n\n");
	char a[] = {"\t\t\t\t\t\t\t\t\t\t=================================================\n"
				"\t\t\t\t\t\t\t\t\t\t|--------- Selamat Datang  Di Aplikasi ---------|\n"
				"\t\t\t\t\t\t\t\t\t\t|---------  Phamacy System Integrated  ----------|\n"
				"\t\t\t\t\t\t\t\t\t\t|-----------  Pemrograman Lanjut 01  -----------|\n"
				"\t\t\t\t\t\t\t\t\t\t=================================================\n"
				"\t\t\t\t\t\t\t\t\t\t|               This app made by :              |\n"
				"\t\t\t\t\t\t\t\t\t\t|  1. Ariq   			//NPM					 |\n"
				"\t\t\t\t\t\t\t\t\t\t|  2. Callula   		//NPM 				     |\n"
				"\t\t\t\t\t\t\t\t\t\t=================================================\n\n"};

	for (i = 0; a[i] != a[828]; i++)
	{
		printf("%c", a[i]);
		Sleep(2);
	}

	printf("\t\t\t\t\t\t\t\t\t\t\t\t   Loading... \n\n");
	printf("\a");
	Sleep(1000); 				// menjeda program selama 1 detik

	for (i = 1; i <= 211; i++)
	{
		printf("%c", 223); 		// 233 adalah kode KARAKTER beta di dalam ASCII2
		if (i == 70 || i == 140)
			Sleep(500); 		// menjeda program selama 0.5 detik
		Sleep(12);
	}
	Sleep(1600);   				// menjeda program selama 1.6 detik
	system("CLS"); 				// Membersihkan layar
}

// Function login untuk access user sebagai admin atau pelanggan
int Login(){
	int access;						// Variabel access untuk mereturn jenis user (pelanggan = 2, admin = 1)
	char admin[] = "admin";			// Username admin
	char adminPass[] = "admin";		// Password admin
	char username[6], password[6];	// Array string 
	char retry;						// Char retry untuk melakukan relogin ketika login ke admin gagal
	
	do{
		printf("Silahkan masukkan access account : \n");
		printf("1. Admin \n2. Pelanggan \nMasukkan akses : ");
		scanf("%d", &access);									// Meminta access login
		printf("\n");
		
		if(access == 1){			// Jika user memilih akses 
			relog:					// relog akan digunakan ketika user melakukan relogin 
			printf("Username : ");	
			scanf("%s", &username);
			printf("Password : ");
			scanf("%s", &password);
			if (strcmp(username, admin) == 0 && strcmp(password, adminPass) == 0){	// Membandingkan usernam serta password apakaah cocok dengan admin
				access = 1;
				printf("LOGIN AS ADMIN SUCCESS\n");		// Jika berhasil maka akan login ke dalam akses admin
			}else{
				printf("\n\nLOGIN FAILED!!!\n");		// Jika gagal akan menanyakan untuk relogin 
				printf("R untuk Relogin, P untuk akses Pelanggan : ");
				scanf("%s", &retry);
				if(retry == 'R' || retry == 'r'){		// Jika relogin akan kembali ke goto relog
					system("CLS");
					goto relog;
				} else{									// Jika menginput P maka akan login ke akses pelanggan
					goto logPelanggan;
				}
			} 
		} else if (access == 2){						// Jika masuk ke akses pelanggan
			logPelanggan:
			access = 2;
		} else{
			system("color 74");
			printf("Pilihan tidak tersedia, Pilih access sebagai admin atau pelanggan!\n");
			Sleep(2000); system("CLS"); 
	        system("color 07");
			access = 3;
		}
	} while(access < 1 || access > 2);
	
	return access;
}

void MenuAdmin(Patient *user, Medicine *med){
	int choice;
	
	retry :
	printf("Menu Admin : \n");
	printf("1. List Obat \n");
	printf("2. Tambah Obat \n");
	printf("3. Hapus Obat \n");
	printf("4. Update Obat \n");
	printf("Masukkan pilihan : ");
	scanf("%d", &choice);
	
	switch(choice){
		case 1:
			ShowDrugs(med);
			break;
		case 2:
			AddDrugs(med);
			break;
		case 3:
			RemoveDrugs(med); 
			break;
		case 4:
			UpdateDrugs(med);
			break;
		default:
			system("color 74");
			printf("Masukkan input yang sesuai! \n");
			Sleep(2000); system("CLS"); 
	        system("color 07");
	        break;
	        goto retry;
	}
}

void MenuPelanggan(Patient *user, Medicine *med){
	int choice;
	
	
}

void ShowDrugs(Medicine *med){
	int i;
	
	if(med->num <1){
		printf("Belum ada obat yang ditambahkan!\n");
	} else{
		printf("No. \t\t Name \t\t Quantity \t\t Expired");
		for(i=0; i<med->num; i++){
			printf("%d \t\t %s \t\t %d \t\t %d-%d-%d", i+1, med->name, med->quantity, med->dayExp, med->monthExp, med->yearExp);
		}
	}
	
	Sleep(2000); system("CLS"); 
}

void AddDrugs(Medicine *med){
	int i;
	
}
