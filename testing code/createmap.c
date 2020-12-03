#include<stdio.h>

char convert(int n);
void printmap(int *map, int rig, int col);
void genera(int *map, int rig, int col);
void scava(int *map, int rig, int col);
void scava_sotto(int *map, int rig, int col, int *x, int *y, int *b);
void scava_sopra(int *map, int rig, int col, int *x, int *y, int *b);
void scava_destra(int *map, int rig, int col, int *x, int *y, int *b);
void scava_sinistra(int *map, int rig, int col, int *x, int *y), int *b;
void savemap(char filename[], int *map, int rig, int col);

int main(){
    int rig = 25;
    int col = 25;
    /*printf("Inserire dimensione: ");
    scanf("%d%*c",&dim);*/
    float map[rig][col];

    genera(&map,rig,col);
    scava(&map, rig, col);

    printmap(&map,rig,col);
    printf("\n\nInserisci nome mappa: ");
    char filename[20];
    scanf("%s",filename);
    savemap(filename, &map, rig, col);
}

void scava_sotto(int *map, int rig, int col, int *x, int *y, int *b){
    int i = *x;
    int j = *y;
    int cell = *(&map[0]+(i+2)*col+j);
    if(i<rig-3 && cell!=0 && cell!=3 && cell!=2){//scava_sotto
        *(&map[0]+(i+1)*col+j) = 0;
        *(&map[0]+(i+2)*col+j) = 0;
        i=i+2;
        *x = i;
    }
    else{
        *b++;
    }
}
void scava_sopra(int *map, int rig, int col, int *x, int *y, int *b){
    int i = *x;
    int j = *y;
    int cell = *(&map[0]+(i-2)*col+j);
    if(i>2 && cell!=0 && cell!=3 && cell!=2){//scava_sotto
        *(&map[0]+(i-1)*col+j) = 0;
        *(&map[0]+(i-2)*col+j) = 0;
        i=i-2;
        *x = i;
    }
    else{
        *b++;
    }
}
void scava_destra(int *map, int rig, int col, int *x, int *y, int *b){
    int i = *x;
    int j = *y;
    int cell = *(&map[0]+i*col+j+2);
    if(j<col-3 && cell!=0 && cell!=3 && cell!=2){//scava_sotto
        *(&map[0]+i*col+j+1) = 0;
        *(&map[0]+i*col+j+2) = 0;
        j=j+2;
        *y = j;
    }
    else{
        *b++;
    }
}
void scava_sinistra(int *map, int rig, int col, int *x, int *y, int *b){
    int i = *x;
    int j = *y;
    int cell = *(&map[0]+i*col+j-2);
    if(j>2 && cell!=0 && cell!=3 && cell!=2){//scava_sotto
        *(&map[0]+i*col+j-1) = 0;
        *(&map[0]+i*col+j-2) = 0;
        j = j -2;
        *y = j;
    }
    else{
        *b++;
    }
}

void scava(int *map, int rig, int col){
    int i=1;
    int j=1;
    int finito = 0;
    int bloccato = 0;
    //*(map+(i*col)+(j))

    time_t t;
    srand((unsigned) time(&t));
    int n;

    while(!finito && bloccato<rig*col){
        n = rand()%4;
        if(n==0) scava_sotto(map, rig, col, &i, &j, &bloccato);
        if(n==1) scava_sopra(map, rig, col, &i, &j, &bloccato);
        if(n==2) scava_destra(map, rig, col, &i, &j, &bloccato);
        if(n==3) scava_sinistra(map, rig, col, &i, &j, &bloccato);

        if(*(&map[0]+(i*col)+(j+1)) == 3 || *(&map[0]+((i+1)*col)+(j)) == 3) finito = 1;
        else if(bloccato>4){
            torna();
        }
    }
}

void genera(int *map, int rig, int col){
    int i,j;

    for(i=0;i<rig;i++){
        for(j=0;j<col;j++){
            *(&map[0]+i*col+j) = 1;
        }
    }
    *(&map[0]+col+1) = 2;
    *(&map[0]+((rig-2)*col)+col-2) = 3;
    //*(&map[0]+3*col+2) = 4; //stringa di test indici    
}

void printmap(int *map, int rig, int col){
    int i,j;
    for(i=0;i<rig;i++){
        for(j=0;j<col;j++){
            printf("%c ",convert(*(&map[0]+i*col+j)));
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

void savemap(char filename[], int *map, int rig, int col){
    FILE *in;
    int i,j;
    char temp[40];
    sprintf(temp,"files/%s.txt", filename);
    printf("\n%s",temp);
    in = fopen(temp, "w");
    fprintf(in,"%d %d\n",rig, col);

    for(i=0;i<rig;i++){
        for(j=0;j<col;j++){
            fprintf(in,"%d ", *(map+i*col+j));
        }
        fprintf(in,"\n");
    }
    fclose(in);
}