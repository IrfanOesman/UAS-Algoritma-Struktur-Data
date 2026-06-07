#include <iostream>
using namespace std;

struct Tiket_Node {
    int    ID_Tiket;
    string Nama_Pengguna;
    string Detail_Kerusakan;
    int    ID_Teknisi_Assign;
    Tiket_Node* next;
};

Tiket_Node* queueFront = NULL;
Tiket_Node* queueBack  = NULL;
Tiket_Node* listHead   = NULL;

const int SIZE = 15;

struct Teknisi_Node {
    string Nama_Teknisi;
    int    ID_Teknisi;
    Teknisi_Node* next;
};

Teknisi_Node* hashTable[SIZE];

int hashFunction(int id) {
    return id % SIZE;
}

void Init_HashTable() {
    for (int i = 0; i < SIZE; i++) {
        hashTable[i] = NULL;
    }
}

void Tambah_Tiket(int ID, string Nama, string Detail) {
    cout << "\n=============== Penambahan Tiket Baru ===============" << endl;
    Tiket_Node* newNode = new Tiket_Node;
    newNode->ID_Tiket          = ID;
    newNode->Nama_Pengguna     = Nama;
    newNode->Detail_Kerusakan  = Detail;
    newNode->ID_Teknisi_Assign = 0;
    newNode->next              = NULL;
    if (listHead == NULL) {
        listHead = newNode;
    } else {
        Tiket_Node* temp = listHead;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newNode;
    }
    if (queueBack == NULL) {
        queueFront = queueBack = newNode;
    } else {
        queueBack->next = newNode;
        queueBack       = newNode;
    }
    cout << "Tiket ID-" << ID << " atas nama " << Nama << " berhasil ditambahkan!" << endl;
}

void Proses_Tiket() {
    if (queueFront == NULL) {
        cout << "\nAntrean kosong! Tidak ada tiket yang perlu diproses saat ini." << endl;
        return;
    }
    Tiket_Node* tiketDiproses = queueFront;
    cout << "\n========================================" << endl;
    cout << "      MEMPROSES TIKET BERIKUTNYA        " << endl;
    cout << "========================================" << endl;
    cout << "ID Tiket         : " << tiketDiproses->ID_Tiket         << endl;
    cout << "Nama Pengguna    : " << tiketDiproses->Nama_Pengguna    << endl;
    cout << "Detail Kerusakan : " << tiketDiproses->Detail_Kerusakan << endl;
    if (tiketDiproses->ID_Teknisi_Assign != 0)
        cout << "Ditangani Teknisi: ID-" << tiketDiproses->ID_Teknisi_Assign << endl;
    cout << "========================================" << endl;
    queueFront = queueFront->next;
    if (queueFront == NULL) queueBack = NULL;
    cout << "Status: Tiket berhasil keluar dari antrian dan sedang diproses!" << endl;
}

void Tambah_Teknisi(int ID, string Nama) {
    cout << "\n=============== Penambahan Teknisi Baru ===============" << endl;
    int index = hashFunction(ID);
    Teknisi_Node* cek = hashTable[index];
    while (cek != NULL) {
        if (cek->ID_Teknisi == ID) {
            cout << "Gagal! ID Teknisi " << ID << " sudah terdaftar." << endl;
            return;
        }
        cek = cek->next;
    }
    Teknisi_Node* newNode = new Teknisi_Node;
    newNode->ID_Teknisi   = ID;
    newNode->Nama_Teknisi = Nama;
    newNode->next         = hashTable[index];
    hashTable[index]      = newNode;
    cout << "Teknisi " << Nama << " (ID-" << ID << ") berhasil ditambahkan." << endl;
}

Teknisi_Node* Cari_Teknisi(int ID) {
    int index = hashFunction(ID);
    Teknisi_Node* current = hashTable[index];
    while (current != NULL) {
        if (current->ID_Teknisi == ID) return current;
        current = current->next;
    }
    return NULL;
}

void Tampilkan_Cari_Teknisi(int ID) {
    cout << "\n========================================" << endl;
    cout << "          PENCARIAN TEKNISI             " << endl;
    cout << "========================================" << endl;
    Teknisi_Node* hasil = Cari_Teknisi(ID);
    if (hasil == NULL) {
        cout << "Teknisi dengan ID-" << ID << " tidak ditemukan." << endl;
    } else {
        cout << "Teknisi Ditemukan!" << endl;
        cout << "  ID Teknisi   : " << hasil->ID_Teknisi   << endl;
        cout << "  Nama Teknisi : " << hasil->Nama_Teknisi << endl;
    }
    cout << "========================================" << endl;
}

