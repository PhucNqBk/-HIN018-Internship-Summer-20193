#include "Dungeon.h"
#include <cmath>
Dungeon::Dungeon()
{
	for (int i = 0; i < DUNGEON_HEIGHT; i++)
	{
		for (int j = 0; j < DUNGEON_WIDTH; j++)
		{
			m_Dungeon[i][j] = 0;
		}
	}
	CreateRooms();
	for (int i = 0; i < DUNGEON_HEIGHT; i++)
	{
		for (int j = 0; j < DUNGEON_WIDTH; j++)
		{
			if (m_Dungeon[i][j] > 0) {
		//		std::cout <<i << " "<<j<<". ";
			}
			
		}
	//	std::cout << std::endl;
	}
	for (int i = 0; i < TakenList.size(); i++)
	{
	//	std::cout <<TakenList[i].y + gridSizeY<<" "<<TakenList[i].x + gridSizeX<<" ";
	}
		
}
Dungeon::Dungeon(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture):
	m_pModel(model), m_pShader(shader), m_pTexture(texture)
{
	for (int i = 0; i < DUNGEON_HEIGHT; i++)
	{
		for (int j = 0; j < DUNGEON_WIDTH; j++)
		{
			m_Dungeon[i][j] = 0;
		}
	}
	CreateRooms();
	for (int i = 0; i < DUNGEON_HEIGHT; i++)
	{
		for (int j = 0; j < DUNGEON_WIDTH; j++)
		{
			
						std::cout << m_Dungeon[i][j] <<". ";

		}
			std::cout << std::endl;
	}
	for (int i = 0; i < TakenList.size(); i++)
	{
		Room room;
		room.m_RowCount = 2 * (MAP_MIN_HEIGHT + std::rand() % (MAP_MAX_HEIGHT - MAP_MIN_HEIGHT + 1));
		room.m_ColCount = 2 * (MAP_MIN_WIDTH + std::rand() %  (MAP_MAX_WIDTH - MAP_MIN_WIDTH + 1));
		int x = gridSizeX + (int)TakenList[i].x;
		int y = gridSizeY + (int)TakenList[i].y;
		room.m_DungCol = x; room.m_DungRow = y;
		if (x <= ROOM_WIDTH -2)
		{
			if (m_Dungeon[y][x + 1] == 1)
				room.Door_Right = true;
		}
		if (x - 1 >= 0)
		{
			if (m_Dungeon[y][x - 1] == 1)
				room.Door_Left = true;
		}
		if (y <= ROOM_HEIGHT -2)
		{
			if (m_Dungeon[y + 1][x] == 1)
				room.Door_Down = true;
		}
		if (y - 1 >= 0)
		{
			if (m_Dungeon[y - 1][x] == 1)
			room.Door_Up = true;
		}
		m_DungeonRooms.push_back(room);
		//std::cout << m_DungeonRooms.size() << std::endl;;
	}
	m_DungeonRooms[6].m_ColCount = 20;
	m_CurrentRoom = std::make_shared<TileLayer>(model, shader, texture, 10, 20);
	m_CurrentRoom->InitRoom(m_pModel, m_pShader, m_pTexture, m_DungeonRooms[1]);
	//m_CurrentRoom->InitRoom(model, shader, texture, m_DungeonRooms[0]);
	m_CurrentRoom->SetPosition(1280 / 2, 720 / 2);
	
	

}
Dungeon::~Dungeon()
{

}

