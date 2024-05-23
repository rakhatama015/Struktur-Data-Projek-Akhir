#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
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
            int key;
            string name;
            node* prev;
            node* next;
        };
        struct ruangan{
            node* head;
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
        ruangan ruang[SIZE];
        stack<pesanan> stackPesanan;
        queue<pesanan> queuePesanan;
        TreeNode* treeRoot;
        Graph graph;

    public:
        Resto() : treeRoot(nullptr), graph(SIZE) {}
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
};

int main(){
    Resto resto;
    string nama, password, adminName = "admin", adminPass = "password";
    int pilihan, pilihan2;

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
            cout << "\nMasukkan Nama Anda: ";
            cin.ignore();
            getline(cin, nama);
            cout << "Masukkan Password: ";
            getline(cin, password);

            if(nama == adminName && password == adminPass){
                resto.admin();
            }
            else{
                cout << "Sandi Salah\n";
            }
            cout << "1. Ulang\n";
            cout << "0. Keluar\n";
            cin >> pilihan2;
        }while(pilihan2 != 0);

        break;
    case 2:

        do{
            cout << '\n';
            resto.pelanggan();
            cout << "1. Ulang\n";
            cout << "0. Keluar\n";
            cin >> pilihan2;
        }while(pilihan2 != 0);

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
    cin >> pilihan;

    switch (pilihan) {
        case 1:
            tampilkanAntrian();
            break;
        case 2:
            tampilkanReservasi();
            break;
        case 3:
            tampilkanPesanan();
            break;
        default:
            cout << "Pilihan tidak valid" << endl;
    }
}

void Resto::pelanggan(){
    int pilihan;
    cout << '|' << string(75, '-')  << '|' << endl;
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
    cout << left << setw(nameWidth + 3) << "Nama Pesanan" << right << setw(priceWidth) << "Harga" << setw(2 + jumlahWidth) << "Jumlah" << setw(totalWidth - 2) << "Total" << endl;
    cout << string(nameWidth + priceWidth + jumlahWidth + totalWidth + cornerLeft, '-') << endl;

    for (const auto& pesanan : daftarP) {
        cout << left << setw(nameWidth) << pesanan.namaPesanan << right << setw(priceWidth) << pesanan.harga << setw(jumlahWidth) << pesanan.jumlahPesanan << setw(totalWidth) << pesanan.totalHarga << endl;
    }

    // Display tree
    cout << "\nTraversal Tree Pesanan (Total Harga):" << endl;
    displayTree();
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

    if (ruang[i].head != nullptr && ruang[i].head->name != "") {
        cout << "Meja Sudah Di Pesan, Apakah Anda Ingin Antri Atau Dipindah Ke Meja Lain?\n";
        cout << "1. Antri\n";
        cout << "2. Pindah\n";
        cin >> pilihan;
    } else {
        pilihan = 1;
    }

    hash(nama, nomerHP, pilihan);
}

void Resto::hash(string nama, int nomerHP, int pilihan) {
    int index = hashFunction(nomerHP);
    int attempt = 0;

    if (pilihan == 1) {
        int index = hashFunction(nomerHP);

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
        cout << "Tidak ada antrian saat ini." << endl;
    } else {
        cout << "Daftar antrian pesanan:" << endl;
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
        if (ruang[i].head != nullptr) {
            node* temp = ruang[i].head;
            while (temp != nullptr) {
                cout << "Meja " << i + 1 << ": " << temp->name << " - No HP: " << temp->key << endl;
                temp = temp->next;
            }
        } else {
            cout << "Meja " << i + 1 << ": Kosong" << endl;
        }
    }
}
