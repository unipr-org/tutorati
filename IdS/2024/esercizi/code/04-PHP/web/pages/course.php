<?php
if (isset($_GET['id'])) {
    $courseId = $_GET['id'];
    $path = __DIR__ . "./../assets/data/courses.csv";

    foreach (file($path) as $line) {
        $data = explode(",", trim($line));
        if ($data[0] == $courseId) {
            $title = $data[2];
            $description = $data[3];
            break;
        }
    }
}
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="author" content="Simone Colli">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Dettagli corso</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css" rel="stylesheet">
    <link rel="stylesheet" href="/assets/css/common.css">
    <link rel="stylesheet" href="/assets/css/course-page.css">

</head>

<body>
    <main class="container bg-light p-5">
        <h1 class="mb-4"><?php echo $title ?? 'Course Not Found'; ?></h1>

        <small>Descrizione del corso:</small>
        <p class="lead"><?php echo $description ?? 'No description available'; ?></p>
    </main>
    <?php include __DIR__ . "./../includes/footer.php"; ?>
</body>

</html>