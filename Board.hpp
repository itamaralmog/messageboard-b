#ifndef BOARD
#define BOARD
#include <string>
#include "Direction.hpp"
#include <vector>
#include <limits>

namespace ariel
{
    typedef unsigned int uint; // typdef for uint 
    /**
     * Class Point perpouse is to store a point data like x and y cordinates.
    */
    class Point // helper class 
    {
        public:
        uint x,y; 
        Point() // default constructor 
        {
            this->x=0;
            this->y=0;
        }
        Point(uint x, uint y) // not default constructor 
        {
            this->x = x;
            this->y = y;
        }
        Point * max_of_board_edge(Point o) const;
        Point * min_of_board_edge(Point o) const;
    };
    class Board
    {
        public:
            // keep pointers to min  and max 
            Point * min;
            Point * max;
            std::vector<std::vector<char>> * matrix;
            bool there_is_board; 
            Board() 
            {
                this->there_is_board = false;
                this->matrix = new std::vector<std::vector<char>>();
            }
            ~Board() 
            { 
                delete this->min;
                delete this->max;
                delete this->matrix;
            } 
            std::string read(uint x,uint y,Direction direction,uint size);
            void post(uint x, uint y, Direction direction,std::string str);
            void show() const;
            uint add_line_in_board(bool start,uint count,uint size) const;
            uint add_places_in_line(uint line,bool start,uint size) const;
    };

}


#endif