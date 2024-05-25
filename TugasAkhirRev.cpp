#include <iostream>
#include <cstring>
#include <cmath>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

#define SIZE 10

class Resto {
private:
    struct HashEntry {
        string nama;
        long int nomerHP;
        string noHP;
        bool isOccupied;
    };
    HashEntry hashTable[SIZE];
    
    struct pesanan {
        int jumlahPesanan;
        int harga;
        int totalHarga;
        string namaPesanan;
    };
    struct node {
        string key;
        string name;
        node* prev;
        node* next;
    };
    struct bangku {
        node* head;
    };
    struct Node {
        string key;
        string name;
        Node* prev;
        Node* next;
    };
    struct ruangan {
        Node* head;
    };
    struct TreeNode {
        int data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
    };
    struct Graph {
        int adjMatrix[SIZE][SIZE];
        Graph() {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    adjMatrix[i][j] = 0;
                }
            }
        }
        void addEdge(int u, int v) {
            adjMatrix[u][v] = 1;
            adjMatrix[v][u] = 1;
        }
        void bfs(int start) {
            bool visited[SIZE] = { false };
            int queue[SIZE];
            int front = 0;
            int rear = 0;

            queue[rear++] = start;
            visited[start] = true;

            int count = 0;

            while (front < rear) {
                int node = queue[front++];
                cout << "[Meja " << node + 1 << "] ";
                count++;

                if (count % 2 == 0) {
                    cout << endl;
                }

                for (int i = 0; i < SIZE; i++) {
                    if (adjMatrix[node][i] == 1 && !visited[i]) {
                        queue[rear++] = i;
                        visited[i] = true;
                    }
                }
            }

            if (count % 2 != 0) {
                cout << endl;
            }
        }
        void dfsUtil(int node, bool visited[]) {
            visited[node] = true;
            cout << node + 1 << " ";
            for (int i = 0; i < SIZE; i++) {
                if (adjMatrix[node][i] == 1 && !visited[i]) {
                    dfsUtil(i, visited);
                }
            }
        }
        void dfs(int start) {
            bool visited[SIZE] = { false };
            dfsUtil(start, visited);
            cout << endl;
        }
    };

    int antrian;
    pesanan* daftarP;
    pesanan DaftarP[100];
    int daftarPSize;
    int daftarPCapacity;

    pesanan* stackPesanan;
    int stackSize;

    pesanan* queuePesanan;
    int queueFront;
    int queueRear;
    int queueSize;

    TreeNode* treeRoot;
    Graph graph;

public:
    bangku meja[SIZE] = { nullptr };
    ruangan ruang[SIZE] = { nullptr };

    Resto();
    ~Resto();
    void menuList();
    void pesanMenu();
    void tampilkanPesanan();
    void reservasiMeja();

    void hash(string nama, long int nomerHP, int pilihan, string noHP);
    long int hashFunction(long int nomerHP);
    int quadraticProbing(int nomerHP, int attempt);
    void sort();
    void mergeSort(pesanan*, int left, int right);
    void merge(pesanan*, int left, int mid, int right);

    void insertStack(pesanan p);
    void insertQueue(pesanan p);
    TreeNode* insertTree(TreeNode* node, int data);
    void inorder(TreeNode* node);
    void preorder(TreeNode* node);
    void postorder(TreeNode* node);
    void displayTree();
    void createGraph();

    void pelanggan();
    void admin();
    void tampilkanAntrian();
    void tampilkanReservasiMeja();
    void tampilkanReservasiRuangan();
    void tampilkanMejaKosong();

    void reservasiRuangan();
    void hash2(string nama, long int nomerHP, int pilihan, string noHP);
    int quadraticProbing2(int nomerHP, int attempt);
    void tampilkanLetakMeja();
    int sumTree(TreeNode* node);
    int getTotalIncome();
    void tampilkanRuangKosong();
};

Resto::Resto() : treeRoot(nullptr), graph(), daftarPSize(0), daftarPCapacity(10), stackSize(0), queueFront(0), queueRear(0), queueSize(0) {
    daftarP = new pesanan[daftarPCapacity];
    stackPesanan = new pesanan[daftarPCapacity];
    queuePesanan = new pesanan[daftarPCapacity];
    for (int i = 0; i < SIZE; i++) {
        hashTable[i].isOccupied = false;
    }
    createGraph();
}

