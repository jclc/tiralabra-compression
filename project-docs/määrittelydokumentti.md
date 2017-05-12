# Määrittelydokumentti

## Yleiskuva

Tiralabra-Compression toteuttaa Lempel-Ziv-Welch -algoritmin enkooderina sekä dekooderina.
Toteutetulla ohjelmalla voi tiivistää minkä tahansa tiedoston 12- tai 16-bittisillä koodiavaimilla. LZWalgoritmi
on hyvin suosittu kompressioalgoritmi ja se ei edellytä erillistä koodiavaintaulukkoa, vaan
taulukko rakennetaan enkoodatessa sekä dekoodatessa. Tämä tekee LZW-algoritmista myös erittäin
sopeutuvan, sillä kooditaulukko tyhjennetään sen täyttyessä ja täytetään uusilla avainsanoilla. Näin
ollen algoritmi sopeutuu tiedoston sisällä vaihtuviin symbolien esiintymistiheyksiin.

## Käytetyt tietorakenteet

* Taulukot
* Linkitetyt listat
* Tasapainotettu binääripuu (mahdollisena optimointina projektin loppupuolella)

## Validit syötteet

LZW on häviötön algoritmi, joten syötteeksi kelpaa mikä tahansa tiedosto. Enkoodatut tiedostot
sisältävät tunnisteet, jolla ohjelma osaa dekoodata ne.
Vaativuusmäärittely
LZW-algoritmi on sopeutuva algoritmi, jossa taulukon maksimikoko ei riipu lähdetiedoston koosta.
Koska taulukko tyhjennetään tietyin väliajoin, enkoodaus/dekoodausprosessin voi ajatella jakautuvan
tietynmittaisiin, erillisiin paloihin.
