#pragma once

#include<SFML\Graphics.hpp>

class Botao
{
private:
	sf::Texture *m_textura = nullptr;
	sf::RectangleShape *m_rec = nullptr;
	sf::IntRect imgFonte;
public:
	Botao(float posX, float posY, float larg, float alt, short divsoria, std::string nomeImg);
	~Botao();

	bool Pressionado(sf::Vector2i &mouse);
	sf::RectangleShape &GetDraw();
	void TrocarTextura(short valor);
};

