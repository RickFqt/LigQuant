/* WARNING if type checker is not performed, translation could contain errors ! */

#include "LigueQuant.h"

/* Clause SEES */
#include "LigueQuant_ctx.h"

/* Clause CONCRETE_CONSTANTS */
/* Basic constants */

/* Array and record constants */
/* Clause CONCRETE_VARIABLES */

static int32_t LigueQuant__round;
static LigueQuant_ctx__PLAYERS LigueQuant__currplayer;
static int32_t LigueQuant__lin;
static int32_t LigueQuant__col;
static int32_t LigueQuant__lig_qnt;
static LigueQuant_ctx__PLAYERS LigueQuant__winner;
static LigueQuant_ctx__PLAYERS LigueQuant__board_i[LigueQuant_ctx__m1+1][LigueQuant_ctx__m1+1];
static int32_t LigueQuant__col_history[LigueQuant_ctx__mm+1];
static int32_t LigueQuant__lin_history[LigueQuant_ctx__mm+1];
static int32_t LigueQuant__counter;
/* Clause INITIALISATION */
void LigueQuant__INITIALISATION(void)
{
    
    unsigned int i = 0, j= 0;
    LigueQuant__round = 1;
    LigueQuant__currplayer = LigueQuant_ctx__j1;
    LigueQuant__lin = 7;
    LigueQuant__col = 7;
    LigueQuant__lig_qnt = 4;
    LigueQuant__winner = LigueQuant_ctx__emp;
    LigueQuant__counter = 0;
    for(i = 0; i <= LigueQuant_ctx__mm;i++)
    {
        LigueQuant__col_history[i] = 0;
    }
    for(i = 0; i <= LigueQuant_ctx__mm;i++)
    {
        LigueQuant__lin_history[i] = 0;
    }
    for(i = 0; i <= LigueQuant_ctx__m1;i++)
    {
        for(j = 0; j <= LigueQuant_ctx__m1;j++)
        {
            LigueQuant__board_i[i][j] = LigueQuant_ctx__emp;
        }
    }
}

/* Clause OPERATIONS */

