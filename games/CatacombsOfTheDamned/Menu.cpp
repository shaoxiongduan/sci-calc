#include "Defines.h"
#include "Platform.h"
#include "Menu.h"
#include "Font.h"
#include "Game.h"
#include "FixedMath.h"
#include "Draw.h"
#include "Generated/SpriteTypes.h"

void Menu::Init()
{
	selection = 0;
}

void Menu::Draw()
{
	Platform::FillScreen(COLOUR_BLACK);
	Font::PrintString(PSTR("CATACOMBS OF THE DAMNED"), 2, 18, COLOUR_WHITE);
	Font::PrintString(PSTR("by @jameshhoward"), 7, 32, COLOUR_WHITE);
	Font::PrintString(PSTR("Start"), 4, 24, COLOUR_WHITE);
	Font::PrintString(PSTR("Sound:"), 5, 24, COLOUR_WHITE);

	if (Platform::IsAudioEnabled())
	{
		Font::PrintString(PSTR("on"), 5, 52, COLOUR_WHITE);
	}
	else
	{
		Font::PrintString(PSTR("off"), 5, 52, COLOUR_WHITE);
	}
	
	Font::PrintString(PSTR(">"), 4 + selection, 16, COLOUR_WHITE);
	
	const uint16_t* torchSprite = Game::globalTickFrame & 4 ? torchSpriteData1 : torchSpriteData2;
	Renderer::DrawScaled(torchSprite, 0, 10, 9, 255);
	Renderer::DrawScaled(torchSprite, DISPLAY_WIDTH - 18, 10, 9, 255);
}

void Menu::Tick()
{
	static uint8_t lastInput = 0;
	
	// Spin the RNG to have a unique(ish) starting level
	Random();

	if ((Platform::GetInput() & INPUT_DOWN) && !(lastInput & INPUT_DOWN))
	{
		selection = !selection;
	}
	if ((Platform::GetInput() & INPUT_UP) && !(lastInput & INPUT_UP))
	{
		selection = !selection;
	}

	if ((Platform::GetInput() & (INPUT_A | INPUT_B)) && !(lastInput & (INPUT_A | INPUT_B)))
	{
		switch (selection)
		{
		case 0:			
			Game::StartGame();
			break;
		case 1:
			Platform::SetAudioEnabled(!Platform::IsAudioEnabled());
			break;
		}
	}

	lastInput = Platform::GetInput();
}

void Menu::ResetTimer()
{
	timer = 0;
}

void Menu::TickEnteringLevel()
{
	constexpr uint8_t showTime = 30;
	
	if(timer < showTime)
	{
		timer++;
	}
	
	if(timer == showTime && Platform::GetInput() == 0)
	{
		Game::StartLevel();
	}
}

void Menu::DrawEnteringLevel()
{
	Platform::FillScreen(COLOUR_BLACK);
	Font::PrintString(PSTR("Entering floor"), 3, 30, COLOUR_WHITE);
	Font::PrintInt(Game::floor, 3, 90, COLOUR_WHITE);
}	

void Menu::TickGameOver()
{
	constexpr uint8_t minShowTime = 30;
	
	if(timer < minShowTime)
	{
		timer++;
	}
	
	if(timer == minShowTime && (Platform::GetInput() & (INPUT_A | INPUT_B)))
	{
		timer++;
	}
	else if(timer == minShowTime + 1 && Platform::GetInput() == 0)
	{
		Game::SwitchState(Game::State::Menu);
	}
}

