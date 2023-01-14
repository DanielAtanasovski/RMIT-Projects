<?php
// Libraries
require __DIR__ . '/vendor/autoload.php';

use Google\Cloud\Datastore\DatastoreClient;

session_start();

$Invalidpass = false;

// Make sure we get post values and we're logged in
if (array_key_exists('oldpass', $_POST) && array_key_exists('newpass', $_POST) && !is_null($_SESSION['login'])) {
    // empty post values
    if (empty($_POST['oldpass']) || empty($_POST['newpass'])) {
        $Invalidpass = true;
    } else {
        // Confirm Password
        if ($_SESSION['user']['password'] != $_POST['oldpass']) {
            $Invalidpass = true;
        } else {
            // Connect
            $projectId = "s3658474-task2";
            $datastore = new DatastoreClient(['projectId' => $projectId]);

            // Setup a transaction and get the user from datastore
            $transaction = $datastore->transaction();
            $user = $transaction->lookup($_SESSION['userkey']);
            $user['password'] = $_POST['newpass'];
            // Update
            $transaction->update($user);
            $transaction->commit();

            // Update Session Copy of user
            $_SESSION['user'] = $user;

            // Redirect
            header("Location: /");
        }
    }
}

?>

<html>

<body>
    <?php if (is_null($_SESSION['login'])) : ?>
        <form action="/" method="post">
            <p>You must be logged in first!</p>
            <button type="submit">Go to Login</button>
        </form>
    <?php else : ?>

        <!-- Change Name -->
        <form action="/password" method="post">
            <label for="oldpass">Old Password</label>
            <input type="text" name="oldpass">

            <label for="newpass">New Password</label>
            <input type="text" name="newpass">

            <button type="submit">Confirm</button>
        </form>
    <?php endif; ?>
</body>

</html>