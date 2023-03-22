#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// Estructura para cada nodo de la lista doblemente enlazada
struct Guest {
    string name;
    int roomNumber;
    Guest* prev;
    Guest* next;
};

void deleteGuestList();

// Función para cargar la información del archivo de texto en la lista doblemente enlazada
void loadGuestList(Guest*& head) {
    ifstream file("hotel.txt");
    if (file.is_open()) {
        string name;
        int roomNumber;
        while (file >> name >> roomNumber) {
            Guest* guest = new Guest{ name, roomNumber, nullptr, nullptr };
            if (head == nullptr) {
                head = guest;
            }
            else {
                Guest* curr = head;
                while (curr->next != nullptr) {
                    curr = curr->next;
                }
                curr->next = guest;
                guest->prev = curr;
            }
        }
        file.close();
    }
}

// Función para guardar la información del huésped en el archivo de texto
void saveGuest(Guest* guest) {
    ofstream file("hotel.txt", ios::app);
    if (file.is_open()) {
        file << guest->name << " " << guest->roomNumber << endl;
        file.close();
    }
}

// Función para encontrar un huésped por su nombre o número de habitación
Guest* findGuest(Guest* head, string name = "", int roomNumber = 0) {
    Guest* curr = head;
    while (curr != nullptr) {
        if ((name != "" && curr->name == name) || (roomNumber != 0 && curr->roomNumber == roomNumber)) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

// Función para mostrar la lista de huéspedes en orden alfabético
void showGuestListByName(Guest* head) {
    if (head == nullptr) {
        cout << "No hay huéspedes registrados" << endl;
    }
    else {
        Guest* curr = head;
        string* names = new string[100]; // Se asume que no hay más de 100 huéspedes
        int count = 0;
        while (curr != nullptr) {
            names[count] = curr->name;
            count++;
            curr = curr->next;
        }
        sort(names, names + count);
        cout << "Lista de huéspedes en orden alfabético:" << endl;
        for (int i = 0; i < count; i++) {
            curr = findGuest(head, names[i]);
            cout << curr->name << " (" << curr->roomNumber << ")" << endl;
        }
    }
}

// Función para mostrar la lista de huéspedes en orden de llegada
void showGuestListByArrival(Guest* head) {
    if (head == nullptr) {
        cout << "No hay huéspedes registrados" << endl;
    }
    else {
        Guest* curr = head;
        cout << "Lista de huéspedes en orden de llegada:" << endl;
        while (curr != nullptr) {
            cout << curr->name << " (" << curr->roomNumber << ")" << endl;
            curr = curr->next;
        }
    }
}

// Función para encontrar una habitación disponible cerca del número de habitación dado
int findAvailableRoom
        (Guest* head, int roomNumber) {
    Guest* curr = head;
    int availableRoom = 0;
    while (curr != nullptr) {
        if (curr->roomNumber == roomNumber) {
// Buscar la siguiente habitación disponible cerca del número de habitación dado
            if (curr->next != nullptr && curr->next->roomNumber == curr->roomNumber + 1) {
                curr = curr->next;
            }
            else {
                availableRoom = curr->roomNumber + 1;
                break;
            }
        }
        curr = curr->next;
    }
    if (availableRoom == 0) {
// Si no se encontró una habitación disponible cerca del número de habitación dado, buscar en toda la lista
        curr = head;
        int lastRoom = 0;
        while (curr != nullptr) {
            if (curr->roomNumber > lastRoom + 1) {
                availableRoom = lastRoom + 1;
                break;
            }
            lastRoom = curr->roomNumber;
            curr = curr->next;
        }
        if (availableRoom == 0) {
// Si no se encontró una habitación disponible en toda la lista, asignar la siguiente al final de la lista
            availableRoom = lastRoom + 1;
        }
    }
    return availableRoom;
}

// Función principal
int main() {
    Guest* head = nullptr;
    loadGuestList(head);

    int opcion = 0;
    do {
        cout << "----- Menú -----" << endl;
        cout << "1. Agregar un huésped" << endl;
        cout << "2. Buscar un huésped por nombre" << endl;
        cout << "3. Buscar un huésped por número de habitación" << endl;
        cout << "4. Mostrar la lista de huéspedes en orden alfabético" << endl;
        cout << "5. Mostrar la lista de huéspedes en orden de llegada" << endl;
        cout << "6. Encontrar una habitación disponible" << endl;
        cout << "7. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
            {
                string name;
                int roomNumber;
                cout << "Ingrese el nombre del huésped: ";
                cin >> name;
                cout << "Ingrese el número de habitación: ";
                cin >> roomNumber;
                Guest* guest = new Guest{ name, roomNumber, nullptr, nullptr };
                if (findGuest(head, "", roomNumber) != nullptr) {
                    cout << "Ya existe un huésped en la habitación " << roomNumber << endl;
                }
                else {
                    if (head == nullptr) {
                        head = guest;
                    }
                    else {
                        Guest* curr = head;
                        while (curr->next != nullptr) {
                            curr = curr->next;
                        }
                        curr->next = guest;
                        guest->prev = curr;
                    }
                    saveGuest(guest);
                    cout << "Huésped agregado correctamente" << endl;
                }
                break;
            }
            case 2:
            {
                string name;
                cout << "Ingrese el nombre del huésped: ";
                cin >> name;
                Guest* guest = findGuest(head, name);
                if (guest == nullptr) {
                    cout << "No se encontró al huésped" << endl;
                }
                else {
                    cout << "Huésped encontrado: " << guest->name << " (" << guest->roomNumber << ")" << endl;
                }
                break;
            }
            case 3:
            {
                int roomNumber;
                cout << "Ingrese el número de habitación: ";
                cin >> roomNumber;
                Guest* guest = findGuest(head, "", roomNumber);
                if (guest == nullptr) {
                    cout << "No se encontró al huésped" << endl;
                }
                else {
                    cout << "Huésped encontrado: " << guest->name << " (" << guest->roomNumber << ")" << endl;
                }
                break;
            }
            case 4:
                showGuestListByName(head);
                break;
            case 5:
                showGuestListByArrival(head);
                break;
            case 6:
            {
                int roomNumber;
                cout << "Ingrese el número de habitación cerca del cual buscar una habitación disponible: ";
                cin >> roomNumber;
                int availableRoom = findAvailableRoom(head, roomNumber);
                cout << "La siguiente habitación disponible cerca del número de habitación " << roomNumber << " es " << availableRoom << endl;
                break;
            }
            case 7:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción no válida" << endl;
        }
    } while (opcion != 7);

    deleteGuestList();

    return 0;
}

void deleteGuestList() {

}
