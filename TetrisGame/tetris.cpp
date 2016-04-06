//
//  tetris.cpp
//  
//
//  Created by Bing Yang on 9/27/15.
//
//
#include <iostream>
#include <stdio.h>
#include "tetris.h"
#include <string>
#include <assert.h>

using namespace std;
//Initialization of the object,set the heights of the each column 0 and data pointer equal to NULL.
Tetris::Tetris(int a)
{
    width = a;
    heights = new int[width];
    for(int i = 0; i < width; i++)
    {
        heights[i]=0;
    }
    data = new char*[width];
    for(int i = 0; i < width; i++)
    {
        data[i] = NULL;
    }
}

//In add_piece function, we can add squares to the board. First, we should judge the shape. Second, we should
//judge the rotation to see if it is compliant. Third, we should judge the first position we want to add the squares
// and see if it will be out of the boards. If the input don't meet all of the requirements, it will show the error message,such as
//"The position is not suitable" and so on.
void Tetris::add_piece(const char a, const int rotation, const int first_position)
{
    //According the char a, execute different part of the function. What's more, we should also judge the first position is suitable or not(whether the board's width is enough)
    if(a == 'I')
    {
        // Determine different types of 'I' and there are only two situation about the roataion--(90 and 270) (0 and 180)
        if(rotation == 90 || rotation == 270)
        {
            //Judgement of the position
            if(first_position>=0 && (first_position+3)<width)
            {
                //if there are no elements on the bottom of the board, the add action can be easier.So I divide it into two situation.
                if(heights[first_position] != 0 || heights[first_position+1]!= 0||heights[first_position+2]!= 0||heights[first_position+3]!= 0)
                {
                    //After we added a 'I' with rotation of 90 or 270, four column would be affected and each column's height should be same.
                    //So we should determine what is the max height among these four column and  their heights after adding 'I' should be max height plus 1.
                    int max_length = 0;
                    for(int i = 0 ; i < 4 ; i++)
                    {
                        if(max_length < heights[first_position + i])
                        {
                            max_length = heights[first_position + i ];
                        }
                    }
                    max_length = max_length + 1;
                    
                    //create four new "columns" to store the data from old "column" and the data about the new 'I'.
                    char *new_column1 = new char[max_length];char *new_column2 = new char[max_length];
                    char *new_column3 = new char[max_length];char *new_column4 = new char[max_length];
                    
                    //According to the shape of squares we want to add, we can easily know what should be store at the end of each column.
                    new_column1[(max_length-1)]= 'I';new_column2[(max_length-1)]= 'I';new_column3[(max_length-1)]= 'I';new_column4[(max_length-1)]= 'I';
                    
                    //copy the old data to the new column and if old column is not high as the new column,
                    //we should set these null position with space character.
                    for(int i = 0; i< heights[first_position]; i++)
                    {
                        new_column1[i] = data[first_position][i];
                    }
                    for(int i = heights[first_position] ; i < max_length-1 ; i ++)
                    {
                        new_column1[i] =' ';
                    }
                    for(int i = 0; i< heights[first_position+1]; i++)
                    {
                        new_column2[i] = data[first_position+1][i];
                    }
                    for(int i = heights[first_position+1] ; i < max_length-1 ; i ++)
                    {
                        new_column2[i] =' ';
                    }
                    for(int i = 0; i< heights[first_position+2]; i++)
                    {
                        new_column3[i] = data[first_position+2][i];
                    }
                    for(int i = heights[first_position+2] ; i < max_length-1 ; i ++)
                    {
                        new_column3[i] =' ';
                    }
                    for(int i = 0; i< heights[first_position+3]; i++)
                    {
                        new_column4[i] = data[first_position+3][i];
                    }
                    for(int i = heights[first_position+3] ; i < max_length-1 ; i ++)
                    {
                        new_column4[i] =' ';
                    }
                    for(int i = 0 ; i < 4; i++)
                    {
                        heights[first_position+i] = max_length;
                    }
                    
                    // releasing heap space from the old data and make the data pointer point to the new column.
                    delete []data[first_position];delete []data[(first_position+1)];delete []data[(first_position+2)];delete []data[(first_position+3)];
                    data[first_position] = new_column1;
                    data[first_position+1] = new_column2;
                    data[first_position+2] = new_column3;
                    data[first_position+3] = new_column4;
                }
                else
                {
                    //If there are no elements on the bottom of the board,this add action can be easier.
                    char *new_column1 = new char[1];char *new_column2 = new char[1];char *new_column3 = new char[1];char *new_column4 = new char[1];
                    new_column1[0] = 'I';new_column2[0] = 'I';new_column3[0] = 'I';new_column4[0] = 'I';
                    delete []data[first_position];delete []data[(first_position+1)];delete []data[(first_position+2)];delete []data[(first_position+3)];
                    data[first_position] = new_column1;
                    data[first_position+1] = new_column2;
                    data[first_position+2] = new_column3;
                    data[first_position+3] = new_column4;
                    for(int i = 0; i<4;i ++)
                    {
                        heights[first_position+i] = 1;
                    }
                    
                }
            }
            else
            {
                //If the first position we want to add the squares is not suitable and we cannot add it correctly.
                //Then output the message like this.
                cout<<"The position is not suitable"<<endl;
            }
        }
        else if(rotation == 0|| rotation == 180)
        {
            //Another situation, when rotation is 0 and 180.
            if(first_position >=0 && first_position <width)
            {
                if(heights[first_position] != 0)
                {
                    //When we add a 'I' with rotation of 0 or 180, only one column would be affected. So we just need create a new pointer to store the new and old data
                    
                    //Copy the new data.
                    char *new_column = new char[((heights[first_position])+4)];
                    for(int i = 0; i< heights[first_position]; i++)
                    {
                        new_column[i] = data[first_position][i];
                    }
                    
                    //Add the new four elements about 'I' to the new column
                    for(int i = heights[first_position] ; i < (heights[first_position]+4) ; i ++)
                    {
                        new_column[i] ='I';
                    }
                    
                    //Reset the heights about this column and the data.
                    heights[first_position] = heights[first_position]+4;
                    delete[] data[first_position];
                    data[first_position] = new_column;
                }
                else
                {
                    //When there are no elements on the bottom of the board, create a new pointer to store the new data
                    char *new_column = new char[4];
                    for(int i = 0 ; i < 4 ; i ++)
                    {
                        new_column[i] ='I';
                    }
                    delete[] data[first_position];
                    data[first_position] = new_column;
                    heights[first_position] = 4;
                }
            }
            else
            {
                cout<<"The position is not suitable"<<endl;
            }
        }
        
        //If the rotation do not meet the requirement,show the following message.
        else
        {
            cout<<"input the wrong rotation."<<endl;
        }
    }
    
    //Add the 'O' to the board.
    else if(a == 'O')
    {
        //When we want to add 'O' to the board, there is only one shape of the 'O', so we don't need to consider the value of the rotation.
        if(first_position >= 0 && (first_position+1) <width)
        {
            //Fisrt, we should also find out whether the position exist some other elements.
            if(heights[first_position] != 0 || heights[(first_position+1)] != 0)
            {
                //When we add 'O' to the board, it would affect two columns, and each column would have the same height at the end.
                //So we have to find out the max height between these two hights.
                //After adding the 'O', the max height would become max height plus 2.
                int max_length = 0;
                if(heights[first_position] < heights[(first_position+1)])
                {
                    max_length = heights[(first_position+1)];
                }
                else
                {
                    max_length = heights[first_position];
                }
                max_length = max_length + 2;
                //create 2 new pointer to store the new and old data
                char *new_column1 = new char[max_length];
                char *new_column2 = new char[max_length];
                new_column1[(max_length-1)]= 'O';new_column1[(max_length-2)]='O';
                new_column2[(max_length-1)]= 'O';new_column2[(max_length-2)]='O';
                
                //Copy the old data to the new column.
                for(int i = 0; i< heights[first_position]; i++)
                {
                    new_column1[i] = data[first_position][i];
                }
                
                //If two columns do not have the same height, it would produce some "air", so we need to replace the "air" with space character.
                for(int i = heights[first_position] ; i < max_length-2 ; i ++)
                {
                    new_column1[i] =' ';
                }
                for(int i = 0; i< heights[first_position+1]; i++)
                {
                    new_column2[i] = data[first_position+1][i];
                }
                for(int i = heights[(first_position+1)] ; i < max_length-2 ; i ++)
                {
                    new_column2[i] =' ';
                }
                //reset the heights and the data. Of course, releasing the old heap memory.
                heights[first_position] = max_length;
                heights[(first_position+1)] = max_length;
                delete []data[first_position];
                delete []data[(first_position+1)];
                data[first_position] = new_column1;
                data[(first_position+1)] = new_column2;
            }
            else
            {
                //When there is no elements on the bottom of the board.
                //create 2 new pointer to store the new data
                char *new_column1 = new char[2];
                char *new_column2 = new char[2];
                new_column1[1]= 'O';new_column1[0]='O';
                new_column2[1]= 'O';new_column2[0]='O';
                heights[first_position] = 2;
                heights[(first_position+1)] = 2;
                delete []data[first_position];
                delete []data[(first_position+1)];
                data[first_position] = new_column1;
                data[(first_position+1)] = new_column2;
            }
            
        }
        else
        {
            cout<<"the position is not sutiable."<<endl;
        }
            
    }
    
    //Add 'T' to the board.
    else if(a == 'T')
    {
        //When we add 'T' to the board, there are four shapes of the 'T' and can be expressed by different rotation--0,90,180,270.
        //First situation, rotation = 0;
        if(rotation == 0)
        {
            //At the first, we should also judge the position we want to add the 'T'. When the rotation is 0, adding 'T' would affect 3 columns.
            if(first_position >= 0 && (first_position+2) < width)
            {
                //There are also two situation: there are no element on the bottom and there are elements on the bottom.
                //So I also divide it into two situation.
                if(heights[first_position] != 0 || heights[first_position+1] != 0 || heights[first_position+2] != 0)
                {
                    //If there are bottom in the board, we still can divide it into two situation. As we said before, adding 'T' would affect 3 columns.
                    // If the second column has the max height, then the new max height should be (max height + 2) or the new max height should be (max height + 1)
                    
                    //First situation, second column do not have the max height.
                    if(heights[first_position+1]<heights[first_position]||heights[first_position+1]<heights[first_position+2])
                    {
                            //At the begining, we should find out the max height between the first column and the third column and set the new max height.
                            int max_length = 0;
                            if(heights[first_position]<heights[first_position + 2])
                            {
                                max_length = heights[first_position + 2];
                            }
                            else
                            {
                                max_length = heights[first_position];
                            }
                            max_length = max_length + 1;
                        
                            //Adding 'T' would affect 3 columns, so we need create 3 new column to store the new and old data.
                            char *new_column1 = new char[max_length];
                            char *new_column2 = new char[max_length];
                            char *new_column3 = new char[max_length];
                        
                            //According to the shape of the 'T',we can know the value of at end of the each column.
                            new_column1[max_length-1]='T';new_column2[max_length-1]='T';new_column2[max_length-2]='T';new_column3[max_length-1]='T';
                        
                            //Copy old data and fill the "air" with space character.
                            for(int i = 0;i<(max_length-1); i++)
                            {
                                new_column3[i] = data[first_position+2][i];
                            }
                            for(int i = heights[first_position+2]; i < (max_length-1);i++)
                            {
                                new_column3[i] = ' ';
                            }
                            for(int i = 0;i<heights[first_position];i++)
                            {
                                new_column1[i] = data[first_position][i];
                            }
                            for(int i = heights[first_position]; i < (max_length-1);i++)
                            {
                                new_column1[i] = ' ';
                            }
                            for(int i = 0; i<heights[first_position+1];i++)
                            {
                                new_column2[i] = data[first_position+1][i];
                            }
                            for(int i = heights[first_position+1];i<(max_length-2);i++)
                            {
                                new_column2[i] = ' ';
                            }
                        
                            //reset the data pointer,making it point to the new column and also release the old heap memory.
                            delete []data[first_position];delete []data[first_position+1];delete []data[first_position+2];
                            heights[first_position]=max_length;
                            heights[first_position+1]=max_length;
                            heights[first_position+2]=max_length;
                            data[first_position] = new_column1;
                            data[first_position+1]=new_column2;
                            data[first_position+2]=new_column3;
                    }
                    
                    
                    //If the second column has the max height, the new max height would be (max height + 2).
                    else
                    {
                        int max_length = heights[first_position+1];
                        max_length = max_length + 2;
                        char *new_column1 = new char[max_length];
                        char *new_column2 = new char[max_length];
                        char *new_column3 = new char[max_length];
                        new_column1[max_length-2] = ' ';new_column1[max_length-1] = 'T';
                        new_column2[max_length-2] = 'T';new_column2[max_length-1] = 'T';
                        new_column3[max_length-2] = ' ';new_column3[max_length-1] = 'T';
                        for(int i = 0 ; i < heights[first_position]; i++)
                        {
                            new_column1[i] = data[first_position][i];
                        }
                        for(int i = heights[first_position]; i< (max_length-2); i++)
                        {
                            new_column1[i] = ' ';
                        }
                        for(int i = 0 ; i < heights[first_position+1]; i++)
                        {
                            new_column2[i] = data[first_position+1][i];
                        }
                        for(int i = 0 ; i < heights[first_position+2]; i++)
                        {
                            new_column3[i] = data[first_position+2][i];
                        }
                        for(int i = heights[first_position+2]; i< (max_length-2); i++)
                        {
                            new_column3[i] = ' ';
                        }
                        delete []data[first_position];delete []data[first_position+1];delete []data[first_position+2];
                        heights[first_position]=max_length;
                        heights[first_position+1]=max_length;
                        heights[first_position+2]=max_length;
                        data[first_position] = new_column1;
                        data[first_position+1]=new_column2;
                        data[first_position+2]=new_column3;
                    }
                }
                
                //This situation is that there is no elements on the bottom of the board, So we can easily build the new column.
                else
                {
                    char *new_column1 = new char[2];
                    char *new_column2 = new char[2];
                    char *new_column3 = new char[2];
                    new_column1[0] = ' ';new_column1[1] = 'T';
                    new_column2[0] = 'T';new_column2[1] = 'T';
                    new_column3[0] = ' ';new_column3[1] = 'T';
                    delete []data[first_position];delete []data[first_position+1];delete []data[first_position+2];
                    data[first_position] = new_column1;
                    data[first_position+1]=new_column2;
                    data[first_position+2]=new_column3;
                    heights[first_position]=2;
                    heights[first_position+1]=2;
                    heights[first_position+2]=2;
                }
            }
            
            //If the position is not suitable, show the following message.
            else
            {
                cout<<"the position is not sutiable."<<endl;
            }
        }
        
        //Second situation, rotation is 90 and it would affect two columns. So we just need create two column to complete moving and adding new data.
        else if(rotation == 90)
        {
            //See if the position is suitable.
            if(first_position >= 0 && (first_position + 1) < width)
            {
                //To judge if there is element on the bottom of the board.
                if(heights[first_position] != 0 || heights[first_position+1] !=0)
                {
                    //There are two situation when we add a 'T' with rotation of 90.
                    
                    //First situation, if the first column's height is no more than the second height, the new max height would second column's height plus 3.
                    if(heights[first_position]<=heights[first_position+1])
                    {
                        //calculate the max new length of the two column
                        int max_length = heights[first_position+1] + 3;
                        char *new_column1 = new char[max_length-1];
                        char *new_column2 = new char[max_length];
                        new_column1[max_length-2] = 'T';
                        new_column2[max_length-1] = 'T';new_column2[max_length-2] = 'T';new_column2[max_length-3] = 'T';
                        for(int i = 0; i< heights[first_position]; i++)
                        {
                            new_column1[i] = data[first_position][i];
                        }
                        for(int i = heights[first_position];i<(max_length-2);i++)
                        {
                            new_column1[i] = ' ';
                        }
                        for(int i = 0; i <heights[first_position+1];i++)
                        {
                            new_column2[i] = data[first_position+1][i];
                        }
                        heights[first_position] = max_length - 1;
                        heights[first_position+1] = max_length;
                        delete[]data[first_position];delete []data[first_position+1];
                        data[first_position] = new_column1;
                        data[first_position+1] = new_column2;
                    }
                    
                    //Second situation, if the first column's height is more than the second column's height, the new max height would first column's height plus 2.
                    else
                    {
                        int max_length = heights[first_position] + 2;
                        char *new_column1 = new char[max_length-1];
                        char *new_column2 = new char[max_length];
                        new_column1[max_length-2] = 'T';
                        new_column2[max_length-1] = 'T';new_column2[max_length-2] = 'T';new_column2[max_length-3] = 'T';
                        for(int i = 0; i < heights[first_position];i++)
                        {
                            new_column1[i] = data[first_position][i];
                        }
                        for(int i = 0; i< heights[first_position+1];i++)
                        {
                            new_column2[i] = data[first_position+1][i];
                        }
                        for(int i = heights[first_position+1];i<(max_length-3);i++)
                        {
                            new_column2[i] = ' ';
                        }
                        heights[first_position] = max_length - 1;
                        heights[first_position+1] = max_length;
                        delete[]data[first_position];delete []data[first_position+1];
                        data[first_position] = new_column1;
                        data[first_position+1] = new_column2;
                    }
                }
                
                //there are no elements in the bottom of the board
                else
                {
                    char *new_column1 = new char[2];
                    char *new_column2 = new char[3];
                    new_column1[0] = ' ';new_column1[1] = 'T';
                    new_column2[0] = 'T';new_column2[1] = 'T';new_column2[2] = 'T';
                    delete[]data[first_position];delete []data[first_position+1];
                    heights[first_position] = 2;
                    heights[first_position+1] = 3;
                    data[first_position] = new_column1;
                    data[first_position+1] = new_column2;
                }
            }
            else
            {
                cout<<"the position is not sutiable."<<endl;
            }
        }
        
        //Add a 'T' wiht rotation of 180.
        else if(rotation == 180)
        {
            //See if the position is suitable.
            if(first_position >= 0 && (first_position + 2) < width)
            {
                //To judge if there is element on the bottom of the board.
                if(heights[first_position] != 0 || heights[first_position+1] !=0 || heights[first_position+2] !=0)
                {
                    //Adding a 'T' wiht rotation of 180 would affect three columns. The second column would have the max new height. First and third columns' height would
                    //1 less than the second column.
                    int max_length = 0;
                    for(int i = 0; i < 3 ; i++)
                    {
                        if(max_length < heights[first_position + i])
                        {
                            max_length = heights[first_position + i];
                        }
                    }
                    max_length = max_length + 2;
                    char *new_column1 = new char[max_length-1];
                    char *new_column2 = new char[max_length];
                    char *new_column3 = new char[max_length-1];
                    new_column1[max_length-2] = 'T';new_column2[max_length-1] = 'T';new_column2[max_length-2]='T';new_column3[max_length-2] = 'T';
                    for(int i = 0 ; i < heights[first_position];i++)
                    {
                        new_column1[i] = data[first_position][i];
                    }
                    for(int i = heights[first_position];i<(max_length-2);i++)
                    {
                        new_column1[i] = ' ';
                    }
                    for(int i = 0 ; i < heights[first_position+1];i++)
                    {
                        new_column2[i] = data[first_position+1][i];
                    }
                    for(int i = heights[first_position+1];i<(max_length-2);i++)
                    {
                        new_column2[i] = ' ';
                    }
                    for(int i = 0 ; i < heights[first_position+2];i++)
                    {
                        new_column3[i] = data[first_position+2][i];
                    }
                    for(int i = heights[first_position+2];i<(max_length-2);i++)
                    {
                        new_column3[i] = ' ';
                    }
                    delete[]data[first_position];delete []data[first_position+1];delete []data[first_position+2];
                    data[first_position] = new_column1;
                    data[first_position+1] = new_column2;
                    data[first_position+2] = new_column3;
                    heights[first_position] = max_length -1;
                    heights[first_position+1] = max_length;
                    heights[first_position+2] = max_length-1;
                }
                
                //There are no elements on the bottom of the board.
                else
                {
                    char *new_column1 = new char[1];
                    char *new_column2 = new char[2];
                    char *new_column3 = new char[1];
                    new_column1[0] = 'T';new_column2[0] = 'T'; new_column2[1] = 'T'; new_column3[0] = 'T';
                    delete[]data[first_position];delete []data[first_position+1];delete []data[first_position+2];
                    heights[first_position] = 1;
                    heights[first_position+1] = 2;
                    heights[first_position+2] = 1;
                    data[first_position] = new_column1;
                    data[first_position+1] = new_column2;
                    data[first_position+2] = new_column3;
                }
            }
            
            //Show the following message when the position is not suitable.
            else
            {
                cout<<"the position is not suitable."<<endl;
            }
        }
        
        //Add a 'T' wiht rotation of 270.
        else if(rotation == 270)
        {
            //See if the position is suitable.
            if(first_position >= 0 && (first_position + 1) < width)
            {
                //To judge if there is element on the bottom of the board.
                if(heights[first_position] != 0 || heights[first_position+1] !=0)
                {
                    //There are two situation when we add a 'T' with rotation of 270.
                    
                    //First situation, if the first column's height is no more than the second height, the new max height would second column's height plus 2.
                    if(heights[first_position] < heights[first_position+1])
                    {
                        int max_length = heights[first_position+1] + 2;
                        char *new_column1 = new char[max_length];
                        char *new_column2 = new char[max_length-1];
                        new_column1[max_length-1] = 'T';new_column1[max_length-2] = 'T';new_column1[max_length-3] = 'T';
                        new_column2[max_length-2] = 'T';
                        for(int i = 0 ; i< heights[first_position];i++)
                        {
                            new_column1[i] = data[first_position][i];
                        }
                        for(int i = heights[first_position]; i< (max_length-3);i++)
                        {
                            new_column1[i] = ' ';
                        }
                        for(int i = 0; i < heights[first_position + 1];i++)
                        {
                            new_column2[i] = data[first_position+1][i];
                        }
                        delete []data[first_position];delete []data[first_position+1];
                        data[first_position] = new_column1;
                        data[first_position+1] = new_column2;
                        heights[first_position] = max_length;
                        heights[first_position+1] = max_length-1;
                    }
                    //Second situation, if the first column's height no more than the second column's height, the new max height would first column's height plus 3.
                    else
                    {
                        int max_length = heights[first_position]+3;
                        char *new_column1 = new char[max_length];
                        char *new_column2 = new char[max_length-1];
                        new_column1[max_length-1] = 'T';new_column1[max_length-2] = 'T';new_column1[max_length-3] = 'T';
                        new_column2[max_length-2] = 'T';
                        for(int i = 0; i < heights[first_position];i++)
                        {
                            new_column1[i] = data[first_position][i];
                        }
                        for(int i = 0; i < heights[first_position+1];i++)
                        {
                            new_column2[i] = data[first_position+1][i];
                        }
                        for(int i = heights[first_position+1]; i < (max_length-2);i++)
                        {
                            new_column2[i] = ' ';
                        }
                        delete []data[first_position];delete []data[first_position+1];
                        data[first_position] = new_column1;
                        data[first_position+1] = new_column2;
                        heights[first_position] = max_length;
                        heights[first_position+1] = max_length-1;

                    }
                }
                else
                {
                    char *new_column1 = new char[3];
                    char *new_column2 = new char[2];
                    new_column1[0] = 'T';new_column1[1] = 'T';new_column1[2] = 'T';
                    new_column2[0] = ' ';new_column2[1] = 'T';
                    delete []data[first_position];delete []data[first_position+1];
                    data[first_position] = new_column1;
                    data[first_position+1] = new_column2;
                    heights[first_position] = 3;
                    heights[first_position+1] = 2;
                }
            }
            
            //If the position is not suitable, show the following message.
            else
            {
                cout<<"the position is not suitable."<<endl;
            }
        }
        //If the rotation do not meet the requirement,show the following message.
        else
        {
            cout<<"Input the wrong rotation."<<endl;
        }
    }
    
    //Adding a 'Z' to the board, there are only two shapes of 'Z' according to the rotation.(0 and 180, 90 and 270)
    else if(a == 'Z')
    {
        //First,judge the roration to see if it is compliant, else we should print the error information.
        if(rotation == 0 || rotation == 180)
        {
            //Second, judge the position we want to add the "Z",if it is not in the width of the board we should also print the error information.
            if(first_position >= 0 && (first_position + 2) < width)
            {
                //When we add a 'Z' to the board, it would affected 3 existed columns. And the new max height is depended on max height between three columns.
                //First situation, if the first column has max height, the new max height would be (heights[first_position] + 1).
                //Second situation, if second or third column have max height, the new max height would be (heights[first_position+1] + 2 or heights[first_position+2] + 2).
                
                //First situation.
                if(heights[first_position]>heights[first_position+1]&&heights[first_position]>heights[first_position+2])
                {
                    int max_length = heights[first_position]+1;
                    char *new_column1 = new char[max_length];
                    char *new_column2 = new char[max_length];
                    char *new_column3 = new char[max_length-1];
                    
                    //add the new data to the end of the each new column.
                    new_column1[max_length-1] = 'Z';
                    new_column2[max_length-1] = 'Z';new_column2[max_length-2] = 'Z';
                    new_column3[max_length-2] = 'Z';
                    for(int i = 0 ; i < heights[first_position];i++)
                    {
                        new_column1[i] = data[first_position][i];
                    }
                    for(int i = 0; i < heights[first_position+1];i ++)
                    {
                        new_column2[i] = data[first_position+1][i];
                    }
                    for(int i = heights[first_position+1];i<(max_length-2);i++)
                    {
                        new_column2[i] = ' ';
                    }
                    for(int i = 0; i < heights[first_position+2];i ++)
                    {
                        new_column3[i] = data[first_position+2][i];
                    }
                    for(int i = heights[first_position+2];i<(max_length-2);i++)
                    {
                        new_column3[i] = ' ';
                    }
                    
                    //Copy the new data and release the memory.
                    delete []data[first_position];delete []data[first_position+1];delete []data[first_position+2];
                    data[first_position] = new_column1;
                    data[first_position+1] = new_column2;
                    data[first_position+2] = new_column3;
                    heights[first_position] = max_length;
                    heights[first_position+1] = max_length;
                    heights[first_position+2] = max_length-1;
                }
                
                //The second situation.
                else
                {
                    int max_length = 0;
                    for(int i = 0;i<3;i++)
                    {
                        if(max_length < heights[first_position+i])
                        {
                            max_length = heights[first_position+i];
                        }
                    }
                    max_length = max_length +2;
                    char *new_column1 = new char[max_length];
                    char *new_column2 = new char[max_length];
                    char *new_column3 = new char[max_length-1];
                    new_column1[max_length-1] = 'Z';
                    new_column2[max_length-1] = 'Z';new_column2[max_length-2] = 'Z';
                    new_column3[max_length-2] = 'Z';
                    for(int i = 0 ; i < heights[first_position];i++)
                    {
                        new_column1[i] = data[first_position][i];
                    }
                    for(int i = heights[first_position];i<(max_length-1);i++)
                    {
                        new_column1[i] = ' ';
                    }
                    for(int i = 0; i < heights[first_position+1];i ++)
                    {
                        new_column2[i] = data[first_position+1][i];
                    }
                    for(int i = heights[first_position+1];i<(max_length-2);i++)
                    {
                        new_column2[i] = ' ';
                    }
                    for(int i = 0; i < heights[first_position+2];i ++)
                    {
                        new_column3[i] = data[first_position+2][i];
                    }
                    for(int i = heights[first_position+2];i<(max_length-2);i++)
                    {
                        new_column3[i] = ' ';
                    }
                    delete []data[first_position];delete []data[first_position+1];delete []data[first_position+2];
                    data[first_position] = new_column1;
                    data[first_position+1] = new_column2;
                    data[first_position+2] = new_column3;
                    heights[first_position] = max_length;
                    heights[first_position+1] = max_length;
                    heights[first_position+2] = max_length-1;
                }
            }
            
            //Print the message when the position we want to add the new 'Z' is no compliant.
            else
            {
                cout<<"the position is not suitable."<<endl;
            }
        }
        
        //The second shape of 'Z'
        else if(rotation == 90 || rotation == 270)
        {
            //Adding a 'Z' with rotation of 90 or 270 would affect 2 existed columns.
            
            //Judge the position to see if it is compliant or not.
            if(first_position >= 0 && (first_position + 1) < width)
            {
                //There are two situation and the new max height is depended on max height between these two columns.
                //The first situation, if first column's height is less than the second, the new max height would be (heights[first_position+1] +2).
                //The second situation, if first column's height is no less than the second column's height,the new max height would be (heights[first_position] +3)
                
                //First situation.
                if(heights[first_position]<heights[first_position+1])
                {
                    int max_length = heights[first_position+1]+2;
                    char *new_column1 = new char[max_length-1];
                    char *new_column2 = new char[max_length];
                    //add the new data to the end of the each new column.
                    new_column1[max_length-2] = 'Z';new_column1[max_length-3] = 'Z';
                    new_column2[max_length-1] = 'Z';new_column2[max_length-2] = 'Z';
                    for(int i = 0 ; i < heights[first_position];i++)
                    {
                        new_column1[i] = data[first_position][i];
                    }
                    for(int i = heights[first_position];i<(max_length-3);i++)
                    {
                        new_column1[i] = ' ';
                    }
                    for(int i =0;i< heights[first_position+1];i++)
                    {
                        new_column2[i] = data[first_position+1][i];
                    }
                    delete []data[first_position];delete []data[first_position+1];
                    data[first_position] = new_column1;
                    data[first_position+1] = new_column2;
                    heights[first_position] = max_length - 1;
                    heights[first_position+1] = max_length ;
                }
                
                //The second situation.
                else
                {
                    int max_length = heights[first_position] + 3;
                    char *new_column1 = new char[max_length -1];
                    char *new_column2 = new char[max_length];
                    new_column1[max_length-2] = 'Z';new_column1[max_length-3] = 'Z';
                    new_column2[max_length-1] = 'Z';new_column2[max_length-2] = 'Z';
                    for(int i = 0 ; i < heights[first_position];i++)
                    {
                        new_column1[i] = data[first_position][i];
                    }
                    for(int i = heights[first_position];i<(max_length-3);i++)
                    {
                        new_column1[i] = ' ';
                    }
                    for(int i = 0;i<heights[first_position+1];i++)
                    {
                        new_column2[i] = data[first_position+1][i];
                    }
                    for(int i = heights[first_position+1];i<(max_length-2);i++)
                    {
                        new_column2[i] = ' ';
                    }
                    delete []data[first_position];delete []data[first_position+1];
                    data[first_position] = new_column1;
                    data[first_position+1] = new_column2;
                    heights[first_position] = max_length - 1;
                    heights[first_position+1] = max_length ;
                }
            }
            //Print the following information when position is not suitable.
            else
            {
                cout<<"the position is not suitable."<<endl;
            }
        }
        
        //Print the following information when we input wrong rotation.
        else
        {
            cout<<"Input the wrong rotation."<<endl;
        }
    }
    
    //Adding a 'S' to the board, there are only two shapes of 'S' according to the rotation.(0 and 180, 90 and 270)
    else if(a == 'S')
    {
        //First,judge the roration to see if it is compliant, else we should print the error information.
        if(rotation == 0 || rotation == 180)
        {
            //Second, judge the position we want to add the "S",if it is not in the width of the board we should also print the error information.
            if(first_position >= 0 && (first_position + 2) < width)
            {
                //When we add a 'S' to the board, it would affected 3 existed columns. And the new max height is depended on max height between three columns.
                //First situation, if the third column has max height, the new max height would be (heights[first_position+2] + 1).
                //Second situation, if first or second column have max height, the new max height would be (heights[first_position+1] + 2 or heights[first_position] + 2).
                
                //First situation.
                if(heights[first_position+2]>heights[first_position]&&heights[first_position+2]>heights[first_position+1])
                {
                    int max_length = heights[first_position+2]+1;
                    char *new_column1 = new char[max_length-1];
                    char *new_column2 = new char[max_length];
                    char *new_column3 = new char[max_length];
                    new_column1[max_length - 2] = 'S';
                    new_column2[max_length - 1] = 'S';new_column2[max_length-2]='S';
                    new_column3[max_length-1]='S';
                    for (int i=0;i<heights[first_position];i++)
                    {
                        new_column1[i] = data[first_position][i];
                    }
                    for(int i = heights[first_position];i<(max_length-2);i++)
                    {
                        new_column1[i] = ' ';
                    }
                    for (int i=0;i<heights[first_position+1];i++)
                    {
                        new_column2[i] = data[first_position+1][i];
                    }
                    for(int i = heights[first_position];i<(max_length-2);i++)
                    {
                        new_column2[i] = ' ';
                    }
                    for(int i = 0 ; i< heights[first_position+2];i++)
                    {
                        new_column3[i] = data[first_position+2][i];
                    }
                    delete []data[first_position];delete []data[first_position+1];delete []data[first_position+2];
                    data[first_position] = new_column1;
                    data[first_position+1] = new_column2;
                    data[first_position+2] = new_column3;
                    heights[first_position] = max_length-1;
                    heights[first_position+1]=max_length;
                    heights[first_position+2]=max_length;
                }
                //Second situation.
                else
                {
                    int max_length = 0;
                    for(int i = 0; i<3;i++)
                    {
                        if(max_length < heights[first_position+i])
                        {
                            max_length = heights[first_position+i];
                        }
                    }
                    max_length = max_length + 2;
                    char *new_column1 = new char[max_length-1];
                    char *new_column2 = new char[max_length];
                    char *new_column3 = new char[max_length];
                    new_column1[max_length - 2] = 'S';
                    new_column2[max_length - 1] = 'S';new_column2[max_length-2]='S';
                    new_column3[max_length-1]='S';
                    for(int i = 0; i< heights[first_position];i++)
                    {
                        new_column1[i] = data[first_position][i];
                    }
                    for(int i = heights[first_position];i<(max_length-2);i++)
                    {
                        new_column1[i] = ' ';
                    }
                    for(int i = 0; i< heights[first_position+1];i++)
                    {
                        new_column2[i] = data[first_position+1][i];
                    }
                    for(int i = heights[first_position];i<(max_length-2);i++)
                    {
                        new_column2[i] = ' ';
                    }
                    for(int i = 0; i<heights[first_position+2];i++)
                    {
                        new_column3[i] = data[first_position+2][i];
                    }
                    for(int i = heights[first_position+2];i<(max_length-1);i++)
                    {
                        new_column3[i] = ' ';
                    }
                    delete []data[first_position];delete []data[first_position+1];delete []data[first_position+2];
                    data[first_position] = new_column1;
                    data[first_position+1] = new_column2;
                    data[first_position+2] = new_column3;
                    heights[first_position] = max_length-1;
                    heights[first_position+1]=max_length;
                    heights[first_position+2]=max_length;
                }
            }
            else
            {
                cout<<"the position is not suitable."<<endl;
            }
        }
        
        
        //Adding the other shape of 'S'.
        else if(rotation == 90 || rotation == 270)
        {
            //Second, judge the position we want to add the "S",if it is not in the width of the board we should also print the error information.
            if(first_position >= 0 && (first_position + 1) < width)
            {
                //Adding a 'S' with rotation of 90 or 270 would affect 2 existed columns.
                //There are two situation and the new max height is depended on max height between these two columns.
                //The first situation, if first column's height is more than the second, the new max height would be (heights[first_position+1] +2).
                //The second situation, if first column's height is less than the second column's height,the new max height would be (heights[first_position] +3)
                
                //First situation.
                if(heights[first_position]>heights[first_position+1])
                {
                    int max_length = heights[first_position] + 2;
                    char *new_column1 = new char[max_length];
                    char *new_column2 = new char[max_length-1];
                    new_column1[max_length-1] = 'S';new_column1[max_length-2] = 'S';
                    new_column2[max_length-2] = 'S';new_column2[max_length-3] = 'S';
                    for(int i = 0; i< heights[first_position];i++)
                    {
                        new_column1[i]=data[first_position][i];
                    }
                    for(int i = 0; i< heights[first_position+1];i++)
                    {
                        new_column2[i]=data[first_position+1][i];
                    }
                    for(int i = heights[first_position+1];i<(max_length-3);i++)
                    {
                        new_column2[i] = ' ';
                    }
                    delete []data[first_position];delete []data[first_position+1];
                    data[first_position] = new_column1;
                    data[first_position+1] = new_column2;
                    heights[first_position] = max_length ;
                    heights[first_position+1] = max_length-1;
                }
                
                //Second situation.
                else
                {
                    int max_length = heights[first_position+1]+3;
                    char *new_column1 = new char[max_length];
                    char *new_column2 = new char[max_length-1];
                    new_column1[max_length-1] = 'S';new_column1[max_length-2] = 'S';
                    new_column2[max_length-2] = 'S';new_column2[max_length-3] = 'S';
                    for(int i = 0; i< heights[first_position];i++)
                    {
                        new_column1[i]=data[first_position][i];
                    }
                    for(int i = heights[first_position];i<(max_length-2);i++)
                    {
                        new_column1[i]= ' ';
                    }
                    for(int i = 0; i< heights[first_position+1];i++)
                    {
                        new_column2[i]=data[first_position+1][i];
                    }
                    for(int i = heights[first_position+1];i<(max_length-3);i++)
                    {
                        new_column2[i] = ' ';
                    }
                    delete []data[first_position];delete []data[first_position+1];
                    data[first_position] = new_column1;
                    data[first_position+1] = new_column2;
                    heights[first_position] = max_length ;
                    heights[first_position+1] = max_length-1;
                }
            }
            //Print the following information when position is not suitable.
            else
            {
                cout<<"the position is not suitable."<<endl;
            }
        }
         //If the rotation do not meet the requirement,show the following message.
        else
        {
            cout<<"Input the wrong rotation."<<endl;
        }
    }
    
    //Adding a 'L' to the board, there are four shapes of 'L' according to the rotation.
    else if(a == 'L')
    {
        //When the rotation is 0.
        if(rotation == 0)
        {
            //Judge the position we want to add the 'L' and if it is not compliant, print the error message.
            //Adding a 'L' with rotation 0 will affect two existed columns.
            if(first_position >= 0 && (first_position + 1) < width)
            {
                //determine the max height between first column and second column.
                int max_length = 0;
                if(heights[first_position] < heights[first_position+1])
                {
                    max_length = heights[first_position+1];
                }
                else
                {
                    max_length = heights[first_position];
                }
                max_length = max_length + 3;
                
                //According to the shape of 'L', we can easily know the new height of each column. Fisrt column is new max height and the second column is (max length-2).
                char *new_column1 = new char[max_length];
                char *new_column2 = new char[max_length-2];
                
                //Adding the new data to the end of the two relevant column.
                new_column1[max_length-1] = 'L';new_column1[max_length-2] = 'L';new_column1[max_length-3] = 'L';
                new_column2[max_length-3] = 'L';
                for(int i = 0 ; i< heights[first_position];i++)
                {
                    new_column1[i] = data[first_position][i];
                }
                for(int i = heights[first_position];i < (max_length-3);i++)
                {
                    new_column1[i] = ' ';
                }
                for(int i = 0; i<heights[first_position+1];i++)
                {
                    new_column2[i] = data[first_position+1][i];
                }
                for(int i = heights[first_position+1];i<(max_length-3);i++)
                {
                    new_column2[i] = ' ';
                }
                
                //Copy the data and release the memory.
                delete []data[first_position];delete []data[first_position+1];
                data[first_position] = new_column1;
                data[first_position+1] = new_column2;
                heights[first_position] = max_length;
                heights[first_position+1] = max_length -2;
            }
            //print the information when the position is not suitable.
            else
            {
                cout<<"the position is not suitable."<<endl;
            }
        }
        
        //Adding a 'L' with rotaion of 90 and it would affect three existed column.
        else if(rotation == 90)
        {
            //Judge the position we want to add the 'L' and if it is not compliant, print the error message.
            if(first_position >= 0 && (first_position + 2) < width)
            {
                //There are two situation when we want to add a 'L' with rotaion of 90.
                //First situation, first column has the max height and the new max height is (heights[first_position] +2)
                //Second situation, first column do not have the max height and the new max height is (heights[first_position+1] +1 or heights[first_position+2] +1)
                
                //First situation.
                if(heights[first_position]>=heights[first_position+1]&&heights[first_position]>=heights[first_position+1])
                {
                    int max_length = heights[first_position] + 2;
                    char *new_column1 = new char [max_length];
                    char *new_column2 = new char [max_length];
                    char *new_column3 = new char [max_length];
                    
                    //Adding the new data to the end of the new column.
                    new_column1[max_length-1] = 'L';new_column2[max_length-1] = 'L';new_column3[max_length-1] = 'L';
                    new_column1[max_length-2] = 'L';
                    for(int i = 0 ; i< heights[first_position];i++)
                    {
                        new_column1[i] = data[first_position][i];
                    }
                    for(int i = 0; i< heights[first_position+1];i++)
                    {
                        new_column2[i] = data[first_position+1][i];
                    }
                    for(int i = heights[first_position+1];i<(max_length-1);i++)
                    {
                        new_column2[i] = ' ';
                    }
                    for(int i = 0; i< heights[first_position+2];i++)
                    {
                        new_column3[i] = data[first_position+2][i];
                    }
                    for(int i = heights[first_position+2];i<(max_length-1);i++)
                    {
                        new_column3[i] = ' ';
                    }
                    delete []data[first_position];delete []data[first_position+1];delete []data[first_position+2];
                    data[first_position] = new_column1;
                    data[first_position+1] = new_column2;
                    data[first_position+2] = new_column3;
                    heights[first_position] = max_length ;
                    heights[first_position+1] = max_length;
                    heights[first_position+2] = max_length;
                }
                
                //Second situation,the new max height is (heights[first_position+1] +1 or heights[first_position+2] +1)
                else
                {
                    int max_length = 0;
                    if(heights[first_position+1]<heights[first_position+2])
                    {
                        max_length = heights[first_position+2];
                    }
                    else
                    {
                        max_length = heights[first_position+1];
                    }
                    max_length = max_length+1;
                    char *new_column1 = new char [max_length];
                    char *new_column2 = new char [max_length];
                    char *new_column3 = new char [max_length];
                    //Adding the new data to the end of the two relevant column.
                    new_column1[max_length-1] = 'L';new_column2[max_length-1] = 'L';new_column3[max_length-1] = 'L';
                    new_column1[max_length-2] = 'L';
                    for(int i = 0 ; i< heights[first_position];i++)
                    {
                        new_column1[i] = data[first_position][i];
                    }
                    for(int i = heights[first_position];i < (max_length-2);i++)
                    {
                        new_column1[i] = ' ';
                    }
                    for(int i = 0; i< heights[first_position+1];i++)
                    {
                        new_column2[i] = data[first_position+1][i];
                    }
                    for(int i = heights[first_position+1];i<(max_length-1);i++)
                    {
                        new_column2[i] = ' ';
                    }
                    for(int i = 0; i< heights[first_position+2];i++)
                    {
                        new_column3[i] = data[first_position+2][i];
                    }
                    for(int i = heights[first_position+2];i<(max_length-1);i++)
                    {
                        new_column3[i] = ' ';
                    }
                    delete []data[first_position];delete []data[first_position+1];delete []data[first_position+2];
                    data[first_position] = new_column1;
                    data[first_position+1] = new_column2;
                    data[first_position+2] = new_column3;
                    heights[first_position] = max_length ;
                    heights[first_position+1] = max_length;
                    heights[first_position+2] = max_length;

                }
            }
            //print the information when the position is not suitable.
            else
            {
                cout<<"the position is not suitable."<<endl;
            }
        }
        //Adding a 'L' with rotaion of 180 and it would affect 2 existed column.
        else if(rotation == 180)
        {
            //Judge the position we want to add the 'L' and if it is not compliant, print the error message.
            if(first_position >= 0 && (first_position + 1) < width)
            {
                //There are two situation when we want to add a 'L' with rotaion of 180.
                //First situation, first column's height is two or more more than the second column's height.The new max height is (heights[first_position] +1)
                //Second situation, first column do not have the height that is 2 or more more than the second column's height.At this situation, the new max height is (heights[first_position+1] +3)
                
                //First situation.
                if((heights[first_position]-heights[first_position+1])>=2)
                {
                    int max_length = heights[first_position]+1;
                    char *new_column1 = new char[max_length];
                    char *new_column2 = new char[max_length];
                    new_column1[max_length-1] = 'L';
                    new_column2[max_length-1]= 'L'; new_column2[max_length-2]= 'L'; new_column2[max_length-3]= 'L';
                    for(int i = 0 ; i< heights[first_position];i++)
                    {
                        new_column1[i] = data[first_position][i];
                    }
                    for(int i = 0; i< heights[first_position+1];i++)
                    {
                        new_column2[i] = data[first_position+1][i];
                    }
                    for(int i = heights[first_position+1];i<(max_length-3);i++)
                    {
                        new_column2[i] = ' ';
                    }
                    delete []data[first_position];delete []data[first_position+1];
                    data[first_position] = new_column1;
                    data[first_position+1]=new_column2;
                    heights[first_position] = max_length;
                    heights[first_position+1] = max_length;
                }
                
                //Second situation.
                else
                {
                    int max_length = heights[first_position+1]+3;
                    char *new_column1 = new char[max_length];
                    char *new_column2 = new char[max_length];
                    new_column1[max_length-1] = 'L';
                    new_column2[max_length-1]= 'L'; new_column2[max_length-2]= 'L'; new_column2[max_length-3]= 'L';
                    for(int i = 0; i< heights[first_position];i++)
                    {
                        new_column1[i] = data[first_position][i];
                    }
                    for(int i = heights[first_position];i<(max_length-1);i++)
                    {
                        new_column1[i] = ' ';
                    }
                    for(int i = 0; i< heights[first_position+1];i++)
                    {
                        new_column2[i] = data[first_position+1][i];
                    }
                    delete []data[first_position];delete []data[first_position+1];
                    data[first_position] = new_column1;
                    data[first_position+1]=new_column2;
                    heights[first_position] = max_length;
                    heights[first_position+1] = max_length;
                }
            }
            
            //print the information when the position is not suitable.
            else
            {
                cout<<"the position is not suitable."<<endl;
            }
        }
        
        //Adding a 'L' with rotaion of 270 and it would affect 3 existed column.
        else if(rotation == 270)
        {
            //Judge the position we want to add the 'L' and if it is not compliant, print the error message.
            if(first_position >= 0 && (first_position + 2) < width)
            {
                //There is only one situation when we add a 'L' with rotation of 270.
                //The new max height is old max height plus 2. And the new third column's height is max and first and second column is 1 less than it.
                int max_length = 0;
                for(int i = 0 ; i< 3;i++)
                {
                    if (max_length<heights[first_position+i])
                    {
                        max_length = heights[first_position+i];
                    }
                }
                max_length = max_length + 2;
                char *new_column1 = new char[max_length-1];
                char *new_column2 = new char[max_length-1];
                char *new_column3 = new char[max_length];
                new_column1[max_length-2] = 'L';new_column2[max_length-2] = 'L';new_column3[max_length-1] = 'L';new_column3[max_length-2] = 'L';
                for(int i = 0; i< heights[first_position];i++)
                {
                    new_column1[i] = data[first_position][i];
                }
                for(int i = heights[first_position];i<(max_length-2);i++)
                {
                    new_column1[i] = ' ';
                }
                for(int i = 0; i< heights[first_position+1];i++)
                {
                    new_column2[i] = data[first_position+1][i];
                }
                for(int i = heights[first_position+1];i<(max_length-2);i++)
                {
                    new_column2[i] = ' ';
                }
                for(int i = 0; i< heights[first_position+2];i++)
                {
                    new_column3[i] = data[first_position+2][i];
                }
                for(int i = heights[first_position+2];i<(max_length-2);i++)
                {
                    new_column3[i] = ' ';
                }
                delete []data[first_position];delete []data[first_position+1];delete []data[first_position+2];
                data[first_position] = new_column1;
                data[first_position+1]=new_column2;
                data[first_position+2]=new_column3;
                heights[first_position] = max_length-1;
                heights[first_position+1] = max_length-1;
                heights[first_position+2] = max_length;
            }
            //print the information when the position is not suitable.
            else
            {
                cout<<"the position is not suitable."<<endl;
            }
        }
        
        //If the rotation do not meet the requirement,show the following message.
        else
        {
            cout<<"Input the wrong rotation."<<endl;
        }
    }
    
    //Adding a 'J' to the board, there are four shapes of 'L' according to the rotation.
    else if(a == 'J')
    {
        //When the rotation is 0.
        if(rotation == 0)
        {
            //Judge the position we want to add the 'L' and if it is not compliant, print the error message.
            //Adding a 'J' with rotation 0 will affect two existed columns.
            if(first_position>=0&&(first_position+1)<width)
            {
                //determine the max height between first column and second column.
                int max_length = 0;
                if(heights[first_position]< heights[first_position+1])
                {
                    max_length = heights[first_position+1];
                }
                else
                {
                    max_length = heights[first_position];
                }
                max_length =max_length + 3;
                
                //According to the shape of 'J', we can easily know the new height of each column. Fisrt column is new max height-2 and the second column is max length.
                char *new_column1 = new char [max_length-2];
                char *new_column2 = new char[max_length];
                new_column1[max_length-3] = 'J';
                new_column2[max_length-1] = 'J'; new_column2[max_length-2] = 'J'; new_column2[max_length-3] = 'J';
                for(int i = 0 ; i< heights[first_position];i++)
                {
                    new_column1[i] = data[first_position][i];
                }
                for(int i = heights[first_position]; i<(max_length -3);i++)
                {
                    new_column1[i] = ' ';
                }
                for(int i = 0; i<heights[first_position+1];i++)
                {
                    new_column2[i] = data[first_position+1][i];
                }
                for(int i = heights[first_position+1];i< (max_length-3);i++)
                {
                    new_column2[i] =' ';
                }
                //Copy the data and release the memory.
                delete []data[first_position];delete[]data[first_position+1];
                data[first_position] = new_column1;
                data[first_position+1] = new_column2;
                heights[first_position] = max_length -2;
                heights[first_position+1] = max_length;
            }
            //print the information when the position is not suitable.
            else
            {
                cout<<"the position is not suitable."<<endl;
            }
        }
        //Adding a 'J' with rotaion of 90 and it would affect three existed column.
        else if(rotation == 90)
        {
            //Judge the position we want to add the 'L' and if it is not compliant, print the error message.
            if(first_position>=0&&(first_position+2)<width)
            {
                 //There is only one situation when we add a 'J' with rotation of 90.
                //determine the new max height according to the three relevant columns.
                int max_length = 0;
                for(int i = 0 ; i< 3;i++)
                {
                    if(max_length < heights[first_position+i])
                    {
                        max_length = heights[first_position+i];
                    }
                }
                max_length = max_length +2;
                char *new_column1 = new char [max_length];
                char *new_column2 = new char[max_length-1];
                char *new_column3 = new char[max_length-1];
                
                //Add new data at the end of the new column.
                new_column1[max_length-1]='J'; new_column1[max_length-2]='J';new_column2[max_length-2]='J';new_column3[max_length-2]='J';
                for(int i = 0 ; i< heights[first_position];i++)
                {
                    new_column1[i] = data[first_position][i];
                }
                for(int i = heights[first_position] ; i< (max_length-2);i++)
                {
                    new_column1[i] = ' ';
                }
                for(int i = 0 ; i< heights[first_position+1];i++)
                {
                    new_column2[i] = data[first_position+1][i];
                }
                for(int i = heights[first_position+1] ; i< (max_length-2);i++)
                {
                    new_column2[i] = ' ';
                }
                for(int i = 0 ; i< heights[first_position+2];i++)
                {
                    new_column3[i] = data[first_position+2][i];
                }
                for(int i = heights[first_position+2] ; i< (max_length-2);i++)
                {
                    new_column3[i] = ' ';
                }
                //Copy the data and release the memory.
                delete []data[first_position]; delete []data[first_position+1]; delete []data[first_position+2];
                data[first_position] = new_column1;
                data[first_position+1] = new_column2;
                data[first_position+2] = new_column3;
                heights[first_position] = max_length;
                heights[first_position+1]=max_length-1;
                heights[first_position+2]=max_length-1;
            }
            //print the information when the position is not suitable.
            else
            {
                cout<<"the position is not suitable."<<endl;
            }
        }
        
        //Adding a 'L' with rotaion of 180 and it would affect 2 existed column.
        else if(rotation == 180)
        {
            //Judge the position we want to add the 'L' and if it is not compliant, print the error message.
            if(first_position>=0&&(first_position+1)<width)
            {
                //There are two situation when we want to add a 'J' with rotaion of 180.
                //First situation, second column's height is two or more more than the second column's height.The new max height is (heights[first_positi] +1)
                //Second situation, second column do not have the height that is 2 or more more than the second column's height.At this situation, the new max height is (heights[first_position] +3)
                
                //First situation.

                if((heights[first_position+1]-heights[first_position])>=2)
                {
                    int max_length = heights[first_position+1] +1;
                    char *new_column1 = new char [max_length];
                    char *new_column2 = new char [max_length];
                    new_column1[max_length-1] = 'J';new_column1[max_length-2] = 'J';new_column1[max_length-3] = 'J';
                    new_column2[max_length-1] = 'J';
                    for(int i = 0; i< heights[first_position];i++)
                    {
                        new_column1[i] = data[first_position][i];
                    }
                    for(int i = heights[first_position];i<(max_length-3);i++)
                    {
                        new_column1[i] = ' ';
                    }
                    for(int i = 0; i<heights[first_position+1];i++)
                    {
                        new_column2[i] = data[first_position+1][i];
                    }
                    delete []data[first_position]; delete []data[first_position+1];
                    data[first_position] = new_column1;
                    data[first_position+1] = new_column2;
                    heights[first_position] = max_length;
                    heights[first_position+1] = max_length;
                }
                
                //Second situation.
                else
                {
                    int max_length = heights[first_position]+3;
                    char *new_column1 = new char [max_length];
                    char *new_column2 = new char [max_length];
                    new_column1[max_length-1] = 'J';new_column1[max_length-2] = 'J';new_column1[max_length-3] = 'J';
                    new_column2[max_length-1] = 'J';
                    for(int i = 0; i< heights[first_position];i++)
                    {
                        new_column1[i] = data[first_position][i];
                    }
                    for(int i = 0; i<heights[first_position+1];i++)
                    {
                        new_column2[i] = data[first_position+1][i];
                    }
                    for(int i = heights[first_position+1];i<(max_length-1);i++)
                    {
                        new_column2[i] = ' ';
                    }
                    delete []data[first_position]; delete []data[first_position+1];
                    data[first_position] = new_column1;
                    data[first_position+1] = new_column2;
                    heights[first_position] = max_length;
                    heights[first_position+1] = max_length;
                }
            }
            //print the information when the position is not suitable.
            else
            {
                cout<<"the position is not suitable."<<endl;
            }
        }
        //Adding a 'J' with rotaion of 270 and it would affect three existed column.
        else if(rotation == 270)
        {
            //Judge the position we want to add the 'L' and if it is not compliant, print the error message.
            if(first_position>=0&&(first_position+2)<width)
            {
                //There are two situation when we want to add a 'J' with rotaion of 270.
                //First situation, last column has the max height and the new max height is (heights[first_position+2] +2)
                //Second situation, last column do not have the max height and the new max height is (heights[first_position+1] +1 or heights[first_position] +1)
                
                //First situation.
                if(heights[first_position+2]>=heights[first_position]&&heights[first_position+2]>=heights[first_position+1])
                {
                    int max_length = heights[first_position+2] + 2;
                    char *new_column1 = new char [max_length];
                    char *new_column2 = new char [max_length];
                    char *new_column3 = new char [max_length];
                    new_column1[max_length-1] = 'J';new_column2[max_length-1] = 'J';
                    new_column3[max_length-1] = 'J';new_column3[max_length-2] = 'J';
                    for(int i = 0; i<heights[first_position];i++)
                    {
                        new_column1[i] = data[first_position][i];
                    }
                    for(int i = heights[first_position]; i < (max_length-1);i++)
                    {
                        new_column1[i] = ' ';
                    }
                    for(int i = 0; i<heights[first_position+1];i++)
                    {
                        new_column2[i] = data[first_position+1][i];
                    }
                    for(int i = heights[first_position+1]; i < (max_length-1);i++)
                    {
                        new_column2[i] = ' ';
                    }
                    for(int i = 0; i<heights[first_position+2];i++)
                    {
                        new_column3[i] = data[first_position+2][i];
                    }
                    delete []data[first_position]; delete []data[first_position+1];delete []data[first_position+2];
                    data[first_position] = new_column1;
                    data[first_position+1] = new_column2;
                    data[first_position+2] = new_column3;
                    heights[first_position] = max_length;
                    heights[first_position+1] = max_length;
                    heights[first_position+2] = max_length;
                }
                
                //Second situation.
                else
                {
                    int max_length = 0;
                    if(heights[first_position]<heights[first_position+1])
                    {
                        max_length = heights[first_position+1];
                    }
                    else
                    {
                        max_length = heights[first_position];
                    }
                    max_length = max_length +1;
                    char *new_column1 = new char [max_length];
                    char *new_column2 = new char [max_length];
                    char *new_column3 = new char [max_length];
                    new_column1[max_length-1] = 'J';new_column2[max_length-1] = 'J';
                    new_column3[max_length-1] = 'J';new_column3[max_length-2] = 'J';
                    for(int i = 0; i<heights[first_position];i++)
                    {
                        new_column1[i] = data[first_position][i];
                    }
                    for(int i = heights[first_position]; i < (max_length-1);i++)
                    {
                        new_column1[i] = ' ';
                    }
                    for(int i = 0; i<heights[first_position+1];i++)
                    {
                        new_column2[i] = data[first_position+1][i];
                    }
                    for(int i = heights[first_position+1]; i < (max_length-1);i++)
                    {
                        new_column2[i] = ' ';
                    }
                    for(int i = 0; i<heights[first_position+2];i++)
                    {
                        new_column3[i] = data[first_position+2][i];
                    }
                    for(int i = heights[first_position+2]; i < (max_length-2);i++)
                    {
                        new_column3[i] = ' ';
                    }
                    delete []data[first_position]; delete []data[first_position+1];delete []data[first_position+2];
                    data[first_position] = new_column1;
                    data[first_position+1] = new_column2;
                    data[first_position+2] = new_column3;
                    heights[first_position] = max_length;
                    heights[first_position+1] = max_length;
                    heights[first_position+2] = max_length;

                }
            }
             //print the information when the position is not suitable.
            else
            {
                cout<<"the position is not suitable."<<endl;
            }
        }
        //If the rotation do not meet the requirement,show the following message.
        else
        {
            cout<<"Input the wrong rotation."<<endl;
        }
    }
    //If the shape do not meet the requirement,show the following message.
    else
    {
        cout<<"add the wrong shape, please check"<<endl;
    }
}

