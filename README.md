# Genetic Algorithm
Genetic algorithm (GA) adalah heuristik penelusuran yang terinspirasi oleh teori
evolusi alam Charles Darwin. Algoritma ini mencerminkan proses seleksi alam di mana
individu-individu yang paling cocok dipilih untuk reproduksi guna menghasilkan
keturunan dari generasi berikutnya.


![Alt text](https://user-images.githubusercontent.com/55073908/140613329-336d20b5-8dc0-4edf-a823-721352be7bae.png)


## Desain Kromosom dan Metode Pengkodean
Kromosom adalah Cetak biru (sekumpulan parameter) yang menentukan solusi
yang diusulkan untuk masalah tersebut. Genotype adalah nilai gen dari tiap kromosom
sedangkan phenotype adalah nilai asli dari kromosom.
Pertama saya melakukan representasi individu menggunakan desain kromosom
dengan metode value encoding dengan tipe double dengan panjang kromosomnya yaitu 2
(panjang array) dengan fungsi :
```
                          h(x, y) = (cos(x^2) * sin(y^2)) + (x+y)
```
Batasannya :
```
                                  −1 ≤ x ≤ 2 dan −1 ≤ y ≤ 1
```

### Contoh Kasus
Misalkan kita memiliki kromosom A dan B dengan value float dan string.

![Alt text](https://user-images.githubusercontent.com/55073908/140613445-68fb56ac-479c-4c93-83b7-06c44830830f.png)


## Ukuran populasi dan generasi
Ukuran populasi dan generasi yang saya gunakan pada uji coba kali ini yaitu 50
pada setiap generasinya dan ukuran generasi yang digunakan adalah 500 generasi.


## Fitness
Fitness merupakan nilai kualitas kromosom. Dimana solusi yang baik adalah yang
memiliki nilai fitness yang tinggi dan sebaliknya nilai fitness kecil maka akan buruk.
Pada kasus kali ini rumus fitness yang digunakan adalah f = h (nilai maksimum).


## Pemilihan orang tua
Proses pemilihan individu sebagai orang tua berfungsi untuk menghasilkan
keturunan baru untuk generasi selanjutnya.. Penyeleksian orang tua yang saya gunakan
pada tugas ini dilakukan dengan memilih orang tua secara acak dengan single point
crossover, pemilihan acak ini berdasarkan peluang yang sudah didefinisikan yaitu
peluang persilangan sebesar 0.8.


## Crossover
Crossover adalah operator genetik yang digunakan untuk memvariasikan
pemrograman kromosom atau kromosom dari satu generasi ke generasi berikutnya.
Untuk tugas ini metode crossover yang digunakan adalah single-point crossover dengan
probabilitas nya yaitu 80% (0.8). Cross point digunakan untuk menggabungkan anak
pertama dan anak kedua yang nantinya akan menghasiklan offspring yang lebih baik.

### Contoh Kasus

![Alt text](https://user-images.githubusercontent.com/55073908/140613517-8d97fe37-7c21-4c2a-acb0-8987c9f8b554.png)

![Alt text](https://user-images.githubusercontent.com/55073908/140613520-9811dbf7-e6bf-4410-9a04-ee308da73ded.png)


## Mutasi
Mutasi bertujuan untuk mensimulasikan pengaruh kesalahan yang terjadi dengan
probabilitas rendah selama duplikasi. Pada tugas ini mutasi dilakukan dengan
probabilitasnya yaitu mendekati 0.15


## Metode pergantian generasi (survivor selection)
Survivor selection adalah menentukan individu mana yang akan dikeluarkan dan
mana yang akan dipertahankan pada generasi berikutnya. Ini penting karena harus
memastikan bahwa individu yang lebih fitness tidak diusir dari populasi, sementara pada
saat yang sama keanekaragaman harus dipertahankan dalam populasi. Metode pergantian
generasi yang digunakan adalah metode generational replacement yang mana metode ini
akan mengganti seluruh individu dalam satu populasi tiap generasi. Terdapat metode
elitisme, yaitu menyalin kromosom dengan fitness terbaik pada satu generasi ke generasi
selanjutnya.


## Kriteria penghentian evolusi
Kriteria penghentian evolusi yang saya pilih adalah disaat generation sama
dengan max generation, jika syarat tersebut sudah terpenuhi maka evolusi akan berhenti
dan jika belum terpenuhi maka akan dilakukan perulangan lagi


# Hasil
Hasil running dari program source code yang telah saya lakukan didapatkan hasil
berupa generasi 0 - 499. Best fitness nya yaitu 2,48112. Lalu kromosom terbaiknya yaitu
0,868094 dan 0,999658. Dapat dilihat pada gambar dibawah ini:

![Alt text](https://user-images.githubusercontent.com/55073908/140613567-508e2445-af5d-4de9-acfe-7899042ef06b.png)
![Alt text](https://user-images.githubusercontent.com/55073908/140613574-dff9a388-4dbd-412c-ac15-686674f5e466.png)

(Gambar saya tampilkan setengah karena output yang sangat besar)


# Referensi
- https://towardsdatascience.com/introduction-to-genetic-algorithms-including-examplecodee396e98d8bf3#:~:text=A%20genetic%20algorithm%20is%20a,offspring%20of%20the%20next%20generation
- https://www.geeksforgeeks.org/encoding-methods-in-genetic-algorithm/
- https://www.geeksforgeeks.org/crossover-in-geneticalgorithm/#:~:text=Single%20Point%20Crossover%20%3A%20A%20crossover,between%20the%20two%20parent%20organisms.&text=Two%20random%20points%20are%20chosen,is%20exchanged%20at%20these%20points
- https://people.sc.fsu.edu/~jburkardt/cpp_src/simple_ga/simple_ga.html
