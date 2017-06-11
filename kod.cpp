#include<iostream>
#include <cstdlib>
#include <ctime>

struct node {
	int val;
	node *next;
};

using namespace std;

void show(node *H);

void dodajNaPoczatek(node* &H, int val);
void dodajNaKoniec(node * &H, int val);
void usunPierwszy(node* &H);
void usunOstatni(node* &H);
void usunElementyOWartosciX(node* &H, int x);
void usunCoDrugi(node* &H);
void duplikujElementy(node* &H);
void powielListe(node *H);
void powielListeOdwrocona(node *H);
node* merge(node *H1, node *H2); // zał: obie listy są już posortowane;
void swap(node * &H);
void bubbleSort(node * &H);
void swapCustomItems(node* & H, int x, int y);
void babelkowe(node *&H);
void usunWiekszeOdSrednia(node * &H);
void swap2(node * &H, node *p);
void sortowanieBabelkowe(node *&H);
void splitList(node *&H, node *&H1, node *&H2);

void wstawDoPosortowanej(node *&H, int x);
void buckedSort(node *&H, int size);
void buckedSort(int n);
void swapBubble(node *&H, node *&p);
void bubbleSor2(node *&H);

int main()
{
	srand(time(NULL));
	node *H = NULL;

	buckedSort(30000);
	//system("pause");
}

void buckedSort(int n)
{
	int size = n/100;
	node **db = new node*[size];
	node *H = NULL;

	for(int i = 0; i < size; i++)
	{
		db[i] = NULL;
	}

	for(int i = 0; i < n; i++)
	{
		int val = (rand() % 30000);	
		dodajNaPoczatek(db[int(val/100)], val);
		dodajNaPoczatek(H, val);
	}
	//sortowanie tablic 100 - elementowych
	time_t start1, koniec2;
	time( & start1 );
	for(int i = 0; i < size; i++)
	{
		bubbleSort(db[i]);
	}
	time( & koniec );
    cout << "sortowanie kubelkowe" << difftime( koniec, start ) << " sekund";

	// for(int i = 0; i < size; i++)
	// {
	// 	show(db[i]);
	// 	//cout << endl;
	// }

	//laczenie tablic
	H = db[0];
	for(int i = 0; i < size-1; i++)
	{
		node *p = db[i];
		while(p->next != NULL)
		{
			p = p->next;
		}
		p->next = db[i+1];
	}
	show(H);

	//sortowanie listy
	time_t start2, koniec2;
	time( & start2 );
	bubbleSort(H);
	time( & koniec2 );
    cout << "sortowanie babelkowe" << difftime( koniec, start ) << " sekund";
	//show(H);

}

void swapBubble(node *&H, node *&p){
   
    if(p==NULL){
        node *temp = H;
        H=H->next;
        temp->next = H->next;
        H->next=temp;
    }else{
        node *temp = p->next->next;
        p->next->next = temp ->next;
        temp->next = p->next;
        p->next=temp;
    }
   
   
}

void wstawDoPosortowanej(node *&H, int x) 
{
	if(H == NULL)
	{
		dodajNaPoczatek(H, x);
		return;
	}
		
	if(H->val > x)
	{
		dodajNaPoczatek(H, x);
	} else
	{
		node *p = H;

		if(p->next == NULL)
		{
			dodajNaPoczatek(p->next, x);
			return;
		}

		while(p->next == NULL || p->next->val < x) 
		{
			if(p->next == NULL)
			{
				break;
			}
			p = p->next;
		}
		dodajNaPoczatek(p->next, x);
	}		
}

void bubbleSor2(node *&H){
   
    node *p = H;
    int flag = 1;
   
    while(flag == 1){
        flag = 0;
        //if(H->next != NULL && H!=NULL)
        {
        if(H->val > H->next->val){
            swapBubble(H, p=NULL);
            flag = 1;
        }else{
            p=H;
            while(p->next->next != NULL){
               
               
                if(p->next->val>p->next->next->val){
                    swapBubble(H, p);
                    flag = 1;
                }
                p=p->next;
               
            }
        }}
       
    }
   
}


void babelkowe(node *&H)
{
	if (H == NULL || H->next == NULL)
	{
		cout << "nie ma czego sortowac pusto lub jest tylko 1 element" << endl;
	}
	else if (H->next != NULL && H->next->next != NULL)
	{
		if (H->val < H->next->val)
		{
			cout << "posortowane" << endl;
		}
		else
		{
			node *pomocnik = H;
			H = H->next;
			H->next = pomocnik;
			pomocnik->next = NULL;
		}
	}
	else
	{
		node *pomocnik = H;

		if (pomocnik == H && pomocnik->val > pomocnik->next->val)
		{
			H = H->next;
			H->next = pomocnik;
			pomocnik->next = pomocnik->next->next;

		}

		pomocnik = H;

		while (pomocnik != NULL && pomocnik->next != NULL)
		{
			if (pomocnik->val < pomocnik->next->val)
			{
				pomocnik = pomocnik->next;
			}
			else
			{
				node *pomocnik2 = pomocnik;
				node *pomocnik3 = pomocnik->next->next;
				pomocnik = pomocnik->next;
				pomocnik->next = pomocnik2;
				pomocnik2->next = pomocnik3;

			}
			pomocnik = pomocnik->next;
		}
	}


}


