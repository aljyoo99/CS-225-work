/* Your code here! */
#include <queue>
#include <map>
#include <utility>
#include <algorithm>
#include "maze.h"
#include "dsets.h"

/* Empty Constructor
 * */
SquareMaze::SquareMaze() {

}

/* This function checks if moving in the maze from (x, y) in the direction given by dir is possible. 
 * dir 0: right
 * dir 1: down
 * dir 2: left
 * dir 3: up
 */
bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return false;
    }

    if (dir == 0) {         // goto right
        return !right[x + y * width_];
    } else if (dir == 1) {  // goto down
        return !down[x + y * width_];
    } else if (dir == 2) {  // goto left
        if (x == 0) {
            return false;
        } else {
            return !right[x - 1 + y * width_];
        }
    } else if (dir == 3) {  // goto up
        if (y == 0) {
            return false;
        } else {
            return !down[x + (y - 1) * width_];
        }
    }
    return false;
}

/* This function draws the rectangular maze on a PNG image.
 *
 */
PNG * SquareMaze::drawMaze() const {
    int pwidth = width_ * 10 + 1;
    int pheight = height_ * 10 + 1;
    PNG * pic = new PNG(pwidth, pheight);

    for (int x = 10; x < pwidth; x++) {
        HSLAPixel & pixel = pic->getPixel(x, 0);
        pixel.h = 0;
        pixel.s = 0;
        pixel.l = 0;
        pixel.a = 1;
    }

    for (int y = 0; y < pheight; y++) {
        HSLAPixel & pixel = pic->getPixel(0, y);
        pixel.h = 0;
        pixel.s = 0;
        pixel.l = 0;
        pixel.a = 1;
    }
    for (int x = 0; x < width_; x++) {      // right walls
        for (int y = 0; y < height_; y++) {
            if (right[x + y * width_]) {
                for (int h = 0; h <= 10; h++) {
                    HSLAPixel & pixel = pic->getPixel((x + 1)*10, y*10 + h);
                    pixel.h = 0;
                    pixel.s = 0;
                    pixel.l = 0;
                    pixel.a = 1;
                }
            }
        }
    }
    
    for (int y = 0; y < height_; y++) {     // down walls
        for (int x = 0; x < width_; x++) {
            if (down[x + y * width_]) {
                for (int w = 0; w <= 10; w++) {
                    HSLAPixel & pixel = pic->getPixel(x*10 + w, (y + 1)*10);
                    pixel.h = 0;
                    pixel.s = 0;
                    pixel.l = 0;
                    pixel.a = 1;
                }
            }
        }
    }

    return pic;
}

/* This function draws the rectangular maze and its solution on a PNG image.
 *
 */
