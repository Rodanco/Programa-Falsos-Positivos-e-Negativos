#include "Manager.h"


Manager::Manager()
{
	TCHAR path[MAX_PATH + 1] = "L";
	DWORD a = GetCurrentDirectoryA(MAX_PATH, path);
	diretorioExe = path;
	diretorioExe += "\\";
	std::cout << "Diretorio Executavel: " << diretorioExe.c_str() << std::endl;
	janela = new sf::RenderWindow(sf::VideoMode(1280, 720), "Programa");
	fundo1 = new Botao(0,0,1280,720,1,"Assets/Fundo.png");
	fundo2 = new Botao(0, 0, 1280, 720, 1, "Assets/Fundo1.png");
	bsim = new Botao(420, 594, 100, 50, 2, "Assets/Bsim.png");
	bnao = new Botao(760, 594, 100, 50, 2, "Assets/Bnão.png");
	bcomp = new Botao(430, 601, 420, 60, 2, "Assets/ComIma.png");
	selec1 = new Botao(816, 262, 420, 60, 2, "Assets/SeleDire.png");
	selec2 = new Botao(816, 425, 420, 60, 2, "Assets/SeleDire.png");

	open = new OpenDirectory();

	fonte.loadFromFile("arial.ttf");
	txtDiretorioGabarito = new sf::Text();
	txtDiretorioGabarito->setFont(fonte);
	txtDiretorioGabarito->setCharacterSize(20);
	txtDiretorioGabarito->setPosition(21, 266);
	txtDiretorioSegmentadas = new sf::Text(); 
	txtDiretorioSegmentadas->setFont(fonte);
	txtDiretorioSegmentadas->setCharacterSize(20);
	txtDiretorioSegmentadas->setPosition(21, 429);

	relatorioFinal = new sf::Text();
	relatorioFinal->setFont(fonte);
	relatorioFinal->setPosition(90, 130);
}


Manager::~Manager()
{
	if (!imgGabarito.empty())
	{
		for (short i = 0; i < imgGabarito.size(); i++)
			delete imgGabarito[i];
		imgGabarito.clear();
	}
	if (!imgSegmentadas.empty())
	{
		for (short i = 0; i < imgSegmentadas.size(); i++)
			delete imgSegmentadas[i];
		imgSegmentadas.clear();
	}
	delete txtDiretorioSegmentadas;
	delete txtDiretorioGabarito;
	delete relatorioFinal;
	delete janela;
	delete open;
	delete fundo1;
	delete fundo2;
	delete bsim;
	delete bnao;
	delete bcomp;
	delete selec1;
	delete selec2;
}

void Manager::Programa()
{
	while (!quit)
	{		
		Inputs();
		Update();
		Render();
	}
}

void Manager::Inputs()
{
	if (janela->hasFocus() && janela->pollEvent(e))
	{
		mouse = sf::Mouse::getPosition(*janela);
		switch (e.type)
		{
		case sf::Event::Closed:
			quit = true;
			break;
		case sf::Event::KeyPressed:
			InputTeclado();
			break;
		case sf::Event::MouseButtonPressed:
			MouseClicado(e);
			break;
		case sf::Event::MouseMoved:
			MouseMovido();
			break;
		}
	}
}

void Manager::Update()
{
	if (!txtDiretorioSegmentadas->getString().isEmpty() && !txtDiretorioGabarito->getString().isEmpty())
		diretoriosSelecionados = true;
	else
		false;
}

void Manager::Render()
{
	janela->clear();
	switch (estadoTela)
	{
	case TELA_INICIAL:
		RenderTela1();
		break;
	default:
		RenderTela2();
		break;
	}
	janela->display();
}

void Manager::RenderTela1()
{
	janela->draw(fundo1->GetDraw());
	janela->draw(*txtDiretorioGabarito);
	janela->draw(*txtDiretorioSegmentadas);
	janela->draw(selec1->GetDraw());
	janela->draw(selec2->GetDraw());
	janela->draw(bcomp->GetDraw());
}

void Manager::RenderTela2()
{
	janela->draw(fundo2->GetDraw());
	janela->draw(*relatorioFinal);
	janela->draw(bsim->GetDraw());
	janela->draw(bnao->GetDraw());
}