void show(node *H) {

	node *p = H;

	std::cout << "H->";
	while (p != NULL) {
		std::cout << p->val << "->";
		p = p->next;
	}
	std::cout << "NULL" << std::endl;
}

void dodajNaPoczatek(node* &H, int val) {

	node *p = new node;
	p->val = val;
	p->next = H;
	H = p;
}

void dodajNaKoniec(node * &H, int val) {

	if (H == NULL) {
		dodajNaPoczatek(H, val);
		return;
	}

	node *p = H;
	while (p->next != NULL) {
		p = p->next;
	}
	node *w = new node;
	w->val = val;
	w->next = p->next;
	p->next = w;

}

void usunPierwszy(node* &H) {

	if (H != NULL) {
		node *p = H;
		H = p->next;
		delete p;
	}
}

void usunOstatni(node* &H) {

	if (H != NULL) {
		node *p = H;
		if (p->next == NULL) {
			usunPierwszy(H);
			return;
		}
		while (p->next->next != NULL) {
			p = p->next;
		}
		node *w = p->next;
		p->next = w->next;
		delete w;
	}
}

void usunElementyOWartosciX(node* &H, int x) {

	node *p = H;
	node *w = H;
	while (H != NULL && p ->next != NULL ) {

		if (H->val == x) {
			usunPierwszy(H);
			continue;
		}

		if (p->next->val == x) {
			w = p->next;
			p->next = w->next;
			delete w;
			if (p->next == NULL)
				return;
		}
		p = p->next;
	}
}


void usunCoDrugi(node* &H) {

	if (H == NULL)
		return;

	node *p = H;
	node *w = H;
	while (p->next != NULL && p->next->next != NULL) {

		w = p->next;
		p->next = p->next->next;
		delete w;
		p = p->next;
	}

	if (p->next != NULL) {
		w = p->next;
		p->next = NULL;
		delete w;
	}
}

void duplikujElementy(node* &H) {

	node *p = H;
	while (p != NULL) {

		node *w = new node;
		w->val = p->val;
		w->next = p->next;
		p->next = w;
		p = p->next->next;
	}
}

void powielListe(node *H) {

	if (H == NULL)
		return;

	node *p = H;
	node *H2 = NULL;
	
	while (true) {
		dodajNaKoniec(H2, p->val);

		if (p->next == NULL) {
			p->next = H2;
			break;
		}
		p = p->next;
	}
}

void powielListeOdwrocona(node *H) {

	if (H == NULL)
		return;

	node *p = H;
	node *H2 = NULL;

	while (true) {
		dodajNaPoczatek(H2, p->val);

		if (p->next == NULL) {
			p->next = H2;
			break;
		}
		p = p->next;
	}
}

// node* merge(node *H1, node *H2) {
// 	node *H = NULL;
// 	node *p = H;

// 	while (H1 != NULL && H2 != NULL) {

// 		if (H1->val < H2->val) {
// 			if (H == NULL) {

// 				H = H1;
// 				H1 = H1->next;
// 				H->next = NULL;
// 				p = H;

// 			} else {

// 				p->next = H1;
// 				H1 = H1->next;
// 				p = p->next;
// 				p->next = NULL;
// 			}

// 		} else {
// 			if (H == NULL) {

// 				H = H2;
// 				H2 = H2->next;
// 				H->next = NULL;
// 				p = H;

// 			} else {

// 				p->next = H2;
// 				H2 = H2->next;
// 				p = p->next;
// 				p->next = NULL;
// 			}
// 		}
// 	}

// 	if (H1 == NULL && H2 != NULL) {
// 		p->next = H2;
// 	} else {
// 		p->next = H1;
// 	}

// 	return H;
// }

void swap(node * &H) {

	if (H == NULL || H->next == NULL)
		return;

	node *p = H;

	if (H->next->next == NULL) {

		H = p->next;
		H->next = p;
		p->next = NULL;

	} else {

		H = p->next;
		p->next = p->next->next;
		H->next = p;
	}
}

void bubbleSort(node * &H) {

	if (H == NULL || H->next == NULL)
		return;

	//gdy lista ma dwa elementy
	if (H->val > H->next->val) {
		swap(H);
		return;
	}
		
	bool isSorted = false;
	node *p;
	while (!isSorted) {
		isSorted = true;
		p = H;
		//show(H);
		while (p->next != NULL) {
			if (H->val > H->next->val) {
				swap(p->next);
				p = p->next;
				isSorted = false;
			}
		}
	}


}

