Autori: Daniel Florek, Martin Grn��
Projekt: Solitaire

Popis funkcnosti CLI rozhrania:
Implementuje jednoduche textove rozhranie pre hru Solitaire. Hlavn� princ�p funk�nosti s� vectory a pres�vanie prvkov medzi nimi. Na za�iatku hry m� hr��
mo�nos� si vybra� �i chce nov� hru, �i chce hru na��ta�, alebo ukon�i�. N�sledne sa vytvor� pre hr��a n�hodne vygenerovan� hracia plocha.
Hra sa ovl�da �t�lom, �e sa najprv vyberie po�adovan� akcia o��slovan� od 1 do 6 pr�padne e�te Undo kl�vesou "U" alebo odchod z hry klavesou "E".
Na z�klade vybranej akcie sa nasledne vypisu pokyny pre vykonanie danej akcie.
1 - Presun kariet v r�mci hernej plochy. Hr�� zad� ��slo radu odkia� chce pres�va�, potom zad� kartu ktor� chce pres�va� form�tom "znak cislo" a nakoniec cislo destinacneho radu.
2 - Presun kariet z waste do hernej plochy. Hr�� vyberie rad do ktoreho sa ma karta presunut.
3 - Potiahne sa karta z balicku do waste.
4 - Hrac vyberie rad z ktor�ho sa m� karta presunu� do foundation stackov.
5 - Karta z waste sa presunie do foundation stacku
6 - Pohyb Karty zo stacku sp� do po�a. Hra� vybere stack podla znaku "c" a potom ��slo destinacneho radu.
U - Vrati poslednu operaciu sp�. Udr�uje sa 5 posledn�ch oper�ci�.
E - Ukon�� hru, hr�� si m��e vybra�, ci chce hru ulozit
Hra po kazdom kole kontroluje ci nie je splnena podmienka konecnosti hry.

Popis funkcnosti GUI rozhrania:
GUI rozhranie hry sa n�m �plne implementova� nepodarilo z d�vodu zdravotn�ho stavu jedn�ho z rie�ite�ov a nedostatku �asu. Tak sa n�m podarilo implementova� aspo� logiku pres�vania kariet medzi
radmi, otacanie z balicku do stacku a presun kariet do foundation stackov. Implementovali sme prakticky v�etky hern� mechanizmy, nestihli sme u� implementova� v�as hern� logiku.


P.S Kv�li problemom s makefilom sa makefile pre GUI musi vygenerovat, tak�e pripadna dokumentacia GUI zdrojovych suborov sa musi riesit rucnym zavolanim doxygen Doxyfile