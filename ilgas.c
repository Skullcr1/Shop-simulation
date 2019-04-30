#include "ilgas.h"
/*#define DEBUG */
/* strlen (char*) --- String ilgis be '\0'
 */
 
struct LinkedList {

	int data;
	struct LinkedList *next;
	
};
 
int Isub (ManoIlgas Ilgas1, ManoIlgas Ilgas2, ManoIlgas* Skirtumas) ;
void IlgasTrumpiau (ManoIlgas Ilgas) ;



void createIlgas (ManoIlgas* head, int length) {
	
	int i;
	ManoIlgas element;
	ManoIlgas lastElement = NULL;
	
	for (i = 1; i <= length; i++) {
		
		element = malloc (sizeof (ManoIlgas));
		element->next = NULL;
		element->data = 0;
		
		#ifdef DEBUG
		printf("%d :\t%d",element,element->data);
		#endif
		
		if (i == 1) {*head = element; lastElement = element;}
		else {lastElement->next = element; lastElement = element;}
		
		#ifdef DEBUG
		printf("\t %d\n",lastElement);
		#endif
	}
}

void printIlgas (ManoIlgas head) {
	/* atspausdina visa ilga */
	ManoIlgas element = head;
	
	while (element != NULL) {
		
		printf("%d ",element->data);
		element = element->next;
	}
	printf("\n");
	
}

int getIndex (ManoIlgas head, int index) {
	/* nueina iki i'tojo elemento ir grazina jo reiksme */
	int i;
	ManoIlgas element = head;
	
	for (i = 0; i < index; i++){
		
		if (element->next != NULL){element = element->next;}
		else					  {return -1;}
		
	}
	return element->data;
}

void setIndex (ManoIlgas head, int index, int value){
	/* nueina iki i'tojo elemento ir pakeicia jo reiksme i value */
	
	int i;
	ManoIlgas element = head;
	
	for (i = 0; i < index; i++){
		
		if (element->next != NULL) {element = element->next;}
		else					   {break;}
		
	}
	
	element->data = value;
	
}

void freeIlgas (ManoIlgas *Ilgas) {

	ManoIlgas element = *Ilgas;
	ManoIlgas lastElement = NULL;	

	while (element != NULL) {
		
		if (element != *Ilgas) {	
				lastElement = element;
				element = element->next;
			    free(lastElement); 
  				}
				
	else element = element->next;
	
	}
	Ilgas = NULL;
	
}
/* Struktإ«ros funkcijإ³ pabaiga */
/* ====================================================================== */
/* ====================================================================== */

