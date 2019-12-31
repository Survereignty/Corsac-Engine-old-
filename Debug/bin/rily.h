#ifndef RILY_H
#define RILY_H

#include <SDL2/SDL.h>
#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>
#include <map>

class Rect;
class Tringle;

class Rily
{
	private:

		SDL_Renderer		 *render;				// Ссылка на рендер
		std::vector<Rect>	 RectObjects;   		// Динамический массив прямоугольников
		std::vector<Rect>	 RectVisibility;		// Динамический массив прямоугольников которые нужно отрисовывать
		std::vector<Tringle> TringObjects;	        // Динамический массив треугольников
		std::vector<Tringle> TringVisibility; 		// Динамический массив треугольников которые нужно отрисовывать

	public:
		
		class Rect 								   	// Класс параллелограмма
		{
			private:
				int size_x, size_y, number;
				std::string name; 
				void (*OM)();
				void (*UC)();
				void (*DC)();
				
				bool On    = false,
				     Up    = false, 
				     Down  = false;	

			    void Draw(SDL_Renderer *R);
				void MoveFinal(int x, int y, int speed_x, int speed_y);	

			public:
				int x, y;
				Uint8 r, g, b, a;

			    void OnMouse(void (*f)());
				void UpClick(void (*f)());
				void DownClick(void (*f)());
				void Move(int x, int y, int speed);
				Rect(std::string name, int size_x, int size_y, int x, int y);

				friend class Rily;
		}; 										   

		class Tringle							   	// Класс Треугольника	
		{
			private:
				int ax, ay, bx, by, cx, cy, center_x, center_y, number;
				std::string name; 
				void (*OM)();
				void (*UC)();
				void (*DC)();
				
				bool On   = false,
				     Up   = false, 
				     Down = false;	

				void Draw(SDL_Renderer *R);
				void MoveFinal(int x, int y, int speed_x, int speed_y);

			public:							
				Uint8 r, g, b, a;
			    
				void OnMouse(void (*f)());
				void UpClick(void (*f)());
				void DownClick(void (*f)());
				void Move(int x, int y, int speed);
				Tringle(std::string name, int ax, int ay, int bx, int by, int cx, int cy);
				friend class Rily;
		}; 

		Rily(SDL_Renderer *R);

		Tringle* CreateTringle(std::string name, int ax, int ay, int bx, int by, int cx, int cy);
		Rect*    CreateRect(std::string name,int size_x, int size_y, int x, int y);
		void Visibility(Rily::Tringle *R);
		void Visibility(Rily::Rect *R);
		void DrawingObjects();
		void ChekEvent();
};

#endif