void LigueQuant__play(int32_t cc, bool *ret)
{
    {
        LigueQuant_ctx__PLAYERS top_element;
        
        top_element = LigueQuant__board_i[cc][LigueQuant__lin-1];
        if((top_element == LigueQuant_ctx__emp) &&
        (LigueQuant__winner == LigueQuant_ctx__emp))
        {
            (*ret) = true;
            LigueQuant__round = LigueQuant__round+1;
            {
                int32_t ll;
                int32_t l1;
                
                ll = LigueQuant__lin-1;
                l1 = LigueQuant__lig_qnt-1;
                {
                    int32_t ii;
                    LigueQuant_ctx__PLAYERS curr;
                    
                    ii = LigueQuant__lin;
                    curr = LigueQuant_ctx__emp;
                    while((ii) > (0))
                    {
                        ii = ii-1;
                        curr = LigueQuant__board_i[cc][ii];
                        if(curr == LigueQuant_ctx__emp)
                        {
                            ll = ii;
                        }
                    }
                }
                LigueQuant__board_i[cc][ll] = LigueQuant__currplayer;
                LigueQuant__counter = LigueQuant__counter+1;
                LigueQuant__col_history[LigueQuant__counter] = cc;
                LigueQuant__lin_history[LigueQuant__counter] = ll;
                {
                    int32_t ii;
                    int32_t jj;
                    int32_t cnt;
                    LigueQuant_ctx__PLAYERS curr;
                    LigueQuant_ctx__PLAYERS prev;
                    
                    ii = cc;
                    jj = 1;
                    cnt = 0;
                    curr = LigueQuant_ctx__emp;
                    prev = LigueQuant_ctx__emp;
                    while(((jj) < (LigueQuant__lin)) &&
                    ((cnt) < (l1)))
                    {
                        curr = LigueQuant__board_i[ii][jj];
                        prev = LigueQuant__board_i[ii][jj-1];
                        if((curr == LigueQuant__currplayer) &&
                        (prev == curr))
                        {
                            cnt = cnt+1;
                        }
                        else
                        {
                            cnt = 0;
                        }
                        jj = jj+1;
                        if(cnt == l1)
                        {
                            LigueQuant__winner = LigueQuant__currplayer;
                        }
                    }
                }
                {
                    int32_t ii;
                    int32_t jj;
                    int32_t cnt;
                    LigueQuant_ctx__PLAYERS curr;
                    LigueQuant_ctx__PLAYERS prev;
                    
                    ii = 1;
                    jj = ll;
                    cnt = 0;
                    curr = LigueQuant_ctx__emp;
                    prev = LigueQuant_ctx__emp;
                    while(((ii) < (LigueQuant__col)) &&
                    ((cnt) < (l1)))
                    {
                        curr = LigueQuant__board_i[ii][jj];
                        prev = LigueQuant__board_i[ii-1][jj];
                        if((curr == LigueQuant__currplayer) &&
                        (prev == curr))
                        {
                            cnt = cnt+1;
                        }
                        else
                        {
                            cnt = 0;
                        }
                        ii = ii+1;
                        if(cnt == l1)
                        {
                            LigueQuant__winner = LigueQuant__currplayer;
                        }
                    }
                }
                {
                    int32_t ii;
                    int32_t jj;
                    int32_t cnt;
                    LigueQuant_ctx__PLAYERS curr;
                    LigueQuant_ctx__PLAYERS prev;
                    int32_t dist;
                    
                    if((cc) < (ll))
                    {
                        dist = cc;
                    }
                    else
                    {
                        dist = ll;
                    }
                    if((LigueQuant__lig_qnt) < (dist))
                    {
                        dist = LigueQuant__lig_qnt;
                    }
                    ii = cc-dist+1;
                    jj = ll-dist+1;
                    cnt = 0;
                    curr = LigueQuant_ctx__emp;
                    prev = LigueQuant_ctx__emp;
                    while((((ii) < (LigueQuant__col)) &&
                        ((jj) < (LigueQuant__lin))) &&
                    ((cnt) < (l1)))
                    {
                        curr = LigueQuant__board_i[ii][jj];
                        prev = LigueQuant__board_i[ii-1][jj-1];
                        if((curr == LigueQuant__currplayer) &&
                        (prev == curr))
                        {
                            cnt = cnt+1;
                        }
                        else
                        {
                            cnt = 0;
                        }
                        ii = ii+1;
                        jj = jj+1;
                        if(cnt == l1)
                        {
                            LigueQuant__winner = LigueQuant__currplayer;
                        }
                    }
                }
                {
                    int32_t ii;
                    int32_t jj;
                    int32_t cnt;
                    LigueQuant_ctx__PLAYERS curr;
                    LigueQuant_ctx__PLAYERS prev;
                    int32_t dist;
                    int32_t l2;
                    
                    l2 = LigueQuant__lin-ll-1;
                    if((cc) < (l2))
                    {
                        dist = cc;
                    }
                    else
                    {
                        dist = l2;
                    }
                    if((LigueQuant__lig_qnt) < (dist))
                    {
                        dist = LigueQuant__lig_qnt;
                    }
                    ii = cc-dist+1;
                    jj = ll+dist-1;
                    cnt = 0;
                    curr = LigueQuant_ctx__emp;
                    prev = LigueQuant_ctx__emp;
                    while((((ii) < (LigueQuant__col)) &&
                        ((jj) >= (0))) &&
                    ((cnt) < (l1)))
                    {
                        curr = LigueQuant__board_i[ii][jj];
                        prev = LigueQuant__board_i[ii-1][jj+1];
                        if((curr == LigueQuant__currplayer) &&
                        (prev == curr))
                        {
                            cnt = cnt+1;
                        }
                        else
                        {
                            cnt = 0;
                        }
                        ii = ii+1;
                        jj = jj-1;
                        if(cnt == l1)
                        {
                            LigueQuant__winner = LigueQuant__currplayer;
                        }
                    }
                }
                if(LigueQuant__currplayer == LigueQuant_ctx__j1)
                {
                    LigueQuant__currplayer = LigueQuant_ctx__j2;
                }
                else
                {
                    LigueQuant__currplayer = LigueQuant_ctx__j1;
                }
            }
        }
        else
        {
            (*ret) = false;
        }
    }
}

void LigueQuant__reset(void)
{
    unsigned int i = 0, j= 0;
    {
        LigueQuant__round = 1;
        LigueQuant__currplayer = LigueQuant_ctx__j1;
        LigueQuant__winner = LigueQuant_ctx__emp;
        LigueQuant__counter = 0;
        for(i = 0; i <= LigueQuant_ctx__m1;i++)
        {
            for(j = 0; j <= LigueQuant_ctx__m1;j++)
            {
                LigueQuant__board_i[i][j] = LigueQuant_ctx__emp;
            }
        }
    }
}

