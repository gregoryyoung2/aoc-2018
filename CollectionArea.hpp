#ifndef CollectionArea_hpp
#define CollectionArea_hpp

#include <vector>
#include <iostream>

class CollectionArea {
public:
    
    CollectionArea(std::istream &, size_t = 50, size_t = 50);
    
    void simulateMinute();
    
    unsigned int getResourceValue() const;
    
    unsigned int getMinutesSimulated() const;
    
    friend std::ostream & operator<<(std::ostream &, const CollectionArea &);
    
    
private:
    
    enum Acre : char { Open = '.', Tree = '|', Yard = '#'};
    
    unsigned int treeCount = 0;
    unsigned int yardCount = 0;
    
    unsigned int minutesSimulated = 0;
    
    std::vector<std::vector<Acre>> area;
    
};

#endif /* CollectionArea_hpp */
