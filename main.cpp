
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "transformed_view.h"
#include "complex.h"

// Override base class with your custom functionality
class Window : public olc::PixelGameEngine
{
	TranformedView tv;
public:
	Window()
	{
		// Name your application
		sAppName = "Window";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		tv.scale = 0.001;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame, draws random coloured pixels
		//std::vector<std::vector<int>>  
		for (int x = 0; x < ScreenWidth(); x += 20) {
			for (int y = 0; y < ScreenHeight(); y++) {
				int value = (x + y) / (float)(ScreenWidth() + ScreenHeight()) * 255;
				//Draw(x, y, olc::Pixel(x / (float)ScreenWidth() * 255, y / (float)ScreenHeight() * 255, 0));
				//auto world_coords = tv.screen_to_world(olc::vf2d(x, y));
				float world_x = x / (float)ScreenWidth() * 5 - 2.5;
				float world_y = y / (float)ScreenHeight() * 5 - 2.5;
				//std::cout << world_coords.str() << '\n';
				Complex z(world_x, world_y);

				// Equation
				// (2*z + 5) / (5*z - 3)
				Complex res = (z * 2 + 5) / (z * 5 + 3);
				//std::cout << res.str() << '\n';

				//auto screen_coords = tv.world_to_screen(olc::vf2d(res.real, res.imag));
				float screen_x = (res.real + 2.5) / 5 * ScreenWidth();
				float screen_y = (res.imag + 2.5) / 5 * ScreenHeight();

				//Draw(screen_x, screen_y, olc::Pixel(0, value, 0));
				Draw(screen_x, screen_y, olc::Pixel(x / (float)ScreenWidth() * 255, y / (float)ScreenHeight() * 255, 0));
			}
		}
		return true;
	}
};

int main()
{
	//Complex	a(2, 5);
	//Complex b(4, -1);
	//std::cout << (a / b).str();

	Window win;
	if (win.Construct(800, 800, 1, 1))
		win.Start();
	return 0;
}