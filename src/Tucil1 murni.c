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

int dr[8] = {-1,-1,-1,0,0,1,1,1};
int dc[8] = {-1,0,1,-1,1,-1,0,1};


int q[20][50];
int front = 0, rear = 0, size = 0;


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

void pushQueue()
{
    if(size==20)
    {
        front=(front+1)%20;
        size--;
    }
    memcpy(q[rear], pos, sizeof(int) * N);
    rear=(rear+1)%20;
    size++;
}

int solve(int r)
{
    if(r==N)
    {
        kasus++;
        pushQueue();
        return validasi();
    }
    else
    {
        for(int c=0;c<N;c++)
        {
            pos[r]=c;
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
        printf("File tidak ditemukan\n");
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
        printf("Input tidak valid\n");
        return 1;
    }

    clock_t mulai = clock();
    int found = solve(0);
    clock_t selesai = clock();

    double waktu = (double)(selesai - mulai) * 1000 / CLOCKS_PER_SEC;

    printf("20 Konfigurasi Terakhir\n\n");

    int idx = front;

    for (int k = 0; k < size; k++)
    {
        printf("Percobaan ke-%lld:\n", kasus - size + k + 1);

        for (int r = 0; r < N; r++)
        {
            for (int c = 0; c < N; c++)
            {
                if (c == q[idx][r])
                {
                    printf("#");
                }
                else
                {
                    printf("%c", board[r][c]);
                }
            }
            printf("\n");
        }
        printf("\n");
        idx = (idx + 1) % 20;
    }
    printf("\nWaktu pencarian: %f ms\n", waktu);
    printf("Banyak kasus yang ditinjau: %lld kasus\n", kasus);
    if (!found)
    {
        printf("\nTidak ada solusi\n\n");
    }
    char pilihan[10];
    printf("Apakah Anda ingin menyimpan solusi? (Ya/Tidak) ");
    scanf("%s", pilihan);

    if (strcmp(pilihan, "Ya") == 0 || strcmp(pilihan, "ya") == 0)
    {
        saveSolution(board, N, waktu, kasus, found);
    }
    return 0;
}