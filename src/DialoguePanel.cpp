#include "../headers/DialoguePanel.h"

DialoguePanel::DialoguePanel(const sf::IntRect& textBox_) {
    index = 0;
    charIndex = 0;
    typingSpeed = 0.0625f;
    timer = 0.f;
    textBox = textBox_;
    text.setPosition(textBox_.left, textBox_.top);

}


void DialoguePanel::setTexture(const sf::Texture& texture_) {
    sprite.setTexture(texture_);
}

void DialoguePanel::setTextureRect(const sf::IntRect& intRect_) {
    sprite.setTextureRect(intRect_);
}

void DialoguePanel::setTexturePos(const sf::Vector2<float>& pos_) {
    sprite.setPosition(pos_);
}

void DialoguePanel::setTextureDim(const sf::Vector2<float>& dim_) {
    sprite.setScale(dim_.x / sprite.getTexture()->getSize().x, dim_.y / sprite.getTexture()->getSize().y);
}

void DialoguePanel::setText(const sf::Text& text_) {
    text = text_;
}

void DialoguePanel::setText(const std::string& string_) {
    text.setString(string_);
}

void DialoguePanel::addText(const std::string& string_) {
    strings.emplace_back(string_);
}

void DialoguePanel::setFont(const sf::Font& font_) {
    text.setFont(font_);
}

void DialoguePanel::setTextPos(const sf::Vector2<float>& pos_) {
    text.setPosition(pos_);
    textBox.left = pos_.x;
    textBox.top = pos_.y;
}

void DialoguePanel::setTextSize(int size_) {
    text.setCharacterSize(size_);
}

void DialoguePanel::setTextBox(const sf::IntRect& box_) { 
    text.setPosition(box_.left, box_.top);
    textBox = box_;
}

void DialoguePanel::setTextColor(const sf::Color& color_) {
    text.setFillColor(color_);
}

void DialoguePanel::setTypingSpeed(const float& typingSpeed_) {
    typingSpeed = typingSpeed_;
}

void DialoguePanel::next() {
    charIndex = 0;
    timer = 0.f;
    if (index < strings.size()-1) index++;
}

void DialoguePanel::update(const float& dt) {
    timer += dt;
    if (timer > typingSpeed) {
        timer = 0.f;
        if (charIndex < strings[index].size()) charIndex++;
    }

    text.setString(strings[index].substr(0, charIndex));
    if (text.getGlobalBounds().width > textBox.width) {
        auto backIndex = text.getString().toWideString().find_last_of('\n');
        auto spaceIndex = text.getString().toWideString().find_last_of(' ');
        if (spaceIndex != std::string::npos && ( backIndex == std::string::npos || backIndex < spaceIndex))
            strings[index][spaceIndex] = '\n';
        else strings[index].insert(charIndex-1, "\n");
    }       

    if (text.getGlobalBounds().height > textBox.height) { 
        auto backIndex = text.getString().toWideString().find_last_of('\n');
        if (backIndex != std::string::npos) {
            strings.insert(strings.begin() + index + 1, strings[index].substr(backIndex+1, strings[index].size()));
            strings[index] = strings[index].substr(0, backIndex);
        }
        else {
            strings.insert(strings.begin() + index + 1, strings[index].substr(charIndex-3, strings[index].size()));
            strings[index] = strings[index].substr(0, charIndex-3);
        }
        strings[index].append("...");
    }
}

void DialoguePanel::render(sf::RenderWindow& window_) {
    window_.draw(sprite);
    window_.draw(text);
}