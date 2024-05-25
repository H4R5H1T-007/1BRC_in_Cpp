/* C++ code produced by gperf version 3.0.3 */
/* Command-line: /Library/Developer/CommandLineTools/usr/bin/gperf -L C++ results.txt  */
/* Computed positions: -k'1,3,5,$' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif


#define TOTAL_KEYWORDS 413
#define MIN_WORD_LENGTH 3
#define MAX_WORD_LENGTH 26
#define MIN_HASH_VALUE 5
#define MAX_HASH_VALUE 1268
/* maximum key range = 1264, duplicates = 0 */

class Perfect_Hash
{
private:
  static inline unsigned int hash (const char *str, unsigned int len);
public:
  static const char *in_word_set (const char *str, unsigned int len);
};

inline unsigned int
Perfect_Hash::hash (register const char *str, register unsigned int len)
{
  static unsigned short asso_values[] =
    {
      1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
      1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
      1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
      1269, 1269,  110, 1269, 1269, 1269, 1269, 1269, 1269,    0,
      1269,    0, 1269, 1269, 1269,    0,    0, 1269, 1269, 1269,
      1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
      1269, 1269, 1269, 1269, 1269,  145,   10,  240,   65,  175,
        33,  413,  320,  280,   30,  190,  325,    0,  340,  335,
       170, 1269,  385,  105,  115,   40,  456,  190,    0,  340,
         0, 1269, 1269, 1269, 1269, 1269, 1269,    0,  280,  280,
       310,   15,   15,  250,  225,    5,  210,   35,   25,   90,
         0,   30,  325,    5,    5,   20,  105,  200,  275,  315,
         5,  260,  130, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
      1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
      1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
      1269, 1269, 1269,    0, 1269, 1269, 1269, 1269, 1269, 1269,
      1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,    5,  325,
      1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
      1269, 1269, 1269, 1269,   20, 1269, 1269, 1269,   10, 1269,
      1269, 1269, 1269, 1269, 1269,    5,   10,    0, 1269, 1269,
      1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
      1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
      1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
      1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
      1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269, 1269,
      1269, 1269, 1269, 1269, 1269, 1269
    };
  register unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[4]];
      /*FALLTHROUGH*/
      case 4:
      case 3:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

