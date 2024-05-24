#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <math.h>
#include <iomanip>
#include <queue>
#include <stack>

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
        struct node{
            string key;
            string name;
            node* prev;
            node* next;
        };
        struct bangku{
            node* head;
        };
        struct Node{
            string key;
            string name;
            node* prev;
            node* next;
        };
        struct ruangan{
            Node* head;
        };
        struct TreeNode {
            int data;
            TreeNode* left;
            TreeNode* right;
            TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
        };
        struct Graph {
            vector<vector<int>> adjList;
            Graph(int n) {
                adjList.resize(n);
            }
            void addEdge(int u, int v) {
                adjList[u].push_back(v);
                adjList[v].push_back(u);
            }
            void bfs(int start) {
                vector<bool> visited(adjList.size(), false);
                queue<int> q;
                q.push(start);
                visited[start] = true;
                while (!q.empty()) {
                    int node = q.front();
                    q.pop();
                    cout << node << " ";
                    for (int neighbor : adjList[node]) {
                        if (!visited[neighbor]) {
                            q.push(neighbor);
                            visited[neighbor] = true;
                        }
                    }
                }
                cout << endl;
            }
            void dfsUtil(int node, vector<bool>& visited) {
                visited[node] = true;
                cout << node << " ";
                for (int neighbor : adjList[node]) {
                    if (!visited[neighbor]) {
                        dfsUtil(neighbor, visited);
                    }
                }
            }
            void dfs(int start) {
                vector<bool> visited(adjList.size(), false);
                dfsUtil(start, visited);
                cout << endl;
            }
        };

        int antrian;
        vector<pesanan> daftarP;

        stack<pesanan> stackPesanan;
        queue<pesanan> queuePesanan;
        TreeNode* treeRoot;
        Graph graph;

    public:
        bangku meja[SIZE] = { nullptr };
        ruangan ruang[SIZE] = { nullptr };
        Resto() : treeRoot(nullptr), graph(SIZE) {}
        void menuList();
        void pesanMenu();
        void tampilkanPesanan();
        void reservasiMeja();

        void hash(string nama, long int nomerHP, int pilihan, string noHP);
        long int hashFunction(long int nomerHP);
        int quadraticProbing(int nomerHP, int attempt);
        void sort();
        void mergeSort(vector<pesanan>&, int left, int right);
        void merge(vector<pesanan>&, int left, int mid, int right);

        void insertStack(pesanan p);
        void insertQueue(pesanan p);
        void searchPesanan(string nama);
        TreeNode* insertTree(TreeNode* node, int data);
        void inorder(TreeNode* node);
        void preorder(TreeNode* node);
        void postorder(TreeNode* node);
        void displayTree();
        void createGraph();

        void pelanggan();
        void admin();
        void tampilkanAntrian();
        void tampilkanReservasi();

        void reservasiRuangan();
        void hash2(string nama, long int nomerHP, int pilihan, string noHP);
        int quadraticProbing2(int nomerHP, int attempt);
};

int main(){
    Resto resto;
    string nama, password, adminName = "admin", adminPass = "password";
    int pilihan, pilihan2;

    do{
        cout << "|" << string(59, '-') << "|" << '\n';
        cout << "|" << string(10, '=') << " SELAMAT DATANG DI APLIKASI RESTO KAMI " << string(10, '=') << "|" << '\n';
        cout << "|" << string(59, '-') << "|" << '\n';
        cout << "|1. Admin\n";
        cout << "|2. Pelanggan\n";
        cout << "|0. Keluar\n";
        cout << "|Masukkan Pilihan Anda > ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:

            do{
                cout << "\n|Masukkan Nama Anda: ";
                cin.ignore();
                getline(cin, nama);
                cout << "|Masukkan Password: ";
                getline(cin, password);

                if(nama == adminName && password == adminPass){
                    resto.admin();
                }
                else{
                    cout << "Sandi Salah\n";
                }
                cout << "\n|1. Ulang\n";
                cout << "|0. Keluar\n";
                cout << "|> ";
                cin >> pilihan2;
            }while(pilihan2 != 0);

            break;
        case 2:

            do{
                cout << '\n';
                resto.pelanggan();
                cout << "\n|1. Ulang\n";
                cout << "|0. Keluar\n";
                cout << "|> ";
                cin >> pilihan2;
            }while(pilihan2 != 0);

            break;
        case 0: 
            cout << '\n' << string(10, '-') << " Anda Memilih Keluar " << string(10, '-') << '\n';
            break;
        default:
            break;
        }
    }while(pilihan != 0);

    return 0;
}

