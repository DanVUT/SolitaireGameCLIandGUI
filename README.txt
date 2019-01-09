Autori: Daniel Florek, Martin Grnáè
Projekt: Solitaire

Popis funkcnosti CLI rozhrania:
Implementuje jednoduche textove rozhranie pre hru Solitaire. Hlavnı princíp funkènosti sú vectory a presúvanie prvkov medzi nimi. Na zaèiatku hry má hráè
monos si vybra èi chce novú hru, èi chce hru naèíta, alebo ukonèi. Následne sa vytvorí pre hráèa náhodne vygenerovaná hracia plocha.
Hra sa ovláda štılom, e sa najprv vyberie poadovaná akcia oèíslovaná od 1 do 6 prípadne ešte Undo klávesou "U" alebo odchod z hry klavesou "E".
Na základe vybranej akcie sa nasledne vypisu pokyny pre vykonanie danej akcie.
1 - Presun kariet v rámci hernej plochy. Hráè zadá èíslo radu odkia¾ chce presúva, potom zadá kartu ktorú chce presúva formátom "znak cislo" a nakoniec cislo destinacneho radu.
2 - Presun kariet z waste do hernej plochy. Hráè vyberie rad do ktoreho sa ma karta presunut.
3 - Potiahne sa karta z balicku do waste.
4 - Hrac vyberie rad z ktorého sa má karta presunu do foundation stackov.
5 - Karta z waste sa presunie do foundation stacku
6 - Pohyb Karty zo stacku spä do po¾a. Hraè vybere stack podla znaku "c" a potom èíslo destinacneho radu.
U - Vrati poslednu operaciu spä. Udruje sa 5 poslednıch operácií.
E - Ukonèí hru, hráè si môe vybra, ci chce hru ulozit
Hra po kazdom kole kontroluje ci nie je splnena podmienka konecnosti hry.

Popis funkcnosti GUI rozhrania:
GUI rozhranie hry sa nám úplne implementova nepodarilo z dôvodu zdravotného stavu jedného z riešite¾ov a nedostatku èasu. Tak sa nám podarilo implementova aspoò logiku presúvania kariet medzi
radmi, otacanie z balicku do stacku a presun kariet do foundation stackov. Implementovali sme prakticky všetky herné mechanizmy, nestihli sme u implementova vèas hernú logiku.


P.S Kvôli problemom s makefilom sa makefile pre GUI musi vygenerovat, take pripadna dokumentacia GUI zdrojovych suborov sa musi riesit rucnym zavolanim doxygen Doxyfile