/*
	This code has built based on https://people.sc.fsu.edu/~jburkardt/cpp_src/simple_ga/simple_ga.html
*/

# include <cmath>
# include <math.h>
# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <iomanip>
# include <ctime>
# include <cstring>

using namespace std;

# define jumlahPopulasi 50
# define generasiMaksimum 500
# define jumlahVariabel 2
# define peluangPersilangan 0.8
# define peluangMutasi 0.15

struct tipeGen
{
  double gen[jumlahVariabel];
  double fitness;
  double batasAtas[jumlahVariabel];
  double batasBawah[jumlahVariabel];
  double fitnessRelatif;
  double fitnessKumulatif;
};

struct batas 
{
      double bawah;
      double atas;
};

struct tipeGen populasi[jumlahPopulasi+1];
struct tipeGen populasiBaru[jumlahPopulasi+1]; 

void dekode_kromosom();
void pemilihanOrangTua(int &bibit);
void elitis();
void evaluasi();
int angkaAcakInt(int a, int b, int &bibit);
void inisialisasi(int &bibit);
void pertahankanTerbaik();
void mutasi(int &bibit);
double angkaAcakReal(double a, double b, int &bibit);
void lapor(int generasi);
void seleksi(int &bibit);
void persilangan(int genKesatu, int genKedua, int &bibit);

int main()
{
	
	  int bibit = 123456789;
	  inisialisasi(bibit);
	  evaluasi();
	  pertahankanTerbaik();

	  for(int generasi = 0; generasi < generasiMaksimum; generasi++) {
		  
			seleksi(bibit);
			pemilihanOrangTua(bibit);
			mutasi(bibit);
			lapor(generasi);
			evaluasi();
			elitis();
			
	  }

	  cout << "\n";
	  cout << "  Kromosom terbaik setelah " << generasiMaksimum << " generasi:\n";
	  cout << "\n";

	  dekode_kromosom();

	  cout << "\n";
	  cout << "  Fitness terbaik = " << populasi[jumlahPopulasi].fitness << "\n";
	  
	  return 0;
	  
}

void dekode_kromosom()
{
	
		for ( int i = 0; i < jumlahVariabel; i++ ) {
			
			  if(i==0) {
				  
				 cout << "  variabel(x) = " << populasi[jumlahPopulasi].gen[i] << "\n"; 
				 
			  } else {
				  
				 cout << "  variabel(y) = " << populasi[jumlahPopulasi].gen[i] << "\n"; 
				 
			  }	
	  }
	  
	  return;
  
}

void pemilihanOrangTua(int &bibit)
{
	
	  const double a = 0.0;
	  const double b = 1.0;
	  int genKesatu;
	  int gen = 0;
	  double peluangAcak;

	  for (int individu = 0; individu < jumlahPopulasi; ++individu) {
		  
			peluangAcak = angkaAcakReal(a, b, bibit);
			
			if (peluangAcak < peluangPersilangan) {
				
				  ++gen;
				  
				  if (gen % 2 == 0) {
					  
						persilangan(genKesatu, individu, bibit);
					
				  } else {
					  
						genKesatu = individu;
					
				  }
				  
			}
			
	  }
	  
	  return;
  
}


