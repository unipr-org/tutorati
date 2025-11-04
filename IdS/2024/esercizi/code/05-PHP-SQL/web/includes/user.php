<link rel="stylesheet" href="/assets/css/user.css">
<section class="container">

    <h1 class="p-5">My courses</h1>

    <div class="container">
        <?php

        // $path = __DIR__ . ;
        require_once "Database.php";
        $db = new Database();
        $sql = "SELECT id, course_image, course_name, course_description, course_year FROM courses";
        $result = $db->query($sql);

        $content = '<section class="row row-cols-1 row-cols-md-3 g-4">';
        if ($result->num_rows > 0) {
            while ($row = $result->fetch_assoc()) {
                $content .= "
                <article class='col'>
                    <a class='card text-bg-dark overflow-hidden' target='_blank' href='/pages/course.php?id={$row['id']}'>
                        <img src='{$row['course_image']}' class='card-img' alt='Course image'>
                        <div class='card-img-overlay p-0'>
                            <div class='my-overlay container-fluid p-3 d-flex flex-column align-items-center'>
                                <h3 class='card-title'>{$row['course_name']}</h3>
                                <p class='card-text'>{$row['course_description']}</p>
                                <p class='card-text'><small>{$row['course_year']}</small></p>
                            </div>
                        </div>
                    </a>
                </article>
                ";
            }
        }
        $content .= '</section>';
        echo $content;
        ?>
    </div>

</section>