#include "Menu.hpp"

Menu::Menu() :
	mState(State::TopLevel)
{

	mControls.DownEvent = [this]() { ChangeSelectedItem(false); };
	mControls.UpEvent = [this]() { ChangeSelectedItem(true); };
	mFont.loadFromFile(Font);
	
	MenuButton::ButtonSettings bs;
	bs.fontSize = 35;
	bs.selectedBackgroundColor = bs.backgroundColor = sf::Color(0x20, 0x20, 0x20);
	bs.selectedBoxOutlineColor = sf::Color::Cyan;
	bs.boxOutlineColor = sf::Color(0x60, 0x60, 0x60);
	bs.selectedBoxOutlineSize = bs.boxOutlineSize = 2;
	bs.selectedTextColor = bs.textColor = sf::Color::White;
	bs.boxSize = { 250.f, 60.f };

	MenuButton mbNewGame("New game", mFont, bs);
	mbNewGame.Select();
	MenuButton mbExit("Exit", mFont, bs);
	mTopLevelButtons.push_back(mbNewGame);
	mTopLevelButtons.push_back(mbExit);
}

void Menu::ChangeSelectedItem(bool goUp)
{
	if (mTopLevelButtons.size() == 1)
	{
		mTopLevelButtons[0].Select();
		return;
	}

	MenuButton * last = &mTopLevelButtons[0];

	size_t itemsCount = mTopLevelButtons.size();
	for (int i = 0; i < itemsCount; i++)
	{
		MenuButton& actual = mTopLevelButtons[i];
		if (actual.IsSelected())
		{
			if (goUp)
			{
				actual.Unselect();
				last->Select();
				return;
			}
			else if (i + 1 < itemsCount)
			{
				actual.Unselect();
				mTopLevelButtons[i + 1].Select();
				return;
			}
		}
		last = &actual;
	}
}

sf::Time Menu::GetSleepTime()
{
	return sf::Time();
}

void Menu::Update()
{

}

void Menu::DrawTopLevel(sf::RenderWindow& window, sf::Transform t, uint8_t alpha)
{
	t.translate({ window.getSize().x * 0.1f, window.getSize().y * 0.6f });
	for (MenuButton& b : mTopLevelButtons)
	{
		b.Draw(window, t, alpha);
		auto s = b.GetSize();
		t.translate({ 0, s.y + 10 });
	}

}

void Menu::DrawNewGame(sf::RenderWindow& window, sf::Transform t, uint8_t alpha)
{

}

void Menu::Draw(sf::RenderWindow & window, sf::Transform t, uint8_t alpha)
{
	window.clear();
	//TODO background

	switch (mState)
	{
		case State::TopLevel:
			DrawTopLevel(window, t, alpha);
			break;
		case State::NewGame:
			DrawNewGame(window, t, alpha);
			break;
	}

}

void Menu::ProcessEvent(sf::Event e)
{
	mControls.ProcessEvent(e);
}