<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="author" content="Simone Colli">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>UniMe</title>
    <link
        href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css"
        rel="stylesheet"
        integrity="sha384-QWTKZyjpPEjISv5WaRU9OFeRpok6YctnYmDr5pNlyT2bRjXh0JMhjY6hW+ALEwIH"
        crossorigin="anonymous" />
    <link rel="icon" href="/assets/icon/um.png" type="image/icon type">
    <link rel="stylesheet" href="/assets/css/common.css">
    <link rel="stylesheet" href="/assets/css/style.css">

</head>

<body>
    <?php include "./includes/nav.php"; ?>

    <main class="container-fluid">

        <?php
        $page = $_GET["page"] ?? "user";

        if ($page === "admin") {
            include "./includes/admin.php";
        } else {
            include "./includes/user.php";
        }

        ?>
    </main>

    <?php include "./includes/footer.php"; ?>

    <script
        src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"
        integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz"
        crossorigin="anonymous"></script>
</body>

</html>