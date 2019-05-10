var DISPLAY_OFF = true;
var Link = /** @class */ (function () {
    function Link(link, description, big_description) {
        this.link = link;
        this.description = description;
        this.big_description = big_description;
    }
    Link.prototype.getHTML = function () {
        var node = document.createElement("a");
        node.classList.add("link");
        node.href = this.link;
        node.innerText = this.description;
        if (this.big_description != null) {
            var text = document.createElement("p");
            text.innerText = this.big_description;
            node.appendChild(text);
        }
        return node;
    };
    return Link;
}());
var Lesson = /** @class */ (function () {
    function Lesson() {
    }
    Lesson.prototype.ext = function () {
        this.class_num = "e";
        return this;
    };
    Lesson.prototype.display = function (value) {
        this.display_on = value;
        return this;
    };
    Lesson.prototype.intro = function () {
        this.class_num = 'i';
        return this;
    };
    Lesson.prototype.setDesc = function (description) {
        this.description = description;
        return this;
    };
    Lesson.prototype.setSubject = function (subject) {
        this.subject = subject;
        return this;
    };
    Lesson.prototype.setDate = function (day, month, year) {
        this.date = new Date(year, month - 1, day);
        return this;
    };
    ;
    Lesson.prototype.setIOI = function (ioi) {
        this.ioi = ioi;
        return this;
    };
    Lesson.prototype.setExpDate = function (month, year) {
        this.expected_date = new Date();
        this.expected_date.setFullYear(year, month - 1);
        return this;
    };
    Lesson.prototype.setCode = function (code) {
        this.code = code;
        return this;
    };
    Lesson.prototype.setLinks = function (links) {
        this.links = links;
        return this;
    };
    Lesson.prototype.getDate = function () {
        if (this.date !== undefined) {
            var date = this.date;
            return (date.getDate()) + "/" + (date.getMonth() + 1) + " " + date.getFullYear();
        }
        if (this.expected_date !== undefined) {
            var date = this.expected_date;
            return (date.getMonth() + 1) + "/" + date.getFullYear() + "?";
        }
        return "";
    };
    Lesson.get_HTML_head = function (fields, names) {
        var row = document.createElement("tr");
        for (var i in fields) {
            var field = fields[i];
            var col = document.createElement("th");
            col.innerHTML = names[i];
            col.classList.add("head_" + field);
            row.appendChild(col);
        }
        return row;
    };
    Lesson.prototype.get_HTML_row = function (fields) {
        var row = document.createElement("tr");
        for (var _i = 0, fields_1 = fields; _i < fields_1.length; _i++) {
            var field = fields_1[_i];
            var col = document.createElement("td");
            row.appendChild(col);
            col.classList.add("row_" + field);
            var value = this[field];
            if (field == 'date') {
                var date = this.getDate();
                col.innerHTML = date;
                if (date.indexOf("?") != -1 || date == "") {
                    row.classList.add("expected_time");
                }
                else {
                    row.classList.add("accurate_time");
                }
            }
            else if (field == 'links') {
                if (typeof this.links !== 'undefined') {
                    iter_add_elements_to_parent(col, this.links);
                }
            }
            else {
                if (value !== undefined)
                    col.innerHTML = value;
            }
        }
        return row;
    };
    return Lesson;
}());
function add_lessons() {
    var lesson_section_int = document.getElementById("lessons_introductory");
    var lesson_section_ext = document.getElementById("lessons_extension");
    var table_int = document.createElement("table");
    var table_ext = document.createElement("table");
    var fields = ["subject", "date", "description", "links"];
    var names = ["Temat", "Data", "Opis", "Linki"];
    // lesson_section_int.appendChild(table_int);
    lesson_section_ext.appendChild(table_ext);
    table_int.id = "introductory";
    table_ext.id = "extension";
    //table_int.appendChild(Lesson.get_HTML_head(fields, names))
    table_ext.appendChild(Lesson.get_HTML_head(fields, names));
    for (var _i = 0, lessons_1 = lessons; _i < lessons_1.length; _i++) {
        var lesson = lessons_1[_i];
        //console.log(lesson_str);
        if (lesson.display_on == 1) {
            var container = lesson.get_HTML_row(fields);
            //if (lesson.class_num == "i") {
            //table_int.appendChild(container);
            //} else {
            table_ext.appendChild(container);
            //}
        }
    }
}
var Book = /** @class */ (function () {
    function Book(name, author, comment, link) {
        this.name = name;
        this.author = author;
        this.comment = comment;
        this.link = link;
        return this;
    }
    Book.prototype.getHTML = function () {
        var node = document.createElement("a");
        if (this.link) {
            node.href = this.link;
        }
        node.innerText = this.name;
        if (this.author) {
            node.innerText += ", " + this.author;
        }
        if (this.comment) {
            node.innerText += " (" + this.comment + ")";
        }
        return node;
    };
    return Book;
}());
function iter_add_elements_to_parent(parent, array) {
    for (var _i = 0, array_1 = array; _i < array_1.length; _i++) {
        var elem = array_1[_i];
        parent.appendChild(elem.getHTML());
    }
}
function iter_add_elements(parent_id, array) {
    var section = document.getElementById(parent_id);
    iter_add_elements_to_parent(section, array);
}
function main() {
    iter_add_elements("testers", testers);
    iter_add_elements("materials", materials);
    iter_add_elements("books", books);
    add_lessons();
}
var testers = [
    new Link("https://szkopul.edu.pl/", "Szkopuł"),
    new Link("https://www.spoj.com/", "spoj.com"),
    new Link("https://pl.spoj.com/", "spoj.pl"),
    new Link("https://sio2.mimuw.edu.pl/", "SIO2"),
    new Link("https://codeforces.com/", "Codeforces")
];
var materials = [
    new Link("https://oi.edu.pl", "OI"),
    new Link("files/ioi-syllabus-2017.pdf", "IOI - Sylabus"),
    new Link("https://om.edu.pl", "OM"),
    new Link("http://archom.ptm.org.pl/", "ARCHOM"),
];
var books = [
    new Book("Kółko Matematyczne dla Olimpijczyków", "Pawłowski, Henryk", undefined, "https://www.matematyka.pl/3263.htm"),
    new Book("Wprowadzenie do algorytmów", " Cormen Thomas H., Leiserson Charles E., Rivest Ronald L, Clifford Stein "),
    new Book("Inne", undefined, undefined, "https://oi.edu.pl/l/oi_zalecana_literatura/")
];
var lessons = [
    new Lesson().ext()
        .setSubject("Inne").display(1)
        .setDesc("Materiały z zeszłych lat")
        .setLinks([
        new Link("files/old/index.html", "Stara strona (2017/2018)")
    ]),
    new Lesson().ext()
        .setSubject("Programowanie dynamiczne").display(1).setDate(19, 10, 2018)
        .setDesc("Programowanie dynamiczne na grafach, Sortowanie topologiczne")
        .setLinks([
        new Link("files/01-Indukcja/indukcja.pdf", "Skrypt"),
        new Link("https://www.spoj.com/problems/EDIST/", "EDIST (SPOJ)"),
        new Link("https://www.spoj.com/problems/ADVEDIST/", "ADVEDIST (SPOJ)"),
        new Link("https://oi.edu.pl/static/attachment/20171006/oi23.pdf", "23 OI - Nadajniki s.81 (dla zainteresowanych)"),
        new Link("https://www.youtube.com/watch?v=R1C0sSrOucM", "Omówienie Nadajników (dla zainteresowanych)"),
    ]),
    new Lesson().ext()
        .setSubject("Drzewa przedziałowe").display(1).setDate(26, 10, 2018)
        .setDesc("Statyczne drzewa przedziałowe")
        .setLinks([
        new Link("https://szkopul.edu.pl/problemset/problem/VYTSyRwgdwmLf56i_ffWGB0L/site/?key=statement", "9 OI - Koleje"),
        new Link("https://oi.edu.pl/static/attachment/20110811/oi9.pdf", "Omówienie Kolei s.45"),
        new Link("https://szkopul.edu.pl/problemset/problem/k-RYEjhwNTo_XdaCidXQUGMU/site/?key=statement", "22 OI - Kinoman"),
        new Link("https://www.oi.edu.pl/static/attachment/20160825/oi22.pdf", "Omowienie Kinomana s.65")
    ]),
    new Lesson().ext().setDate(9, 11, 2018).display(1)
        .setSubject("Zbiory")
        .setDesc("Zbiory i iteratory <set>")
        .setLinks([
        new Link("files/03-Set/zbiory.pdf", "Skrypt"),
        new Link("files/03-Set/zbiory_start.cpp", "Start"),
        new Link("files/03-Set/test.in", "test.in"),
        new Link("files/03-Set/zbiory_rozw.cpp", "Rozwiązanie")
    ]),
    new Lesson().ext().setCode("ZA").setDate(16, 11, 2018).display(1)
        .setIOI("AL2 (3)")
        .setLinks([
        new Link("https://www.spoj.com/problems/BUSYMAN/", "BUSYMAN (SPOJ)"),
        /*new Link("files/03-Zachlan/busyman.cpp", "busyman.cpp"),*/
        new Link("https://en.cppreference.com/w/cpp/container/map", "<map>")
    ])
        .setSubject("Algorytmy zachłanne")
        .setDesc("Algorytmy zachłanne. <map>"),
    new Lesson().ext().setCode("TG_7").setDate(23, 11, 2018).display(1)
        .setIOI("AL3b (8)")
        .setSubject("LCA").setDesc("Najniższy wspólny przodek")
        .setLinks([
        new Link("https://www.spoj.com/problems/LCASQ/", "LCASQ (SPOJ)")
    ]),
    new Lesson().ext().setCode("GE_1").setDate(30, 11, 2018).display(1)
        .setIOI('M (6-8), AL10 (1-3)')
        .setSubject("Geometria").setDesc("Liczby zespolone, rzutowania")
    /*.setLinks([
        new Link("https://en.cppreference.com/w/cpp/numeric/complex", "<complex>"),
        new Link("http://codeforces.com/blog/entry/22175", "Triki (CodeForces By Hikari9)"),
    ])*/ ,
    new Lesson().ext().setCode("GE_2").setDate(14, 12, 2018).display(1)
        .setIOI('M (6-8), AL10 (1-3)')
        .setSubject("Geometria 2").setDesc("Otoczka wypukła")
        .setLinks([
        new Link("https://www.spoj.com/problems/BSHEEP/", "BSHEEP (SPOJ)")
    ]),
    new Lesson().ext().setCode("TG_12").setDate(4, 01, 2019).display(1)
        .setIOI("AL2 (2)")
        .setSubject("Kombinatoryka").setDesc("Cykl Hamiltona")
        .setLinks([
        new Link("https://en.cppreference.com/w/cpp/utility/bitset", "<bitset>"),
        new Link("https://www.spoj.com/SHORTEN/problems/BINOMIAL/", "Binomial (SPOJ)"),
        new Link("https://code.google.com/codejam/contest/dashboard?c=32004#s=p2", "Cycles (Google Code Jam)"),
    ]),
    new Lesson().ext().setDate(11, 01, 2019).display(1)
        .setSubject("Teoria Gier").setDesc("Gra Nim")
        .setLinks([
        new Link("files/08-Nim/build/nim.pdf", "Uwagi do zadań!"),
        new Link("https://www.spoj.com/problems/REPEAT/", "REPEAT (SPOJ)"),
        new Link("https://szkopul.edu.pl/p/default/problemset/oi/17", "17 OI - Gra w minima"),
        new Link("https://szkopul.edu.pl/p/default/problemset/oi/11", "11 OI - Gra"),
        new Link("https://szkopul.edu.pl/p/default/problemset/oi/23", "Do poczytania: 23 OI - Wcale nie nim"),
    ]),
    new Lesson().ext().setDate(18, 01, 2019).display(1)
        .setSubject("Programowanie dynamiczne").setDesc("Dijkstra II")
        .setLinks([
        new Link("files/old/10-dijkstra/dijkstra.html", "Dijkstra 2017/2018"),
        new Link("files/09-Dijkstra/build/dijkstra.pdf", "Skrypt v.2"),
        new Link("https://www.spoj.com/problems/FCANDY/", "FCANDY (SPOJ)"),
    ]),
    new Lesson().ext().setDate(25, 01, 2019).display(1)
        .setSubject("Programowanie dynamiczne").setDesc("FCANDY c.d")
        .setLinks([
        new Link("files/09-Dijkstra/fcandy.cpp", "Rozwiązanie")
    ]),
    new Lesson().ext().setDate(15, 2, 2019).display(1)
        .setSubject("Programowanie dynamiczne").setDesc("Maski bitowe")
        .setLinks([
        new Link("https://www.spoj.com/problems/AIRLINES/", "AIRLINES (SPOJ)"),
        new Link("files/10-Airlines/matrix.hpp", "Mala biblioteka do mnozenia macierzy mod P"),
        new Link("files/10-Airlines/init.cc", "Start")
    ]),
    new Lesson().ext().setDate(1, 3, 2019).display(1)
        .setSubject("Programowanie dynamiczne").setDesc("Maski bitowe c.d."),
    new Lesson().ext().setDate(8, 3, 2019).display(1)
        .setSubject("Algorytmy tekstowe").setDesc("Aho-Corasick")
        .setLinks([
        new Link("https://www.spoj.com/problems/SUB_PROB/", "SUB_PROB (SPOJ)"),
        new Link("files/11-Corasick/test.zip", "Testy"),
        new Link("files/11-Corasick/start.zip", "Start"),
        new Link("files/11-Corasick/rozw.zip", "Rozwiazania")
    ]),
    new Lesson().ext().setCode("TG_11").setDate(15, 3, 2018).display(1)
        .setSubject("Grafy dwudzielne").setDesc("Maksymalne skojarzenia (Hopcroft-Karp)")
        .setLinks([
        new Link("https://www.spoj.com/problems/MATCHING/", "MATCHING (SPOJ)")
    ]),
    new Lesson().ext().setDate(22, 3, 2019).display(1)
        .setSubject("Sieci przepływowe").setDesc("Maksymalny przepływ (Dinic)"),
    new Lesson().ext().setDate(29, 3, 2019).display(1)
        .setSubject("Sieci przepływowe").setDesc("c.d.")
        .setLinks([
        new Link("https://szkopul.edu.pl/p/default/problemset/oi/12", "Kości (12 OI)")
    ]),
    new Lesson().ext().setDate(10, 5, 2019).display(1)
        .setSubject("Punkty artykulacji").setDesc("Funkcja Low")
        .setLinks([
        new Link("https://szkopul.edu.pl/p/default/problemset/oi/15", "Blokada (15 OI)")
    ]),
    new Lesson().ext().setDate(1, 3, 2018).display(0)
        .setSubject("Układy równań liniowych").setDesc("Eliminacja Gaussa"),
    new Lesson().ext().setCode("TG_10").setExpDate(3, 2018).display(0)
        .setIOI("AL3a (15) Dodać gdzieś Mosty i punkty artykulacji, cykl")
        .setSubject("Silnie spójne składowe").setDesc(),
    new Lesson().ext().setCode("TG_13").setExpDate(4, 2019).display(0)
        .setSubject("Programowanie genetyczne").setDesc(""),
    new Lesson().ext().setCode("TG_9").setExpDate(5, 2019).display(0)
        .setSubject("Heurystyki").setDesc("Kostka Rubika"),
    new Lesson().ext().setCode("TE_2").setExpDate(5, 2019).display(0)
        .setSubject("Template").setDesc("Wypisz mój typ, specjalizacja")
        .setLinks([
        new Link("https://www.boost.org/doc/libs/1_64_0/libs/mpl/doc/tutorial/tutorial-metafunctions.html#id41", "Do poczytania (dla chętnych)")
    ]),
];
var other_lessons = [
    new Lesson().intro().setCode("IO_2").setExpDate(10, 2018).setDate(18, 10, 2018)
        .setIOI('PF3 (3)')
        .setSubject("&ltiostream&gt").setDesc("Operacje wejścia/wyjścia w C++, "),
    new Lesson().intro().setCode("SD_1").setExpDate(10, 2018)
        .setIOI('PF3 (7)')
        .setSubject("struct").setDesc("Struktury, tablice struktur, typedef")
        .setLinks([new Link("https://en.cppreference.com/w/c/language/struct", "struct")]),
    new Lesson().intro().setCode("MAT_2").setExpDate(11, 2018).setIOI('M (2-4)')
        .setSubject("Modulo").setDesc("Wstęp do arytmetyki modulo"),
    new Lesson().intro().setCode("MAT_1").setExpDate(11, 2018)
        .setSubject("Rekurencja").setDesc("Liczby pierwsze, równania rekurencyjne, szeregi ciągi, zapis n-arny, NWD")
        .setLinks([
        new Link("http://pldml.icm.edu.pl/pldml/element/bwmeta1.element.dl-catalog-a064b502-798f-4529-935f-9b132b5667dd", "Teoria Liczb, Sierpiński Wacław (1950)"),
        new Link("https://pl.spoj.com/problems/PRZEDSZK/", "Przeszkolanka (SPOJ)"),
        new Link("https://stackoverflow.com/questions/30898575/inbuilt-gcda-b-function-in-c", "__gcd"),
        new Link("https://szkopul.edu.pl/problemset/problem/yZeuTNLgpfpx2vNXSGNRr2RE/site/?key=statement", "Liczby drugie (PA 2017)"),
    ]),
    new Lesson().intro().setCode("MAT_3").setExpDate(12, 2018)
        .setSubject("Macierze").setDesc(),
    new Lesson().intro().setCode("SD_2").setExpDate(12, 2018)
        .setIOI("PF3 (5,10) AL3b (1)")
        .setSubject("&ltstack&gt, &ltlist&gt").setDesc("Alokacja pamięci w C (malloc, free), wskaźnikowa implementacja listy jednokierunkowej na przykładzie stosu"),
    new Lesson().intro().setCode("SD_3").setExpDate(12, 2018)
        .setSubject("&ltqueue&gt").setDesc("Listowa implementacja kolejki, iteratory, operator++, operator*, operator[]"),
    new Lesson().intro().setCode("SD_4").setExpDate(12, 2018)
        .setSubject("&ltvector&gt").setDesc("Alokacja pamięci w C++ (new, delete), implementacja dynamicznej tablicy, klasy w C++"),
    new Lesson().intro().setCode("SO_1").setExpDate(1, 2019)
        .setSubject("&ltalgorithm&gt").setDesc("Porządek liniowy, przeciążanie operatora&lt, wyszukiwanie binarne na strukturach (lower_bound, upper_bound, find)"),
    new Lesson().intro().setCode("SO_2").setExpDate(2, 2019)
        .setIOI('DS1 (2), PF4 (1-4), AL3a (3, 7)')
        .setSubject("&ltalgorithm&gt").setDesc("Sortowanie kubełkowe, mergesort"),
    new Lesson().intro().setCode("SD_5").setExpDate(2, 2019)
        .setIOI("PF3 (6)")
        .setSubject("class BST").setDesc("Dynamiczne drzewo BST"),
    new Lesson().intro().setCode("DP_1").setExpDate(2, 2019)
        .setIOI("AL2 (6)")
        .setSubject("DP").setDesc("Programowanie dynamiczne"),
    new Lesson().intro().setCode("TG_1").setExpDate(3, 2019)
        .setIOI("PF3 (6), AL3a (9)")
        .setSubject("DFS").setDesc("Reprezentacja grafów. Rekurencyjne przechodzenie grafu"),
    new Lesson().intro().setCode("TG_2").setExpDate(3, 2019)
        .setIOI("AL8 (1)")
        .setSubject("Min-max").setDesc("Drzewa minimaxowe, obliczanie strategii wygrywającej na przykładzie gry kółko i krzyżyk"),
    new Lesson().intro().setCode("TG_3").setExpDate(3, 2019)
        .setIOI("AL3a (9)")
        .setSubject("BFS").setDesc("Przechodzenie grafu przy użyciu kolejki (SPOJ)"),
    new Lesson().intro().setCode("TG_4").setExpDate(4, 2019)
        .setSubject("Dijkstra").setDesc("Znajdowanie najkrótszych ścieżek w grafach ważonych. (przy użyciu kolejek priorytetowych), Floyd-Warshall"),
    new Lesson().intro().setCode("MAT_4").setExpDate(4, 2019)
        .setIOI('DS1 (2) AL3b (4)')
        .setSubject("Find Union").setDesc("Klasy abstrakcji, Struktura zbiorów rozłącznych"),
    new Lesson().intro().setCode("TX_1").setExpDate(4, 2019)
        .setSubject("KMP").setDesc(),
    new Lesson().intro().setCode("TG_5").setExpDate(5, 2019)
        .setIOI("AL3a (13)")
        .setSubject("MST").setDesc("Znajdowanie minimalnego drzewa rozpinającego przy użyciu algorytmu Kruskala i Prima (przy użyciu &ltset&gt)"),
    new Lesson().intro().setCode("TE_1").setExpDate(5, 2019)
        .setSubject("Szablon").setDesc("Template w C++, mnożenie macierzy (MxN) x (NxR)"),
    new Lesson().intro().setCode("MAT_5").setExpDate(5, 2019)
        .setSubject("Arytmetyka Modulo 2").setDesc("MTF, WTF, Twierdzenie Eulera"),
    new Lesson().intro().setCode("TX_2").setExpDate(6, 2019)
        .setSubject("Karp-Rabin").setDesc("Znajdowanie wystąpienia wzorca w tekście"),
    new Lesson().intro().setCode("SD_6").setExpDate(6, 2019)
        .setIOI("AL3b (5)")
        .setSubject("Drzewo potęgowe").setDesc("Implementacja statycznego drzewa potęgowego, reprezentacja ograniczonych zbiorów liczb naturalnych"),
    new Lesson().ext().setCode("IO_1").setExpDate(11, 2018)
        .setSubject("Testowanie")
        .setIOI('M (1), PF1(1-5), PF3 (1,2)')
        .setDesc("Operacje wejścia/wyjścia w C, pisanie testów automatycznych, obsługa plików"),
];
main();
