<?php
// Libraries
require __DIR__ . '/vendor/autoload.php';

use Google\Cloud\Datastore\DatastoreClient;

session_start();
?>

<html>
<body>
    <?php if (is_null($_SESSION['login'])) : ?>
        <form action="/" method="post">
            <p>You must be logged in first!</p>
            <button type="submit">Go to Login</button>
        </form>
    <?php else : ?>
        <?php
        $name = $_SESSION['user']['name'];
        ?>
        <!-- Display Name -->
        <?php
        echo 'Hello, ' . $name . "!";
        ?>
        <!-- Change Name -->
        <form action="/name" method="post">
            <button type="submit">Change Name</button>
        </form>
        <!-- Change Password -->
        <form action="/password" method="post">
            <button type="submit">Change Password</button>
        </form>
    <?php endif; ?>
</body>

</html>