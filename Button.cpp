#include "Button.h"

void Button::setTexture(const sf::Texture& texture_) {
    sprite.setTexture(texture_);
}

void Button::setTextureRect(const sf::IntRect& intRect_) {
    sprite.setTextureRect(intRect_);
}

void Button::setText(const sf::Text& text_) {
    text = text_;
}

void Button::setText(const std::string& string_) {
    text.setString(string_);
}

std::string Button::getTextString() const {
    return text.getString();
}

void Button::setFont(const sf::Font& font_) {
    text.setFont(font_);
}

void Button::setTextPos(const sf::Vector2<float>& pos_) {
    text.setPosition(pos_);
}

void Button::setTextSize(int size_) {
    text.setCharacterSize(size_);
}

void Button::setTextColor(const sf::Color& color_) {
    text.setFillColor(color_);
}

bool Button::isMouseOver(const sf::Vector2<float>& pos_) const {
    return (pos.x<pos_.x && pos_.x<pos.x+dim.x)&&(pos.y<pos_.y && pos_.y<pos.x+dim.y);
}

void Button::setClicked(bool clicked_) {
    clicked = clicked_;
}

void Button::setClicked() {
    clicked = !clicked;
}

bool Button::isClicked() const {
    return clicked;
}

void Button::setActive(bool active_) {
    active = active_;
}

bool Button::isActive() const {
    return active;
}

void Button::render(sf::RenderWindow& window_, sf::Shader* shader) {
    window_.draw(sprite, shader);
    window_.draw(text);
}
