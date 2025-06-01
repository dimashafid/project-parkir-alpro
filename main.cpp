#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;


const int maxMobil = 30;
const int maxMotor = 50;
int jumlahMobil = 0;
int jumlahMotor = 0;

struct Waktu {
    int jam;
    int menit;
};

struct Kendaraan {
    string nomor_plat;
    string jenis_kend;
    Waktu waktu_masuk;
    Waktu waktu_keluar;
    string status;
    int tarif;
};

Kendaraan kendaraan[100];

struct Akun {
    string username;
    string password;
};

const int maxUser = 30;
int user = 3;

Akun pengguna[maxUser] = {
    {"Dimas", "Hafid"},
    {"Mufid", "Dhamarjati"},
    {"admin", "admin"}
};

string namafile;
int jumlahdata;
int totalData = 0;


void tambahData() {
    if (namafile.empty()) return;
    system("cls");
    cout << "INPUT DATA KENDARAAN\n";
    cout << "File: " << namafile << endl;
    cout << "Jumlah kendaraan yang masuk: ";
    cin >> jumlahdata;
    cin.ignore();

    fstream file(namafile.c_str(), ios::app);
    if (file.is_open()) {
        for (int i = 0; i < jumlahdata; i++) {
            cout << "\nKendaraan ke - " << i + 1 << endl;
            cout << "Nomor Plat\t\t\t: ";
            getline(cin, kendaraan[totalData].nomor_plat);
            cout << "Jenis Kendaraan (mobil/motor)\t: ";
            getline(cin, kendaraan[totalData].jenis_kend);

            if (kendaraan[totalData].jenis_kend == "mobil") {
                if (jumlahMobil >= maxMobil) {
                    cout << "Slot mobil penuh! Data mobil ini tidak dapat ditambahkan.\n";
                    continue; 
                }
                jumlahMobil++;
            } else if (kendaraan[totalData].jenis_kend == "motor") {
                if (jumlahMotor >= maxMotor) {
                    cout << "Slot motor penuh! Data motor ini tidak dapat ditambahkan.\n";
                    continue; 
                }
                jumlahMotor++;
            } else {
                cout << "Jenis kendaraan tidak dikenali! Data kendaraan ini tidak dapat ditambahkan.\n";
                continue; 
            }

            bool waktuMasukValid = false;
            do {
                cout << "Waktu Masuk (jam menit)\t\t: ";
                cin >> kendaraan[totalData].waktu_masuk.jam;
                cin >> kendaraan[totalData].waktu_masuk.menit;
                cin.ignore(); 

                if (kendaraan[totalData].waktu_masuk.jam >= 0 && kendaraan[totalData].waktu_masuk.jam <= 23 &&
                    kendaraan[totalData].waktu_masuk.menit >= 0 && kendaraan[totalData].waktu_masuk.menit <= 59) {
                    waktuMasukValid = true;
                } else {
                    cout << "Input waktu tidak valid! Jam harus antara 0-23 dan menit 0-59.\n";
                }
            } while (!waktuMasukValid);

            kendaraan[totalData].waktu_keluar.jam = 0;
            kendaraan[totalData].waktu_keluar.menit = 0;
            kendaraan[totalData].tarif = 0;
            kendaraan[totalData].status = "ada";

            file << kendaraan[totalData].nomor_plat << endl;
            file << kendaraan[totalData].jenis_kend << endl;
            file << kendaraan[totalData].waktu_masuk.jam << " " << kendaraan[totalData].waktu_masuk.menit << endl; 
            file << kendaraan[totalData].waktu_keluar.jam << " " << kendaraan[totalData].waktu_keluar.menit << endl; 
            file << kendaraan[totalData].tarif << endl;
            file << kendaraan[totalData].status << endl;

            totalData++;
            cout << endl;
        }
        file.close();
        cout << "Data kendaraan berhasil ditambahkan!\n";
    } else {
        cout << "File gagal dibuka!\n"; 
    }
    system("PAUSE");
}


