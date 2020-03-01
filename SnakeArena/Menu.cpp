#include <typeinfo>

#include "Menu.hpp"
#include "MenuButton.hpp"
#include "MenuSelect.hpp"

Menu::Menu() 
{

	mControls.DownEvent = [this]() { ChangeSelectedItem(false); };
	mControls.UpEvent = [this]() { ChangeSelectedItem(true); };
	mControls.SelectEvent = [this]() { if (mActiveMenu != nullptr) mActiveMenu->Click(); };
	mControls.LeftEvent = [this]() { if (mActiveMenu != nullptr) mActiveMenu->Swap(false); };
	mControls.RightEvent = [this]() { if (mActiveMenu != nullptr) mActiveMenu->Swap(true); };
	mFont.loadFromFile(Font);
	
	MenuItem::Settings bs;
	bs.isVisible = true;
	bs.fontSize = 28;
	bs.selectedBackgroundColor = bs.backgroundColor = sf::Color(0x20, 0x20, 0x20);
	bs.selectedBoxOutlineColor = sf::Color(0x8C, 0x23, 0x23);
	bs.boxOutlineColor = sf::Color(0x60, 0x60, 0x60);
	bs.selectedBoxOutlineSize = bs.boxOutlineSize = 2;
	bs.textColor = sf::Color::White;
	bs.boxSize = { 250.f, 60.f };

	mTopLevelMenu.Init(bs, mFont);
	mTopLevelMenu.SetOnClickEventNewGame([this]() { mActiveMenu = &mNewGameMenu; });

	bs.boxSize = { 450.f, 60.f };
	mNewGameMenu.Init(bs, mFont);
	mNewGameMenu.SetOnClickEventBack([this]() { mActiveMenu = &mTopLevelMenu; });

	mActiveMenu = &mTopLevelMenu;
}

void Menu::ChangeSelectedItem(bool goUp)
{
	if (mActiveMenu == nullptr)
		return;

	mActiveMenu->ChangeSelectedItem(goUp);
}

void Menu::Update()
{
	if (mActiveMenu == nullptr)
		return;

	mActiveMenu->Update();
}

void Menu::Draw(sf::RenderWindow & window, sf::Transform t, uint8_t alpha)
{
	if (mActiveMenu == nullptr)
		return;

	mActiveMenu->Draw(window, t, alpha);
}

void Menu::ProcessEvent(sf::Event e)
{
	mControls.ProcessEvent(e);
}