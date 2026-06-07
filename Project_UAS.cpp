#include <iostream>
using namespace std;

struct Tiket_Node {
    int ID_Tiket;
    string Nama_Pengguna;
    string Detail_Kerusakan;
    Tiket_Node* next;
};

Tiket_Node* queueFront = NULL;
Tiket_Node* queueBack = NULL;
Tiket_Node* listHead = NULL;

const int SIZE = 15;

struct Teknisi_Node {
    string Nama_Teknisi;
    int ID_Teknisi;
    Teknisi_Node* next;
};

Teknisi_Node* hashTable[SIZE];

void Tambah_Tiket(int ID, string Nama, string Detail){
    cout << "=============== Penamahan Tiket Baru ===============" << endl;
    Tiket_Node* newNode = new Tiket_Node;
    newNode->ID_Tiket = ID;
    newNode->Nama_Pengguna = Nama;
    newNode->Detail_Kerusakan = Detail;
    newNode->next = NULL;

    if (listHead == NULL) {
        listHead = newNode;
    } else {
        Tiket_Node* temp = listHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    if (queueBack == NULL) {
        queueFront = queueBack = newNode;
    } else {
        queueBack->next = newNode;
        queueBack = newNode;
    }
}

void Proses_Tiket() {
    if (queueFront == NULL) {
        cout << "Antrean kosong! Tidak ada tiket yang perlu diproses saat ini." << endl;
        return; 
    }

    Tiket_Node* tiketDiproses = queueFront;

    cout << "\n========================================" << endl;
    cout << "      MEMPROSES TIKET BERIKUTNYA        " << endl;
    cout << "========================================" << endl;
    cout << "ID Tiket         : " << tiketDiproses->ID_Tiket << endl;
    cout << "Nama Pengguna    : " << tiketDiproses->Nama_Pengguna << endl;
    cout << "Detail Kerusakan : " << tiketDiproses->Detail_Kerusakan << endl;
    cout << "========================================" << endl;

    queueFront = queueFront->next;

    if (queueFront == NULL) {
        queueBack = NULL;
    }

    cout << "Status: Tiket berhasil keluar dari antrian dan sedang diproses!" << endl;
    
    // Notes: tidak adanya proses delete karna alamat memorinya masih tersimpan fi list head
    // Sehingga data tersebut tidak hilang dari sistem, tetapi hanya keluar dari barisan antrean.

}

void Tampilkan_Antrean() {
    cout << "\n========================================" << endl;
    cout << "         DAFTAR ANTRIAN TIKET YANG AKTIF     " << endl;
    cout << "========================================" << endl;

    if (queueFront == NULL) {
        cout << "Antrean saat ini kosong! Tidak ada tiket dalam antrean." << endl;
        return; 
    }

    Tiket_Node* current = queueFront;
    int nomorAntrean = 1;

    // Proses Looping dari queueFront sampai ke data terakhir
    while (current != NULL) {
        cout << "Antrean Ke-" << nomorAntrean << endl;
        cout << "  ID Tiket         : " << current->ID_Tiket << endl;
        cout << "  Nama Pengguna    : " << current->Nama_Pengguna << endl;
        cout << "  Detail Kerusakan : " << current->Detail_Kerusakan << endl;
        cout << "----------------------------------------" << endl;
        
        // Geser pointer bantuan ke node berikutnya di dalam antrian
        current = current->next;
        nomorAntrean++;
    }
    
    cout << "Berhasil menampilkan semua tiket dalam antrian!" << endl;
}