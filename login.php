<?php
// Libraries
require __DIR__ . '/vendor/autoload.php';

use Google\Cloud\Datastore\DatastoreClient;

session_start();
// TODO: Reference google entities examples.
// Check for login details
if (array_key_exists('user', $_POST) && array_key_exists('pass', $_POST)) {
    // Setup connection
    $projectId = "s3658474-task2";
    $datastore = new DatastoreClient(['projectId' => $projectId]);

    // Save to variables
    $inputUser = htmlspecialchars($_POST['user']);
    $inputPass = htmlspecialchars($_POST['pass']);

    // Get the key for the user
    $key = $datastore->key('user', $inputUser);
    $user = $datastore->lookup($key);
    $dataPass = $user['password'];
    // Check if user exists
    if (!is_null($user)) {
        if ($dataPass == $inputPass) {
            // Save to session to persist across pages
            $_SESSION['login'] = true;
            $_SESSION['user'] = $user;
            $_SESSION['userkey'] = $key;

            header("Location: main");
            $loginFailed = false;
        } else {
            $loginFailed = true;
        }
    } else {
        $loginFailed = true;
    }
}

?>

<html>
<!-- TODO: Reference w3schools for form -->
<body>
    <form action="/" method="post">
        <!-- Username -->
        <label for="user">Username</label>
        <input type="text" placeholder="Username" name="user">
        <!-- Password -->
        <label for="pass">Password</label>
        <input type="text" placeholder="xxxxxxxx" name="pass">
        <!-- Submit -->
        <button type="submit">Login</button>
    </form>
    <?php
    // TODO: Show failed error message here if ['login_failed'] exists in post
    if ($loginFailed) {
        echo '<p style="color: red;">Login Failed!</p>';
    }
    ?>
</body>

</html>