void elitis()
{
	
	  int individuTerbaik, individuTerburuk;
	  double terbaik = populasi[0].fitness;
	  double terburuk = populasi[0].fitness;

	  for (int i = 0; i < jumlahPopulasi - 1; ++i) {
		  
			if (populasi[i+1].fitness < populasi[i].fitness) {
		
				  if (terbaik <= populasi[i].fitness) {
					  
						terbaik = populasi[i].fitness;
						individuTerbaik = i;
						
				  }
			
				  if (populasi[i+1].fitness <= terburuk) {
					  
						terburuk = populasi[i+1].fitness;
						individuTerburuk = i + 1;
						
				  }
		
			} else {
				
				  if (populasi[i].fitness <= terburuk) {
					  
						terburuk = populasi[i].fitness;
						individuTerburuk = i;
						
				  }
			
				  if (terbaik <= populasi[i+1].fitness) {
					  
						terbaik = populasi[i+1].fitness;
						individuTerbaik = i + 1;
						
				  }
				  
			}
			
	  }
	  
	  if (populasi[jumlahPopulasi].fitness <= terbaik) {
		  
			for (int i = 0; i < jumlahVariabel; i++) {
				
				populasi[jumlahPopulasi].gen[i] = populasi[individuTerbaik].gen[i];
			  
			}
			
			populasi[jumlahPopulasi].fitness = populasi[individuTerbaik].fitness;
			
	  } else {
		  
			for (int i = 0; i < jumlahVariabel; i++) {
				
			  populasi[individuTerburuk].gen[i] = populasi[jumlahPopulasi].gen[i];
			  
			}
			
			populasi[individuTerburuk].fitness = populasi[jumlahPopulasi].fitness;
			
	  } 

	  return;
	  
}


void evaluasi()
{
	
	  double x[jumlahVariabel+1];
	  for ( int individu = 0; individu < jumlahPopulasi; individu++ ) {
			  
			for ( int i = 0; i < jumlahVariabel; i++ ) {
				
				x[i+1] = populasi[individu].gen[i];
			  
			} 
			
			populasi[individu].fitness = ( cos( (x[1]*x[1]) )  * sin( (x[2]*x[2]) ) ) + (x[1] + x[2]);
			
	  }
	  
	  return;
	  
}


int angkaAcakInt(int a, int b, int &bibit)
{
	
	  const int integerBesar = 2147483647;
	  int c, k, nilai;
	  float r;

	  if ( b < a ) {
		  
		c = a;
		a = b;
		b = c;
		
	  }

	  k = bibit / 127773;

	  bibit = 16807 * ( bibit - k * 127773 ) - k * 2836;

	  if ( bibit < 0 ) {
		  
		bibit = bibit + integerBesar;
		
	  }

	  r = (float) (bibit) * 4.656612875E-10;
	  r = (1.0 - r)*((float) a - 0.5) + r * ((float) b + 0.5);

	  nilai = round (r);
	  
	  if (nilai < a) {
		  
		nilai = a;
		
	  }
	  
	  if (b < nilai) {
		  
		nilai = b;
		
	  }

	  return nilai;
	  
}


void inisialisasi(int &bibit)
{
	
	  int i, j;
	  batas arrayBatas[jumlahVariabel] = {{-1.0,2.0},{-1.0,1.0}};

	  for ( i = 0; i < jumlahVariabel; i++ ) {
		  
			for ( j = 0; j < jumlahPopulasi; j++ ) {
				
				if(i==0) {
					
					populasi[j].fitness = 0;
					populasi[j].fitnessRelatif = 0;
					populasi[j].fitnessKumulatif = 0; 
					  
				}
				
				populasi[j].batasBawah[i] = arrayBatas[i].bawah;
				populasi[j].batasAtas[i]= arrayBatas[i].atas;
				populasi[j].gen[i] = angkaAcakReal(arrayBatas[i].bawah, arrayBatas[i].atas, bibit);
				
			}
		
	  }
	  
	  return;
}


void pertahankanTerbaik()
{
	
	  int terbaik_sekarang = 0;
	  
	  for ( int individu = 0; individu < jumlahPopulasi; individu++ ) {
			if ( populasi[jumlahPopulasi].fitness < populasi[individu].fitness ) {
				  terbaik_sekarang = individu;
				  populasi[jumlahPopulasi].fitness = populasi[individu].fitness;
			}
	  }
	  
	  for ( int i = 0; i < jumlahVariabel; i++ ) {
		  
		populasi[jumlahPopulasi].gen[i] = populasi[terbaik_sekarang].gen[i];
		
	  }
	  
	  return;
	  
}

