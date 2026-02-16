# Tucil1_13524046
Penyelesaian Permainan Queens Linkedin Brute Force
## Penjelasan Singkat Program

Program ini dibuat untuk menyelesaikan permasalahan **N-Queens dengan tambahan constraint region**, yaitu setiap queen harus ditempatkan sedemikian rupa sehingga:

1. Tidak ada dua queen yang berada pada **kolom yang sama**.
2. Tidak ada dua queen yang berada pada **sel bertetangga** (8 arah: horizontal, vertikal, diagonal).
3. Tidak ada dua queen yang berada dalam **region yang sama**.
4. Setiap baris harus mengandung **tepat satu queen**.

Program membaca konfigurasi papan dari file input `.txt`, kemudian mencari solusi menggunakan metode brute force, dan menampilkan hasil solusi beserta waktu eksekusi dan banyak kasus yang ditinjau.

Program juga menyediakan opsi untuk **menyimpan solusi ke dalam file output `.txt`**.

---

## Requirement Program dan Instalasi

### Perangkat Lunak:
- **Compiler C** (disarankan: `gcc`)
- Sistem operasi:
  - Windows (MinGW / MSYS2 / WSL)
  - Linux
  - macOS

### Instalasi Compiler (Windows - MSYS2):
pacman -S mingw-w64-x86_64-gcc

## Cara Mengkompilasi Program

###Struktur Program
├── src/
│   └── Tucil1 murni.c
│   └── test1.txt
│   └── test2.txt
│   └── test3.txt
│   └── test4.txt
│   └── test5.txt
├── bin/
│   └── Tucil1.exe
├── test/
│   └── Jb test1.txt
│   └── Jb test2.txt
│   └── Jb test3.txt
│   └── Jb test4.txt
│   └── Jb test5.txt

###Kompilasi Program
Masuk ke folder src dengan cara 
cd src

kemudian
gcc "Tucil1 murni.c" -o ../bin/Tucil1.exe

##Cara Menjalankan dan Menggunakan Program

###Menjalankan Program

Dari folder src
../bin/Tucil1.exe

###Menggunakan Program

Taruhlah file yang hendak diinput pada folder.
Program akan meminta untuk memasukkan nama file input.
Setelahnya, program akan menampilkan 20 konfigurasi terakhir sebagai Live Update dan konfigurasi yang terakhir adalah jawaban, beserta menampilkan waktu eksekusi dan banyaknya kasus yang ditinjau.
Setelah itu, program akan menanyakan apakah jawaban hendak disimpan dalam file output, apabila menjawab ya, maka bisa memberikan penamaan file output.
File output akan disimpan pada folder test.

##Author:
Nama : Farrell
NIM : 13524046