void showData() {
    cout << "Data Kendaraan:\n";
    for (int i = 0; i < totalData; i++) {
        cout << "Kendaraan [" << i + 1 << "]\n";
        cout << "Nomor Plat      : " << kendaraan[i].nomor_plat << endl;
        cout << "Jenis Kendaraan : " << kendaraan[i].jenis_kend << endl;
        cout << "Waktu Masuk     : " << kendaraan[i].waktu_masuk.jam << ":" << kendaraan[i].waktu_masuk.menit << endl;
        cout << "Waktu Keluar    : " << kendaraan[i].waktu_keluar.jam << ":" << kendaraan[i].waktu_keluar.menit << endl;
        cout << "Tarif           : " << kendaraan[i].tarif  << endl;
        cout << "Status          : " << kendaraan[i].status << endl << endl;
    }
    cout << "Slot Tersisa Mobil: " << maxMobil - jumlahMobil << endl;
    cout << "Slot Tersisa Motor: " << maxMotor - jumlahMotor << endl;
}


void kendaraanKeluar() {
    system("cls");
    cout << "DAFTAR KENDARAAN SAAT INI:\n";
    showData(); 
    cout << "\n===========================================\n";

    int pilihanCari;
    cout << "Pilih metode pencarian kendaraan keluar:\n";
    cout << "[1] Berdasarkan Nomor Plat\n";
    cout << "[2] Berdasarkan Nomor Urut Data\n";
    cout << "Pilihan: ";
    cin >> pilihanCari;
    cin.ignore(); 

    int indexCari = -1; 

    if (pilihanCari == 1) {
        string platCari;
        cout << "Nomor plat kendaraan yang keluar: ";
        getline(cin, platCari);

        for (int i = 0; i < totalData; i++) {
            if (kendaraan[i].nomor_plat == platCari && kendaraan[i].status == "ada") {
                indexCari = i;
                break;
            }
        }
    } else if (pilihanCari == 2) {
        int nomorUrut;
        cout << "Masukkan Nomor Urut Data Kendaraan (dari daftar di atas): ";
        cin >> nomorUrut;
        cin.ignore();

        if (nomorUrut > 0 && nomorUrut <= totalData) {
            if (kendaraan[nomorUrut - 1].status == "ada") {
                indexCari = nomorUrut - 1;
            } else {
                cout << "Kendaraan pada nomor urut tersebut sudah keluar.\n";
            }
        } else {
            cout << "Nomor urut data tidak valid.\n";
        }
    } else {
        cout << "Pilihan metode pencarian tidak valid.\n";
        system("PAUSE");
        return; 
    }

    if (indexCari != -1) {
        bool waktuKeluarValid = false;
        do {
            cout << "Masukkan Waktu Keluar (jam menit): ";
            cin >> kendaraan[indexCari].waktu_keluar.jam >> kendaraan[indexCari].waktu_keluar.menit;
            cin.ignore(); 

            if (kendaraan[indexCari].waktu_keluar.jam >= 0 && kendaraan[indexCari].waktu_keluar.jam <= 23 &&
                kendaraan[indexCari].waktu_keluar.menit >= 0 && kendaraan[indexCari].waktu_keluar.menit <= 59) {
                waktuKeluarValid = true;
            } else {
                cout << "Input waktu tidak valid! Jam harus antara 0-23 dan menit 0-59.\n";
            }
        } while (!waktuKeluarValid);


        int masukMenit = kendaraan[indexCari].waktu_masuk.jam * 60 + kendaraan[indexCari].waktu_masuk.menit;
        int keluarMenit = kendaraan[indexCari].waktu_keluar.jam * 60 + kendaraan[indexCari].waktu_keluar.menit;
        int durasiMenit = keluarMenit - masukMenit;
        if (durasiMenit < 0) durasiMenit += 24 * 60; 

        int totalJam = durasiMenit / 60;
        int sisaMenit = durasiMenit % 60;

        int tarif;
        if (kendaraan[indexCari].jenis_kend == "mobil") {
            tarif = 5000;
        } else {
            tarif = 3000;
        }

        int bayar;
        if (sisaMenit > 0) {
            bayar = (totalJam + 1) * tarif;
        } else {
            bayar = totalJam * tarif;
        }
        cout << "\n===========================================\n";

        char karcis;
        cout << "Apakah kamu bawa karcis? (y/n) : ";
        cin >> karcis;
        cin.ignore();

        if(karcis == 'n' || karcis == 'N'){
            cout << "Tidak membawa karcis. Denda berlaku\n";
            bayar *= 2; 
        }



        cout << "Durasi parkir: " << totalJam << " jam " << sisaMenit << " menit\n";
        cout << "\n===========================================\n";
        cout << "Total bayar: Rp" << bayar << endl;
        kendaraan[indexCari].tarif = bayar;
        kendaraan[indexCari].status = "keluar";

        if (kendaraan[indexCari].jenis_kend == "mobil"){
            jumlahMobil--;
        } else if (kendaraan[indexCari].jenis_kend == "motor"){
            jumlahMotor--;
        }

        fstream file(namafile.c_str(), ios::out | ios::trunc); 
        if (file.is_open()) {
            for (int i = 0; i < totalData; i++) {
                file << kendaraan[i].nomor_plat << endl;
                file << kendaraan[i].jenis_kend << endl;
                file << kendaraan[i].waktu_masuk.jam << " " << kendaraan[i].waktu_masuk.menit << endl;
                file << kendaraan[i].waktu_keluar.jam << " " << kendaraan[i].waktu_keluar.menit << endl;
                file << kendaraan[i].tarif << endl;
                file << kendaraan[i].status << endl;
            }
            file.close();
            cout << "Status kendaraan diperbarui menjadi 'keluar'.\n";
        } else {
            cout << "Gagal membuka file untuk memperbarui data.\n";
        }
        system("PAUSE");
    } else {
    
        if (pilihanCari == 1) { 
             cout << "Kendaraan dengan plat tersebut tidak ditemukan atau sudah keluar.\n";
        }
        system("PAUSE");
    }
}

