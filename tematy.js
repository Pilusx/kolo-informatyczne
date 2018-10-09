var DISPLAY_OFF = true;
var Link = (function () {
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
})();
var Lesson = (function () {
    function Lesson() {
    }
    Lesson.prototype.ext = function () {
        this.class_num = "e";
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
        if (this.date == null) {
            var date_1 = this.expected_date;
            return (date_1.getMonth() + 1) + "/" + date_1.getFullYear() + "?";
        }
        var date = this.date;
        return (date.getDate()) + "/" + (date.getMonth() + 1) + " " + date.getFullYear();
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
        for (var _i = 0; _i < fields.length; _i++) {
            var field = fields[_i];
            var col = document.createElement("td");
            row.appendChild(col);
            col.classList.add("row_" + field);
            var value = this[field];
            if (field == 'date') {
                var date = this.getDate();
                col.innerHTML = date;
                if (date.indexOf("?") != -1) {
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
})();
function add_lessons() {
    var lesson_section_int = document.getElementById("lessons_introductory");
    var lesson_section_ext = document.getElementById("lessons_extension");
    var table_int = document.createElement("table");
    var table_ext = document.createElement("table");
    var fields = ["subject", "date", "description", "links"];
    var names = ["Temat", "Data", "Opis", "Linki"];
    lesson_section_int.appendChild(table_int);
    lesson_section_ext.appendChild(table_ext);
    table_int.id = "introductory";
    table_ext.id = "extension";
    table_int.appendChild(Lesson.get_HTML_head(fields, names));
    table_ext.appendChild(Lesson.get_HTML_head(fields, names));
    for (var _i = 0; _i < lessons.length; _i++) {
        var lesson = lessons[_i];
        //console.log(lesson_str);
        if (!DISPLAY_OFF || lesson.date !== undefined) {
            var container = lesson.get_HTML_row(fields);
            if (lesson.class_num == "i") {
                table_int.appendChild(container);
            }
            else {
                table_ext.appendChild(container);
            }
        }
    }
}
var Book = (function () {
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
})();
function iter_add_elements_to_parent(parent, array) {
    for (var _i = 0; _i < array.length; _i++) {
        var elem = array[_i];
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
    new Link("http://smurf.mimuw.edu.pl/", "Smurf"),
    new Link("http://was.zaa.mimuw.edu.pl/", "WAS"),
    new Link("old", "Materiały z 2017/2018"),
];
var books = [
    new Book("Kółko Matematyczne dla Olimpijczyków", "Pawłowski, Henryk", undefined, "https://www.matematyka.pl/3263.htm"),
    new Book("Wprowadzenie do algorytmów", " Cormen Thomas H., Leiserson Charles E., Rivest Ronald L, Clifford Stein "),
    new Book("Inne", undefined, undefined, "https://oi.edu.pl/l/oi_zalecana_literatura/")
];
var lessons = [
    new Lesson().intro().setCode("IO_1").setExpDate(10, 2018)
        .setDate(11, 10, 2018)
        .setSubject("&ltcstdio&gt")
        .setIOI('M (1), PF1(1-5), PF3 (1,2)')
        .setDesc("Operacje wejścia/wyjścia w C (printf->stdout, scanf->stdin), funkcje built-in")
        .setLinks([new Link("http://www.cplusplus.com/reference/cstdio/", "<cstdio>(CPP)"),
        new Link("https://en.cppreference.com/w/cpp/header/cstdio", "<cstdio>(CPPR)"),
        new Link("https://en.cppreference.com/w/cpp/io/c/fscanf", "scanf"),
        new Link("https://en.cppreference.com/w/cpp/io/c/fprintf", "printf"),
        new Link("https://en.cppreference.com/w/cpp/io/c/fopen", "fopen"),
        new Link("https://en.cppreference.com/w/cpp/io/c/fclose", "fclose"),
        new Link("https://en.cppreference.com/w/cpp/string/byte/islower", "islower"),
        new Link("files/00-IO_C/init", "Start"),
        new Link("files/00-IO_C/final", "Koniec")
    ]),
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
    new Lesson().ext().setCode("TG_7").setExpDate(10, 2018)
        .setIOI("AL3b (8)")
        .setSubject("LCA").setDesc("Najniższy wspólny przodek"),
    new Lesson().ext().setCode("TG_8").setExpDate(10, 2018)
        .setSubject("Dynamiki na drzewach").setDesc("Programowanie dynamiczne na drzewach"),
    new Lesson().ext().setCode("ZA").setExpDate(10, 2018)
        .setIOI("AL2 (3)")
        .setSubject("Algorytmy zachłanne").setDesc(),
    new Lesson().ext().setCode("GE_1").setExpDate(11, 2018)
        .setIOI('M (6-8), AL10 (1-3)')
        .setSubject("Geometria 1").setDesc("Liczby zespolone")
        .setLinks([
        new Link("https://en.cppreference.com/w/cpp/numeric/complex", "<complex>"),
        new Link("http://codeforces.com/blog/entry/22175", "Triki (CodeForces By Hikari9)"),
    ]),
    new Lesson().ext().setCode("GE_2").setExpDate(11, 2018)
        .setIOI("AL10 (4-6)")
        .setSubject("Geometria 2").setDesc(),
    new Lesson().ext().setCode("GE_3").setExpDate(11, 2018)
        .setIOI("AL10 (7)")
        .setSubject("Geometria 3").setDesc("Otoczka wypukła"),
    new Lesson().ext().setCode("SD_7").setExpDate(12, 2018)
        .setIOI("AL3b (6)")
        .setSubject("AVL").setDesc("Drzewo AVL Dynamiczne drzewo AVL + proste zadanie na <set>, rotacje"),
    new Lesson().ext().setCode("TE_2").setExpDate(12, 2018)
        .setSubject("Specjalizacja").setDesc("Wypisz mój typ.")
        .setLinks([
        new Link("https://www.boost.org/doc/libs/1_64_0/libs/mpl/doc/tutorial/tutorial-metafunctions.html#id41", "Dimensional analysis (***)")
    ]),
    new Lesson().ext().setCode("SD_8").setExpDate(12, 2018)
        .setIOI("AL3b (5)")
        .setSubject("Drzewo przedziałowe").setDesc(),
    new Lesson().ext().setCode("TG_9").setExpDate(1, 2019)
        .setSubject("Heurystyki").setDesc("Kostka rubika"),
    new Lesson().ext().setCode("TG_10").setExpDate(1, 2019)
        .setIOI("AL3a (15) Dodać gdzieś Mosty i punkty artykulacji, cykl eulera")
        .setSubject("Silne spójne składowe").setDesc(),
    new Lesson().ext().setCode("TG_11").setExpDate(2, 2019)
        .setSubject("Grafy dwudzielne").setDesc("Skojarzenia w grafach dwudzielnych"),
    new Lesson().ext().setCode("TG_12").setExpDate(2, 2019)
        .setIOI("AL2 (2)")
        .setSubject("Hamilton 1").setDesc("Cykl Hamiltona O(n*n!)")
        .setLinks([
        new Link("http://www.cplusplus.com/reference/algorithm/next_permutation/", "next_permutation")
    ]),
    new Lesson().ext().setCode("DP_2").setExpDate(2, 2019)
        .setIOI("AL2 (1,4,6)")
        .setSubject("Hamilton 2").setDesc("Cykl Hamiltona O(n^3 * 2^n) <bitset>, DP"),
    new Lesson().ext().setCode("TG_13").setExpDate(3, 2019)
        .setSubject("Genetyki").setDesc("Problem n-hetmanów"),
    new Lesson().ext().setCode("SD_9").setExpDate(3, 2019)
        .setSubject("Kopce").setDesc("Kopiec, Kopiec Fibonacciego, Kopiec Dwumianowy"),
];
main();
