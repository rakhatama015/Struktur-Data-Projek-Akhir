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
        string nohp;
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
        TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}    };

    
   TreeNode* insertTree(TreeNode* node, int data) {
        if (node == nullptr) {
            node = new TreeNode(data); // Menggunakan konstruktor dengan argumen
        } else if (data <= node->data) {
            node->left = insertTree(node->left, data);
        } else {
            node->right = insertTree(node->right, data);
        }
        return node;
    }
    int sumTree(TreeNode* node) {
        if (node == nullptr) return 0;
        return node->data + sumTree(node->left) + sumTree(node->right);
    }
    void inorder(TreeNode* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    // Fungsi rekursif untuk traversal preorder
    void preorder(TreeNode* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    // Fungsi rekursif untuk traversal postorder
    void postorder(TreeNode* node) {
        if (node == nullptr) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }
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
    void insertTreeData(int data) {
        treeRoot = insertTree(treeRoot, data);
    }
    void hash(string nama, long int nomerHP, int pilihan, string noHP);
    long int hashFunction(long int nomerHP);
    int quadraticProbing(int nomerHP, int attempt);
    void sort();
    void mergeSort(pesanan*, int left, int right);
    void merge(pesanan*, int left, int mid, int right);

    int getTotalIncome() {
        return sumTree(treeRoot);
    }
    void insertStack(pesanan p);
    void insertQueue(pesanan p);
    
    void createGraph();
    void displayStack() {
        cout << "\n|PESANAN|\n";
        for (int i = stackSize - 1; i >= 0; i--) {
            cout << "| Pesanan: " << stackPesanan[i].namaPesanan 
                 << " | Jumlah: " << stackPesanan[i].jumlahPesanan 
                 << " | Total Harga: " << stackPesanan[i].totalHarga << endl;
        }
    }
    void popStack() {
        if (stackSize == 0) {
            cout << "| Stack kosong.\n";
        } else {
            stackSize--;
            cout << "| Pesanan terakhir dihapus dari stack.\n";
        }
    }
    void displayTree() {
        cout << "\nUang Yang Masuk: ";
        preorder(treeRoot);
        cout << endl;
    }
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
        cout << "|1. Tampilkan Pesanan\n";
        cout << "|2. Urutkan Pesanan\n";
        cout << "|3. Tampilkan Reservasi Meja\n";
        cout << "|4. Tampilkan Reservasi Ruangan\n";
        cout << "|5. Tampikan Daftar Pesanan dan Pembayaran Hari Ini\n";
        cout << "|6. Tampilkan Total Uang Masuk Hari Ini\n";
        cout << "|7. Histori Pesanan\n";
        cout << "|8. Hapus Pesanan Terakhir\n";
        cout << "|0. Keluar\n";
        cout << "|Masukkan Pilihan > ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            displayStack();
            break;
        case 2:
            sort();
            break;
        case 3:
            tampilkanReservasiMeja();
            break;
        case 4:
            tampilkanReservasiRuangan();
            break;
        case 5:
            tampilkanPesanan();
            break;
        case 6:
            displayTree();
            cout << "\nTotal uang masuk hari ini: " << getTotalIncome() << " Rupiah" << endl;
            break;
        case 7:
            tampilkanAntrian();
            break;
        case 8:
            popStack();
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
        cout << '|' << string(75, '-') << '|' << endl;
        cout << '|' << string(20, '=') << " SELAMAT DATANG DI RESTAURANT KAMI " << string(20, '=') << '|' << endl;
        cout << '|' << string(75, '-') << '|' << endl;
        cout << "|1. Pesan Menu\n";
        cout << "|2. Reservasi Meja\n";
        cout << "|3. Reservasi Ruangan\n";
        cout << "|4. Tampilkan Daftar Menu\n";
        cout << "|5. Tampilkan Meja Kosong\n";
        cout << "|6. Tampilkan Ruang Kosong\n";
        cout << "|7. Tampilkan Letak Meja\n";
        cout << "|0. Keluar\n";
        cout << "|Masukkan Pilihan > ";
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
            menuList();
            break;
        case 5:
            tampilkanMejaKosong();
            break;
        case 6:
            tampilkanRuangKosong();
            break;
        case 7:
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
    cout << '\n' << '|' << string(59, '-') << '|' << '\n';
    cout << '|' << string(10, '=') << " DAFTAR MENU RESTORAN KAMI " << string(10, '=') << '|' << '\n';
    cout << '|' << string(59, '-') << '|' << '\n';
    cout << "|1. Nasi Goreng\t\t\tRp15,000\n";
    cout << "|2. Mie Goreng\t\t\tRp12,000\n";
    cout << "|3. Ayam Goreng\t\t\tRp20,000\n";
    cout << "|4. Ikan Bakar\t\t\tRp25,000\n";
    cout << "|5. Teh Manis\t\t\tRp5,000\n";
    cout << '|' << string(59, '-') << '|' << '\n';
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

    menuList();
    cout << "\nMasukkan Pilihan Menu: ";
    cin >> pilihan;
    cout << "Masukkan Jumlah Pesanan: ";
    cin >> jumlahPesanan;

    switch (pilihan) {
        case 1:
            namaPesanan = "Nasi Goreng";
            harga = 15000;
            break;
        case 2:
            namaPesanan = "Mie Goreng";
            harga = 12000;
            break;
        case 3:
            namaPesanan = "Ayam Goreng";
            harga = 20000;
            break;
        case 4:
            namaPesanan = "Ikan Bakar";
            harga = 25000;
            break;
        case 5:
            namaPesanan = "Teh Manis";
            harga = 5000;
            break;
        default:
            cout << "Pilihan tidak valid\n";
            return;
    }

    totalHarga = harga * jumlahPesanan;

    pesanan p;
    p.namaPesanan = namaPesanan;
    p.jumlahPesanan = jumlahPesanan;
    p.harga = harga;
    p.totalHarga = totalHarga;
    insertTreeData(totalHarga);
    // Masukkan pesanan ke dalam daftar pesanan
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
    
    // Masukkan pesanan ke dalam antrian
    insertQueue(p);
    insertStack(p);

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
    cin >> pilihan;

    if (pilihan == 1) {
        pesanMenu();
    }
}

void Resto::tampilkanPesanan() {
    if (queueSize == 0) {
        cout << "\nTidak ada pesanan untuk ditampilkan\n";
        return;
    }

    cout << '\n' << '|' << string(59, '-') << '|' << '\n';
    cout << '|' << string(10, '=') << " DAFTAR PESANAN DAN PEMBAYARAN HARI INI " << string(10, '=') << '|' << '\n';
    cout << '|' << string(59, '-') << '|' << '\n';

    int count = 1;
    for (int i = queueFront; i != queueRear; i = (i + 1) % daftarPCapacity) {
        cout << "|" << setw(2) << count << ". " << setw(15) << left << queuePesanan[i].namaPesanan
            << "\t" << setw(3) << queuePesanan[i].jumlahPesanan << " Porsi\t" << "Rp" << queuePesanan[i].totalHarga << '\n';
        count++;
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
    cout << "Anda Mendapat Meja Nomor " << index + 1 << "\n";
}

long int Resto::hashFunction(long int nomerHP) {
    return nomerHP % SIZE;
}

int Resto::quadraticProbing(int index, int attempt) {
    return (index + attempt * attempt) % SIZE;
}

void Resto::sort() {
    mergeSort(daftarP, 0, daftarPSize - 1);

    // Menampilkan hasil setelah pengurutan
    cout << '\n' << '|' << string(59, '-') << '|' << '\n';
    cout << '|' << string(10, '=') << " DAFTAR PESANAN HARI INI SETELAH DIURUTKAN " << string(10, '=') << '|' << '\n';
    cout << '|' << string(59, '-') << '|' << '\n';

    for (int i = 0; i < daftarPSize; i++) {
        cout << "| " << i + 1 << ". " 
             << left << setw(15) << daftarP[i].namaPesanan 
             << setw(6) << daftarP[i].jumlahPesanan << " Porsi       Rp" 
             << right << setw(5) << daftarP[i].totalHarga << '\n';
    }

    cout << '|' << string(59, '-') << '|' << '\n';
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
                cout << "|Ruangan " << i + 1 << ": " << current->name << ", No HP: " << current->nohp << '\n';
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
    newNode->nohp = noHP;
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