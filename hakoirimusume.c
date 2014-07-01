//
//  main.c
//  hakoirimusume
//
//  Created by UCHIDAYUTA on 2014/6/9.
//  Copyright (c) 2014 YUT. All rights reserved.
//

#include<stdio.h>

int check_can_move(int blockCount);
int check_in_frame(int blockCount);
int check_range(int mpositiony, int mpositionx);
int check_empty(int blockCount);

int *temp[5];
int *mtemp[5];
int positiony[5] = {0,0,0,0,0};
int positionx[5] = {0,0,0,0,0};
int mpositiony[5] = {0,0,0,0,0};
int mpositionx[5] = {0,0,0,0,0};


int main(void)
{
    int board[6][5] = {
          { 0,  0,  0,  0,  0}
    	, { 0,  1,  2,  2,  3}
        , { 0,  1,  2,  2,  3}
        , { 0,  4,  5,  5,  6}
        , { 0,  4,  8,  9,  6}
        , { 0,  7,  0,  0, 10}};
    char direction[2];
    int select_block = 0;
    
    printf("   p\n");
    printf("   ↑\n");
    printf("b ← → f\n");
    printf("   ↓\n");
    printf("   n\n");
    printf("\n");
    
    int blockCount;
	int updown;
	int side;
    
    while(1) {
        updown = 0;
        side = 0;
        blockCount = 0;
        for (int i = 0; i <= 5; ++i)
        {
        	positiony[i] = 0;
        	positionx[i] = 0;
        	mpositiony[i] = 0;
        	mpositionx[i] = 0;
        	temp[i] = 0;
        	mtemp[i] = 0;
		}

    	printf(" %2d  %2d  %2d  %2d\n"  , board[1][1], board[1][2], board[1][3], board[1][4]);
    	printf(" %2d  %2d  %2d  %2d\n"  , board[2][1], board[2][2], board[2][3], board[2][4]);
    	printf(" %2d  %2d  %2d  %2d\n"  , board[3][1], board[3][2], board[3][3], board[3][4]);
    	printf(" %2d  %2d  %2d  %2d\n"  , board[4][1], board[4][2], board[4][3], board[4][4]);
    	printf(" %2d  %2d  %2d  %2d\n\n", board[5][1], board[5][2], board[5][3], board[5][4]);
        
		printf("Please select position.\n");
		scanf("%d" , &select_block);
        
        // 動かすブロックの"左上"の位置を取得
		for (int y = 1; y <= 5; y++)
		{
			for (int x = 1; x <= 4; x++)
			{
				if (board[y][x] == select_block)
				{
					positiony[1] = y;
					positionx[1] = x;
                    y = 6;
                    x = 5;
				}
			}
		}
        
        // 同一ブロックの位置を取得
        switch (select_block) {
        	case 2:
        		// 2x2ブロック
        		blockCount = 4;
        		positiony[2] = positiony[1];
				positionx[2] = positionx[1] + 1;
				positiony[3] = positiony[1] + 1;
				positionx[3] = positionx[1];
				positiony[4] = positiony[1] + 1;
				positionx[4] = positionx[1] + 1;
        		break;
        	case 1:
        	case 3:
        	case 4:
        	case 6:
        		// 2x1ブロック
        		blockCount = 2;
        		positiony[2] = positiony[1] + 1;
				positionx[2] = positionx[1];
        		break;
        	case 5:
        		// 1x2ブロック
        		blockCount = 2;
        		positiony[2] = positiony[1];
				positionx[2] = positionx[1] + 1;
        		break;
        	case 7:
        	case 8:
        	case 9:
        	case 10:
        		// 1x1ブロック
        		blockCount = 1;
        		break;
        }
        
		printf("Please select a direction.\n");
    	scanf("%s" , direction);
        
	    switch (direction[0]) {
	    	case 'f':
	    		updown = 0;
	    		side = 1;
	    		break;
	    	case 'b':
	    		updown = 0;
	    		side = -1;
	    		break;
	    	case 'n':
	    		updown = 1;
	    		side = 0;
	    		break;
	    	case 'p':
	    		updown = -1;
	    		side = 0;
	    		break;
	    	case 'e':
	    		printf("\nend\n");
	    		return 0;
	    }

        // 移動先の位置を取得
        for (int i = 1; i <= 4; ++i)
        {
        	if (i <= blockCount)
        	{
        		mpositiony[i] = positiony[i] + updown;
			    mpositionx[i] = positionx[i] + side;
        		temp[i] = &board[positiony[i]][positionx[i]];
				mtemp[i] = &board[mpositiony[i]][mpositionx[i]];
        	}
        }
        
        if (check_can_move(blockCount)) 
        {
        	switch (blockCount) {
        		case 1:
        			*mtemp[1] = *temp[1];
					*temp[1] = 0;
        			break;
        		case 2:
        			if (positiony[1] == mpositiony[2] && positionx[1] == mpositionx[2])
					{
						// 2x1, 1x2のブロックでtemp[1]とmtemp[2]が同じ位置の場合
		                *mtemp[1] = *temp[1];
		                *mtemp[2] = *temp[2];
		                *temp[2] = 0;
					}
					else if (positiony[2] == mpositiony[1] && positionx[2] == mpositionx[1])
					{
						// 2x1, 1x2のブロックでtemp[2]とmtemp[1]が同じ位置の場合
		                *mtemp[2] = *temp[2];
		                *mtemp[1] = *temp[1];
		                *temp[1] = 0;
					}
					else
					{
						// 横ブロックが上下へ移動する場合
						// 縦ブロックが左右へ移動する場合
						*mtemp[1] = *temp[1];
						*temp[1] = 0;
						*mtemp[2] = *temp[2];
						*temp[2] = 0;
					}
        			break;
        		case 4:
        			switch (direction[0]) {
				    	case 'f':
			                *mtemp[2] = *temp[2];
			                *mtemp[1] = *temp[1];
			                *temp[1] = 0;
			                *mtemp[4] = *temp[4];
			                *mtemp[3] = *temp[3];
			                *temp[3] = 0;
				    		break;
				    	case 'b':
				    		*mtemp[1] = *temp[1];
			                *mtemp[2] = *temp[2];
			                *temp[2] = 0;
			                *mtemp[3] = *temp[3];
			                *mtemp[4] = *temp[4];
			                *temp[4] = 0;
				    		break;
				    	case 'n':
				    		*mtemp[3] = *temp[3];
			                *mtemp[1] = *temp[1];
			                *temp[1] = 0;
			                *mtemp[4] = *temp[4];
			                *mtemp[2] = *temp[2];
			                *temp[2] = 0;
				    		break;
				    	case 'p':
				    		*mtemp[1] = *temp[1];
			                *mtemp[3] = *temp[3];
			                *temp[3] = 0;
			                *mtemp[2] = *temp[2];
			                *mtemp[4] = *temp[4];
			                *temp[4] = 0;
				    		break;
				    }
        			break;
        	}
		}
    }
    
}