Resto::~Resto() {
    delete[] daftarP;
    delete[] stackPesanan;
    delete[] queuePesanan;
}

int main() {
    Resto resto;
    string nama, password, adminName = "admin", adminPass = "password";
    int pilihan, pilihan2;

    do {
        cout << "|" << string(59, '-') << "|" << '\n';
        cout << "|" << string(10, '=') << " SELAMAT DATANG DI APLIKASI RESTO KAMI " << string(10, '=') << "|" << '\n';
        cout << "|" << string(59, '-') << "|" << '\n';
        cout << "|1. Admin\n";
        cout << "|2. Pelanggan\n";
        cout << "|0. Keluar\n";
        cout << "|Masukkan Pilihan Anda > ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            pilihan2 = 0;
            do {
                cout << "\n|Masukkan Nama Anda: ";
                cin.ignore();
                getline(cin, nama);
                cout << "|Masukkan Password: ";
                getline(cin, password);

                if (nama == adminName && password == adminPass) {
                    resto.admin();
                    pilihan2 = 0;
                }
                else {
                    cout << "\nSandi Salah\n";
                    cout << "\n|1. Ulang\n";
                    cout << "|0. Keluar\n";
                    cout << "|> ";
                    cin >> pilihan2;
                }
            } while (pilihan2 != 0);
            break;
        case 2:
            cout << '\n';
            resto.pelanggan();
            break;
        case 0:
            cout << '\n' << string(10, '-') << " Anda Memilih Keluar " << string(10, '-') << '\n';
            break;
        default:
            cout << "\nPilihan Tidak Valid\n";
            break;
        }
        cout << endl;
    } while (pilihan != 0);

    return 0;
}

void Resto::admin() {
    int pilihan;
    do {
        cout << endl;
        cout << '|' << string(42, '=') << '|' << '\n';
        cout << '|' << string(10, '=') << " SELAMAT DATANG ADMIN " << string(10, '=') << '|' << '\n';
        cout << '|' << string(42, '=') << '|' << '\n';
        cout << "|1. Tampilkan Antrian\n";
        cout << "|2. Tampilkan Reservasi Meja\n";
        cout << "|3. Tampilkan Reservasi Ruangan\n";
        cout << "|4. Tampikan Daftar Pesanan dan Pembayaran Hari Ini\n";
        cout << "|5. Tampilkan Total Uang Masuk Hari Ini\n";
        cout << "|0. Keluar\n";
        cout << "|Masukkan Pilihan > ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tampilkanAntrian();
            break;
        case 2:
            tampilkanReservasiMeja();
            break;
        case 3:
            tampilkanReservasiRuangan();
            break;
        case 4:
            tampilkanPesanan();
            break;
        case 5:
            displayTree();
            cout << "\nTotal uang masuk hari ini: " << getTotalIncome() << " Rupiah" << endl;
            break;
        case 0:
            break;
        default:
            cout << "\nPilihan tidak valid" << endl;
            break;
        }
    } while (pilihan != 0);
}

void Resto::pelanggan() {
    int pilihan;
    do {
        cout << '|' << string(75, '-')  << '|' << endl;
        cout << '|' << string(20, '=') << " SELAMAT DATANG DI RESTAURANT KAMI " << string(20, '=') << '|' << endl;
        cout << '|' << string(75, '-') << '|' << endl;
        cout << left << setw(37) << "|1. Menu Makanan" << right << setw(40) << '|' << endl;
        cout << left << setw(37) << "|2. Reservasi Meja" << right << setw(40) << '|' << endl;
        cout << left << setw(37) << "|3. Reservasi Ruangan" << right << setw(40) << '|' << '\n';
        cout << left << setw(37) << "|4. Tampilkan Meja Kosong" << right << setw(40) << '|' << '\n';
        cout << left << setw(37) << "|5. Tampilkan Ruang Kosong" << right << setw(40) << '|' << '\n';
        cout << left << setw(37) << "|6. Tampilkan Letak Meja di restauran" << right << setw(40) << '|' << '\n';
        cout << left << setw(37) << "|0. Keluar" << right << setw(40) << '|' << '\n';
        cout << "|Masukkan Pilihan Anda > ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            pesanMenu();
            break;
        case 2:
            reservasiMeja();
            break;
        case 3:
            reservasiRuangan();
            break;
        case 4:
            tampilkanMejaKosong();
            break;
        case 5:
            tampilkanRuangKosong();
            break;
        case 6:
            tampilkanLetakMeja();
            break;
        case 0:
            cout << "\nTerima kasih telah berkunjung ke restaurant kami.\n";
            break;
        default:
            cout << "\nPilihan tidak valid" << endl;
            break;
        }
    } while (pilihan != 0);
}

