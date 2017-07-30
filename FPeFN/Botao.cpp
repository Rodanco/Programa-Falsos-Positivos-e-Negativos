#include "Botao.h"



Botao::Botao(float posX, float posY, float larg, float alt, short divisoria, std::string nomeImg)
{
	m_textura = new sf::Texture();
	m_textura->loadFromFile(nomeImg);
	m_rec = new sf::RectangleShape();
	m_rec->setTexture(m_textura);
	int l = m_textura->getSize().x;
	int h = m_textura->getSize().y / (divisoria * 1.0f);
	imgFonte = { 0,0,l,h };
	m_rec->setTextureRect(sf::IntRect(0, 0, l, h));
	m_rec->setPosition(posX, posY);
	m_rec->setSize(sf::Vector2f(larg, alt));
}


Botao::~Botao()
{
	delete m_textura;
	delete m_rec;
}

bool Botao::Pressionado(sf::Vector2i & mouse)
{
	if (m_rec->getPosition().x <= mouse.x && m_rec->getPosition().x + m_rec->getGlobalBounds().width >= mouse.x)
		if (m_rec->getPosition().y <= mouse.y && m_rec->getPosition().y + m_rec->getGlobalBounds().height >= mouse.y)
			return true;
	return false;
}

sf::RectangleShape & Botao::GetDraw()
{
	return *m_rec;
}

void Botao::TrocarTextura(short valor)
{
	imgFonte.top = valor;
	m_rec->setTexture(m_textura, true);
	m_rec->setTextureRect(imgFonte);
}