void Resto::admin(){
    int pilihan;
    do{
        cout << endl;
        cout << '|' << string(42, '=') << '|' <<'\n';
        cout << '|' << string(10, '=') << " SELAMAT DATANG ADMIN " << string(10, '=') << '|' <<'\n';
        cout << '|' << string(42, '=') << '|' <<'\n';
        cout << "|1. Tampilkan antrian\n";
        cout << "|2. Tampilkan reservasi\n";
        cout << "|3. Tampikan Daftar Pesanan dan Pembayaran hari ini\n";
        cout << "|0. Keluar\n";
        cout << "|Masukkan Pilihan > ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tampilkanAntrian();
            break;
        case 2:
            tampilkanReservasi();
            break;
        case 3:
            tampilkanPesanan();
            break;
        case 0:
            break;
        default:
            cout << "Pilihan tidak valid" << endl;
            break;
        }
    }while(pilihan != 0);
}

void Resto::pelanggan(){
    int pilihan;
    do{
        cout << '|' << string(75, '-')  << '|' << endl;
        cout << '|' << string(20, '=') << " SELAMAT DATANG DI RESTAURANT KAMI " << string(20, '=') << '|' << endl;
        cout << '|' << string(75, '-') << '|' << endl;
        cout << left << setw(37) << "|1. Menu Makanan" << right << setw(40) << '|' << endl;
        cout << left << setw(37) << "|2. Reservasi Meja" << right << setw(40) << '|' << endl;
        cout << left << setw(37) << "|3. Reservasi Ruangan" << right << setw(40) << '|' << '\n';
        cout << left << setw(37) << "|4. Tampilkan Meja Kosong" << right << setw(40) << '|' << '\n';
        cout << left << setw(37) << "|5. Tampilkan Letak Meja di restauran" << right << setw(40) << '|' << '\n';
        cout << left << setw(37) << "|0. Keluar" << right << setw(40) << '|' << '\n';
        cout << "|Masukkan Pilihan Anda > ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            menuList();
            break;
        case 2:
            reservasiMeja();
            break;
        case 3:
            reservasiRuangan();
            break;
        case 4:
            tampilkanReservasi();
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            break;
        }
    }while(pilihan != 0);
}

void Resto::menuList(){
    int pilihan, jumlah, harga, total = 0, attempt = 0;
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
            cout << "|Masukkan Jumlah Yang Ingin Dipesan: ";
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

            daftarP.push_back(p);
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

            daftarP.push_back(p);
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

            daftarP.push_back(p);
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

            daftarP.push_back(p);
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

            daftarP.push_back(p);
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

            daftarP.push_back(p);
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

            daftarP.push_back(p);
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

            daftarP.push_back(p);
            insertStack(p);
            insertQueue(p);
                        // Insert into tree
            treeRoot = insertTree(treeRoot, p.totalHarga);

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
        total += daftarP[i].totalHarga;
    }

    cout << left << string(50, '-') << endl;

    cout << "\nTotal: " << right << setw(46) << total;

    cout << "\nTraversal Tree Pesanan (Total Harga):" << endl;
    displayTree();

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

void Resto::reservasiMeja() {
    string nama, noHP;
    int pilihan;

    cout << "|Masukkan Nama Anda: ";
    cin.ignore();
    getline(cin, nama);
    cout << "|Masukkan Nomor HP Anda: ";
    getline(cin, noHP);

    long int nomerHP = stoll(noHP);

    long int index = hashFunction(nomerHP);

    if(meja[index].head != nullptr && meja[index].head->name != "") {
        cout << "Meja Sudah Di Pesan, Apakah Anda Ingin Antri Atau Dipindah Ke Meja Lain?\n";
        cout << "1. Antri\n";
        cout << "2. Pindah\n";
        cin >> pilihan;
    } else {
        pilihan = 2; // Jika meja kosong, langsung pilih opsi pindah
    }

    hash(nama, nomerHP, pilihan, noHP);

    cout << "|Meja Berhasil Di Reservasi|\n";
    cout << "|Anda Mendapat Meja Nomor " << index << " |\n";
}

