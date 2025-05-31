#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;


const int maxMobil = 40;
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
    {"Mufid", "Darmajati"},
    {"admin", "admin"}
};

string namafile;
int jumlahdata;
int totalData = 0;

void bacaData() {
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
            cout << "Operasi dibatalkan.\n";
            return;
        }
    } else {
        int i = 0;
        jumlahMobil = 0;
        jumlahMotor = 0;
        while (getline(file, kendaraan[i].nomor_plat)) {
            getline(file, kendaraan[i].jenis_kend);
            file >> kendaraan[i].waktu_masuk.jam >> kendaraan[i].waktu_masuk.menit;
            file >> kendaraan[i].waktu_keluar.jam >> kendaraan[i].waktu_keluar.menit;
            file >> kendaraan[i].tarif;
            file.ignore(); // buang newline
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


void tambahData() {
    bacaData();

    if (namafile.empty()) return;

    cout << "\nINPUT DATA KENDARAAN\n";
    cout << "File: " << namafile << endl;
    cout << "Jumlah kendaraan yang masuk: ";
    cin >> jumlahdata;
    cin.ignore();

    fstream file(namafile.c_str(), ios::app);
    if (file.is_open()) {
        for (int i = 0; i < jumlahdata; i++) {
            cout << "Nomor Plat\t\t\t: ";
            getline(cin, kendaraan[totalData].nomor_plat);
            cout << "Jenis Kendaraan (mobil/motor) : ";
            getline(cin, kendaraan[totalData].jenis_kend);

            if (kendaraan[totalData].jenis_kend == "mobil") {
                if (jumlahMobil >= maxMobil) {
                    cout << "Slot mobil penuh!\n"; 
                }
                jumlahMobil++;
            } else if (kendaraan[totalData].jenis_kend == "motor") {
                if (jumlahMotor >= maxMotor) {
                    cout << "Slot motor penuh!\n"; 
                }
                jumlahMotor++;
            } else {
                cout << "Jenis kendaraan tidak dikenali!\n"; 
            }

            cout << "Waktu Masuk (jam menit): ";
            cin >> kendaraan[totalData].waktu_masuk.jam;
            cin >> kendaraan[totalData].waktu_masuk.menit;
            cin.ignore();

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
    bacaData();

    string platCari;
    cout << "Nomor plat kendaraan yang keluar: ";
    getline(cin, platCari);

    bool ditemukan = false;
    for (int i = 0; i < totalData; i++) {
        if (kendaraan[i].nomor_plat == platCari && kendaraan[i].status == "ada") {
            cout << "Masukkan Waktu Keluar (jam menit): ";
            cin >> kendaraan[i].waktu_keluar.jam >> kendaraan[i].waktu_keluar.menit;
            cin.ignore();

            int masukMenit = kendaraan[i].waktu_masuk.jam * 60 + kendaraan[i].waktu_masuk.menit;
            int keluarMenit = kendaraan[i].waktu_keluar.jam * 60 + kendaraan[i].waktu_keluar.menit;
            int durasiMenit = keluarMenit - masukMenit;
            if (durasiMenit < 0) durasiMenit += 24 * 60;

            int totalJam = durasiMenit / 60;
            int sisaMenit = durasiMenit % 60;

             int tarif;
            if (kendaraan[i].jenis_kend == "mobil") {
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

            cout << "Durasi parkir: " << totalJam << " jam " << sisaMenit << " menit\n";
            cout << "Total bayar: Rp" << bayar << endl;
            kendaraan[i].tarif = bayar;
            kendaraan[i].status = "keluar";

            if (kendaraan[i].jenis_kend == "mobil"){
            jumlahMobil--;
            }else if (kendaraan[i].jenis_kend == "motor"){
            jumlahMotor--;
            }

            ditemukan = true;
            break;
        }
    }

    if (ditemukan) {
        fstream file(namafile.c_str(), ios::out);
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
        system("PAUSE");
    } else {
        cout << "Kendaraan dengan plat tersebut tidak ditemukan atau sudah keluar.\n";
        system("PAUSE");
    }
}

void sortShellDesc(){
    bacaData();
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
    bacaData();
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
    bacaData(); 
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
    bacaData();
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
    
void urutindataAsc() {
    bacaData();
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
}

void binarySearchTarif() {
    bacaData();
    urutindataAsc();

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


//untuk mencari status kendaraan ada/tidak ada
void searchNonSent(){
    bacaData();
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
    cout << "Login berhasil!";
    this_thread::sleep_for(chrono::milliseconds(1000));
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
                return true;
            }
        }

        percobaan--;
        cout << "Login gagal. Percobaan tersisa: " << percobaan << "\n";
        system("PAUSE");
    }

    cout << "Login gagal. Anda diblokir.\n";
    return false;
}

    

int main() {
    int pilihan;

    do {
        system("cls");
        cout << "=====================================\n";
        cout << "   Projek Aplikasi Manajemen Parkir  \n";
        cout << "=====================================\n";
        cout << "Dibuat Oleh : \n";
        cout << "Dimas Hafid Fathoni (123240159) : \n";
        cout << "Mufid Darmajati Kusuma (123240171) : \n";
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
                        cout << "[7] Logout\n";
                        cout << "====================================\n";
                        cout << "Pilih menu: ";
                        cin >> menu;
                        cin.ignore(); 

                        switch (menu) {
                            case 1:
                                tambahData();
                                break;
                            case 2:
                                bacaData();
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
                                        cout << "[3] Mencari Kendaraan bedasarkan tarif\n";
                                        cout << "[3] Kembali ke menu parkir\n";
                                        cout << "============================================\n";
                                        cout << "Pilih searching : ";
                                        cin >> cari;
                                        cin.ignore();

                                        switch (cari) {
                                            case 1:
                                                searchSent();
                                                system("PAUSE");
                                                break;
                                            case 2:
                                                searchNonSent();
                                                system("PAUSE");
                                                break;
                                            case 3:
                                                binarySearchTarif();
                                                system("PAUSE");
                                                break;
                                            case 4:
                                                cout << "Kembali ke menu parkir...\n";
                                                break;

                                            default:
                                                cout << "Pilihan tidak valid!\n";
                                                system("PAUSE");
                                                break;
                                        }
                                    } while (cari != 3);
                                    break;    
                            case 6 :
                                totalPendapatan();
                                break;
                            case 7 :
                                cout << "Logout berhasil.\n";
                                system("PAUSE");
                                break;
                            default:
                                cout << "Menu tidak valid!\n";
                                system("PAUSE");
                        }
                    } while (menu != 7);
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
