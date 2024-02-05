#include <iostream>
#include <vector>

int g_iWidth;
int g_iHeight;
int g_iMapSize;
unsigned char* g_ucMap;

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
bool PlaceObject(int iX, int iY, unsigned char ucObject);
bool Move(int iX, int iY, EMoveDirection eDirection);

int main()
{
    g_iWidth = 30;
    g_iHeight = 30;
    g_iMapSize = g_iWidth * g_iHeight;

    g_ucMap = new unsigned char[g_iMapSize];
    memset(g_ucMap, ' ', sizeof(unsigned char)* g_iMapSize);

    // Player Place
    bool bSuccess = PlaceObject(3, 1, 'P');
    if (bSuccess != true)
    {
        // message
        return 1;
    }

    FillWall();
    DrawMap();

    // Play Start


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
            std::cout << g_ucMap[i * g_iWidth + j];
        }

        std::cout << std::endl;
    }

}

bool PlaceObject(int iX, int iY, unsigned char ucObject)
{
    // Target Pos가 벽이 아닐 경우 ucObject를 iX, iY위치에 배치
    if (WallCheck(iX, iY) != true)
    {
        int iObjectPos = iY * g_iHeight + iX;
        g_ucMap[iObjectPos] = ucObject;
        return true;
    }        
    else
        return false;
}

bool WallCheck(int iX, int iY)
{
    // Target Pos가 벽일경우
    int iObjectPos = iY * g_iHeight + iX;

    if (iX == 0 || iY == 0 || iX == g_iWidth - 1 || iY == g_iHeight - 1)
    {
        return true;
    }
    else
        return false;
}

bool Move(int iX, int iY, EMoveDirection eDirection)
{
    auto pair = g_pairMove[(int)eDirection];

    int iOriginPosX = iX;
    int iOriginPosY = iY;

    int iDirectionX = pair.first;
    int iDirectionY = pair.second;


}