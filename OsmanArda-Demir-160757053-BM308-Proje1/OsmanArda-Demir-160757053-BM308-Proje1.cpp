/*
	           Haz�rlayan : Osman Arda DEMIR
	           ��renci No : 160757053
	               B�l�m� : Bilgisayar M�hendisli�i
	   Dersin Ad� ve Kodu : PARALEL PROGRAMLAMAYA G�R�S, BM-308-50-50
   	             Proje No : 1
Dersi Veren ��retim �yesi : Dr. ��r. �yesi Tolga AYDIN
*/

#include <iostream>// Cout Cin
#include <fstream> // dosya i�lemleri
#include <sys/time.h>//struct timeval ve gettimeofday
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;
int main(int argc, char* argv[ ])
{
	void siralamaFonk(int* , int); // Diziyi K���kten B�y��e S�ralamam�z ��in Fonksiyonu
	ifstream dosyaOku(argv[1]); // Dosya A�ma i�lemi
	string arg=argv[1];
	int argumanBoyutu=arg.size(); // Arguman Boyutunu Al
	int satir,sutun;
	dosyaOku>>satir; //Dosyadan Sat�r Say�s�n� Oku
	dosyaOku>>sutun; //Dosyadan Sutun Say�s�n� Oku
	int diziBoyutu=satir*sutun;
	int *tekDiziPtr=new int[diziBoyutu];		   //Tek Boyutlu Dinamik Dizi Tan�mlama
	int **matrisPtr=new int*[satir];
	for(int f=0;f<satir;f++){
 		matrisPtr[f]=new int[sutun];         	   //�ki Boyutlu Dinamik Dizi Tan�mlama
	}
	int **ciktiMatrisPtr=new int*[satir];
	for(int p=0;p<satir;p++){
 		ciktiMatrisPtr[p]=new int[sutun];          //�ki Boyutlu Dinamik Dizi Tan�mlama
	}
	int sayac,yeniSayi;
	int temp;
	srand(time(0));
	
	for (int i = 0; i < satir; i++){
		for (int j = 0; j < sutun; j++)
	    {
	        dosyaOku>>matrisPtr[i][j];       // Dosyadan Okunan Matris iki Boyutlu Diziye At�lmas�
	    }
	}
	for (int q = 0; q < satir; q++){
    	for (int t = 0; t < sutun; t++)
	    {
	        tekDiziPtr[q*sutun+t]=matrisPtr[q][t];   // Dinamik �ki Boyutlu Dizinin Matrisinin Tek Boyutlu Diziye At�lmas�
	    }
	}
		
	dosyaOku.close();
	int boyut=25;
	int yedekPtr[boyut];   // yedek tek boyutlu dizi bu diziye okudu�umuz 5x5 matrisi at�caz.
	int a;
	struct timeval currentTime;
	double startTime,endTime,elapsedTime;
	
	// Ge�erli saatini alma. 2. arg�man NULL ��nk� saat dilimini umursam�yoruz
    	gettimeofday(&currentTime, NULL); //d�nemden itibaren saniyeler
		startTime=currentTime.tv_sec+(currentTime.tv_usec/1000000.0); 		
			/*S�resini �l�mek �stedi�imiz Filtreleme Burada*/	
					int x=0;
					while(x<satir-4)
					{
						int y=0;
						while(y<sutun-4)
						{
								a=0;
								for(int sa=x;sa<x+5;sa++)
								{
									for(int su=y;su<y+5;su++)
									{
										yedekPtr[a]=tekDiziPtr[sa*sutun+su]; // 5x5 matrisin elemanlar�n� yedek diziye ata.
										a++; // saya� 
									}
									
								}
								siralamaFonk(yedekPtr ,25); // Diziyi K���kten B�y��e S�ralamam�z ��in Fonksiyonu.
								yeniSayi=yedekPtr[12];    // K���kten B�y��e s�ralad���m�z dizinin ortas�ndaki say�y� al.
								tekDiziPtr[(x+2)*sutun+(y+2)]=yeniSayi; // tekDiziPtr ye yeni say�y� yaz.
								y++;
						}
					x++;	
					}	
				
				
	// Ger�ek Zaman� Al
    	gettimeofday(&currentTime, NULL); //Saniyeler
	endTime=currentTime.tv_sec+(currentTime.tv_usec/1000000.0);	
	// Zaman� Hesaplama ��lemleri
    	elapsedTime = endTime-startTime;
	cout << "Toplam Gecen Zaman (saniye cinsinden): " << elapsedTime << endl;
	
	
	string uzanti;
	int sayi=22;
	while(sayi<argumanBoyutu-4)
	{
		uzanti=uzanti+arg[sayi];     // Argumandaki dosyan�n ismini alma
		sayi++;
	}
	
	ofstream dosyaCikti(uzanti+"_filtered.txt");
	
	if (dosyaCikti.is_open())
  	{
  	for (int i = 0; i < satir; i++){
		for (int j = 0; j < sutun; j++)
	    {
	        ciktiMatrisPtr[i][j]=tekDiziPtr[i*sutun+j];       // Dosyadan Okunan Matris iki Boyutlu Diziye At�lmas�
	    }
	}
	for (int q = 0; q < satir; q++){
    	for (int t = 0; t < sutun; t++)
	    {
			dosyaCikti<<ciktiMatrisPtr[q][t]<<"\t";
		}
		dosyaCikti<<endl;
	}
	
	}
	dosyaCikti.close();

	delete []tekDiziPtr;
	for(int f=0;f<satir;f++){
		delete [ ] matrisPtr[f];   // Pointer Dizileri Bellekten Silme
	}
	delete []matrisPtr;
	for(int d=0;d<satir;d++){
		delete [ ] ciktiMatrisPtr[d];
	}
	delete []ciktiMatrisPtr;

	return 0;
}

void siralamaFonk(int dizi[], int x) {
  int tut;
  for(int a=0;a<x;a++)
	{		
		for(int b=a;b<x;b++)				// S�ralama Fonksiyonu
		{
			if(dizi[a]>dizi[b])
			{
				tut  =dizi[a];
				dizi[a]=dizi[b];
				dizi[b]=tut;
			}
		}
	}
}