PNG * SquareMaze::drawMazeWithSolution() {
    PNG * pic = drawMaze();
    vector<int> dir = solveMaze();
    int curx = 5;
    int cury = 5;
    int newx = curx;
    int newy = cury;
 
    for (size_t i = 0; i < dir.size(); i++) {
        if (dir[i] == 0) {
            newx += 10;
            for (int x = curx; x <= newx; x++) {
                HSLAPixel & pixel = pic->getPixel(x, cury);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
        } else if (dir[i] == 1) {
            newy += 10;
            for (int y = cury; y <= newy; y++) {
                HSLAPixel & pixel = pic->getPixel(curx, y);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
        } else if (dir[i] == 2) {
            newx -= 10;
            for (int x = curx; x >= newx; x--) {
                HSLAPixel & pixel = pic->getPixel(x, cury);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
        } else if (dir[i] == 3) {
            newy -= 10;
            for (int y = cury; y >= newy; y--) {
                HSLAPixel & pixel = pic->getPixel(curx, y);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
        }
        curx = newx;
        cury = newy;
    }

    int x = curx / 10;
    int y = cury / 10;
    
    for (int w = 1; w <= 9; w++) {
        HSLAPixel & pixel = pic->getPixel(x*10 + w, (y + 1)*10);
        pixel.h = 0;
        pixel.s = 0;
        pixel.l = 1;
        pixel.a = 1;
    }
    return pic;
}

/* This function makes the maze by randomly erasing right and down walls at randomly chosen coordinates.
 *
 */
void SquareMaze::makeMaze(int width, int height) {
    width_ = width;
    height_ = height;
    int total = 0;
    DisjointSets dset;

    dset.addelements(width * height);
    down.assign(width * height, true);
    right.assign(width * height, true);
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);

    while (total < width * height - 1) {
        int randx = rand() % width;
        int randy = rand() % height;
        int breakdir = rand() % 2;
//cout<<total<<endl;
        if (breakdir) { // break down
            if (randy < height - 1 && dset.find(randx + randy * width) != dset.find(randx + (randy + 1) * width) && down[randx + randy * width]) {
                down[randx + randy * width] = false;
                dset.setunion((randx + randy * width), (randx + (randy + 1) * width));
                total++;
            }
        } else {        // break right
            if (randx < width - 1 && dset.find(randx + randy * width) != dset.find(randx + 1 + randy * width) && right[randx + randy * width]) {
                right[randx + randy * width] = false;
                dset.setunion((randx + randy * width), (randx + 1 + randy * width));
                total++;
            }
        }
    }
}

/* This function sets the right or down wall to exist or not exist at a given coordinate.
 * dir 0: right
 * dir 1: down
 */
void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return;
    }

    int index = x + y * width_;
    if (exists) {
        if (dir == 0) {         // right
            right[index] = true;
        } else if (dir == 1) {  // down
            down[index] = true;
        }
    } else {
        if (dir == 0) {         // right
            right[index] = false;
        } else if (dir == 1) {  // down
            down[index] = false;
        }
    }
}

/* This function solves the maze by using a map to store the valid paths through the maze. Then the longest path to the bottom row is selected. 
 *
 */
vector<int> SquareMaze::solveMaze() {
    vector<int> lastrow;
    queue<int> que;
    map<int, int> path;
    vector<bool> visited;
    int     v;  // current location
    int     x;
    int     y;

    visited.assign(height_ * width_, false);
    que.push(0);
    visited[0] = true;
    path.insert(pair<int, int>(0, 0));

    while (!que.empty()) {
        v = que.front();
        que.pop();
        x = v % width_;
        y = v / width_;
        if (y == height_ - 1) {
            lastrow.push_back(v);
        }
        if (canTravel(x, y, 0) && !visited[v + 1]) {
            visited[v + 1] = true;
            que.push(v + 1);
            path.insert(pair<int, int>(v + 1, v));
            //cout<< "(" << v + 1 << ", " << v << ")" << endl;
        }

        if (canTravel(x, y, 1) && !visited[v + width_]) {
            visited[v + width_] = true;
            que.push(v + width_);
            path.insert(pair<int, int>(v + width_, v));
            //cout<< "(" << v + width_ << ", " << v << ")" << endl;
        }

        if (canTravel(x, y, 2) && !visited[v - 1]) {
            visited[v - 1] = true;
            que.push(v - 1);
            path.insert(pair<int, int>(v - 1, v));
            //cout<< "(" << v - 1 << ", " << v << ")" << endl;
        }

        if (canTravel(x, y, 3) && !visited[v - width_]) {
            visited[v - width_] = true;
            que.push(v - width_);
            path.insert(pair<int, int>(v - width_, v));
            //cout<< "(" << v - width_ << ", " << v << ")" << endl;
        }
    }
    //cout<<endl << endl;

    //cout<<"last row"<<endl;
    //for (size_t i = 0; i < lastrow.size(); i++) {
    //    cout<<lastrow[i]<<" ";
    //}
    //cout<<endl<<endl;

    //cout<<"path"<<endl;
    //map<int, int>::iterator it;
    //for (it = path.begin(); it != path.end(); it++) {
    //    cout<<"("<<it->first<<","<<it->second<<") ";
    //}
    //cout<<endl;
    //for (size_t i = 0; i < visited.size(); i++) {
    //    cout<<visited[i]<<" ";
    //}
    //cout<<endl;

    vector<int> redpath;
    int         last;
    size_t      loop;
    int         max,
                cnt;

    // remove the shorter cell in the path
    //cout<< "before: " << lastrow.size() << endl;
    loop = 1;
    while (lastrow.size() > loop) {
        last = lastrow.size() - loop;
        v = lastrow[last];
        while (v != 0) {
            v = path[v];
            if (v >= width_ * (height_ - 1)) {
                for (size_t i = 0; i < lastrow.size(); i++) {
                    if (lastrow[i] == v) {
                        lastrow.erase(lastrow.begin() + i);
                        break;
                    }
                }
            }
        }
        loop++;
    }
    //cout<< "after: " << lastrow.size() << endl;

    // find longest path with smallest x value
    sort(lastrow.begin(), lastrow.end());
    max = -1;
    last = lastrow.size() - 1;
    for (size_t i = 0; i < lastrow.size(); i++) {
        v = lastrow[i];
        cnt = 0;
        while (v != 0) {
            cnt++;
            v = path[v];
        }
        if (max < cnt) {
            last = i;
            max = cnt;
        }
    }

    // generate final path
    v = lastrow[last];
    while (v != 0) {
        //cout<< " " << v;
        if (path[v] == v - 1)      redpath.push_back(0);
        if (path[v] == v - width_) redpath.push_back(1);
        if (path[v] == v + 1)      redpath.push_back(2);
        if (path[v] == v + width_) redpath.push_back(3);
        v = path[v]; 
    }
    //cout<<endl;
    reverse(redpath.begin(), redpath.end());
    return redpath;
}


// Part 3 creative component
/* This function creates a randomly generated maze with an I shape.
 */
void SquareMaze::makeMazeCreative() {
    width_ = 80;
    height_ = 120;
    int total = 0;
    DisjointSets dset;

    dset.addelements(width_ * height_);
    down.assign(width_ * height_, true);
    right.assign(width_ * height_, true);
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);


    while (total < 7199) {
        int randx = rand() % width_;
        int randy = rand() % height_;
        int breakdir = rand() % 2;
        if (breakdir) { // break down
            if (randy >= 29 && randy <= 89 && (randx <= 19 || randx >= 60)) {

            } else if (randy < height_ - 1 && dset.find(randx + randy * width_) != dset.find(randx + (randy + 1) * width_) && down[randx + randy * width_]) {
                down[randx + randy * width_] = false;
                dset.setunion((randx + randy * width_), (randx + (randy + 1) * width_));
                total++;
            }
        } else {        // break right
            if (randy >= 30 && randy <= 89 && (randx <= 19 || randx >= 59)) {

            } else if (randx < width_ - 1 && dset.find(randx + randy * width_) != dset.find(randx + 1 + randy * width_) && right[randx + randy * width_]) {
                right[randx + randy * width_] = false;
                dset.setunion((randx + randy * width_), (randx + 1 + randy * width_));
                total++;
            }
        }
    
    }
}

