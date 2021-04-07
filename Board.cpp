#include "Board.hpp"
#include "Direction.hpp"
#include <iostream>
#include <string>
#include <cmath>

using ariel::Direction;
using namespace std;

namespace ariel
{

    Point * Point::max_of_board_edge(Point o) const 
    {
        Point * p = new Point();
        p->x = max(this->x,o.x); 
        p->y = max(this->y,o.y); 
        return p;
    }

    Point * Point::min_of_board_edge(Point o) const
    {
        Point * p = new Point();
        p->x = min(this->x,o.x);
        p->y = min(this->y,o.y);
        return p;
    }

    bool point_in_the_board(Point other,Board * b)
    {
        if (b->max == NULL || b->min == NULL){return false;}
        return ( other.y <= b->max->y &&other.x <= b->max->x  &&other.y >= b->min->y  && other.x >= b->min->x);
    }    
    string Board::read(uint x,uint y,Direction direction,uint size)
    {        
        Point p = Point(x,y);
        string s;
        for (size_t i = 0; i < size; i++)
        {
            if(point_in_the_board(p,this)){
                s +=   this->matrix->at(p.x - this->min->x).at(p.y-this->min->y);
            }
            else{
                s += '_';
            }
            if(direction == Direction::Horizontal){
                p.y += 1;
            }
            else{
                p.x+=1;
            }
        }
        return s;
    }
    void Board::post(uint x, uint y, Direction direction,string str)
    {    
        Point p_start = Point(x,y);
        Point p_finish=Point(x + str.length()-1,y);
        if(direction == Direction::Horizontal){
            p_finish=Point(x,y+str.length()-1);
        }
        if(!there_is_board)
        {
            there_is_board = true;
            this->min = new Point(x,y);  
            this->max = new Point(x,y);
        }
        if(point_in_the_board(p_start,this) && point_in_the_board(p_finish,this))
        {   
            for(uint i = 0;i < str.length();i++)
            {
                this->matrix->at(p_start.x-this->min->x).at(p_start.y - this->min->y) = str.at(i); 
            
                if(!(direction==Direction::Horizontal)){
                    p_start.x += 1; 
                }
                if(!(direction==Direction::Vertical)){
                    p_start.y += 1; 
                }
            }
        }
        else
        {
            const bool END=false, START=true;
            Point * max = p_finish.max_of_board_edge(*(this->max)); 
            Point * min = Point(x,y).min_of_board_edge(*(this->min)); 
            uint add_to_line_start = (this->min->y == min->y)?0:this->min->y - min->y+1; 
            uint add_to_line_end = (max->y == this->max->y)? 0:max->y - this->max->y+1;
            for (size_t i = 0; i < this->matrix->size(); i++)
            {
                if(add_to_line_start>0){
                    add_places_in_line(i,START,add_to_line_start);
                }
                if(add_to_line_end>0){
                    add_places_in_line(i,END,add_to_line_end);
                }
            }
            uint new_num_of_lines = max->y - min->y + 1; 
            uint add_lines_to_start =0;
            if(!(this->min->x == min->x)){
                add_lines_to_start=this->min->x - min->x+1;}
            uint add_lines_to_end =0;
            if(!(max->x == this->max->x)){
                add_lines_to_end=max->x - this->max->x+1;}
            if(add_lines_to_start>0){
                add_line_in_board(START,add_lines_to_start,new_num_of_lines);
                } 
            if(add_lines_to_end>0){
                add_line_in_board(END,add_lines_to_end,new_num_of_lines);}
            if((add_lines_to_end + add_lines_to_start)==0 && this->matrix->empty()) {
                add_line_in_board(START,1,new_num_of_lines); 
            }
            delete this->max;  
            delete this->min;
            this->max = max;  
            this->min = min;
            this->post(x,y,direction,str); 
        }
    }

    uint Board::add_line_in_board(bool put_the_line,uint count,uint size) const
    {
        if (size == 0) {return 0;}
        vector<char> temp = vector<char>(size,'_');
        this->matrix->insert(put_the_line?this->matrix->begin():this->matrix->end(),count,temp); 
        return size;
    }

    uint Board::add_places_in_line(uint line,bool put_place_line,uint size) const
    {
        vector<vector<char>> * mat = this->matrix;
        std::vector<char>::iterator position=mat->at(line).begin();
        if(!put_place_line){
           position=mat->at(line).end(); 
        }
        mat->at(line).insert(position,size,'_');
        return size;
    } 
    void Board::show() const
    {
        uint line = this->min->x;
        for (size_t i = 0; i < this->matrix->size(); i++)
        {
            cout << line <<": "; 
            for (size_t j = 0; j < this->matrix->at(i).size(); j++)
            {
                cout << this->matrix->at(i).at(j); 
            }
            cout << endl;
            line++; 
        }
        cout << endl;
    }

}