void Resto::menuList() {
    int pilihan, jumlah, harga, total = 0, attempt = 0;
    string nama;
    pesanan p;

    const int nameWidth = 20;
    const int priceWidth = 10;
    const int jumlahWidth = 8;
    const int totalWidth = 12;
    const int cornerLeft = 3;

    do{
        cout << "\n|-------------------------------------------|\n";
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
            cout << "|Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;
            
            p.harga = harga;
            p.totalHarga = jumlah * harga;
            p.jumlahPesanan = jumlah;
            p.namaPesanan = nama;

            DaftarP[attempt] = p;
            insertStack(p);
            insertQueue(p);
            // Insert into tree
            treeRoot = insertTree(treeRoot, p.totalHarga);
            break;

        case 2: 
            harga = 15000;
            nama = "Nasi Goreng Ayam";

            cout << "|Anda Memilih Nasi Goreng Ayam\n";
            cout << "|Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;

            p.harga = harga;
            p.totalHarga = jumlah * harga;
            p.jumlahPesanan = jumlah;
            p.namaPesanan = nama;

            DaftarP[attempt] = p;
            insertStack(p);
            insertQueue(p);
                        // Insert into tree
            treeRoot = insertTree(treeRoot, p.totalHarga);            
            break;

        case 3:
            harga = 10000;
            cout << "|Anda Memilih Mie Ayam\n";
            cout << "|Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;

            p.harga = harga;
            p.totalHarga = jumlah * harga;
            p.jumlahPesanan = jumlah;
            p.namaPesanan = nama;

            DaftarP[attempt] = p;
            insertStack(p);
            insertQueue(p);
                        // Insert into tree
            treeRoot = insertTree(treeRoot, p.totalHarga);
            break;

        case 4:
            harga = 10000;
            nama = "Mie Ayam Kuah";
            cout << "|Anda Memilih Mie Ayam Kuah\n";
            cout << "|Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;

            p.harga = harga;
            p.totalHarga = jumlah * harga;
            p.jumlahPesanan = jumlah;
            p.namaPesanan = nama;

            DaftarP[attempt] = p;
            insertStack(p);
            insertQueue(p);
                        // Insert into tree
            treeRoot = insertTree(treeRoot, p.totalHarga);
            break;

        case 5:
            harga = 10000;
            nama = "Mie Goreng";

            cout << "|Anda Memilih Mie Goreng\n";
            cout << "|Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;

            p.harga = harga;
            p.totalHarga = jumlah * harga;
            p.jumlahPesanan = jumlah;
            p.namaPesanan = nama;

            DaftarP[attempt] = p;
            insertStack(p);
            insertQueue(p);
                        // Insert into tree
            treeRoot = insertTree(treeRoot, p.totalHarga);
            break;
        case 6:
            harga = 13000;
            nama = "Nasi Uduk";

            cout << "|Anda Memilih Nasi Uduk\n";
            cout << "|Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;

            p.harga = harga;
            p.totalHarga = jumlah * harga;
            p.jumlahPesanan = jumlah;
            p.namaPesanan = nama;

            DaftarP[attempt] = p;
            insertStack(p);
            insertQueue(p); 
                        // Insert into tree
            treeRoot = insertTree(treeRoot, p.totalHarga);   
            break;
        case 7:
            harga = 13000;
            nama = "Nasi Liwet";

            cout << "|Anda Memilih Nasi Liwet\n";
            cout << "|Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;

            p.harga = harga;
            p.totalHarga = jumlah * harga;
            p.jumlahPesanan = jumlah;
            p.namaPesanan = nama;

            DaftarP[attempt] = p;
            insertStack(p);
            insertQueue(p);
                        // Insert into tree
            treeRoot = insertTree(treeRoot, p.totalHarga);
            break;
        case 8:
            harga = 13000;
            nama = "Soto Ayam";

            cout << "|Anda Memilih Soto Ayam\n";
            cout << "|Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;

            p.harga = harga;
            p.totalHarga = jumlah * harga;
            p.jumlahPesanan = jumlah;
            p.namaPesanan = nama;

            DaftarP[attempt] = p;
            insertStack(p);
            insertQueue(p);
                        // Insert into tree
            treeRoot = insertTree(treeRoot, p.totalHarga);
            break;
        case 9:
            harga = 13000;
            nama = "Rawon";

            cout << "|Anda Memilih Rawon\n";
            cout << "|Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;

            p.harga = harga;
            p.totalHarga = jumlah * harga;
            p.jumlahPesanan = jumlah;
            p.namaPesanan = nama;

            DaftarP[attempt] = p;
            insertStack(p);
            insertQueue(p);
                        // Insert into tree
            treeRoot = insertTree(treeRoot, p.totalHarga);

            break;
        case 0:
            cout << "\nPesanan Anda Telah Diterima\n";
            break;
        default:
            break;
        }

        attempt++;

    }while(pilihan != 0);

    antrian++;

    int size = sizeof(DaftarP)/sizeof(DaftarP[0]);

    mergeSort(DaftarP, 0, size - 1);

    cout << left << string(19, '-') << " PESANAN ANDA " << right << string(20, '-') << endl;
    cout << left << setw(nameWidth + 3) << "Nama Pesanan" << right << setw(priceWidth) << "Harga" << setw(2 + jumlahWidth) << "jumlah" << setw(totalWidth - 2) << "Total" << endl;
    cout << string(nameWidth + priceWidth + jumlahWidth + totalWidth + 3, '-') << endl;

    for(int i = 0; i < size; i++){
        if(DaftarP != 0)
        cout << i + 1 << ". " << left << setw(nameWidth) << DaftarP[i].namaPesanan << right << setw(priceWidth) << DaftarP[i].harga << setw(jumlahWidth) << DaftarP[i].jumlahPesanan << setw(totalWidth) << DaftarP[i].totalHarga << endl;
        total += DaftarP[i].totalHarga;
    }

    cout << left << string(50, '-') << endl;

    cout << "\nTotal: " << right << setw(46) << total << endl;

}
void Resto::tampilkanMejaKosong() {
    cout << '\n' << '|' << string(59, '-') << '|' << '\n';
    cout << '|' << string(10, '=') << " DAFTAR MEJA KOSONG " << string(10, '=') << '|' << '\n';
    cout << '|' << string(59, '-') << '|' << '\n';
    for (int i = 0; i < SIZE; i++) {
        if (!hashTable[i].isOccupied) {
            cout << "|Meja " << i + 1 << " kosong\n";
        }
    }
    cout << '|' << string(59, '-') << '|' << '\n';
}


