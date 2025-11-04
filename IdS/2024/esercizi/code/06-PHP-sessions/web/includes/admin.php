<?php
require_once "checkSession.php";
if ($_SESSION["user"]["role"] !== "admin") {
    header("Location: ./../pages/unime.php?page=user");
    exit();
}
require_once "Database.php";

if ($_SERVER['REQUEST_METHOD'] === 'POST') {

    $course_name = $_POST['course_name'];
    $course_description = $_POST['course_description'];
    $course_year = $_POST['course_year'];
    $course_image = $_POST['course_image'];

    try {
        $db = new Database();

        $sql = "INSERT INTO courses (course_name, course_description, course_year, course_image) VALUES (?, ?, ?, ?)";
        $params = [$course_name, $course_description, $course_year, $course_image];

        echo $db->query($sql, $params);

        $db->close();
    } catch (Exception $e) {
        echo "Errore: " . $e->getMessage();
    }
}
?>

<section class="container-fluid h-100">
    <h1 class="m-4">Aggiungi corso</h1>

    <form action="" method="POST" class="form-group">
        <label for="course_name">Nome del Corso:</label>
        <input type="text" id="course_name" name="course_name" class="form-control" required>

        <label for="course_description">Descrizione del Corso:</label>
        <textarea id="course_description" name="course_description" class="form-control" required></textarea>

        <label for="course_year">Anno del Corso:</label>
        <input type="text" id="course_year" name="course_year" class="form-control" required>

        <label for="course_image">Percorso Immagine del Corso (URL):</label>
        <input type="text" id="course_image" name="course_image" class="form-control" required placeholder="/assets/img/{nome_file}">

        <button type="submit" class="btn btn-primary mt-3">Aggiungi Corso</button>
    </form>
</section>