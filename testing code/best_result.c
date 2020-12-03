#include<stdio.h>

char convert(int n);
void printmap(int *map, int rig, int col);
void genera(int *map, int rig, int col);
void scava(int *map, int rig, int col, int x, int y, int xprec, int yprec);
int adiacenti(int *map, int rig, int col, int x, int y);

void scava_sotto(int *map, int rig, int col, int x, int y);
void scava_sopra(int *map, int rig, int col, int x, int y);
void scava_destra(int *map, int rig, int col, int x, int y);
void scava_sinistra(int *map, int rig, int col, int x, int y);

int main(){
    int rig = 33;
    int col = 39;
    char c;
    // int dim;
    // printf("Inserire dimensione: ");
    // scanf("%d%*c",&dim);
    int map[rig][col];
    // rig = dim;
    // col = dim;

    genera(&map,rig,col);

    scava(&map, rig, col, 1, 3, 1, 3);
    map[1][1] = 2;
    map[rig-2][col-2] = 3;

    printmap(&map,rig,col);

    printf("\n Press enter to exit...");
    scanf("%c", &c);
    return 0;
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