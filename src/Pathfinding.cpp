#include "../headers/Pathfinding.h"


//todo tracePath


int PathAlgorithm::calculateHValue(Vector2i pos, Vector2i target){
return (abs(pos.x-target.x)+abs(pos.y-target.y));
}

bool PathAlgorithm::isValid(Vector2i pos, bool flying){
    return !(map(pos)->isSolid());
};

bool PathAlgorithm::isDestination(Vector2i pos,Vector2i target){
    return (pos==target);
}

std::list<Vector2i> A_Star::tracePath(node *nodeInfo,int width,int height,Vector2i target){
    
    int row = target.x;
    int col = target.y;
 
    std::stack<Vector2i> Path;
 
    while (!(nodeInfo[row*width+col].parentPos.x == row
             && nodeInfo[row*width+col].parentPos.y == col)) {
        Path.push({row,col});
        int temp_row = nodeInfo[row*width+col].parentPos.x ;
        int temp_col = nodeInfo[row*width+col].parentPos.y ;
        row = temp_row;
        col = temp_col;
    }
 
    Path.push({row,col});
    std::list<Vector2i> finalPath;
    while (!Path.empty()) {
        Vector2i p = Path.top();
        Path.pop();
        finalPath.push_back(p);
    }
 
    return finalPath;
}


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
        if(isValid({i-1,j},flying)){
            if(isDestination({i-1,j},target)){
               
                nodeInfo[i - 1][j].parentPos.x = i;
                nodeInfo[i - 1][j].parentPos.y = j;
                printf("The destination cell is found\n");
                destFound = true; 
                    //costruisci e rendi la listadi passi
                return tracePath(&nodeInfo[0][0], mapX,mapY,target);
            }
            else if(closedList[i-1][j]==false){
                //calcolo f
                gNew = nodeInfo[i][j].g + 1.0;
                hNew = calculateHValue(sf::Vector2i({i-1,j}), target);
                fNew = gNew + hNew;
 
                if(nodeInfo[i-1][j].f==INT32_MAX||
                   nodeInfo[i-1][j].f>fNew){
                       openList.insert(std::make_pair(fNew,sf::Vector2i({i-1,j})));
                       //update node info
                        nodeInfo[i - 1][j].f = fNew;
                        nodeInfo[i - 1][j].g = gNew;
                        nodeInfo[i - 1][j].h = hNew;
                        nodeInfo[i - 1][j].parentPos.x = i;
                        nodeInfo[i - 1][j].parentPos.y = j;
                   }
            }
        }
        //---------BOTTOM------------
        if(isValid({i+1,j},flying)){
            if(isDestination({i+1,j},target)){
               
                nodeInfo[i + 1][j].parentPos.x = i;
                nodeInfo[i + 1][j].parentPos.y = j;
                printf("The destination cell is found\n");
                destFound = true; 
                    //costruisci e rendi la listadi passi
                return tracePath(&nodeInfo[0][0], mapX,mapY,target);
            }
            else if(closedList[i+1][j]==false){
                //calcolo f
                gNew = nodeInfo[i][j].g + 1.0;
                hNew = calculateHValue(sf::Vector2i({i+1,j}), target);
                fNew = gNew + hNew;
 
                if(nodeInfo[i+1][j].f==INT32_MAX||
                   nodeInfo[i+1][j].f>fNew){
                       openList.insert(std::make_pair(fNew,sf::Vector2i({i+1,j})));
                       //update node info
                        nodeInfo[i + 1][j].f = fNew;
                        nodeInfo[i + 1][j].g = gNew;
                        nodeInfo[i + 1][j].h = hNew;
                        nodeInfo[i + 1][j].parentPos.x = i;
                        nodeInfo[i + 1][j].parentPos.y = j;
                   }
            }
        }
        //---------LEFT------------
        if(isValid({i,j-1},flying)){
            if(isDestination({i,j-1},target)){
               
                nodeInfo[i][j-1].parentPos.x = i;
                nodeInfo[i][j-1].parentPos.y = j;
                printf("The destination cell is found\n");
                destFound = true; 
                    //costruisci e rendi la listadi passi
                return tracePath(&nodeInfo[0][0], mapX,mapY,target);
            }
            else if(closedList[i][j-1]==false){
                //calcolo f
                gNew = nodeInfo[i][j].g + 1.0;
                hNew = calculateHValue(sf::Vector2i({i,j-1}), target);
                fNew = gNew + hNew;
 
                if(nodeInfo[i][j-1].f==INT32_MAX||
                   nodeInfo[i][j-1].f>fNew){
                       openList.insert(std::make_pair(fNew,sf::Vector2i({i,j-1})));
                       //update node info
                        nodeInfo[i][j-1].f = fNew;
                        nodeInfo[i][j-1].g = gNew;
                        nodeInfo[i][j-1].h = hNew;
                        nodeInfo[i][j-1].parentPos.x = i;
                        nodeInfo[i][j-1].parentPos.y = j;
                   }
            }
        }
        //---------RIGHT------------
        if(isValid({i,j+1},flying)){
            if(isDestination({i,j+1},target)){
               
                nodeInfo[i][j+1].parentPos.x = i;
                nodeInfo[i][j+1].parentPos.y = j;
                printf("The destination cell is found\n");
                destFound = true; 
                    //costruisci e rendi la listadi passi
                return tracePath(&nodeInfo[0][0], mapX,mapY,target);
            }
            else if(closedList[i][j+1]==false){
                //calcolo f
                gNew = nodeInfo[i][j].g + 1.0;
                hNew = calculateHValue(sf::Vector2i({i,j+1}), target);
                fNew = gNew + hNew;
 
                if(nodeInfo[i][j+1].f==INT32_MAX||
                   nodeInfo[i][j+1].f>fNew){
                       openList.insert(std::make_pair(fNew,sf::Vector2i({i,j+1})));
                       //update node info
                        nodeInfo[i][j+1].f = fNew;
                        nodeInfo[i][j+1].g = gNew;
                        nodeInfo[i][j+1].h = hNew;
                        nodeInfo[i][j+1].parentPos.x = i;
                        nodeInfo[i][j+1].parentPos.y = j;
                   }
            }
        }
        if (destFound==false){
            std::list<Vector2i> emptyList;
            return emptyList;
        }

    }

};