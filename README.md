# OOP_PROJECT
## ucitavanje iz fajla
### prvi fajl
- sifra_stajalista naziv_stajalista
- sifra_stajalista
	- celobrojna i jedinstvena oznaka stajalista
- posle naziv_stajalista moze da bude "\[!\]" koji oznacava da se stajaliste nalazi kod vazne gradske destinacije ?
### drugi fajl
povezanost stanica
`oznaka_linije stajalista`
oznaka_linije je tekstualna i jedinstvena 
stajalista su sifre svih stajalista kroz koja linija prolazi u oba smera, po redu
`EKO1 654 585 583 190`
## prikaz informacija
### na osnovu zadate sifre stajalista
- sifra stajalista
- naziv stajalista
- oznake svih linija koje prolaze kroz dato stajaliste 
- sifre svih vaznih stajalista koja su direktno povezana sa datim stajalistem
#### format:
`sifra naziv [oznake_svih_linija] {! oznake_vaznih_stajalist !}`
- linije treba da ubdu sortirane alfabetski i odvojene razmacima
- stajalista sortirana numericki i odvojena razmacima
primer:
`585 Tehnicki fakulteti [26 27 74 EKO1] {! 551 556 583 654 !}`
treba ispisati u tekstualni fajl sa nazivom `stajaliste_sifra_stajalista` npr. stajalist_585.txt
### ! predvideti naknadno dodavanje novih formata za prikaz informacija o stajalistima

### na osnovu zadate oznake linije
- oznaka linije
- pocetno i krajnje stajaliste
- sifre i nazive svih stajalista kroz koja linija prolazi
prvi red: `oznaka_linije pocetno_stajaliste->krajnje_stajalist`

svaki sledeci red: sifra, naziv, eventualni indikator vaznosti stajalista kroz koje linija prolazi redoslednom kojim linija prolazi kroz njih

treba ispisati u fajl `linija_oznaka_linije` (`linija_27.txt`)
#### predvideti naknadno dodavanje novih formata za prikaz informacija o linijama


## simulacija kretanja kroz mrezu gradskog prevoza
### ulazni parametri - pocetna i krajnja stanica
generise putanju izmedju njih
izlaz: tekstualni fajl `putanja_pocetak_kraj.txt` pocetak i kraj su sifre stajalista
primer:
``` putanja_363_584.txt
->16
363 298 360
16->EKO1
360 703 534 582 584
```
### strategije
- 3 strategije
### 1. strategija
- bilo koja putanja izmedju pocetnog i krajnjeg stajalista
### 2. strategija
- putanja na kojoj je potreban najmanji broj presednja
### 3. strategija
- putanja koja obilazi sva vana stajalista u mrezi gradskog prevoza (xd?)

## interakcija sa korisnikom
```
Dobrodošli u simulator mreže gradskog prevoza. Molimo Vas, odaberite opciju:
1. Učitavanje podataka o mreži gradskog prevoza 
0. Kraj rada 
1 
Molimo Vas, unesite putanju do fajla sa stajalištima ili kliknite ENTER za učitavanje podrazumevanog fajla (ulazi/stajalista.txt):

Učitan je podrazumevani fajl sa stajalištima. 
Molimo Vas, unesite putanju do fajla sa linijama gradskog prevoza ili kliknite ENTER za učitavanje podrazumevanog fajla (ulazi/linije.txt):
ulazi/nove_linije.txt
Mreža gradskog prevoza je uspešno učitana. Molimo Vas, odaberite opciju: 
1. Prikaz informacija o stajalištu 
2. Prikaz informacija o liniji gradskog prevoza 
3. Pronalazak putanje između dva stajališta 
0. Kraj rada 
2 
Molimo Vas, unesite oznaku linije čije informacije želite da prikažete.
EKO1
Generisan je fajl linija_EKO1.txt sa osnovnim informacijama o liniji EKO1.
```
## napomena
Programski sistem realizovati tako da bude detaljno komentarisan, modularan i lako proširiv novim klasama i operacijama. Ukoliko u zadatku nešto nije dovoljno jasno definisano, treba usvojiti razumnu pretpostavku i na temeljima te pretpostavke nastaviti izgrađivanje svog rešenja.
