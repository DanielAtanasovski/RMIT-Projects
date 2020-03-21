<?php
// Libraries
require __DIR__ . '/vendor/autoload.php';

use Google\Cloud\Datastore\DatastoreClient;

session_start();

$InvalidName = false;
// Check if we got data and logged in (as we depend on some session variables)
if (array_key_exists('changefield', $_POST) && !is_null($_SESSION['login'])) {
    if (empty($_POST['changefield'])) {
        $InvalidName = true;
    } else {
        $InvalidName = false;
        // Connect
        $projectId = "s3658474-task2";
        $datastore = new DatastoreClient(['projectId' => $projectId]);

        // Setup a transaction and get the user from datastore
        $transaction = $datastore->transaction();
        $user = $transaction->lookup($_SESSION['userkey']);
        $user['name'] = $_POST['changefield'];
        
        // Update
        $transaction->update($user);
        $transaction->commit();

        // Update Session Copy of user
        $_SESSION['user'] = $user;

        // Redirect
        header("Location: main");
    }
}

?>
<html>

<body>
    <!-- Check if logged in -->
    <?php if (is_null($_SESSION['login'])) : ?>
        <form action="/name" method="post">
            <p>You must be logged in first!</p>
            <button type="submit">Go to Login</button>
        </form>
    <?php else : ?>
        <?php
        $name = $_SESSION['user']['name'];
        ?>
        <!-- Display Name -->
        <p>Changing Name</p>
        <!-- Change Name -->
        <form action="/name" method="post">
            <label for="changefield">New Name</label>
            <input type="text" name="changefield">
            <button type="submit">Confirm</button>
        </form>
        <?php
        if ($InvalidName) {
            echo '<p style="color: red;">Name cannot be empty!</p>';
        }
        ?>
    <?php endif; ?>

</body>

</html>