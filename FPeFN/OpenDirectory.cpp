#include "OpenDirectory.h"



OpenDirectory::OpenDirectory()
{
}


OpenDirectory::~OpenDirectory()
{
}
//...
bool OpenDirectory::SelecionarPasta(short tipo, std::string diretorioBase)
{
	char filename[MAX_PATH];
	OPENFILENAME openFile;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&openFile, sizeof(openFile));
	openFile.lStructSize = sizeof(openFile);
	openFile.hwndOwner = NULL;
	openFile.lpstrFile = filename;
	openFile.nMaxFile = MAX_PATH;
	openFile.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
	openFile.lpstrInitialDir = diretorioBase.c_str();
	std::cout << openFile.lpstrInitialDir << std::endl;
	switch (tipo)
	{
	case 0://Imagens Originais
		openFile.lpstrTitle = "Selecionar Pasta das Fotos Originais";
		break;
	case 1://Imagens Gabaritos
		openFile.lpstrTitle = "Selecionar Pasta dos Gabaritos";
		break;
	case 2://Imagens Segmentadas
		openFile.lpstrTitle = "Selecionar Pasta das Imagens Segmentadas";
		break;
	}
	if (GetOpenFileName(&openFile))
	{
		diretorio = (std::string)filename;
		while (diretorio[diretorio.length() - 1] != '\\')
			diretorio.erase(diretorio.begin() + diretorio.length()-1);
		return true;
	}
	else
		return false;
}

std::string & OpenDirectory::GetDiretorioDaPasta()
{
	return diretorio;
}
