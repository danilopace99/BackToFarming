#pragma once
#include "stdafx.h"

using namespace std;

class plant
{
protected:
	string type;
	int growTime;
	int complteteGrowTime;
	int ammountWater;

public:

	//setters
	void setType(string Ntype)
	{
		type = Ntype;
	}

	void setGrowTime(int NgrowTime)
	{
		growTime = NgrowTime;
	}
	void setComplteteGrowTime(int NcomplteteGrowTime)
	{
		complteteGrowTime = NcomplteteGrowTime;
	}
	void setAmmountWater(int NammountWater)
	{
		ammountWater = NammountWater;
	}

	//getters
	string getType()
	{
		return type;
	}

	int getGrowTime()
	{
		return growTime;
	}

	int getCompleteGrowTime()
	{
		return complteteGrowTime;
	}

	int getAmmountWater()
	{
		return ammountWater;
	}
};