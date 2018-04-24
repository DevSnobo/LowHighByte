
/**
 * @file   aufgabe1-bit.c
 * @brief  Aufgabe1 - Bit Manipulationen
 */

#include <cstdio>
// Falls notwendig erweitern Sie die Liste der includes


/**
   @brief Aufgabe1a: Vertauschen von Bytes
   @param [in] short int i
   @return short int

Schreiben Sie eine Funktion die das Low Byte (Bits 0-7) und
das High Byte (Bits 8-15) vertauscht.
Z.B. aus der Zahl 0x4020 wird die Zahl 0x2040.
*/

short int switchLowHighByte(short int i) {

    auto value = static_cast<unsigned short int>(i);    // Wert wird in "value" kopiert.
    unsigned short int newValue = 0;                    // Default = 0, für newValue
    unsigned short int maskLow = 0x00ff;
    unsigned short int maskHigh = 0xff00;

    printf("value Wert = %x\n", value);

    newValue |= ((maskLow & value) << 8);         // LowByte wird auf HighByte "geschoben" und verUNDet
    printf("newValue1 Wert = %x\n", newValue);

    newValue |= ((maskHigh & value) >> 8);        // HighByte wird auf LowByte "geschoben" und verUNDet
    printf("newValue2 Wert = %x\n", newValue);

    return static_cast<short>(newValue);
}


typedef enum {
    Stop = 0,
    Start = 1,
    Finish = 5,
    Fail = 255
} Status;


typedef enum {
    One = 1,
    Fifteen = 15,
    Last = 255
} Numbers;

/**
   @brief Aufgabe1b: Serialisierung von Datenstrukturen
   @param [in] Status s
   @param [in] Numbers n
   @param [out] short int* data

Gegeben sind zwei enums. Ihre Aufgabe ist es jeweils Werte der
beiden enums in ein Datenpacket der Groesse 16Bit zu packen (serialisieren).
Werte des enums Status sollen dabei in das Low Byte und Werte
des enums Numbers sollen in das High Byte gepackt werden.
*/


void serialize(Status s, Numbers n, short int *data) {
    unsigned short int value = n << 8;            // Bitshift nach links
    value = value | s;                            // Status in LowByte gespeichert
    *data = value;
}

/**
   @brief Aufgabe1c: Deserialisierung von Datenstrukturen
   @param [in] short int data
   @param [out] Status* s
   @param [out] Numbers* n

Schreiben Sie eine Funktion die Werte der enums Status und Number
aus einem 16Bit Wert entpackt (deserialisiert).
Wir nehmen an, dass die enum Werte mittels der serialize Funktion
verpackt wurden.
*/

void deserialize(short int data, Status *s, Numbers *n) {
    *s = static_cast<Status>(data & 0x00ff);              // Status aus LowByte herausholen
    *n = static_cast<Numbers>((data & 0xff00) >> 8);      // Number aus HighByte herausholen
}

enum TestEnum {
    OK,
    FAIL
};
typedef enum TestEnum Test;

Test testLowHigh(short int i) {
    Test t;
    if (i == switchLowHighByte(switchLowHighByte(i)))
        t = OK;
    else
        t = FAIL;

    return t;
}

Test testSeDeserialize(Status status, Numbers numbers) {
    Test t;

    unsigned short int data;
    Status status2;
    Numbers numbers2;

    serialize(status, numbers, reinterpret_cast<short *>(&data));
    printf("\nSerialize:\n\nStatus was: %d\nNumbers was: %d\ndata was: %x\n", status, numbers, data);

    deserialize(data, &status2, &numbers2);
    printf("\nDeserialize:\n\nStatus was: %d\nNumbers was: %d\ndata was: %x\n", status2, numbers2, data);

    if (status2 == status && numbers2 == numbers) {
        printf("OK \n");
        t = OK;
    } else
        printf("FAIL \n");
    t = FAIL;
    return t;
}

int main() {
    // Ihre Testroutinen

    printf("Lo/Hi Test 1\n");
    testLowHigh(0x1213);
    printf("\n");
    printf("Lo/Hi Test 2\n");
    testLowHigh(0x0059);
    printf("\n");
    printf("Lo/Hi Test 3\n");
    testLowHigh(0x2200);
    printf("\n");
    printf("Lo/Hi Test 4\n");
    testLowHigh(0x1124);
    printf("\n");
    printf("Lo/Hi Test 5\n");
    testLowHigh(0xabcd);

    printf("\n");
    printf("\nAusgabe 1 testSeDeserialize\n");
    testSeDeserialize(Start, Fifteen);
    printf("\nAusgabe 2 testSeDeserialize\n");
    testSeDeserialize(Fail, One);
    printf("\nAusgabe 3 testSeDeserialize\n");
    testSeDeserialize(Finish, One);
    printf("\nAusgabe 4 testSeDeserialize\n");
    testSeDeserialize(Finish, Fifteen);
    printf("\nAusgabe 5 testSeDeserialize\n");
    testSeDeserialize(Finish, Last);

}