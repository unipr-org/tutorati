<?php
session_start();
require_once __DIR__ . "/./../includes/Database.php";


if ($_SERVER["REQUEST_METHOD"] === "POST") {
    $mail = $_POST["mail"];
    $password = $_POST["password"];
    $sql = "SELECT * FROM users WHERE mail = ?";

    $db = new Database();

    $result = $db->query($sql, [$mail]);

    // echo password_hash($password, PASSWORD_DEFAULT);

    if ($result && $result->num_rows > 0) {
        $user = $result->fetch_assoc();


        if (password_verify($password, $user["password"])) {

            unset($user["password"]);
            $_SESSION["user"] = $user;

            header("Location: unime.php");

            exit();
        } else {
            $error = "Password errata.";
        }
    } else {
        $error = "Utente non trovato.";
    }

    $db->close();
}
?>
<!DOCTYPE html>

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login</title>
    <link
        href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css"
        rel="stylesheet"
        integrity="sha384-QWTKZyjpPEjISv5WaRU9OFeRpok6YctnYmDr5pNlyT2bRjXh0JMhjY6hW+ALEwIH"
        crossorigin="anonymous" />
</head>

<body>
    <main class="container d-flex justify-content-center align-items-center vh-100">
        <article class="m-auto w-50 bg-light rounded p-5">

            <h2 class="m-0 mb-5">Login</h2>
            <form method="POST" action="">
                <div class="mb-3">
                    <label for="mail" class="form-label">Email address</label>
                    <input type="mail" class="form-control" id="mail" name="mail" required>
                </div>
                <div class="mb-3">
                    <label for="password" class="form-label">Password</label>
                    <input type="password" class="form-control" id="password" name="password" required>
                </div>
                <button type="submit" class="btn btn-primary">Login</button>
            </form>
            <?php if (!empty($error)): ?>
                <p style="color: red;"><?php echo htmlspecialchars($error); ?></p>
            <?php endif; ?>
        </article>
    </main>

    <?php include "./includes/footer.php"; ?>
</body>

<script
    src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"
    integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz"
    crossorigin="anonymous"></script>

</html>