// get the width
int Tetris::get_width() const
{
    return width;
}

//get max height.
int Tetris::get_max_height() const
{
    int max_length = 0;
    for(int i = 0; i< width; i++)
    {
        if(max_length <= heights[i])
        {
            max_length = heights[i];
        }
    }
    return max_length;
}

//cout how many elements stored in the data.
int Tetris::count_squares()
{
    int count_squares = 0;
    for (int i = 0 ; i < width ; i++)
    {
        for(int j = 0 ; j < heights[i]; j++)
        {
            if(data[i][j] != ' ')
            {
                count_squares = count_squares + 1;
            }
        }
    }
    return count_squares;
}

//remove_full_rows.
int Tetris::remove_full_rows()
{
    //determine the max height among the all columns.
    int max_height = 0;
    int score = 0;
    for(int i = 0; i<width;i++)
    {
        if(max_height<=heights[i])
        {
            max_height = heights[i];
        }
    }
    
    //At first, we should judge each row of the board, from top to bottom, so that we can know if the row is full of the elements.
    for(int i = max_height;i >0;i--)
    {
        //First situation, if there is one column's height is less than the max_height, this row could not be full of the elements.
        //So we do not need to do other judgement just stop the function here and excute i--.
        
        //use a bool variable is_height_enough to record if there is one column's height is less than the max_height.
        bool is_height_enough = false;
        for(int j = 0; j<width;j++)
        {
            if(heights[j]<i)
            {
                is_height_enough = true;
            }
        }
        
        //If there is no one column's height is less than the max_height,this row is possiblely be filled with element.
        if(!is_height_enough)
        {
                //If this row has the element that is space character, we should not remove it.So we need to judge if this row has space character.
                //Use a bool variable is_null to record the result.
                bool is_null = false;
                int k=0;
                while( !is_null && k<width)
                {
                    if(data[k][i-1] == ' ')
                    {
                        is_null = true;
                    }
                    k = k+1;
                }
            
                //If this row do not have space character, it should be a full row, so we need to remove it.
                if(!is_null)
                {
                    //We should create n (n = width) new column to store the old column's data after remove one element from it.
                    for(int l = 0 ; l < width ; l++)
                    {
                        char *new_column = new char[heights[l]-1];
                        for(int m = 0; m<(i-1);m++)
                        {
                            new_column[m] = data[l][m];
                        }
                        
                        //each element after the element we remove should move forward one position.
                        for(int n = (i-1);n <(heights[l]-1);n++)
                        {
                            new_column[n] = data[l][n+1];
                        }
                        //Releasing the memory and record the change we make.
                        delete[]data[l];
                        heights[l] = heights[l] -1;
                        data[l] = new_column;
                        bool is_empty = false;
                        
                        //After we removed one row and move the data, some other "wrong" situation might happen. For example, the last element of one column is a space
                        //character. At that situation, we should remove the space character. So we use a bool variable to record if last element is a space character.
                        while(!is_empty)
                        {
                            // If heights[l] = 0, it means that this column do no have anything, so we should reset the relevant and make the data pointer point NULL.
                            //If heights[l] != 0, we should judge the last element.
                            if(heights[l] != 0)
                            {
                                //If last element is equal to space character, we remove it and record the change.
                                if(data[l][heights[l]-1] == ' ' )
                                {
                                    char *new_columns = new char[heights[l]-1];
                                    for(int w = 0 ; w< (heights[l]-1);w ++)
                                    {
                                        new_columns[w] = data[l][w];
                                    }
                                    delete[]data[l];
                                    heights[l] = heights[l] -1;
                                    data[l] = new_columns;
                                }
                                else
                                {
                                    is_empty = true;
                                }
                            }
                            else
                            {
                                delete []data[l];
                                data[l] = NULL;
                                is_empty = true;
                            }
                        }
                    }
                    score = score + 1;
                }
        }
    }
    return score;
}

