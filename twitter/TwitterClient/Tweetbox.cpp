
#include "Tweetbox.h"
#include "cmath"

Tweetbox::Tweetbox()
{
}

Tweetbox::Tweetbox(float x, float y, const sf::Vector2f& size,
	float radius, unsigned int cornerPointCount,
	sf::Font* font, sf::Color color, std::string text)
{
	this->m_size = size;
	this->m_radius = radius;
	this->m_cornerPointCount = cornerPointCount;
	this->setPosition(sf::Vector2f(x, y));
	this->setFillColor(color);
	this->setOutlineThickness(1);
	this->setOutlineColor(sf::Color(0xAAB8C2FF));

	this->m_font = font;
	this->m_text.setFont(*this->m_font);
	this->m_text.setCharacterSize(15);
	this->m_text.setFillColor(sf::Color::White);
	this->m_text.setString(text);
	this->m_text.setPosition(
		this->getPosition().x + this->getSize().x / 5,
		this->getPosition().y + this->getSize().y / 4+20
	);
	this->reboundText();
	this->initButtons();
	this->initClick();

	update();
}

Tweetbox::~Tweetbox()
{
	
}

void Tweetbox::SetUsername(const std::string& username)
{
	this->m_button.UserName->SetText(username);
}

void Tweetbox::SetText(const std::string& text)
{
	this->m_text.setString(text);
}

void Tweetbox::setSize(const sf::Vector2f& size)
{
	m_size = size;
	update();
}

void Tweetbox::setCornersRadius(float radius)
{
	m_radius = radius;
	update();
}

void Tweetbox::setCornerPointCount(unsigned int count)
{
	m_cornerPointCount = count;
	update();
}

const sf::Vector2f& Tweetbox::getSize() const
{
	return m_size;
}

float Tweetbox::getCornersRadius() const
{
	return m_radius;
}

std::size_t Tweetbox::getPointCount() const
{
	return m_cornerPointCount * 4;
}

sf::Vector2f Tweetbox::getPoint(std::size_t index) const
{
	if (index >= m_cornerPointCount * 4)
		return sf::Vector2f(0, 0);

	float delta = 90.0f / (m_cornerPointCount - 1);
	sf::Vector2f center;
	unsigned int centerIndex = index / m_cornerPointCount;
	static const float pi = 3.141592654f;

	switch (centerIndex)
	{
	case 0:
		center.x = m_size.x - m_radius;
		center.y = m_radius;
		break;
	case 1:
		center.x = m_radius;
		center.y = m_radius;
		break;
	case 2:
		center.x = m_radius;
		center.y = m_size.y - m_radius;
		break;
	case 3:
		center.x = m_size.x - m_radius;
		center.y = m_size.y - m_radius;
		break;
	}

	return sf::Vector2f(m_radius * cos(delta * (index - centerIndex) * pi / 180) + center.x,
		-m_radius * sin(delta * (index - centerIndex) * pi / 180) + center.y);
}

void Tweetbox::reboundText()
{
	std::string text = m_text.getString();
	text.insert(0, 1, ' ');
	m_text.setString(text);
	float xBoundary = this->getPosition().x + this->getSize().x - 10;
	float yBoundary = this->getPosition().y + this->getSize().y / 4 * 3;
	int lastSpace = -1;
	for (int index = 0;index <= text.size();index++)
	{
		if (text[index] == ' ')
			lastSpace = index;
		if (m_text.findCharacterPos(index).x > xBoundary)
		{
			text.insert(lastSpace, 1, '\n');
			m_text.setString(text);
		}
		if (m_text.findCharacterPos(index).y > yBoundary)
		{
			m_text.setCharacterSize(m_text.getCharacterSize() - 2);
		}
	}
}

void Tweetbox::updateUseButtons()
{
	if (this->m_button.Comment->getButtonState() == 2 and !this->m_click.CommentClick)
	{
		//action
		std::cout << "comm\n";
		this->m_click.CommentClick = true;
	}
	if (this->m_button.Likes->getButtonState() == 2 and !this->m_click.LikesClick)
	{
		//action
		std::cout << "like\n";
		this->m_click.LikesClick = true;
	}
	
	if (this->m_button.Retweet->getButtonState() == 2 and !this->m_click.RetweetClick)
	{
		//action
		std::cout << "retweet\n";
		this->m_click.RetweetClick = true;
	}
	if (this->m_button.UserName->getButtonState() == 2 and !this->m_click.UserNameClick)
	{
		//action
		std::cout << "user\n";
		this->m_click.UserNameClick = true;
	}
}

void Tweetbox::updateButtons(const sf::Vector2f mousePos)
{
	this->m_button.Comment->update(mousePos);
	this->m_button.Likes->update(mousePos);
	this->m_button.Retweet->update(mousePos);
	this->m_button.UserName->update(mousePos);
}

void Tweetbox::updateTweetbox(const sf::Vector2f mousePos)
{
	this->updateButtons(mousePos);
	this->updateUseButtons();
}


void Tweetbox::renderButtons(sf::RenderTarget* target)
{
	this->m_button.Comment->render(target);
	this->m_button.Likes->render(target);
	this->m_button.Retweet->render(target);
	this->m_button.UserName->render(target);
}

void Tweetbox::render(sf::RenderTarget* target)
{
	target->draw(*this);
	target->draw(this->m_text);
	renderButtons(target);
}

void Tweetbox::initButtons()
{
	this->m_button.Comment = new Button(this->getPosition().x+this->getSize().x / 18*2,this->getPosition().y+this->getSize().y / 4 * 3+20,
		this->getSize().x / 18 * 4, this->getSize().y / 32 * 4,
		this->m_font, "3(comment)",
		sf::Color::Transparent, sf::Color(0xAAB8C2FF),
		sf::Color::Transparent, sf::Color::Transparent);
	this->m_button.Retweet = new Button(this->getPosition().x+this->getSize().x / 18*7,this->getPosition().y+this->getSize().y / 4 * 3+20,
		this->getSize().x / 18 * 4, this->getSize().y / 32 * 4,
		this->m_font, "54(Retweets)",
		sf::Color::Transparent, sf::Color(0xAAB8C2FF),
		sf::Color::Transparent, sf::Color::Transparent);
	this->m_button.Likes = new Button(this->getPosition().x+this->getSize().x / 18*12,this->getPosition().y+this->getSize().y / 4 * 3+20,
		this->getSize().x / 18 * 4, this->getSize().y / 32 * 4,
		this->m_font, "103(Likes)",
		sf::Color::Transparent, sf::Color(0xAAB8C2FF),
		sf::Color::Transparent, sf::Color::Transparent);
	this->m_button.UserName = new Button(this->getPosition().x+this->getSize().x / 5,this->getPosition().y+this->getSize().y / 8 ,
		this->getSize().x / 18 * 4, this->getSize().y / 32 * 4,
		this->m_font, "UserName",
		sf::Color::Transparent, sf::Color(0xAAB8C2FF),
		sf::Color::Transparent, sf::Color::Transparent);
	this->m_button.UserName->setTextStyle(sf::Text::Bold);
	sf::Vector2f pos{
		this->getPosition().x + this->getSize().x / 5+2,
		this->getPosition().y + this->getSize().y / 8+ 10
	};
	this->m_button.UserName->setPosition(pos);
}

void Tweetbox::initClick()
{
	this->m_click.CommentClick = false;
	this->m_click.LikesClick = false;
	this->m_click.RetweetClick = false;
	this->m_click.UserNameClick = false;
}

