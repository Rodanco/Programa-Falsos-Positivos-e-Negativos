#pragma once
#include<iostream>
#include <Windows.h>


class OpenDirectory
{
private:
	std::string diretorio;

public:
	OpenDirectory();
	~OpenDirectory();

	bool SelecionarPasta(short tipo, std::string diretorioBase);

	std::string& GetDiretorioDaPasta();
};

