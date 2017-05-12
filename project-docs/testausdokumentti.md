# Testausdokumentti

## Testauksen laajuus

Jokaista käännösyksikköä kohden (main.cpp:tä lukuunottamatta) luodaan yksi testitiedosto. Kussakin
testitiedostossa on useampi testi jotka testaavat eri ominaisuuksia sekä ääritapauksia.
Näiden lisäksi toteutetaan integraatiotestejä, jossa useampia luokkia sisällytetään suurempiin luokkiin,
jotka testaavat ohjelman toimivuutta.

Koska main-funktiota on hyvin vaikeaa ja epäkäytännöllistä testata, sen suorittama toiminnallisuus
testataan integraatiotesteillä. Integraatiotestit suorittavat enkoodauksen ja dekoodauksen samalla
lähdetiedostolla, varmistaen että ohjelma tuottaa identtisen tiedoston dekoodaamisen jälkeen.

## Testien suoritus

Testien suoritus toimii CMake:n sisäänrakennetun testiajoympäriston ctest:in avulla. Ohjeet
README.md:ssä. Testit vaativat että Google Test on asennettu.
