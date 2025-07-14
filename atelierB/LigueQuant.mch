MACHINE
    LigueQuant

SEES LigueQuant_ctx


/* Variaveis
    history: Sequencia que armazena as jogadas feitas pelos jogadores nas ultimas rodadas
    round: Armazena o numero da rodada atual
    currplayer: Armazena quem eh o jogador da vez
    lin e col: Quantidade de linhas e colunas do tabuleiro
    lig_qnt: Quantidade de peças consecutivas necessarias para ganhar o jogo
    board: Array bidimensional que armazena a localizacao das peças durante o jogo
    winner: Variavel que armazena o jogador vencedor, caso exista
*/
VARIABLES
    history, round, currplayer, lin, col, lig_qnt, board, winner

INVARIANT
    round : NAT1 &
    currplayer : PLAYERS & currplayer /= emp & lin : NAT1 & col : NAT1 & 
    history : seq((0..col-1)*(0..lin-1)) & 
    size(history) <= maxx*maxx &
    lig_qnt : NAT1 & lig_qnt : ligue_quantos_min..ligue_quantos_max &
    lin : minn..maxx  & 
    col : minn..maxx &
    board : ((0..col-1) * (0..lin-1)) --> PLAYERS &
    // History mantém exatamente todos os elementos não vazios do board
    ! xx . (xx : ran(history) => board(xx) /= emp) &
    ! xx . ((xx : dom(board) & board(xx) /= emp) => xx : ran(history)) &
    // Indices impares de history correspondem a peças no board de j1
    ! xx . ((xx : dom(history) & xx mod 2 = 1) => board(history(xx)) = j1) &
    // Indices pares de history correspondem a peças no board de j2
    ! xx . ((xx : dom(history) & xx mod 2 = 0) => board(history(xx)) = j2) &
    // Jogadas armazenadas em history sao consistentes (se uma peca p1 eh jogada antes de p2 e na mesma coluna de p2, entao p1 esta em uma linha abaixo de p2)
    ! (ii, jj) . (ii : dom(history) & jj : dom(history) & ii < jj & dom({history(ii)}) = dom({history(jj)})
    => !(xx, yy) . ((xx : ran({history(ii)}) & yy : ran({history(jj)})) => xx < yy)) &
    // O jogador j1 joga em rodadas impares
    ((round mod 2 = 1) => (currplayer = j1)) &
    //  O jogador j2 joga em rodadas pares
    ((round mod 2 = 0) => (currplayer = j2)) &
    // Lei da gravidade (não há peças flutuando)
    !(cc, xx) . ( cc : 0..col-1 & xx : 0..lin-1 => ( (board(cc, xx) /= emp) => (!yy . (yy : 0..xx => board(cc, yy) /= emp)) )) &
    winner : PLAYERS &
    lin >= lig_qnt & col >= lig_qnt &
    // Verifica se há alguma coluna com lig_qnt peças seguidas de algum jogador
    !pp . ((pp : PLAYERS - {emp}) =>((#(cc,ll) . (cc : 0..col-1 & ll : 0..lin-lig_qnt &                
    !jj . ((jj : ll..ll+lig_qnt-1 ) =>     
    board(cc,jj) = pp))) => (winner = pp)))       
    &
    // Verifica se há alguma linha com lig_qnt peças seguidas de algum jogador
    !pp . ((pp : PLAYERS - {emp}) => ((#(cc,ll) . (cc : 0..col-lig_qnt & ll : 0..lin-1 &                
    !jj . ((jj : cc..cc+lig_qnt-1 ) =>     
    board(jj,ll) = pp))) => (winner = pp)))  
    &
    // Verifica se há alguma diagonal "/" com lig_qnt peças seguidas de algum jogador
    !pp . ((pp : PLAYERS - {emp}) => ((#(cc,ll) . (cc : 0..col-lig_qnt & 
                  ll : 0..lin-lig_qnt &                
    !(ii) . (ii : 0..lig_qnt-1  =>     
    board(cc+ii,ll+ii) = pp))) => (winner = pp)))     
    &
    // Verifica se há alguma diagonal "\" com lig_qnt peças seguidas de algum jogador
    !pp . ((pp : PLAYERS - {emp}) =>((#(cc,ll) . (cc : 0..col-lig_qnt & 
                  ll : lig_qnt-1..lin-1 &                
    !(ii) . (ii : 0..lig_qnt-1  =>     
    board(cc+ii,ll-ii) = pp))) => (winner = pp)))    

