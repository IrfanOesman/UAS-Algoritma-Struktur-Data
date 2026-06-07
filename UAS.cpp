#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. STRUKTUR DATA UTAMA (TIKET & TEKNISI)
// ==========================================

// Struktur data untuk Tiket 
struct Tiket {
    int idTiket;
    string deskripsiKerusakan;
    string status; // "Antri", "Diproses", "Selesai"
    string namaTeknisi;
};

// Node untuk Linked List Utama (
struct NodeTiket {
    Tiket data;
    NodeTiket* next;
};

// Node untuk Queue (Antrian Tiket) [cite: 5]
struct NodeQueue {
    int idTiket;
    NodeQueue* next;
};

// Node untuk Hash Table (Data Teknisi dengan Chaining) [cite: 6]
struct Teknisi {
    string nama;
    string spesialisasi;
    Teknisi* next;
};


// ==========================================
// 2. IMPLEMENTASI ADT (QUEUE & HASH TABLE)
// ==========================================

// ADT Queue untuk Antrian Tiket [cite: 2, 5]
class QueueTiket {
public:
    NodeQueue* front;
    NodeQueue* rear;

public:
    QueueTiket() {
        front = nullptr;
        rear = nullptr;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    // Memasukkan tiket ke antrian belakang [cite: 5]
    void enqueue(int id) {
        NodeQueue* newNode = new NodeQueue{id, nullptr};
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Mengambil tiket dari antrian depan [cite: 5]
    int dequeue() {
        if (isEmpty()) return -1;
        
        NodeQueue* temp = front;
        int id = temp->idTiket;
        front = front->next;
        
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        return id;
    }

    // Getter untuk melihat antrian depan tanpa menghapusnya [cite: 13]
    NodeQueue* getFront() {
        return front;
    }
};

// ADT Hash Table untuk Data Teknisi [cite: 2, 6]
class HashTableTeknisi {
private:
    static const int TABLE_SIZE = 10;
    Teknisi* table[TABLE_SIZE];

    // Fungsi Hash Sederhana [cite: 2]
    int hashFunction(string key) {
        int sum = 0;
        for (char ch : key) {
            sum += ch;
        }
        return sum % TABLE_SIZE;
    }

public:
    HashTableTeknisi() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    // FITUR 3: Tambah Teknisi [cite: 10]
    void tambahTeknisi(string nama, string spesialisasi) {
        int index = hashFunction(nama);
        Teknisi* newTeknisi = new Teknisi{nama, spesialisasi, table[index]};
        table[index] = newTeknisi;
        cout << "? Teknisi " << nama << " berhasil ditambahkan!\n";
    }

    // FITUR 4: Cari Teknisi [cite: 11]
    Teknisi* cariTeknisi(string nama) {
        int index = hashFunction(nama);
        Teknisi* curr = table[index];
        while (curr != nullptr) {
            if (curr->nama == nama) {
                return curr;
            }
            curr = curr->next;
        }
        return nullptr; // Tidak ditemukan
    }
};


// ==========================================
// 3. SISTEM HELPDESK UTAMA
// ==========================================
class SistemHelpdesk {
private:
    NodeTiket* headLL; // Head untuk Linked List Tiket [cite: 4]
    QueueTiket antrian; // Queue Antrian [cite: 5]
    HashTableTeknisi dataTeknisi; // Hash Table Teknisi [cite: 6]
    int idCounter; // Auto-increment ID Tiket

    // Helper: Cari tiket di Linked List berdasarkan ID [cite: 4]
    NodeTiket* cariTiketLL(int id) {
        NodeTiket* curr = headLL;
        while (curr != nullptr) {
            if (curr->data.idTiket == id) return curr;
            curr = curr->next;
        }
        return nullptr;
    }

public:
    SistemHelpdesk() {
        headLL = nullptr;
        idCounter = 101; // ID dimulai dari 101
    }

    // FITUR 1: Tambah Tiket [cite: 8]
    void tambahTiket(string deskripsi) {
        Tiket tiketBaru = {idCounter, deskripsi, "Antri", "-"};
        
        // Simpan ke Linked List (Insert di depan/head agar mudah) [cite: 4]
        NodeTiket* newNode = new NodeTiket{tiketBaru, headLL};
        headLL = newNode;

        // Masukkan ke Antrian Proses [cite: 5]
        antrian.enqueue(idCounter);

        cout << "? Tiket #" << idCounter << " berhasil dibuat dan masuk antrian.\n";
        idCounter++;
    }

    // FITUR 2: Proses Tiket Berikutnya 
    void prosesTiketBerikutnya() {
        int idDiproses = antrian.dequeue(); // Mengambil antrian terdepan [cite: 5]
        if (idDiproses == -1) {
            cout << "? Tidak ada tiket dalam antrian untuk diproses.\n";
            return;
        }

        // Update status di Linked List [cite: 4]
        NodeTiket* tiketNode = cariTiketLL(idDiproses);
        if (tiketNode != nullptr) {
            tiketNode->data.status = "Diproses";
            cout << "? Menugaskan Tiket #" << idDiproses << " [ " << tiketNode->data.deskripsiKerusakan << " ] ke status: DIPROSES.\n";
        }
    }

    // Akses publik untuk tambah teknisi [cite: 10]
    void tambahTeknisiKeSistem(string nama, string spesialisasi) {
        dataTeknisi.tambahTeknisi(nama, spesialisasi);
    }

    // FITUR 4: Cari dan Tampilkan Teknisi [cite: 11]
    void cariTeknisiDiSistem(string nama) {
        Teknisi* t = dataTeknisi.cariTeknisi(nama);
        if (t != nullptr) {
            cout << "?? Teknisi Ditemukan! Nama: " << t->nama << " | Spesialisasi: " << t->spesialisasi << "\n";
        } else {
            cout << "? Teknisi bernama \"" << nama << "\" tidak ditemukan.\n";
        }
    }

    // FITUR 5: Assign Tiket ke Teknisi [cite: 12]
    void assignTiketKeTeknisi(int idTiket, string namaTeknisi) {
        // 1. Cek apakah teknisi terdaftar di Hash Table [cite: 6, 11]
        Teknisi* t = dataTeknisi.cariTeknisi(namaTeknisi);
        if (t == nullptr) {
            cout << "? Gagal Assign! Teknisi \"" << namaTeknisi << "\" tidak terdaftar di sistem.\n";
            return;
        }

        // 2. Cek apakah tiket ada di Linked List [cite: 4]
        NodeTiket* tiketNode = cariTiketLL(idTiket);
        if (tiketNode == nullptr) {
            cout << "? Gagal Assign! ID Tiket #" << idTiket << " tidak ditemukan.\n";
            return;
        }

        // 3. Update data tiket [cite: 4]
        tiketNode->data.namaTeknisi = t->nama;
        tiketNode->data.status = "Selesai";
        cout << "? Tiket #" << idTiket << " BERHASIL ditugaskan ke " << t->nama << " dan status menjadi SELESAI.\n";
    }

    // FITUR 6: Tampilkan Status Antrian [cite: 13]
    void tampilkanAntrian() {
        cout << "\n=== DAFTAR ANTRIAN TIKET SAAT INI ===\n";
        NodeQueue* currQueue = antrian.getFront();
        
        if (currQueue == nullptr) {
            cout << "(Antrian Kosong)\n";
        } else {
            int posisi = 1;
            while (currQueue != nullptr) {
                // Cari detail infonya di Linked List [cite: 4]
                NodeTiket* t = cariTiketLL(currQueue->idTiket);
                if (t != nullptr) {
                    cout << posisi << ". Tiket #" << t->data.idTiket 
                         << " | Deskripsi: " << t->data.deskripsiKerusakan 
                         << " | Status: " << t->data.status << "\n";
                }
                currQueue = currQueue->next;
                posisi++;
            }
        }

        // Tambahan: Menampilkan seluruh data histori di Linked List agar terlihat bedanya [cite: 4]
        cout << "\n=== HISTORI SEMUA TIKET (LINKED LIST) ===\n";
        NodeTiket* currLL = headLL;
        if (currLL == nullptr) {
            cout << "(Belum ada histori tiket)\n";
        } else {
            while (currLL != nullptr) {
                cout << "• ID: #" << currLL->data.idTiket 
                     << " | Deskripsi: " << currLL->data.deskripsiKerusakan 
                     << " | Status: " << currLL->data.status 
                     << " | Teknisi: " << currLL->data.namaTeknisi << "\n";
                currLL = currLL->next;
            }
        }
        cout << "=======================================\n";
    }
};


// ==========================================
// 4. MAIN FUNCTION (MENU INTERAKTIF)
// ==========================================
int main() {
    SistemHelpdesk helpdesk;
    int pilihan;

    // Data Awal Driver (Optional, biar pas dirun tidak kosong banget)
    helpdesk.tambahTeknisiKeSistem("Andi", "Hardware");
    helpdesk.tambahTeknisiKeSistem("Budi", "Jaringan");
    cout << "\n";

    do {
        cout << "\n=== MENU IT HELPDESK SYSTEM ===\n";
        cout << "1. Tambah Tiket\n";
        cout << "2. Proses Tiket Berikutnya\n";
        cout << "3. Tambah Teknisi\n";
        cout << "4. Cari Teknisi\n";
        cout << "5. Assign Tiket ke Teknisi\n";
        cout << "6. Tampilkan Status Antrian & Histori\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu (0-6): ";
        cin >> pilihan;
        cin.ignore(); // Membersihkan buffer input

        switch (pilihan) {
            case 1: {
                string deskripsi;
                cout << "Masukkan deskripsi kerusakan: ";
                getline(cin, deskripsi);
                helpdesk.tambahTiket(deskripsi);
                break;
            }
            case 2:
                helpdesk.prosesTiketBerikutnya();
                break;
            case 3: {
                string nama, spesialisasi;
                cout << "Masukkan nama teknisi: ";
                getline(cin, nama);
                cout << "Masukkan spesialisasi: ";
                getline(cin, spesialisasi);
                helpdesk.tambahTeknisiKeSistem(nama, spesialisasi);
                break;
            }
            case 4: {
                string nama;
                cout << "Masukkan nama teknisi yang dicari: ";
                getline(cin, nama);
                helpdesk.cariTeknisiDiSistem(nama);
                break;
            }
            case 5: {
                int idTiket;
                string namaTeknisi;
                cout << "Masukkan ID Tiket: ";
                cin >> idTiket;
                cin.ignore();
                cout << "Masukkan Nama Teknisi: ";
                getline(cin, namaTeknisi);
                helpdesk.assignTiketKeTeknisi(idTiket, namaTeknisi);
                break;
            }
            case 6:
                helpdesk.tampilkanAntrian();
                break;
            case 0:
                cout << "Terima kasih! Program selesai.\n";
                break;
            default:
                cout << "? Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    return 0;
}
