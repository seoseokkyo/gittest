#include <iostream>
#include <conio.h>
#include <vector>

int g_iWidth;
int g_iHeight;
int g_iMapSize;
unsigned char* g_ucMap;
std::pair<int, int> g_pairPlayerPos;
std::pair<int, int> g_pairFlagPos;
std::pair<int, int> g_pairGoalPos;
bool g_bGameRun = false;


enum class EMoveDirection
{
    eUp,
    eDown,
    eLeft,
    eRight,
    eMoveDirectionMax
};

std::vector<std::pair<int, int>> g_pairMove =
{
    {std::make_pair(0, -1) },
    {std::make_pair(0, 1) },
    {std::make_pair(-1, 0) },
    {std::make_pair(1, 0) }
};

void FillWall();
void DrawMap();
bool WallCheck(int iX, int iY);
bool PlaceObject(int iX, int iY, unsigned char ucObject);
bool Move(int& iX, int& iY, EMoveDirection eDirection);
void CharactorMove(EMoveDirection eDirection);

int main()
{
    g_iWidth = 30;
    g_iHeight = 30;
    g_iMapSize = g_iWidth * g_iHeight;

    g_ucMap = new unsigned char[g_iMapSize];
    memset(g_ucMap, ' ', sizeof(unsigned char)* g_iMapSize);

    // Player Place
    g_pairPlayerPos.first = 3;
    g_pairPlayerPos.second = 1;

    // Flag Place
    g_pairFlagPos.first = 10;
    g_pairFlagPos.second = 10;
    PlaceObject(g_pairFlagPos.first, g_pairFlagPos.second, 'F');

    // Goal Place
    g_pairGoalPos.first = 20;
    g_pairGoalPos.second = 20;
    PlaceObject(g_pairGoalPos.first, g_pairGoalPos.second, 'G');

    bool bSuccess = PlaceObject(g_pairPlayerPos.first, g_pairPlayerPos.second, 'P');
    if (bSuccess != true)
    {
        // message
        return 1;
    }

    FillWall();
    DrawMap();

    g_bGameRun = true;

    // Play Start
    while (g_bGameRun)
    {
        unsigned char cCommand = [] {    
            while (1)
            {
                if (_kbhit())
                    return _getch();
            }                
        }();
        
        if (cCommand == 'w' || cCommand == 'W')
        {
            CharactorMove(EMoveDirection::eUp);
        }
        else if (cCommand == 'a' || cCommand == 'A')
        {
            CharactorMove(EMoveDirection::eLeft);
        }
        else if (cCommand == 's' || cCommand == 'S')
        {
            CharactorMove(EMoveDirection::eDown);
        }
        else if (cCommand == 'd' || cCommand == 'D')
        {
            CharactorMove(EMoveDirection::eRight);
        }
    
        system("cls");
        DrawMap();
    }

    system("cls");
    std::cout << "GameEnd";

    delete[] g_ucMap;

    int iTemp = 0;
}

void FillWall()
{
    for (int i = 0; i < g_iWidth; i++)
    {
        for (int j = 0; j < g_iHeight; j++)
        {
            if (i == 0 || j == 0 || i == g_iHeight - 1 || j == g_iWidth - 1)
                PlaceObject(i, j, 'W');
        }
    }
}

void DrawMap()
{
    for (int i = 0; i < g_iWidth; i++)
    {
        for (int j = 0; j < g_iHeight; j++)
        {
            std::cout << ' ' << g_ucMap[i * g_iWidth + j] << ' ';
        }

        std::cout << std::endl;
    }

}

bool PlaceObject(int iX, int iY, unsigned char ucObject)
{
    int iObjectPos = iY * g_iHeight + iX;
    g_ucMap[iObjectPos] = ucObject;

    return true;
}

bool WallCheck(int iX, int iY)
{
    // Target Pos가 벽일경우
  if (iX == 0 || iY == 0 || iX == g_iWidth - 1 || iY == g_iHeight - 1)
    {
        return true;
    }
    else
        return false;
}

bool Move(int& iX, int& iY, EMoveDirection eDirection)
{
    auto pair = g_pairMove[(int)eDirection];

    int iOriginPosX = iX;
    int iOriginPosY = iY;

    int iDirectionX = pair.first;
    int iDirectionY = pair.second;

    int iTargetPosX = iOriginPosX + iDirectionX;
    int iTargetPosY = iOriginPosY + iDirectionY;

    if (WallCheck(iTargetPosX, iTargetPosY) != true)
    {
        int iObjectPos = iY * g_iHeight + iX;
        unsigned char ucTemp = g_ucMap[iObjectPos];
        g_ucMap[iObjectPos] = ' ';

        int iNewObjectPos = iTargetPosY * g_iHeight + iTargetPosX;
        iX = iTargetPosX;
        iY = iTargetPosY;

        if (g_ucMap[iNewObjectPos] == 'G' && ucTemp == 'F')
        {
            g_bGameRun = false;
            return false;
        }

        g_ucMap[iNewObjectPos] = ucTemp;

        return true;
    }
    else
    {
        return false;
    }
}

void CharactorMove(EMoveDirection eDirection)
{
    int iOriginPosX = g_pairFlagPos.first;
    int iOriginPosY = g_pairFlagPos.second;

    int iDirectionX = g_pairMove[(int)eDirection].first;
    int iDirectionY = g_pairMove[(int)eDirection].second;

    int iTargetPosX = iOriginPosX + iDirectionX;
    int iTargetPosY = iOriginPosY + iDirectionY;

    int iNewObjectPos = iOriginPosY * g_iHeight + iOriginPosX;

    if ((g_pairPlayerPos.first + iDirectionX == g_pairFlagPos.first) && 
        (g_pairPlayerPos.second + iDirectionY == g_pairFlagPos.second) &&
        g_ucMap[iNewObjectPos] == 'F')
    {
        Move(g_pairFlagPos.first, g_pairFlagPos.second, eDirection);
    }

    Move(g_pairPlayerPos.first, g_pairPlayerPos.second, eDirection);
}