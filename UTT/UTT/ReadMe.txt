Ultimate Tic Tac Toe 
CCBigBlackBug

Niculae Ioan - Paul
Albu Alexandru
Ciuca Maria Theodora
Toader Calin Mihai

credentials:
domain: pub.theaigames.com
username: ioan_paul.niculae@stud.acs.upb.ro
password: Galben12!@

//minitutorial :
    
se arhiveaza sursele + headerele intr-o arhiva .zip(nu conteaza numele)
se incarca pe site
win?? 



Pentru implementare am folosit urmatoarele functii:

	In Board.h :

-void Board::getCurrentPlayingBoards(std::vector<int> &playingBoards)
	Functia primeste un vector in care sunt retinute bordurile in care se mai poate juca


-static void getEmptyPositions(const int board, std::vector<std:: pair<int, int> > &emptyPositions);
	Functia primeste ca argument board-ul un vector de perechi in care sunt retinute pozitiile libere in care putem pune.

-bool Board::throwOpponentInBlankGame(int board, const int opponent, std::vector<std::pair<int, int> >& possibleClosingPossitions)
	Functia primeste ca argument board-ul , oponentul si un vector in care sunt retinute pozitiile libere in care pot pune astfel incat sa trimit oponentul intr-un blank game.

- static bool isEmpty(const int board);
	Functia primeste ca parametru board-ul si returneaza true daca nu a fost pus nimic acolo si false altfel.

- static int getBoard(const int value);
	Functia primeste ca parametru o valoare din vectorul _field si returneaza o valoare din _macroboard aferenta pozitiei.

- static bool throwOpponentNoAdvantage(int board, const int opponent, std::vector<std::pair<int, int> >& possibleClosingPossitions);
	Functia primeste ca parametrii board-ul, adversarul si un vector care retine pozitiile in care eu pot pune astfel incat sa trimit
	adversarul intr -un board in care nu poate inchide. Returneaza 'true' daca il pot trimite si 'false' altfel.

- static bool getClosingPositions(const int board, const int player, std::set< std::pair<int, int> > &allPositionsToClose);
	Functia primeste ca parametrii board-ul, player-ul si un vector in care sunt retinute toate pozitiile din board in care poate
	inchide player-ul si returneaza 'true' daca exista pozitii in care se poate inchide, altfel returneaza 'false'.

- static void twoOnRow(const int board, const int player,const int row, std::vector< std::pair<int, int> > &PositionToClose);
	Functia primeste ca parametrii board-ul, player-ul, o linie din board si un vector in care retine pozitiile in care pot inchide, verifica
	daca player-ul a pus de doua ori pe linia respectiva apoi apeleaza functia addIfTree.

- static void twoOnColumn(const int board, const int player, const int column, std::vector< std::pair<int, int> > &PositionToClose);
	Functia primeste ca parametrii board-ul, player-ul, o coloana din board si un vector in care retine pozitiile in care pot inchide, verifica
	daca player-ul a pus de doua ori pe coloana respectiva apoi apeleaza functia addIfTree.

- static void twoOnFirstDiagonal(const int board, const int player, std::vector< std::pair<int, int> > &PositionToClose);
	Functia primeste ca parametrii board-ul, player-ul si un vector in care retine pozitiile in care pot inchide, verifica
	daca player-ul a pus de doua ori pe diagonala principala apoi apeleaza functia addIfTree.

- static void twoOnSecondDiagonal(const int board, const int player, std::vector< std::pair<int, int> > &PositionToClose);
	Functia primeste ca parametrii board-ul, player-ul si un vector in care retine pozitiile in care pot inchide, verifica
	daca player-ul a pus de doua ori pe diagonala secundara apoi apeleaza functia addIfTree.

	In Position.h :

- static int getPosition(const int board, const int i, const int j);
	Functia primeste ca paramtrii board-ul si pozitiile din board-ul respectiv si returneaza pozitia din vectorul _field.

- static void setPosition(const int board, const int i, const int j, const int player);
	Functia primeste ca paramtrii board0ul si pozitiile din board-ul recpectiv cat si jucatorul care este la mutare si va returna casuta ocupata de acesta.

- static std::pair<int, int> getMatrixPosition(const int value);
	Functia primeste o valoare din _field si returneaza pozitiile absolute din matricea de 9x9.

- static std::pair<int, int> getMatrixPosition(const int board, const std::pair<int, int> relativePosition);
	Functia primeste board-ul si o pereche de pozitii relative si returneaza pozitiile absolute din matricea de 9x9.

	In BotIO.cpp:

- in functia:  std::pair<int, int> BotIO::action(const std::string &type, int time) 
	
	