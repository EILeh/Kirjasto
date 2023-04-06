# Kirjasto

Ohjelma kysyy käyttäjältä syötetiedoston nimen ja tarkistaa sen oikeellisuu-
den. Jos syötetiedoston avaaminen ei onnistu, tulostetaan virheilmoitus. Jos
syötetiedosto onnistutaan avaamaan, luetaan sen sisältö riveittäin vektoriin
ja tarkistetaan jokaisen rivin kohdalla, että ne eivät koostu pelkästään vä-
lilyönneistä ja, että tietoja on jokaisella rivillä neljä. Tiedosto pitää
sisällään tiedon kirjastosta, tekijästä, kirjan nimestä sekä kirjan varausten
määrästä. Jos kirjalla ei ole varauksia, on se ilmaistu tekstillä
'on-the-shelf'. Syötetiedoston tiedot lisätään map:in, jossa avaimena on kir-
jasto ja hyötytietona vektori Book, jonka tyyppi on struct. Sturct Book
sisältää tiedot tekijästä, kirjan nimestä sekä kirjan varausten määrästä.
Käyttäjä voi suorittaa kirjoihin liittyviä hakuja. Komento libraries tulostaa
kaikki tunnetut kirjastot aakkosjärjestyksessä. Komento material tulostaa
aakkosjärjestyksessä kaikki syötetyn kirjaston kirjat. Komento books tulostaa
kirjan nimen mukaisessa aakkosjärjestyksessä kaikki syötetyn tekijän kirjat,
jotka löytyvät syötetystä kirjastosta sekä kirjojen varaustiedot. Komento
reservable tulostaa lyhyimmän varausjonon syötetyn tekijän kirjalle sekä aak-
kosjärjestyksessä ne kirjastot, joissa on samanpituinen varausjono. Jos kirja
löytyy kirjaston hyllystä, tulostetaan käyttäjälle on the shelf. Komento
loanable tulostaa kaikkien kirjastojen kaikista kirjoista ne, jotka löytyvät
hyllystä. Käyttäjälle tulostetaan kirjan tekijä sekä kirjan nimi aakkosjär-
jestyksessä. Käyttäjä pystyy lopettamaan ohjelman suorituksen syöttämällä
komennon quit.
