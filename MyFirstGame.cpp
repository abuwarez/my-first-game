#include <string>
#include <iostream>
#include <vector>

#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#include <windows.h>
#include <wincon.h>
#include <ConsoleApi.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using Pixel = char;

namespace MyGame
{

       class PixelMatrix
       {
              int width, height;
              Pixel pixels[100][100];

       public:
              int GetWidth() const { return width; }
              int GetHeight() const { return height; }
              Pixel GetPixelAt(int x, int y) const { return pixels[x][y]; }

              void SetWidth(int w) { width = w; }
              void SetHeight(int h) { height = h; }
              void SetPixelAt(int x, int y, Pixel p) { pixels[x][y] = p; }
       };

       class Shape
       {
       public:
              virtual void FillPixels(PixelMatrix & output) const = 0;
              virtual std::string GetName() const = 0;

              virtual int GetWidth() const = 0;
              virtual int GetHeight() const = 0;
       };

       class Rectangle : public Shape
       {
              int lungime;
              int latime;

       public:
              Rectangle(int _lungime, int _latime) : lungime(_lungime), latime(_latime) {}

              virtual void FillPixels(PixelMatrix & output) const override
              {
                     output.SetWidth(lungime);
                     output.SetHeight(latime);
                     for (int i = 0; i < lungime; ++i)
                     {
                           for (int j = 0; j < latime; ++j)
                           {
                                  output.SetPixelAt(i, j, ' ');
                           }
                     }

                     //prima si ultima linie
                     for (int i = 0; i < lungime; ++i)
                     {
                           output.SetPixelAt(i, 0, 'x');
                           output.SetPixelAt(i, latime - 1, 'x');
                     }

                     for (int j = 1; j < latime - 1; ++j) // toate liniile mai putin prima si ultima
                     {
                           output.SetPixelAt(0, j, 'x');
                           output.SetPixelAt(lungime - 1, j, 'x');
                     }
              }

              virtual std::string GetName() const override
              {
                     return "rectangle";
              }

              virtual int GetWidth() const override { return lungime; }
              virtual int GetHeight() const override { return latime; }

       };

       class Screen
       {
              void MoveCursor(int line, int col)
              {
                     // CSI sequence for positioning cursor - https://en.wikipedia.org/wiki/ANSI_escape_code
                     std::cout << "\033[" << line << ";" << col << "H";
              }

       public:
              Screen()
              {
#if defined(_WIN32) || defined(_WIN64)
                     HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
                     DWORD dwMode;

                     GetConsoleMode(hOutput, &dwMode);

                     dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                     SetConsoleMode(hOutput, dwMode);
#endif
              }

              void Clear()
              {
                     // CSI sequence for clear screen - https://en.wikipedia.org/wiki/ANSI_escape_code
                     std::cout << "\033[2J\033[1;1H\033[?25l";
              }

	      ~Screen()
	      {
		     Clear();
                     //show cursor
		     std::cout << "\033[?25h";
	      }

              void Draw(const Shape& s, int x, int y)
              {
                     PixelMatrix pixels;

                     s.FillPixels(pixels);

                     MoveCursor(y + 1, x + 1); // +1 pentru ca randurile si coloanele terminalului incep de la 1

                     for (int i = 0; i < pixels.GetHeight(); ++i) //get height -> numarul de linii
                     {
                           MoveCursor(y + 1 + i, x + 1);

                           for (int j = 0; j < pixels.GetWidth(); ++j) //numarul de caractere pe linie
                           {
                                  // scriem o linie din matricea de pixeli
                                  std::cout << pixels.GetPixelAt(j, i);
                           }
                     }
              }
       };

       class PinocchioLeft: public Shape
       {
       public:
              virtual void FillPixels(PixelMatrix & output) const override
              {
                     output.SetPixelAt(0, 0, '-');
                     output.SetPixelAt(1, 0, 'O');
                     output.SetPixelAt(2, 0, ' ');
                     output.SetPixelAt(0, 1, '/');
                     output.SetPixelAt(1, 1, '|');
                     output.SetPixelAt(2, 1, '/');
                     output.SetPixelAt(0, 2, '/');
                     output.SetPixelAt(1, 2, ' ');
                     output.SetPixelAt(2, 2, '\\');

                     output.SetHeight(3);
                     output.SetWidth(3);
              }

              virtual std::string GetName() const override
              {
                     return "Pinocchio";
              }

              virtual int GetWidth() const override
              {
                     return 3;
              }

              virtual int GetHeight() const override
              {
                     return 3;
              }
       };

       class PinocchioRight : public Shape
       {
       public:
              virtual void FillPixels(PixelMatrix & output) const override
              {
                     output.SetPixelAt(0, 0, ' ');
                     output.SetPixelAt(1, 0, 'O');
                     output.SetPixelAt(2, 0, '-');
                     output.SetPixelAt(0, 1, '\\');
                     output.SetPixelAt(1, 1, '|');
                     output.SetPixelAt(2, 1, '\\');
                     output.SetPixelAt(0, 2, '/');
                     output.SetPixelAt(1, 2, ' ');
                     output.SetPixelAt(2, 2, '\\');

                     output.SetHeight(3);
                     output.SetWidth(3);
              }

              virtual std::string GetName() const override
              {
                     return "Pinocchio";
              }

              virtual int GetWidth() const override
              {
                     return 3;
              }

              virtual int GetHeight() const override
              {
                     return 3;
              }
       };

       class Personaj
       {
       public:
              enum Orientare
              {
                     SPRE_STANGA = 0,
                     SPRE_DREAPTA
              };

              Personaj() : mOrientare(SPRE_STANGA), mPosX(0), mPosY(0) {}
              
