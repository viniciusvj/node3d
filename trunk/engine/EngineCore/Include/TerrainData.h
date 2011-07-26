#pragma once
#include "InterfaceScene.h"

enum E_TERRAIN_ATT_TYPE
{
	TERRAIN_ATT_TYPE_SAFE	= 1<<0,
	TERRAIN_ATT_TYPE_BALK	= 1<<2,
	TERRAIN_ATT_TYPE_CLEAR	= 1<<3,
};

#define ATTRIBUTE_GRASS 0x8

#define ATTRIBUTE_SAFE		(0x01<<0)
#define ATTRIBUTE_BREAK		(0x01<<2)
#define ATTRIBUTE_UNVISIBLE	(0x01<<3)

// 地图文件数据
class CTerrainData:public iTerrainData
{
public:
	CTerrainData(); 
	~CTerrainData();
	//
	void				clear();
	void				create(size_t width, size_t height, size_t cubeSize);
	bool				resize(size_t width, size_t height, size_t cubeSize);
	//
	int					getWidth()const			{ return m_nWidth; }
	int					getHeight()const		{ return m_nHeight; }
	int					getChunkSize()const		{ return m_nChunkSize; }
	int					getVertexCount()const	{ return m_Cells.size(); }
	//
	bool				isCellIn(int x, int y)const;
	bool				isPointIn(int x, int y)const;
	//
	TerrainCell*		getCell(int x, int y);
	const TerrainCell*	getCell(int x, int y)const;
	//
	unsigned char		getCellTileID(int x, int nCellY, size_t layer = 0)const;
	void				setCellTileID(int x, int nCellY, unsigned char uTileID, size_t layer = 0);
	//
	unsigned long		getVertexIndex(int nCellX, int nCellY)const;
	int					getCellXByVertexIndex(unsigned long uVertexIndex)const;
	int					getCellYByVertexIndex(unsigned long uVertexIndex)const;
	//
	float				getVertexHeight(int x, int y)const;
	void				setVertexHeight(int x, int y, float fHeight);
	//
	Vec3D				getVertexNormal(int x, int y)const;
	//
	unsigned char		getCellAttribute(int x, int y)const;
	void				setCellAttribute(int x, int y, unsigned char uAtt);
	//
	Color32				getVertexColor(int x, int y)const;
	void				setVertexColor(int x, int y, Color32 color);
	//
	float				getHeight(float fX, float fY)const;
	Vec4D				getColor(float fX, float fY)const;
	// 碰撞精选
	virtual bool		pickCell(int nCellX, int nCellY, const Vec3D& vRayPos, const Vec3D& vRayDir, Vec3D* pPos = NULL)const;
	virtual bool		pick(const Vec3D& vRayPos, const Vec3D& vRayDir, Vec3D* pPos = NULL)const;
	//
	const std::string&	getFilename()const{return m_strFilename;}
	//
	void				getVertexByCell(int nCellX, int nCellY, TerrainVertex& vertex)const;
	void				getGrassVertexByCell(int nCellX, int nCellY, TerrainVertex*& vertex)const;

	bool				hasGrass(int nCellX, int nCellY)const;

	std::vector<TerrainCell>&		getCells()	{return m_Cells;}

	unsigned char		getPath(int sx,int sy,int tx,int ty, std::vector<unsigned char>& path);
	//////////////////启发式搜索(A*)寻路/////////////////////////////////
#define MAX_NODE 		100 //允许同时存在多少待扩展节点
#define MAX_ALLNODE 	1000 //允许节点数
	struct Node
	{
		int x,y,f,level,n;
	};
	//待扩展节点的资料
	Node node[MAX_NODE];
	//节点的资料
	struct AllNode
	{
		unsigned char dir;
		int father;
	}
	m_allnode[MAX_ALLNODE];

	int m_nNodeCount; //目前的待扩展节点数
	int m_nAllNodeCount; //目前的节点数
	void AddNode(int x,int y,int tx,int ty,unsigned char dir,int level,int father);
	Node GetNode();
	void Add2Hash(int x,int y);
	bool CheckHash(int x,int y);

	std::vector<bool> m_Searched;
protected:
	std::string					m_strFilename;
	int							m_nWidth;
	int							m_nHeight;
	int							m_nChunkSize;

	std::vector<TerrainCell>	m_Cells;
	std::vector<TerrainChunk>	m_Chunks;
	unsigned short				m_uMuFlgMap;
	unsigned long				m_uMuFlgAtt;
};