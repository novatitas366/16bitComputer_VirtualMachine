#include <iostream>
#include <fstream>
#include <stdio.h>
#include <bitset>
using namespace std;

void nuskaitymas(char *PC, ifstream &file){
    while(file.get(*(PC))){
        PC++;
    }
}
void instrukcijos(char opkodas, char *&PC, unsigned char regs[], char &Eflags, ifstream &filetext){
    *(PC+254) = 0b11110000 & *(PC+1);
    *(PC+254)= *(PC+254) >> 4;
    if(opkodas == 0x01){ //INC
        *(PC+255) = 0b00001111 & *(PC+1);
        regs[*(PC+255)] = regs[*(PC+255)] + 0b1;
        PC+=2;
        if (regs[*(PC+255)] == 0x00){
            Eflags = Eflags | 0b00001000;
        }
        else if(regs[*(PC+255)] != 0x00){
            Eflags = Eflags & 0b11110111;
        }
    }
    else if(opkodas == 0x02){//DEC
        *(PC+255) = 0b00001111 & *(PC+1);
        regs[*(PC+255)] = regs[*(PC+255)] - 0b1;
        PC+=2;
        if (regs[*(PC+255)] == 0x00){
            Eflags = Eflags | 0b00001000;
        }
        else if(regs[*(PC+255)] != 0x00){
            Eflags = Eflags & 0b11110111;
        }
    }
    else if(opkodas == 0x03){//MOV
        *(PC+255) = 0b00001111 & *(PC+1);
        *(PC+254) = 0b11110000 & *(PC+1);
        *(PC+254) = *(PC+254) >> 4;
        regs[*(PC+255)] = regs[*(PC+254)];
        PC+=2;
        if (regs[*(PC+255)] == 0x00){
            Eflags = Eflags | 0b00001000;
        }
        else if(regs[*(PC+255)] != 0x00){
            Eflags = Eflags & 0b11110111;
        }
    }
    else if(opkodas == 0x04){//MOVC
        regs[0] = *(PC + 1);
        PC+=2;
        if (regs[0] == 0x00){
            Eflags = Eflags | 0b00001000;
        }
        else if(regs[0] != 0x00){
            Eflags = Eflags & 0b11110111;
        }
    }
    else if(opkodas == 0x05){//LSL
        *(PC+255) = 0b00001111 & *(PC+1);
        regs[*(PC+255)] = regs[*(PC+255)] << 1;
        PC+=2;
        if (regs[*(PC+255)] == 0x00){
            Eflags = Eflags | 0b00001000;
        }
        else if(regs[*(PC+255)] != 0x00){
            Eflags = Eflags & 0b11110111;
        }
    }
    else if(opkodas == 0x06){//LSR
        *(PC+255) = 0b00001111 & *(PC+1);
        regs[*(PC+255)] = regs[*(PC+255)] >> 1;
        PC+=2;
        if (regs[*(PC+255)] == 0x00){
            Eflags = Eflags | 0b00001000;
        }
        else if(regs[*(PC+255)] != 0x00){
            Eflags = Eflags & 0b11110111;
        }
    }
    else if(opkodas == 0x07){//JMP
        
        PC = PC + *(PC + 1);
        
    }
    else if(opkodas == 0x08){//JZ
        if((Eflags & 0b00001000) == 0b00001000)
            PC = PC + *(PC+ 1);
        else PC+=2;
    }
    else if(opkodas == 0x09){//JNZ
        if((Eflags & 0b00001000) != 0b00001000)
            PC = PC + *(PC + 1);
        else PC+=2;
    }
    else if(opkodas == 0x0A){//JFE
        
        if( (Eflags & 0b00010000) == 0b00010000)
            PC = PC + *(PC+ 1);
        else PC+=2;
        
    }
    else if(opkodas == 0x0C){//ADD
        *(PC+255) = 0b00001111 & *(PC+1);
        *(PC+254) = 0b11110000 & *(PC+1);
        *(PC+254) = *(PC+254) >> 4;
        regs[*(PC+255)] = regs[*(PC+255)] + regs[*(PC+254)];
        if (regs[*(PC+255)] == 0x00){
            Eflags = Eflags | 0b00001000;
        }
        else if(regs[*(PC+255)] != 0x00){
            Eflags = Eflags & 0b11110111;
        }
        PC+=2;
    }
    else if(opkodas == 0x0D){//SUB
        *(PC+255) = 0b00001111 & *(PC+1);
        *(PC+254) = 0b11110000 & *(PC+1);
        *(PC+254) = *(PC+254) >> 4;
        regs[*(PC+255)] = regs[*(PC+255)] - regs[*(PC+254)];
        if (regs[*(PC+255)] == 0x00){
            Eflags = Eflags | 0b00001000;
        }
        else if(regs[*(PC+255)] != 0x00){
            Eflags = Eflags & 0b11110111;
        }
        PC+=2;
    }
    else if(opkodas == 0x0E){//XOR
        *(PC+255) = 0b00001111 & *(PC+1);
        *(PC+254) = 0b11110000 & *(PC+1);
        *(PC+254) = *(PC+254) >> 4;
        regs[*(PC+255)] = regs[*(PC+255)] ^ regs[*(PC+254)];
        if (regs[*(PC+255)] == 0x00){
            Eflags = Eflags | 0b00001000;
        }
        else if(regs[*(PC+255)] != 0x00){
            Eflags = Eflags & 0b11110111;
        }
        PC+=2;
    }
    else if(opkodas == 0x0F){//OR
        *(PC+255) = 0b00001111 & *(PC+1);
        *(PC+254) = 0b11110000 & *(PC+1);
        *(PC+254) = *(PC+254) >> 4;
        regs[*(PC+255)] = regs[*(PC+255)] | regs[*(PC+254)];
        if (regs[*(PC+255)] == 0x00){
            Eflags = Eflags | 0b00001000;
        }
        else if(regs[*(PC+255)] != 0x00){
            Eflags = Eflags & 0b11110111;
        }
        PC+=2;
    }
    else if(opkodas == 0x10){//IN
    *(PC+255)= 0b00001111 & *(PC+1);
        filetext >> regs[*(PC+255)];
        
        if(*(PC+255) == 0b00000000){
            Eflags = Eflags | 0b00001000;
        }
        else Eflags = Eflags & 0b11100111;


        if(filetext.eof()){
            Eflags = Eflags | 0b00010000;
        }
        else Eflags = Eflags & 0b11101111;
        PC+=2;
    }
    else if(opkodas == 0x11){//OUT
        *(PC+255) = 0b00001111 & *(PC+1);
        cout << regs[*(PC+255)];
        cout.flush();
        PC+=2;
    }
}

int main(){
    char RAM[256] = {0}; //Ram[255] = Rx, Ram[254] = Ry
    unsigned char regs[16] ={0};
    char Eflags = 0b00000010; //eof 4, zero 3
    char *PC;
    PC = RAM;
    ifstream file("decryptor.bin", ios::in | ios::binary);
    ifstream filetext ("q1_encr.txt");
    nuskaitymas(PC, file);
    while(true){
        char opkodas = *(PC);
        if(opkodas == 0x0B){
            break;
        }
        instrukcijos(opkodas, PC, regs, Eflags, filetext);
    }
}