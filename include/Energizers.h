#pragma
#include "Eatable.h"

class Energizer: public Eatable
{
public:
	Energizer(Type energizerType):Eatable(energizerType),Entity(energizerType)
	{
		
	}

	~Energizer(){}

private:

};

