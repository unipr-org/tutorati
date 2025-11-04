<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>PHP intro</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 800px;
            margin: 0 auto;
            padding: 20px;
            line-height: 1.6;
            background-color: #f5f5f5;
        }

        .output {
            background-color: white;
            padding: 15px;
            margin: 10px 0;
            border-radius: 5px;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
        }

        code {
            display: block;
            background-color: #f8f8f8;
            padding: 10px;
            border-radius: 5px;
            border: 1px solid #ddd;
            font-family: monospace;
            white-space: pre;
            margin: 10px 0;
        }
    </style>
</head>

<body>
    <?php

    echo '<code>

    // Commento su una riga
    # Anche questo è un commento su una riga

    /*
    Commento su
    più righe
    */
    echo </code>';


    echo "<div class='output'>PHP Version: " . phpversion() . "</div>";

    // Variabili
    $nome = "Maria"; // stringa
    $eta = 25;       // intero
    $altezza = 1.75; // float

    echo '<code>
    $nome = "Maria"; // stringa
    $eta = 25;       // intero
    $altezza = 1.75; // float
    </code>';

    echo "<div class='output'>Nome: $nome, Età: $eta, Altezza: $altezza </div>";

    // i tipi di dato a disposizione sono:
    // stringhe, numeri interi, numeri decimali, booleani, array, oggetti



    // Costrutti condizionali

    echo '<code>
    $età = 20;
     if ($età >= 18) {
        echo "Sei maggiorenne.";
    } elseif ($età >= 13) { // !!!! non else if
        echo "Sei adolescente.";
    } else {
        echo "Sei un bambino.";
    }
    </code>';

    $età = 20;

    echo "<div class='output'>";
    if ($età >= 18) {
        echo "Sei maggiorenne.";
    } elseif ($età >= 13) { // !!!! non else if
        echo "Sei adolescente.";
    } else {
        echo "Sei un bambino.";
    }
    echo "</div>";
    echo '<code>
    $colore = "rosso";
    switch ($colore) {
        case "rosso":
            echo "Il colore è rosso.";
            break;
        case "blu":
            echo "Il colore è blu.";
            break;
        default:
            echo "Colore non riconosciuto.";
            break;
    }
    </code>';

    $colore = "rosso";
    echo "<div class='output'>";
    switch ($colore) {
        case "rosso":
            echo "Il colore è rosso.";
            break;
        case "blu":
            echo "Il colore è blu.";
            break;
        default:
            echo "Colore non riconosciuto.";
            break;
    }
    echo "</div>";

    // Ciclo While
    echo '<code>
    $i = 1;
    while ($i <= 5) {
        echo $i . " ";
        ++$i;
    }
    </code>';

    echo "<div class='output'>";
    $i = 1;
    while ($i <= 5) {
        echo $i . " ";
        ++$i;
    }
    echo "</div>";

    // Ciclo Do-While
    echo '<code>
    $i = 1;
    do {
        echo $i . " ";
        ++$i;
    } while ($i <= 5);
    </code>';

    echo "<div class='output'>";
    $i = 1;
    do {
        echo $i . " ";
        ++$i;
    } while ($i <= 5);
    echo "</div>";

    // Ciclo For
    echo '<code>
    for ($i = 1; $i <= 5; $i++) {
        echo $i . " ";
    }
    </code>';

    echo "<div class='output'>";
    for ($i = 1; $i <= 5; $i++) {
        echo $i . " ";
    }
    echo "</div>";

    // Ciclo Foreach
    $frutti = ["Mela", "Banana", "Arancia"];

    echo '<code>
    $frutti = ["Mela", "Banana", "Arancia"];
    foreach ($frutti as $frutto) {
        echo $frutto . " ";
    }
    </code>';

    echo "<div class='output'>";
    foreach ($frutti as $frutto) {
        echo $frutto . " ";
    }
    echo "</div>";

    // Array associativo
    echo '<code>
    $persona = [
        "nome" => "Maria",
        "età" => 25,
        "città" => "Roma"
    ];
    echo $persona["nome"];
    </code>';

    // array associativo (mappe chiave-valore)
    $persona = [
        "nome" => "Maria",
        "età" => 25,
        "città" => "Roma"
    ];
    echo "<div class='output'>" . $persona["nome"] . "</div>";



    // Funzione con parametri e valore di ritorno
    echo '<code>
    function saluta($nome = "Utente") {
        return "Ciao, " . $nome . "!";
    }
    echo saluta();
    echo saluta("Marco");
    </code>';

    function saluta($nome = "Utente")
    {
        return "Ciao, " . $nome . "!";
    }

    echo "<div class='output'>" . saluta() . "</div>";
    echo "<div class='output'>" . saluta("Marco") . "</div>";

    // Funzione tipizzata
    echo '<code>
    function somma(int $a, int $b): int {
        return $a + $b;
    }
    echo somma(3, 5);
    </code>';

    function somma(int $a, int $b): int
    {
        return $a + $b;
    }

    echo "<div class='output'>" . somma(3, 5) . "</div>";
    ?>

</body>

</html>