void Tetris::add_left_column()
{
    //create new_heights and new_data as temporary variable to store the old data
    int *new_heights = new int[width+1];
    char **new_data = new char *[width+1];
    new_heights[0] = 0;
    new_data[0] = NULL;
    for(int i =0; i<width;i++)
    {
        new_heights[i+1] = heights[i];
    }
    for(int i = 0; i<width;i++)
    {
        new_data[i+1] = data[i];
    }
    //reset the data pointer,making it point to the new column and also release the old heap memory.
    delete []data;
    delete []heights;
    heights = new_heights;
    data = new_data;
    width = width +1;
    
    
}

void Tetris::add_right_column()
{
    int *new_heights = new int[width+1];
    char **new_data = new char *[width+1];
    new_heights[width] = 0;
    new_data[width] = NULL;
    for(int i = 0; i<width;i++)
    {
        new_heights[i] = heights[i];
    }
    for(int i =0 ;i<width;i++)
    {
        new_data[i] = data[i];
    }
    delete []data;
    delete []heights;
    heights = new_heights;
    data = new_data;
    width = width +1;

}

void Tetris::remove_left_column()
{
    if( width > 0)
    {
        int *new_heights =new int[width-1];
        char **new_data = new char *[width-1];
        for(int i =0;i<(width-1);i++)
        {
            new_heights[i] = heights[i+1];
        }
        for(int i = 0; i<(width-1);i++)
        {
            new_data[i] = data[i+1];
        }
        
        //We should also release the memory used for the column we romove.
        delete []data[0];
        delete []data;
        delete []heights;
        heights = new_heights;
        data = new_data;
        width = width-1;
    }
    else
    {
        cout<<"The width is already 0, there is no another column can be removed:"<<endl;
    }
    

}

void Tetris::remove_right_column()
{
    if(width > 0)
    {
        int *new_heights =new int[width-1];
        char **new_data = new char *[width-1];
        for(int i =0;i<(width-1);i++)
        {
            new_heights[i] = heights[i];
        }
        for(int i = 0; i<(width-1);i++)
        {
            new_data[i] = data[i];
        }
         //We should also release the memory used for the column we romove.
        delete []data[width-1];
        delete []data;
        delete []heights;
        heights = new_heights;
        data = new_data;
        width = width-1;
    }
    else
    {
        cout<<"The width is already 0, there is no another column can be removed:"<<endl;
    }
}

//Releasing the heap memory and avoid the memory leak.
void Tetris::destroy()
{
    delete[] heights;
    for(int i = 0 ; i< width; i++)
    {
        delete []data[i];
    }
    delete []data;
};
































