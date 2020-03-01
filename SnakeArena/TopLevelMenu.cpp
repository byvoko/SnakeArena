#include "TopLevelMenu.hpp"
#include "MenuButton.hpp"

TopLevelMenu::TopLevelMenu()
{
	
}

void TopLevelMenu::Init(MenuItem::Settings ItemsSettings, sf::Font& font)
{
	MenuButton* mbNewGame = new MenuButton("New game", font, ItemsSettings);
	mbNewGame->Select();
	MenuButton* mbSettings = new MenuButton("Settings", font, ItemsSettings);
	MenuButton* mbExit = new MenuButton("Exit", font, ItemsSettings);
	mItems.push_back(mbNewGame);
	mItems.push_back(mbSettings);
	mItems.push_back(mbExit);

/*	TODO
	enum I
	{
		NewGame = 0,
		Settings,
		Exit,

		ICount
	};
	mItems.reserve(I::ICount);
	mItems[I::Exit] = mbExit;*/
}

void TopLevelMenu::Update()
{

}

void TopLevelMenu::Draw(sf::RenderWindow& window, sf::Transform t, uint8_t alpha)
{
	window.clear(sf::Color(0x27, 0x6B, 0x38));

	t.translate({ window.getSize().x * 0.1f, window.getSize().y * 0.6f });

	for (MenuItem* mi : mItems)
	{
		if (!mi->IsVisible())
			continue;

		auto s = mi->GetSize();
		mi->Draw(window, t, alpha);
		t.translate({ 0, s.y + 10 });
	}
}

void TopLevelMenu::SetOnClickEventNewGame(Event e)
{
	MenuButton& newGame = *(static_cast<MenuButton*>(mItems[0]));
	newGame.SetOnClickEvent(e);
}