<?php

// Paragraph print
function pprint($name)
{
    echo "<p> $name </p>";
}

// Debug print
function dprint($name, $flag)
{
    if ($flag) {
        print($name);
    }

}

function redirecting_button($name, $url)
{
    echo "<form method='get' action='$url'><button type='submit'>$name </button></form>";
}

function id_button($name, $value, $url)
{
    echo "<form method='post' action='$url'><button type='submit' name='$name' value='$value'> Usuń. </button>";
}

function form()
{
    pprint("Dane klienta:");
    echo "<form method='post'>";
    foreach (new Client() as $key => $value) {
        echo "$key : <input type='txt' name='$key'></br>";
    }
    echo "<input type='submit'></form>";
}

function client_choose_form($db)
{
    $db->print_all_tables();
}

function option_default($name, $val, $comment)
{
    echo " <option value='$val' ";
    if ($_SESSION[$name] == $val) {
        echo "selected='selected'";
    }
    echo ">  $comment </option>";

}

function order_add_form($db)
{
    pprint("Czy klient ma konto?");
    echo "
        <form method='post'>
        <select name='OAF'>";
    option_default("OAF", "Tak", "Ma. Chcę znaleźć go w bazie.");
    option_default("OAF", "Nie", "Nie ma, ale chce założyć.");
    echo "
        </select>
        <input type='submit' value='Potwierdzam.'>
        </form>";

    switch ($_SESSION['OAF']) {
        case 'Nie':
        case 'Tak':
            form();
            break;
        case 'Filtered':
            $client = unserialize($_SESSION['Client']);
            $db->get_id($client);
            break;
        default:
            break;
    }
}
