/* Your code here! */
#include "cs225/PNG.h"
using cs225::PNG;
#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;
#include <vector>

using namespace std;

class SquareMaze {
    public:
        SquareMaze();
        bool canTravel(int x, int y, int dir) const;
        PNG * drawMaze() const;
        PNG * drawMazeWithSolution();
        void makeMaze(int width, int height);
        void setWall(int x, int y, int dir, bool exists);
        vector<int> solveMaze();
        void makeMazeCreative();
        PNG * drawMazeCreative();
    private:
        int width_;
        int height_;
        vector<bool> down;
        vector<bool> right;
        
};
