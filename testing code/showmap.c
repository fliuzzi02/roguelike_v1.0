#include<stdio.h>

char convert(int n);
void printmap(int *map, int rig, int col);
void fillmap(FILE *in, int *map, int rig, int col);
void findmapsize(FILE *in, int *rig, int *col);

int main(){
    FILE *in;
    in = fopen("files/map1.txt","r");
    int rig, col;

    findmapsize(in, &rig, &col); //cerca la dimensione della mappa

    int map[rig][col];//dichiaro l'array che conterrà la mappa

    fillmap(in, &map, rig, col);//riempio l'array con i valori dal file

    printmap(&map, rig, col);//stampo l'array ottenuto

    fclose(in);
}

void fillmap(FILE *in, int *map, int rig, int col){
    int i,j;
    for(i=0;i<rig;i++){
        for(j=0;j<col;j++){
            *(map+i*col+j) = fgetc(in) - '0';
            fseek(in, 1, SEEK_CUR);
        }
        fseek(in, 1, SEEK_CUR);
    }
}

void printmap(int *map, int rig, int col){
    int i,j;
    for(i=0;i<rig;i++){
        for(j=0;j<col;j++){
            printf("%c  ",convert(*(map+i*col+j)));
        }
        printf("\n");
    }
}

char convert(int n){
    if(n==1)return '#';
    if(n==0)return ' ';
    if(n==2)return 'T';
    if(n==3)return 'A';
}

void findmapsize(FILE *in, int *rig, int *col){
    int size[2] = {0,0};
    int i=0,j=0;
    char c='a';

    while(c!='\n'){ //leggo prima riga file con dimensioni mappa
        c = fgetc(in);
        if(c!='\n'){
            size[i]=c-'0';
            i++;
        }
    }
    if(size[1]==0) size[1]=size[0];
    *rig = size[0];
    *col = size[1];
}