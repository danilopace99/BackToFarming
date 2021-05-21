#pragma once
#include "stdafx.h"

using namespace std;

class Cplant
{
protected:
	string type;
	int growTime;
	int complteteGrowTime;
	int ammountWater;

public:

	Cplant(string Ntype, int NgrowTime, int NcomplteteGrowTime, int NammountWater)
	{
		type = Ntype;
		growTime = NgrowTime;
		complteteGrowTime = NcomplteteGrowTime;
		ammountWater = NammountWater;
	}

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

	float getPercentDone()
	{
		return growTime / complteteGrowTime;
	}
};

int getCompleteGrowtime(string type)
{
	if (type == "carrots")
	{
		return 2400;
	}
	else if (type == "potatoes")
	{
		return 4800;
	}
}