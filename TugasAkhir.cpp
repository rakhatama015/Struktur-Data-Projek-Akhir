#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <math.h>

using namespace std;

class Resto{
    private:
        
    public:
        void menuList();
        void pesanMenu();
        void tampilkanPesanan();
        void reservasi();

        void hash();
        void sort();
        void mergeSort();
        void merge();

        void queue();
        void stack();
        void rakha();
};

int main(){
    Resto resto;
    int pilihan;

    resto.menuList();

    return 0;
}

void Resto::menuList(){
    int pilihan, jumlah, totalHarga, harga, attempt = 0;
    vector<int> jumlahHarga;
    
    do{
        cout << "|-------------------------------------------|\n";
        cout << "|=============== MENU MAKANAN ==============|\n";
        cout << "|-------------------------------------------|\n";
        cout << "|1. Nasi Goreng Jawa              Rp. 15.000|\n";
        cout << "|2. Nasi Goreng Ayam              Rp. 15.000|\n";
        cout << "|3. Mie Ayam                      Rp. 10.000|\n";
        cout << "|4. Mie Ayam Kuah                 Rp. 10.000|\n";
        cout << "|5. Mie Goreng                    Rp. 10.000|\n";
        cout << "|6. Nasi Uduk                     Rp. 10.000|\n";
        cout << "|7. Nasi Liwet                    Rp. 10.000|\n";
        cout << "|8. Soto Ayam                     Rp. 10.000|\n";
        cout << "|9. Rawon                         Rp. 10.000|\n";
        cout << "|0. Selesai                                 |\n";
        cout << "|Masukkan Pilihan Menu Anda > ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            harga = 15000;
            cout << "|Anda Memilih Nasi Goreng Jawa\n";
            cout << "Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;
            totalHarga = (harga * jumlah);
            jumlahHarga[attempt] = totalHarga;
            break;
        
        case 2: 
            harga = 15000;
            cout << "|Anda Memilih Nasi Goreng Ayam\n";
            cout << "Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;
            totalHarga = (harga * jumlah);
            jumlahHarga[attempt] = totalHarga;
            break;
        case 3:
            harga = 15000;
            cout << "|Anda Memilih Nasi Goreng Jawa\n";
            cout << "Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;
            totalHarga = (harga * jumlah);
            jumlahHarga[attempt] = totalHarga;
            break;
        case 4:
            harga = 15000;
            cout << "|Anda Memilih Nasi Goreng Jawa\n";
            cout << "Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;
            totalHarga = (harga * jumlah);
            jumlahHarga[attempt] = totalHarga;
            break;
        case 5:
            harga = 15000;
            cout << "|Anda Memilih Nasi Goreng Jawa\n";
            cout << "Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;
            totalHarga = (harga * jumlah);
            jumlahHarga[attempt] = totalHarga;
            break;
        case 6:
            harga = 15000;
            cout << "|Anda Memilih Nasi Goreng Jawa\n";
            cout << "Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;
            totalHarga = (harga * jumlah);
            jumlahHarga[attempt] = totalHarga;
            break;
        case 7:
            harga = 15000;
            cout << "|Anda Memilih Nasi Goreng Jawa\n";
            cout << "Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;
            totalHarga = (harga * jumlah);
            jumlahHarga[attempt] = totalHarga;
            break;
        case 9:
            harga = 15000;
            cout << "|Anda Memilih Nasi Goreng Jawa\n";
            cout << "Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;
            totalHarga = (harga * jumlah);
            jumlahHarga[attempt] = totalHarga;
            break;
        case 0:

            break;
        default:
            break;
        }

        attempt++;

    }while(pilihan != 0);
}
