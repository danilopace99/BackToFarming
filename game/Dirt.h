#pragma once
#include "stdafx.h"
#include "Plant.h"

using namespace std;

class CDirt : public CSprite
{
protected:
	Cplant* plant;

public:

	//methods
	void agePlant()
	{
		plant->setGrowTime(plant->getGrowTime() + 1);
	}

	void waterPlant()
	{
		plant->setAmmountWater(plant->getAmmountWater() + 20);
	}

	void plantPlant(string type)
	{
		Cplant* Nplant = new Cplant(type, 0, getCompleteGrowtime(type) ,100)
		plant = Nplant;
	}

	//setters
	void setPlant(Cplant* Nplant)
	{
		plant = Nplant;
	}

	//getters
	Cplant* getPlant()
	{
		return plant;
	}
};