<?php
class DataBase extends SQLite3
{
    public function __construct($db_name)
    {
        parent::__construct('pizzeria.sqlite3');
        return $this;
    }

    public function print_result($ret)
    {
        $col_num = $ret->numColumns();
        echo "<table border='1'>";
        echo "<tr>";
        for ($i = 0; $i < $col_num; $i++) {
            $h = $ret->columnName($i);
            echo "<th> $h </th>";
        }
        echo "</tr>";
        while ($row = $ret->fetchArray(SQLITE3_ASSOC)) {
            echo "<tr>";
            foreach ($row as $key => $value) {
                if ($key == 'id_klienta') {
                    echo "<td>";
                    id_button("ID_KLIENTA", $value, "action.php");
                    echo "</td>";
                } else {
                    echo "<td> $value </td>";
                }
            }
            print "</tr>";
        }
        echo "</table>";
    }

    public function print_table($table_name, $title = '', $what = '*', $where = '')
    {
        if ($title != "") {
            echo "<h3> $title </h3>";
        }

        $w = ($where = "" ? "" : "WHERE $where");
        $stmt;
        if ($where != "") {
            $stmt = $this->prepare("SELECT $what FROM $table_name;");
        } else {
            $stmt = $this->prepare("SELECT $what FROM $table_name WHERE $where;");
        }

        $result = $stmt->execute();
        $this->print_result($result);
    }

    public function query_table_names()
    {
        $res = $this->query("SELECT name FROM sqlite_master where type='table';");
        $arr = array();
        while ($table_name = $res->fetchArray(SQLITE3_ASSOC)) {
            array_push($arr, $table_name['name']);
        }
        global $DEBUG;
        if ($DEBUG) {
            var_dump($arr);
        }
        return $arr;
    }

    public function print_all_tables()
    {
        echo '<div id="tables">';
        echo "<h1> Tabele </h1>";
        echo '<div class="grid-container">';
        $names = $this->query_table_names();
        foreach ($names as $name) {
            $this->print_table($name, $name);
        }
        echo "</div> </div>";
    }

    public function get_id($client, $table_name = 'Klient')
    {
        $first = false;
        //$arr = array('imie' => ':im', 'nazwisko' => ':na', 'email' => ':em', 'ulica' => ':ul', 'miasto' => ':mi', 'telefon' => ':te');
        //$col_name = "imie, nazwisko, email, ulica, miasto, telefon";
        $col_name = "*";
        $sql = "SELECT $col_name FROM $table_name";
        foreach ($client as $key => $val) {
            if ($val != "") {
                //echo $val . "</br>";
                //$k = $arr[$key];
                //$k2 = $k . '2';
                if ($first == false) {
                    $sql .= ' WHERE ' . $key . ' = "' . $val . '"';
                    $first = true;
                } else {
                    $sql .= ' AND ' . $key . '=\'' . $val . '\'';
                }
            }
        }

        $sql .= ";";
        dprint($sql, $_SESSION['DEBUG']);

        $stmt = $this->prepare($sql);

        // Do zabezpieczenia przed SQL INJECTION
        // foreach ($client as $key => &$value) {
        //     if ($value != "") {
        //         $kk = $key;
        //         $va = $value;
        //         $k = $arr[$key];
        //         $k2 = $k . '2';
        //         $stmt->bindParam($k, $kk);
        //         $stmt->bindValue($k2, $va);
        //         $str = $key . '="' . $value . '"';
        //         pprint($str);
        //     }
        // }

        //$stmt = $this->prepare("SELECT * FROM Klient WHERE imie='Bart*';");
        $result = $stmt->execute();
        $this->print_result($result);
    }

    public function remove_id()
    {
        $num = $_SESSION['ID_KLIENTA'];
        $sql = "DELETE FROM Klient WHERE id_klienta =" . $num . ";";
        if ($num != '') {
            $stmt = $this->prepare($sql);
            if ($stmt->execute()) {
                pprint("Usunięto.");
                $_SESSION['ID_KLIENTA'] = '';
            }
        }
    }

};