void swapCustomItems(node* & H, int x, int y) {

	node *p = H;
	node *w = H;

	if (H == NULL)
		return;

	if (H->val != x) {
		while (p->next != NULL && p->next->val != x) {
			p = p->next;
		}
	} 

	if (H->val != y) {
		while (w->next != NULL && w->next->val != y) {
			w = w->next;
		}
	} 

	if (p->next->val == w->val || w->next->val == p->val) {
		swap(p->next);
		return;
	}
	
	if (p->next->val == x && w->next->val == y) {

		node *x = p->next;
		node *z = w->next;
		node *y = z->next;

		p->next = w->next;
		z->next = x->next;
		w->next = x;
		x->next = y;

	} else if(((H->val == x) && (w->next->val == y)) || ((p->next->val == x) && (H->val == y))) {
		//przypadek gdy ktoryś z elementów jest pierwszy
	}

}

void przeniesWiekszeOdSrednia(node * &H) {
	int sumaElementow = 0;
	int liczbaElementow = 0;
	node *p = H;
	node *w = H;

	while (p != NULL) {
		liczbaElementow++;
		sumaElementow += p->val;
		if (p->next == NULL)
			w = p;
		p = p->next;
	}
	int srednia = sumaElementow / liczbaElementow;

	std::cout << liczbaElementow << " " << sumaElementow << " " << srednia;

	node *H1 = NULL;
	p = H;
	while (p != NULL) {
		if (p->val > srednia)
			dodajNaKoniec(H1, p->val);
		p = p->next;
	}
	w->next = H1;
}


void usunWiekszeOdSrednia(node * &H)
{
	if (H == NULL)
		return;

	node *p = H;
	node *w;

	int iloscElementow = 0;
	int sumaElementow = 0;

	while (p != NULL)
	{
		sumaElementow += p->val;
		iloscElementow++;
		p = p->next;
	}

	int srednia = sumaElementow / iloscElementow;
	std::cout << iloscElementow << " " << sumaElementow << " " << srednia << std::endl;

	p = H;

	while (p->val < srednia)
	{
		w = p->next;
		H = w;
		delete p;
		p = w;
	}
	w = p->next;

	while (w != NULL)
	{
		if (w->val < srednia)
		{
			p->next = w->next;
			delete w;
		}
		else {
			p = p->next;
		}
		
		if (p->next == NULL)
			return;

		w = p->next;
	}

}

void sortowanieBabelkowe(node *&H) {

    if(H == NULL || H->next == NULL)
        return;
    
    int sortCounter = -1; 
	node *p;
    while(sortCounter != 0) 
	{   
        if(H->val > H->next->val)
            swap2(H, NULL);

		sortCounter = 0;
        p = H;
        
        while(p->next != NULL && p->next->next != NULL) 
		{
            if(p->next->val > p->next->next->val) 
			{
                swap2(H, p);
                sortCounter++;
            }
            p = p->next;
        }      
    }
}


void splitList(node *&H, node *&H1, node *&H2)
{
	node *p1 = H1;
	node *p2 = H2;

	while(H != NULL)
	{
		if(H1 == NULL)
		{
			H1 = H;
			H = H->next;
			H1->next = NULL;
			p1 = H1;

		} 
		else if (H != NULL)
		{
			p1->next = H;
			H = H->next;
			p1 = p1->next;
			p1->next = NULL;
		}

		if(H2 == NULL)
		{
			H2 = H;
			H = H->next;
			H2->next = NULL;
			p2 = H2;

		} 
		else if (H != NULL)
		{
			p2->next = H;
			H = H->next;
			p2 = p2->next;
			p2->next = NULL;
		}
	}

}


void swap2(node * &H, node *p) {

	if (H == NULL || H->next == NULL)
		return;

	node *w;

	if(p == NULL)
	{
		w = H;
		H = H->next;
		w->next = H->next;
		H->next = w;
		return;
	}

	w = p->next;
	node *x = w->next->next;
	p->next = w->next;
	p->next->next = w;
	w->next = x;
}

node* merge(node *H1, node *H2) {
	node *H = NULL;
	node *p = H;

	while (H1 != NULL && H2 != NULL) {

		if (H1->val < H2->val) {
			if (H == NULL) {

				H = H1;
				H1 = H1->next;
				H->next = NULL;
				p = H;

			} else {

				p->next = H1;
				H1 = H1->next;
				p = p->next;
				p->next = NULL;
			}

		} else {
			if (H == NULL) {

				H = H2;
				H2 = H2->next;
				H->next = NULL;
				p = H;

			} else {

				p->next = H2;
				H2 = H2->next;
				p = p->next;
				p->next = NULL;
			}
		}
	}

	if (H1 == NULL && H2 != NULL) {
		p->next = H2;
	} else {
		p->next = H1;
	}

	return H;
}
