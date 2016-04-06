//
//  tetris.h
//  
//
//  Created by Bing Yang on 9/27/15.
//
//
#include <iostream>
#include <assert.h>
#ifndef tetris_h
#define tetris_h

using namespace std;
class Tetris
{
public:
    Tetris(int a);
    void print() const;
    void add_piece(const char a, const int rotation, const int first_position);
    int get_width() const;
    int get_max_height() const ;
    int count_squares();
    int remove_full_rows();
    void add_left_column();
    void add_right_column();
    void remove_left_column();
    void remove_right_column();
    void destroy();
private:
    int width;
    int *heights;
    char **data;
};
#endif /* tetris_h */
