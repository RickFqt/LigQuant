MACHINE
    LigueQuant_ctx
    
SETS
    PLAYERS = {j1, j2, emp}

/* Constantes
    LIGUE_QUANTOS: conjunto que determina os valores possiveis para a quantidade de peças consecutivas
                   necessarias para ganhar o jogo;
    minn e maxx: valores minimo e maximo possíveis para a quantidade de linhas e colunas do tabuleiro
*/
CONSTANTS
    minn, maxx, m1, mm, ligue_quantos_min, ligue_quantos_max

PROPERTIES
    minn : NAT1 & minn = 4 & maxx : NAT1 & maxx = 20 & minn <= maxx &
    ligue_quantos_min : NAT1 & ligue_quantos_min = 2 & ligue_quantos_max : NAT1 & ligue_quantos_max = 7 &
    m1 : NAT & m1 = maxx-1 & mm : NAT & mm = maxx*maxx

END