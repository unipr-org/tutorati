<?php
session_start();
if (!isset($_SESSION["user"])) {
    header("Location: ./../pages/login.php");
    exit();
}
?>
<nav class="navbar navbar-expand-lg bg-body-tertiary">
    <section class="container-fluid">
        <a class="navbar-brand" href="#">UniMe</a>
        <button
            class="navbar-toggler"
            type="button"
            data-bs-toggle="collapse"
            data-bs-target="#navbarNavAltMarkup"
            aria-controls="navbarNavAltMarkup"
            aria-expanded="false"
            aria-label="Toggle navigation">
            <span class="navbar-toggler-icon"></span>
        </button>
        <aside
            class="collapse navbar-collapse justify-content-end"
            id="navbarNavAltMarkup">
            <div class="navbar-nav">
                <a class="nav-link" href="?page=user">User</a>
                <?php if ($_SESSION["user"]["role"] === "admin"): ?>
                    <a class="nav-link" href="?page=admin">Admin</a>
                <?php endif; ?>
                <a class="nav-link text-danger" href="./../includes/logout.php">Logout</a>
            </div>
        </aside>
    </section>
</nav>