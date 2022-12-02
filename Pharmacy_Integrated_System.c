#include <stdio.h>		// Penggunaan library stdio untuk input dan output
#include <stdlib.h>		// Penggunaan library stdlib untuk memory allocation
#include <string.h>		// Penggunaan library string untuk function string compare

// Struct dengan tipe jenis Medicine untuk menyimpan data obat-obatan
typedef struct{
	char name[50];	// variabel nama dengan maksimal 50 karakter
	int quantity;	// jumlah obat yang tersedia
	int dayExp;		// tanggal expired obat
	int monthExp;	// bulan expired obat
	int yearExp;	// tahun expired obat
	int num;		// variabel untuk melihat banyaknya data obat yang diinput
	int update;		// variabel update untuk melihat kondisi mengupdate obat atau menambah
	int much;		// variable much untuk index banyaknya obat yang dibeli
	
	// Struct request untuk merequest obat
	struct{
		char name[50];	// variable name untuk menyimpan data yang direquest user
		char jenis[50];	// variable jenis untuk menentukan jenis obat yang direquest
		char desc[50];	// variable desc untuk menambah deskripsi sebuah pesan
	}Request;
	
	// Struct buy untuk obat yang dibeli
	struct{
		char name[50]; 	// variable name untuk menyimpan data yang dibeli
		int quantity;	// variable quantity untuk menyimpan jumlah obat yang dibeli tiap jenisnya
		double price;	// variable untuk menyimpan harga
	}Buy;
}Medicine;

// Struct dengan tipe jenis data Patient untuk menyimpan data terkait pasien
typedef struct{
	char name[50];		// variable name untuk menyimpan nama user
	int age;			// variable age untuk menyimpan umur
	char birthDate[10];	// variable untuk menyimpan tanggal lahir
}Patient;

// Prototype Start untuk menampilkan opening program
void start();
// Prototype login sebagai admin atau user
int login();
// Prototype menu untuk menampilkan menu pelanggan
int menuPelanggan(Patient *user, Medicine *med);
// Prototype menu untuk menampilkan menu admin
int menuAdmin(Patient *user, Medicine *med);
// Prototype untuk menampilkan daftar obat yang tersedia
void showDrugs(Medicine *med);
// Prototype untuk menambah obat
void addDrugs(Medicine *med);
//Prototype untuk mengupdate data obat
void updateDrugs(Medicine *med);
// Prototype untuk mencari list obat
int findDrugs(Medicine *med, char name[]);
//prototype func untuk menggunakan angka random untuk tempat parkir
int rand();
// Prototype untuk membantu user memahami aplikasi
void help();
// Prototype untuk melihat struk belanja
void showStruk(Medicine *med);
// Prototype untuk melihat database user
void account(Patient *user, Medicine *med);
// Prototype untuk membeli obat
void buyDrugs(Medicine *med);
// Prototype merequest obat
void reqDrugs(Medicine *med);
// Prototype mencari obat 
void showDrugsByName(Medicine *med);

// func main sebagai func utama jalannya program 
int main(){
	Medicine *med;		// Menggunkana struct by pointer untuk Medicine dan Patient
	Patient *user;
	int access, back;	
	
	//untuk mengalokasikan ruang sesuai dengan jumlah alokasi memori yang digunakan
	med = (Medicine*) calloc (15, sizeof(Medicine));
	user = (Patient*) calloc (15, sizeof(Patient));
	med->update = -1;
	med->num = 0;
	
	//untuk memberikan informasi jika memory untuk pointer tidak tercukupi
	if(med == NULL || user == NULL){
		printf("Error! Memory Not Allocated");
		exit(0);
	}
	
	// Memulai program dengan menampilkan opening start 
//	Start();

	// Untuk kembali ke menu login sebagai admin atau pelanggan 
	do{
		// Memanggil func Login untuk menentukan sebagai admin atau pelanggan
		access = login();
		
		// Akses ke menu sebagai admin atau pelanggan
		if (access == 1){
			back = menuAdmin(user, med);
		} else{
			back = menuPelanggan(user, med);
		}
	} while (back==1);
	
	// Closing Program
	printf("Terima kasih telah menggunakan program pharmacy center\n\n");
	
	// membersihkan memori dynamic yang digunakan
	free(med);
	free(user);
	return 0;
}

