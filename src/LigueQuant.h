#ifndef _LigueQuant_h
#define _LigueQuant_h

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
/* Clause SEES */
#include "LigueQuant_ctx.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Clause SETS */

/* Clause CONCRETE_CONSTANTS */
/* Basic constants */
/* Array and record constants */

/* Clause CONCRETE_VARIABLES */

extern void LigueQuant__INITIALISATION(void);

/* Clause OPERATIONS */

extern void LigueQuant__play(int32_t cc, bool *ret);
extern void LigueQuant__reset(void);
extern void LigueQuant__undo_move(bool *ret);
extern void LigueQuant__undo_moves(int32_t nn, bool *ret);
extern void LigueQuant__change_game_rules(int32_t ll, int32_t cc, int32_t qnt, bool *ret);
extern void LigueQuant__query_round(int32_t *rr);
extern void LigueQuant__query_player(LigueQuant_ctx__PLAYERS *jj);
extern void LigueQuant__query_game_end(bool *end, LigueQuant_ctx__PLAYERS *ww);
extern void LigueQuant__query_lin(int32_t *ll);
extern void LigueQuant__query_col(int32_t *cc);
extern void LigueQuant__query_lig_qnt(int32_t *qq);
extern void LigueQuant__query_board(LigueQuant_ctx__PLAYERS *bb, int32_t *cc, int32_t *ll);
extern void LigueQuant__query_history(int32_t *hcol, int32_t *hlin, int32_t *ii);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _LigueQuant_h */
