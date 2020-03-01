#include "NewGameMenu.hpp"
#include "MenuButton.hpp"
#include "MenuSelect.hpp"

NewGameMenu::NewGameMenu()
{
}

void NewGameMenu::Init(MenuItem::Settings ItemsSettings, sf::Font& font)
{
	MenuButton* mbBack = new MenuButton("< Back", font, ItemsSettings);
	mbBack->Select();
	mItems.push_back(mbBack);
	MenuButton* mbStart = new MenuButton("Start", font, ItemsSettings);

	const size_t PlayersCount = 4;
	MenuSelect::Item iPlayers[PlayersCount];
	for (int i = 0; i < PlayersCount; i++)
	{
		iPlayers[i].text = std::to_string(i + 1);
		iPlayers[i].value = i + 1;
	}
	std::vector<MenuSelect::Item> viPlayers;
	viPlayers.assign(iPlayers, iPlayers + PlayersCount);
	MenuSelect* msPlayers = new MenuSelect("Players", font, ItemsSettings, viPlayers, 1);

	mItems.push_back(msPlayers);

	for (int i = 0; i < PlayersCount; i++)
	{
		PlayerInputSelector* pisPlayer = new PlayerInputSelector(i + 1, ItemsSettings, font);
		mPlayersIS.push_back(pisPlayer);
		mItems.push_back(&(mPlayersIS[i]->GetSelector()));
	}
	mItems.push_back(mbStart);
}

void NewGameMenu::Update()
{
	const int playersCount = (*(static_cast<MenuSelect*>(mItems[1]))).GetValue();
	for (int i = 0; i < mPlayersIS.size(); i++)
	{
		mPlayersIS[i]->Update();
		mPlayersIS[i]->GetSelector().Visible(i < playersCount);
	}

	for (int i = 0; i < mItems.size(); i++)
	{
		mItems[i]->Update();
	}
}

void NewGameMenu::Draw(sf::RenderWindow& window, sf::Transform t, uint8_t alpha)
{
	window.clear(sf::Color(0x27, 0x6B, 0x38));

	t.translate({ window.getSize().x * 0.1f, window.getSize().y * 0.2f });

	for (MenuItem* mi : mItems)
	{
		if (!mi->IsVisible())
			continue;

		auto s = mi->GetSize();
		mi->Draw(window, t, alpha);
		t.translate({ 0, s.y + 10 });
	}
}

void NewGameMenu::SetOnClickEventBack(Event e)
{
	MenuButton& newGame = *(static_cast<MenuButton*>(mItems[0]));
	newGame.SetOnClickEvent(e);
}
