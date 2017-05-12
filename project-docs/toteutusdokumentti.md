# Toteutusdokumentti

## Toteutus

Asetusten määrittämisen jälkeen kutsutaan enkoodaus/dekoodausfunktiota. Molemmissa tapauksissa
luodaan StringTable-olio, joka aina allokoi 2n tavua, jossa n on koodiavainten bittikoko (12 tai 16). Sen
lisäksi taulukon jokaiselle avaimelle luodaan linkitetty lista, joka enkoodatessa osoittaa seuraavaan
avaimeen ja dekoodatessa edelliseen avaimeen, muodostaen merkkijonoja.
Lähdetiedosto käydään läpi symboli kerrallaan (enkoodatessa tavu, dekoodatessa 12- tai 16-bittinen
koodi). Jokainen uusi merkkijono talletetaan StringTable-olioon. Taulukon täyttyessä taulukko
tyhjennetään ja kirjoitetaan/luetaan arvo 0xFFFF, joka kertoo milloin taulukko tulee tyhjentää.
Vaativuusanalyysi

## Tilavaativuus

Tilavaativuus on sekä enkoodatessa että dekoodatessa vakio koodisanan bittipituuteen nähden.
Tilavaativuus ei muutu tiedostokoon kasvaessa, sillä taulukon täyttyessä se tyhjennetään.
Tilavaativuuden skaalautuvuus on siis O(1) tiedostokokoon nähden ja O(2<sup>n</sup>
) bittipituuteen nähden.

## Aikavaativuus

Aikavaativuus on sekä enkoodatessa että dekoodatessa on suoraan suhteessa lähdetiedoston kokoon,
joten aikavaativuus on O(n).

## Parannusmahdollisuudet

Ohjelmassa on edellytykset rinnakkaislaskennalle, mutta tämä ominaisuus on jätetty pois ohjelmasta,
sillä se ei ole olennaista kurssin päämäärien kannalta.

## Käytetyt lähteet

* http://web.mit.edu/6.02/www/s2012/handouts/3.pdf
* http://michael.dipperstein.com/lzw/
* https://users.cs.cf.ac.uk/Dave.Marshall/Multimedia/node214.html
