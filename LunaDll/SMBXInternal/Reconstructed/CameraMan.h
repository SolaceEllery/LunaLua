#ifndef CameraMan_hhh
#define CameraMan_hhh

#include "../Functions.h"
#include "../Types.h"
#include "../Variables.h"

struct CameraList
{
    int X = 0;
    int Y = 0;
    int Width = 0;
    int Height = 0;
    int XOffset = 0;
    int YOffset = 0;
    int TempX = 0;
    int TempY = 0;
    int TempDelay = 0;
    bool Visible = false;
};

class CameraMan {
    public:
        CameraMan();
        ~CameraMan();

        void SetupScreens();
        void GetVScreen(int16_t& playerIdx);
        void GetBoundaryScreen(int A, int X, int Y, int Width, int Height);
        void GetVScreenAverage();
        void DrawScreens();
};

extern CameraList gCameraManList[199];
extern CameraMan gCameraMan;

#endif