# FS-system-linked-lists
Pentru implementare am folosit 3 headere:
File.h -> la cele 2 structuri din skel am adaugat o structura de tip lista si de tip nod.
       -> am folosit tipuri generice pentru retinerea informatiei.
Directoare.h -> am implementant urmatoarele functii:
1. create_fs()->aloca memorie si creeaza directorul 'root'.
2. mkdir()-> creaza, aloca memorie si adauga in ordine lexicografica directoare in
lista de directoare a directorului curent.
   	  -> daca nu avem directoare in lista, adaugam directorul ca prim nod in lista.
	  -> parcurgem verificand cu un if lista, pana gasim unde trebuie adaugat nodul
	  -> cand gasim pozitia, refacem legatura, adaugam nodul si dam return.
3. ls()-> afiseaza continutul directorului curent
       -> parcurgem atat lista de fisiere, cat si cea de directoare si dam print fiecarui nod
4. pwd()-> afisam calea de la root la directorul curent
        -> daca directorul are un tata (adica nu e root), apelam recursiv functia pentru tatal lui
si afisam numele sau.
5. cd() -> ne muta in directoarele dorite daca exista, altfel afiseaza o eroare
   	-> verificam cazul special ".." in care trebuie sa ne ducem in spate; facem asta atribuind
nodului curent adresa parintelui
	-> cautam nodul in care trebuie sa ne mutam, si cand il gasim schimbam adresa celui curent
in adresa acelui nod
6. tree() -> afisam arborescent sistemul de fisiere
   	  -> tinem un argument depth care retine adancimea functiei; ne va ajuta la afisarea spatiilor
	  -> afisam numele directorului curent
	  -> afisam toate fisierele din directorul curent
	  -> apelam recursiv tree pentru fiecare director din lista
7. rm() -> stergem fisiere din lista de fisiere
   	-> daca primul fisier trebuie sters, urmatorul devine primul si eliberam memoria pentru cel care
trebuie sters, dezalocam memoria si dam return
	-> parcurgem lista de fisiere pana gasim fisierul care trebuie scos si dupa il stergem si dam return
	-> daca nu exista afisam eroare
8. rmdir() -> stergem un director si toate elementele sale
  	  -> cautam directorul si refacem legatura in lista
	  -> pentru directorul gasit parcurgem lista de fisiere si apelam functia rm()
	  -> tot pentru el parcurgem lista de directoare si apelam pentru fiecare rmdir()
	  -> la sfarsit dezalocam memoria pentru directorul sters
9. delete_fs() -> stergem rootul si dezalocam memoria pentru el
10. aux_delete() -> am obeservat o problema la valgrind la testele in care se apela delete_fs() din alt director
diferit de root
		 -> aceasta functie sterge tot subsistemul pana la root si dezaloca memoria
		 -> folosim cd(..) sa ajungem in root
		 -> ne folosim de rm() si rmdir() sa stergem restul fisierelor si directoarelor

Fisiere.h -> am implementat urmatoarele functii:
1. touch() -> creeaza un fisier nou in directorul curent
   	   -> alocam memoria necesara
	   -> cautam pozitia lexicografica unde trebuie adaugat fisierul
	   -> adaugam fisierul si refacem legaturile
2. find()  -> cautam un fisier cu specificatiile din cerinta
   	   -> folosim un contor depth pentru fiecare nivel de adancime in care cautam;trebuie
sa fie mai mic ca max_depth
       	   -> parcurgem lista de fisiere si verificam conditiile de size si content; daca trece conditiile
afisam numele fisierului
       	   -> parcurgem recursiv toate directoarele pana la adancime max_depth si reluam operatia

In main:
   -> avem o bucla infinita pentru citire care se opreste cand citim "delete"
   -> citim linie cu linie si scoatem parametrii pentru functii folosind strtok()
   -> comparam pointerul *p cu diferitele siruri care reprezinta sirurile functiilor, apoi apelam functiile
