#pragma once
#include<SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "OpenDirectory.h"
#include "dirent.h"
#include "Botao.h"

#define TELA_INICIAL 0
#define TELA_RESULTADO 1

class Manager
{
private:
	sf::RenderWindow *janela;

	Botao *fundo1 = nullptr, *fundo2 = nullptr, *bsim = nullptr, *bnao = nullptr, *bcomp = nullptr;
	Botao *selec1, *selec2;
	sf::Vector2i mouse;
	sf::Event e;
	sf::Font fonte;
	std::vector<sf::Image*> imgGabarito, imgSegmentadas;
	std::vector<std::string> nomeArquivos;
	sf::Text* txtDiretorioGabarito = nullptr, *txtDiretorioSegmentadas = nullptr;
	sf::Text *relatorioFinal = nullptr;

	DIR *dir;
	struct dirent *lsdir;

	bool quit = false, diretoriosSelecionados = false;

	OpenDirectory *open;

	FILE* txtresultado;
	std::string diretorioExe, nomeArquivoParaSalvar;
	int fpt = 0, fnt = 0, fp = 0, fn = 0, totalPixels = 0;
	short estadoTela = TELA_INICIAL;

public:
	Manager();
	~Manager();

	void Programa();


	void Inputs();
	void Update();
	void Render();

	void RenderTela1();
	void RenderTela2();

	void InputTeclado();
	void MouseClicado(sf::Event& e);
	void MouseMovido();

	void CompararImagens();
	void DefinindoNomeArquivo();
	void ComparandoIndividulamente(short i);
	void ImprimindoDados(std::string titulo, int numPixels, int falsoP, int falsoN, bool n);
};