void Assign_Tiket(int ID_Tiket, int ID_Teknisi) {
    cout << "\n========================================" << endl;
    cout << "        ASSIGN TIKET KE TEKNISI         " << endl;
    cout << "========================================" << endl;
    Tiket_Node* tiket = listHead;
    while (tiket != NULL) {
        if (tiket->ID_Tiket == ID_Tiket) break;
        tiket = tiket->next;
    }
    if (tiket == NULL) {
        cout << "Gagal! Tiket ID-" << ID_Tiket << " tidak ditemukan." << endl;
        return;
    }
    Teknisi_Node* teknisi = Cari_Teknisi(ID_Teknisi);
    if (teknisi == NULL) {
        cout << "Gagal! Teknisi ID-" << ID_Teknisi << " tidak ditemukan." << endl;
        return;
    }
    tiket->ID_Teknisi_Assign = ID_Teknisi;
    cout << "Berhasil! Tiket ID-" << ID_Tiket
         << " (" << tiket->Nama_Pengguna << ")"
         << " telah di-assign ke Teknisi "
         << teknisi->Nama_Teknisi << " (ID-" << ID_Teknisi << ")." << endl;
    cout << "========================================" << endl;
}

void Tampilkan_Antrean() {
    cout << "\n========================================" << endl;
    cout << "     DAFTAR ANTRIAN TIKET YANG AKTIF    " << endl;
    cout << "========================================" << endl;
    if (queueFront == NULL) {
        cout << "Antrean saat ini kosong! Tidak ada tiket dalam antrian." << endl;
        return;
    }
    Tiket_Node* current = queueFront;
    int nomorAntrean = 1;
    while (current != NULL) {
        cout << "Antrean Ke-" << nomorAntrean << endl;
        cout << "  ID Tiket         : " << current->ID_Tiket         << endl;
        cout << "  Nama Pengguna    : " << current->Nama_Pengguna    << endl;
        cout << "  Detail Kerusakan : " << current->Detail_Kerusakan << endl;
        if (current->ID_Teknisi_Assign != 0) {
            Teknisi_Node* tek = Cari_Teknisi(current->ID_Teknisi_Assign);
            cout << "  Assigned Teknisi : "
                 << (tek ? tek->Nama_Teknisi : "?")
                 << " (ID-" << current->ID_Teknisi_Assign << ")" << endl;
        } else {
            cout << "  Assigned Teknisi : Belum di-assign" << endl;
        }
        cout << "----------------------------------------" << endl;
        current = current->next;
        nomorAntrean++;
    }
    cout << "Berhasil menampilkan semua tiket dalam antrian!" << endl;
}

int main() {
    Init_HashTable();
    int pilihan;
    do {
        cout << "\n+--------------------------------------+" << endl;
        cout << "¦   SISTEM HELPDESK TIKET IT           ¦" << endl;
        cout << "¦--------------------------------------¦" << endl;
        cout << "¦  1. Tambah Tiket                     ¦" << endl;
        cout << "¦  2. Proses Tiket Berikutnya           ¦" << endl;
        cout << "¦  3. Tambah Teknisi                   ¦" << endl;
        cout << "¦  4. Cari Teknisi                     ¦" << endl;
        cout << "¦  5. Assign Tiket ke Teknisi           ¦" << endl;
        cout << "¦  6. Tampilkan Status Antrian          ¦" << endl;
        cout << "¦  0. Keluar                           ¦" << endl;
        cout << "+--------------------------------------+" << endl;
        cout << "Pilihan: ";
        cin  >> pilihan;
        if (pilihan == 1) {
            int    id;
            string nama, detail;
            cout << "ID Tiket         : "; cin >> id; cin.ignore();
            cout << "Nama Pengguna    : "; getline(cin, nama);
            cout << "Detail Kerusakan : "; getline(cin, detail);
            Tambah_Tiket(id, nama, detail);
        } else if (pilihan == 2) {
            Proses_Tiket();
        } else if (pilihan == 3) {
            int    id;
            string nama;
            cout << "ID Teknisi   : "; cin >> id; cin.ignore();
            cout << "Nama Teknisi : "; getline(cin, nama);
            Tambah_Teknisi(id, nama);
        } else if (pilihan == 4) {
            int id;
            cout << "Masukkan ID Teknisi yang dicari: "; cin >> id;
            Tampilkan_Cari_Teknisi(id);
        } else if (pilihan == 5) {
            int idTiket, idTeknisi;
            cout << "ID Tiket   : "; cin >> idTiket;
            cout << "ID Teknisi : "; cin >> idTeknisi;
            Assign_Tiket(idTiket, idTeknisi);
        } else if (pilihan == 6) {
            Tampilkan_Antrean();
        } else if (pilihan != 0) {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihan != 0);
    cout << "\nTerima kasih! Program selesai." << endl;
    return 0;
}
