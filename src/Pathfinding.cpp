#include "../headers/Pathfinding.h"



bool PathAlgorithm::isValid(Vector2i pos, bool flying){
    return !(map(pos)->isSolid());
};



std::list<Vector2i> A_Star::findPath(Vector2i start, Vector2i target, bool flying){
    // saving map info
    int mapX=map.getDim().x;
    int mapY=map.getDim().y;

    //initialize closed list and node info structure
    bool closedList[mapX][mapY];
    memset(closedList,false,sizeof(closedList));
    node nodeInfo[mapX][mapY];
    for (int i = 0; i < mapX; i++)
    {
        for (int j = 0; j < mapY; j++)
        {
            nodeInfo[i][j].f=INT32_MAX;
            nodeInfo[i][j].g=INT32_MAX;
            nodeInfo[i][j].h=INT32_MAX;
            nodeInfo[i][j].parentPos={-1,-1};
        }
        
    }
    //initialize starting node
    nodeInfo[start.x][start.y].f=0;
    nodeInfo[start.x][start.y].g=0;
    nodeInfo[start.x][start.y].h=0;
    nodeInfo[start.x][start.y].parentPos={start.x,start.y};

    //initialize open list
    std::set<Pair> openList;
    openList.insert(std::make_pair(0,start));

    bool destFound=false;
    //starting exploration
    while(!openList.empty()){
        //getting and exploring next node
        Pair p=*openList.begin();
        openList.erase(openList.begin());
        int i=p.second.x;
        int j=p.second.y;
        closedList[i][j]=true;
        //init necessary value
        int gNew,hNew,fNew;
        //New node generation and exploration
        //---------TOP------------



    }

};