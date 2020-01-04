#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>
#include <map>
#include <future>
#include <thread>

class Rily;

class FigurePrivate
{
	public:
		std::string name;
		Uint8 const_r, const_g, const_b, const_a;

		bool 	OB = false,
				OD = false;

		std::function<void(void)> DC;
		std::function<void(void)> OM;
		std::function<void(void)> UC;

		void DefaultColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
};

class FigurePublic
{
	public:
		Uint8 r, g, b, a;

		void Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
};

class Rect: public FigurePublic, private FigurePrivate								// Класс параллелограмма
{
	private:
		int size_x, size_y, number;
		std::vector<std::function<void(void)>> SecondaryFunctions;
		void Draw(SDL_Renderer *R);
		void MoveFinal(int x, int y, int speed_x, int speed_y);


	public:
		int x, y;

		void Move(int x, int y, int speed);
		
		Rect(std::string name, int size_x, int size_y, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

		friend class Rily;
};

class Tringle: public FigurePublic, private FigurePrivate							// Класс Треугольника
{
	private:
		int ax, ay, bx, by, cx, cy, center_x, center_y, number;
		std::vector<std::function<void(void)>> SecondaryFunctions;
		
		void Draw(SDL_Renderer *R);
		void MoveFinal(int x, int y, int speed_x, int speed_y);

	public:

		void Move(int x, int y, int speed);
		Tringle(std::string name, int ax, int ay, int bx, int by, int cx, int cy, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
		
		friend class Rily;
};

class Rily
{
	private:
		SDL_Renderer		*render;				// Ссылка на рендер
		std::vector<Rect*>	RectObjects;			// Динамический массив прямоугольников
		std::vector<Rect*>	OnMouseRect;			// Динамический массив наведения на прямоугольник
		std::vector<Rect*>	UpClickRect; 			// Динамический массив начала нажатия на прямоугольник
		std::vector<Rect*>	DownClickRect;			// Динамический массив конца нажатия на прямоугольник
		std::vector<Rect*>	RectVisibility;			// Динамический массив прямоугольников которые нужно отрисовывать
		std::vector<Tringle*> TringObjects;			// Динамический массив треугольников
		std::vector<Tringle*> OnMouseTringle;		// Динамический массив наведения на треугольник
		std::vector<Tringle*> UpClickTringle;		// Динамический массив начала нажатия на треугольник
		std::vector<Tringle*> DownClickTringle;		// Динамический массив конца нажатия на треугольник
		std::vector<Tringle*> TringVisibility;		// Динамический массив треугольников которые нужно отрисовывать

		void AllDClick(SDL_Event e);
		void AllUpClick(SDL_Event e);
		void AllOnMouse(int x, int y);

	public:
		Rily(SDL_Renderer *R);

		Tringle* CreateTringle(std::string name, int ax, int ay, int bx, int by, int cx, int cy, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
		Rect*    CreateRect(std::string name, int x, int y, int size_x, int size_y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
		void Visibility(Tringle *R);
		void Visibility(Rect *R);
		void DrawingObjects();
		void ChekEvent(SDL_Event e);

		void OnMouse(Rect* R, std::function<void(void)> f);
		void UpClick(Rect* R, std::function<void(void)> f);
		void DownClick(Rect* R, std::function<void(void)> f);

		void OnMouse(Tringle* T, std::function<void(void)> f);
		void UpClick(Tringle* T, std::function<void(void)> f);
		void DownClick(Tringle* T, std::function<void(void)> f);
};