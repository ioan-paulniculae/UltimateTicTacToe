#pragma once
#include <vector>
#include <set>
class Board
{

public:
	Board(std::vector<int>& field, std::vector<int>& macroboard);

	bool isEmpty(const int board) const;

	//returns all unique closing positions in the board for the player
	//the positions are relative to the game NOT to the board
	bool getClosingPositions(const int board, const int player, std::set< std::pair<int, int> > &allPositionsToClose) const;

	//
	int getBoard(const int value) const;

	//returns a container with all the empty positions in the board
	//the positions are absolute
	void getEmptyPositions(const int board, std::vector<int> &emptyPositions) const;
	void getCurrentPlayingBoards(std::vector<int>& playing_boards) const;
	
	~Board();
private:
	std::vector<int>_field;
	std::vector<int>_macroboard;
	void addIfThree(const int player, const int first, const int second, const int third, std::vector<std::pair<int, int> >& positionToClose)const;
	void twoOnRow(const int board, const int player,const int row, std::vector< std::pair<int, int> > &PositionToClose) const;
	void twoOnColumn(const int board, const int player, const int column, std::vector< std::pair<int, int> > &PositionToClose) const;
	void twoOnFirstDiagonal(const int board, const int player, std::vector< std::pair<int, int> > &PositionToClose) const;
	void twoOnSecondDiagonal(const int board, const int player, std::vector< std::pair<int, int> > &PositionToClose) const;


	Board();

};