Na arduino su povezane 3 LED diode i jedan pushup gumb
Default stanje countera koji mijenja koja dioda svijetli je 0, te tada svijetli samo magenta dioda na pinu 6
Kada se na serial monitor upiše broj 2, stanje countera se mijenja na 2 i paliti će se samo žuta dioda na pinu 7
Pritiskom na tipkalo će se counter varijabla promijeniti na vrijednost 1 te će se paliti samo plava dioda na pinu 8
Svakih 8 sekundi se pokreće watchdog timer koji resetira counter ponovno na vrijednost 0

Interupt pritiska na tipkalo ima najviši prioritet pri izvođenju
Watchdog timer ima srednji prioritet te će biti uvijek drugi na izvođenjuž
Čitanje serijskog porta ima najmanji prioritet te će se čitanje sa serijskog porta izvršavati zadnje
