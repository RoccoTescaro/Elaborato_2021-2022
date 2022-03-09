#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>

class Button {
public:

    Button(const sf::Vector2<float>& pos_, const sf::Vector2<int> dim_): pos(pos_), dim(dim_){};

    //TEXTURE/SPRITE
    void setTexture(const sf::Texture& texture_);

    void setTextureRect(const sf::IntRect& intRect_);

    //TEXT
    void setText(const sf::Text& text_);

    std::string getTextString() const;

    void setText(const std::string& string_);

    void setFont(const sf::Font& font_);

    void setTextPos(const sf::Vector2<float>& pos_);

    void setTextSize(int size_);

    void setTextColor(const sf::Color& color_);

    //BUTTON
    bool isMouseOver(const sf::Vector2<float>& pos_) const;

    void setClicked(bool clicked_);

    void setClicked();

    bool isClicked() const;
    
    void setActive(bool active_);

    bool isActive() const;

    //RENDER
    void render(sf::RenderWindow& window_, sf::Shader* shader = nullptr);

private:

    bool active = true;
    
    bool clicked = false;

    sf::Vector2<float> pos;
    sf::Vector2<int> dim;

    sf::Sprite sprite;

    sf::Text text;

};


#endif //BUTTON_H
