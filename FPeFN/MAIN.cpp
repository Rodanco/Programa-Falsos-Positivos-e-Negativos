#include <SFML\Graphics.hpp>
#include "Manager.h"

int main()
{
	Manager* manager = new Manager();
	manager->Programa();
	delete manager;
	return 0;
}