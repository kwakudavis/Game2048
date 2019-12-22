#pragma once
class Tile

{
private:

public:
	bool type;
	int value;
	void add(Tile *other);
	bool equals(Tile* other);

};