INITIALISATION
    history := [] || round := 1 || currplayer := j1 || lin := 7 || col := 7 || lig_qnt := 4 || 
    board := ((0..6) * (0..6)) * {emp} || winner := emp
    
OPERATIONS
    
    /*
    Operações

        Play(coluna) X
        Reset()      X
        Undo_move()  X
        Undo_moves(num)  X
        change_game_rules(lin, col, quant) X
        query_game_end() X
        query_round() X
        query_player() X
        query_board() X
        query_history() X
        
    */

/* Operação play 

    Dada uma coluna, uma peça é colocada no tabuleiro board correspondente à menor linha vazia daquela coluna.
    A peça colocada é do jogador indicado por currplayer.

    A chamada dessa operação muda:
    1) history, adicionando a jogada feita
    2) round, incrementando a rodada
    3) currplayer, trocando quem é o jogador da vez
    4) board, atualizando o tabuleiro com a peça colocada
    
    A chamada dessa operação pode mudar:
    1) winner, caso a jogada faça o jogador atual vencer

    Essa operação só pode ser chamada se:
    1) Ainda não há um jogador ganhador/perdedor;
    2) A coluna escolhida está no range 0..col-1
    3) A coluna escolhida não está cheia;
*/

ret <-- play(cc) =
    PRE cc : NAT & round +1 : NAT1
    THEN 
        IF cc : 0..col-1 & board(cc, lin-1) = emp & winner = emp THEN
            LET newboard BE newboard = board <+ {(cc, min({xx | xx : 0..lin-1 & board(cc, xx) = emp})) |-> currplayer} IN
                // Condicao de vitoria coluna
                IF (#(cc,ll) . (cc : 0..col-1 & ll : 0..lin-lig_qnt & !jj . ((jj : ll..ll+lig_qnt-1 ) => newboard(cc,jj) = currplayer))) 
                // Condicao de vitoria linha
                or (#(cc,ll) . (cc : 0..col-lig_qnt & ll : 0..lin-1 & !jj . ((jj : cc..cc+lig_qnt-1 ) => newboard(jj,ll) = currplayer)))
                // Condicao de vitoria diagonal "/"
                or (#(cc,ll) . (cc : 0..col-lig_qnt & ll:0..lin-lig_qnt & !(ii).(ii : 0..lig_qnt-1 => newboard(cc+ii,ll+ii) = currplayer)))
                // Condicao de vitoria diagonal "\"
                or (#(cc,ll) . (cc : 0..col-lig_qnt & ll:lig_qnt-1..lin-1 & !(ii).(ii : 0..lig_qnt-1 => newboard(cc+ii,ll-ii) = currplayer)))
                THEN
                    ANY jj WHERE jj : PLAYERS - {currplayer, emp} THEN
                    ret := TRUE || 
                    history := history <- (cc |-> min({xx | xx : 0..lin-1 & board(cc, xx) = emp}))  ||
                    round := round + 1 ||
                    currplayer := jj ||
                    board := newboard ||
                    winner := currplayer
                    END
                ELSE
                    ANY jj WHERE jj : PLAYERS - {currplayer, emp} THEN
                    ret := TRUE ||
                    history := history <- (cc |-> min({xx | xx : 0..lin-1 & board(cc, xx) = emp})) ||
                    round := round + 1 ||
                    currplayer := jj ||
                    board := newboard
                    END
                END
            END
        ELSE
            ret := FALSE
        END
    END;


/* Operação reset
    
    Reseta o estado da máquina para o inicial, desfazendo qualquer jogada feita e limpando o tabuleiro
*/
reset = 
    BEGIN
    history := [] || round := 1 || currplayer := j1 || 
    board := ((0..col-1) * (0..lin-1)) * {emp} || winner := emp
    END;

/* Operação undo_move

    Desfaz a ultima jogada feita.
    
    A chamada dessa operação muda:
    1) history, desfazendo a jogada feita
    2) round, decrementando a rodada
    3) board, tirando uma peça do tabuleiro
    4) currplayer, mudando para o ultimo jogador

    Essa operação só pode ser chamada se:
    1) Ainda não há um jogador ganhador/perdedor;
    2) O histórico não está vazio
*/
ret <-- undo_move =
    BEGIN
         IF winner = emp & size(history) > 0 THEN
            ANY jj WHERE jj : PLAYERS - {currplayer, emp} THEN
                ret := TRUE || history := front(history) || round := round - 1 ||
                board := board <+ {last(history) |-> emp} || currplayer := jj
            END
         ELSE
             ret := FALSE
         END
    END;

/* Operação undo_moves(nn)

    Desfaz as ultimas nn jogadas feitas.
    
    A chamada dessa operação muda:
    1) history, desfazendo as nn ultimas jogadas
    2) round, decrementando a rodada nn vezes
    3) board, tirando nn peças do tabuleiro
    4) currplayer, mudando para o jogador da rodada round - nn

    Essa operação só pode ser chamada se:
    1) Ainda não há um jogador ganhador/perdedor;
    2) O histórico possui pelo menos nn elementos
*/

ret <-- undo_moves(nn) = 
    PRE nn : NAT1
    THEN IF winner  = emp & size(history) >= nn & round > nn THEN
        IF (round - nn) mod 2 = 0 THEN
            ret := TRUE || history := history /|\ (size(history) - nn) || round := round - nn ||
            board := board <+ ran(history \|/ (size(history) - nn))*{emp} || currplayer := j2
        ELSE
            ret := TRUE || history := history /|\ (size(history) - nn) || round := round - nn ||
            board := board <+ ran(history \|/ (size(history) - nn))*{emp} || currplayer := j1
        END
    ELSE
        ret := FALSE
    END
    END;

/* Operação change_game_rules(ll, cc, qnt)

    Determina os valores de linhas e colunas presentes no tabuleiro, além de dizer qual a quantidade de peças
    em sequência necessária para definir um ganhador.
    
    A chamada dessa pode mudar:
    1) lin, alterando seu valor
    2) col, alterando seu valor
    3) lig_qnt, alterando seu valor
    4) board, alterando a quantidade de "slots" vazios no tabuleiro

    Essa operação só pode ser chamada se:
    1) ll, cc e qnt estiverem dentro dos limites definidos
    2) Deve ser possível algum jogador ganhar dado os valores de ll, cc e qnt
    3) Nenhuma jogada ainda foi feita
*/
ret <-- change_game_rules(ll, cc, qnt) =
    PRE ll : NAT & cc : NAT & qnt : NAT
    THEN IF ll : minn..maxx & cc : minn..maxx & qnt : ligue_quantos_min..ligue_quantos_max & history = [] & ll >= qnt & cc >= qnt THEN
        ret := TRUE || lin := ll || col := cc || lig_qnt := qnt || board := ((0..cc-1) * (0..ll-1)) * {emp}
    ELSE
        ret := FALSE
    END
    END;

/* Operações de query */

rr <-- query_round = 
    BEGIN
    rr := round
    END;

jj <-- query_player =
    BEGIN
    jj := currplayer
    END;

end, ww <-- query_game_end =
    IF winner /= emp or emp /: ran(board) THEN
        end := TRUE || ww := winner
    ELSE
        end := FALSE || ww := winner
    END;

ll <-- query_lin =
    BEGIN
    ll := lin
    END;

cc <-- query_col =
    BEGIN
    cc := col
    END;

qq <-- query_lig_qnt =
    BEGIN
    qq := lig_qnt
    END;

bb, cc, ll <-- query_board =
    BEGIN
        ANY bd WHERE
            bd : ((0..m1) * (0..m1)) --> PLAYERS &
            bd = board \/ ((((0..m1)*(0..m1)) - dom(board)) * {emp})
        THEN
            bb := bd || ll := lin || cc := col
        END
    
    END;

hcol, hlin, ii <-- query_history =
    BEGIN
        ANY cc, ll WHERE 
            cc : 0..mm --> 0..m1 &
            ll : 0..mm --> 0..m1 &
            history = % kk . (kk : 1..size(history) | (cc(kk), ll(kk)))
        THEN
            hcol := cc ||
            hlin := ll ||
            ii := size(history)
        END
      
    END

    


END