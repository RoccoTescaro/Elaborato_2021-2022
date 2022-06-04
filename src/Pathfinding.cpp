#include "../headers/Pathfinding.h"

#include "../headers/Map.h"

//todo tracePath


bool PathAlgorithm::isValid(Vector2i pos, bool flying){
    std::cout<<" isValid "<<std::endl;
    std::cout<<" exit::"<<!(map.isOccupied(pos,Map::entityLayer::gameCharacterLayer,flying))<<std::endl;
    return !(map.isOccupied(pos,Map::entityLayer::gameCharacterLayer,flying));
        
};

bool PathAlgorithm::isDestination(Vector2i pos,Vector2i target){
    std::cout<<"      isDestination "<<std::endl;
    std::cout<<"    exit::"<<(pos==target)<<std::endl;
    return (pos==target);
}

int PathAlgorithm::calculateDistance(Vector2i pos, Vector2i target){
    std::cout<<"          calculateHValue "<<std::endl;
    std::cout<<"         exit::"<<(abs(pos.x-target.x)+abs(pos.y-target.y))<<std::endl;
return (abs(pos.x-target.x)+abs(pos.y-target.y));
}


/////////////////////////A_STAR///////////////////////////////7

std::list<Vector2i> A_Star::tracePath(std::vector<std::vector<node>> nodeInfo,Vector2i target){
    std::cout<<"STARTING TRACEPATH ALGORITHM"<<std::endl;
    //declaring starting point
    int row = target.x;
    int col = target.y;
    std::cout<<" i,j:"<<row<<"-"<<col<<std::endl;
    //temporary data holder
    std::stack<Vector2i> Path;
    //building path
    while (!(nodeInfo[row][col].parentPos.x == row
             && nodeInfo[row][col].parentPos.y == col)) {
        //insertion in path

        Path.push({row,col});
        std::cout<<" element inserted in path:"<<row<<"-"<<col<<std::endl;

        //getting new node
        int temp_row = nodeInfo[row][col].parentPos.x ;
        int temp_col = nodeInfo[row][col].parentPos.y ;
        row = temp_row;
        col = temp_col;
        std::cout<<"a"<<std::endl;
        std::cout<<" new node:"<<row<<"-"<<col<<std::endl;

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
    node n;
    n.f=INT32_MAX;
    n.g=INT32_MAX;
    n.h=INT32_MAX;
    n.parentPos={-1,-1};
    std::vector<std::vector<node>> nodeInfo(mapX,std::vector<node>(mapY, n));
    std::cout<<"a"<<std::endl;
    //initialize starting node
    nodeInfo[start.x][start.y].f=0;
    nodeInfo[start.x][start.y].g=0;
    nodeInfo[start.x][start.y].h=0;
    nodeInfo[start.x][start.y].parentPos={start.x,start.y};

    //initialize open list
    std::set<Pair,fCompare> openList;
    openList.insert(std::make_pair(0,start));
    int startH=calculateDistance(start,target);
    Pair minimumNode={startH,start};
    bool destFound=false;
    //starting exploration
    while(!openList.empty()){
        std::cout<<" OPEN LIST:"<<std::endl;
        std::cout<<"-size:"<<openList.size()<<std::endl;
        for(auto i:openList){
            std::cout<<"---node:\n"<<std::endl;
            std::cout<<"----f:"<<i.first<<std::endl;
            std::cout<<"----Pos:"<<i.second.x<<"-"<<i.second.y<<std::endl;
        }

        //getting and exploring next node
        Pair p=*openList.begin();
        std::cout<<" NEW NODE:"<<p.second.x<<"-"<<p.second.y<<std::endl;

        openList.erase(openList.begin());

        int i=p.second.x;
        int j=p.second.y;
        
        std::cout<<"i,j:"<<i<<"-"<<j<<std::endl;
        closedList[i][j]=true;
        //init necessary value
        int gNew,hNew,fNew;
        //New node generation and exploration
        std::vector<sf::Vector2i> possibleSteps={{i-1,j},{i+1,j},{i,j-1},{i,j+1}};

        for(auto k:possibleSteps){
            std::cout<<"-----left-----"<<std::endl;
            if(isValid(k,flying)){
                if(isDestination(k,target)){
                
                    nodeInfo[k.x][k.y].parentPos.x = i;
                    nodeInfo[k.x][k.y].parentPos.y = j;

                            std::cout<<" new node built:parentPos:"<<nodeInfo[k.x][k.y].parentPos.x<<"-"<<nodeInfo[k.x][k.y].parentPos.y<<std::endl;
                    
                    destFound = true; 
                        //costruisci e rendi la listadi passi
                    return tracePath(nodeInfo,target);
                }
                else if(closedList[k.x][k.y]==false){
                    //calcolo f
                    gNew = nodeInfo[k.x][k.y].g + 1.0;
                    hNew = calculateDistance(sf::Vector2i(k), target);
                    fNew = gNew + hNew;
                    if(fNew<minimumNode.first){
                        minimumNode.first=fNew;
                        minimumNode.second=k;
                    }
                    if(nodeInfo[k.x][k.y].f==INT32_MAX||
                    nodeInfo[k.x][k.y].f>fNew){
                        openList.insert(std::make_pair(fNew,sf::Vector2i(k)));
                        //update node info
                            nodeInfo[k.x][k.y].f = fNew;
                            nodeInfo[k.x][k.y].g = gNew;
                            nodeInfo[k.x][k.y].h = hNew;
                            nodeInfo[k.x][k.y].parentPos.x = i;
                            nodeInfo[k.x][k.y].parentPos.y = j;
                            std::cout<<" new node built:parentPos:"<<nodeInfo[k.x][k.y].parentPos.x<<"-"<<nodeInfo[k.x][k.y].parentPos.y<<std::endl;

                    }
                }
            }

        }



        std::cout<<"-size:"<<openList.size()<<std::endl;
    }
    if (destFound==false){
        
        return tracePath(nodeInfo,minimumNode.second);
    }

};
/////////////////////////DIGLETT_MOVEMENT///////////////////////////////7



bool DiglettMovement::isReachable(Vector2i start, Vector2i end, bool flying){
    return 0;
};
        
        



std::list<Vector2i> DiglettMovement::findPath(Vector2i start, Vector2i target, bool flying){


    int speed=2;
    int maxDistance=3;
    //initialize open list
    int distanceValue=-1;
    std::vector<sf::Vector2i> possibleTargets;
    for (int i = 0; i < 1+2*maxDistance; i++)
    {
        for (int j = 0; j < 1+2*maxDistance; j++)
        {
            sf::Vector2i pos={target.x-3+i,target.y-3+j};
            int newDistanceValue=calculateDistance(pos,target);
            if(isReachable(start,pos)&&newDistanceValue>=distanceValue){
                if(newDistanceValue>distanceValue)
                   possibleTargets.clear();
                possibleTargets.push_back(pos);
                }
        }
    }
    int r=rand()%possibleTargets.size();
    std::list<Vector2i> finalDestination={{possibleTargets.at(r).x,possibleTargets.at(r).y}};
    return finalDestination;
}




