int check_can_move(int blockCount) {

	int retval = 0;

	if (check_in_frame(blockCount) && check_empty(blockCount)) retval = 1;

    return retval;
}

int check_in_frame(int blockCount) {

	int retval = 0;

	switch (blockCount) {
		case 1:
			if (check_range(mpositiony[1], mpositionx[1])) retval = 1;
			break;
		case 2:
			if (check_range(mpositiony[1], mpositionx[1]) && check_range(mpositiony[2], mpositionx[2])) retval = 1;
			break;
		case 4:
			if (check_range(mpositiony[1], mpositionx[1]) && check_range(mpositiony[2], mpositionx[2])
            	 	&& check_range(mpositiony[3], mpositionx[3]) && check_range(mpositiony[4], mpositionx[4])) retval = 1;
			break;
	}
    if (retval == 0) printf("don't move. (frame)\n\n");

    return retval;
}

int check_range(int mpositiony, int mpositionx) {

	int retval = 0;

	if (mpositiony >= 1 && mpositiony <= 5 && mpositionx >= 1 && mpositionx <= 4) retval = 1;

	return retval;
}

int check_empty(int blockCount) {

	int retval = 0;

	switch (blockCount) {
		case 1:
			if (*mtemp[1] == 0) retval = 1;	// 1x1が上下左右に移動する場合
			break;
		case 2:
			if ((*mtemp[1] == 0 && *mtemp[2] == 0)						// 2x1が左右に, 1x2のブロックが上下に移動する場合
					|| (*temp[1] == *mtemp[2] && *mtemp[1] == 0)		// 2x1が上, 1x2が左に移動する場合
					|| (*temp[2] == *mtemp[1] && *mtemp[2] == 0))		// 2x1が下, 1x2が右に移動する場合
			{
				retval = 1;
			}
			break;
		case 4:
			if (((*temp[1] == *mtemp[3] && *mtemp[1] == 0) && (*temp[2] == *mtemp[4] && *mtemp[2] == 0))			// 2x2が上に移動する場合
					|| ((*temp[3] == *mtemp[1] && *mtemp[3] == 0) && (*temp[4] == *mtemp[2] && *mtemp[4] == 0))		// 2x2が下に移動する場合
					|| ((*temp[1] == *mtemp[2] && *mtemp[1] == 0) && (*temp[3] == *mtemp[4] && *mtemp[3] == 0))		// 2x2が左に移動する場合
					|| ((*temp[2] == *mtemp[1] && *mtemp[2] == 0) && (*temp[4] == *mtemp[3] && *mtemp[4] == 0)))
			{
				retval = 1;
			}

			break;
	}
	if (retval == 0) printf("don't move. (no null)\n\n");

	return retval;
}