/* This function draws the creative maze with its solution which is the UIUC block I.
 *
 */
PNG * SquareMaze::drawMazeCreative() {
    makeMazeCreative();
    
    int bluex = 100;
    int bluey = 150;
    int oranx = 50;
    int orany = 75;
    int pwidth = width_ * 10 + 2 * bluex + 1;
    int pheight = height_  * 10 + 2 * bluey + 1;
    PNG * pic = new PNG(pwidth, pheight);

    for (int x = 0; x < pwidth; x++) {
        for (int y = 0; y < pheight; y++) {
            HSLAPixel & pixel = pic->getPixel(x, y);
            pixel.h = 11;
            pixel.s = .85;
            pixel.l = .60;
            pixel.a = 1;
        }
    }

    for (int x = oranx; x < pwidth - oranx; x++) {
        for (int y = oranx; y < pheight - orany; y++) {
            HSLAPixel & pixel = pic->getPixel(x, y);
            pixel.h = 216;
            pixel.s = .85;
            pixel.l = .25;
            pixel.a = 1;
        }
    }

    for (int x = bluex; x < pwidth - bluex; x++) {
        for (int y = bluey; y < pheight - bluey; y++) {
            HSLAPixel & pixel = pic->getPixel(x, y);
            pixel.h = 0;
            pixel.s = 0;
            pixel.l = 1;
            pixel.a = 1;
        }
    }

    for (int x = 10 + bluex; x < pwidth - bluex; x++) {
        HSLAPixel & pixel = pic->getPixel(x, bluey);
        pixel.h = 0;
        pixel.s = 0;
        pixel.l = 0;
        pixel.a = 1;
    }

    for (int y = 0 + bluey; y < pheight - bluey; y++) {
        HSLAPixel & pixel = pic->getPixel(bluex, y);
        pixel.h = 0;
        pixel.s = 0;
        pixel.l = 0;
        pixel.a = 1;
    }
    for (int x = 0; x < width_; x++) {      // right walls
        for (int y = 0; y < height_; y++) {
            if (right[x + y * width_]) {
                for (int h = 0; h <= 10; h++) {
                    HSLAPixel & pixel = pic->getPixel((x + 1)*10 + bluex, y*10 + h + bluey);
                    pixel.h = 0;
                    pixel.s = 0;
                    pixel.l = 0;
                    pixel.a = 1;
                }
            }
        }
    }
    
    for (int y = 0; y < height_; y++) {     // down walls
        for (int x = 0; x < width_; x++) {
            if (down[x + y * width_]) {
                for (int w = 0; w <= 10; w++) {
                    HSLAPixel & pixel = pic->getPixel(x*10 + w + bluex, (y + 1)*10 + bluey);
                    pixel.h = 0;
                    pixel.s = 0;
                    pixel.l = 0;
                    pixel.a = 1;
                }
            }
        }
    }

    for (int x = bluex; x <= bluex + 199; x++) {
        for (int y = bluey + 301; y <= bluey + 899; y++) {
            HSLAPixel & pixel = pic->getPixel(x, y);
            pixel.h = 216;
            pixel.s = .85;
            pixel.l = .25;
            pixel.a = 1;
        } 
    }

    for (int x = bluex + 601; x <= bluex + 800; x++) {
        for (int y = bluey + 301; y <= bluey + 899; y++) {
            HSLAPixel & pixel = pic->getPixel(x, y);
            pixel.h = 216;
            pixel.s = .85;
            pixel.l = .25;
            pixel.a = 1;
        }
    }
    vector<int> dir = solveMaze();
    int curx = 5;
    int cury = 5;
    int newx = curx;
    int newy = cury;
 
    for (size_t i = 0; i < dir.size(); i++) {
        if (dir[i] == 0) {
            newx += 10;
            for (int x = curx; x <= newx; x++) {
                HSLAPixel & pixel = pic->getPixel(x + bluex, cury + bluey);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
        } else if (dir[i] == 1) {
            newy += 10;
            for (int y = cury; y <= newy; y++) {
                HSLAPixel & pixel = pic->getPixel(curx + bluex, y + bluey);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
        } else if (dir[i] == 2) {
            newx -= 10;
            for (int x = curx; x >= newx; x--) {
                HSLAPixel & pixel = pic->getPixel(x + bluex, cury + bluey);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
        } else if (dir[i] == 3) {
            newy -= 10;
            for (int y = cury; y >= newy; y--) {
                HSLAPixel & pixel = pic->getPixel(curx + bluex, y + bluey);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = 0.5;
                pixel.a = 1;
            }
        }
        curx = newx;
        cury = newy;
    }

    int x = curx / 10;
    int y = cury / 10;
    
    for (int w = 1; w <= 9; w++) {
        HSLAPixel & pixel = pic->getPixel(x*10 + w + bluex, (y + 1)*10+ bluey);
        pixel.h = 0;
        pixel.s = 0;
        pixel.l = 1;
        pixel.a = 1;
    }
    return pic;
}