void sortShellDesc(){

    Kendaraan temp;

    for (int gap = totalData / 2; gap > 0; gap /= 2)
    {
        int j;
        for (int i = gap; i < totalData; i++)
        {
            temp = kendaraan[i]; 
            j = i;         
            while ((temp.tarif > kendaraan[j - gap].tarif) && (j >= gap))
            {
                kendaraan[j] = kendaraan[j - gap];
                j = j - gap;
            }
            kendaraan[j] = temp;
        }
    }
    showData();
}

void sortInsAsc(){

    int j;
    Kendaraan temp;
    for (int i = 1; i < totalData; i++)
    {
        temp = kendaraan[i];
        j = i - 1;
        while ((j >= 0) && (temp.tarif < kendaraan[j].tarif))
        {
            kendaraan[j + 1] = kendaraan[j];
            j = j - 1;
        }
        kendaraan[j + 1] = temp;
    }
    showData();
}


void totalPendapatan() { 
    int totalPendapatan = 0;

    for (int i = 0; i < totalData; i++) {
        if (kendaraan[i].status == "keluar") {
            totalPendapatan += kendaraan[i].tarif;
        }
    }

    cout << "\n====================================\n";
    cout << "     Total Pendapatan Parkir        \n";
    cout << "====================================\n";
    cout << "Total Pendapatan: Rp" << totalPendapatan << endl;
    cout << "====================================\n";
    system("PAUSE");
}

