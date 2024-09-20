
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "transformed_view.h"
#include "complex.h"

// Override base class with your custom functionality
class Window : public olc::PixelGameEngine
{
	TranformedView tv;
	olc::vf2d prev_mouse;

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
		tv.scale = 0.01;
		tv.zoom_sens = 0.0001;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame, draws random coloured pixels
		//std::vector<std::vector<int>> 
		Clear(olc::BLACK);

		if (GetMouse(0).bHeld) {
			tv.translate(GetMousePos() - prev_mouse);
		}
		if (GetKey(olc::UP).bPressed) {
			tv.zoom_in(GetMousePos());
		}
		if (GetKey(olc::DOWN).bPressed) {
			tv.zoom_out(GetMousePos());
		}
		prev_mouse = GetMousePos();

		for (int x = 0; x < ScreenWidth(); x +=1) {
			for (int y = 0; y < ScreenHeight(); y++) {
				int value = (x + y) / (float)(ScreenWidth() + ScreenHeight()) * 255;
				//Draw(x, y, olc::Pixel(x / (float)ScreenWidth() * 255, y / (float)ScreenHeight() * 255, 0));
				auto world_coords = tv.screen_to_world(olc::vf2d(x, y));
				//std::cout << world_coords.str() << '\n';
				Complex z(world_coords.x, world_coords.y);

				// Equation
				// y = (2*x + 5) / (5*x - 3)
				// x = (2*y + 5) / (5*y - 3)
				Complex res = (z * 2 + 5) / (z * 5 - 3);
				//std::cout << res.str() << '\n';

				auto screen_coords = tv.world_to_screen(olc::vf2d(res.real, res.imag));
				//std::cout << "s " << screen_coords.str() << '\n';

				//Draw(screen_x, screen_y, olc::Pixel(0, value, 0));
				Draw(x,y, olc::Pixel(screen_coords.x / (float)ScreenWidth() * 255, screen_coords.y / (float)ScreenHeight() * 255, 0));
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