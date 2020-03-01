#pragma once
#include "MenuItem.hpp"

class IMenuContainer
{
public:
	typedef std::vector<MenuItem*>	vMenu;

protected:
	vMenu mItems;

public:

	IMenuContainer()
	{
	}

	void ChangeSelectedItem(bool goUp)
	{
		if (mItems.size() == 0)
			return;

		if (mItems.size() == 1 && mItems[0]->IsVisible())
		{
			mItems[0]->Select();
			return;
		}

		MenuItem* last = nullptr;
		MenuItem* first = nullptr;

		size_t itemsCount = mItems.size();
		uint32_t i;
		bool isSelected = false;
		bool selectNext = false;
		for (i = 0; i < itemsCount; i++)
		{
			MenuItem& actual = *mItems[i];
			if (!actual.IsVisible())
				continue;

			if (selectNext)
			{
				actual.Select();
				return;
			}

			isSelected |= actual.IsSelected();
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
					selectNext = true;
				}
			}
			last = &actual;
			if (first == nullptr)
				first = &actual;
		}

		if (i == itemsCount && !isSelected)
		{
			if (goUp && last != nullptr)
				last->Select();
			else if (first != nullptr)
				first->Select();
		}
	}

	void Click()
	{
		for (int i = 0; i < mItems.size(); i++)
		{
			if (mItems[i]->IsSelected())
			{
				mItems[i]->Click();
				return;
			}
		}
	}

	void Swap(bool Right)
	{
		for (int i = 0; i < mItems.size(); i++)
		{
			if (mItems[i]->IsSelected())
			{
				mItems[i]->Swap(Right);
				return;
			}
		}
	}

	virtual void Init(MenuItem::Settings ItemsSettings, sf::Font& font) = 0;
	virtual void Update() = 0;
	virtual void Draw(sf::RenderWindow& window, sf::Transform t = sf::Transform::Transform::Identity, uint8_t alpha = 255) = 0;

};

