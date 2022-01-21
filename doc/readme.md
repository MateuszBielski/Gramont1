Podział na bloki.
 
logika współpracy bloków
Bloki w oddzielnych wątkach
Każdy blok ma pętlę i komunikują się za pomocą kolejek do których wstawiane są polecenia.
Dodatkowo może blok moze mieć swój własny dodatkowy wątek, do wykonania dłuższych poleceń w tle.

Szczególnie widać to na przykładzie klasy DoNarysowania.
logika rysowania:
Opiera się na logice działania OpenGL, która realizuje w każdej klatce stos poleceń. 
Stąd mój główny pomysł na optymalizację, żeby wywoływane były tylko te niezbędne polecenia.
Więc lista poleceń powinna być dynamicznie modyfikowana.
klasa DoNarysowania tworzy i przechowuje liste polecen należących do klasy renderowanie. 
Lista ta jest aktualizowana w istotnych momentach w trakcie zarządzania.
Klasa DoNarysowania dziedziczy między innymi po Grupowalne, która umożliwia tworzenie struktury drzewiastej, dlatego lista poleceń jest tworzona rekurencyjnie.
Wybór właściwych poleceń dokonywany jest na podstawie stanu obiektu.
Brane są pod uwagę takie właściwości jak:
czy mają być generowane identyfikatory, czy jest jakaś lokalna transformacja. 

Rozwój 
Rozwój modułów, polega na ruchu w górę, czyli w miarę rozbudowy danej klasy część pól i metod przenoszona jest w górę hierarchii.

Kierunki wymagające zmiany.
Niektóre zostały zaprojektowane odgórnie np obsługa poleceń. Później okazało się, że ta architektura ma wady. 
Wada polega na tym, że wybrano obiekt polecenie jako abstrakcyjną, która ma być później konkretyzowana.
Konkretnym klasom polecenie powierzono odpowiedzialność za wykorzystanie metod z innych klas przejmując od nich odpowiedzialność. 

Powoli próbuję je usuwać wdrażając nową logikę działania.

odejście od najstarszej wersji biblioteki i wykorzystanie shaderów.
testy:
niektóre fragmenty kodu są włączane i działają tylko w środowisku testowym.
Przykładem są funkcje monitorujące, które zbierają informacje o ilości rodzajach wywołań danej metody