const char *
Perfect_Hash::in_word_set (register const char *str, register unsigned int len)
{
  static const char * wordlist[] =
    {
      "", "", "", "", "",
      "Xi'an",
      "", "", "", "", "", "", "", "", "",
      "Miami",
      "", "", "", "", "", "", "", "", "",
      "Bratislava",
      "Berlin",
      "", "", "",
      "Milan",
      "Manila",
      "",
      "\303\234r\303\274mqi",
      "",
      "Busan",
      "Bergen",
      "",
      "Montreal",
      "Barcelona",
      "",
      "Burnie",
      "",
      "Bordeaux",
      "Marseille",
      "Fianarantsoa",
      "Minneapolis",
      "",
      "Murmansk",
      "Milwaukee",
      "Boise",
      "",
      "Makurdi",
      "", "", "",
      "Ulaanbaatar",
      "", "", "", "", "", "",
      "Belgrade",
      "Baltimore",
      "Mango",
      "Boston",
      "",
      "Makassar",
      "",
      "Dhaka",
      "Bilbao",
      "Mek'ele",
      "Jos",
      "",
      "Minsk",
      "Durban",
      "Jakarta",
      "Denpasar",
      "Melbourne",
      "Birao",
      "Darwin",
      "", "",
      "Fresno",
      "",
      "Bosaso",
      "Bangkok",
      "", "", "",
      "Denver",
      "", "", "", "",
      "Manama",
      "Mombasa",
      "",
      "Dili",
      "",
      "Mumbai",
      "", "",
      "Flores",
      "Fukuoka",
      "",
      "Bishkek",
      "Dushanbe",
      "", "",
      "Sana'a",
      "Moncton",
      "Djibouti",
      "",
      "Dakar",
      "Dallas",
      "", "",
      "Bata",
      "", "", "", "",
      "Toamasina",
      "Sofia",
      "Tirana",
      "", "",
      "Singapore",
      "",
      "Muscat",
      "Dolisie",
      "",
      "Saskatoon",
      "",
      "Dikson",
      "Tbilisi",
      "Blantyre",
      "", "", "",
      "Bloemfontein",
      "San Juan",
      "", "",
      "Taipei",
      "Toliara",
      "", "", "",
      "Thi\303\250s",
      "Tallinn",
      "",
      "Jerusalem",
      "",
      "\304\260zmir",
      "Toronto",
      "San Jose",
      "",
      "Tunis",
      "",
      "Tripoli",
      "",
      "Aden",
      "St. John's",
      "Brazzaville",
      "Thessaloniki",
      "",
      "Alexandra",
      "Alexandria",
      "Bamako",
      "Dampier",
      "", "",
      "Praia",
      "Austin",
      "Atlanta",
      "Santo Domingo",
      "", "",
      "San Francisco",
      "Frankfurt",
      "Adelaide",
      "", "", "",
      "Philadelphia",
      "Dar es Salaam",
      "",
      "Seoul",
      "Ankara",
      "Troms\303\270",
      "", "", "",
      "Kankan",
      "",
      "Alice Springs",
      "", "", "",
      "Karonga",
      "Damascus",
      "Maun",
      "Kandi",
      "",
      "Kuala Lumpur",
      "",
      "San Diego",
      "Tampa",
      "Port-Gentil",
      "Phoenix",
      "Portland (OR)",
      "",
      "Tokyo",
      "Batumi",
      "",
      "Kingston",
      "Pontianak",
      "Paris",
      "Bangui",
      "Kolkata",
      "Pretoria",
      "Kano",
      "Washington",
      "Arkhangelsk",
      "San Salvador",
      "", "",
      "Wellington",
      "",
      "Seattle",
      "", "",
      "Whitehorse",
      "Bissau",
      "Palermo",
      "",
      "Marrakesh",
      "Porto",
      "Banjul",
      "Saint-Pierre",
      "", "", "",
      "Asmara",
      "Z\303\274rich",
      "Benghazi",
      "Baku",
      "",
      "Tamale",
      "", "", "", "",
      "Astana",
      "Managua",
      "Brussels",
      "",
      "Chiang Mai",
      "Kuopio",
      "",
      "Canberra",
      "", "",
      "Antsiranana",
      "",
      "Mandalay",
      "Stockholm",
      "",
      "Cairns",
      "",
      "Edmonton",
      "",
      "Bridgetown",
      "",
      "Beijing",
      "Zanzibar City",
      "Amsterdam",
      "",
      "Sokoto",
      "Chicago",
      "Tashkent",
      "Monterrey",
      "Kyoto",
      "Da Lat",
      "Kampala",
      "",
      "Charlotte",
      "",
      "San Antonio",
      "Antananarivo",
      "",
      "Port Vila",
      "Port Sudan",
      "Douala",
      "",
      "Mexicali",
      "", "",
      "Baguio",
      "",
      "Upington",
      "", "",
      "Ifrane",
      "Pointe-Noire",
      "", "",
      "Cairo",
      "Kumasi",
      "Detroit",
      "",
      "Juba",
      "Medan",
      "Monaco",
      "",
      "Brisbane",
      "Bujumbura",
      "",
      "Tamanrasset",
      "El Paso",
      "Tauranga",
      "", "",
      "Beirut",
      "Honiara",
      "",
      "Hanga Roa",
      "Lhasa",
      "",
      "Tijuana",
      "", "",
      "Hanoi",
      "Harbin",
      "Palm Springs",
      "", "",
      "Omaha",
      "Malabo",
      "Memphis",
      "", "",
      "Split",
      "Tehran",
      "Fairbanks",
      "Hargeisa",
      "",
      "Ouahigouya",
      "Harare",
      "Niigata",
      "",
      "Hiroshima",
      "Odesa",
      "Dublin",
      "Jacksonville",
      "Sarajevo",
      "Lyon",
      "Dubai",
      "London",
      "",
      "Helsinki",
      "", "",
      "Skopje",
      "Abidjan",
      "Shanghai",
      "Heraklion",
      "",
      "Moscow",
      "Halifax",
      "",
      "Abha",
      "Ndola",
      "Yangon",
      "", "", "", "",
      "Lisbon",
      "Dunedin",
      "Columbus",
      "Suva",
      "",
      "Lusaka",
      "Nairobi",
      "Bulawayo",
      "", "",
      "Prague",
      "Colombo",
      "Khartoum",
      "Oslo",
      "",
      "Athens",
      "",
      "Surabaya",
      "",
      "Sochi",
      "", "", "",
      "Bucharest",
      "",
      "Tabora",
      "Erzurum",
      "", "", "", "", "", "",
      "N'Djamena",
      "",
      "Anadyr",
      "Parakou",
      "Istanbul",
      "", "",
      "Yellowknife",
      "Nakhon Ratchasima",
      "Kinshasa",
      "Guadalajara",
      "Sacramento",
      "Toluca",
      "Seville",
      "", "",
      "Accra",
      "Tucson",
      "Da Nang",
      "Suwa\305\202ki",
      "", "",
      "Belize City",
      "Algiers",
      "", "", "", "", "",
      "Hamilton",
      "Mahajanga",
      "Garissa",
      "", "",
      "Rostov-on-Don",
      "", "",
      "Palmerston North",
      "Kunming",
      "Winnipeg",
      "Chihuahua",
      "Chi\310\231in\304\203u",
      "Albuquerque",
      "",
      "La Ceiba",
      "St. Louis",
      "",
      "Kansas City",
      "Irkutsk",
      "", "", "",
      "Maputo",
      "", "",
      "San Jos\303\251",
      "",
      "Dodoma",
      "", "",
      "Kyiv",
      "",
      "Andorra la Vella",
      "Vienna",
      "",
      "Anchorage",
      "",
      "Saint Petersburg",
      "Wichita",
      "Ashgabat",
      "", "",
      "Addis Ababa",
      "Karachi",
      "",
      "Valencia",
      "Ouarzazate",
      "", "",
      "Villahermosa",
      "Rome",
      "Phnom Penh",
      "",
      "Sapporo",
      "Changsha",
      "",
      "Vancouver",
      "",
      "Christchurch",
      "City of San Marino",
      "Valletta",
      "", "",
      "Vladivostok",
      "", "",
      "Erbil",
      "Lake Tekapo",
      "",
      "Vilnius",
      "Salt Lake City",
      "",
      "Warsaw",
      "Johannesburg",
      "",
      "Podgorica",
      "",
      "Los Angeles",
      "Yakutsk",
      "", "",
      "Kabul",
      "", "", "", "",
      "Pittsburgh",
      "Panama City",
      "Calgary",
      "", "", "",
      "Tabriz",
      "", "", "", "",
      "Las Palmas de Gran Canaria",
      "Conakry",
      "Wroc\305\202aw",
      "Palembang",
      "",
      "Ouagadougou",
      "", "", "",
      "Willemstad",
      "Zagreb",
      "Cotonou",
      "Honolulu",
      "Ghanzi",
      "",
      "Mexico City",
      "Port Moresby",
      "",
      "Ljubljana",
      "Gangtok",
      "", "",
      "Gjoa Haven",
      "Oulu",
      "",
      "Nassau",
      "",
      "Tel Aviv",
      "Naha",
      "Louisville",
      "La Paz",
      "",
      "Yinchuan",
      "",
      "Copenhagen",
      "Lahore",
      "Bouak\303\251",
      "",
      "Nuuk",
      "", "",
      "Entebbe",
      "", "", "", "", "", "",
      "Petropavlovsk-Kamchatsky",
      "",
      "Cracow",
      "Iqaluit",
      "Wau",
      "Kathmandu",
      "", "", "", "", "",
      "Vientiane",
      "Havana",
      "", "", "",
      "Mzuzu",
      "Almaty",
      "", "",
      "Lviv",
      "Chittagong",
      "Roseau",
      "",
      "Timbuktu",
      "", "", "", "", "", "",
      "Lagos",
      "Niamey",
      "Indianapolis",
      "Jayapura",
      "Garoua",
      "",
      "Livingstone",
      "Yerevan",
      "", "",
      "Perth",
      "Madrid",
      "Houston",
      "", "", "", "", "", "",
      "Riga",
      "",
      "Luanda",
      "", "", "",
      "Libreville",
      "Lodwar",
      "Nicosia",
      "", "", "", "", "", "", "", "",
      "Tegucigalpa",
      "Reggane",
      "",
      "Nashville",
      "", "", "", "",
      "Cabo San Lucas",
      "",
      "S\303\251gou",
      "", "", "", "", "", "",
      "Odienn\303\251",
      "", "", "", "", "", "",
      "Mal\303\251",
      "Novosibirsk",
      "", "",
      "Cape Town",
      "Ahvaz",
      "", "", "",
      "Hong Kong",
      "Nouakchott",
      "Napier",
      "", "",
      "Edinburgh",
      "Luxembourg City",
      "Sydney",
      "", "",
      "Gagnoa",
      "",
      "Napoli",
      "Guatemala City",
      "Yaound\303\251",
      "George Town",
      "Virginia Beach",
      "", "", "",
      "Pyongyang",
      "Lubumbashi",
      "", "", "", "", "",
      "Hobart",
      "", "", "", "",
      "Gaborone",
      "Rangpur",
      "",
      "Gab\303\250s",
      "", "", "", "", "",
      "Assab",
      "", "", "",
      "New Delhi",
      "", "", "", "", "", "", "", "", "",
      "", "",
      "Lake Havasu City",
      "", "", "", "", "", "", "", "", "",
      "", "",
      "Budapest",
      "", "",
      "Ottawa",
      "",
      "Ab\303\251ch\303\251",
      "", "", "", "",
      "Auckland",
      "Mogadishu",
      "", "", "", "", "", "", "",
      "Hat Yai",
      "",
      "Chongqing",
      "",
      "Kuwait City",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "",
      "Launceston",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "",
      "Las Vegas",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "Oklahoma City",
      "", "", "", "", "", "",
      "Oranjestad",
      "",
      "Hamburg",
      "", "", "", "",
      "Guangzhou",
      "", "", "", "",
      "Ngaound\303\251r\303\251",
      "",
      "Veracruz",
      "Rabat",
      "", "", "", "", "", "",
      "Baghdad",
      "", "", "", "", "", "", "", "", "",
      "", "", "",
      "Reykjav\303\255k",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "",
      "Ho Chi Minh City",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "",
      "New Orleans",
      "", "", "", "", "", "", "", "", "",
      "Vaduz",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "",
      "Nouadhibou",
      "", "", "", "", "", "", "", "", "",
      "Lom\303\251",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "",
      "Riyadh",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "New York City"
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
          register const char *s = wordlist[key];

          if (*str == *s && !strcmp (str + 1, s + 1))
            return s;
        }
    }
  return 0;
}