void searchSent(){
    if (totalData == 0)
    {
        cout << "Belum ada data parkir.\n";
        return;
    }

    string platCari;
    bool ditemukan = false;

    cout << "Masukan nomor plat yang dicari : " ;
    getline(cin, platCari );

    for (int  i = 0; i < totalData; i++)
    {
        if (kendaraan[i].nomor_plat == platCari)
        {
            cout << "Nomor Plat      : " << kendaraan[i].nomor_plat << endl;
            cout << "Jenis Kendaraan : " << kendaraan[i].jenis_kend << endl;
            cout << "Waktu Masuk     : " << kendaraan[i].waktu_masuk.jam << ":" << kendaraan[i].waktu_masuk.menit << endl;
            cout << "Waktu Keluar    : " << kendaraan[i].waktu_keluar.jam << ":" << kendaraan[i].waktu_keluar.menit << endl;
            cout << "Tarif           : " << kendaraan[i].tarif  << endl;
            cout << "Status          : " << kendaraan[i].status << endl << endl;
            ditemukan = true;
            break;
        }
    }

    if(!ditemukan){
        cout << "Data tidak ditemukan" << endl;
    }
        system("pause");
    }
    

void binarySearchTarif() {

    Kendaraan temp;
    for (int i = 1; i < totalData; i++) {
        temp = kendaraan[i];
        int j = i - 1;
        while (j >= 0 && kendaraan[j].nomor_plat > temp.nomor_plat) {
            kendaraan[j + 1] = kendaraan[j];
            j--;
        }
        kendaraan[j + 1] = temp;
    }

    int cariTarif;
    cout << "Masukkan tarif yang ingin dicari: Rp";
    cin >> cariTarif;
    cin.ignore();

    int kiri = 0, atas = totalData - 1, tengah;
    bool ditemukan = false;

    cout << "\nHasil Pencarian:\n";
    while (kiri <= atas) {
        tengah = (kiri + atas) / 2;
        if (kendaraan[tengah].tarif == cariTarif) {
            int mulai = tengah, akhir = tengah;
            while (mulai > 0 && kendaraan[mulai - 1].tarif == cariTarif) mulai--;
            while (akhir < totalData - 1 && kendaraan[akhir + 1].tarif == cariTarif) akhir++;

            for (int i = mulai; i <= akhir; i++) {
                cout << "Nomor Plat      : " << kendaraan[i].nomor_plat << endl;
                cout << "Jenis Kendaraan : " << kendaraan[i].jenis_kend << endl;
                cout << "Waktu Masuk     : " << kendaraan[i].waktu_masuk.jam << ":" << kendaraan[i].waktu_masuk.menit << endl;
                cout << "Waktu Keluar    : " << kendaraan[i].waktu_keluar.jam << ":" << kendaraan[i].waktu_keluar.menit << endl;
                cout << "Tarif           : Rp" << kendaraan[i].tarif << endl;
                cout << "Status          : " << kendaraan[i].status << "\n\n";
            }
            ditemukan = true;
            break;
        } else if (kendaraan[tengah].tarif < cariTarif) {
            kiri = tengah + 1;
        } else {
            atas = tengah - 1;
        }
    }

    if (!ditemukan) {
        cout << "Data dengan tarif Rp" << cariTarif << " tidak ditemukan.\n";
    }

    system("PAUSE");
}


void searchNonSent(){
    if (totalData == 0) {
        cout << "Belum ada data parkir.\n";
        return;
    }

    string statusCari;
    int jumlahDapat = 0;

    cout << "Masukkan status yang dicari (ada / keluar): ";
    getline(cin, statusCari);

    for (int i = 0; i < totalData; i++) {
        if (kendaraan[i].status == statusCari) {
            cout << "Nomor Plat      : " << kendaraan[i].nomor_plat << endl;
            cout << "Jenis Kendaraan : " << kendaraan[i].jenis_kend << endl;
            cout << "Waktu Masuk     : " << kendaraan[i].waktu_masuk.jam << ":" << kendaraan[i].waktu_masuk.menit << endl;
            cout << "Waktu Keluar    : " << kendaraan[i].waktu_keluar.jam << ":" << kendaraan[i].waktu_keluar.menit << endl;
            cout << "Tarif           : " << kendaraan[i].tarif << endl;
            cout << "Status          : " << kendaraan[i].status << endl << endl;
            jumlahDapat++;
        }
    }

    if (jumlahDapat == 0) {
        cout << "Tidak ada kendaraan dengan status '" << statusCari << "' ditemukan.\n";
    }

    system("pause");
}


