`create_wagon`:
1. Alocă memorie pentru o nouă structură Wagon.
2. Inițializează pointerii `next` și `prev` cu NULL.
3. Setează câmpul `val` cu '#'.
4. Returnează pointerul către Wagon-ul nou creat.

`create_train`:
1. Creează primul vagon folosind `create_wagon`.
2. Alocă memorie pentru o nouă structură Train.
3. Inițializează `sentinel` și îl leagă de primul vagon.
4. Setează `mechanic` la primul vagon și returnează pointerul către Train.

`show_current`:
1. Accesează câmpul `mechanic` al structurii Train.
2. Returnează câmpul `val` al Wagon-ului unde se află mechanic.

`show`:
1. Alocă memorie pentru un șir de rezultate.
2. Iterează peste vagoane începând cu cel de lângă sentinel.
3. Adaugă `val` din fiecare vagon la șirul de rezultate, marcând poziția mechanic-ului.
4. Returnează șirul de rezultate după adăugarea unui terminator null.

`write`:
1. Accesează câmpul `mechanic` al structurii Train.
2. Scrie caracterul furnizat în câmpul `val` al Wagon-ului unde se află mechanic.

`move_left`:
1. Mută `mechanic` la Wagon-ul `prev`.
2. Dacă `mechanic` este la sentinel, mută-l la ultimul Wagon.

`move_right`:
1. Verifică dacă `mechanic` este la ultimul Wagon.
2. Dacă este, creează un nou Wagon în dreapta folosind `insert_right`.
3. Dacă nu este, mută `mechanic` la Wagon-ul `next`.

`clear_cell`:
1. Verifică dacă `mechanic` nu este la un Wagon singur.
2. Dacă nu este, șterge Wagon-ul unde se află mechanic și mută `mechanic` la stânga.
3. Dacă este, scrie un '#' în câmpul `val` al Wagon-ului.

`clear_all`:
1. Cât timp `mechanic` nu este la un Wagon singur, apelează `clear_cell`.
2. Scrie un '#' în câmpul `val` al Wagon-ului rămas.

`insert_right`:
1. Creează un nou Wagon cu caracterul furnizat.
2. Inserează noul Wagon în dreapta `mechanic`-ului.
3. Actualizează pointerii `next` și `prev` ai Wagon-urilor înconjurătoare.
4. Mută `mechanic` la noul Wagon.

`insert_left`:
1. Verifică dacă `mechanic` este la primul Wagon.
2. Dacă nu este, creează un nou Wagon cu caracterul furnizat.
3. Inserează noul Wagon la stânga `mechanic`-ului și actualizează pointerii `next` și `prev` ai Wagon-urilor înconjurătoare.
4. Dacă nu e primul vagon nu se creeaza vagon nou dar se afișează `ERROR`.
4. Mută `mechanic` la noul Wagon.

`search`:
1. Începe de la Wagon-ul unde se află `mechanic`.
2. Iterează peste Wagon-uri într-o manieră circulară, comparând `val` fiecărui Wagon cu caracterele din text.
3. Dacă textul este găsit, setează `mechanic` la primul caracter din text.
4. Returnează true dacă textul este găsit, false altfel.

`search_right`:
1. Începe de la Wagon-ul unde se află `mechanic`.
2. Iterează peste Wagon-uri spre dreapta, comparând `val` fiecărui Wagon cu caracterele din text.
3. Dacă textul este găsit, setează `mechanic` la ultimul caracter din text.
4. Returnează true dacă textul este găsit, false altfel.

`search_left`:
1. Începe de la Wagon-ul unde se află `mechanic`.
2. Itereaza peste Wagon-uri spre stânga, comparând `val` fiecărui Wagon cu caracterele din text.
3. Dacă textul este găsit, setează `mechanic` la ultimul caracter din text.
4. Returnează true dacă textul este găsit, false altfel.

 `mechanic`.
2. Iterează peste Wagon-uri spre stânga, comparând `val` fiecărui Wagon cu caracterele din text.
3. Dacă textul este găsit, setează `mechanic` la ultimul caracter din text.
4. Returnează true dacă textul este găsit, false altfel.