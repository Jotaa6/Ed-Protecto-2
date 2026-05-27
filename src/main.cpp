#include <iostream>
#include <cstdlib>
#include "../include/api_client.h"
using namespace std;

int main() {
    system("mkdir -p output");
    char result[5000];
    httpGet("/galaxias", result, 5000);
    if (result[0] == '\0') {
        cout << "FALLO: respuesta vacia." << endl;
    } else {
        cout << "EXITO: respuesta recibida." << endl;
        cout << result << endl;
    }
    return 0;
}