void loading() {
    system("cls");
    cout << "Memuat ";
    for (int i = 0; i < 5; ++i) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    system("cls");
}

bool login() {
    string inputUsn, inputPass;
    int percobaan = 3;
    while (percobaan > 0) {
        system("cls");
        cout << "================================\n";
        cout << "|    Sistem Manajemen Parkir   |\n";
        cout << "================================\n";
        cout << "Login Sebagai admin\n";
        cout << "Username: ";
        getline(cin, inputUsn);
        cout << "Password: ";
        getline(cin, inputPass);

        for (int i = 0; i < user; i++) {
            if (pengguna[i].username == inputUsn && pengguna[i].password == inputPass) {
                loading();
                cout << "Login berhasil. Selamat datang " << pengguna[i].username;
                        this_thread::sleep_for(chrono::milliseconds(1500));
                return true;
            }
        }

        percobaan--;
        loading();
        cout << "Login gagal. Percobaan tersisa: " << percobaan << "\n";
        system("PAUSE");
    }

    cout << "Login gagal. Anda diblokir.\n";
    return false;
}

void gantiFile() {
    system("cls");
    cout << "Masukkan nama file yang berbeda (.txt): ";
    getline(cin, namafile);

    ifstream file(namafile.c_str());
    if (!file.is_open()) {
        char buat;
        system("cls");
        loading();
        cout << "File tidak ditemukan. Ingin membuat file baru? (y/n): ";
        cin >> buat;
        cin.ignore();

        if (buat == 'y' || buat == 'Y') {
            ofstream baru(namafile);
            baru.close();
            cout << "File baru '" << namafile << "' berhasil dibuat.\n";
        } else {
            cout << "Operasi dibatalkan.\n";
        }

    } else {
        loading();
        cout << "Ganti File Berhasil!\n";
        int i = 0;
        jumlahMobil = 0;
        jumlahMotor = 0;

        while (getline(file, kendaraan[i].nomor_plat)) {
            getline(file, kendaraan[i].jenis_kend);
            file >> kendaraan[i].waktu_masuk.jam >> kendaraan[i].waktu_masuk.menit;
            file >> kendaraan[i].waktu_keluar.jam >> kendaraan[i].waktu_keluar.menit;
            file >> kendaraan[i].tarif;
            file.ignore(); 
            getline(file, kendaraan[i].status);

            if (kendaraan[i].status == "ada") {
                if (kendaraan[i].jenis_kend == "mobil") jumlahMobil++;
                else if (kendaraan[i].jenis_kend == "motor") jumlahMotor++;
            }
        i++;
        }
        totalData = i;
        file.close();
    }
}