int Str2Ilgas(ManoIlgas* Ilgas, char* S){
/* Perveda teksto eilute i 'Ilgo' formata */

	int  i, ilgis, zenklas = 0;
	int l;
	
/* Tikrinu ar sveikas skaicius teigiamas, ar neigiamas
	Jei '+' -->  zenklas skaitmuo 0
	Jei '-' -->  zenklas skaitmuo 1 */

	if (S[0] == '-') {ilgis = strlen(S)+1; zenklas++;}
	else  			 {ilgis = strlen(S)+2;}

	/* OPTIMIZACIJA, ELIMINUOJAM 0 NUO PRIEKIO! */

	createIlgas(Ilgas,ilgis);
	setIndex(*Ilgas,0,zenklas);
/* Ciklas, kuris 'parsina' char->int
*/

	for (i = zenklas; i < ilgis-2+zenklas; i++) {

		switch (S[i]) {
		  case '0':
			if (zenklas) {setIndex(*Ilgas,i,0);}
			else         {setIndex(*Ilgas,i+1,0);}
			break;
		  case '1':
			if (zenklas) {setIndex(*Ilgas,i,1);}
			else         {setIndex(*Ilgas,i+1,1);}
			break;
		  case '2':
			if (zenklas) {setIndex(*Ilgas,i,2);}
			else         {setIndex(*Ilgas,i+1,2);}
			break;
		  case '3':
			if (zenklas) {setIndex(*Ilgas,i,3);}
			else         {setIndex(*Ilgas,i+1,3);}
			break;
		  case '4':
			if (zenklas) {setIndex(*Ilgas,i,4);}
			else         {setIndex(*Ilgas,i+1,4);}
			break;
		  case '5':
			if (zenklas) {setIndex(*Ilgas,i,5);}
			else         {setIndex(*Ilgas,i+1,5);}
			break;
		  case '6':
			if (zenklas) {setIndex(*Ilgas,i,6);}
			else         {setIndex(*Ilgas,i+1,6);}
			break;
		  case '7':
			if (zenklas) {setIndex(*Ilgas,i,7);}
			else         {setIndex(*Ilgas,i+1,7);}
			break;
		  case '8':
			if (zenklas) {setIndex(*Ilgas,i,8);}
			else         {setIndex(*Ilgas,i+1,8);}
			break;
		  case '9':
			if (zenklas) {setIndex(*Ilgas,i,9);}
			else         {setIndex(*Ilgas,i+1,9);}
			break;
		  default:
			S = NULL;
			return 0;
			break;
		}

	}
	
	setIndex(*Ilgas,ilgis-1,GALAS);
	IlgasTrumpiau(*Ilgas);

	return 1;
}
/* ====================================================================== */
char* Ilgas2Str(ManoIlgas Ilgas){
/* Perveda Ilgo formata i teksto eilute */
	
	if (Ilgas == NULL) {return NULL;}
	
	int i = getIndex(Ilgas,0);
	int ilgis = 0, zenklas;
	
	if (getIndex(Ilgas,0) != 0 && getIndex(Ilgas,0) != 1){return NULL;}

	while (i != GALAS) {
		i = getIndex(Ilgas,ilgis);
		if (i < 0) {return NULL;}
		ilgis++;
	}

	char* Str = (char*) calloc(ilgis,sizeof(char) );

	int temp = ilgis;

	if (getIndex(Ilgas,0)) {Str[0] = '-'; zenklas = 1;}
	else {zenklas = 0;}

	for (i = 1; i < ilgis-1; i++) {
				
		switch (getIndex(Ilgas,i)){

			case 0:
			  if (zenklas) {Str[i]='0';}
			  else         {Str[i-1]='0';}
			  break;
			case 1:
			  if (zenklas) {Str[i]='1';}
			  else         {Str[i-1]='1';}
			  break;
			case 2:
			  if (zenklas) {Str[i]='2';}
			  else         {Str[i-1]='2';}
			  break;
			case 3:
			  if (zenklas) {Str[i]='3';}
			  else         {Str[i-1]='3';}
			  break;
			case 4:
			  if (zenklas) {Str[i]='4';}
			  else         {Str[i-1]='4';}
			  break;
			case 5:
			  if (zenklas) {Str[i]='5';}
			  else         {Str[i-1]='5';}
			  break;
			case 6:
			  if (zenklas) {Str[i]='6';}
			  else         {Str[i-1]='6';}
			  break;
			case 7:
			  if (zenklas) {Str[i]='7';}
			  else         {Str[i-1]='7';}
			  break;
			case 8:
			  if (zenklas) {Str[i]='8';}
			  else         {Str[i-1]='8';}
			  break;
			case 9:
			  if (zenklas) {Str[i]='9';}
			  else         {Str[i-1]='9';}
			  break;
			default:
			  free(Str);
			  return NULL;
		}

	}
	return Str;
} /* Ilgas2Str pabaiga */
/* ====================================================================== */
void Int2Ilgas(ManoIlgas* Ilgas, int S){
	
	/* a - laikinas skaicius
	   n - skaiciaus ilgis	*/
	   
	int a = S, n = 0, i;	
	/* Ilgio nustatymas     */
	while (a) {
		a /= 10;
		n++;
	}
		
	/* Dinamines atminties isskyrimas    */
	createIlgas(Ilgas,n+2);

	/* Zenklo nustatymas 		*/
	if (S >= 0) {setIndex(*Ilgas,0,0);}
	else	    {setIndex(*Ilgas,0,1); S = S * -1;}
		
	/* Baigties simbolio 'GALAS' imetimas */
	setIndex(*Ilgas,n+1,GALAS);
	
	for (i = n; i != 0; i--){
		
		setIndex(*Ilgas,i,S % 10);
		S /= 10;
		
	}
}
/* ====================================================================== */
void IlgasTrumpiau (ManoIlgas Ilgas) {

	int kiekis = 0, i = 1, ilgis = IlgoIlgis(Ilgas);

	while (1) {

		if (getIndex(Ilgas,i) != 0) {if (getIndex(Ilgas,i) == GALAS) {kiekis--;}
							break;}
		i++; kiekis++;

	}

	for (i = 1; i <= ilgis+1; i++) {
		setIndex(Ilgas,i,getIndex(Ilgas,i+kiekis));
		if (getIndex(Ilgas,i) == GALAS) {break;}

	}
	if (getIndex(Ilgas,1) == 0) {setIndex(Ilgas,0,0);}
}
/* ====================================================================== */
int IlgoIlgis (ManoIlgas Ilgas) {

	int ilgis=0, i;

	do
	{
		ilgis++;
		i = getIndex(Ilgas, ilgis);
	}
	while (i != GALAS);

	ilgis--;

	return ilgis;

}
/* ====================================================================== */
int arIlgas (ManoIlgas Ilgas) {
	
	if (Ilgas == NULL) {return 0;}  
	if (getIndex(Ilgas,0) != 1 && getIndex(Ilgas,0) != 0){return 0;}
	
	int i = 1;
	
	while (1){
		
		if (getIndex(Ilgas,i)<0 || getIndex(Ilgas,i)>9 && getIndex(Ilgas,i)!=GALAS) {return 0;}
		if (getIndex(Ilgas,i)==GALAS) {break;}
		i++;
	}
	return 1;
}
/* ====================================================================== */
int Iadd (ManoIlgas Ilgas1, ManoIlgas Ilgas2, ManoIlgas* Suma) {
	
	/* Tikrina, ar abu yra taisyklingi */
	if (arIlgas(Ilgas1) == 0 || arIlgas(Ilgas2) == 0) {return 0;}

	int n1 = IlgoIlgis(Ilgas1);
	int n2 = IlgoIlgis(Ilgas2);
	int sumIlgis,i;

	/* Jeigu nelygus zenklai, tada nusiunciam i atimties funkcija */
	if (getIndex(Ilgas1,0) != getIndex(Ilgas2,0) ) {
													if (getIndex(Ilgas2,0) ){setIndex(Ilgas2,0, 0); Isub(Ilgas1,Ilgas2,Suma); setIndex(Ilgas2,0, 1); return 1;}
													else					{setIndex(Ilgas2,0, 1); Isub(Ilgas1,Ilgas2,Suma); setIndex(Ilgas2,0, 0); return 1;} 
													}

	
	/* Sukuriam laikina sumos kintamaji ir nuli */
	ManoIlgas laikSuma;
	ManoIlgas nulis;
	Str2Ilgas(&nulis,"0");
	
	/* Patikrinam, kuris didesnis, ir isskiriam vietos+1 */
	if (n1 > n2) {createIlgas(&laikSuma,n1+3); sumIlgis = n1+3;} 
	else		 {createIlgas(&laikSuma,n2+3); sumIlgis = n2+3;}

	int i1 = n1, i2 = n2, a1,a2,r,ir,p = 0;

	/* i1 - pirmojo Ilgo indeksas
	   i2 - antrojo Ilgo indeksas
	   r - rezultatas sudeties skaitmenu
	   ir - rezultato indeksas
	   p - papildomas sumos narys
	*/

	if (n1 > n2) {ir = n1+1;}
	else 		 {ir = n2+1;}

	while (1) {

		if (i1 > 0) {a1 = getIndex(Ilgas1,i1);}
		else 	{a1 = 0;}

		if (i2 > 0) {a2 = getIndex(Ilgas2,i2);}
		else    {a2 = 0;}

		r = a1 + a2 + p;
		setIndex(laikSuma,ir,r % 10);
		p = r / 10;
		i1--;
		i2--;
		ir--;
		if ( (i1 <= 0) && (i2 <= 0) ) {break;}

	}

	setIndex(laikSuma,ir,getIndex(laikSuma,ir)+p);
	if (n1 > n2) {setIndex(laikSuma,n1+2,GALAS);}
	else		 {setIndex(laikSuma,n2+2,GALAS);}

	if (getIndex(Ilgas1,0)){setIndex(laikSuma,0,1);}
	else 			       {setIndex(laikSuma,0,0);}
	
	/* Eliminuojam nulius nuo priekio, jei reikia */
	IlgasTrumpiau(laikSuma);
	createIlgas(Suma,sumIlgis);

	for (i = 0; i < sumIlgis; i++){
		setIndex(*Suma,i,getIndex(laikSuma,i) );		
	}
	
	freeIlgas(&laikSuma);
	freeIlgas(&nulis);

	return 1;
}
/* ====================================================================== */
int Isub (ManoIlgas Ilgas1, ManoIlgas Ilgas2, ManoIlgas* Skirtumas) {
		
	int klaida = 1;
	/* Tikrina, ar abu yra taisyklingi */
	if (arIlgas(Ilgas1) == 0 || arIlgas(Ilgas2) == 0) {return 0;}
	
	/* Patikrinam, jei zenklai skirtingi, tai kvieciame add'a */
	if (getIndex(Ilgas1,0) != getIndex(Ilgas2,0))
    {
        if(getIndex(Ilgas2,0) ){setIndex(Ilgas2,0,0); Iadd(Ilgas1,Ilgas2,Skirtumas); setIndex(Ilgas2,0,1); return 1;}
        else 				   {setIndex(Ilgas2,0,1); Iadd(Ilgas1,Ilgas2,Skirtumas); setIndex(Ilgas2,0,0); return 1;} 	
    }
	
	
	int n1 = IlgoIlgis(Ilgas1);
	int n2 = IlgoIlgis(Ilgas2);
	int a1,a2,p = 0, i1 = n1, i2 = n2, ir = n1, i;
	int s = getIndex(Ilgas1,0);
	/*
		i1 - pirmojo Ilgo indeksas
		i2 - antrojo Ilgo indeksas
		ir - rezultato indeksas
		s - rezultato sign bitas
	    p - pasiskolinimas is vyresnio skaitmens
	*/
	
	/* Sukuriam laikina skirtumo kintamaji ir nuli */
	ManoIlgas laikSkirtumas;
	ManoIlgas nulis;
	Str2Ilgas(&nulis,"0");
	
	
	/*Patikrinam, kuris is dvieju skaiciu didesnis*/
    i1 = Icmp(Ilgas1 , Ilgas2);
    if(getIndex(Ilgas1,0) == 1)(i1 = i1 * (-1));
	if(i1 == -1){
		if(getIndex(Ilgas2,0) == 1){s = 0;}
		else  s = 1;
		klaida = Isub( Ilgas2, Ilgas1,&laikSkirtumas );
		
		for (i = 0; i < n1+2; i++){
		setIndex(*Skirtumas,i,getIndex(laikSkirtumas,i) );		
		}
		setIndex(*Skirtumas,0,s);
		return 1;
	} else {createIlgas(&laikSkirtumas,n1+2);}

	i1 = n1;
	/*Atimtis*/
	while (1) {

        a1 = getIndex(Ilgas1,i1);

		if (i2 > 0) {a2 = getIndex(Ilgas2,i2);}
		else    {a2 = 0;}

		if(p == 1)
		{
			if(a1 == 0){
				a1 = 9;
				p = 1;
			}
			else {a1--; p = 0;}
		}

		if(a1<a2){
			a1+=10;
			p=1;
			setIndex(laikSkirtumas,ir,a1-a2);
		} else{ setIndex(laikSkirtumas,ir,a1-a2);}

		i1--;
		i2--;
		ir--;
		if ( (i1 <= 0) && (i2 <= 0) ) {break;}
	}
	
	setIndex(laikSkirtumas,0,s);
	setIndex(laikSkirtumas,n1+1,GALAS);
	IlgasTrumpiau(laikSkirtumas);
	
	createIlgas(Skirtumas,n1+2);

	for (i = 0; i < n1+2; i++){
		setIndex(*Skirtumas,i,getIndex(laikSkirtumas,i) );		
	}
	
	freeIlgas(&laikSkirtumas);
	freeIlgas(&nulis);
	
	return 1;
}
/* ====================================================================== */

