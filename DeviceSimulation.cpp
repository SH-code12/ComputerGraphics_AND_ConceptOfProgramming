#include <iostream>
using namespace std;
struct DeviceVtable;
struct Device
{
DeviceVtable* vtable;
};
struct DeviceVtable
{
// The constructor is not virtual so it does not exist here
void (*TurnOn)(Device*);
void (*TurnOff)(Device*);

};
void TurnOn(Device* device)
{
device->vtable->TurnOn(device);
}
void TurnOff(Device* device)
{
device->vtable->TurnOff(device);
}
// Printer
struct Printer
{
Device parent;

};
void PrinterTurnOn(Printer* printer)
{
    cout<<"Printer ready. \n";
}
void PrinterTurnOff(Printer* printer)
{
    cout<<"Printer is off. \n";
}


DeviceVtable printer_vtable=
{

(void(*)(Device*)) PrinterTurnOn,
(void(*)(Device*)) PrinterTurnOff

};
void printerInitialize(Printer* printer)
{
printer->parent.vtable=&printer_vtable;

}

// Scanner
struct Scanner
{
Device parent;

};
void ScannerTurnOn(Scanner* scanner)
{
    cout<<"Scanner ready. \n";
}
void ScannerTurnOff(Scanner* scanner)
{
    cout<<"Scanner is off. \n";
}


DeviceVtable scanner_vtable=
{

(void(*)(Device*)) ScannerTurnOn,
(void(*)(Device*)) ScannerTurnOff

};
void scannerInitialize(Scanner* scanner)
{
scanner->parent.vtable=&scanner_vtable;

}

int main()
{
Printer printer;
printerInitialize(&printer);

Scanner scanner;
scannerInitialize(&scanner);

Device* devices[2];
devices[0]=(Device*)&printer; // heroes[0]=&superman.parent;
devices[1]=(Device*)&scanner; // heroes[1]=&batman.parent;

TurnOn(devices[0]);
TurnOn(devices[1]);
TurnOff(devices[0]);
TurnOff(devices[1]);

return 0;
}