void Menu::DrawGameOver()
{
	Platform::FillScreen(COLOUR_BLACK);
	Font::PrintString(PSTR("GAME OVER"), 0, 64 - 18, COLOUR_WHITE);

	switch (Game::stats.killedBy)
	{
	case EnemyType::None:
		Font::PrintString(PSTR("You escaped the catacombs!"), 1, 12, COLOUR_WHITE);
		break;
	case EnemyType::Mage:
		Font::PrintString(PSTR("Killed by a mage on level"), 1, 8, COLOUR_WHITE);
		Font::PrintInt(Game::floor, 1, 112, COLOUR_WHITE);
		break;
	case EnemyType::Skeleton:
		Font::PrintString(PSTR("Killed by a knight on level"), 1, 4, COLOUR_WHITE);
		Font::PrintInt(Game::floor, 1, 116, COLOUR_WHITE);
		break;
	case EnemyType::Bat:
		Font::PrintString(PSTR("Killed by a bat on level"), 1, 10, COLOUR_WHITE);
		Font::PrintInt(Game::floor, 1, 110, COLOUR_WHITE);
		break;
	case EnemyType::Spider:
		Font::PrintString(PSTR("Killed by a spider on level"), 1, 4, COLOUR_WHITE);
		Font::PrintInt(Game::floor, 1, 116, COLOUR_WHITE);
		break;
	}
	
	Font::PrintString(PSTR("LOOT:"), 2, 20, COLOUR_WHITE);

	constexpr uint8_t firstRow = 21;
	constexpr uint8_t secondRow = 38;

	Renderer::DrawScaled(chestSpriteData, 0, firstRow, 9, 255);
	Font::PrintInt(Game::stats.chestsOpened, 4, 18, COLOUR_WHITE);

	Renderer::DrawScaled(crownSpriteData, 0, secondRow, 9, 255);
	Font::PrintInt(Game::stats.crownsCollected, 6, 18, COLOUR_WHITE);

	Renderer::DrawScaled(scrollSpriteData, 30, firstRow, 9, 255);
	Font::PrintInt(Game::stats.scrollsCollected, 4, 48, COLOUR_WHITE);

	Renderer::DrawScaled(coinsSpriteData, 30, secondRow, 9, 255);
	Font::PrintInt(Game::stats.coinsCollected, 6, 48, COLOUR_WHITE);

	///
	int offset = (Game::globalTickFrame & 8) == 0 ? 32 : 0;
	Font::PrintString(PSTR("KILLS:"), 2, 84, COLOUR_WHITE);

	Renderer::DrawScaled(skeletonSpriteData + offset, 66, firstRow, 9, 255);
	Font::PrintInt(Game::stats.enemyKills[(int)EnemyType::Skeleton], 4, 84, COLOUR_WHITE);

	Renderer::DrawScaled(mageSpriteData + offset, 66, secondRow, 9, 255);
	Font::PrintInt(Game::stats.enemyKills[(int)EnemyType::Mage], 6, 84, COLOUR_WHITE);

	Renderer::DrawScaled(batSpriteData + offset, 96, firstRow, 9, 255, true);
	Font::PrintInt(Game::stats.enemyKills[(int)EnemyType::Bat], 4, 114, COLOUR_WHITE);

	Renderer::DrawScaled(spiderSpriteData + offset, 96, secondRow, 9, 255);
	Font::PrintInt(Game::stats.enemyKills[(int)EnemyType::Spider], 6, 114, COLOUR_WHITE);

	// Calculate final score here
	uint16_t finalScore = 0;
	constexpr int finishBonus = 500;
	constexpr int levelBonus = 20;
	constexpr int chestBonus = 15;
	constexpr int crownBonus = 10;
	constexpr int scrollBonus = 8;
	constexpr int coinsBonus = 4;
	constexpr int skeletonKillBonus = 10;
	constexpr int mageKillBonus = 10;
	constexpr int batKillBonus = 5;
	constexpr int spiderKillBonus = 4;

	finalScore += (Game::floor - 1) * levelBonus;

	if (Game::stats.killedBy == EnemyType::None)
		finalScore += finishBonus;
	finalScore += Game::stats.chestsOpened * chestBonus;
	finalScore += Game::stats.crownsCollected * crownBonus;
	finalScore += Game::stats.scrollsCollected * scrollBonus;
	finalScore += Game::stats.coinsCollected * coinsBonus;
	finalScore += Game::stats.enemyKills[(int)EnemyType::Skeleton] * skeletonKillBonus;
	finalScore += Game::stats.enemyKills[(int)EnemyType::Mage] * mageKillBonus;
	finalScore += Game::stats.enemyKills[(int)EnemyType::Bat] * batKillBonus;
	finalScore += Game::stats.enemyKills[(int)EnemyType::Spider] * spiderKillBonus;

	Font::PrintString(PSTR("FINAL SCORE:"), 7, 20, COLOUR_WHITE);
	Font::PrintInt(finalScore, 7, 72, COLOUR_WHITE);
}

#include <stdio.h>

void Menu::FadeOut()
{
	constexpr uint16_t toggleMask = 0x1f6e;
	constexpr int fizzlesPerFrame = 255;
	constexpr uint16_t startValue = 1;

	if (fizzleFade == 0)
	{
		fizzleFade = startValue;
	}

	for (int n = 0; n < fizzlesPerFrame; n++)
	{
		bool lsb = (fizzleFade & 1) != 0;
		fizzleFade >>= 1;
		if (lsb)
		{
			fizzleFade ^= toggleMask;
		}

		uint8_t x = (uint8_t)(fizzleFade & 0x7f);
		uint8_t y = (uint8_t)(fizzleFade >> 7);
		Platform::PutPixel(x, y, COLOUR_BLACK);

		if (fizzleFade == startValue)
		{
			Game::SwitchState(Game::State::GameOver);
			return;
		}
	}

}