int Imul (ManoIlgas Ilgas1, ManoIlgas Ilgas2, ManoIlgas* Sandauga) {

	/* Idؤ—ja:
	sudauginam Ilgas1 su paskutiniu Ilgas2 skaitmeniu
	sudauginam Ilgas1 su prieإ،paskutiniu Ilgas2 skaitmeniu, rez * 10, sudedam su pirmuoju, free rez
	sudauginam Ilgas1 su prieإ،prieإ،..., rez * 100, sudedam su pirmuoju, free rez
	ir tai iki tol kol, viskas susideda ir viskas puiku!
	*/

	/* Tikrina, ar abu yra taisyklingi */
	int klaida = 1;
	if (arIlgas(Ilgas1) == 0 || arIlgas(Ilgas2) == 0) {return 0;}
	
	int n1 = IlgoIlgis(Ilgas1);
	int n2 = IlgoIlgis(Ilgas2);
	ManoIlgas Laikinas;
	ManoIlgas Rez;
	ManoIlgas Nulis;
	/* Optimizacija, jei Ilgas2 > Ilgas1 */
	if (n2 > n1) {klaida = Imul(Ilgas2,Ilgas1,Sandauga); return 1;}

	/* Susikuriam Sandaugos "Ilga" = 0 */
	
	klaida = Str2Ilgas(&Rez,"0");
	Str2Ilgas(&Nulis,"0");
	if(klaida == 0) return klaida;
	if ( (getIndex(Ilgas1,1) == 0 )|| (getIndex(Ilgas2,1) == 0) ) {return 1;}
	
	int i1 = n1, i2 = n2, i, ni;
	
	/* ni yra ilgesnis iإ، dviejإ³ */
	if (n1 > n2) {ni = n1;}
	else		 {ni = n2;}

	int r,ir,p = 0;
	int kelintas = 0;

	for (i1 = n1; i1 != 0; i1--) {

		createIlgas(&Laikinas,n2+3+kelintas);
		
		setIndex(Laikinas,0,0);
		p = 0;
		setIndex(Laikinas,n2+2+kelintas,GALAS);
		ir = n2+1; /* pastato indeksa i nuliu rasymo pozicija */


		for (i2 = n2; i2 != 0; i2--){
			setIndex(Laikinas,ir,(getIndex(Ilgas1,i1)*getIndex(Ilgas2,i2)+p)%10);
			p = (getIndex(Ilgas1,i1)*getIndex(Ilgas2,i2)+ p) / 10;
			ir--;
		}
		setIndex(Laikinas,ir,p);
		
		for (i = n2+1+kelintas; i > n2+1; i--) {
			
			setIndex(Laikinas,i,0);

		}

		IlgasTrumpiau(Laikinas);
		kelintas++;
		
		klaida = Iadd(Rez,Laikinas,&Rez);
		freeIlgas(&Laikinas);

	}

	/* Zenklo nustatymas */
	int zenklas;
	
	if (getIndex(Ilgas1,0) != getIndex(Ilgas2,0)) {zenklas = 1;}
	else 										  {zenklas = 0;}
	
	Iadd(Rez,Nulis,Sandauga);
	setIndex(*Sandauga,0,zenklas);
	
	return 1;

}
/* ====================================================================== */
int Idiv (ManoIlgas Ilgas1, ManoIlgas Ilgas2, ManoIlgas* Dalmuo) {
	/* Tikrina, ar abu yra taisyklingi */
	if (arIlgas(Ilgas1) == 0 || arIlgas(Ilgas2) == 0) {return 0;}
	
	int klaida = 1;
	int n1 = IlgoIlgis(Ilgas1);
	int n2 = IlgoIlgis(Ilgas2);
	ManoIlgas Dauginamasis;
	int i1 = 1, ir=1,kiek = n2, r = 0, naujas = 0, issaugoti, tikrinti;
	int	s1 = getIndex(Ilgas1,0);
	int s2 = getIndex(Ilgas2,0);
	/*
		i1 - indeksas reikalingas ciklo for vykdymui
		ir - rezultato indeksas
		s1 - pirmojo Ilgo sign bito reiksme
		s2 - antrojo Ilgo sign bito reiksme
		r - reiksme, kuri bus irasoma i rezultato vieta
		naujas - nauja pirmojo Ilgo reiksme po atimties
		issaugoti - reiksme, kuri atimties metu bus pakeiciama GALAS konstanta
		tikrinti - i si kintamaji bus irasomas Icmp funkcijos grazinamas rezultatas;
		kiek - pirmojo Ilgo dalybos indeksas
	*/

	/*Tikriname ar vartotojas nebando atlikti dalybos is nulio*/
	if(n2 == 1 && getIndex(Ilgas2,1) == 0){return 0;}

	ManoIlgas IlgasNulis;
	klaida = Str2Ilgas(&IlgasNulis,"0");
	if (klaida == 0){ return 0; }
	ManoIlgas Daliklis; 
	klaida = Iadd(Ilgas2,IlgasNulis,&Daliklis);

	/*Tikriname, jei dvieju skaicu ilgiai vienodi - ar antras skaicius nera didesnis uz pirma*/
	
	setIndex(Ilgas1,0,0);
	setIndex(Ilgas2,0,0);
    tikrinti = Icmp(Ilgas1,Ilgas2);
    if(tikrinti == -1 ){
		setIndex(Ilgas1,0,s1);
		setIndex(Ilgas2,0,s2);
		createIlgas(Dalmuo,3);
		setIndex(*Dalmuo,0,0);
		setIndex(*Dalmuo,1,0);
		setIndex(*Dalmuo,2,GALAS);
		return 1;
	}
	createIlgas(Dalmuo,n1+2);
	/*Nustatome sign bita*/
	if( (s1 + s2) == 1){setIndex(*Dalmuo,0,1);}
	else {setIndex(*Dalmuo,0,0);}

    /*Nustatome kintamojo Dauginamasis didziasia reiksme: 10000...0*/
	createIlgas(&Dauginamasis,n1-n2+3);
	
	setIndex(Dauginamasis,0,0);
	setIndex(Dauginamasis,1,1);
	for(i1 = 2; i1 <= n1-n2+1; i1++){setIndex(Dauginamasis,i1,0);}

	/*Dalyba*/
	
	while(kiek <= n1){

		/*Tikriname ar i tam tikra poziciju skaiciu bent viena karta telpa Daliklis ir nuo Icmp funkcijos rezultato priklausomai atliekame veiksmus*/
		issaugoti = getIndex(Ilgas1,kiek+1);
		setIndex(Ilgas1,kiek+1,GALAS);
		tikrinti = Icmp(Ilgas1,Ilgas2);
		setIndex(Ilgas1,kiek+1,issaugoti);

		if(tikrinti == -1 && r == 0){
            if(ir!=1){setIndex(*Dalmuo,ir,r); ir++;}
			kiek++;
		} else if(tikrinti == 1){
			setIndex(Ilgas2,0,s2);
			klaida = Iadd(Ilgas2,Daliklis,&Ilgas2);
			setIndex(Ilgas2,0,0);
			r++;
		} else {if(kiek != n1){
                if(tikrinti != 0){setIndex(Ilgas2,0,s2); klaida = Isub(Ilgas2,Daliklis,&Ilgas2); setIndex(Ilgas2,0,0);}
				setIndex(Dauginamasis,n1-kiek+2,GALAS);
				setIndex(Ilgas2,0,s2);
				klaida = Imul(Ilgas2, Dauginamasis,&Ilgas2);
				setIndex(Ilgas2,0,0);
				setIndex(Dauginamasis,n1-kiek+2,0);
				/*Atimtis*/
				if( s1 == 0){klaida = Isub(Ilgas1,Ilgas2,&Ilgas1);}
				else {setIndex(Ilgas1,0,1); setIndex(Ilgas2,0,1); klaida = Isub(Ilgas1,Ilgas2,&Ilgas1); setIndex(Ilgas1,0,0); setIndex(Ilgas2,0,0);}

				/*Irasome reiksme i rezultata*/
                if(tikrinti == 0){setIndex(*Dalmuo,ir,r+1);}
				else {setIndex(*Dalmuo,ir,r);}

				/*Atstatome pradine kintamojo Ilgas2 reiksme*/
				i1=1;
				for(i1; i1<=n2+1;i1++){setIndex(Ilgas2,i1,getIndex(Daliklis,i1));}

				naujas = IlgoIlgis(Ilgas1);
				/*atstatom ilgi*/
				if (naujas < n1){
					kiek = kiek - (n1- naujas);
					if(kiek<0){
                        while(kiek!=0){
                            ir++;
							setIndex(*Dalmuo,ir,0);
                            kiek++;
                        }
					}
					n1 = naujas;
 				}
			}else {
                if(tikrinti == 0){setIndex(*Dalmuo,ir,r+1);}
				else {setIndex(*Dalmuo,ir,r);}
            }
			r=0;
			kiek++;
			ir++;
		}
	}
	
	setIndex(Ilgas1,0,s1);
	setIndex(Ilgas2,0,s2);
	setIndex(*Dalmuo,ir,GALAS);
	IlgasTrumpiau(*Dalmuo);
	
	freeIlgas(&Dauginamasis);
	freeIlgas(&IlgasNulis);
	freeIlgas(&Daliklis);
	
	return 1;

}