void Manager::InputTeclado()
{
	if(estadoTela == TELA_INICIAL)
		switch (e.key.code)
		{
		case sf::Keyboard::M:
			if (open->SelecionarPasta(1, diretorioExe))
			{
				if (!imgGabarito.empty())
					imgGabarito.clear();
				dir = opendir(open->GetDiretorioDaPasta().c_str());
				nomeArquivos.clear();
				while ((lsdir = readdir(dir)) != NULL)
				{
					nomeArquivos.push_back(lsdir->d_name);
				}
				nomeArquivos.erase(nomeArquivos.begin());
				nomeArquivos.erase(nomeArquivos.begin());
				for (short i = 0; i < nomeArquivos.size(); i++)
				{
					imgGabarito.push_back(new sf::Image());
					imgGabarito[i]->loadFromFile(open->GetDiretorioDaPasta() + nomeArquivos[i]);
				}
			}
			break;

		case sf::Keyboard::N:
			if (open->SelecionarPasta(2, diretorioExe))
			{
				if (!imgSegmentadas.empty())
					imgSegmentadas.clear();
				dir = opendir(open->GetDiretorioDaPasta().c_str());
				nomeArquivos.clear();
				while ((lsdir = readdir(dir)) != NULL)
				{
					nomeArquivos.push_back(lsdir->d_name);
				}
				nomeArquivos.erase(nomeArquivos.begin());
				nomeArquivos.erase(nomeArquivos.begin());
				for (short i = 0; i < nomeArquivos.size(); i++)
				{
					imgSegmentadas.push_back(new sf::Image());
					imgSegmentadas[i]->loadFromFile(open->GetDiretorioDaPasta() + nomeArquivos[i]);
				}
			}
			break;

		case sf::Keyboard::K:
			CompararImagens();
			break;
		}

	else
	{
		switch (e.key.code)
		{

		}
	}
}

void Manager::MouseClicado(sf::Event& e)
{
	switch (e.mouseButton.button)
	{
	case sf::Mouse::Left:

		if (estadoTela == TELA_INICIAL)
		{
			if (selec1->Pressionado(mouse))
			{
				if (open->SelecionarPasta(1, diretorioExe))
				{
					if (!imgGabarito.empty())
					{
						for (short i = 0; i < imgGabarito.size(); i++)
							delete imgGabarito[i];
						imgGabarito.clear();
					}
					dir = opendir(open->GetDiretorioDaPasta().c_str());
					txtDiretorioGabarito->setString(open->GetDiretorioDaPasta());
					nomeArquivos.clear();
					while ((lsdir = readdir(dir)) != NULL)
					{
						nomeArquivos.push_back(lsdir->d_name);
					}
					nomeArquivos.erase(nomeArquivos.begin());
					nomeArquivos.erase(nomeArquivos.begin());
					for (short i = 0; i < nomeArquivos.size(); i++)
					{
						imgGabarito.push_back(new sf::Image());
						imgGabarito[i]->loadFromFile(open->GetDiretorioDaPasta() + nomeArquivos[i]);
					}
				}
				break;
			}

			if (selec2->Pressionado(mouse))
			{
				if (open->SelecionarPasta(2, diretorioExe))
				{
					if (!imgSegmentadas.empty())
					{
						for (short i = 0; i < imgSegmentadas.size(); i++)
							delete imgSegmentadas[i];
						imgSegmentadas.clear();
					}
					dir = opendir(open->GetDiretorioDaPasta().c_str());
					txtDiretorioSegmentadas->setString(open->GetDiretorioDaPasta());
					nomeArquivos.clear();
					while ((lsdir = readdir(dir)) != NULL)
					{
						nomeArquivos.push_back(lsdir->d_name);
					}
					nomeArquivos.erase(nomeArquivos.begin());
					nomeArquivos.erase(nomeArquivos.begin());
					for (short i = 0; i < nomeArquivos.size(); i++)
					{
						imgSegmentadas.push_back(new sf::Image());
						imgSegmentadas[i]->loadFromFile(open->GetDiretorioDaPasta() + nomeArquivos[i]);
					}
				}
				break;
			}

			if (bcomp->Pressionado(mouse) && diretoriosSelecionados)
			{
				estadoTela = TELA_RESULTADO;
				CompararImagens();
			}
		}
		else
		{
			if (bsim->Pressionado(mouse))
			{
				estadoTela = TELA_INICIAL;
				std::string m;
				m.clear();
				txtDiretorioGabarito->setString(m);
				txtDiretorioSegmentadas->setString(m);
				relatorioFinal->setString(m);
				diretoriosSelecionados = false;
			}
			if (bnao->Pressionado(mouse))
				quit = true;
		}
		break;
	}
}

