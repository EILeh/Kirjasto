/* Kirjasto
 *
 * Kuvaus:
 * Ohjelma kysyy käyttäjältä syötetiedoston nimen ja tarkistaa sen oikeellisuu-
 * den. Jos syötetiedoston avaaminen ei onnistu, tulostetaan virheilmoitus. Jos
 * syötetiedosto onnistutaan avaamaan, luetaan sen sisältö riveittäin vektoriin
 * ja tarkistetaan jokaisen rivin kohdalla, että ne eivät koostu pelkästään vä-
 * lilyönneistä ja, että tietoja on jokaisella rivillä neljä. Tiedosto pitää
 * sisällään tiedon kirjastosta, tekijästä, kirjan nimestä sekä kirjan varausten
 * määrästä. Jos kirjalla ei ole varauksia, on se ilmaistu tekstillä
 * 'on-the-shelf'. Syötetiedoston tiedot lisätään map:in, jossa avaimena on kir-
 * jasto ja hyötytietona vektori Book, jonka tyyppi on struct. Sturct Book
 * sisältää tiedot tekijästä, kirjan nimestä sekä kirjan varausten määrästä.
 * Käyttäjä voi suorittaa kirjoihin liittyviä hakuja. Komento libraries tulostaa
 * kaikki tunnetut kirjastot aakkosjärjestyksessä. Komento material tulostaa
 * aakkosjärjestyksessä kaikki syötetyn kirjaston kirjat. Komento books tulostaa
 * kirjan nimen mukaisessa aakkosjärjestyksessä kaikki syötetyn tekijän kirjat,
 * jotka löytyvät syötetystä kirjastosta sekä kirjojen varaustiedot. Komento
 * reservable tulostaa lyhyimmän varausjonon syötetyn tekijän kirjalle sekä aak-
 * kosjärjestyksessä ne kirjastot, joissa on samanpituinen varausjono. Jos kirja
 * löytyy kirjaston hyllystä, tulostetaan käyttäjälle on the shelf. Komento
 * loanable tulostaa kaikkien kirjastojen kaikista kirjoista ne, jotka löytyvät
 * hyllystä. Käyttäjälle tulostetaan kirjan tekijä sekä kirjan nimi aakkosjär-
 * jestyksessä. Käyttäjä pystyy lopettamaan ohjelman suorituksen syöttämällä
 * komennon quit.
 *
 * Ohjelman kirjoittajat
 *
 * Nimi: EILeh
 *
 * Nimi: Henri D....r
 *
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

//Tietuetyyppi kirjan tietojen esittämiseen.
struct Book
{
    string author;
    string title;
    int reservations;
};

//Globaalivakio, jonka syötettäessä ohjelman suoritus lopetetaan.
const string END_COMMAND = "quit";

//Globaalivakio, joka kertoo välilyöntien maksimimäärän.
const int MAX_AMOUNT_OF_SPACES = 2;

//Globaalivakio, jonka sisällä käyttäjä voi halutessaan ilmaista kirjan nimen.
const char OPTION_TO_SEPARATE_BOOK_NAME = '"';

vector<string> split(string line, char separator, bool parts_no_empty = false)
{
// Käy merkkijonon line läpi kirjain kirjaimelta, pilkkoo sen osiin halutun
// merkin separator kohdalta ja lisää tiedot vektoriin.

// MUUTTUJIEN ALUSTUKSET TIETOTYYPEITTÄIN AAKKOSJÄRJESTYKSESSÄ.

//  Kokonaisluvut:
    int counter = 0;

//  Merkkijonot:
    string substring = "";

//  Vektorit:
    vector<string> splitted_vector = {};

//  return: Palauttaa vektorin, joka sisältää tiedot merkkijonosta pilkottuna

    for (char c : line)
    {
        // Tarkistetaan, onko kyseinen kirjain OPTION_TO_SEPARATE_BOOK_NAME,
        // jos syötteestä löytyy OPTION_TO_SEPARATE_BOOK_NAME, mennään for-loo-
        // pissa seuraavalle kierrokselle.
        if (c == OPTION_TO_SEPARATE_BOOK_NAME)
        {
            continue;
        }

        // Jos erotinmerkki on välilyönti, lasketaan välilyöntien määrä, jotta
        // syötteestä voidaan erottaa komennot sekä tiedostosta saadut tiedot.
        if (separator == ' ')
        {
            // Jos erotinmerkki löydetään ja kierrosten määrä on pienempi kuin
            // MAX_AMOUNT_OF_SPACCES, lisätään vektoriin uusi alkio. Tyhjenne-
            // tään alimerkkijono ja kasvatetaan counter:n arvoa yhdellä. Jos
            // kyseinen kirjain ei ole erotinmerkki, lisätään alimerkkijonoon
            // uusi kirjain.
            if ((c == separator) && (counter < MAX_AMOUNT_OF_SPACES))
            {
                if (!(parts_no_empty && substring.empty()))
                {
                    splitted_vector.push_back(substring);
                    substring.clear();

                    counter++;
                }
            }
            else
            {
                substring += c;
            }
        }

        // Jos erotinmerkki on puolipiste, käydään tekstiä läpi kirjain kirjai-
        // melta. Jos kyseinen kirjain on sama kuin erotinmerkki, lisätään vek-
        // toriin alimerkkijonon sisältämä tieto ja tyhjennetään alimerkkijono.
        // Jos kyseinen kirjain ei ole erotinmerkki, lisätään alimerkkijonoon
        // uusi kirjain.
        else if (separator == ';')
        {
            if (c == separator)
            {
                if (!(parts_no_empty && substring.empty()))
                {
                    splitted_vector.push_back(substring);
                    substring.clear();
                }
            }
            else
            {
                substring += c;
            }
        }
    }
    // Lisää substring:iin muodostetun sanan splitted_vector:iin.
    if (!(parts_no_empty && substring.empty()))
    {
        splitted_vector.push_back(substring);
        substring.clear();
    }

    return splitted_vector;
}


bool spaces(const string &line_info, bool only_spaces)
{
// Käy merkkijonon line_info läpi kirjain kirjaimelta ja tarkistaa sisältääkö se
// pelkkiä välilyöntejä ja palauttaa totuusarvon löydetyn tiedon perusteella.

// return: Palauttaa totuusarvon tehdyn löydön perusteella.

    for (char c : line_info)
    {
        if (!isspace(c))
        {
            only_spaces = false;
            return only_spaces;
        }
    }
    return true;
}


bool compare_by_name(const Book& a, const Book& b)
{
// Vertailee onko a.author ennen b.author:ia aakkosissa ja palauttaa sen totuus-
// arvon löydetyn tiedon perusteella.

// return: Palauttaa totuusarvon tehdyn löydön perusteella.

    return a.author < b.author;
}


vector<Book> add_to_struct(vector<string>& line_info, vector<Book>& books,
                           map<string, vector<Book>>& file_information)
{
// Ottaa parametrinaan tiedot tiedoston riveistä vektorissa line_info, tallentaa
// vektoriin books tiedot kirjoista sekä tallentaa tiedostossa olevat kaikki
// tiedot map-rakenteeseen file_information. Funktio lisää tiedot struct raken-
// teeseen sekä struct lisätään map rakenteeseen ja muuttaa varausten määrän
// merkkijonosta kokonaisluvuksi. Jos avainta ei löydy, se luo uuden parin map-
// rakenteeseen, jos avain löytyy, lisää uuden hyötytiedon haluttuun avaimeen.

// MUUTTUJIEN ALUSTUKSET TIETOTYYPEITTÄIN AAKKOSJÄRJESTYKSESSÄ.

//  Kokonaisluvut:
    int reservations = 0;
    reservations = stoi(line_info.at(3));

//  Merkkijonot:
    string author;
    author = line_info.at(1);
    string library = line_info.at(0);
    string title;
    title = line_info.at(2);

//  STL-säiliöt:
    map<string, vector<Book>>::iterator it = file_information.find(library);

//  Tietuetyypit:
    Book book_information = {author, title, reservations};

//  return: Palauttaa vektorin books, joka sisältää tiedot kirjoista.

    // Tarkistaa, löytyykö mapista information jo kyseessä oleva kirjasto. Jos
    // kirjasto löytyy, lisätään sen hyötytiedoksi struct:ssa olevat tiedot.
    // Jos kirjastoa ei löydy, luodaan uusi avain-hyötytieto-pari.
    if (it != file_information.end())
    {
        it->second.push_back(book_information);
    }

    else
    {
        books.push_back(book_information);
        file_information.insert({library, books});
        books.clear();
    }

    return books;
}


void libraries(map<string, vector<Book>>& file_information)
{
// Tulostaa kaikki halutut kirjastot map-rakenteesta file_information, joka si-
// sältää tiedostosta saadun tiedon.

//  return: Palaa takaisin kutsufunktioon.

    // Käydään map file_information läpi ja tulostetaan kaikki kirjastot, jotka
    // löytyvät map:sta file_information.
    for (const auto &library : file_information)
    {
        cout << library.first << endl;
    }
}


void material(vector<string>& command_vector,
              map<string, vector<Book>>& file_information)
{
// Tulostaa aakkosjärjestyksessä kaikki syötetyn kirjaston kirjat. Funktio ottaa
// parametrinaan map:ssa file_information olevan tiedon. Map file_information
// sisältää kaikki tiedostosta saadut tiedot. Map:in tehdään hakuja käyttäjän
// syötteestä muodostetun vektorin command_vector perusteella.

// MUUTTUJIEN ALUSTUKSET TIETOTYYPEITTÄIN AAKKOSJÄRJESTYKSESSÄ.

//  Merkkijonot:
    string library = command_vector.at(1);

//  STL-säiliöt:
    map<string, vector<Book>>::iterator it = file_information.find(library);
    vector<Book> new_info;

//  return: Palaa takaisin kutsufunktioon.

    // Tarkistetaan löytyykö syötetty kirjasto map:sta file_information. Jos
    // päästään map file_information alusta loppuun, ei kirjastoa tällöin ole
    // löytynyt, jolloin tulostetaan virheilmoitus ja palataan kutsufunktioon.
    if (it == file_information.end())
    {
        cout << "Error: unknown library" << endl;
        return;
    }

    // Jos kirjasto löytyy tallennetaan vektoriin new_info tieto kirjoista ja
    // järjestetään se aakkosjärjestykseen.
    else
    {
        new_info = file_information.at(library);
        sort(new_info.begin(), new_info.end(), compare_by_name);

        // Käydään vektori new_info läpi ja tulostetaan kaikki annetun kirjaston
        // kirjojen tekijät sekä kirjojen nimet.
        for (unsigned long long i = 0; i < new_info.size(); i++)
        {
            cout << new_info.at(i).author << ": " <<
                    new_info.at(i).title << endl;
        }
    }
}


void books(vector<string>& command_vector,
           map<string, vector<Book>>& file_information)
{
// Tulostaa aakkosjärjestyksessä kaikki syötetyn tekijän kirjat sekä niiden va-
// raustilanteen, jotka löytyvät kyseisestä kirjastosta. Funktio ottaa paramet-
// rinaan map:ssa file_information olevan tiedon. Map file_information sisältää
// kaikki tiedostosta saadut tiedot. Map:in tehdään hakuja käyttäjän syötteestä
// muodostetun vektorin command_vector perusteella.

// MUUTTUJIEN ALUSTUKSET TIETOTYYPEITTÄIN AAKKOSJÄRJESTYKSESSÄ.

//  Merkkijonot:
    string input_author = "";
    string library = "";

//  STL-säiliöt:
    set<string> found_books;

//  return: Palaa takaisin kutsufunktioon.

    if (command_vector.size() != 3)
    {
        cout << "Error: wrong number of parameters" << endl;
        return;
    }

    // Tallennetaan library muuttujaan tieto kirjastosta sekä muuttujaan
    // input_author tieto tekijästä, jotka löytyvät vektorin command_vector
    // indekseistä.
    library = command_vector.at(1);
    input_author = command_vector.at(2);

    // Käydään map file_information läpi ja tarkistetaan löytyykö syötetty kir-
    // jasto siitä. Jos file_information päästään loppuun saakka, kirjastoa ei
    // löytynyt, jolloin tulostetaan virheilmoitus ja palataan kutsufunktioon.
    if (file_information.find(library) == file_information.end())
    {
        cout << "Error: unknown library" << endl;
        return;
    }

    // Käydään map:ssa file_information olevat kirjastot läpi ja tarkistetaan
    // löytyykö syötetty tekijä kirjastoista.
    auto library_found = file_information.at(library);

    for (auto& i : library_found)
    {
        // Jos tämänhetkinen tekijä vastaa syötettyä tekijää, lisätään kirjan
        // nimi set:in found_books.
        if (i.author == input_author)
        {
            found_books.insert(i.title);
        }
    }

    // Jos set:n found_books pituus on nolla, ei kirjailijaa löydy kirjastoista.
    // Tulostetaan virheilmoitus ja palataan kutsufunktioon.
    if (found_books.size() == 0)
    {
        cout << "Error: unknown author" << endl;
        return;
    }

    // Uloimmassa for-loopissa käydään läpi map:n file_infomation tietopareja ja
    // sisemmässä map:n file_information hyötytietoja, jolloin päästään käsiksi
    // kirjojen tietoihin.
    for (auto& pair : file_information)
    {
        for (auto& data : pair.second)
        {
            // Jos tämänhetkinen kirjasto täsmää syötettyyn kirjastoon ja tämän-
            // hetkinen tekijä täsmää syötettyyn tekijään, tarkistetaan kyseisen
            // kirjaston ja tekijän kirjojen varausten määrät.
            if ((pair.first == library) && (data.author == input_author))
            {
                // Jos kirjalla on varauksia nolla, tulostetaan kirjan nimen pe-
                // rään teksti on the shelf.
                if (data.reservations == 0)
                {
                    cout << data.title << " --- on the shelf" << endl;
                }

                // Jos varauksia on enemmän kuin nolla, tulostetaan kirjan nimen
                // perään tieto varausten määristä.
                else
                {
                    cout << data.title << " --- " << data.reservations
                         << " reservations" << endl;
                }
            }
        }
    }
}


void reservable(vector<string>& command_vector,
                map<string, vector<Book>>& file_information)
{
// Tulostaa lyhyimmän varausjonon halutun tekijän halutulle kirjailijalle sekä
// aakkosjärjestyksessä ne kirjastot, joista kirja löytyy tällä varausjonolla.
// Funktio ottaa parametrinaan map:ssa file_information olevan tiedon. Map
// file_information sisältää kaikki tiedostosta saadut tiedot. Map:in tehdään
// hakuja käyttäjän syötteestä muodostetun vektorin command_vector perusteella.

// MUUTTUJIEN ALUSTUKSET TIETOTYYPEITTÄIN AAKKOSJÄRJESTYKSESSÄ.

//  Kokonaisluvut:
    int min_reservations = 0;
    int amount_of_reservations = 0;

//  Merkkijonot:
    string author = command_vector.at(1);
    string library = "";
    string title = command_vector.at(2);

//  STL-säiliöt:
    set<string> found_books;
    set<string> on_the_shelf_set = {};
    set<string> reservations_set = {};

//  Totuusarvot:
    bool on_the_shelf = false;

//  return: Palaa takaisin kutsufunktioon.

    // Käydään uloimmassa for-loopissa läpi kirjastoja, jotka löytyvät map:n
    // file_information avain parista. Tallennetaan merkkijonolle library uusi
    // tieto eli map:n file_information avain. Sisemmässä for-loopissa
    // päästään käsiksi map:n file_information hyötytietoihin eli voidaan löytää
    // kirjojen tekijät.
    for (auto& i : file_information)
    {
        library = i.first;
        auto library_found = file_information.at(library);
        for (auto& j : library_found)
        {
            // Jos tämänhetkinen tekijä on sama kuin syötetty tekijä, lisätään
            // kirjan nimi set:in found_books.
            if (j.author == author)
            {
                found_books.insert(j.title);
            }
        }
    }

    // Kun file_information on käyty läpi, etsitään set:stä found_books syötetty
    // kirjan nimi. Jos set found_books päästään loppuun saakka ilman, että kir-
    // jan nimeä tulee vastaan, tulostetaan virheilmoitus ja palataan kutsufunk-
    // tioon.
    if (found_books.find(title) == found_books.end())
    {
        cout << "Book is not a library book" << endl;
        return;
    }

    // Uloimmassa for-loopissa käydään läpi map:n file_infomation tietopareja ja
    // sisemmässä map:n file_information hyötytietoja, jolloin päästään käsiksi
    // kirjojen tietoihin.
    for (auto& pair : file_information)
    {
        for (auto& data : pair.second)
        {
            // Jos tämänhetkinen tekijä täsmää syötettyyn tekijään ja tämänhet-
            // kinen kirjan nimi täsmää syötettyyn kirjan nimeen, tallennetaan
            // muuttujaan amount_of_reservations tämänhetkinen varausten määrä.
            if ((data.author == author) && (data.title == title))
            {
                amount_of_reservations = data.reservations;

                // Jos kirjalla on varauksia sata tai enemmän, tulostetaan vir-
                // heilmoitus ja palataan kutsufunktioon.
                if (amount_of_reservations >= 100)
                {
                    cout << "Book is not reservable from any library" << endl;
                    return;
                }

                // Jos varauksia on nolla, lisätään kirjasto set:in
                // on_the_shelf_set ja tallennetaan muuttujan on_the_shelf to-
                // tuusarvoksi true.
                else if (amount_of_reservations == 0)
                {
                    on_the_shelf_set.insert(pair.first);
                    on_the_shelf = true;
                }

                // Jos varausten määrä on pienempi kuin varausten tämänhetkinen
                // vähimmäismäärä tai varausten vähimmäismäärä on nolla, päivi-
                // tetään varausten vähimmäismääräksi uusi vähimmäismäärä, joka
                // saatiin muuttujan amount_of_reservations tämänhetkisestä
                // arvosta. Tyhjennetään reservations_set, jotta vanha tieto ei
                // jää talteen ja lisätään kirjasto set:in reservations_set.
                else if (amount_of_reservations < min_reservations ||
                         min_reservations == 0)
                {
                    min_reservations = amount_of_reservations;
                    reservations_set.clear();
                    reservations_set.insert(pair.first);
                }

                // Jos muuttujan amount_of_reservations arvo on yhtä suuri kuin
                // muuttujan min_reservations, lisätään kirjasto set:in
                // reservations_set.
                else if (amount_of_reservations == min_reservations)
                {
                    reservations_set.insert(pair.first);
                }
            }
        }
    }

    // Jos muuttujan on_the_shelf totuusarvoksi on saatu true, tulostetaan ne
    // kirjastot, joissa kirjan on hyllyssä käymällä for-loopilla läpi set
    // on_the_shelf_set.
    if (on_the_shelf == true)
    {
        cout << "on the shelf" << endl;

        for (auto& library : on_the_shelf_set)
        {
            cout << "--- " << library << endl;
        }
    }

    // Jos on_the_shelf totuusarvo on false, tulostetaan muuttujaan
    // min_reservations saatu tieto sekä sen alapuolelle tieto kirjastoista,
    // joissa on lyhin varausjono. Kirjastot saadaan tulostettua käymällä for-
    // loopin avulla läpi set reservations_set.
    else
    {
        cout << min_reservations << " reservations" << endl;

        for (auto& library : reservations_set)
        {
            cout << "--- " << library << endl;
        }
    }
}


void loanable(map<string, vector<Book>>& file_information)
{
// Etsii kaikista kirjastoista kaikki ne kirjat, jotka löytyvät hyllystä ja tu-
// lostaa kirjan tekijän sekä kirjan nimen aakkosjärjestyksessä ensin tekijän
// mukaan ja sitten kirjan nimen mukaan. Funktio ottaa parametrinaan map:ssa
// file_information olevan tiedon. Map file_information sisältää kaikki tiedos-
// tosta saadut tiedot.

// MUUTTUJIEN ALUSTUKSET TIETOTYYPEITTÄIN AAKKOSJÄRJESTYKSESSÄ.

//  STL-säiliöt:
    multimap<string, string> books_available;

//  return: Palaa takaisin kutsufunktioon.

    // Uloimmassa for-loopissa käydään läpi map:n file_infomation tietopareja ja
    // sisemmässä map:n file_information hyötytietoja, jolloin päästään käsiksi
    // kirjojen tietoihin.
    for (auto& pair : file_information)
    {
        for (auto& data : pair.second)
        {
            // Kirjoista haluttiin tulostaa ne, jotka löytyvät hyllystä eli joi-
            // den varaustilanne on nolla. Lisätään kaikki tällaisten kirjojen
            // tekijä sekä kirjan nimi multimap:in books_available.
            if (data.reservations == 0)
            {
                string author = data.author;
                string title = data.title;
                books_available.insert({author, title});
            }
        }
    }
    // Alustetaan set books multimap:in books_available sisällöllä.
    set<pair<string,string>> books(books_available.begin(),
                                   books_available.end());

    // Käydään set books läpi alusta loppuun for-loopin avulla ja tulostetaan
    // sen tietoalkiot, joista first on tekijä ja second on kirjan nimi.
    for(const auto& pair : books)
    {
        cout << pair.first << ": " << pair.second << endl;
    }
}


void ask_a_command (map<string, vector<Book>>& file_information)
{
// Kysyy käyttäjältä minkälaista tietoa hän haluaa tiedostosta etsiä. Funktio
// ottaa parametrinaan map:ssa file_information olevan tiedon. Map
// file_information sisältää kaikki tiedostosta saadut tiedot.

// MUUTTUJIEN ALUSTUKSET TIETOTYYPEITTÄIN AAKKOSJÄRJESTYKSESSÄ.

//  Merkkijonot:
    string command = "";
    char separator = ' ';

//  Vektorit:
    vector<string> command_vector;

//  return: Palaa takaisin kutsufunktioon.

    while (true)
    {
        cout << "lib> ";
        getline(cin, command);

        // Käyttäjä syöttää tiedot välilyönneillä erotettuna siten, että ensim-
        // mäisenä syötetään komento ja sen jälkeen mahdolliset muut tiedot
        // (kirjasto, tekijä, kirjan nimi). Komento saadaan pilkkomalla käyttä-
        // jän syöte välilyönnin kohdalta ja tallentamalla se vektoriin
        // command_vector. Vektorin indeksistä nolla löytyy tieto käyttäjän
        // syöttämästä komennosta.
        command_vector.push_back(command);
        command_vector = split(command, separator, true);

        if (command == "libraries")
        {
            libraries(file_information);
        }

        else if (command_vector.at(0) == "material")
        {
            material(command_vector, file_information);
        }

        else if (command_vector.at(0) == "books")
        {

            books(command_vector, file_information);
        }

        else if (command_vector.at(0) == "reservable")
        {
            reservable(command_vector, file_information);
        }

        else if (command == "loanable")
        {
            loanable(file_information);
        }

        // Jos käyttäjä syöttää lopetuskomennon, ohjelman suoritus lopetetaan.
        else if (command == END_COMMAND)
        {
            // Palataan takaisin kutsufunktioon.
            return;
        }

        // Jos käyttäjän syöttämää komentoa ei löydy, tulostetaan virheilmoitus.
        else
        {
            cout << "Error: unknown command" << endl;
        }
    }
}


int main()
{
// MUUTTUJIEN ALUSTUKSET TIETOTYYPEITTÄIN AAKKOSJÄRJESTYKSESSÄ.

//  Merkkijonot:
    string file = "";
    string line = "";

//  STL-säiliöt:
    vector<Book> books;
    vector<string> line_info;
    map<string, vector<Book>> file_information;

    cout << "Input file: ";
    getline(cin, file);

    ifstream input_file(file);

    // Jos tiedoston avaaminen ei onnistu, tulostetaan virheilmoitus ja ohjelman
    // suoritus päättyy paluuarvoon EXIT_FAILURE.
    if (!input_file)
    {
        cout << "Error: input file cannot be opened" << endl;
        input_file.close();
        return EXIT_FAILURE;
    }

    // Tiedoston rivit käydään läpi ja rivit pilkotaan puolipisteen kohdalta
    // vektorin line_info alkioiksi.
    while (getline(input_file, line))
    {
        line_info = split(line, ';', true);

        //Jokainen alkio tarkistetaan, että se ei sisällä pelkkiä välilyöntejä
        // ja alkioita on oikea määrä eli neljä.
        for (const string &word : line_info)
        {
            bool only_spaces = true;

            // Jos tiedoston rivillä tieto koostuu pelkistä välilyönneistä tai
            // rivillä on muu määrä kuin neljä tietoa, tulostetaan virheilmoitus
            // ja ohjelman suoritus päättyy paluuarvoon EXIT_FAILURE.
            if (spaces(word, only_spaces) || (line_info.size() != 4))
            {
                cout << "Error: empty field" << endl;
                input_file.close();
                return EXIT_FAILURE;
            }

            // Jos vektorin indeksissä kolme oleva alkio on on-the-shelf,
            // muutetaan indeksin kolme arvoksi nolla.
            if ( line_info.at(3) == "on-the-shelf" )
            {
                line_info.at(3) = "0";
            }
        }

        books = add_to_struct(line_info, books, file_information);
    }
    input_file.close();

    ask_a_command(file_information);

    return EXIT_SUCCESS;
}
