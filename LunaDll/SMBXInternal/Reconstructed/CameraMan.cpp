#include "CameraMan.h"

#include "../Functions.h"
#include "../Types.h"
#include "../Variables.h"

#include "../../Defines.h"
#include "../../Globals.h"

#include "../../Misc/VB6StrPtr.h"
#include "../../Misc/VB6Bool.h"
#include "../../Misc/VB6RNG.h"
#include "../../Misc/VB6Logic.h"

#include "../../Rendering/GL/GLContextManager.h"

CameraMan gCameraMan;
CameraList gCameraManList[199];

CameraMan::CameraMan()
{
    
}

CameraMan::~CameraMan()
{
    
}

void CameraMan::SetupScreens()
{
    
}

void CameraMan::GetBoundaryScreen(int A, int X, int Y, int Width, int Height)
{
    if(-gCameraManList[A].X < X)
    {
        gCameraManList[A].X = -X;
    }
    if(-gCameraManList[A].X + g_GLContextManager.GetMainFBWidth() > Width)
    {
        gCameraManList[A].X = -(Width - g_GLContextManager.GetMainFBWidth());
    }
    if(-gCameraManList[A].Y < Y)
    {
        gCameraManList[A].Y = -Y;
    }
    if(-gCameraManList[A].Y + g_GLContextManager.GetMainFBHeight() > Width)
    {
        gCameraManList[A].X = -(Width - g_GLContextManager.GetMainFBHeight());
    }
}

void CameraMan::GetVScreen(int16_t& playerIdx)
{
    using namespace SMBX13::Types;
    using namespace SMBX13::Vars;
    using namespace SMBX13::Functions;

    /*auto& p = Player[playerIdx];

    gCameraManList[playerIdx].X = -p.Location.X + (gCameraManList[playerIdx].Width * 0.5) - p.Location.Width / 2;
    gCameraManList[playerIdx].Y = -p.Location.Y + (gCameraManList[playerIdx].Height * 0.5) - gCameraManList[playerIdx].YOffset - p.Location.Height;
    gCameraManList[playerIdx].X = gCameraManList[playerIdx].X - gCameraManList[playerIdx].TempX;
    gCameraManList[playerIdx].Y = gCameraManList[playerIdx].Y - gCameraManList[playerIdx].TempY;
    gCameraMan.GetBoundaryScreen(playerIdx, level[p.Section].X, level[p.Section].Y, level[p.Section].Width, level[p.Section].Height);
    if(gCameraManList[playerIdx].TempDelay > 0)
    {
        gCameraManList[playerIdx].TempDelay = gCameraManList[playerIdx].TempDelay - 1;
    }
    else
    {
        if(gCameraManList[playerIdx].TempX > 0)
        {
            gCameraManList[playerIdx].TempX = gCameraManList[playerIdx].TempX - 1;
        }
        if(gCameraManList[playerIdx].TempX < 0)
        {
            gCameraManList[playerIdx].TempX = gCameraManList[playerIdx].TempX + 1;
        }
        if(gCameraManList[playerIdx].TempY > 0)
        {
            gCameraManList[playerIdx].TempY = gCameraManList[playerIdx].TempY - 1;
        }
        if(gCameraManList[playerIdx].TempY < 0)
        {
            gCameraManList[playerIdx].TempY = gCameraManList[playerIdx].TempY + 1;
        }
    }*/
}

void CameraMan::GetVScreenAverage()
{
    using namespace SMBX13::Functions;
    using namespace SMBX13::Types;
    using namespace SMBX13::Vars;
    /*int16_t A = 0;
    int16_t B = 0;
    auto& level = level;
    auto& p1 = Player[1];

    for(int i = 1; i <= GM_PLAYERS_COUNT; i++)
    {
        auto& p = Player[i];
        if VBAnd(!p.Dead, p.Effect != 6)
        {
            gCameraManList[0].X = gCameraManList[0].X - p.Location.Y - p.Location.Width / 2;
            if(p.Mount == 2)
            {
                gCameraManList[0].Y = gCameraManList[0].Y - p.Location.Y;
            }
            else
            {
                gCameraManList[0].Y = gCameraManList[0].Y - p.Location.Y - p.Location.Height;
            }
            B = B + 1;
        }
    }
    A = 1;
    if(B == 0)
    {
        
    }
    gCameraManList[0].X = (gCameraManList[0].X / B) + (g_GLContextManager.GetMainFBWidth() * 0.5)
    gCameraManList[0].Y = (gCameraManList[0].Y / B + (g_GLContextManager.GetMainFBHeight() * 0.5) - gCameraManList[0].YOffset)
    gCameraMan.GetBoundaryScreen(1, level[p1.Section].X, level[p1.Section].Y, level[p1.Section].Width, level[p1.Section].Height);*/
}

void CameraMan::DrawScreens()
{
    using namespace SMBX13::Functions;
    using namespace SMBX13::Types;
    using namespace SMBX13::Vars;

    
}
