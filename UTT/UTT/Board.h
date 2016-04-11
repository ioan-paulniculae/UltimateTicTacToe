#pragma once
#include <vector>
#include <set>
class Board
{

public:
	static std::vector<int>_field;
	static std::vector<int>_macroboard;
	static bool isEmpty(const int board);
	static bool isClosed(const int board);
	//returns all unique closing positions in the board for the player
	//the positions are relative to the game NOT to the board
	static bool getClosingPositions(const int board, const int player, std::set< std::pair<int, int> > &allPositionsToClose);

	//
	static int getBoard(const int value);

	//returns a container with all the empty positions in the board
	//the positions are absolute
	static void getEmptyPositions(const int board, std::vector<std:: pair<int, int> > &emptyPositions);
	static void getCurrentPlayingBoards(std::vector<int>& playing_boards);
	static bool throwOpponentNoAdvantage(int board, const int opponent, std::vector<std::pair<int, int> >& possibleClosingPossitions);
	static bool throwOpponentInBlankGame(int board, const int opponent, std::vector<std::pair<int, int> >& possibleClosingPossitions);

	static std::pair<int, int> chooseBestPosition(std::pair<int, int> bestPosition, std::vector< std::pair<int,int> > blankPositions);

	//returns true if the game isn't close else false
	static bool isValid(const int move);

	//returns all empty positions from all boards that are not closed
	//(relative positions [0-9][0-9]
	static void getEmptyPositions(std::set<std::pair<int,int> > &emptyPositions);
	
	~Board();

private:

	static void addIfThree(const int player, const int first, const int second, const int third, std::vector<std::pair<int, int> >& positionToClose);
	static void twoOnRow(const int board, const int player,const int row, std::vector< std::pair<int, int> > &PositionToClose);
	static void twoOnColumn(const int board, const int player, const int column, std::vector< std::pair<int, int> > &PositionToClose);
	static void twoOnFirstDiagonal(const int board, const int player, std::vector< std::pair<int, int> > &PositionToClose);
	static void twoOnSecondDiagonal(const int board, const int player, std::vector< std::pair<int, int> > &PositionToClose);


	Board();

};