#pragma once

class Position
{
public:
	
	int starting_position[] = { 0, 3, 6, 27, 30, 33, 54, 57, 60 };
	int GetPosition(int board, int i, int j) const;
	void SetPosition(std::vector<int> &s, int board, int i, int j, int player);

	Position();
	~Position();
};

