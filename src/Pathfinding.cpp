#include "../headers/Pathfinding.h"

#include "../headers/Map.h"

//todo tracePath


bool PathAlgorithm::isValid(Vector2i pos, bool flying){
    std::cout<<"\n isValid "<<std::endl;
    std::cout<<" i,j:"<<pos.x<<"-"<<pos.y<<std::endl;
    if(map(pos)!=nullptr){
        std::cout<<" exit::"<<!(map(pos)->isSolid())<<std::endl;
        return !(map(pos)->isSolid());
        }
    else{
        
        if(pos.x>=0&&pos.x<=map.getDim().x&&
           pos.y>=0&&pos.y<=map.getDim().y ){
           std::cout<<" exit::"<<true<<std::endl;
            return true;}
        else{
           std::cout<<" exit::"<<false<<std::endl;
            return false;}
        }
};

bool PathAlgorithm::isDestination(Vector2i pos,Vector2i target){
    std::cout<<"\n       isDestination "<<std::endl;
    std::cout<<"    i,j:"<<pos.x<<"-"<<pos.y<<std::endl;
    std::cout<<"    target:"<<target.x<<"-"<<target.y<<std::endl;
    std::cout<<"    exit::"<<(pos==target)<<std::endl;
    return (pos==target);
}

int PathAlgorithm::calculateHValue(Vector2i pos, Vector2i target){
    std::cout<<"\n           calculateHValue "<<std::endl;
    std::cout<<"         i,j:"<<pos.x<<"-"<<pos.y<<std::endl;
    std::cout<<"         target:"<<target.x<<"-"<<target.y<<std::endl;
    std::cout<<"         exit::"<<(abs(pos.x-target.x)+abs(pos.y-target.y))<<std::endl;
return (abs(pos.x-target.x)+abs(pos.y-target.y));
}

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


std::list<Vector2i> A_Star::findPath(Vector2i start, Vector2i target, bool flying,sf::RenderWindow &window){
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
    std::set<Pair,Compare> openList;
    openList.insert(std::make_pair(0,start));

    bool destFound=false;
    //starting exploration
    while(!openList.empty()){
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
        //---------TOP------------
        std::cout<<"-----TOP-----"<<std::endl;
        if(isValid({i-1,j},flying)){
            if(isDestination({i-1,j},target)){
               
                nodeInfo[i - 1][j].parentPos.x = i;
                nodeInfo[i - 1][j].parentPos.y = j;

                        std::cout<<" new node built:parentPos:"<<nodeInfo[i - 1][j].parentPos.x<<"-"<<nodeInfo[i - 1][j].parentPos.y<<std::endl;
                printf("The destination cell is found: TOP\n");
                destFound = true; 
                    //costruisci e rendi la listadi passi
                return tracePath(nodeInfo,target);
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
                        std::cout<<" new node built:parentPos:"<<nodeInfo[i - 1][j].parentPos.x<<"-"<<nodeInfo[i - 1][j].parentPos.y<<std::endl;

                   }
            }
        }
        //---------BOTTOM------------
        std::cout<<"-----BOTTOM-----"<<std::endl;
        if(isValid({i+1,j},flying)){
            if(isDestination({i+1,j},target)){
               
                nodeInfo[i + 1][j].parentPos.x = i;
                nodeInfo[i + 1][j].parentPos.y = j;

                        std::cout<<" new node built:parentPos:"<<nodeInfo[i - 1][j].parentPos.x<<"-"<<nodeInfo[i - 1][j].parentPos.y<<std::endl;
                printf("The destination cell is found: BOTTOM\n");
                destFound = true; 
                    //costruisci e rendi la listadi passi
                return tracePath(nodeInfo,target);
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
                        std::cout<<" new node built:parentPos:"<<nodeInfo[i - 1][j].parentPos.x<<"-"<<nodeInfo[i - 1][j].parentPos.y<<std::endl;
                   }
            }
        }
        //---------LEFT------------
        std::cout<<"-----LEFT-----"<<std::endl;
        if(isValid({i,j-1},flying)){
            if(isDestination({i,j-1},target)){
               
                nodeInfo[i][j-1].parentPos.x = i;
                nodeInfo[i][j-1].parentPos.y = j;

                        std::cout<<" new node built:parentPos:"<<nodeInfo[i - 1][j].parentPos.x<<"-"<<nodeInfo[i - 1][j].parentPos.y<<std::endl;
                printf("The destination cell is found: LEFT\n");
                destFound = true; 
                    //costruisci e rendi la listadi passi
                return tracePath(nodeInfo,target);
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

                        std::cout<<" new node built:parentPos:"<<nodeInfo[i - 1][j].parentPos.x<<"-"<<nodeInfo[i - 1][j].parentPos.y<<std::endl;
                   }
            }
        }
        //---------RIGHT------------
        std::cout<<"-----RIGHT-----"<<std::endl;
        if(isValid({i,j+1},flying)){
            if(isDestination({i,j+1},target)){
               
                nodeInfo[i][j+1].parentPos.x = i;
                nodeInfo[i][j+1].parentPos.y = j;

                        std::cout<<" new node built:parentPos:"<<nodeInfo[i - 1][j].parentPos.x<<"-"<<nodeInfo[i - 1][j].parentPos.y<<std::endl;
                printf("The destination cell is found: RIGHT\n");
                destFound = true; 
                    //costruisci e rendi la listadi passi
                return tracePath(nodeInfo,target);
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
                        std::cout<<" new node built:parentPos:"<<nodeInfo[i - 1][j].parentPos.x<<"-"<<nodeInfo[i - 1][j].parentPos.y<<std::endl;
                   }
            }
        }
    }
    if (destFound==false){
        std::list<Vector2i> emptyList;
        return emptyList;
    }

};