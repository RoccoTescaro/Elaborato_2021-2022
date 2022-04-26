#ifndef DIALOGUEPANEL_H
#define DIALOGUEPANEL_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class DialoguePanel {
public:

    DialoguePanel(const sf::IntRect& textBox_);

    void setTexture(const sf::Texture& texture_);

    void setTextureRect(const sf::IntRect& intRect_);

    void setTexturePos(const sf::Vector2<float>& pos_);

    void setTextureDim(const sf::Vector2<float>& dim_);

    void setText(const sf::Text& text_);

    void addText(const std::string& string_);

    void setFont(const sf::Font& font_);

    void setTextPos(const sf::Vector2<float>& pos_);

    void setTextSize(int size_);

    void setTextBox(const sf::IntRect& box_);

    void setTextColor(const sf::Color& color_);

    void setTypingSpeed(const float& typingSpeed_);

    void next();

    void update(const float& dt);

    void render(sf::RenderWindow& window_);

private:

    //STATE
    std::vector<std::string> strings;

    unsigned int index;

    unsigned int charIndex;

    float typingSpeed;

    float timer;

    //POSITION
    sf::IntRect textBox;

    //RENDER
    sf::Sprite sprite;

    sf::Text text;

    //SOUND
    std::vector<sf::SoundBuffer> soundBuffer;

    sf::Sound sound;
};

#endif //DIALOGUEPANEL_H