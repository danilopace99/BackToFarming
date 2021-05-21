#pragma once
#include "stdafx.h"
#include "Plant.h"
#include "MyGame.h"

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
		setImgRight();
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

	int harvestPlant()
	{
		if (plant != NULL)
		{
			if (plant->getPercentDone() > 1)
			{
				int rtn;
				if (plant->getType() == "carrots")
				{
					rtn = 1;
				}
				else if (plant->getType() == "potatoes")
				{
					rtn = 2;
				}
				plant = NULL;
				return rtn;
			}
		}
		else
		{
			return 0;
		}
	}

	void setImgRight()
	{
		if (plant == NULL)
		{
			SetImage("feild1.jpg");
		}
		else if (plant->getPercentDone() < 0.4)
		{
			SetImage("feild2.jpg");
		}
		else if (plant->getPercentDone() < 1)
		{
			SetImage("feild3.jpg");
		}
		else if (plant->getPercentDone() > 1)
		{
			SetImage("feild4.jpg");
		}
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