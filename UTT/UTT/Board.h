#pragma once
#include <vector>
#include <set>
class Board
{

public:
	Board();
	Board(const std::vector<int>& field, const std::vector<int>& macroboard);

	bool isValid(const int move) const;
	bool isEmpty(const int board) const;
	bool isClosed(const int board) const;

	int next(const std::pair<int, int>& move) const;
	int getBoard(const int value) const;
	int getBoard(const std::pair<int, int> & move) const;
	//returns all unique closing positions in the board for the player
	//the positions are relative to the game NOT to the board

	void getCurrentPlayingBoards(std::vector<int>& playing_boards);
	bool getClosingPositions(const int board, const int player, std::set< std::pair<int, int> > &allPositionsToClose) const;
	void getEmptyPositions(const int board, std::set<std::pair<int, int> > &emptyPositions) const;
	void getEmptyPositions(std::set<std::pair<int, int> > &emptyPositions) const;
	bool playingBoards(const int move) const;
	std::pair<int, int> chooseBestPosition(std::pair<int, int> bestPosition, std::vector< std::pair<int, int> > blankPositions);
	//
	int getPosition(const int board, const int i, const int j) const;
	void setPosition(const int board, const int i, const int j, const int player);

	bool isFinished(const int board) const;
	// alex 
	void applyMove(const std::pair<int, int>&, const int player);

	//returns a container with all the empty positions in the board
	//the positions are absolute
	bool throwOpponentNoAdvantage(int board, const int opponent, std::vector<std::pair<int, int> >& possibleClosingPossitions);
	bool throwOpponentInBlankGame(int board, const int opponent, std::vector<std::pair<int, int> >& possibleClosingPossitions);


	//returns true if the game isn't close else false

	//returns all empty positions from all boards that are not closed
	//(relative positions [0-9][0-9]
	
	~Board();
	std::vector<int>_field;
	std::vector<int>_macroboard;
private:


	void addIfThree(const int player, const int first, const int second, const int third, std::vector<std::pair<int, int> >& positionToClose) const;
	void twoOnRow(const int board, const int player,const int row, std::vector< std::pair<int, int> > &PositionToClose) const;
	void twoOnColumn(const int board, const int player, const int column, std::vector< std::pair<int, int> > &PositionToClose) const;
	void twoOnFirstDiagonal(const int board, const int player, std::vector< std::pair<int, int> > &PositionToClose) const;
	void twoOnSecondDiagonal(const int board, const int player, std::vector< std::pair<int, int> > &PositionToClose) const;


};