/* ====================================================================== */
int Imod (ManoIlgas Ilgas1, ManoIlgas Ilgas2, ManoIlgas* Liekana) {
	int klaida = 1;
	/* Tikrina, ar abu yra taisyklingi */
	if (arIlgas(Ilgas1) == 0 || arIlgas(Ilgas2) == 0) {return 0;}
	
    klaida = Idiv(Ilgas1,Ilgas2,Liekana);
	klaida = Imul (Ilgas2,*Liekana,Liekana);
    setIndex(*Liekana,0,getIndex(Ilgas1,0) );
    klaida = Isub(Ilgas1,*Liekana,Liekana);
	if(klaida == 0) return 0;
    else return 1;
}
/* ====================================================================== */
int  Icmp (ManoIlgas Ilgas1, ManoIlgas Ilgas2) {
	/* 		(-1, jei 1 < 2)  (0, jei 1 == 2)  (1, jei 1 > 2) */
	/*      ( 3, jei Ilgas1 arba Ilgas2 yra neteisingi);
	
	/* Tikrina, ar abu yra taisyklingi */
	if (arIlgas(Ilgas1) == 0 || arIlgas(Ilgas2) == 0) {return 2;}
	
	/* Jei skiriasi zenklas */
	if 		(getIndex(Ilgas1,0) > getIndex(Ilgas2,0))  {return -1;}
	else if (getIndex(Ilgas1,0) < getIndex(Ilgas2,0))  {return  1;}

	/* Jei skiriasi ilgis */
	int n1 = IlgoIlgis(Ilgas1);
	int n2 = IlgoIlgis(Ilgas2);

	if 		(n1 > n2) {if (getIndex(Ilgas1,0)) {return -1;}
					   else 		  {return  1;}		}
	else if	(n1 < n2) {if (getIndex(Ilgas1,0)) {return  1;}
					   else 		  {return -1;}		}

	/* Jei zenklas ir ilgis lygus, tikrinam po skaitmeni */
	int a1, a2, i1=1, i2=1;

	while ( (i1 <= n1) || (i2 <= n2) ) {

		if 		(getIndex(Ilgas1,i1) > getIndex(Ilgas2,i2)) {if (getIndex(Ilgas1,0)) {return -1;}
										   else 	    {return  1;} }
		else if (getIndex(Ilgas1,i1) < getIndex(Ilgas2,i2)) {if (getIndex(Ilgas1,0)) {return  1;}
										   else 	    {return -1;} }

		i1++; i2++;
	}
	return 0;
}
/* ====================================================================== */
int Iabs (ManoIlgas Ilgas, ManoIlgas* rezultatas){
	
	if (arIlgas(Ilgas) == 0) {return 0;}
	Str2Ilgas(rezultatas,"0");
	Iadd(*rezultatas,Ilgas,rezultatas);
	
	setIndex(*rezultatas,0,0);
	return 1;
}
/* ====================================================================== */
int Ipow (ManoIlgas Ilgas,int l, ManoIlgas* rezultatas){
	int klaida = 1;
	if (arIlgas(Ilgas) == 0) {return 0;}
	
	int i;
	
	if      (l == 1) {
		ManoIlgas nulis;
		klaida = Str2Ilgas(&nulis,"0");
		klaida = Iadd(Ilgas,nulis,rezultatas);
		klaida = Str2Ilgas(rezultatas,"1"); 
		return 1;	
		}
	else if (l == 0) { klaida = Str2Ilgas(rezultatas,"1"); return 1;}
	else if (l < 0 ) {return 0;}
	else 
	{
		klaida = Str2Ilgas(rezultatas,"1");
		
		for (i = 1; i <= l; i++){
			klaida = Imul(*rezultatas, Ilgas,rezultatas);
		}
		return 1;
	}
}
/* ====================================================================== */
/* ====================================================================== */
/* ====================================================================== */
