#ifndef ISTRATEGY_H
#define ISTRATEGY_H

#include <string>
#include <vector>
class IStrategy {
    private:

    public:
        std::vector<std::string> getDataName(){
            return std::vector<std::string>();
        };
};
#endif  //ISTRATEGY_H