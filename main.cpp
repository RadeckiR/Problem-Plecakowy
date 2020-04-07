#include <fstream>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <cmath>

using namespace std;
struct przedmiot
	{
		int s;		//	size, rozmiar
		int v;			//value, wartosc
	};








void quickSort2(float *tab, int *tab2, int *tab3, int x, int y) {
    int i= x;
    int j=y;
     int k = tab[(x+y)/2];

       do{
        while (tab[i] < k){i++;} ;
        while (tab[j] > k){j--;};
        if (i<=j)

         {  //cout<<"hihih  "<<lista[i] << " " << lista[j] << endl;
            swap(tab[i], tab[j]);
			swap(tab2[i], tab2[j]);
			swap(tab3[i], tab3[j]);
            j--;
            i++;

        }
}   while( j>i );
if ( x < j ) quickSort2(tab, tab2, tab3, x, j);
if ( y > i ) quickSort2(tab, tab2, tab3, i, y);

return;
}
/*void usunPlecak(przedmiot*plecak, przedmiot* muzeum)
{


	if (plecak)
	{
		delete[] plecak;
		plecak = nullptr;
	}
}
*/
void stworz_muzeum(int n, przedmiot * muzeum)
{
	//int pojemnosc_plecaka = n;

	//int ilosc_muzeum = n;
	int rozmiar, wartosc;
	for (int i = 0; i < n; i++)
	{
		rozmiar = (rand() % n) + 1;
		wartosc = (rand() % (2*n)) + 1;

		muzeum[i].s = rozmiar;
		muzeum[i].v = wartosc;
	}
	return;
}

void zadanie_stworz(przedmiot * muzeum)
{
	//pojemnosc_plecaka = 16;
	//muzeum = new przedmiot[5];
	//ilosc_muzeum = 5;
	//int rozmiar, wartosc;

	muzeum[0].s = 2;
	muzeum[0].v = 2;
	muzeum[1].s = 9;
	muzeum[1].v = 7;
	muzeum[2].s = 5;
	muzeum[2].v = 6;
	muzeum[3].s = 13;
	muzeum[3].v = 16;
	muzeum[4].s = 2;
	muzeum[4].v = 4;

	return;
}

void pokaz_muzeum(przedmiot * muzeum, int ilosc_muzeum)
{
	if (!muzeum)
		std::cout << "BRAK OTOCZENIA";
	else
	{
		std::cout << "muzeum: [rozmiar / wartosc]\n";
		for (int i = 0; i < ilosc_muzeum; i++)
		{
			std::cout << "|" << muzeum[i].s << "  " << muzeum[i].v << "| ";
		}
		std::cout << std::endl;
	}
}



void zachlanny(int *wartosc_ilosc ,przedmiot * plecak, przedmiot * muzeum, int pojemnosc_plecaka,int ilosc_muzeum )
{
	float w;
	float obecna_wartosc, obecny_rozmiar;
	float *tablica_wspolczynnikow = new float[ilosc_muzeum];
	int *tablica_rozmiarow = new int[ilosc_muzeum];
	int *tablica_wartosci = new int[ilosc_muzeum];

	for (int i = 0; i < ilosc_muzeum; i++)
	{
		obecna_wartosc = muzeum[i].v;
		obecny_rozmiar = muzeum[i].s;
		w = (float)(obecna_wartosc / obecny_rozmiar);
		tablica_wspolczynnikow[i] = rint(w);
		tablica_rozmiarow[i] = obecny_rozmiar;
		tablica_wartosci[i] = obecna_wartosc;
	}
	quickSort2(tablica_wspolczynnikow, tablica_rozmiarow, tablica_wartosci, 0, ilosc_muzeum-1);

	std::cout << "Posortowane:" << std::endl;
	std::cout << "wspolczynniki: ";
	for (int i = ilosc_muzeum-1;i>=0 ; i--)
	{
	//	std::cout << tablica_wspolczynnikow[i] << ", ";
	}
	std::cout << std::endl;
	std::cout << "wartosci: ";
	for (int i = ilosc_muzeum-1; i>=0; i--)
	{
		std::cout << tablica_wartosci[i] << ", ";
	}
	std::cout << std::endl;
	std::cout << "rozmiary: ";
	for (int i = ilosc_muzeum-1;i>=0 ; i--)
	{
		std::cout << tablica_rozmiarow[i] << ", ";
	}
	std::cout << std::endl;

	int rozmiar = 0;
	for (int i = ilosc_muzeum-1; i >=0; i--)
	{
		if (rozmiar + tablica_rozmiarow[i] <= pojemnosc_plecaka)
		{
			plecak[wartosc_ilosc[1]].s = tablica_rozmiarow[i];
			plecak[wartosc_ilosc[1]].v = tablica_wartosci[i];
			wartosc_ilosc[1]++;
			wartosc_ilosc[0] += tablica_wartosci[i];
			rozmiar += tablica_rozmiarow[i];
		}
	}
	delete[] tablica_wartosci;
	delete[] tablica_wspolczynnikow;
	delete[] tablica_rozmiarow;

	return;
}