void Manager::MouseMovido()
{
	if (bsim->Pressionado(mouse))
		bsim->TrocarTextura(50);
	else
		bsim->TrocarTextura(0);

	if (bnao->Pressionado(mouse))
		bnao->TrocarTextura(50);
	else
		bnao->TrocarTextura(0);

	if (bcomp->Pressionado(mouse))
		bcomp->TrocarTextura(60);
	else
		bcomp->TrocarTextura(0);

	if (selec1->Pressionado(mouse))
		selec1->TrocarTextura(60);
	else
		selec1->TrocarTextura(0);

	if (selec2->Pressionado(mouse))
		selec2->TrocarTextura(60);
	else
		selec2->TrocarTextura(0);
}

void Manager::CompararImagens()
{	
	totalPixels = 0; fpt = 0; fnt = 0;
	DefinindoNomeArquivo();
	std::string nome = diretorioExe + "Relatorios\\" + nomeArquivoParaSalvar;
	txtresultado = fopen(nome.c_str(), "w+");
	for (short i = 0; i < imgGabarito.size(); i++)
	{
		ComparandoIndividulamente(i);
	}
	ImprimindoDados("SOMATÓRIO DE TODAS AS IMAGENS", totalPixels, fpt, fnt, true);
	fclose(txtresultado);
}

void Manager::DefinindoNomeArquivo()
{
	nomeArquivoParaSalvar = txtDiretorioGabarito->getString();
	std::string n = txtDiretorioGabarito->getString();
	n.erase(n.begin() + n.length() - 1);
	nomeArquivoParaSalvar.erase(nomeArquivoParaSalvar.begin() + nomeArquivoParaSalvar.length() - 1);
	short v = n.length() - 1;
	while (n[v] != '\\')
	{
		n.erase(n.begin() + v);
		v--;
	}

	nomeArquivoParaSalvar.replace(nomeArquivoParaSalvar.begin(), nomeArquivoParaSalvar.begin() + v + 1, "");
	nomeArquivoParaSalvar += ".txt";
}

void Manager::ComparandoIndividulamente(short img)
{
	const sf::Vector2u tamImg = imgGabarito[img]->getSize();
	fp = 0, fn = 0;

	for (short i = 0; i < tamImg.y; i++)
	{
		for (short j = 0; j < tamImg.x; j++)
		{
			if (imgGabarito[img]->getPixel(j, i) != imgSegmentadas[img]->getPixel(j, i))
			{
				if (imgGabarito[img]->getPixel(j, i).a > 0)
				{
					fp++;
					fpt++;
				}
				else
				{
					fn++;
					fnt++;
				}
			}
		}
	}
	int valor = tamImg.x*tamImg.y;
	totalPixels += valor;
	ImprimindoDados(nomeArquivos[img], valor, fp, fn, false);

}

void Manager::ImprimindoDados(std::string titulo, int numPixels, int falsoP, int falsoN, bool n)
{
	if (n == true)
	{
		std::string k = titulo + "\n" + "Total de Pixels :" + std::to_string(numPixels) + "\n";
		k += "_________________| Total | % \n";
		k += "Falsos Positivos:        |    " +
			std::to_string(falsoP) + "    | " + std::to_string(falsoP * 100.f / numPixels) + " \n";
		k += "Falsos Negativos:      |    " + std::to_string(falsoN) + "    | " + std::to_string(falsoN*100.f/numPixels) +
			" \n\n\n";
		relatorioFinal->setString(k);
	}
	fprintf(txtresultado, "%s \n", titulo.c_str());
	fprintf(txtresultado, "Total de Pixels:  %d \n", numPixels);
	fprintf(txtresultado, "_______________________| Total | %% \n");
	fprintf(txtresultado, "Falsos Positivos:      |   %d   | %f \n", falsoP, falsoP * 100.f / numPixels);
	fprintf(txtresultado, "Falsos Negativos:      |   %d   | %f \n\n\n", falsoN, falsoN * 100.f / numPixels);
}
