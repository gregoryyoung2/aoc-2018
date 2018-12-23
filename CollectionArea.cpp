#include "CollectionArea.hpp"

using std::vector;

CollectionArea::CollectionArea(std::istream & in, size_t row, size_t col) {
    
    area.resize(row, vector<Acre>(col));
    
    for (unsigned int r = 0; r < area.size(); r++) {
        for (unsigned int c = 0; c < area[r].size(); c++) {
            char temp;
            in.get(temp);
            area[r][c] = temp == '.' ? Open : temp == '|' ? Tree : temp == '#' ? Yard : throw temp;
            if (temp == Tree) treeCount++;
            if (temp == Yard) yardCount++;
        }
        in.get();
    }
    
}
    

void CollectionArea::simulateMinute() {
    
    vector<vector<Acre>> buffer(2, vector<Acre>(area[0].size()));
    bool bufferIndex = 0;
    
    const int adj[8][2] = {{0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0}, {-1,1}};
    
    for (unsigned int r = 0; r < area.size(); r++) {
        for (unsigned int c = 0; c < area[r].size(); c++) {
            buffer[bufferIndex][c] = area[r][c];
            unsigned int goalTile = 0;
            bool secondGoal = false;
            for (unsigned int i = 0; i < 8; i++) {
                if (c == area[r].size() - 1 and (i <= 1 or  i >= 7)) continue;
                if (r == area.size()    - 1 and (i <= 3 and i >= 1)) continue;
                if (c == 0                  and (i <= 5 and i >= 3)) continue;
                if (r == 0                  and (i >= 5           )) continue;
                
                
                const Acre current = i > 3 ? buffer[adj[i][0] == 0 ? bufferIndex : bufferIndex ^ 1][c + adj[i][1]] : area[r + adj[i][0]][c + adj[i][1]];
                
                if (area[r][c] == Open or area[r][c] == Tree) {
                    if (8 - i + goalTile < 3) break;
                    if (current == (area[r][c] == Tree ? Yard : Tree)) goalTile++;
                    if (goalTile >= 3) {
                        if (area[r][c] == Open) {
                            treeCount++;
                            area[r][c] = Tree;
                        }
                        else {
                            treeCount--;
                            yardCount++;
                            area[r][c] = Yard;
                        }
                        break;
                    }
                }
                else if (current == Tree) {
                    goalTile = true;
                    if (secondGoal) break;
                }
                else if (current == Yard) {
                    secondGoal = true;
                    if (goalTile) break;
                }
                
            }
            if (buffer[bufferIndex][c] == Yard and not (goalTile and secondGoal)) {
                area[r][c] = Open;
                yardCount--;
            }
        }
        bufferIndex = bufferIndex ^ 1;
    }
    
    minutesSimulated++;
    
}

std::ostream & operator<<(std::ostream & out, const CollectionArea & ca) {
    for (unsigned int r = 0; r < ca.area.size(); r++) {
        for (unsigned int c = 0; c < ca.area[r].size(); c++) {
            out << (char) ca.area[r][c];
        }
        out << '\n';
    }
    return out;
}

unsigned int CollectionArea::getResourceValue() const {
    return treeCount * yardCount;
}

unsigned int CollectionArea::getMinutesSimulated() const {
    return minutesSimulated;
}