// Func Start sebagai function opening yang akan muncul saat pertama kali program dijalankan
void start(){
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
int login(){
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
	
	system("pause"); system("cls");
	return access;
}

// Function ketika user berhasil login sebagai admin
int menuAdmin(Patient *user, Medicine *med){
	int choice, back;
	
	// masuk ke menu admin dan memilih input
	do{
		retry :
		printf("Menu Admin : \n");
		printf("1. List Obat \n");
		printf("2. Tambah Obat \n");
		printf("3. Update Obat \n");
		printf("4. Kembali ke menu login\n");
		printf("5. Exit Program \n");
		printf("Masukkan pilihan : ");
		scanf("%d", &choice);		// input fitur yang ingin digunakan 
	
		switch(choice){
			case 1:	// input 1 untuk melihat list obat
				showDrugs(med);
				system("pause"); system("cls");
				break;
			case 2:	// input 2 untuk menambah obat baru
				med->update = -1;	// update di setting ke -1 untuk menambah index baru
				addDrugs(med);
				break;
			case 3:	// input 3 untuk mengupdate obat sesuai list yang dipilih
				updateDrugs(med); 
				break;
			case 4:	// kembali ke menu login
				back = 1;	// back diset ke 1 sehingga akan mereturn 1 dan kembali ke menu login
				break;
			case 5:	// keluar dari program
				back = 0;	// back diset ke 1 sehingga akan mereturn 1 dan kembali ke menu login
				break;
			default:
				system("color 74");
				printf("Masukkan input yang sesuai! \n");
				Sleep(2000); system("CLS"); 
		        system("color 07");
		        goto retry;
		        break;
		}
	} while(choice!=4 && choice!=5);
	
	system("pause"); system("cls");
	return back;
}

// Funtion saat user berhasil masuk kedalam account pelanggan
int menuPelanggan(Patient *user, Medicine *med){
	int choice, back;
	char temp[50];	//menyimpan input nama obat sementara
	
	// input database user
	printf("Masukkan nama anda : ");
	scanf(" %49[^\n]s", &user->name);
	printf("Tanggal lahir anda : ");
	scanf(" %20[^\n]s", &user->birthDate);
	printf("Umur anda saat ini : ");
	scanf("%d", &user->age);
	system("pause"); system("cls");
	
	// Menu pelanggan dan meminta input
	do{
		retry :
		printf("Menu Pelanggan : \n");
		printf("1. Lihat Obat yang tersedia \n");
		printf("2. Request Obat \n");
		printf("3. Beli obat \n");
		printf("4. Cari nama obat yang tersedia \n");
		printf("5. Informasi akun \n");
		printf("6. Helpdesk \n");
		printf("7. Kembali ke menu login\n");
		printf("8. Exit Program \n");
		printf("Masukkan pilihan : ");
		scanf("%d", &choice);		// meminta pilihan fitur
		
		system("pause"); system("cls");
		
		// switch case input
		switch(choice){
			case 1:	// input 1 untuk melihat data obat
				showDrugs(med);
				system("pause"); system("cls");
				break;
			case 2:	// input 2 untuk merequest obat
				reqDrugs(med);
				break;
			case 3:	// input 3 untuk membeli obat
				buyDrugs(med); 
				break;
			case 4:	// input 4 untuk melihat data yang dicari
				printf("Nama obat yang ingin anda cari : ");
				scanf(" %49[^\n]s", &temp);
				findDrugs(med, temp);
				showDrugsByName(med);
				break;
			case 5:	// input 5 untuk melihat database account dan obat yang dibeli
				account(user, med);
				break;
			case 6:	// input 6 melihat helpdesk
				help();
				break;
			case 7:	// kembali ke menu login
				back = 1;
				break;
			case 8 :	// keluar program
				break;
			default:	// jika input tidak sesuai di pilihan
				system("color 74");
				printf("Masukkan input yang sesuai! \n");
				Sleep(2000); system("CLS"); 
		        system("color 07");
		        goto retry;
		        break;
		}
	} while(choice!=8 && choice!=7);
	
	system("pause"); system("cls");
	return back;
}

// function help untuk membantu user ketika tidak memahami penggunaan program
void help(){
	printf("SELAMAT DATANG DI APLIKASI ONLINE PHARMACY \n\n");
	printf("Mari kami bantu untuk bagaimana menggunakan aplikasi ini\n");
	printf("Pada bagian menu terdapat option 1 hingga 7 terdapat beberapa fitur yaitu : \n");
	printf("Opsi 1 : untuk melihat seluruh database obat yang terdapat pada sistem \n");
	printf("Opsi 2 : untuk merequest obat yang belum tersedia pada sistem \n");
	printf("Opsi 3 : untuk melakukan pembelian obat yang tersedia pada sistem \n");
	printf("Opsi 4 : untuk melakukan pencarian obat yang ingin anda cari\n");
	printf("Opsi 5 : untuk meanpilkan database pengguna serta struk belanja dari data yang telah diinput user\n");
	printf("Opsi 6 : untuk melihat helpdesk maupun bantuan dari tata cara penggunaan aplikasi ini \n");
	printf("Opsi 7 : kembali ke menu login\n");
	printf("Opsi 8 : untuk keluar dari aplikasi kami \n");
	printf("\nSelain opsi tersebut, program akan melooping hingga user menginput opsi yang sesuai\n\n");
	
	system("pause"); system("cls");
}

// Funtion menampilkan database user serta obat yang dibeli
void account(Patient *user, Medicine *med){
	printf("Nama : %s\n", user->name);
	printf("TTL  : %s\n", user->birthDate);
	printf("Umur : %d\n\n", user->age);
	printf("List obat yang anda beli adalah :\n");
	showStruk(med);		// Memanggil func showStruk untuk melihat data obat yang dibeli
}

// Function untuk menampilkan struk pembelian
void showStruk(Medicine *med){
	int i;
	float totalPrice = 0;	// variabel menunjukkan total harga dari obat yang dibeli
	
	// Jika belum ada obat yang dibeli maka akan memberikan informasi belum membeli obat apapun
	if(med->much < 0){
		printf("Anda belum membeli obat apapun\n\n");
	} else{		// Jika terdapat obat yang dibeli akan menampilkan struk belanja
		printf("Nama obat \t Jumlah Obat \t Total Harga\n");
		printf("\n============================================\n");
		for(i=0; i<med->much; i++){	// mengeprint data obat yang dibeli
			printf("%s \t %d \t\t %.0lf \n", (med + i)->Buy.name, (med + i)->Buy.quantity, (med + i)->Buy.price);
			totalPrice += (med + i)->Buy.price;
		}
		printf("\n============================================\n");
		printf("Total Harga : %.0lf\n", totalPrice);
		printf("============================================\n");
	}
	
	system("pause"); system("cls");
}

// Funtion untuk membeli sebuah obat
void buyDrugs(Medicine *med){
	char name[50];					// Variabel name untuk menyimpan sementara nama obat yang ingin dibeli
	int loop = 0, accBuy;	// variabel untuk melakuakn confirm buying serta index obat yang dibeli
	double priceTemp;				// variabel sementara untuk menyimpan total harga obat yang dibeli
	
	// Jika terdapat obat dalam database
	if(med->num > 0){
		// looping selama obat yang dicari tidak tersedia
		do{
			printf("OBAT YANG TERSEDIA\n\n");
			showDrugs(med);		// Menampilkan seluruh obat dalam database
			
			// Input obat
			printf("\nSilahkan masukkan nama obat yang ingin anda beli : ");
			scanf(" %49[^\n]s", &name);
			findDrugs(med, name);		// Mencari obat yang ingin dibeli
			if(med->update == -1){		// Jika tidak terdapat dalam database maka akan melooping
				printf("Obat tidak tersedia, silahkan masukkan obat yang lain! ");
				loop = 1;
				system("pause"); system("cls");
			} else{						// Jika tersedia dalam database akan lanjut menginput data
				strcpy((med + med->much)->Buy.name, name);		// Mengcopy nama obat yang ingin dibeli
				printf("harga tiap satuan obat adalah : %.0lf\n", (med + med->much)->Buy.price);	// Menunjukkan harga satuan obat
				printf("Berapa kuantitas obat yang ingin anda pesan : ");
				scanf("%d", &(med + med->much)->Buy.quantity);		// Input jumlah obat yang ingin dibeli
				priceTemp = (med + med->much)->Buy.price * (med + med->much)->Buy.quantity;		// Total harga obat
				printf("Total harga menjadi : %.0lf\n\n", priceTemp);	// Show total price
				backConfirm:	// kembali ke menu ini jika pembelian tidak terkonfirmasi
				printf("Konfirmasi pembelian (1=yes, 2=no) : ");
				scanf("%d", &accBuy);
				if(accBuy == 1){	// Jika berhasil konfirmasi pembelian maka success
					loop =0;
					(med + med->much)->quantity -= (med + med->much)->Buy.quantity; // Mengurangi jumlah obat dalam database
					med->much++;	// Menambah index, untuk pembelian selanjutnya
					printf("\n\nSUCCESS TO BUY THE DRUGS\n\n");
					(med + med->much)->Buy.price = priceTemp;	// Mengubah data price menjadi total harga obat yang dibeli
				} else if(accBuy == 2){	// Jika gagal konfirmasi kembali looping
					printf("\n\nFailed to buy the drugs\n\n");
					system("pause"); system("cls");
					loop = 1;
				} else{		// Jika input tidak sesuai back to backConfirm goto
					printf("Harap menginput 1=yes atau 2=no\n");
					goto backConfirm;
				}
				
			}
		} while(loop == 1);
	} else{
		printf("Belum terdapat obat apapun dalam database\n\n");
	}
	
	system("pause"); system("cls");
}

// Function untuk merequest obat yang tidak tersedia
void reqDrugs(Medicine *med){
	printf("Masukkan nama obat yang ingin di request : ");
	scanf(" %49[^\n]s", med->Request.name);
	printf("Jenis obat yang di request : ");
	scanf(" %49[^\n]s", med->Request.jenis);
	printf("Deskripsi obat : ");
	scanf(" %49[^\n]s", med->Request.desc);
	
	printf("\nSUCCESS TO REQUEST A DRUG\n\n");
	
	system("pause"); system("cls");
}

// Funtion untuk melihat seluruh data obat yang tersedia
void showDrugs(Medicine *med){
	int i;
	
	// jika tidak terdapat obat dalam database
	if(med->num <1){
		printf("Belum ada obat yang ditambahkan!\n");
	} else{	// jika terdapat obat dalam database
		printf("No. \t\t Name \t\t Quantity \t\t Expired\n");
		for(i=0; i<med->num; i++){
			printf("%d \t\t %s \t\t %d \t\t %d-%d-%d\n", i+1, (med + i)->name, (med + i)->quantity, (med + i)->dayExp, (med + i)->monthExp, (med + i)->yearExp);
		}
	}
}

// Function untuk melihat obat yang di cari pada fiture search
void showDrugsByName(Medicine *med){
	int i;
	
	// Jika obat tidak terdapat pada database (-1) maka akan menampilkan informasi bahwa tidak ada obat yang dicari, sebaliknya (!=-1) akan memberikan informasi tersedia
	if(med->update == -1){
		printf("\nObat yang anda cari belum tersedia, silahkan menginput request obat\n\n");
	}else{
		printf("\nObat yang anda cari tersedia!!\n\n");
		printf("No. \t\t Name \t\t Quantity \t\t Expired\n");
		printf("%d \t\t %s \t\t %d \t\t %d-%d-%d\n", i+1, (med + med->update)->name, (med + med->update)->quantity, 
													(med + med->update)->dayExp, (med + med->update)->monthExp, (med + med->update)->yearExp);
	}
	
	system("pause"); system("CLS"); 
}

// Function untuk menambah obat
void addDrugs(Medicine *med){
	int i, temp;
	
	// Mengecek apakah func dipanggil untuk update (!=-1) atau dipanggil saat ingin menambah obat baru (-1)
	if(med->update == -1){
		temp = med->num;	// Jika menambah obat baru, maka index yang digunakan merupakan index list obat baru dan disimpan ke variabel temp
		med->num++;			// Index akan diincrement
	} else{
		temp = med->update;	// Jika merupakan update, maka akan mendapat index dari obat yang ingin di update
	}
	
	// Input data obat
	printf("\nMasukkan nama obat : ");
	scanf(" %49[^\n]s", &(med + temp)->name);	// Input nama obat,  %49[^\n]s berarti dapat menginput string meskipun terdapat space dan maksimal 49 character
	printf("Kuantitas obat : ");
	scanf("%d", &(med + temp)->quantity);		// Input jumlah obat
	printf("Tanggal expired (day month year) : ");
	scanf("%d %d %d", &(med + temp)->dayExp, &(med + temp)->monthExp, &(med + temp)->yearExp);		// Input tanggal expired obat
	(med + temp)->Buy.price = (rand() % 40 + 7) * 1000; //Masukkan harga obat dengan minimal 7 ribu dan maksimal 40000
	
	printf("\nSuccess to add the drugs!\n");
	system("pause"); system("cls");
}

// Funtion untuk mengupdate database obat
void updateDrugs(Medicine *med){
	int i, acc;
	char temp[50];
	
	// menginput nama obat yang ingin diupdate
	printf("Masukkan nama obat : ");
	scanf(" %49[^\n]s", &temp);
	acc = findDrugs(med, temp);	// menentukan apakah nama obat ada di database atau tidak
	if (acc != -1){	// jika ada akan diupdate
		printf("\nWe found in the database\nUPDATE DATABASE\n\n");
		addDrugs(med);
	} else{			// jika tidak ada maka tidak terjadi di update
		printf("\nObat tidak ditemukan\n\n");
		system("pause"); system("cls");
	}
}

// Funtion utnk mencari obat yang tersedia pada database
int findDrugs(Medicine *med, char name[]){
	int i, acc;
	
	// mencari tiap index nama yang ada di database
	for(i=0; i<med->num; i++){
		if(strcmp((med + i)->name, name) == 0){	// jika input nama sesaui dalam database akan mengupdate index ke med->update
			acc = 1;	// mensetting acc menjadi 1 sehingga akan terjaid kondisi update pada addDrugs
			med->update = i;	// update index yang akan di update
			break;
		} else{	// jika input nama tidak ditemukan maka akan mensetting acc -1 dan update -1 sehingga tidak terjadi kondisi upadte
			printf("ERROR %d\n", i);
			acc = -1;
			med->update = -1;
		}
	}
	
	return acc;
}
