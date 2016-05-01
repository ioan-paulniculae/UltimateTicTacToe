Ultimate Tic Tac Toe 
CCBigBlackBug v24

Niculae Ioan - Paul
Albu Alexandru
Ciuca Maria Theodora
Toader Calin Mihai

Algoritmul implementat pentru a 2a etapa este algoritmul negamax cu alpha-beta pruning.

Functia de evaluare euristica foloseste un heatMap pe jocul cel mare unde,
daca sunt 2 celule adiacente completate de acelasi jucator, valoarea celei de
a treia creste in heatMap, ponderea ei fiind mai mare in determinarea
castigului fiecarui jucator

Pentru aceasta, am implementat in clasa de Board metode de :
isValid(move),
isFinished(miniboard),
finishes(move) -- verifica daca mutarea primita va inchide jocul
applyMove(move)
eval(player)

De asemenea am creeat metode aditionale pentru a facilita scrierea codului si pentru debuging
am suprascris operatorul << pentru clasa board si am implementat metode care "convertesc"
index-ul din vectorul de 81 de elemente ca fiind, defapt, un index intr-o matrice de 9 x 9
