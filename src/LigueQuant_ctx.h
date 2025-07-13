#ifndef _LigueQuant_ctx_h
#define _LigueQuant_ctx_h

#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Clause SETS */
typedef enum
{
    LigueQuant_ctx__j1,
    LigueQuant_ctx__j2,
    LigueQuant_ctx__emp
    
} LigueQuant_ctx__PLAYERS;
#define LigueQuant_ctx__PLAYERS__max 3

/* Clause CONCRETE_CONSTANTS */
/* Basic constants */
typedef int LigueQuant_ctx__LIGUE_QUANTOS;
#define LigueQuant_ctx__minn 4
#define LigueQuant_ctx__maxx 20
#define LigueQuant_ctx__m1 LigueQuant_ctx__maxx-1
#define LigueQuant_ctx__mm LigueQuant_ctx__maxx * LigueQuant_ctx__maxx
/* Array and record constants */






/* Clause CONCRETE_VARIABLES */

extern void LigueQuant_ctx__INITIALISATION(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _LigueQuant_ctx_h */
