#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <queue>
#include <stack>
#include <unordered_map>
#include <list>

using namespace std;

#define SIZE 10

// Struct Pesanan
struct pesanan {
    int jumlahPesanan;
    int harga;
    int totalHarga;
    string namaPesanan;
};

// Struct Node untuk Linked List
struct node {
    int key;
    string name;
    node* prev;
    node* next;
};

// Struct Ruangan
struct ruangan {
    node* head;
};

// Struct untuk Node Tree
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Struct untuk Graph
struct Graph {
    unordered_map<int, list<int>> adjList;

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Karena ini graph tak berarah
    }

    void BFS(int start) {
        unordered_map<int, bool> visited;
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (auto neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
    }

    void DFSUtil(int node, unordered_map<int, bool>& visited) {
        visited[node] = true;
        cout << node << " ";

        for (auto neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }

    void DFS(int start) {
        unordered_map<int, bool> visited;
        DFSUtil(start, visited);
    }
};

class Resto {
private:
    vector<pesanan> daftarP;
    ruangan ruang[SIZE];
    int antrian;

    // Untuk Stack dan Queue
    stack<pesanan> stackPesanan;
    queue<pesanan> queuePesanan;

    TreeNode* treeRoot;

public:
    Resto() : antrian(0), treeRoot(nullptr) {
        for (int i = 0; i < SIZE; ++i) {
            ruang[i].head = nullptr;
        }
    }

    void menuList();
    void pesanMenu();
    void tampilkanPesanan();
    void reservasiMeja();

    void hash(string nama, int nomerHP, int pilihan);
    int hashFunction(int nomerHP);
    int quadraticProbing(int nomerHP, int attempt);
    void sort();
    void mergeSort(vector<pesanan>&, int left, int right);
    void merge(vector<pesanan>&, int left, int mid, int right);

    void queue();
    void stack();
    void insertStack(pesanan p);
    void insertQueue(pesanan p);
    void pelanggan();
    void admin();

    void searchPesanan(string nama);

    // Tree operations
    TreeNode* insertTree(TreeNode* node, int data);
    void inorder(TreeNode* node);
    void preorder(TreeNode* node);
    void postorder(TreeNode* node);
    void displayTree();

    // Graph operations
    Graph graph;
    void createGraph();
};

int main() {
    Resto resto;
    string nama, password, adminName = "admin", adminPass = "admin123";
    int pilihan;

    cout << "Selamat datang aplikasi resto, silahkan anda pilih anda sebagai apa\n";
    cout << "1. Admin\n";
    cout << "2. Pelanggan\n";
    cout << "0. Keluar\n";
    cout << "Masukkan Pilihan Anda > ";
    cin >> pilihan;
    cin.ignore();

    switch (pilihan) {
    case 1:
        cout << "Masukkan Nama Anda: ";
        getline(cin, nama);
        cout << "Masukkan Password: ";
        getline(cin, password);

        if (nama == adminName && password == adminPass) {
            resto.admin();
        } else {
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

void Resto::admin() {
    int pilihan;
    cout << "Selamat datang admin, silahkan pilih menu anda\n";
    cout << "1. Tampilkan antrian\n";
    cout << "2. Tampilkan reservasi\n";
    cout << "3. Tampikan Daftar Pesanan dan Pembayaran hari ini\n";
    cout << "4. Tampilkan Tree Pesanan\n";
    cout << "5. Tampilkan Graph\n";
    cout << "0. Keluar\n";
    cin >> pilihan;

    switch (pilihan) {
    case 1:
        // Implementasi tampilkan antrian
        break;
    case 2:
        // Implementasi tampilkan reservasi
        break;
    case 3:
        tampilkanPesanan();
        break;
    case 4:
        displayTree();
        break;
    case 5:
        cout << "BFS dari node 1: ";
        graph.BFS(1);
        cout << "\nDFS dari node 1: ";
        graph.DFS(1);
        cout << endl;
        break;
    case 0:
        break;
    default:
        break;
    }
}

void Resto::pelanggan() {
    int pilihan;
    cout << '|' << string(75, '-') << '|' << endl;
    cout << '|' << string(20, '=') << " SELAMAT DATANG DI RESTAURANT KAMI " << string(20, '=') << '|' << endl;
    cout << '|' << string(75, '-') << '|' << endl;
    cout << "|1. Menu Makanan" << right << setw(61) << '|' << endl;
    cout << "|2. Reservasi Meja" << right << setw(61) << '|' << endl;
    cout << "|3. Reservasi Ruangan\n";
    cout << "|4. Tampilkan Meja Kosong\n";
    cout << "|5. Tampilkan Letak Meja di restauran\n";
    cout << "|0. Keluar\n";
    cout << "|Masukkan Pilihan Anda > ";
    cin >> pilihan;

    switch (pilihan) {
    case 1:
        menuList();
        break;
    default:
        break;
    }
}

void Resto::menuList() {
    int pilihan, jumlah, harga;
    string nama;
    pesanan p;

    do {
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

        switch (pilihan) {
        case 1:
            harga = 15000;
            nama = "Nasi Goreng Jawa";
            break;
        case 2:
            harga = 15000;
            nama = "Nasi Goreng Ayam";
            break;
        case 3:
            harga = 10000;
            nama = "Mie Ayam";
            break;
        case 4:
            harga = 10000;
            nama = "Mie Ayam Kuah";
            break;
        case 5:
            harga = 10000;
            nama = "Mie Goreng";
            break;
        case 6:
            harga = 12000;
            nama = "Nasi Uduk";
            break;
        case 7:
            harga = 12000;
            nama = "Nasi Liwet";
            break;
        case 8:
            harga = 12000;
            nama = "Soto Ayam";
            break;
        case 9:
            harga = 12000;
            nama = "Rawon";
            break;
        case 0:
            cout << "Pesanan Anda Telah Diterima\n";
            break;
        default:
            continue;
        }

        if (pilihan != 0) {
            cout << "Masukkan Jumlah Yang Ingin Dipesan: ";
            cin >> jumlah;

            p.harga = harga;
            p.totalHarga = jumlah * harga;
            p.jumlahPesanan = jumlah;
            p.namaPesanan = nama;

            daftarP.push_back(p);
            insertStack(p);
            insertQueue(p);

            // Insert into tree
            treeRoot = insertTree(treeRoot, p.totalHarga);
        }

    } while (pilihan != 0);

    antrian++;

    mergeSort(daftarP, 0, daftarP.size() - 1);

    // Display sorted orders
    cout << left << string(19, '-') << " PESANAN ANDA " << right << string(20, '-') << endl;
    const int nameWidth = 20;
    const int priceWidth = 10;
    const int jumlahWidth = 8;
    const int totalWidth = 12;
    cout << left << setw(nameWidth + 3) << "Nama Pesanan" << right << setw(priceWidth) << "Harga" << setw(2 + jumlahWidth) << "jumlah" << setw(totalWidth - 2) << "Total" << endl;
    cout << string(nameWidth + priceWidth + jumlahWidth + totalWidth + 3, '-') << endl;

    for (int i = 0; i < daftarP.size(); i++) {
        cout << i + 1 << ". " << left << setw(nameWidth) << daftarP[i].namaPesanan << right << setw(priceWidth) << daftarP[i].harga << setw(jumlahWidth) << daftarP[i].jumlahPesanan << setw(totalWidth) << daftarP[i].totalHarga << endl;
    }
}

void Resto::mergeSort(vector<pesanan>& p, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(p, left, mid);
        mergeSort(p, mid + 1, right);
        merge(p, left, mid, right);
    }
}

void Resto::merge(vector<pesanan>& p, int left, int mid, int right) {
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

void Resto::reservasiMeja() {
    string nama, noHP;
    int pilihan;

    cout << "Masukkan Nama Anda: ";
    cin.ignore();
    getline(cin, nama);
    cout << "Masukkan Nomor HP Anda: ";
    getline(cin, noHP);

    int nomerHP = stoi(noHP);
    int i = hashFunction(nomerHP);

    if (ruang[i].head != nullptr) {
        cout << "Meja Sudah Di Pesan, Apakah Anda Ingin Antri Atau Dipindah Ke Meja Lain?\n";
        cout << "1. Antri\n";
        cout << "2. Pindah\n";
        cin >> pilihan;
    }

    hash(nama, nomerHP, pilihan);
}

void Resto::hash(string nama, int nomerHP, int pilihan) {
    int index = hashFunction(nomerHP);
    int attempt = 0;

    if (pilihan == 1) {
        node* newNode = new node;
        newNode->name = nama;
        newNode->key = nomerHP;
        newNode->prev = nullptr;
        newNode->next = nullptr;

        if (ruang[index].head == nullptr) {
            ruang[index].head = newNode;
        } else {
            node* temp = ruang[index].head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
    } else if (pilihan == 2) {
        index = quadraticProbing(nomerHP, attempt);
        if (index != -1) {
            node* newNode = new node;
            newNode->name = nama;
            newNode->key = nomerHP;
            newNode->prev = nullptr;
            newNode->next = nullptr;

            ruang[index].head = newNode;
        } else {
            cout << "Hash table sudah penuh, tidak dapat menambahkan data baru." << endl;
        }
    }
}

int Resto::hashFunction(int nomerHP) {
    return abs(nomerHP) % SIZE;
}

int Resto::quadraticProbing(int nomerHP, int attempt) {
    int index = hashFunction(nomerHP);
    int probeIndex = index;

    for (int i = 1; i < SIZE; i++) {
        probeIndex = (index + attempt * attempt) % SIZE;
        if (ruang[probeIndex].head == nullptr) {
            return probeIndex;
        }
        attempt++;
    }

    return -1; // Semua bucket terisi, tidak ada tempat untuk menambahkan data baru
}

void Resto::insertStack(pesanan p) {
    stackPesanan.push(p);
}

void Resto::insertQueue(pesanan p) {
    queuePesanan.push(p);
}

void Resto::searchPesanan(string nama) {
    for (const auto& p : daftarP) {
        if (p.namaPesanan == nama) {
            cout << "Pesanan ditemukan: " << p.namaPesanan << " - Jumlah: " << p.jumlahPesanan << " - Total Harga: " << p.totalHarga << endl;
            return;
        }
    }
    cout << "Pesanan tidak ditemukan." << endl;
}

TreeNode* Resto::insertTree(TreeNode* node, int data) {
    if (node == nullptr) {
        return new TreeNode(data);
    }

    if (data < node->data) {
        node->left = insertTree(node->left, data);
    } else {
        node->right = insertTree(node->right, data);
    }

    return node;
}

void Resto::inorder(TreeNode* node) {
    if (node != nullptr) {
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }
}

void Resto::preorder(TreeNode* node) {
    if (node != nullptr) {
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }
}

void Resto::postorder(TreeNode* node) {
    if (node != nullptr) {
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }
}

void Resto::displayTree() {
    cout << "Inorder Traversal: ";
    inorder(treeRoot);
    cout << "\nPreorder Traversal: ";
    preorder(treeRoot);
    cout << "\nPostorder Traversal: ";
    postorder(treeRoot);
    cout << endl;
}

void Resto::createGraph() {
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);
    graph.addEdge(4, 5);
}