void Resto::pesanMenu() {
    int pilihan, jumlahPesanan, harga = 0;
    string namaPesanan;
    int totalHarga;

    const int nameWidth = 20;
    const int priceWidth = 10;
    const int jumlahWidth = 8;
    const int totalWidth = 12;
    const int cornerLeft = 3;

        cout << "\n|-------------------------------------------|\n";
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
        cout << "|Masukkan Pilihan Menu > ";
        cin >> pilihan;
        cout << "|Masukkan Jumlah Pesanan > ";
        cin >> jumlahPesanan;

        switch (pilihan)
        {
        case 1:
            harga = 15000;
            namaPesanan = "Nasi Goreng";
            break;

        case 2: 
            harga = 15000;
            namaPesanan = "Nasi Goreng Ayam";       
            break;

        case 3:
            harga = 10000;
            namaPesanan = "Mie Ayam";
            break;

        case 4:
            harga = 10000;
            namaPesanan = "Mie Ayam Kuah";
            break;

        case 5:
            harga = 10000;
            namaPesanan = "Mie Goreng";
            break;
        case 6:
            harga = 13000;
            namaPesanan = "Nasi Uduk"; 
            break;
        case 7:
            harga = 13000;
            namaPesanan = "Nasi Liwet";
            break;
        case 8:
            harga = 13000;
            namaPesanan = "Soto Ayam";
            break;
        case 9:
            harga = 13000;
            namaPesanan = "Rawon";
            break;
        case 0:
            cout << "\nPesanan Anda Telah Diterima\n";
            break;
        default:
            cout << "Pilihan tidak valid\n";
            return;
            break;
        }
    

    totalHarga = harga * jumlahPesanan;

    pesanan p;
    p.namaPesanan = namaPesanan;
    p.jumlahPesanan = jumlahPesanan;
    p.harga = harga;
    p.totalHarga = totalHarga;

    if (daftarPSize == daftarPCapacity) {
        daftarPCapacity *= 2;
        pesanan* newDaftarP = new pesanan[daftarPCapacity];
        for (int i = 0; i < daftarPSize; i++) {
            newDaftarP[i] = daftarP[i];
        }
        delete[] daftarP;
        daftarP = newDaftarP;
    }
    daftarP[daftarPSize++] = p;

    /*
    cout << "\nPesanan Anda Telah Diterima\n";
    cout << "------------------- PESANAN ANDA --------------------\n";
    cout << "Nama Pesanan                Harga    jumlah     Total\n";
    cout << "-----------------------------------------------------\n";
    cout << left << setw(30) << p.namaPesanan
         << setw(10) << p.harga
         << setw(10) << p.jumlahPesanan
         << setw(10) << p.totalHarga << '\n';
    cout << "-----------------------------------------------------\n";
    cout << "Total: " << setw(45) << right << p.totalHarga << "\n";
    cout << "-----------------------------------------------------\n";

    cout << "\n|1. Lanjutkan Pesanan\n";
    cout << "|0. Kembali ke Menu Utama\n";
    cout << "|Masukkan Pilihan > ";
    cin >> pilihan; */

    cout << left << string(19, '-') << " PESANAN ANDA " << right << string(20, '-') << endl;
    cout << left << setw(nameWidth + 3) << "Nama Pesanan" << right << setw(priceWidth) << "Harga" << setw(2 + jumlahWidth) << "Jumlah" << setw(totalWidth - 2) << "Total" << endl;
    cout << string(nameWidth + priceWidth + jumlahWidth + totalWidth + 3, '-') << endl;

    cout << "- " << left << setw(nameWidth) << p.namaPesanan << right << setw(priceWidth) << p.harga << setw(jumlahWidth) << p.jumlahPesanan << setw(totalWidth) << p.totalHarga << endl;
    /*
    for(int i = 0; i < size; i++){
        cout << i + 1 << ". " << left << setw(nameWidth) << daftarP[i].namaPesanan << right << setw(priceWidth) << daftarP[i].harga << setw(jumlahWidth) << daftarP[i].jumlahPesanan << setw(totalWidth) << daftarP[i].totalHarga << endl;
        total += daftarP[i].totalHarga;
    }*/

    cout << left << string(53, '-') << endl;

    cout << "\nTotal: " << right << setw(45) << p.totalHarga << endl;

    if (pilihan == 1) {
        pesanMenu();
    }

    cout << endl;
}


