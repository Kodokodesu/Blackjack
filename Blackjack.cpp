#include <iostream>
#include <ctime>

using namespace std;

void tasowanie(bool talia[]);
void wyswietlanie_karty(int karta);
void wyswietlenie_reki(int reka[], const int wartosc_karty);
int dobranie_karty(bool talia[]);
int wartosc_w_rece(int reka[], const int wartosc_karty);
void wyswietl_wynik_i_reke(int reka_gospodarza[], const int wartosc_kart_gospodarza, int reka_gracza[], const int wartosc_kart_gracza);

int main() {

    cout << "Witamy w grze BlackJack!" << endl;

    cout << "Oto wartosci dla kart jakie przyjelismy w tej grze:" << endl << endl;
    cout << "Karty od 2 do 9 dowolnego koloru sa warte tyle co liczba jaka reprezentuja\n"
            "Karta 10(T) oraz figury Waleta(J), Krolowej(Q) i Krola(K) -  maja wartosc 10 punktow kazda\n"
            "As(A) przyjmuje wartosc 11" << endl << endl;
    cout << "Zaczynajmy!" << endl << endl;

	time_t czas;
	time(&czas);
	srand(czas);

	bool talia[52];
	int iHouseCardCount = 0;
	int iaHouseHand[12];
	int iPlayerCardCount = 0;
	int iaPlayerHand[12];
    int x = 1;
	while (true) {
        tasowanie(talia);

		// rozdanie dwoch kart do reki
		iaPlayerHand[0]		= dobranie_karty(talia);
		iaHouseHand[0]		= dobranie_karty(talia);
		iaPlayerHand[1]		= dobranie_karty(talia);
		iaHouseHand[1]		= dobranie_karty(talia);
		iHouseCardCount		= 2;
		iPlayerCardCount	= 2;

        //poczatek rundy
		cout << "----------------   !Nowa runda!    ----------------" << endl;


		char cPlayerChoice;
		bool bPlayerHits	= true;
		int iPlayerScore	= wartosc_w_rece(iaPlayerHand, iPlayerCardCount);
		do {

			cout << "Karty Gospodarza: " << endl;
			cout << "** ";
            wyswietlanie_karty(iaHouseHand[1]);
			cout << endl;
			cout << "Wynik z kart gracza:" << wartosc_w_rece(iaPlayerHand, iPlayerCardCount) << endl;
            wyswietlenie_reki(iaPlayerHand, iPlayerCardCount);


			cout << "Dobierz karte(d) albo spasuj(s)";
			cin >> cPlayerChoice;
			if (cPlayerChoice == 'd') {
				iaPlayerHand[iPlayerCardCount] = dobranie_karty(talia);
				++iPlayerCardCount;
			} else if (cPlayerChoice == 's') {
				bPlayerHits = false;
			} else {
				cout << "Blad, sproboj ponownie" << endl;
			}
			cout << endl;

			iPlayerScore	= wartosc_w_rece(iaPlayerHand, iPlayerCardCount);
		} while (bPlayerHits && iPlayerScore < 22);

		if (iPlayerScore > 21) {
			cout << "**** Przegrywasz ****" << endl;
            wyswietl_wynik_i_reke(iaHouseHand, iHouseCardCount, iaPlayerHand, iPlayerCardCount);
            cout << "Czy chcesz zagrac jeszcze raz?" << endl;
            cout << "Wpisz 1 jesli tak, wybierz 0 jesli chcesz wylaczyc gre:" << endl;
            cin >> x;

            if(x==0)
                break;
		} else {

			int iHouseScore		= wartosc_w_rece(iaHouseHand, iHouseCardCount);
			while (iHouseScore < 17) {
				iaHouseHand[iHouseCardCount] = dobranie_karty(talia);
				++iHouseCardCount;
				iHouseScore		= wartosc_w_rece(iaHouseHand, iHouseCardCount);
			}
			bool bHouseBusts = (iHouseScore > 21);
			if (bHouseBusts) {

				cout << "**** Wygrywasz ****" << endl;
                wyswietl_wynik_i_reke(iaHouseHand, iHouseCardCount, iaPlayerHand, iPlayerCardCount);
                cout << "Czy chcesz zagrac jeszcze raz?" << endl;
                cout << "Wpisz 1 jesli tak, wybierz 0 jesli chcesz wylaczyc gre:" << endl;
                cin >> x;

                if(x==0)
                    break;
			} else {

				if (iPlayerScore == iHouseScore) {

					cout << "**** Remis ****" << endl;
                    wyswietl_wynik_i_reke(iaHouseHand, iHouseCardCount, iaPlayerHand, iPlayerCardCount);
                    cout << "Czy chcesz zagrac jeszcze raz?" << endl;
                    cout << "Wpisz 1 jesli tak, wybierz 0 jesli chcesz wylaczyc gre:" << endl;
                    cin >> x;

                    if(x==0)
                        break;
				} else if (iPlayerScore > iHouseScore) {

					cout << "**** Wygrywasz ****" << endl;
                    wyswietl_wynik_i_reke(iaHouseHand, iHouseCardCount, iaPlayerHand, iPlayerCardCount);
                    cout << "Czy chcesz zagrac jeszcze raz?" << endl;
                    cout << "Wpisz 1 jesli tak, wybierz 0 jesli chcesz wylaczyc gre:" << endl;
                    cin >> x;

                    if(x==0)
                        break;
				} else {

					cout << "**** Przegrywasz ****" << endl;
                    wyswietl_wynik_i_reke(iaHouseHand, iHouseCardCount, iaPlayerHand, iPlayerCardCount);
                    cout << "Czy chcesz zagrac jeszcze raz?" << endl;
                    cout << "Wpisz 1 jesli tak, wybierz 0 jesli chcesz wylaczyc gre:" << endl;
                    cin >> x;

                    if(x==0)
                        break;


				}
			}
        }

    }

}


