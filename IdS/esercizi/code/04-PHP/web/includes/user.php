<link rel="stylesheet" href="/assets/css/user.css">
<section class="container">

    <h1 class="p-5">My courses</h1>

    <div class="container">
        <?php
        $path = __DIR__ . "./../assets/data/courses.csv";
        // foreach (file($path) as $line) {
        //     echo $line . "<br />\n";
        // }

        $content = '<section class="row row-cols-1 row-cols-md-3 g-4">';
        foreach (file($path) as $line) {
            $data = explode(",", trim($line));
            $content .= "
            <article class='col'>
                <a class='card text-bg-dark overflow-hidden' target='_blank' href='/pages/course.php?id={$data[0]}'>
                    <img src='{$data[1]}' class='card-img' alt='Course image'>
                    <div class='card-img-overlay p-0'>
                        <div class='my-overlay container-fluid p-3 d-flex flex-column align-items-center'>
                            <h3 class='card-title'>{$data[2]}</h3>
                            <p class='card-text'>{$data[3]}</p>
                            <p class='card-text'><small>{$data[4]}</small></p>
                        </div>
                    </div>
                </a>
            </article>
            ";
        }
        $content .= '</section>';
        echo $content;
        ?>
    </div>

</section>