void Resto::tampilkanPesanan() {
    if (daftarPSize == 0) {
        cout << "\nTidak ada pesanan untuk ditampilkan\n";
        return;
    }

    cout << '\n' << '|' << string(59, '-') << '|' << '\n';
    cout << '|' << string(10, '=') << " DAFTAR PESANAN DAN PEMBAYARAN HARI INI " << string(10, '=') << '|' << '\n';
    cout << '|' << string(59, '-') << '|' << '\n';

    for (int i = 0; i < daftarPSize; i++) {
        cout << "|" << setw(2) << (i + 1) << ". " << setw(15) << left << daftarP[i].namaPesanan
            << "\t" << setw(3) << daftarP[i].jumlahPesanan << " Porsi\t" << "Rp" << daftarP[i].totalHarga << '\n';
    }
    cout << '|' << string(59, '-') << '|' << '\n';
}

void Resto::reservasiMeja() {
    string nama, noHP;
    long int nomerHP;
    int pilihan;

    cout << "\nMasukkan Nama Anda: ";
    cin.ignore();
    getline(cin, nama);
    cout << "Masukkan Nomor HP Anda: ";
    cin >> noHP;

    try {
        nomerHP = stoll(noHP);
    }
    catch (const invalid_argument&) {
        cout << "Nomor HP tidak valid\n";
        return;
    }

    cout << "\n|1. Pesan\n";
    cout << "|0. Kembali ke Menu Utama\n";
    cout << "|Masukkan Pilihan > ";
    cin >> pilihan;

    if (pilihan == 1) {
        hash(nama, nomerHP, pilihan, noHP);
    }
}