void hapusData() {
    system("cls");
    cout << "===== HAPUS DATA KENDARAAN =====\n";
    if (totalData == 0) {
        cout << "Belum ada data kendaraan untuk dihapus.\n";
        system("PAUSE");
        return;
    }

    showData(); 
    cout << "\n=================================\n";

    string platHapus;
    cout << "Masukkan Nomor Plat kendaraan yang ingin dihapus: ";
    getline(cin, platHapus);

    int indexHapus = -1; 
    for (int i = 0; i < totalData; i++) {
        if (kendaraan[i].nomor_plat == platHapus) {
            indexHapus = i;
            break;
        }
    }

    if (indexHapus != -1) {
        char konfirmasi;
        cout << "Data ditemukan: " << kendaraan[indexHapus].nomor_plat << " (" << kendaraan[indexHapus].jenis_kend << ").\n";
        cout << "Apakah Anda yakin ingin menghapus data ini? (y/n): ";
        cin >> konfirmasi;
        cin.ignore();

        if (konfirmasi == 'y' || konfirmasi == 'Y') {
            if (kendaraan[indexHapus].status == "ada") {
                if (kendaraan[indexHapus].jenis_kend == "mobil") {
                    jumlahMobil--;
                } else if (kendaraan[indexHapus].jenis_kend == "motor") {
                    jumlahMotor--;
                }
            }

            for (int i = indexHapus; i < totalData - 1; i++) {
                kendaraan[i] = kendaraan[i + 1];
            }
            totalData--; 

            fstream file(namafile.c_str(), ios::out | ios::trunc); 
            if (file.is_open()) {
                for (int i = 0; i < totalData; i++) {
                    file << kendaraan[i].nomor_plat << endl;
                    file << kendaraan[i].jenis_kend << endl;
                    file << kendaraan[i].waktu_masuk.jam << " " << kendaraan[i].waktu_masuk.menit << endl;
                    file << kendaraan[i].waktu_keluar.jam << " " << kendaraan[i].waktu_keluar.menit << endl;
                    file << kendaraan[i].tarif << endl;
                    file << kendaraan[i].status << endl;
                }
                file.close();
                cout << "Data kendaraan berhasil dihapus dan file diperbarui.\n";
            } else {
                cout << "Gagal membuka file untuk memperbarui data setelah penghapusan.\n";
            }
        } else {
            cout << "Penghapusan dibatalkan.\n";
        }
    } else {
        cout << "Kendaraan dengan Nomor Plat '" << platHapus << "' tidak ditemukan.\n";
    }
    system("PAUSE");
}