void tasowanie(bool talia[]) {
	for (int iIndex = 0; iIndex < 52; ++iIndex) {
        talia[iIndex] = false;
	}
}

void wyswietlanie_karty(int karta) {

	// Wyswietlenie wyniku

	const int kiRank = (karta % 13);
	if (kiRank == 0) {
		cout << 'A';
	} else if (kiRank < 9) {
		cout << (kiRank + 1);
	} else if (kiRank == 9) {
		cout << 'T';
	} else if (kiRank == 10) {
		cout << 'J';
	} else if (kiRank == 11) {
		cout << 'Q';
	} else {
		cout << 'K';
	}
	// Wyswietlenie koloru
	const int kolor = (karta / 13);
	if (kolor == 0) {
		cout << 'C';
	} else if (kolor == 1) {
		cout << 'D';
	} else if (kolor == 2) {
		cout << 'H';
	} else {
		cout << 'S';
	}
}

void wyswietlenie_reki(int reka[], const int wartosc_karty) {

	for (int iCardIndex = 0; iCardIndex < wartosc_karty; ++iCardIndex) {
		const int kiNextCard = reka[iCardIndex];
        wyswietlanie_karty(kiNextCard);
		cout << " ";
	}
	cout << endl;
}

int dobranie_karty(bool talia[]) {
	bool bCardDealt	= true;
	int iNewCard	= -1;
	do {
		iNewCard = (rand() % 52);
		if (!talia[iNewCard]) {
			bCardDealt = false;
		}
	} while (bCardDealt);
	return iNewCard;
}

int wartosc_w_rece(int reka[], const int wartosc_karty) {
	int iAceCount	= 0;
	int iScore		= 0;
	for (int iCardIndex = 0; iCardIndex < wartosc_karty; ++iCardIndex) {
		const int kiNextCard = reka[iCardIndex];
		const int kiRank = (kiNextCard % 13);
		if (kiRank == 0) {
			++iAceCount;
			++iScore;
		} else if (kiRank < 9) {
			iScore = iScore + (kiRank + 1);
		} else {
			iScore = iScore + 10;
		}
	}
	while (iAceCount > 0 && iScore < 12) {
		--iAceCount;
		iScore = iScore + 10;
	}
	return iScore;
}

void wyswietl_wynik_i_reke(int reka_gospodarza[], const int wartosc_kart_gospodarza, int reka_gracza[], const int wartosc_kart_gracza) {

	cout << "Reka gospodarza: Wynik = " << wartosc_w_rece(reka_gospodarza, wartosc_kart_gospodarza) << endl;
    wyswietlenie_reki(reka_gospodarza, wartosc_kart_gospodarza);
	cout << "Reka gracza:  Wynik = " << wartosc_w_rece(reka_gracza, wartosc_kart_gracza) << endl;
    wyswietlenie_reki(reka_gracza, wartosc_kart_gracza);
	cout << endl;
}