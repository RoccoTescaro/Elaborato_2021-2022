# The Forbidden Sketchbook
Elaborato di programmazione anno accademico 2021-2022

## Concept:
  - ### Sviluppo
      Gioco "single-player" strategico a turni top-down 2D. 
  - ### Obbiettivo
      Sbloccare l'item "The Forbidden Sketchbook".
## Meccaniche di gioco:
  - ### Mappa
      La mappa è composta di tile che costituiscono la scacchiera di gioco. Lungo il percorso il giocatore si imbatterà in ostacoli fisici e "psicologici": muri di inchiostro, mobs, ecc. 
      
  - ### Giocatore
      Il giocatore controlla la propria pedina nel mondo di gioco cliccando sui tile con i quali vuole interagire, limitato, però, dai __punti azione__.
      I punti azione vengono reimpostati ad un valore di default all'inzio del turno del giocatore, senza, quindi, accumulare i punti non impiegati nel turno           precedente. Il protagonista ha a disposizione strumenti ed armi per affrontare i vari ostacoli. Lo stato dei __punti vita__, strumenti e punti azione sono           sempre visibili al giocatore.
  - ### Strumenti
      Nel gioco sono presenti diversi strumenti sbloccabili ottenibili in diversi modi:
      + __astuccio__
      
         > si occupa di conservare tutti gli strumenti.
         
      + __calamaio__
      
         > si occupa di conservare l'_inchiostro_.
         
      + __penna__
      
         > ti permette di disegnare in tile specifici a patto di aver dell'inchiostro nel _calamaio_.
         
      + __pezzi di gomma__
      
         > ti permettono di cancellare tile specifici a patto di averne a sufficienza.
         
      + __penna multicolore__
      
         > ti permette a patto di aver collezionato tutti e 4 i <i>colori</i> di sbloccare un'arma. La grafica di gioco viene                                                 influenzata sbloccando i differenti colori della penna multicolore reperibili in giro per la mappa.
         
  - ### Armi
      Le armi sono di due tipi: "corpo a corpo" o "da distanza".
      Le prime agiscono se in presenza di mobs ostili in tile adiacenti a quello del giocatore. 
      Le seconde invece possono essere attivate su un qualsiasi tile su cui è presente un mob ostile entro un certo range proprio dell'arma;
      in caso il mob si trovi fuori dal range ma il giocatore possedesse abbastanza punti azione ( vedi [Giocatore](#giocatore) ) il giocatore procederà ad           avvicinarsi al mob fino a entrare nel range necessario.
      La penna multicolore permette di sbloccare una nuova arma da distanza.
      Le armi sono selezionabili spendendo punti <i> inchiostro </i>.
      
      //mappa
      L'inchiostro è utilizzabile alla scrivania per modificare le proprie armi.
            
  - ### Nemici
      I nemici una volta sconfitti rilasciano <i>pezzi di gomma</i> e/o <i>inchiostro</i>.
___
## Autori:
Bernacchioni Lapo </br>
Tescaro Rocco