int main() {
    int pilihan;

    do {
        system("cls");
        cout << "=====================================\n";
        cout << "   Projek Aplikasi Manajemen Parkir  \n";
        cout << "=====================================\n";
        cout << "Dibuat Oleh : \n";
        cout << "Dimas Hafid Fathoni (123240159)     : \n";
        cout << "Mufid Dhamarjati Kusuma (123240171) : \n";
        cout << "Press any key to continue. . .\n";
        cin.get();

        system("cls");
        cout << "=====================================\n";
        cout << "   Projek Aplikasi Manajemen Parkir  \n";
        cout << "=====================================\n";
        cout << "[1] Menu Login\n";
        cout << "[2] Keluar Program\n";
        cout << "=> ";

        cin >> pilihan;
        cin.ignore(); 

        switch (pilihan) {
            case 1:
                if (login()) {

                    system("cls"); 
                    cout << "Masukkan nama file (dengan ekstensi .txt): ";
                    getline(cin, namafile);

                    ifstream file(namafile.c_str());
                    if (!file.is_open()) {
                        char buat;
                        cout << "File tidak ditemukan. Ingin membuat file baru? (y/n): ";
                        cin >> buat;
                        cin.ignore();
                        if (buat == 'y' || buat == 'Y') {
                            ofstream baru(namafile);
                            baru.close();
                            cout << "File baru '" << namafile << "' berhasil dibuat.\n";
                        } else {
                            cout << "Operasi dibatalkan. Program akan kembali ke menu utama.\n";
                            system("PAUSE");
                            break; 
                        }
                    } else {
                        
                        jumlahMobil = 0;
                        jumlahMotor = 0;
                        totalData = 0; 

                        string line;
                        int i = 0;
                        while (getline(file, kendaraan[i].nomor_plat)) {
                            getline(file, kendaraan[i].jenis_kend);
                            file >> kendaraan[i].waktu_masuk.jam >> kendaraan[i].waktu_masuk.menit;
                            file >> kendaraan[i].waktu_keluar.jam >> kendaraan[i].waktu_keluar.menit;
                            file >> kendaraan[i].tarif;
                            file.ignore(); 
                            getline(file, kendaraan[i].status);

                            if (kendaraan[i].status == "ada") {
                                if (kendaraan[i].jenis_kend == "mobil") jumlahMobil++;
                                else if (kendaraan[i].jenis_kend == "motor") jumlahMotor++;
                            }
                            i++;
                        }
                        totalData = i; 
                        file.close();
                        cout << "Data dari '" << namafile << "' berhasil dimuat.\n";
                        system("PAUSE");
                    }
            
                    int menu;
                    do {
                        system("cls");
                        cout << "=========== MENU PARKIR ============\n";
                        cout << "[1] Tambah Data Kendaraan\n";
                        cout << "[2] Tampilkan Semua Data\n";
                        cout << "[3] Kendaraan Keluar dan Tagihan\n";
                        cout << "[4] Lihat Kendaraan Berdasarkan Tarif\n";
                        cout << "[5] Mencari Kendaraan\n";
                        cout << "[6] Total Pendapatan Parkir\n";
                        cout << "[7] Hapus Kendaraan\n";
                        cout << "[8] Ganti File Data Parkir\n"; 
                        cout << "[9] Logout\n";
                        cout << "====================================\n";
                        cout << "Sisa Slot Mobil: " << maxMobil - jumlahMobil << endl;
                        cout << "Sisa Slot Motor: " << maxMotor - jumlahMotor << endl;
                        cout << "====================================\n";
                        cout << "Pilih menu: ";
                        cin >> menu;
                        cin.ignore(); 

                        switch (menu) {
                            case 1:
                                tambahData();
                                break;
                            case 2:
                                showData();
                                system("PAUSE");
                                break;
                            case 3:
                                kendaraanKeluar();
                                break;
                            case 4: 
                                int sort;
                                do {
                                    system("cls");
                                    cout << "========= Sorting Tarif Kendaraan ==========\n";
                                    cout << "[1] Urutkan data: tarif terkecil ke terbesar\n";
                                    cout << "[2] Urutkan data: tarif terbesar ke terkecil\n";
                                    cout << "[3] Kembali ke menu parkir\n";
                                    cout << "============================================\n";
                                    cout << "Pilih sorting : ";
                                    cin >> sort;
                                    cin.ignore();

                                    switch (sort) {
                                        case 1:
                                            sortInsAsc();
                                            system("PAUSE");
                                            break;
                                        case 2:
                                            sortShellDesc();
                                            system("PAUSE");
                                            break;
                                        case 3:
                                            cout << "Kembali ke menu parkir...\n";
                                            break;
                                        default:
                                            cout << "Pilihan tidak valid!\n";
                                            system("PAUSE");
                                            break;
                                    }
                                } while (sort != 3);
                                break;
                            case 5:
                                int cari;
                                do {
                                    system("cls");
                                    cout << "=========== Menu Cari Kendaraan ============\n";
                                    cout << "[1] Mencari Kendaraan berdasarkan nomor plat\n";
                                    cout << "[2] Mencari Kendaraan berdasarkan status\n";
                                    cout << "[3] Mencari Kendaraan berdasarkan tarif\n"; 
                                    cout << "[4] Kembali ke menu parkir\n"; 
                                    cout << "============================================\n";
                                    cout << "Pilih searching : ";
                                    cin >> cari;
                                    cin.ignore();

                                    switch (cari) {
                                        case 1:
                                            searchSent();
                                            break;
                                        case 2:
                                            searchNonSent();
                                            break;
                                        case 3: 
                                            binarySearchTarif();
                                            break;
                                        case 4: 
                                            cout << "Kembali ke menu parkir...\n";
                                            break;
                                        default:
                                            cout << "Pilihan tidak valid!\n";
                                            system("PAUSE");
                                            break;
                                    }
                                } while (cari != 4); 
                                break;    
                            case 6 :
                                totalPendapatan();
                                break;
                            case 7 : 
                                hapusData();
                                break;
                            case 8 : 
                                gantiFile();
                                system("PAUSE");
                                break;
                            case 9 :
                                cout << "Logout berhasil. Kembali ke menu utama.\n";
                                system("PAUSE");
                                break;
                            default:
                                cout << "Menu tidak valid!\n";
                                system("PAUSE");
                                break;
                        }
                    } while (menu != 8);
                }
                break;
            case 2:
                cout << "Terima kasih. Program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                system("PAUSE");
                break;
        }
    } while (pilihan != 2);

    return 0;
}
