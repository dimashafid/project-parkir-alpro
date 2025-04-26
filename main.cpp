#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

string inputUsn, inputPass;

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

void login() {

    cout << "Anda ingin login sebagai apa?\n";
    cout << "1. Admin\n" 
         << "2. Pengguna Parkir\n"
         << "=> ";
    cin >> choice;
}

void Adminlogin (

    int percobaan = 3;
    bool berhasil = false;
    int choice;

    switch (choice) {
    case 1 :  
        break;
    
    default:
        break;
    }
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

void pengguna()

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
}