void Resto::hash(string nama, long int nomerHP, int pilihan, string noHP) {
    long int index = hashFunction(nomerHP);
    int attempt = 0;
    
    if(pilihan == 1) {
        node* newNode = new node;
        newNode->name = nama;
        newNode->key = noHP;
        newNode->prev = nullptr;
        newNode->next = nullptr;

        if (meja[index].head == nullptr) {
            meja[index].head = newNode;
        } else {
            node* temp = meja[index].head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
    } else if(pilihan == 2) {
        index = quadraticProbing(nomerHP, attempt);

        if (index != -1) {
            node* newNode = new node;
            newNode->name = nama;
            newNode->key = noHP;
            newNode->prev = nullptr;
            newNode->next = nullptr;

            meja[index].head = newNode;
        } else {
            cout << "Meja Sudah Penuh" << endl;
        }
    }
}

long int Resto::hashFunction(long int nomerHP){
    return abs(nomerHP) % SIZE;
}

int Resto::quadraticProbing(int nomerHP, int attempt) {
    int index = hashFunction(nomerHP);
    int probeIndex = index;

    for (int i = 1; i < SIZE; i++) {
        probeIndex = (index + attempt * attempt) % SIZE;
        if (meja[probeIndex].head == nullptr) {
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

Resto::TreeNode* Resto::insertTree(TreeNode* node, int data) {
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
    cout << "Inorder traversal: ";
    inorder(treeRoot);
    cout << endl;
    cout << "Preorder traversal: ";
    preorder(treeRoot);
    cout << endl;
    cout << "Postorder traversal: ";
    postorder(treeRoot);
    cout << endl;
}

void Resto::createGraph() {
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 5);
    graph.addEdge(2, 6);

    cout << "BFS traversal: ";
    graph.bfs(0);

    cout << "DFS traversal: ";
    graph.dfs(0);
}

void Resto::tampilkanAntrian() {
    if (queuePesanan.empty()) {
        cout << '\n' << string(10, '-') << "Tidak ada antrian saat ini." << string(10, '-') << endl;
    } else {
        cout << '\n' << string(10, '-') <<"Daftar antrian pesanan:" << string(10, '-') << endl;
        queue<pesanan> tempQueue = queuePesanan;
        while (!tempQueue.empty()) {
            pesanan p = tempQueue.front();
            tempQueue.pop();
            cout << p.namaPesanan << " - Jumlah: " << p.jumlahPesanan << " - Total: " << p.totalHarga << endl;
        }
    }
}

void Resto::tampilkanReservasi() {
    cout << "Daftar reservasi meja:" << endl;
    for (int i = 0; i < SIZE; i++) {
        if (meja[i].head != nullptr) {
            node* temp = meja[i].head;
            cout << "Meja " << i + 1 << ": ";
            while (temp != nullptr) {
                cout << temp->name << " - No HP: " << temp->key;
                if (temp->next != nullptr) {
                    cout << ", ";
                }
                temp = temp->next;
            }
            cout << endl;
        } else {
            cout << "Meja " << i + 1 << ": Kosong" << endl;
        }
    }
}

void Resto::tampilkanPesanan() {
    if (daftarP.empty()) {
        cout << "Belum ada pesanan." << endl;
        return;
    }

    const int nameWidth = 20;
    const int priceWidth = 10;
    const int jumlahWidth = 8;
    const int totalWidth = 12;

    cout << left << string(19, '-') << " DAFTAR PESANAN " << right << string(20, '-') << endl;
    cout << left << setw(nameWidth + 3) << "Nama Pesanan" << right << setw(priceWidth) << "Harga" << setw(2 + jumlahWidth) << "Jumlah" << setw(totalWidth - 2) << "Total" << endl;
    cout << string(nameWidth + priceWidth + jumlahWidth + totalWidth + 3, '-') << endl;

    for (int i = 0; i < daftarP.size(); i++) {
        cout << i + 1 << ". " << left << setw(nameWidth) << daftarP[i].namaPesanan << right << setw(priceWidth) << daftarP[i].harga << setw(jumlahWidth) << daftarP[i].jumlahPesanan << setw(totalWidth) << daftarP[i].totalHarga << endl;
    }
}

void Resto::reservasiRuangan() {
    string nama, noHP;
    int pilihan;

    cout << "|Masukkan Nama Anda: ";
    cin.ignore();
    getline(cin, nama);
    cout << "|Masukkan Nomor HP Anda: ";
    getline(cin, noHP);

    long int nomerHP = stoll(noHP);

    long int index = hashFunction(nomerHP);

    if(ruang[index].head != nullptr && ruang[index].head->name != "") {
        cout << "Meja Sudah Di Pesan, Apakah Anda Ingin Antri Atau Dipindah Ke Meja Lain?\n";
        cout << "1. Antri\n";
        cout << "2. Pindah\n";
        cin >> pilihan;
    } else {
        pilihan = 2; // Jika meja kosong, langsung pilih opsi pindah
    }

    hash(nama, nomerHP, pilihan, noHP);

    cout << "|Meja Berhasil Di Reservasi|\n";
    cout << "|Anda Mendapat Meja Nomor " << index << " |\n";
}

int Resto::quadraticProbing2(int nomerHP, int attempt) {
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

void Resto::hash2(string nama, long int nomerHP, int pilihan, string noHP) {
    long int index = hashFunction(nomerHP);
    int attempt = 0;
    
    if(pilihan == 1) {
        Node* newNode = new Node;
        newNode->name = nama;
        newNode->key = noHP;
        newNode->prev = nullptr;
        newNode->next = nullptr;

        if (ruang[index].head == nullptr) {
            ruang[index].head = newNode;
        } else {
            Node* temp = ruang[index].head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
    } else if(pilihan == 2) {
        index = quadraticProbing(nomerHP, attempt);

        if (index != -1) {
            Node* newNode = new Node;
            newNode->name = nama;
            newNode->key = noHP;
            newNode->prev = nullptr;
            newNode->next = nullptr;

            ruang[index].head = newNode;
        } else {
            cout << "Meja Sudah Penuh" << endl;
        }
    }
}
