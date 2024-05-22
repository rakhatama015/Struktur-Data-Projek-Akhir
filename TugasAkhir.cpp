#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <math.h>
#include <iomanip>

using namespace std;

class Resto{
    private:
        struct pesanan{
            int jumlahPesanan;
            int harga;
            int totalHarga;
            string namaPesanan;
        };
        int antrian;
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
};

int main(){
    Resto resto;
    int pilihan;

    resto.menuList();

    return 0;
}

void Resto::menuList(){
    int pilihan, jumlah, harga, attempt = 0;
    string nama;
    pesanan p;
    vector<pesanan> daftarP;

    const int nameWidth = 20;
    const int priceWidth = 10;
    const int jumlahWidth = 8;
    const int totalWidth = 12;
    const int cornerLeft = 3;

    do{
        cout << "|-------------------------------------------|\n";
        cout << "|=============== MENU MAKANAN ==============|\n";
        cout << "|-------------------------------------------|\n";
        cout << "|1. Nasi Goreng Jawa              Rp. 15.000|\n";
        cout << "|2. Nasi Goreng Ayam              Rp. 15.000|\n";
        cout << "|3. Mie Ayam                      Rp. 10.000|\n";
        cout << "|4. Mie Ayam Kuah                 Rp. 10.000|\n";
        cout << "|5. Mie Goreng                    Rp. 10.000|\n";
        cout << "|6. Nasi Uduk                     Rp. 12.000|\n";
        cout << "|7. Nasi Liwet                    Rp. 12.000|\n";
        cout << "|8. Soto Ayam                     Rp. 12.000|\n";
        cout << "|9. Rawon                         Rp. 12.000|\n";
        cout << "|0. Selesai                                 |\n";
        cout << "|Masukkan Pilihan Menu Anda > ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            harga = 15000;
            nama = "Nasi Goreng";

            cout << "|Anda Memilih Nasi Goreng Jawa\n";
            cout << "Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;
            
            p.harga = harga;
            p.totalHarga = jumlah * harga;
            p.jumlahPesanan = jumlah;
            p.namaPesanan = nama;

            daftarP.push_back(p);
            break;

        case 2: 
            harga = 15000;
            nama = "Nasi Goreng Ayam";

            cout << "|Anda Memilih Nasi Goreng Ayam\n";
            cout << "Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;

            p.harga = harga;
            p.totalHarga = jumlah * harga;
            p.jumlahPesanan = jumlah;
            p.namaPesanan = nama;

            daftarP.push_back(p);            
            break;

        case 3:
            harga = 10000;
            cout << "|Anda Memilih Mie Ayam\n";
            cout << "Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;

            p.harga = harga;
            p.totalHarga = jumlah * harga;
            p.jumlahPesanan = jumlah;
            p.namaPesanan = nama;

            daftarP.push_back(p);
            break;

        case 4:
            harga = 10000;
            nama = "Mie Ayam Kuah";
            cout << "|Anda Memilih Mie Ayam Kuah\n";
            cout << "Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;

            p.harga = harga;
            p.totalHarga = jumlah * harga;
            p.jumlahPesanan = jumlah;
            p.namaPesanan = nama;

            daftarP.push_back(p);
            break;

        case 5:
            harga = 10000;
            nama = "Mie Goreng";

            cout << "|Anda Memilih Mie Goreng\n";
            cout << "Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;

            p.harga = harga;
            p.totalHarga = jumlah * harga;
            p.jumlahPesanan = jumlah;
            p.namaPesanan = nama;

            daftarP.push_back(p);
            break;
        case 6:
            harga = 13000;
            nama = "Nasi Uduk";

            cout << "|Anda Memilih Nasi Uduk\n";
            cout << "Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;

            p.harga = harga;
            p.totalHarga = jumlah * harga;
            p.jumlahPesanan = jumlah;
            p.namaPesanan = nama;

            daftarP.push_back(p);    
            break;
        case 7:
            harga = 13000;
            nama = "Nasi Liwet";

            cout << "|Anda Memilih Nasi Liwet\n";
            cout << "Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;

            p.harga = harga;
            p.totalHarga = jumlah * harga;
            p.jumlahPesanan = jumlah;
            p.namaPesanan = nama;

            daftarP.push_back(p);
            break;
        case 8:
            harga = 13000;
            nama = "Soto Ayam";

            cout << "|Anda Memilih Soto Ayam\n";
            cout << "Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;

            p.harga = harga;
            p.totalHarga = jumlah * harga;
            p.jumlahPesanan = jumlah;
            p.namaPesanan = nama;

            daftarP.push_back(p);
            break;
        case 9:
            harga = 13000;
            nama = "Rawon";

            cout << "|Anda Memilih Rawon\n";
            cout << "Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;

            p.harga = harga;
            p.totalHarga = jumlah * harga;
            p.jumlahPesanan = jumlah;
            p.namaPesanan = nama;

            daftarP.push_back(p);
            break;
        case 0:
            cout << "Pesanan Anda Telah Diterima\n";
            break;
        default:
            break;
        }

    }while(pilihan != 0);

    antrian++;

    cout << left << string(19, '-') << " PESANAN ANDA " << right << string(20, '-') << endl;
    cout << left << setw(nameWidth + 3) << "Nama Pesanan" << right << setw(priceWidth) << "Harga" << setw(2 + jumlahWidth) << "jumlah" << setw(totalWidth - 2) << "Total" << endl;
    cout << string(nameWidth + priceWidth + jumlahWidth + totalWidth + 3, '-') << endl;

    for(int i = 0; i < daftarP.size(); i++){
        cout << i + 1 << ". " << left << setw(nameWidth) << daftarP[i].namaPesanan << right << setw(priceWidth) << daftarP[i].harga << setw(jumlahWidth) << daftarP[i].jumlahPesanan << setw(totalWidth) << daftarP[i].totalHarga << endl;
    }
}
