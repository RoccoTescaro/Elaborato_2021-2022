# The Forbidden Sketchbook
Elaborato di programmazione anno accademico 2021-2022

## Concept:
  - ### GamePlay
      Gioco "single-player" strategico a turni top-down 2D. Il giocatore ha l'obbiettivo di sbloccare l'item "The Forbidden Sketchbook". Per completare questa
      missione dovrà risolvere enigmi e sconfiggere i nemici che cercheranno di ostacolarlo. Ad aiutarlo avrà a disposizione strumenti e armi sbloccabili lungo il       percorso.
## Meccaniche di gioco:
  - ### Mappa
      La mappa è composta di tile che costituiscono la scacchiera di gioco. Lungo il percorso il giocatore si imbatterà in ostacoli fisici e "psicologici": 
      + __muri__
      + __fosse__
      
         > a differenza dei muri possono essere occupati da nemici volanti.
      
      + __ostacoli cancellabili__ (vedi [Strumenti, _pezzi di gomma_](#strumenti))
      + __ostacoli modificabili__ (vedi [Strumenti, _matita_](#strumenti))     
      + __scrivania__
      
         > tile per la modifica e "crafting" delle armi a costo di _inchiostro_.
      
      + __piedistalli__ 

         > conservano gli _strumenti_ e _colori_ non acora sbloccati.
     
  - ### Giocatore
      Il giocatore controlla la propria pedina nel mondo di gioco cliccando sui tile con i quali vuole interagire, limitato, però, dai __punti azione__.
      I punti azione vengono reimpostati ad un valore di default all'inzio del turno del giocatore, senza, quindi, accumulare i punti non impiegati nel turno           precedente. Il protagonista ha a disposizione strumenti ed armi per affrontare i vari ostacoli. Lo stato dei __punti vita__, strumenti e punti azione sono           sempre visibili al giocatore.
  - ### Strumenti
      Nel gioco sono presenti diversi strumenti sbloccabili ottenibili in diversi modi:
      + __astuccio__
      
         > si occupa di conservare tutti gli strumenti.
         
      + __calamaio__
      
         > si occupa di conservare l'_inchiostro_.
         
      + __matita__
      
         > ti permette di disegnare in tile specifici.
         
      + __pezzi di gomma__
      
         > ti permettono di cancellare tile specifici a patto di averne a sufficienza.
         
      + __penna multicolore__
      
         > ti permette a patto di aver collezionato tutti e 4 i <i>colori</i> di sbloccare un'arma. La grafica di gioco viene                                                 influenzata sbloccando i differenti colori della penna multicolore reperibili in giro per la mappa.
         
  - ### Armi
      Le armi sono di due tipi: __matita__ ("corpo a corpo") o __penna__ ("distanza").
      La prima agisce se in presenza di mobs ostili in tile adiacenti a quello del giocatore. 
      La seconda invece possono essere attivate su un qualsiasi tile su cui è presente un mob ostile entro un certo range proprio dell'arma;
      in caso il mob si trovi fuori dal range ma il giocatore possedesse abbastanza punti azione ( vedi [Giocatore](#giocatore) ) il giocatore procederà ad           avvicinarsi al mob fino a entrare nel range necessario.
      La penna multicolore permette di sbloccare una nuova arma da distanza.
      Le armi sono selezionabili spendendo punti _inchiostro_.
             
  - ### Nemici
      La mappa è disseminata di vari nemici, che rinascono dopo un certo numero di turni (dalla morte), nel tile in cui sono nati.
      + __nemici volanti__ 

         > ricercano la posizione del giocatore avvicinandosi per colpirlo ingnorando le fosse.

      + __nemici "corpo a corpo"__
      
         > ricercano la posizione del giocatore avvicinandosi per colpirlo.
         
      + __nemici "da distanza"__
      
         > Se il giocatore si trova in un certo range dalla sua posizione, si muovono ignorando ogni tipo di ostacolo in un tile casuale ma distante dal                      giocatore. Se il giocatore è sufficientemente distante lo attaccherà dalla distanza.
      
      + __boss__
      
      I nemici una volta sconfitti rilasciano _pezzi di gomma_ e/o _inchiostro_.
___
## Autori:
Bernacchioni Lapo </br>
Tescaro Rocco
