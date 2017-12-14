//
//  main.m
//  472_Assignment3_Question2
//
//  Created by Peter El Jiz on 2012-11-02.
//  Copyright (c) 2012 Peter El Jiz. All rights reserved.
//

#import <Foundation/Foundation.h>
//#import <cmath>

int main(int argc, const char * argv[])
{
    char trainingset[100][17] = {};
        
    //NSString *path = [[NSBundle mainBundle] pathForResource:@"4x4digits" ofType:@"txt"];
    NSString *path = [NSString stringWithFormat:@"/Users/Peter/Xcode Projects/472_Assignment3_Question2/472_Assignment3_Question2/trainingset.txt"];
    NSString *content = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:nil];
    
    if (content == nil)
    {
        NSLog(@"\nError reading file at \n%@", path);
        //return -1;
    }

    
    // first, separate by new line
    NSArray *allLinedStrings = [content componentsSeparatedByCharactersInSet:[NSCharacterSet newlineCharacterSet]];
    
    
    for (int i = 1; i < [allLinedStrings count]; i++)
    {
        // then break down even further
        NSString *strsInOneLine = [allLinedStrings objectAtIndex:i];
        
        // choose whatever input identity you have decided. in this case ;
        NSArray *singleStrs = [strsInOneLine componentsSeparatedByCharactersInSet: [NSCharacterSet characterSetWithCharactersInString:@"\t"]];
        
        for (int j = 0; j < [singleStrs count]; j++)
        {
            // then break down into characters
            NSString *character = [singleStrs objectAtIndex:j];
            
            trainingset[i-1][j] = [character UTF8String][0];

            
        }

    }

    
    
    
    printf("Training Set:\n");
    for (int i = 0; i < 100; ++i)
    {
        for (int j = 0; j < 17; ++j)
        {
            printf("%c\t", trainingset[i][j]);

        }
        if ((i == 9) || (i == 19) || (i == 29) || (i == 39) || (i == 49) || (i == 59) || (i == 69) || (i == 79) || (i == 89) || (i == 99))
            printf("\n");
        printf("\n");

    }
    
    
    
    
    //calculate probability of f1|c0, f1|c1, f1|c2,....till f1|c9
    //calculate probability of f2|c0, f2|c1, f2|c2,....till f2|c9
    //....
    //calculate probability of f16|c0, f16|c1, f16|c2,....till f16|c9
    
    double probabilities[10][17]; //probability[row][column] = probability of that element being a BLACK represents the probability of having f1-16 for document c0 till c9;
    //for all classes ci 0-9
    //for all tiles fj (1-16) for that class of number
    //compute p(fj | ci)
    
    
    int blackcount = 0;
    int index = 0;
    
    for (int j = 0; j < 16; j++)
    {
        
        for (int i = 0; i < 100; i++)
        {
            if (trainingset[i][j] == 'B')
                ++blackcount;
            
            if (i %10 == 9)//((i == 9) || (i == 19) || (i == 29) || (i == 39) || (i == 49) || (i == 59) || (i == 69) || (i == 79) || (i == 89) || (i == 99))
            {
                //printf("\nAt Package: %i\n", i);
                
                double K = 0.5; //smoothing
                
                probabilities[i/10][j] = ((double) (blackcount) + K)/(10 + K*10);
                blackcount = 0;
            }
            
        }
    }
    
    for (int i = 0; i < 10; ++i)
    {
        probabilities[i][16] = i;
    }
    
    printf("\n\n\nProbabilities:\n");
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 17; ++j)
        {
            if (j != 16)
                printf("%.2f\t", probabilities[i][j]);
            else
                printf("%i", ((int) probabilities[i][j]));
            
        }
        printf("\n");
        
    }
    
    
    
    
    
    
    
    
    //TEST SET
    char testset[3][17] = {};
    
    //NSString *path = [[NSBundle mainBundle] pathForResource:@"4x4digits" ofType:@"txt"];
    NSString *path2 = [NSString stringWithFormat:@"/Users/Peter/Xcode Projects/472_Assignment3_Question2/472_Assignment3_Question2/testset.txt"];
    NSString *content2 = [NSString stringWithContentsOfFile:path2 encoding:NSUTF8StringEncoding error:nil];
    
    if (content2 == nil)
    {
        NSLog(@"\nError reading file at \n%@", path2);
        //return -1;
    }
    
    
    // first, separate by new line
    NSArray *allLinedStrings2 = [content2 componentsSeparatedByCharactersInSet:[NSCharacterSet newlineCharacterSet]];
    
    
    for (int i = 1; i < [allLinedStrings2 count]; i++)
    {
        // then break down even further
        NSString *strsInOneLine2 = [allLinedStrings2 objectAtIndex:i];
        
        // choose whatever input identity you have decided. in this case ;
        NSArray *singleStrs2 = [strsInOneLine2 componentsSeparatedByCharactersInSet: [NSCharacterSet characterSetWithCharactersInString:@"\t"]];
        
        for (int j = 0; j < [singleStrs2 count]; j++)
        {
            // then break down into characters
            NSString *character = [singleStrs2 objectAtIndex:j];
            
            testset[i-1][j] = [character UTF8String][0];
            
            
        }
        
    }
    
    
    
    /*
    printf("\n\n\nTest Set:\n");
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 17; ++j)
        {
            printf("%c\t", testset[i][j]);
            
        }

        printf("\n");
        
    }
    */
    
    
    
    
    
    
    
    
    
    
    
    
    //Know that we have computed the probabilities P(fj | Ci) ...the probability of blacks in column fj knowing the digit Ci,
    //we compute the probabilities of Ci, Ci+1...etc (ie: 0, 1, 2, 3 etc)
    
    //Out of 100 data instances, there are 10 test values for each digit (ie: for 0, there are 10 rows; for 1, there are 10 rows...etc up until 9...10 rows)
    
    //So the probability for each digit to occur is equally distributed ===> P(C0) = P (C1) = P(C2) = ... = P(C9) = 10/100 = 1/10;
    //P(Ci) = 1/10 for all i.
    
    //We're going to calculate the probabilities using the logs
    //The scoring function goes as follows: Score(Ci) = log(P(Ci)) + sigma log(fj | Ci)    [fj being the values that appear in the testing set]
    
    double scoreForNumber1[10];//{0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
    double scoreForNumber2[10];//{0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
    double scoreForNumber3[10];//{0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};


    
    //Score(Digit = 0) = P(X | digit = 0) * P(Digit = 0)
    //Score(Digit = 1) = P(X | digit = 0) * P(Digit = 1)
    //....
    //with P(X | Digit = 0) = P(f1 = B | Digit = 0) * P(f2 = B | Digit = 0) * P(f3 = B | Digit = 0) * P(f4 = B | Digit = 0) * P(f5 = B | Digit = 0) * P(f6 = B | Digit = 0) * P(f7 = W | Digit = 0) * P(f8 = W | Digit = 0) * P(f9 = W | Digit = 0) * P(f10 = W | Digit = 0) * P(f11 = B | Digit = 0) * P(f12 = W | Digit = 0) * P(f13 = B | Digit = 0) * P(f14 = B | Digit = 0) * P(f15 = B | Digit = 0) * P(f16 = W | Digit = 0)
    
    //But there is a better way to compute the score function.
    //Score(Digit = 0) = log(P(Digit = 0)) + sigma log(P(f# = Character | Digit = 0))
    
    
    for (int i = 0; i < 10; ++i)
    {
        scoreForNumber1[i] = log(0.1); //log((10/100));
        for (int j = 0; j < 16; ++j)
        {
            double probability = probabilities[i][j];
            
            if (testset[0][j] == 'W')
                probability = 1 - probability;
            scoreForNumber1[i] += log(probability);
        }
    }
    
    for (int i = 0; i < 10; ++i)
    {
        scoreForNumber2[i] = log(0.1); //log((10/100));
        for (int j = 0; j < 16; ++j)
        {
            double probability = probabilities[i][j];
            
            if (testset[1][j] == 'W')
                probability = 1 - probability;
            scoreForNumber2[i] += log(probability);
        }
    }
    
    for (int i = 0; i < 10; ++i)
    {
        scoreForNumber3[i] = log(0.1); //log((10/100));
        for (int j = 0; j < 16; ++j)
        {
            double probability = probabilities[i][j];
            
            if (testset[2][j] == 'W')
                probability = 1 - probability;
            scoreForNumber3[i] += log(probability);
        }
    }
    
    
    printf("\n\n\n\nScores for Number 1:\n");
    
    for (int i = 0; i < 10; ++i)
    {
        printf("%.2f\t", scoreForNumber1[i]);
    }
    
    printf("\n\nScores for Number 2:\n");
    
    for (int i = 0; i < 10; ++i)
    {
        printf("%.2f\t", scoreForNumber2[i]);
    }
    
    printf("\n\nScores for Number 3:\n");
    
    for (int i = 0; i < 10; ++i)
    {
        printf("%.2f\t", scoreForNumber3[i]);
    }
    
    
    //find the highest value for number 1
    double highestValue1 = scoreForNumber1[0];
    double highestValue2 = scoreForNumber2[0];
    double highestValue3 = scoreForNumber3[0];
    
    int highestNumber1 = 0;
    int highestNumber2 = 0;
    int highestNumber3 = 0;
    
    for (int i = 0; i < 10; ++i)
    {
        if (scoreForNumber1[i] > highestValue1)
        {
            highestValue1 = scoreForNumber1[i];
            highestNumber1 = i;
        }
    }
    
    //find the highest value for number 1
    for (int i = 0; i < 10; ++i)
    {
        if (scoreForNumber2[i] > highestValue2)
        {
            highestValue2 = scoreForNumber2[i];
            highestNumber2 = i;
        }
    }
    
    //find the highest value for number 1
    for (int i =0; i < 10; ++i)
    {
        if (scoreForNumber3[i] > highestValue3)
        {
            highestValue3 = scoreForNumber3[i];
            highestNumber3 = i;
        }
    }
    
    //printf("\n\n\nDigit1 is: %i\n", highestNumber1);
    //printf("\nDigit2 is: %i\n", highestNumber2);
    //printf("\nDigit3 is: %i\n", highestNumber3);
    
    
    testset[0][16] = highestNumber1 + '0';
    testset[1][16] = highestNumber2 + '0';
    testset[2][16] = highestNumber3 + '0';
    
    
    printf("\n\n\nTest Set:\n");
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 17; ++j)
        {
            printf("%c\t", testset[i][j]);
            
        }
        
        printf("\n");
        
    }
    
    
    return 0;
    
}