void wyczerpujacy(int *wartosc_ilosc, przedmiot * plecak, przedmiot * muzeum, int pojemnosc_plecaka, int ilosc_muzeum  )
{
	//plecak = new przedmiot[ilosc_muzeum];
	int najlepsza_wartosc = 0;
	int obecny_rozmiar = 0;
	int obecna_wartosc = 0;
	int *tablica = new int[ilosc_muzeum];
	for (int i = 0; i < ilosc_muzeum; i++)
		tablica[i] = i;
	stack <int> kombinacja;

	for (unsigned i = (1 << ilosc_muzeum); --i; )
	{
		for (unsigned k = 0; k < ilosc_muzeum; ++k)
			if ((i >> k) & 1)
			{
				kombinacja.push(tablica[k]);
				obecny_rozmiar += muzeum[k].s;
				obecna_wartosc += muzeum[k].v;
			}
		if (obecna_wartosc > najlepsza_wartosc && obecny_rozmiar <= pojemnosc_plecaka)
		{
			wartosc_ilosc[1] = 0;
			najlepsza_wartosc = obecna_wartosc;
			wartosc_ilosc[0] = najlepsza_wartosc;
			while (!kombinacja.empty())
			{
				int aktualna = kombinacja.top();
				plecak[wartosc_ilosc[1]].s = muzeum[aktualna].s;
				plecak[wartosc_ilosc[1]].v = muzeum[aktualna].v;
				wartosc_ilosc[1]++;
				kombinacja.pop();
			}
		}
		obecna_wartosc = 0;
		obecny_rozmiar = 0;
		while (!kombinacja.empty())
			kombinacja.pop();
	}
	delete[] tablica;
}

void programowanie_dynamiczne(int *wartosc_ilosc,int **tablica ,przedmiot * muzeum,  int pojemnosc_plecaka, int ilosc_muzeum )
{

	for (int i = 0; i <=pojemnosc_plecaka; i++)
	{
		tablica[i] = new int[ilosc_muzeum+1];
		tablica[i][0] = 0;
		std::cout << tablica[i][0] << "\t";
	}
	std::cout << std::endl;
	int najlepszy = 0;

	for (int i = 1; i <= ilosc_muzeum; i++)
	{
		for (int j = 0; j <= pojemnosc_plecaka; j++)
		{
			if (j < muzeum[i - 1].s)
			{
				tablica[j][i] = tablica[j][i - 1];
				najlepszy = fmax(najlepszy, tablica[j][i]);
				std::cout << tablica[j][i] << "\t";
			}
			else
			{
				tablica[j][i] = fmax(tablica[j - muzeum[i - 1].s][i-1] + muzeum[i - 1].v, tablica[j][i - 1]);
				najlepszy = fmax(najlepszy, tablica[j][i]);
				std::cout << tablica[j][i] << "\t";
			}
		}
		std::cout << std::endl;
	}

	/*for (int i = 1; i <= pojemnosc_plecaka; i++)
		tablica[i] = -1;

	for (int i = 0; i < ilosc_muzeum; i++)
		for (int j = pojemnosc_plecaka; j >= 0; j--)
			if (!((j - muzeum[i].s < 0) || (tablica[j - muzeum[i].s] < 0)))
			{
				tablica[j] = fmax(tablica[j - muzeum[i].s] + muzeum[i].v, tablica[j]);
				if (tablica[j] > najlepszy)
					najlepszy = tablica[j];
			}*/
	wartosc_ilosc[0] = najlepszy;

	for (int i = 0; i < ilosc_muzeum; i++)
		delete[] tablica[i];

	delete[] tablica;
}


