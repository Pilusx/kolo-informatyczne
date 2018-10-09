<?php
class Client
{
    public $imie = "", $nazwisko = "", $email = "", $ulica = "", $miasto = "", $telefon = "";
    public function __toString()
    {
        return "($this->imie, $this->nazwisko, $this->email, $this->ulica, $this->miasto, $this->telefon)";
    }

    public function insert_to_db($db, $table_name = 'Klient')
    {
        $col_name = "(imie, nazwisko, email, ulica, miasto, telefon)";
        $stmt = $db->prepare("INSERT INTO $table_name $col_name VALUES (:im, :na, :em, :ul, :mi, :te);");
        $arr = array('imie' => ':im', 'nazwisko' => ':na', 'email' => ':em', 'ulica' => ':ul', 'miasto' => ':mi', 'telefon' => ':te');
        foreach ($this as $key => &$value) {
            $stmt->bindParam($arr[$key], $value);
        }

        $stmt->execute();
    }
};