void Resto::hash(string nama, long int nomerHP, int pilihan, string noHP) {
    int index = hashFunction(nomerHP);

    if (hashTable[index].isOccupied) {
        int attempt = 1;
        int newIndex;
        do {
            newIndex = quadraticProbing(index, attempt);
            attempt++;
        } while (hashTable[newIndex].isOccupied);

        index = newIndex;
    }

    hashTable[index].nama = nama;
    hashTable[index].nomerHP = nomerHP;
    hashTable[index].noHP = noHP;
    hashTable[index].isOccupied = true;

    cout << "\nReservasi berhasil dilakukan\n";
}

long int Resto::hashFunction(long int nomerHP) {
    return nomerHP % SIZE;
}

int Resto::quadraticProbing(int index, int attempt) {
    return (index + attempt * attempt) % SIZE;
}

void Resto::sort() {
    mergeSort(DaftarP, 0, daftarPSize - 1);
}

void Resto::mergeSort(pesanan* array, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

void Resto::merge(pesanan* array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    pesanan* L = new pesanan[n1];
    pesanan* R = new pesanan[n2];

    for (int i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = array[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].totalHarga <= R[j].totalHarga) {
            array[k] = L[i];
            i++;
        }
        else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void Resto::insertStack(pesanan p) {
    if (stackSize == daftarPCapacity) {
        daftarPCapacity *= 2;
        pesanan* newStackPesanan = new pesanan[daftarPCapacity];
        for (int i = 0; i < stackSize; i++) {
            newStackPesanan[i] = stackPesanan[i];
        }
        delete[] stackPesanan;
        stackPesanan = newStackPesanan;
    }
    stackPesanan[stackSize++] = p;
}

void Resto::insertQueue(pesanan p) {
    if (queueSize == daftarPCapacity) {
        daftarPCapacity *= 2;
        pesanan* newQueuePesanan = new pesanan[daftarPCapacity];
        for (int i = 0; i < queueSize; i++) {
            newQueuePesanan[i] = queuePesanan[i];
        }
        delete[] queuePesanan;
        queuePesanan = newQueuePesanan;
    }
    queuePesanan[queueRear] = p;
    queueRear = (queueRear + 1) % daftarPCapacity;
    queueSize++;
}

Resto::TreeNode* Resto::insertTree(TreeNode* node, int data) {
    if (node == nullptr) {
        return new TreeNode(data);
    }

    if (data < node->data) {
        node->left = insertTree(node->left, data);
    }
    else if (data > node->data) {
        node->right = insertTree(node->right, data);
    }

    return node;
}

void Resto::inorder(TreeNode* node) {
    if (node == nullptr) return;
    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}

void Resto::preorder(TreeNode* node) {
    if (node == nullptr) return;
    cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
}

void Resto::postorder(TreeNode* node) {
    if (node == nullptr) return;
    postorder(node->left);
    postorder(node->right);
    cout << node->data << " ";
}

void Resto::displayTree() {
    cout << "\nTree Inorder: ";
    inorder(treeRoot);
    cout << "\nTree Preorder: ";
    preorder(treeRoot);
    cout << "\nTree Postorder: ";
    postorder(treeRoot);
    cout << endl;
}

void Resto::createGraph() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i != j) {
                graph.addEdge(i, j);
            }
        }
    }
}

void Resto::tampilkanAntrian() {
    if (queueSize == 0) {
        cout << "\nTidak ada antrian untuk ditampilkan\n";
        return;
    }

    cout << '\n' << '|' << string(59, '-') << '|' << '\n';
    cout << '|' << string(10, '=') << " DAFTAR ANTRIAN " << string(10, '=') << '|' << '\n';
    cout << '|' << string(59, '-') << '|' << '\n';

    int count = 1;
    for (int i = queueFront; i != queueRear; i = (i + 1) % daftarPCapacity) {
        cout << "|" << setw(2) << count << ". " << setw(15) << left << queuePesanan[i].namaPesanan
            << "\t" << setw(3) << queuePesanan[i].jumlahPesanan << " Porsi\t" << "Rp" << queuePesanan[i].totalHarga << '\n';
        count++;
    }

    cout << '|' << string(59, '-') << '|' << '\n';
}

