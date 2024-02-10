#include <iostream>
#include <conio.h>
#include <vector>

int g_iWidth;
int g_iHeight;
int g_iMapSize;
char** g_chMap;
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
    
	g_chMap = new char*[g_iWidth];
	for (int i = 0; i < g_iWidth; i++)
	{
		g_chMap[i] = new char[g_iHeight];
		memset(g_chMap[i], ' ', sizeof(char)* g_iHeight);
	}    

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

    //
	for (int i = 0; i < g_iWidth; i++)
		delete[] g_chMap[i];

    int iTemp = 0;
}

void FillWall()
{
    for (int i = 0; i < g_iWidth; i++)
    {
        for (int j = 0; j < g_iHeight; j++)
        {
            if (i == 0 || j == 0 || i == g_iWidth - 1 || j == g_iHeight - 1)
                PlaceObject(i, j, 'W');
        }
    }
}

void DrawMap()
{
	for (int i = 0; i < g_iHeight; i++)    
    {
		for (int j = 0; j < g_iWidth; j++)
        {
            std::cout << ' ' << g_chMap[j][i] << ' ';
        }

        std::cout << std::endl;
    }

}

bool PlaceObject(int iX, int iY, unsigned char ucObject)
{
	g_chMap[iX][iY] = ucObject;

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
        unsigned char ucTemp = g_chMap[iOriginPosX][iOriginPosY];
		
        iX = iTargetPosX;
        iY = iTargetPosY;

        if (g_chMap[iTargetPosX][iTargetPosY] == 'G' && g_chMap[iOriginPosX][iOriginPosY] == 'F')
        {
            g_bGameRun = false;
            return false;
        }

		g_chMap[iOriginPosX][iOriginPosY] = ' ';
		g_chMap[iTargetPosX][iTargetPosY] = ucTemp;

        return true;
    }
    else
    {
        return false;
    }
}

void CharactorMove(EMoveDirection eDirection)
{
    int iOriginPosX = g_pairPlayerPos.first;
    int iOriginPosY = g_pairPlayerPos.second;

    int iDirectionX = g_pairMove[(int)eDirection].first;
    int iDirectionY = g_pairMove[(int)eDirection].second;

    int iTargetPosX = iOriginPosX + iDirectionX;
    int iTargetPosY = iOriginPosY + iDirectionY;

    if ((g_pairPlayerPos.first + iDirectionX == g_pairFlagPos.first) && 
        (g_pairPlayerPos.second + iDirectionY == g_pairFlagPos.second) &&
		g_chMap[iTargetPosX][iTargetPosY] == 'F')
    {
        Move(g_pairFlagPos.first, g_pairFlagPos.second, eDirection);
    }

    Move(g_pairPlayerPos.first, g_pairPlayerPos.second, eDirection);
}