    INVENTARUL UNUI MAGAZIN DE MOBILA
    Programul manipuleaza datele din inventarul unui magazin de mobila.

    Datele de intrare din fisier sunt memorate in urmatoarea ordine: 
    Numarul total de mobila din inventar (total_mob)
    <clasa Mobila>
    Numele mobilierului (tip)
    Numarul de piese care trebuie asamblate (comp.nr_piese)
    Piesele principale (comp.comp_princip)
    Stocul actual (stoc)
    Pretul (pret)
    <clasa Vanzari>
    Tipul de mobilier (mobila)
    Numarul de vanzi (nr_vnz)

    Asupra datelor, se pot face urmatoarele operatii: 
        - afisarea informatiilor memorate in clase
        - afisarea datelor membre ale claselor
        - afisearea numarul total de adaugari in inventar
        - adaugarea in inventar a unui tip nou de mobilier
        - actualizarea stocului, pretului, nr. de vanzari
        - stergerea din inventar
        - calcularea venitului total din vanzari

    In cazul in care stocul este scazut, programul va genera o sugestie de crestere a pretului cu 5%
    (apelarea functiei private stoc_redus)