void Resto::tampilkanReservasiMeja() {
    cout << '\n' << '|' << string(59, '-') << '|' << '\n';
    cout << '|' << string(10, '=') << " DAFTAR RESERVASI MEJA " << string(10, '=') << '|' << '\n';
    cout << '|' << string(59, '-') << '|' << '\n';

    for (int i = 0; i < SIZE; i++) {
        if (hashTable[i].isOccupied) {
            cout << "|Meja " << i + 1 << ": " << hashTable[i].nama << ", Nomor HP: " << hashTable[i].noHP << '\n';
        }
    }

    cout << '|' << string(59, '-') << '|' << '\n';
}

void Resto::tampilkanReservasiRuangan() {
    cout << '\n' << '|' << string(59, '-') << '|' << '\n';
    cout << '|' << string(10, '=') << " DAFTAR RESERVASI RUANGAN " << string(10, '=') << '|' << '\n';
    cout << '|' << string(59, '-') << '|' << '\n';

    for (int i = 0; i < SIZE; i++) {
        if (ruang[i].head != nullptr) {
            Node* current = ruang[i].head;
            while (current != nullptr) {
                cout << "|Ruangan " << i + 1 << ": " << current->name << '\n';
                current = current->next;
            }
        }
    }

    cout << '|' << string(59, '-') << '|' << '\n';
}

void Resto::reservasiRuangan() {
    string nama, noHP;
    long int nomerHP;
    int pilihan, ruanganNo;

    cout << "\nMasukkan Nama Anda: ";
    cin.ignore();
    getline(cin, nama);
    cout << "Masukkan Nomor HP Anda: ";
    cin >> noHP;

    try {
        nomerHP = stoll(noHP);
    }
    catch (const invalid_argument&) {
        cout << "Nomor HP tidak valid\n";
        return;
    }

    cout << "\nMasukkan Nomor Ruangan (1-10): ";
    cin >> ruanganNo;

    if (ruanganNo < 1 || ruanganNo > 10) {
        cout << "Nomor ruangan tidak valid\n";
        return;
    }

    ruanganNo--;

    Node* newNode = new Node();
    newNode->name = nama;
    newNode->key = noHP;
    newNode->next = nullptr;

    if (ruang[ruanganNo].head == nullptr) {
        ruang[ruanganNo].head = newNode;
        newNode->prev = nullptr;
    }
    else {
        Node* current = ruang[ruanganNo].head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }

    cout << "\nReservasi berhasil dilakukan\n";
}

void Resto::hash2(string nama, long int nomerHP, int pilihan, string noHP) {
    int index = hashFunction(nomerHP);

    if (hashTable[index].isOccupied) {
        int attempt = 1;
        int newIndex;
        do {
            newIndex = quadraticProbing2(index, attempt);
            attempt++;
        } while (hashTable[newIndex].isOccupied);

        index = newIndex;
    }

    hashTable[index].nama = nama;
    hashTable[index].nomerHP = nomerHP;
    hashTable[index].noHP = noHP;
    hashTable[index].isOccupied = true;

    cout << "\nReservasi berhasil dilakukan\n";
}

int Resto::quadraticProbing2(int index, int attempt) {
    return (index + attempt * attempt) % SIZE;
}

void Resto::tampilkanLetakMeja() {
    cout << '\n' << '|' << string(59, '-') << '|' << '\n';
    cout << '|' << string(10, '=') << " LETAK MEJA " << string(10, '=') << '|' << '\n';
    cout << '|' << string(59, '-') << '|' << '\n';
    graph.bfs(0);
}

int Resto::sumTree(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->data + sumTree(node->left) + sumTree(node->right);
}

int Resto::getTotalIncome() {
    return sumTree(treeRoot);
}

void Resto::tampilkanRuangKosong() {
    cout << '\n' << '|' << string(59, '-') << '|' << '\n';
    cout << '|' << string(10, '=') << " DAFTAR RUANGAN KOSONG " << string(10, '=') << '|' << '\n';
    cout << '|' << string(59, '-') << '|' << '\n';

    for (int i = 0; i < SIZE; i++) {
        if (ruang[i].head == nullptr) {
            cout << "|Ruangan " << i + 1 << " kosong\n";
        }
    }

    cout << '|' << string(59, '-') << '|' << '\n';
}