void pokaz_plecak(int *wartosc_ilosc, przedmiot * plecak, int pojemnosc_plecaka)
{
	if (!plecak)
	{
		std::cout << "Plecak pusty"<< "\n";

	}
	else
	{
		cout << "Pojemnosc plecaka: " << pojemnosc_plecaka << " Wartosc plecaka: " << wartosc_ilosc[0] << " Ilosc przedmiotow w plecaku " << wartosc_ilosc[1] << endl;
		cout << "Przedmioty w plecaku: rozmiar|wartosc\n";
		for (int i = 0; i < wartosc_ilosc[1]; i++)
		{
			cout << "  " << plecak[i].s << "|" << plecak[i].v << "   ";
		}
		cout << endl;
	}

}



int main()
{
    std::fstream wynik1, wynik2,wynik3;
    wynik1.open("dynam.txt", std::ios::trunc | std::ios::out);
	wynik2.open("greedy.txt", std::ios::trunc | std::ios::out);
	wynik3.open("calkowite.txt", std::ios::trunc | std::ios::out);
srand(time(NULL));
    typedef std::chrono::high_resolution_clock Clock;


	srand(time(NULL));

	//int ilosc_plecak = 0;
	 //int ilosc_muzeum = 0;

	int* wartosc_ilosc = new int [2];          // 0 - wartosc przedmioutow plecaka .  1 -- ilosc przedmiotow w plecaku

	wartosc_ilosc[0]= 0;
	wartosc_ilosc[1]= 0;

//            // do dynamicznego


/*
  clock_t start, finish, czas_wyczerpujacy2;

    double czas_wyczerpujacy, czas_zachlanny, czas_dynamiczny,  t3, t4, czas, czas1;

for (int ilosc = 100; ilosc <=250; ilosc+=10)
{   przedmiot * plecak = new przedmiot[ilosc];

    int pojemnosc_plecaka=ilosc ;
       // pojemnosc_plecaka = 15;
        przedmiot *muzeum = new przedmiot[ilosc];

    stworz_muzeum(ilosc,muzeum);

	///wyczerpujacy:
		cout<<"wyczerpujacy"<<endl;

			 auto t1 = Clock::now();
    wyczerpujacy(wartosc_ilosc,plecak, muzeum, pojemnosc_plecaka, ilosc);

				auto t2 = Clock::now();
            czas_wyczerpujacy=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
            czas_wyczerpujacy2=(finish-start)/CLOCKS_PER_SEC;
    pokaz_plecak(wartosc_ilosc, plecak, pojemnosc_plecaka);
     wynik3<<ilosc<<" "<<czas_wyczerpujacy<<endl;
        delete[] plecak;
		plecak = nullptr;
			wartosc_ilosc[0]=0;
			wartosc_ilosc[1]=0;             //usuwanie przedmioutow z plecaka i reset pomiarow

			cout<<"czas:"<<czas_wyczerpujacy<<" ms"<<endl<< "albo:"<<czas_wyczerpujacy2<<"||||||||||||||||||||||||||||"<<endl;


///zachlanny:

		cout<<"zachlanny"<<endl;

    przedmiot * plecak2 = new przedmiot[ilosc];
			 t1 = Clock::now();
		start= clock();
    zachlanny(wartosc_ilosc, plecak2, muzeum, pojemnosc_plecaka, ilosc);
    finish= clock();
			t2 = Clock::now();
	 czas_wyczerpujacy2=((finish-start)/CLOCKS_PER_SEC)*1000;
            czas_zachlanny=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
            wynik2<<ilosc<<" "<<czas_zachlanny<<endl;
    pokaz_plecak(wartosc_ilosc, plecak2, pojemnosc_plecaka);

             //usuwanie przedmioutow z plecaka
            cout<<"czas:"<<czas_zachlanny<<" milliseconds"<<endl<<"-------------"<<endl;
            delete[] plecak2;
//		plecak2 = nullptr;
			wartosc_ilosc[0]=0;
			wartosc_ilosc[1]=0;

/// dynamiczne
     cout<<"dynamiczny"<<endl;
     int **tablicdyn = new int*[pojemnosc_plecaka+1];
    przedmiot * plecak3 = new przedmiot[ilosc];
		 t1 = Clock::now();
    programowanie_dynamiczne(wartosc_ilosc,tablicdyn,muzeum,pojemnosc_plecaka,ilosc);
	 	t2 = Clock::now();
            czas_dynamiczny=std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
            wynik1<<ilosc<<" "<<czas_dynamiczny<<endl;
    pokaz_plecak(wartosc_ilosc, plecak3, pojemnosc_plecaka);
         delete[] plecak3;
		plecak3 = nullptr;

			wartosc_ilosc[0]=0;
			wartosc_ilosc[1]=0;             //usuwanie przedmioutow z plecaka
            cout<<"czas:"<<czas_dynamiczny<<" milliseconds"<<endl<<"-------------"<<endl;
}
wynik1.close();
wynik2.close();
wynik3.close();
*/
cout<<"zadanie"<<endl;
int	pojemnosc_plecaka = 16;
int ilosc_zadanie = 5;
wartosc_ilosc[0]=0;
			wartosc_ilosc[1]=0;
 przedmiot * plecak4 = new przedmiot[ilosc_zadanie];
 przedmiot * plecak5 = new przedmiot[ilosc_zadanie];
 przedmiot * plecak6 = new przedmiot[ilosc_zadanie];
  przedmiot * muzeum4 = new przedmiot[ilosc_zadanie];
  przedmiot * muzeum5 = new przedmiot[ilosc_zadanie];
  przedmiot * muzeum6 = new przedmiot[ilosc_zadanie];
  zadanie_stworz(muzeum4);
  zadanie_stworz(muzeum5);
  zadanie_stworz(muzeum6);
  pokaz_muzeum(muzeum4,ilosc_zadanie);


cout<<"WYCZERPUJACY"<<endl<<endl;

	 wyczerpujacy(wartosc_ilosc,plecak4, muzeum4, pojemnosc_plecaka, ilosc_zadanie);
     pokaz_plecak(wartosc_ilosc, plecak4, pojemnosc_plecaka);
            wartosc_ilosc[0]=0;
			wartosc_ilosc[1]=0;
cout<<"ZACHLANNY"<<endl<<endl;
 zachlanny(wartosc_ilosc, plecak5, muzeum5, pojemnosc_plecaka, ilosc_zadanie);
    pokaz_plecak(wartosc_ilosc, plecak5, pojemnosc_plecaka);
            wartosc_ilosc[0]=0;
			wartosc_ilosc[1]=0;
    cout<<"DYNAMICZNY"<<endl<<endl;
     int **tablica_zad = new int*[pojemnosc_plecaka+1];
    programowanie_dynamiczne(wartosc_ilosc,tablica_zad,muzeum6,pojemnosc_plecaka,ilosc_zadanie);
   // pokaz_plecak(wartosc_ilosc,plecak6,pojemnosc_plecaka);            */
	return 0;
}



/*
int main(){
przedmiot * muzeum = new przedmiot[15];
 przedmiot *plecak = new przedmiot[15];
stworz_muzeum(15, muzeum);
pokaz_muzeum(muzeum, 15);

return 0;}
*/