              const Shape& GetShape() const
              {
                     if (mOrientare == SPRE_STANGA) return mShapeLeft;
                     else return mShapeRight;
              }

              int GetX() const { return mPosX; }
              int GetY() const { return mPosY; }

              void SetX(int x) { mPosX = x; }
              void SetY(int y) { mPosY = y; }

              void SetOrientare(Orientare orientare) { mOrientare = orientare; }

       private:

              PinocchioLeft mShapeLeft;
              PinocchioRight mShapeRight;
              int mPosX, mPosY;
              Orientare mOrientare;
       };

       class InputListener
       {
       public:
              virtual void MoveUp() = 0;
              virtual void MoveDown() = 0;
              virtual void MoveLeft() = 0;
              virtual void MoveRight() = 0;

              virtual ~InputListener() {}
       };

       class SpatialShape
       {
       public:
              virtual Shape & GetShape() = 0;
              virtual const Shape & GetShape() const = 0;
              virtual int GetX() const = 0;
              virtual int GetY() const = 0;

              ~SpatialShape() {}
       };

       class Stone : public SpatialShape
       {
              Rectangle mShape;
              int mX, mY;

       public:
              Stone() : mShape(0, 0), mX(0), mY(0) {}
              Stone(int x, int y, int width, int height) : mShape(width, height), mX(x), mY(y) {}

              virtual Shape & GetShape() override { return mShape; }
              virtual const Shape & GetShape() const override { return mShape; };
              virtual int GetX() const override { return mX; }
              virtual int GetY() const override { return mY; }
       };

       class Mover :public InputListener
       {
              Personaj & mPersonaj;
              Rectangle & mArena;
              std::vector<Stone> & mStones;

              bool IsCollitizone(const Shape& s1, int x1, int y1, const Shape& s2, int x2, int y2)
              {
                     bool xOverlap = (x1 <= x2) && (x2 - x1 < s1.GetWidth()) || (x2 < x1) && (x1 - x2 < s2.GetWidth());
                     bool yOverlap = (y1 <= y2) && (y2 - y1 < s1.GetHeight()) || (y2 < y1) && (y1 - y2 < s2.GetHeight());

                     return xOverlap && yOverlap;
              }

              bool IsCollision(int newX, int newY)
              {
                     for (const Stone & s : mStones)
                           if (IsCollitizone(mPersonaj.GetShape(), newX, newY, s.GetShape(), s.GetX(), s.GetY()))
                                  return true;

                     return false;
              }


              public:
                     Mover(Personaj & personaj, Rectangle & arena, std::vector<Stone> & stones) : mPersonaj(personaj), mArena(arena), mStones(stones) {}

                     virtual void MoveUp() override 
                     {
                           int y = mPersonaj.GetY();
                           if (y > 0 && !IsCollision(mPersonaj.GetX(), mPersonaj.GetY() - 1))
                                  mPersonaj.SetY(y - 1);
                     }

                     virtual void MoveDown() override
                     {
                           int y = mPersonaj.GetY();
                           if (y + mPersonaj.GetShape().GetHeight() < mArena.GetHeight() && 
                                  !IsCollision(mPersonaj.GetX(), mPersonaj.GetY() + 1))
                                  mPersonaj.SetY(y + 1);
                     }

                     virtual void MoveLeft() override
                     {
                           int x = mPersonaj.GetX();
                           if (x > 0 && !IsCollision(mPersonaj.GetX() - 1, mPersonaj.GetY()))
                                  mPersonaj.SetX(x - 1);

                           mPersonaj.SetOrientare(Personaj::SPRE_STANGA);
                     }

                     virtual void MoveRight() override 
                     {
                           int x = mPersonaj.GetX();
                           if (x + mPersonaj.GetShape().GetWidth() < mArena.GetWidth() &&
                                  !IsCollision(mPersonaj.GetX() + 1, mPersonaj.GetY()))
                                  mPersonaj.SetX(x + 1);

                           mPersonaj.SetOrientare(Personaj::SPRE_DREAPTA);
                     }
       };

       class Settings
       {
       public:
              char upKey;
              char downKey;
              char leftKey;
              char rightKey;
              char layBombKey;
       };
}


//linux getch()
#if !defined(_WIN32) && !defined(_WIN64)
char _getch(){
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    //printf("%c\n",buf);
    return buf;
}

#endif

int main()
{
       const int maxX = 80;
       const int maxY = 30;

       MyGame::Screen s;

       MyGame::Personaj personaj;
       MyGame::Rectangle arena(maxX, maxY);
       
       std::vector<MyGame::Stone> mStones(5);

       mStones.push_back(MyGame::Stone(36, 13, 8, 4));
       mStones.push_back(MyGame::Stone(13, 4, 9, 5));
       mStones.push_back(MyGame::Stone(54, 6, 3, 3));
       mStones.push_back(MyGame::Stone(9, 20, 12, 8));
       mStones.push_back(MyGame::Stone(40, 19, 20, 2));

       personaj.SetX(70);
       personaj.SetY(25);

       MyGame::Mover mover(personaj, arena, mStones);

       while (1)
       {
              //rendering
              s.Clear();
              s.Draw(arena, 0, 0);
              for (const MyGame::Stone & stone : mStones)
                     s.Draw(stone.GetShape(), stone.GetX(), stone.GetY());

              s.Draw(personaj.GetShape(), personaj.GetX(), personaj.GetY());

              //input handling
	      char input = _getch();

              switch (input)
              {
              case 'w':
                    mover.MoveUp();
                     break;
              case 'a':
                     mover.MoveLeft();
                     break;
              case 's':
                     mover.MoveDown();
                     break;
              case 'd':
                     mover.MoveRight();
                     break;
	      case 'q':
		     s.Clear();
		     return 0;
              default:
                     break;
              }
       }
}

