#include<stdio.h>
#include<time.h>
#include<stdlib.h>

typedef struct{
    int x;
    int y;
} player;

char convert(int n);
void printmap(int *map, int rig, int col);
void genera(int *map, int rig, int col);
void scava(int *map, int rig, int col, int x, int y, int xprec, int yprec);
int adiacenti(int *map, int rig, int col, int x, int y);
player move(int *map, player p1, char c, int col);
void credits();
void easter_egg();

void scava_sotto(int *map, int rig, int col, int x, int y);
void scava_sopra(int *map, int rig, int col, int x, int y);
void scava_destra(int *map, int rig, int col, int x, int y);
void scava_sinistra(int *map, int rig, int col, int x, int y);

int main(){
    credits();
    int rig;
    int col;
    char c = ' ';
    printf("Inserire numero colonne per giocare: ");
    scanf("%d%*c",&col);
    printf("Inserire numero righe per giocare: ");
    scanf("%d%*c",&rig);
    rig = rig - rig%10 +3;
    col = col - col%10 +5;
    int map[rig][col];

    //riempio la matrice di 1
    genera(&map, rig, col);

    //scelgo un punto casuale da dove cominciare a scavare la matrice
    time_t t;
    srand((unsigned) time(&t));
    int rigini = rand()%(rig-2) + 2;
    int colini = rand()%(col-2) + 2;
    if(rigini%2 == 0) rigini++;
    if(colini%2 == 0) colini++;
    scava(&map, rig, col, rigini, colini, 0, 0);

    //posizione giocatore e uscita
    map[1][1] = 2;
    map[rig-2][col-2] = 3;

    printmap(&map,rig,col);
    player p1;
    p1.x = 1;
    p1.y = 1;
    
    do{
        printf("\nChose your move (w,a,s,d; q to exit): ");
        scanf("%c%*c",&c);
        p1 = move(&map, p1, c, col);
        printf("\n");

        if(p1.x == col-2 && p1.y == rig-2){
            c = 'q';
            printf("HAI VINTO!!!\n");
            scanf("%c");
        }else{
            for(int i=0; i<100;i++) printf("\n");
            credits();
            printmap(&map,rig,col);            
        }
    }while(c!='q');

    easter_egg();

    return 0;
}

player move(int *map, player p1, char c, int col){
    int x = p1.x;
    int y = p1.y;
    if(c=='w'){
        if(*(&map[0]+(x-1)*col+y) != 1){
            *(&map[0]+(x-1)*col+y) = 2;
            *(&map[0]+(x)*col+y) = 0;
            x--;
        }
    }
    if(c=='a'){
        if(*(&map[0]+x*col+y-1) != 1){
            *(&map[0]+x*col+y-1) = 2;
            *(&map[0]+(x)*col+y) = 0;
            y--;
        }
    }
    if(c=='s'){
        if(*(&map[0]+(x+1)*col+y) != 1){
            *(&map[0]+(x+1)*col+y) = 2;
            *(&map[0]+(x)*col+y) = 0;
            x++;
        }
    }
    if(c=='d'){
        if(*(&map[0]+x*col+y+1) != 1){
            *(&map[0]+x*col+y+1) = 2;
            *(&map[0]+(x)*col+y) = 0;
            y++;
        }
    }
    p1.x=x;
    p1.y=y;

    return p1;
}

