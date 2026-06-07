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