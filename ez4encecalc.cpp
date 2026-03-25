#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1200, 600 }), "kalkulerer", sf::Style::Titlebar | sf::Style::Close);
	//fataahh
	float buttonSize = window.getSize().x / 10;
	float buttonHeight = window.getSize().y / 10;
	float buttonMargin = 3;
	sf::RectangleShape buttonSquares({ buttonSize, buttonHeight });
	sf::RectangleShape outPutSquare({ (buttonSize + buttonMargin) * 3 - buttonMargin, buttonHeight });
	sf::Vector2f buttonPos(100, 100);
	sf::Font font("kalk.ttf");
	sf::Text text(font);
	sf::Text outputText(font);
	text.setFillColor(sf::Color::Black);
	outputText.setFillColor(sf::Color::Black);
	std::string kalkInput;

	std::string numbers;
	int tempInt = 0;
	std::vector<int> allNumbers;
	std::vector<char> operators;

	std::string calculate(std::string kalkInput, std::vector<int> allNumbers, std::vector<char> operators, std::string numbers);
	while (window.isOpen())
	{
		sf::Vector2f buttonPos(100, 100);
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		int buttonNumber;

		while (std::optional event = window.pollEvent())
		{
			std::string numbers;
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (mouseClick->button == sf::Mouse::Button::Left)
				{
					for (int i = 0; i <= 5; i++)
					{
						for (int j = 1; j <= 3; j++)
						{
							buttonPos = sf::Vector2f({ buttonPos.x + buttonSize + buttonMargin, buttonPos.y });
							buttonNumber = i * 3 + j;
							if (mousePos.x > buttonPos.x && mousePos.y > buttonPos.y && mousePos.x < buttonPos.x + buttonSize && mousePos.y < buttonPos.y + buttonHeight)
							{
								if (i < 3)
								{
									kalkInput = kalkInput + std::to_string(buttonNumber);
								}
								else if (i == 3 && j == 2)
								{
									kalkInput = kalkInput + "0";
								}
								switch (buttonNumber)
								{
								case 10:
									kalkInput = kalkInput + "+";
									break;
								case 12:
									kalkInput = kalkInput + "-";
									break;
								case 13:
									kalkInput = kalkInput + "*";
									break;
								case 14:
								{
									kalkInput = calculate(kalkInput, allNumbers, operators, numbers);
									break;
								}
								case 15:
									kalkInput = kalkInput + "/";
									break;
								case 17:
									if (kalkInput.length() > 0)
									{
										kalkInput.erase(0, kalkInput.length());
									}
									break;
								}
							}
						}
						buttonPos = sf::Vector2f({ 100, buttonPos.y + buttonHeight + buttonMargin });
					}
				}
				if (mouseClick->button == sf::Mouse::Button::Right)
				{
					std::cout << kalkInput << std::endl;
				}
			}
			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->code == sf::Keyboard::Key::Enter)
				{
					kalkInput = calculate(kalkInput, allNumbers, operators, numbers);
				}
				if (keyPressed->code == sf::Keyboard::Key::Backspace)
				{
					kalkInput.erase(kalkInput.length() - 1, 1);
				}
			}
			if (event->is<sf::Event::TextEntered>())
			{
				const auto* textEntered = event->getIf<sf::Event::TextEntered>();
				std::cout << std::to_string(textEntered->unicode) << std::endl;
				if (textEntered->unicode >= 48 && textEntered->unicode <= 57)
				{
					kalkInput = kalkInput + (char)textEntered->unicode;
				}
				else if (textEntered->unicode == 43 || textEntered->unicode == 42 || textEntered->unicode == 45 || textEntered->unicode == 47)
				{
					kalkInput = kalkInput + (char)textEntered->unicode;
				}
			}
		}
		window.clear(sf::Color::Black);
		buttonPos = sf::Vector2f(100 + buttonSize + buttonMargin, 100 - buttonMargin - buttonHeight);
		outPutSquare.setPosition(buttonPos);
		window.draw(outPutSquare);
		outputText.setString(kalkInput);
		outputText.setPosition(buttonPos);
		window.draw(outputText);
		buttonPos = sf::Vector2f(100, 100);

		for (int i = 0; i <= 5; i++)
		{
			for (int j = 1; j <= 3; j++)
			{
				buttonPos = sf::Vector2f({ buttonPos.x + buttonSize + buttonMargin, buttonPos.y });
				buttonSquares.setPosition(buttonPos);
				window.draw(buttonSquares);
				int buttonNumber = i * 3 + j;
				if (i < 3)
				{
					text.setPosition(buttonPos);
					text.setString(std::to_string(buttonNumber));
					window.draw(text);
				}
				switch (buttonNumber)
				{
				case 10:
					text.setPosition(buttonPos);
					text.setString("+");
					window.draw(text);
					break;
				case 11:
					text.setPosition(buttonPos);
					text.setString("0");
					window.draw(text);
					break;
				case 12:
					text.setPosition(buttonPos);
					text.setString("-");
					window.draw(text);
					break;
				case 13:
					text.setPosition(buttonPos);
					text.setString("*");
					window.draw(text);
					break;
				case 14:
					text.setPosition(buttonPos);
					text.setString("=");
					window.draw(text);
					break;
				case 15:
					text.setPosition(buttonPos);
					text.setString("/");
					window.draw(text);
					break;
				case 17:
					text.setPosition(buttonPos);
					text.setString("c");
					window.draw(text);
					break;
				}
			}
			buttonPos = sf::Vector2f({ 100, buttonPos.y + buttonHeight + buttonMargin });
			buttonSquares.setPosition(buttonPos);
		}

		window.display();
	}
}
std::string calculate(std::string kalkInput, std::vector<int> allNumbers, std::vector<char> operators, std::string numbers) {
	kalkInput = kalkInput + "=";
	allNumbers.clear();
	operators.clear();
	for (int i = 0; i < kalkInput.length(); i++) {
		if (kalkInput[i] - '0' >= 0 && kalkInput[i] - '0' <= 9) {
			numbers += kalkInput[i];
		}
		else if (kalkInput[i] == '+' || kalkInput[i] == '-' || kalkInput[i] == '*' || kalkInput[i] == '/') {
			if (kalkInput[i] == '-' && (i == 0 || kalkInput[i - 1] == '+' || kalkInput[i - 1] == '-' || kalkInput[i - 1] == '*' || kalkInput[i - 1] == '/')) {
				numbers += kalkInput[i];
			}
			else {
				allNumbers.push_back(std::stoi(numbers));
				numbers.clear();
				operators.push_back(kalkInput[i]);
			}
		}
		else if (kalkInput[i] == '=') {
			allNumbers.push_back(std::stoi(numbers));
			numbers.erase(0, numbers.length());
		}
	}
	int result = allNumbers[0];

	for (int i = 0; i < operators.size(); i++) {
		if (operators[i] == '*' || operators[i] == '/') {
			if (operators[i] == '*') {
				allNumbers[i] *= allNumbers[i + 1];
			}
			else if (operators[i] == '/') {
				allNumbers[i] /= allNumbers[i + 1];
			}
			allNumbers.erase(allNumbers.begin() + i + 1);
			operators.erase(operators.begin() + i);
			i--;
		}
	}
	result = allNumbers[0];
	for (int i = 0; i < operators.size(); i++) {
		if (operators[i] == '+') {
			result += allNumbers[i + 1];
		}
		else if (operators[i] == '-') {
			result -= allNumbers[i + 1];
		}
	}
	std::cout << result << std::endl;
	return std::to_string(result);
}