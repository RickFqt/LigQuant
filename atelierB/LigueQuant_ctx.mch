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
    LIGUE_QUANTOS, minn, maxx, m1, mm

PROPERTIES
    minn : NAT1 & minn = 4 & maxx : NAT1 & maxx = 20 & minn <= maxx & LIGUE_QUANTOS <: NAT1 & LIGUE_QUANTOS = 2..7 & m1 : NAT & m1 = maxx-1 & mm : NAT & mm = maxx*maxx

END