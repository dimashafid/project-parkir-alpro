#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

string inputUsn, inputPass;

struct Waktu{
    int jam, menit, detik;
};
struct Pemilik{
    string nama;
    string nomor_plat;
};
struct Kendaraan{
    Pemilik data_pemilik;
    string jenis_kend;
    Waktu waktu_masuk;
    Waktu waktu_keluar;
};

void kendaraanMasuk(Kendaraan &k ){
        cout << "Masukkan nama pemilik    : ";
        getline(cin >> ws, k.data_pemilik.nama );
        cout << "Masukkan jenis kendaraan : ";
        getline(cin >> ws, k.jenis_kend );
        cout << "Masukkan nomor plat      : ";
        getline(cin >> ws, k.data_pemilik.nomor_plat);
     
}
struct Akun {
    string username;
    string password;
};

const int maxUser = 30;
int user = 3;

Akun pengguna[maxUser] = {
    {"Dimas", "Hafid"},
    {"Dimashafid", "dimas123"},
    {"admin", "admin"} };

void login();
void buatAkun();
void lobby();
void penggunaParkir();


void login() {
    int percobaan = 3;
    bool berhasil = false;
    int choice;

    cout << "Anda ingin login sebagai apa?\n";
    cout << "1. Admin\n" 
         << "2. Pengguna Parkir\n"
         << "=> ";
    cin >> choice;

    if(choice != 1) {
        penggunaParkir();
    } else {
        do {
            system("cls");
            cout << "================================\n";
            cout << "|| Selamat Datang di Menu Login ||\n";
            cout << "================================\n";
            cout << "Masukkan Username: ";
            getline(cin, inputUsn);
    
            cout << "Masukkan Password: ";
            getline(cin, inputPass);
    
            for (int i = 0; i < user; i++) {
                if (pengguna[i].username == inputUsn && pengguna[i].password == inputPass) {
                    cout << "Login Berhasil. . .\n";
                    cout << "Tekan Apapun untuk masuk ke Menu. . .";
                    cin.get();
                    return; // Kembali ke lobby setelah login berhasil
                }
            }
    
            percobaan--;
            if (percobaan == 0) {
                cout << "\nKesempatan Anda habis. Anda telah diblokir!\n";
                exit(0);
            } else {
                cout << "Login Gagal. Kesempatan tersisa " << percobaan << " kali\n";
                cin.get();
            }
    
        } while (!berhasil);
    }

    
}

void penggunaParkir() {
    cout << "Tap Disini";
}

void buatAkun() {
    if (user >= maxUser) {
        cout << "Akun Sudah Terlalu Banyak. Silahkan Login\n\n";
        cin.get();
        login();
    }

    system("cls");
    cout << "================================\n";
    cout << "|        Buat Akun Anda        |\n";
    cout << "================================\n";
    cout << "Inputkan Username dan Password\n";

    cin.ignore();
    cout << "Username: "; getline(cin, pengguna[user].username);
    cout << "Password: "; getline(cin, pengguna[user].password);
    
    user++;
    cout << "Pembuatan Akun Berhasil!\n\n";
    cout << "Tekan Apapun Untuk Masuk Ke Halaman Login. . .";
    cin.get();
    login();
}

void lobby() {
    int choice;

    do {
        system("cls");
        cout << "===============================\n";
        cout << "Selamat Datang di Lobby Program\n";
        cout << "===============================\n";
        cout << "Apa Yang Ingin Anda Lakukan?\n";
        cout << "[1] Login\n" 
             << "[2] Buat Akun\n" 
             << "[3] Keluar\n" 
             << "=> ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                login();
                return;
                break;

            case 2:
                buatAkun();
                break;

            case 3:
                cout << "\nMeninggalkan Program. . . \n";
                exit(0);
                break;

            default:
                cout << "\nPilihan tidak valid. Silakan coba lagi.\n";
                cin.get();
                break;
        }

    } while (choice != 3);
}

int main() {
    lobby();
    return 0;
    Kendaraan daftar[100];
     int jumlah = 0;

    kendaraanMasuk(daftar[jumlah]);
    jumlah++;
}

// menu yang perlu dibuat
// 1. Tambah data parkir baru untuk pengguan

// Lihat semua data parkir

// Cari kendaraan (search plat nomor)

// Urutkan kendaraan (sorting)

// Hapus kendaraan keluar parkir untuk penguna dan admin

// Simpan data ke file

// Keluar