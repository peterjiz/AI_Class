//
//  main.cpp
//  472_Assignment4_CplusplusVersion
//
//  Created by Peter El Jiz on 2012-11-02.
//  Copyright (c) 2012 Peter El Jiz. All rights reserved.
//

#include <iostream>
#include <stdio.h>

#include <fstream>
#include <string>


#include <iostream>

//String Stream
#include <sstream>

//String
#include <string>

#include <math.h>


using namespace std;

int main(int argc, const char * argv[])
{
    //The N array will be used to store each character's number of occurences as character 1.
    
    double englishModel[26][26] = {};
    double englishN[26] = {};
    
    double frenchModel[26][26] = {};
    double frenchN[26] = {};
    
    double italianModel[26][26] = {};
    double italianN[26] = {};
    
    
    //Characters A to Z will be represented numerically from 0 to 25.
    
    //Processing English File
    
    // first, separate by new line
    std::ifstream file("/Users/Peter/Xcode Projects/472_Assignment4/472_Assignment4/english.txt");
    std::string line;
    while(std::getline(file, line))
    {
        // then break down even further
        stringstream parser (line);
        string word;
        
        while(parser >> word)
        {
            // then break down into characters
            if (word.length() >= 0)
            {
                char *temp;
                
                //Convert from String (C++ type) to C-style string (char array), to better perform operations.
                unsigned long length = word.length() + 1; // word.length + 1, to make space for end of char array '\0'. or ASCII code = 0;
                temp = new char[length];
                strcpy(temp, word.c_str());
                                
                //Convert word from case-sensitive to lowercase, ignoring punctuation
                for(int i=0; temp[i]; i++)
                    if(temp[i]>='A' && temp[i]<='Z') //if character is upper-case, convert to lowercase by adding +32 to characters.
                        temp[i] += 32;
                    else
                        if ( (temp[i] >= 'a' && temp[i] <= 'z') || (temp[i] == '+' || temp[i] == '-') )
                            ;
                        else
                            temp[i] = 0; //if character is anything else not ranging from 'A' to 'Z', nor from 'a' to 'z', then mark our array as the end of the array.
                
                word = "";
                
                for(unsigned long l = 0; ( l < length); l++) //convert back from C-style string to C++ String, ignoring punctuation
                {
                    
                    if (temp[l] != 0)
                        word += temp[l];
                }
                
                
                delete[] temp;
                
                for (int k = 1; k < word.length(); k++)
                {
                    char c1 = word.c_str()[k-1];
                    char c2 = word.c_str()[k];
                    
                    //selecting specific characters, A-Z and a-z, remaining characters will be discarded
                    if ((c1 >= 'a' && c1 <= 'z') || (c1 >= 'A' && c1 <= 'Z'))
                        if ((c2 >= 'a' && c2 <= 'z') || (c2 >= 'A' && c2 <= 'Z'))
                        {
                            //VALID CHARACTERS
                            
                            //changing to lowercase...etc
                            if ( (c1 >= 'a') && (c1 <= 'z'))
                            {
                                c1 = (char) (((int) c1) - 32);
                            }
                            
                            if ( (c2 >= 'a') && (c2 <= 'z'))
                            {
                                c2 = (char) (((int) c2) - 32);
                            }
                            
                            
                            //get respective indices for the model table/array
                            int c1INDEX = c1 - 65;
                            int c2INDEX = c2 - 65;
                            //englishModel[c1][c2] = ;// some value
                            englishModel[c1INDEX][c2INDEX]++;
                            englishN[c1INDEX]++;
                            
                            
                        }
                    
                    //ELSE INVALID CHARACTERS
                    
                    
                    
                }
                
            }
        }
    }
    file.close();
    
    
    
    //ADD-DELTA Smoothing
    for (int i = 0; i < 26; i++) //row
    {
        for (int j = 0; j < 26; j++) //column
        {
            double lambda = 0.5;
            double B = 26*26;
            englishModel[i][j] = (englishModel[i][j] + lambda)/(englishN[i] + lambda*B); // applying this formula (C (w1 w2 ...wn) + δ) / (N+δB)
        }
    }
    
    
    
    
    //Processing French File
    
    file.open("/Users/Peter/Xcode Projects/472_Assignment4/472_Assignment4/french.txt");
    while(std::getline(file, line))
    {
        // then break down even further
        stringstream parser (line);
        string word;
        
        while(parser >> word)
        {
            // then break down into characters
            if (word.length() >= 0)
            {
                char *temp;
                
                //Convert from String (C++ type) to C-style string (char array), to better perform operations.
                unsigned long length = word.length() + 1; // word.length + 1, to make space for end of char array '\0'. or ASCII code = 0;
                temp = new char[length];
                strcpy(temp, word.c_str());
                                
                //Convert word from case-sensitive to lowercase, ignoring punctuation
                for(int i=0; temp[i]; i++)
                    if(temp[i]>='A' && temp[i]<='Z') //if character is upper-case, convert to lowercase by adding +32 to characters.
                        temp[i] += 32;
                    else
                        if ( (temp[i] >= 'a' && temp[i] <= 'z') || (temp[i] == '+' || temp[i] == '-') )
                            ;
                        else
                            temp[i] = 0; //if character is anything else not ranging from 'A' to 'Z', nor from 'a' to 'z', then mark our array as the end of the array.
                
                word = "";
                
                for(unsigned long l = 0; ( l < length); l++) //convert back from C-style string to C++ String, ignoring punctuation
                {
                    
                    if (temp[l] != 0)
                        word += temp[l];
                }
                //                word2 += temp[i];
                
                
                delete[] temp;
                
                
                for (int k = 1; k < word.length(); k++)
                {
                    char c1 = word.c_str()[k-1];
                    char c2 = word.c_str()[k];
                    
                    //selecting specific characters, A-Z and a-z, remaining characters will be discarded
                    if ((c1 >= 'a' && c1 <= 'z') || (c1 >= 'A' && c1 <= 'Z'))
                        if ((c2 >= 'a' && c2 <= 'z') || (c2 >= 'A' && c2 <= 'Z'))
                        {
                            //VALID CHARACTERS
                            
                            //changing to lowercase...etc
                            if ( (c1 >= 'a') && (c1 <= 'z'))
                            {
                                c1 = (char) (((int) c1) - 32);
                            }
                            
                            if ( (c2 >= 'a') && (c2 <= 'z'))
                            {
                                c2 = (char) (((int) c2) - 32);
                            }
                            
                            
                            //get respective indices for the model table/array
                            int c1INDEX = c1 - 65;
                            int c2INDEX = c2 - 65;
                            //englishModel[c1][c2] = ;// some value
                            frenchModel[c1INDEX][c2INDEX]++;
                            frenchN[c1INDEX]++;
                            
                            
                            
                        }
                    
                    //ELSE INVALID CHARACTERS
                    
                    
                    
                }
            }
            
            
        }
    }
    file.close();
    
    
    //ADD-DELTA Smoothing
    for (int i = 0; i < 26; i++) //row
    {
        for (int j = 0; j < 26; j++) //column
        {
            double lambda = 0.5;
            double B = 26*26;
            frenchModel[i][j] = (frenchModel[i][j] + lambda)/(frenchN[i] + lambda*B); // applying this formula (C (w1 w2 ...wn) + δ) / (N+δB)
        }
    }
    
    
    
    
    //Processing Italian File
    
    file.open("/Users/Peter/Xcode Projects/472_Assignment4/472_Assignment4/italian.txt");
    while(std::getline(file, line))
    {
        // then break down even further
        stringstream parser (line);
        string word;
        
        while(parser >> word)
        {
            // then break down into characters
            if (word.length() >= 0)
            {
                char *temp;
                
                //Convert from String (C++ type) to C-style string (char array), to better perform operations.
                unsigned long length = word.length() + 1; // word.length + 1, to make space for end of char array '\0'. or ASCII code = 0;
                temp = new char[length];
                strcpy(temp, word.c_str());
                                
                //Convert word from case-sensitive to lowercase, ignoring punctuation
                for(int i=0; temp[i]; i++)
                    if(temp[i]>='A' && temp[i]<='Z') //if character is upper-case, convert to lowercase by adding +32 to characters.
                        temp[i] += 32;
                    else
                        if ( (temp[i] >= 'a' && temp[i] <= 'z') || (temp[i] == '+' || temp[i] == '-') )
                            ;
                        else
                            temp[i] = 0; //if character is anything else not ranging from 'A' to 'Z', nor from 'a' to 'z', then mark our array as the end of the array.
                
                word = "";
                
                for(unsigned long l = 0; ( l < length); l++) //convert back from C-style string to C++ String, ignoring punctuation
                {
                    //if (i > l)
                    //  break;
                    
                    if (temp[l] != 0)
                        word += temp[l];
                }
                //                word2 += temp[i];
                
                
                delete[] temp;
                
                
                for (int k = 1; k < word.length(); k++)
                {
                    char c1 = word.c_str()[k-1];
                    char c2 = word.c_str()[k];
                    
                    //selecting specific characters, A-Z and a-z, remaining characters will be discarded
                    if ((c1 >= 'a' && c1 <= 'z') || (c1 >= 'A' && c1 <= 'Z'))
                        if ((c2 >= 'a' && c2 <= 'z') || (c2 >= 'A' && c2 <= 'Z'))
                        {
                            //VALID CHARACTERS
                            
                            //changing to lowercase...etc
                            if ( (c1 >= 'a') && (c1 <= 'z'))
                            {
                                c1 = (char) (((int) c1) - 32);
                            }
                            
                            if ( (c2 >= 'a') && (c2 <= 'z'))
                            {
                                c2 = (char) (((int) c2) - 32);
                            }
                            
                            
                            //get respective indices for the model table/array
                            int c1INDEX = c1 - 65;
                            int c2INDEX = c2 - 65;
                            //englishModel[c1][c2] = ;// some value
                            italianModel[c1INDEX][c2INDEX]++;
                            italianN[c1INDEX]++;
                            
                            
                            
                        }
                    
                    //ELSE INVALID CHARACTERS
                    
                    
                    
                }
            }
            
        }
    }
    
    //ADD-DELTA Smoothing
    for (int i = 0; i < 26; i++) //row
    {
        for (int j = 0; j < 26; j++) //column
        {
            double lambda = 0.5;
            double B = 26*26;
            italianModel[i][j] = (italianModel[i][j] + lambda)/(italianN[i] + lambda*B); // applying this formula (C (w1 w2 ...wn) + δ) / (N+δB)
        }
    }
    
    
    printf("Enter a sentence: ");
    
    
    char sentence[600];
    fgets(sentence, 600, stdin);
    sentence[599] = 0;
    
    printf("%s", sentence);
    
    
    double probabilityScoreEnglish;
    double probabilityScoreFrench;
    double probabilityScoreItalian;
    
    
    // then break down even further
    stringstream parser (sentence);
    string word;
    
    while(parser >> word)
    {
        // then break down into characters
        if (word.length() >= 0)
        {
            printf("\nCurrent Word: %s\n", word.c_str());
            
            char *temp;
            
            //Convert from String (C++ type) to C-style string (char array), to better perform operations.
            unsigned long length = word.length() + 1; // word.length + 1, to make space for end of char array '\0'. or ASCII code = 0;
            temp = new char[length];
            strcpy(temp, word.c_str());
                        
            //Convert word from case-sensitive to lowercase, ignoring punctuation
            for(int i=0; temp[i]; i++)
                if(temp[i]>='A' && temp[i]<='Z') //if character is upper-case, convert to lowercase by adding +32 to characters.
                    temp[i] += 32;
                else
                    if ( (temp[i] >= 'a' && temp[i] <= 'z') || (temp[i] == '+' || temp[i] == '-') )
                        ;
                    else
                        temp[i] = 0; //if character is anything else not ranging from 'A' to 'Z', nor from 'a' to 'z', then mark our array as the end of the array.
            
            word = "";
            
            for(unsigned long l = 0; ( l < length); l++) //convert back from C-style string to C++ String, ignoring punctuation
            {
                //if (i > l)
                //  break;
                
                if (temp[l] != 0)
                    word += temp[l];
            }
            //                word2 += temp[i];
            
            
            delete[] temp;
            
            
            
            for (int k = 1; k < word.length(); k++)
            {
                
                char c1 = (char) (word.c_str()[k-1]);
                char c2 = (char) (word.c_str()[k]);
                
                //printf("\nc1 = %c \t c2 = %c\n", c1, c2);
                
                //selecting specific characters, A-Z and a-z, remaining characters will be discarded
                if ((c1 >= 'a' && c1 <= 'z') || (c1 >= 'A' && c1 <= 'Z'))
                {
                    if ((c2 >= 'a' && c2 <= 'z') || (c2 >= 'A' && c2 <= 'Z'))
                    {
                        //VALID CHARACTERS
                        
                        //changing to lowercase...etc
                        if ( (c1 >= 'a') && (c1 <= 'z'))
                        {
                            c1 = (char) (((int) c1) - 32);
                        }
                        
                        if ( (c2 >= 'a') && (c2 <= 'z'))
                        {
                            c2 = (char) (((int) c2) - 32);
                        }
                        
                        
                        //get respective indices for the model table/array
                        int c1INDEX = c1 - 65;
                        int c2INDEX = c2 - 65;
                        
                        printf("\nBIGRAM: %c%c\n", c1, c2);
                        probabilityScoreEnglish += log(englishModel[c1INDEX][c2INDEX]);
                        probabilityScoreFrench += log(frenchModel[c1INDEX][c2INDEX]);
                        probabilityScoreItalian += log(italianModel[c1INDEX][c2INDEX]);
                        
                        printf("French:  P(%c, %c) = %f ===> log probability of sequence so far: %f \n", c1, c2, frenchModel[c1INDEX][c2INDEX], probabilityScoreFrench);
                        printf("English:  P(%c, %c) = %f ===> log probability of sequence so far: %f \n", c1, c2, englishModel[c1INDEX][c2INDEX], probabilityScoreEnglish);
                        printf("Italian:  P(%c, %c) = %f ===> log probability of sequence so far: %f \n", c1, c2, italianModel[c1INDEX][c2INDEX], probabilityScoreItalian);
                        
                        
                    }
                    
                    //ELSE INVALID CHARACTERS
                }
                
                
            }
        }
        
    }
    
    string highest;
    
    if (probabilityScoreEnglish > probabilityScoreFrench)
    {
        highest = "English";
        
        if (probabilityScoreEnglish > probabilityScoreItalian)
            highest = "English";
        else
            highest = "Italian";
    }
    else
    {
        if (probabilityScoreFrench > probabilityScoreItalian)
            highest = "French";
        else
            highest = "Italian";
    }
    
    printf("\n\nThis sentence is most probably in: %s", highest.c_str());
    
    
    
    
    
}