#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <math.h>
#include <iomanip>

using namespace std;

#define SIZE 10

class Resto{
    private:
        struct pesanan{
            int jumlahPesanan;
            int harga;
            int totalHarga;
            string namaPesanan;
        };
        struct ruangan{
            int key;
            string name;
        };
        int antrian;
        vector<pesanan> daftarP;
        ruangan ruang[SIZE];

    public:
        void menuList();
        void pesanMenu();
        void tampilkanPesanan();
        void reservasiMeja();

        void hash(string nama, int nomerHP);
        int hashFunction(int nomerHP);
        void sort();
        void mergeSort(vector<pesanan>&, int left, int right) ;
        void merge(vector<pesanan>&, int left, int mid, int right);

        void queue();
        void stack();

        void pelanggan();
        void admin();
};

int main(){
    Resto resto;
    string nama, password, adminName, adminPass;
    int pilihan;

    cout << "selamat datang aplikasi resto, silahkan anda pilih anda sebagai apa\n";
    cout << "1. Admin\n";
    cout << "2. Pelanggan\n";
    cout << "0. Keluar\n";
    cout << "Masukkan Pilihan Anda > ";
    cin >> pilihan;

    switch (pilihan)
    {
    case 1:
        cout << "Masukkan Nama Anda: ";
        getline(cin, nama);
        cout << "Masukkan Password: ";
        getline(cin, password);

        if(nama == adminName && password == adminPass){
            resto.admin();
        }
        else{
            cout << "Sandi Salah\n";
        }
        break;
    case 2:
        resto.pelanggan();
        break;
    case 0: 
        break;
    default:
        break;
    }

    return 0;
}

void Resto::admin(){
    int pilihan;
    cout << "Selamat datang admin, silahkan pilih menu anda\n";
    cout << "1. Tampilkan antrian\n";
    cout << "2. Tampilkan reservasi\n";
    cout << "3. Tampikan Daftar Pesanan dan Pembayaran hari ini\n";
}

void Resto::pelanggan(){
    int pilihan;
    cout << '|' << string(75, '-')  << '|' << endl;
    cout << '|' << string(20, '=') << " SELAMAT DATANG DI RESTAURANT KAMI " << string(20, '=') << '|' << endl;
    cout << '|' << string(75, '-') << '|' << endl;
    cout << "|1. Menu Makanan" << right << setw(61) << '|' << endl;
    cout << "|2. Reservasi Meja" << right << setw(61) << '|' << endl;
    cout << "|3. Reservasi Ruangan\n";
    cout << "|3. Tampilkan Meja Kosong\n";
    cout << "|4. Tampilkan Letak Meja di restauran\n";
    cout << "|0. Keluar\n";
    cout << "|Masukkan Pilihan Anda > ";
    cin >> pilihan;

    switch (pilihan)
    {
    case 1:
        menuList();
        break;
    default:
        break;
    }
}

void Resto::menuList(){
    int pilihan, jumlah, harga, attempt = 0;
    string nama;
    pesanan p;

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

    mergeSort(daftarP, 0, daftarP.size() - 1);

    cout << left << string(19, '-') << " PESANAN ANDA " << right << string(20, '-') << endl;
    cout << left << setw(nameWidth + 3) << "Nama Pesanan" << right << setw(priceWidth) << "Harga" << setw(2 + jumlahWidth) << "jumlah" << setw(totalWidth - 2) << "Total" << endl;
    cout << string(nameWidth + priceWidth + jumlahWidth + totalWidth + 3, '-') << endl;

    for(int i = 0; i < daftarP.size(); i++){
        cout << i + 1 << ". " << left << setw(nameWidth) << daftarP[i].namaPesanan << right << setw(priceWidth) << daftarP[i].harga << setw(jumlahWidth) << daftarP[i].jumlahPesanan << setw(totalWidth) << daftarP[i].totalHarga << endl;
    }
}

void Resto::mergeSort(vector<pesanan>& p, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Membagi vektor menjadi dua bagian, kemudian melakukan rekursi
        mergeSort(p, left, mid);
        mergeSort(p, mid + 1, right);

        // Menggabungkan dua bagian yang telah diurutkan
        merge(p, left, mid, right);
    }
}

void Resto::merge(vector<pesanan>& p, int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<pesanan> leftVec(n1);
    vector<pesanan> rightVec(n2);

    for (int i = 0; i < n1; ++i)
        leftVec[i] = p[left + i];
    for (int i = 0; i < n2; ++i)
        rightVec[i] = p[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftVec[i].namaPesanan <= rightVec[j].namaPesanan) {
            p[k] = leftVec[i];
            i++;
        } else {
            p[k] = rightVec[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        p[k] = leftVec[i];
        i++;
        k++;
    }

    while (j < n2) {
        p[k] = rightVec[j];
        j++;
        k++;
    }
}

void Resto::reservasiMeja(){
    string nama, noHP;
    cout << "Masukkan Nama Anda: ";
    getline(cin, nama);
    cout << "Masukkan Nomor HP Anda: ";
    getline(cin, noHP);

    int nomerHP = stoi(noHP);

    hash(nama, nomerHP);
}

void Resto::hash(string nama, int nomerHP){
    int index = hashFunction(nomerHP);
    
    ruang[index].name = nama;
    ruang[index].key = nomerHP;
}

int Resto::hashFunction(int nomerHP){
    return abs(nomerHP) % SIZE;
}