void Dungeon::Init()
{
	m_DungeonRooms.clear();
	std::vector<Room>().swap(m_DungeonRooms);
	TakenList.clear();
	std::vector<Vector2>().swap(TakenList);
	for (int i = 0; i < DUNGEON_HEIGHT; i++)
	{
		for (int j = 0; j < DUNGEON_WIDTH; j++)
		{
			m_Dungeon[i][j] = 0;
		}
	}
	CreateRooms();
	for (int i = 0; i < DUNGEON_HEIGHT; i++)
	{
		for (int j = 0; j < DUNGEON_WIDTH; j++)
		{

			std::cout << m_Dungeon[i][j] << ". ";

		}
		std::cout << std::endl;
	}
	for (int i = 0; i < TakenList.size(); i++)
	{
		Room room;
		room.m_RowCount = 2 * (MAP_MIN_HEIGHT + std::rand() % (MAP_MAX_HEIGHT - MAP_MIN_HEIGHT + 1));
		room.m_ColCount = 2 * (MAP_MIN_WIDTH + std::rand() % (MAP_MAX_WIDTH - MAP_MIN_WIDTH + 1));
		int x = gridSizeX + (int)TakenList[i].x;
		int y = gridSizeY + (int)TakenList[i].y;
		room.m_DungCol = x; room.m_DungRow = y;
		if (x <= ROOM_WIDTH - 2)
		{
			if (m_Dungeon[y][x + 1] == 1)
				room.Door_Right = true;
		}
		if (x - 1 >= 0)
		{
			if (m_Dungeon[y][x - 1] == 1)
				room.Door_Left = true;
		}
		if (y <= ROOM_HEIGHT - 2)
		{
			if (m_Dungeon[y + 1][x] == 1)
				room.Door_Down = true;
		}
		if (y - 1 >= 0)
		{
			if (m_Dungeon[y - 1][x] == 1)
				room.Door_Up = true;
		}
		m_DungeonRooms.push_back(room);
		//std::cout << m_DungeonRooms.size() << std::endl;;
	}
	m_DungeonRooms[6].m_ColCount = 20;
	m_CurrentRoom->InitRoom(m_pModel, m_pShader, m_pTexture, m_DungeonRooms[1]);
	//m_CurrentRoom->InitRoom(model, shader, texture, m_DungeonRooms[0]);
	m_CurrentRoom->SetPosition(1280 / 2, 720 / 2);
}
void Dungeon::Draw()
{
	m_CurrentRoom->Draw();
}
void Dungeon::Update(GLfloat deltatime)
{
	//m_CurrentRoom->InitRoom(model, shader, texture, m_DungeonRooms[]);
}
void Dungeon::HandleKeyEvents(int key, bool bIsPressed)
{
	int row = m_CurrentRoom->GetDungRow();
	int col = m_CurrentRoom->GetDungCol();
	std::cout << row << " " << col << std::endl;
	int keyX = -1;
	if (bIsPressed) {
		switch (key)
		{
		case VK_UP:
			keyX = FindRoom(row - 1, col);
			if(keyX != -1)
				m_CurrentRoom->InitRoom(m_pModel, m_pShader, m_pTexture, m_DungeonRooms[keyX]);
			break;
		case VK_DOWN:
			keyX = FindRoom(row +1, col);
			if (keyX != -1)
				m_CurrentRoom->InitRoom(m_pModel, m_pShader, m_pTexture, m_DungeonRooms[keyX]);
			break;
		case VK_LEFT:
		    keyX = FindRoom(row, col -1);
			if (keyX != -1)
				m_CurrentRoom->InitRoom(m_pModel, m_pShader, m_pTexture, m_DungeonRooms[keyX]);
			break;
		case VK_RIGHT:
			keyX = FindRoom(row, col + 1);
			if (keyX != -1)
				m_CurrentRoom->InitRoom(m_pModel, m_pShader, m_pTexture, m_DungeonRooms[keyX]);
			break;
		case 'C':
			Init();
		default:
			break;
		}
	}
}
void Dungeon::SetRoomsPosition(float x, float y)
{
//	m_Position = Vector2(x, y);
	float x1, y1;
	for (int i = 0; i < TakenList.size(); ++i)
	{
		//x1 = (x - DUNGEON_WIDTH * ROOM_WIDTH / 2) + (2 * m_DungeonRooms[i]->GetDungCol() + 1) * ROOM_WIDTH / 2;
	//	y1 = (y - DUNGEON_WIDTH * ROOM_HEIGHT / 2) + (2 * m_DungeonRooms[i]->GetDungRow() + 1) * ROOM_HEIGHT / 2;
	//	m_DungeonRooms[i]->SetPosition(x1, y1);


	}
	
}
void Dungeon::CreateRooms()
{
	gridSizeX = DUNGEON_WIDTH/2;
	gridSizeY = DUNGEON_HEIGHT/2;
	m_Dungeon[gridSizeY][gridSizeX] = 1;
	TakenList.insert(TakenList.begin(),Vector2(0, 0));

	Vector2 checkPos = Vector2(gridSizeX, gridSizeY);

	float randomCompare = 0.2f, randomCompareStart = 0.2f, randomCompareEnd = 0.01f;

	for (int i = 0; i < ROOMS_NUMBER - 1; i++)
	{
		float randomPerc = ((float)i) / (((float)ROOMS_NUMBER-1));
		//lerp (a, b ,t ) = a + t * (b -a)
		randomCompare = randomCompareStart + randomPerc * (randomCompareEnd - randomCompareStart);

		checkPos = NewPosition();
		if (NumberOfNeighbor(checkPos) > 1 && ((float)rand() / (RAND_MAX)) > randomCompare )
		{
			int iterations = 0;
			do
			{
				checkPos = SelectNewPostion();
				iterations++;
			} while (NumberOfNeighbor(checkPos) > 1 && iterations < 100);
			if (iterations >= 50)
			{
				std::cout << "Cannot creat room with fewer neighbors than :  " << NumberOfNeighbor(checkPos) << std::endl;
			}
		}
		m_Dungeon[gridSizeY + (int)checkPos.y][gridSizeX + (int)checkPos.x] = 1;
		TakenList.insert(TakenList.begin(),checkPos);
	}
}
Vector2	Dungeon::NewPosition()
{
	int x = 0, y = 0;
	Vector2 checkingPos = Vector2(0, 0);
	do 
	{
		int index = (int)(((float)rand() / (RAND_MAX)) * (TakenList.size() - 1) + 0.5f);
		x = TakenList[index].x;
		y = TakenList[index].y;
		bool UpDown = (((float)rand() / (RAND_MAX)) < 0.5f);
		bool Positive = (((float)rand() / (RAND_MAX)) < 0.5f);
		if (UpDown)
		{
			if (Positive)
			{
				y += 1;
			}
			else
			{
				y -= 1;
			}

		}else
		{
			if (Positive)
			{
				x += 1;
			}
			else
			{
				x -= 1;
			}
		}
		checkingPos = Vector2(x, y);
	} while (IsContains(checkingPos) || x >= gridSizeX || x <= -gridSizeX || y >= gridSizeY || y <= -gridSizeY);
	return checkingPos;
}
int	Dungeon::NumberOfNeighbor(Vector2 Pos)
{
	int ret = 0;
	if (IsContains(Vector2(Pos.x+1, Pos.y)))
	{
		ret ++;
	}
	if (IsContains(Vector2(Pos.x -1, Pos.y)))
	{
		ret++;
	}
	if (IsContains(Vector2(Pos.x, Pos.y +1)))
	{
		ret++;
	}
	if (IsContains(Vector2(Pos.x, Pos.y -1)))
	{
		ret++;
	}
	return ret;
}
Vector2	Dungeon::SelectNewPostion()
{
	int index = 0, inc = 0;
	int x = 0, y = 0;
	Vector2 checkingPos = Vector2(0, 0);
	do
	{
		inc = 0;
		do
		{
			index = (int)(((float)rand() / (RAND_MAX)) * (TakenList.size() - 1) + 0.5f);
			inc++;
		} while (NumberOfNeighbor(TakenList[index]) > 1 && inc < 100);
		x = (int)TakenList[index].x;
		y = (int)TakenList[index].y;
		bool UpDown = (((float)rand() / (RAND_MAX)) < 0.5f);
		bool Positive = (((float)rand() / (RAND_MAX)) < 0.5f);
		if (UpDown)
		{
			if (Positive)
			{
				y += 1;
			}
			else
			{
				y -= 1;
			}

		}
		else
		{
			if (Positive)
			{
				x += 1;
			}
			else
			{
				x -= 1;
			}
		}
		checkingPos = Vector2(x, y);
	} while (IsContains(checkingPos) || x >= gridSizeX || x <= -gridSizeX || y >= gridSizeY || y <= -gridSizeY);
	if (inc >= 100)
	{
		std::cout << "Error: Could not find pos with only one neigbor"<<std::endl;
	}
	return checkingPos;
}
bool Dungeon::IsContains(Vector2 pos)
{
	for (int i = 0; i < TakenList.size(); i++)
		if (TakenList[i].x == pos.x &&TakenList[i].y == pos.y)
			return true;
	return false;
}
int Dungeon::FindRoom(int d_row, int d_col)
{
	for (int i = 0; i < m_DungeonRooms.size(); ++i) {
		if (m_DungeonRooms[i].m_DungRow == d_row && m_DungeonRooms[i].m_DungCol == d_col)
			return i;
	}
	return -1;
}