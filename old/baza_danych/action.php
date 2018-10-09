<html>
 <head>
  <title>PHP Test</title>
  <meta charset="UTF-8"/>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <link rel="stylesheet" href="style.css">

 </head>
 <body>
 <?php
include 'dbfunctions.php';
include 'dbmodification.php';
include 'client.php';
include 'database.php';

ini_set('session.save_path',realpath(dirname($_SERVER['DOCUMENT_ROOT']) . '/../session'));
session_start();

function session_update($data, $name, $default = "")
{
    if (!isset($_SESSION[$name])) {
        $_SESSION[$name] = $default;
    }
    if (isset($_POST[$name])) {
        $_SESSION[$name] = $_POST[$name];
        
        if($name = 'ID_KLIENTA')
            $data->remove_id();
    }
}

function client_update($db)
{
    $client_name = 'Client';
    session_update($client_name, serialize(new Client()));

    if (isset($_POST['imie'])) {

        $client = new Client();

        foreach ($client as $key => &$value) {
            //echo "$key :  $_POST[$key] </br>";
            $value = $_POST[$key];
            unset($value);
        }
        if ($_SESSION['OAF'] == 'Nie') {
            $client->insert_to_db($db);
        }

        $_SESSION['OAF'] = 'Filtered';

        $_SESSION[$client_name] = serialize($client);
        var_dump($client);
        $_POST['ID_KLIENTA'] = $db->get_id($client);
    }
}
session_update('DEBUG', 'False');

if ($_SESSION['DEBUG'] != 'False') {
    error_reporting(E_ALL);
    ini_set('display_errors', 1);
    pprint("<b>SESSION</b>");
    foreach ($_SESSION as $key => $value) {
        $val = @unserialize($value);
        pprint("$key : " . ($val ? $val : $value));
    }
    pprint("<b>POST</b>");
    foreach ($_POST as $key => $value) {
        pprint("$key : $value");
    }
}

redirecting_button("Powrót do strony głównej.", "index.html");

$db = new DataBase('pizzeria.sqlite3');
if (!$db) {
    pprint('Failed connecting to db');
    $ACTION = "DB_CONN_ERR";
}

session_update($db, 'OAF');
session_update($db, 'Action');
session_update($db, 'ID_KLIENTA');
client_update($db);

if (!empty($_POST)) {
    header("Refresh:0");
}

switch ($_SESSION['Action']) {
    case "Sho":
        $db->print_all_tables();
        break;
    case "OAF":
        order_add_form($db);
        break;
    case "Fin":
        //delete_form();
        break;
    case "OSh":
        break;
    case "Done":
        pprint("Coś nabroiłem z bazą danych. Gratulacje ;)");
        break;
    default:
        pprint("Przykro mi, ale coś się zepsuło.");
}

?>

 </body>
</html>
