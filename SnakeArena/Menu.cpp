#include <typeinfo>

#include "Menu.hpp"
#include "MenuButton.hpp"
#include "MenuSelect.hpp"

Menu::Menu() :
	mActiveMenu (&mNewGameItems)
{

	mControls.DownEvent = [this]() { ChangeSelectedItem(false); };
	mControls.UpEvent = [this]() { ChangeSelectedItem(true); };
	mFont.loadFromFile(Font);
	
	MenuItem::Settings bs;
	bs.isVisible = true;
	bs.fontSize = 35;
	bs.selectedBackgroundColor = bs.backgroundColor = sf::Color(0x20, 0x20, 0x20);
	bs.selectedBoxOutlineColor = sf::Color::Cyan;
	bs.boxOutlineColor = sf::Color(0x60, 0x60, 0x60);
	bs.selectedBoxOutlineSize = bs.boxOutlineSize = 2;
	bs.textColor = sf::Color::White;
	bs.boxSize = { 250.f, 60.f };

	MenuButton * mbNewGame = new MenuButton("New game", mFont, bs);
	mbNewGame->Select();
	MenuButton * mbExit = new MenuButton("Exit", mFont, bs);
	mTopLevelButtons.push_back(mbNewGame);
	mTopLevelButtons.push_back(mbExit);

	bs.boxSize = { 450.f, 60.f };
	MenuButton* mbBack = new MenuButton("< Back", mFont, bs);
	mbBack->Select();
	mNewGameItems.push_back(mbBack);
	MenuButton* mbStart = new MenuButton("Start", mFont, bs);

	const size_t PlayersCount = 4;
	MenuSelect::Item iPlayers[PlayersCount];
	for (int i = 0; i < PlayersCount; i++)
	{
		iPlayers[i].text = std::to_string(i + 1);
		iPlayers[i].value = i + 1;
	}
	std::vector<MenuSelect::Item> viPlayers;
	viPlayers.assign(iPlayers, iPlayers + PlayersCount);
	MenuSelect * msPlayers = new MenuSelect("Players", mFont, bs, viPlayers, 1);

	mNewGameItems.push_back(msPlayers);

	for (int i = 0; i < PlayersCount; i++)
	{
		PlayerInputSelector * pisPlayer = new PlayerInputSelector(i + 1, bs, mFont);
		mPlayersIS.push_back(pisPlayer);
		mNewGameItems.push_back(&(mPlayersIS[i]->GetSelector()));
	}
	mNewGameItems.push_back(mbStart);
}

void Menu::ChangeSelectedItem(bool goUp)
{
	if (mActiveMenu == nullptr)
		return;

	vMenu& activeMenu = *mActiveMenu;
	if (activeMenu.size() == 1)
	{
		activeMenu[0]->Select();
		return;
	}

	MenuItem* last = activeMenu[0];

	size_t itemsCount = activeMenu.size();
	for (int i = 0; i < itemsCount; i++)
	{
		MenuItem& actual = *activeMenu[i];
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
				activeMenu[i + 1]->Select();
				return;
			}
		}
		last = &actual;
	}
}

void Menu::Update()
{
	for (int i = 0; i < mPlayersIS.size(); i++)
	{
		mPlayersIS[i]->Update();
	}
}

void Menu::Draw(sf::RenderWindow & window, sf::Transform t, uint8_t alpha)
{
	window.clear();
	//TODO background

	if (mActiveMenu == nullptr || mActiveMenu->size() == 0)
		return;

	//t.translate({ window.getSize().x * 0.1f, window.getSize().y * 0.6f });
	t.translate({ window.getSize().x * 0.1f, window.getSize().y * 0.2f });

	for (MenuItem* b : (*mActiveMenu))
	{
		auto s = b->GetSize();
		b->Draw(window, t, alpha);
		t.translate({ 0, s.y + 10 });
	}
}

void Menu::ProcessEvent(sf::Event e)
{
	mControls.ProcessEvent(e);
}