void LigueQuant__undo_move(bool *ret)
{
    if((LigueQuant__winner == LigueQuant_ctx__emp) &&
    ((LigueQuant__counter) > (0)))
    {
        LigueQuant__board_i[LigueQuant__col_history[LigueQuant__counter]][LigueQuant__lin_history[LigueQuant__counter]] = LigueQuant_ctx__emp;
        (*ret) = true;
        LigueQuant__counter = LigueQuant__counter-1;
        LigueQuant__round = LigueQuant__round-1;
        if(LigueQuant__currplayer == LigueQuant_ctx__j1)
        {
            LigueQuant__currplayer = LigueQuant_ctx__j2;
        }
        else
        {
            LigueQuant__currplayer = LigueQuant_ctx__j1;
        }
    }
    else
    {
        (*ret) = false;
    }
}

void LigueQuant__undo_moves(int32_t nn, bool *ret)
{
    if(((LigueQuant__winner == LigueQuant_ctx__emp) &&
        ((LigueQuant__counter) >= (nn))) &&
    ((LigueQuant__round) > (nn)))
    {
        {
            int32_t kk;
            
            kk = (LigueQuant__round-nn) % 2;
            if(kk == 0)
            {
                LigueQuant__currplayer = LigueQuant_ctx__j2;
            }
            else
            {
                LigueQuant__currplayer = LigueQuant_ctx__j1;
            }
        }
        (*ret) = true;
        {
            int32_t counter_target;
            int32_t curr_counter;
            
            curr_counter = LigueQuant__counter;
            counter_target = LigueQuant__counter-nn;
            while((curr_counter) > (counter_target))
            {
                LigueQuant__board_i[LigueQuant__col_history[curr_counter]][LigueQuant__lin_history[curr_counter]] = LigueQuant_ctx__emp;
                curr_counter = curr_counter-1;
            }
        }
        LigueQuant__counter = LigueQuant__counter-nn;
        LigueQuant__round = LigueQuant__round-nn;
    }
    else
    {
        (*ret) = false;
    }
}

void LigueQuant__change_game_rules(int32_t ll, int32_t cc, int32_t qnt, bool *ret)
{
    unsigned int i = 0, j= 0;
    {
        if(((LigueQuant__counter == 0) &&
            ((ll) >= (qnt))) &&
        ((cc) >= (qnt)))
        {
            (*ret) = true;
            LigueQuant__lin = ll;
            LigueQuant__col = cc;
            LigueQuant__lig_qnt = qnt;
            for(i = 0; i <= LigueQuant_ctx__m1;i++)
            {
                for(j = 0; j <= LigueQuant_ctx__m1;j++)
                {
                    LigueQuant__board_i[i][j] = LigueQuant_ctx__emp;
                }
            }
        }
        else
        {
            (*ret) = false;
        }
    }
}

void LigueQuant__query_round(int32_t *rr)
{
    (*rr) = LigueQuant__round;
}

void LigueQuant__query_player(LigueQuant_ctx__PLAYERS *jj)
{
    (*jj) = LigueQuant__currplayer;
}

void LigueQuant__query_game_end(bool *end, LigueQuant_ctx__PLAYERS *ww)
{
    {
        int32_t history_max_sze;
        
        history_max_sze = (LigueQuant__lin) * (LigueQuant__col);
        if(((LigueQuant__winner) != (LigueQuant_ctx__emp)) ||
        (LigueQuant__counter == history_max_sze))
        {
            (*end) = true;
            (*ww) = LigueQuant__winner;
        }
        else
        {
            (*end) = false;
            (*ww) = LigueQuant__winner;
        }
    }
}

void LigueQuant__query_lin(int32_t *ll)
{
    (*ll) = LigueQuant__lin;
}

void LigueQuant__query_col(int32_t *cc)
{
    (*cc) = LigueQuant__col;
}

void LigueQuant__query_lig_qnt(int32_t *qq)
{
    (*qq) = LigueQuant__lig_qnt;
}

void LigueQuant__query_board(LigueQuant_ctx__PLAYERS *bb, int32_t *cc, int32_t *ll)
{
    memmove(bb,LigueQuant__board_i,(LigueQuant_ctx__m1+1)*( LigueQuant_ctx__m1+1)* sizeof(LigueQuant_ctx__PLAYERS));
    (*cc) = LigueQuant__col;
    (*ll) = LigueQuant__lin;
}

void LigueQuant__query_history(int32_t *hcol, int32_t *hlin, int32_t *ii)
{
    memmove(hcol,LigueQuant__col_history,(LigueQuant_ctx__mm+1)* sizeof(int32_t));
    memmove(hlin,LigueQuant__lin_history,(LigueQuant_ctx__mm+1)* sizeof(int32_t));
    (*ii) = LigueQuant__counter;
}