void scava(int *map, int rig, int col, int x, int y, int xprec, int yprec){
    time_t t;
    srand((unsigned) time(&t));
    int n = 0;

    /*while(adiacenti(map, rig, col, x, y)){
        n = rand()%4;

        if(n==0 && possogiu(map, rig, col, x, y) == 1){
            scava_sotto(map, rig, col, x, y);
            scava(map, rig, col, x+2, y, x, y);
        }
        if(n==1 && possosu(map, rig, col, x, y) == 2){
            scava_sopra(map, rig, col, x, y);
            scava(map, rig, col, x-2, y, x, y);
        }
        if(n==2 && possodx(map, rig, col, x, y) == 3){
            scava_destra(map, rig, col, x, y);
            scava(map, rig, col, x, y+2, x, y);
        }
        if(n==3 && possosx(map, rig, col, x, y) == 4){
            scava_sinistra(map, rig, col, x, y);
            scava(map, rig, col, x, y-2, x, y);
        }

        printmap(map, rig, col);
    }*/

    while(adiacenti(map, rig, col, x, y)){
        n = rand()%4;

        if(n==0 && (x<rig-2 && *(&map[0]+(x+2)*col+y) != 0)){
            scava_sotto(map, rig, col, x, y);
            scava(map, rig, col, x+2, y, x, y);
        }
        if(n==1 && (x>2 && *(&map[0]+(x-2)*col+y) != 0)){
            scava_sopra(map, rig, col, x, y);
            scava(map, rig, col, x-2, y, x, y);
        }
        if(n==2 && (y<col-2 && *(&map[0]+x*col+y+2) != 0)){
            scava_destra(map, rig, col, x, y);
            scava(map, rig, col, x, y+2, x, y);
        }
        if(n==3 && (y>2 && *(&map[0]+x*col+y-2) != 0)){
            scava_sinistra(map, rig, col, x, y);
            scava(map, rig, col, x, y-2, x, y);
        }

        //printmap(map, rig, col);
    }
}

int adiacenti(int *map, int rig, int col, int x, int y){
    int n = 0;
    if(x<rig-2 && *(&map[0]+(x+2)*col+y) != 0) n++; //sotto
    if(x>2 && *(&map[0]+(x-2)*col+y) != 0) n++; //sopra
    if(y<col-2 && *(&map[0]+x*col+y+2) != 0) n++; //destra
    if(y>2 && *(&map[0]+x*col+y-2) != 0) n++; //sinistra
    return n;
}

void scava_sotto(int *map, int rig, int col, int x, int y){
    *(&map[0]+(x+1)*col+y) = 0;
    *(&map[0]+(x+2)*col+y) = 0;
}
void scava_sopra(int *map, int rig, int col, int x, int y){
    *(&map[0]+(x-1)*col+y) = 0;
    *(&map[0]+(x-2)*col+y) = 0;
}
void scava_destra(int *map, int rig, int col, int x, int y){
    *(&map[0]+x*col+y+1) = 0;
    *(&map[0]+x*col+y+2) = 0;
}
void scava_sinistra(int *map, int rig, int col, int x, int y){
    *(&map[0]+x*col+y-1) = 0;
    *(&map[0]+x*col+y-2) = 0;
}

char convert(int n){
    if(n==1)return '#';
    if(n==0)return ' ';
    if(n==2)return 'T';
    if(n==3)return 'O';
}

void printmap(int *map, int rig, int col){
    int i,j;
    for(i=0;i<rig;i++){
        for(j=0;j<col;j++){
            printf("%c ",convert(*(&map[0]+i*col+j)));
        }
        printf("\n");
    }
    printf("\n");
}

void genera(int *map, int rig, int col){
    int i,j;

    for(i=0;i<rig;i++){
        for(j=0;j<col;j++){
            *(&map[0]+i*col+j) = 1;
        }
    }
    //*(&map[0]+col+1) = 2;
    //*(&map[0]+((rig-2)*col)+col-2) = 3;
    //*(&map[0]+3*col+2) = 4; //stringa di test indici    
}

void credits(){
    printf("ROGUELIKE v1.0 \nWritten in C by fliuzzi02\n\nYou are the T in the map, reach the O\nHave fun!\n\n");
}

void easter_egg(){
    FILE *in;
    in = fopen("il_ritorno.txt", "w");
    fprintf(in, "Il Ritorno\n\nL\'aereo si stacca da terra,\nil tuo cuore con lui.\nCome il cherosene nei motori,\nil sorriso irrompe sulle labbra.\nE brucia dentro te quel sentimento nuevo,\nche ti tiene alta la vita.\nEd è bellissimo perdersi.\n\nFederico Liuzzi");
    fclose(in);
}