void mutasi(int &bibit)
{
	
	  const double a = 0.0;
	  const double b = 1.0;
	  double bawah, atas, peluangAcak;

	  for ( int i = 0; i < jumlahPopulasi; i++ ) {
		  
			for ( int j = 0; j < jumlahVariabel; j++ ) {
				
				  peluangAcak = angkaAcakReal(a, b, bibit);
				  
				  if (peluangAcak < peluangMutasi) {
					  
						bawah = populasi[i].batasBawah[j];
						atas = populasi[i].batasAtas[j];  
						populasi[i].gen[j] = angkaAcakReal(bawah, atas, bibit);
						
				  }
			}
	  }

	  return;
}

double angkaAcakReal(double a, double b, int &bibit)
{
	
	  int integerBesar = 2147483647;
	  double nilai;

	  int k = bibit / 127773;

	  bibit = 16807 * ( bibit - k * 127773 ) - k * 2836;

	  if ( bibit < 0 ) {
		  
		bibit = bibit + integerBesar;
		
	  }

	  nilai = (double) (bibit) * 4.656612875E-10;

	  nilai = a + (b - a) * nilai;

	  return nilai;
}

void lapor(int generasi)
{
	
	  if (generasi == 0) {
			cout << "\n";
			cout << "  Nomor             Nilai  \n";
			cout << "  generasi          terbaik \n";
			cout << "\n";
	  }
	  
	  double nilaiTerbaik = populasi[jumlahPopulasi].fitness;	  
	  cout << "  " << setw(4) << generasi << "  " << setw(19) << nilaiTerbaik << "\n";
	  
	  return;
  
}

void seleksi ( int &bibit )
{
	
	  const double a = 0.0;
	  const double b = 1.0;
	  double peluangAcak;
	  double jumlah = 0.0;
	  
	  for ( int individu = 0; individu < jumlahPopulasi; individu++ ) {
		  
			jumlah += populasi[individu].fitness;
		
	  }

	  for ( int individu = 0; individu < jumlahPopulasi; individu++ ) {
		  
			populasi[individu].fitnessRelatif = populasi[individu].fitness / jumlah;
		
	  }

	  populasi[0].fitnessKumulatif = populasi[0].fitnessRelatif;
	  
	  for ( int individu = 1; individu < jumlahPopulasi; individu++ ) {
		  
			populasi[individu].fitnessKumulatif = populasi[individu-1].fitnessKumulatif + populasi[individu].fitnessRelatif;
			
	  }
  
	  for ( int i = 0; i < jumlahPopulasi; i++ ) { 
		  
			peluangAcak = angkaAcakReal(a,b,bibit);
			
			if (peluangAcak < populasi[0].fitnessKumulatif) {
				
					populasiBaru[i] = populasi[0]; 
					 
			} else {
				
				  for ( int j = 0; j < jumlahPopulasi; j++ ) { 
					  
						if ( populasi[j].fitnessKumulatif <= peluangAcak && peluangAcak < populasi[j+1].fitnessKumulatif ) {
							
						  populasiBaru[i] = populasi[j+1];
						  
						}
						
				  }
				  
			}
        
		}
  
	  for ( int i = 0; i < jumlahPopulasi; i++ ) {
		  
		populasi[i] = populasiBaru[i]; 
		
	  }
	  
	  return; 
		  
}

void persilangan(int genKesatu, int genKedua, int &bibit)
{
	
	  double sementara;
	  int titik = angkaAcakInt (0, jumlahVariabel - 1, bibit);

	  for ( int i = 0; i < titik; i++ ) {
		  
		sementara = populasi[genKesatu].gen[i];
		populasi[genKesatu].gen[i] = populasi[genKedua].gen[i];
		populasi[genKedua].gen[i]  = sementara;
		
	  }

	  return;
  
}   
