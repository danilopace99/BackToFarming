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
	void eachframe()
	{
		if (plant != NULL)
		{
			agePlant();
		}
	}

	void agePlant()
	{
		plant->setGrowTime(plant->getGrowTime() + 1);
		plant->setAmmountWater(plant->getAmmountWater() - 1);
	}

	void waterPlant()
	{
		plant->setAmmountWater(plant->getAmmountWater() + 1800);
	}

	void plantPlant(string type)
	{
		Cplant* Nplant = new Cplant(type, 0, getCompleteGrowtime(type), 1800);
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