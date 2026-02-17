#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char board[50][50];
int queen[50][50];
int colUsed[50];
int regionUsed[256];

int N;
long long kasus = 0;
int pos[50];
clock_t last_display = 0;

int dr[8] = {-1,-1,-1,0,0,1,1,1};
int dc[8] = {-1,0,1,-1,1,-1,0,1};

void displayLive(int currentRow)
{
    system("cls");
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(i < currentRow && queen[i][j])
            {
                printf("#");
            }
            else if(i == currentRow)
            {
                if(j == pos[currentRow])
                    printf("#");
                else
                    printf("%c", board[i][j]);
            }
            else
            {
                printf("%c", board[i][j]);
            }
        }
        printf("\n");
    }
    fflush(stdout);
}

int validasi()
{
    memset(queen, 0, sizeof(queen));
    memset(colUsed, 0, sizeof(colUsed));
    memset(regionUsed, 0, sizeof(regionUsed));
    for(int r=0;r<N;r++)
    {
        int c=pos[r];
        if(colUsed[c])
        {
            return 0;
        }
        colUsed[c]=1;
        if(regionUsed[(int)board[r][c]])
        {
            return 0;
        }
        regionUsed[(int)board[r][c]]=1;
        queen[r][c]=1;
    }
    for(int r=0;r<N;r++)
    {
        int c=pos[r];
        for(int i=0;i<=7;i++)
        {
            int nr=r+dr[i];
            int nc=c+dc[i];
            if(nr>=0 && nc>=0 && nr<N && nc<N && queen[nr][nc])
            {
                return 0;
            }
        }
    }
    return 1;
}

int solve(int r)
{
    if(r==N)
    {
        kasus++;
        return validasi();
    }
    else
    {
        for(int c=0;c<N;c++)
        {
            pos[r]=c;
            clock_t now = clock();
            double elapsed = (double)(now - last_display) * 1000 / CLOCKS_PER_SEC;
            if(elapsed >= 300)
            {
                displayLive(r);
                last_display = now;
            }
            
            if(solve(r+1))
            {
                return 1;
            }
        }
        return 0;
    }
}

int validateInput()
{
    int region[256] = {0};
    int unique = 0;
    for (int i = 0; i < N; i++)
    {
        if ((int)strlen(board[i]) != N)
        {
            return 0;
        }
        for (int j = 0; j < N; j++)
        {
            if (!region[(int)board[i][j]])
            {
                region[(int)board[i][j]] = 1;
                unique++;
            }
        }
    }
    return unique == N;
}

void saveSolution(char board[50][50], int N, double waktu, long long kasus, int found)
{
    char name[100];
    char filename[120];
    printf("Masukkan nama file output: ");
    scanf("%s", name);

    sprintf(filename, "../test/%s.txt", name);

    FILE *f = fopen(filename, "w");
    if (f == NULL)
    {
        printf("Gagal membuat file\n");
        return;
    }

    if (!found)
    {
        fprintf(f, "\nTidak ada solusi\n\n");
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (queen[i][j])
                    fputc('#', f);
                else
                    fputc(board[i][j], f);
            }
            fputc('\n', f);
        }
    }
    fprintf(f, "\nWaktu pencarian: %f ms\n", waktu);
    fprintf(f, "Banyak kasus yang ditinjau: %lld\n", kasus);
    fclose(f);
    printf("Solusi berhasil disimpan\n");
}


int main()
{
    char filename[100];
    printf("Masukkan nama file input: ");
    scanf("%s", filename);

    FILE *f = fopen(filename, "r");
    if (!f)
    {
        printf("File tidak ditemukan!\n");
        return 1;
    }

    char line[100];
    N = 0;
    while (fgets(line, sizeof(line), f))
    {
        line[strcspn(line, "\n")] = 0;
        strcpy(board[N], line);
        N++;
    }
    fclose(f);
    if (!validateInput())
    {
        printf("Input tidak valid!\n");
        return 1;
    }

    clock_t mulai = clock();
    int found = solve(0);
    clock_t selesai = clock();

    double waktu = (double)(selesai - mulai) * 1000 / CLOCKS_PER_SEC;

    system("cls");
    if (!found)
    {   
        printf("Tidak ada solusi.\n");
    }

    else
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (queen[i][j])
                {
                    printf("#");
                }
                else
                {
                    printf("%c", board[i][j]);
                }
            }
            printf("\n");
        }
    }
    printf("\nWaktu pencarian: %f ms\n", waktu);
    printf("Banyak kasus yang ditinjau: %lld\n", kasus);
    char pilihan[10];
    printf("Apakah Anda ingin menyimpan solusi? (Ya/Tidak): ");
    scanf("%s", pilihan);

    if (strcmp(pilihan, "Ya") == 0 || strcmp(pilihan, "ya") == 0)
    {
        saveSolution(board, N, waktu, kasus, found);
    }
    return 0;
}
