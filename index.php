<?php
require __DIR__ . '/vendor/autoload.php';

use Google\Cloud\Datastore\DatastoreClient;

session_start();
if (isset($_POST['add_stopID']) && !is_null($_POST['add_stopID'])) {
    setcookie('FavouriteStopID', $_POST['add_stopID'], time() + (86400 * 30), "/"); // 86400 = 1 day);
    $_COOKIE['FavouriteStopID'] = $_POST['add_stopID'];
    setcookie('FavouriteStopRoute', $_POST['add_stopRoute'], time() + (86400 * 30), "/"); // 86400 = 1 day);
    $_COOKIE['FavouriteStopRoute'] = $_POST['add_stopRoute'];
    //echo $_COOKIE['FavouriteStopID'];
    //$_SESSION['favourite_stopID'] = $_POST['add_stopID'];
    // $_SESSION['favourite_stopType'] = $_POST['add_stopRoute'];
}

# Your Google Cloud Platform project ID
$projectId = 'cc-ptv-planner';

# Instantiates a client
$datastore = new DatastoreClient([
    'projectId' => $projectId
]);

$devid = "3001608";
$apikey = "751a9dd5-9e2e-4f2a-b87d-009a45729806";
$searchurl = "http://timetableapi.ptv.vic.gov.au";

$currentTime = new \DateTime("now", new \DateTimeZone("UTC"));
$favourite = null;
// Map
$showMap = false;
$mapLat = 0;
$mapLon = 0;
$mapName = "No Results";

// On Search Post
if (isset($_POST['search'])) {
    $result = SearchAndFilter();

    if (count($result['stops']) != 0) {
        $showMap = true;
    }
}

// Functions

// Search
function SearchAndFilter()
{
    global $devid;
    global $apikey;
    global $searchurl;

    $req = "/v3/search/" . myUrlEncode($_POST["search"]) . "?"
        . "route_types=" . htmlspecialchars($_POST["search-filter"])
        . "&devid=" . $devid;

    $signature = hash_hmac("sha1", $req, $apikey);

    $response = file_get_contents($searchurl . $req . "&signature=" . $signature);
    $return = json_decode($response, true);
    return $return;
}

function GetStop($id, $type)
{
    global $devid;
    global $apikey;
    global $searchurl;

    $req = "/v3/stops/" . $id . "/route_type/" . $type
        . "?stop_location=true&devid=" . $devid;

    $signature = hash_hmac("sha1", $req, $apikey);

    $response = file_get_contents($searchurl . $req . "&signature=" . $signature);
    $return = json_decode($response, true);
    return $return;
}

function myUrlEncode($string)
{
    $entities = "+";
    $replacements = "%20";
    return str_replace($entities, $replacements, urlencode($string));
}

// Departures
function Departures($route_type, $stop_id)
{
    global $devid;
    global $apikey;
    global $searchurl;

    // /v3/departures/route_type/{route_type}/stop/{stop_id} 
    $req = "/v3/departures/route_type/" . $route_type . "/stop/" . $stop_id . "?devid=" . $devid;

    $signature = hash_hmac("sha1", $req, $apikey);
    $response = file_get_contents($searchurl . $req . "&signature=" . $signature);
    $return = json_decode($response, true);
    return $return;
}

// Runs
function Runs($runid)
{
    global $devid;
    global $apikey;
    global $searchurl;

    // v3/runs/run_id
    $req = "/v3/runs/" . $runid . "?devid=" . $devid;

    $signature = hash_hmac("sha1", $req, $apikey);
    $response = file_get_contents($searchurl . $req . "&signature=" . $signature);
    $return = json_decode($response, true);
    return $return;
}

function OrganiseData()
{
    global $result;
    global $currentTime;

    // Organise the data 
    $data = array();
    foreach ($result['stops'] as $stop) {
        // Collect info we want on Stop
        $stopInfo['stop_latitude'] = $stop['stop_latitude'];
        $stopInfo['stop_longitude'] = $stop['stop_longitude'];
        $stopInfo['stop_name'] = $stop['stop_name'];
        $stopInfo['route_type'] = $stop['route_type'];
        $stopInfo['stop_id'] = $stop['stop_id'];

        // Collect info we want on all departures to leave this stop
        $departures = array();

        // Call Departures on Each Stop
        $dToSort = Departures($stopInfo['route_type'], $stopInfo['stop_id']);
        $count = 0;
        foreach ($dToSort['departures'] as $departure) {
            // Arbitray limit to not spam the api or freeze it
            if ($count > 10)
                break;

            // Collect departure data
            $departureData['scheduled_departure_utc'] = $departure['scheduled_departure_utc'];
            $departureData['platform_number'] = $departure['platform_number'];

            $departureTime = new \DateTime($departure['scheduled_departure_utc']);

            if ($departureTime < $currentTime)
                continue;

            $count++;

            $departureEntry['route_id'] =  $departure['route_id'];
            $departureEntry['run_id'] =  $departure['run_id'];
            $run = Runs($departure['run_id'])['runs'];

            if ($run == null)
                continue;

            $departureEntry['destination_name'] = $run[0]['destination_name'];
            $departureEntry['data'] = $departureData;
            array_push($departures, $departureEntry);
            // }
        }

        // Push all data
        $stopInfo['departures'] = $departures;
        array_push($data, $stopInfo);
    }

    return $data;
}

function OrganiseSpecific($id, $type)
{
    global $result;
    global $currentTime;

    // Organise the data 
    $stopData = GetStop($id, $type);
    $data['stopName'] = $stopData['stop']['stop_name'];
    $data['stop_id'] = $id;
    $data['stop_type'] = $type;
    $data['stop_latitude'] = $stopData['stop']['stop_location']['gps']['latitude'];
    $data['stop_longitude'] = $stopData['stop']['stop_location']['gps']['longitude'];

    // Collect info we want on all departures to leave this stop
    $departures = array();

    // Call Departures on Each Stop
    $dToSort = Departures($type, $id);
    $count = 0;
    foreach ($dToSort['departures'] as $departure) {
        // Arbitray limit to not spam the api or freeze it
        if ($count > 15)
            break;

        // Collect departure data
        $departureData['scheduled_departure_utc'] = $departure['scheduled_departure_utc'];
        $departureData['platform_number'] = $departure['platform_number'];

        $departureTime = new \DateTime($departure['scheduled_departure_utc']);

        if ($departureTime < $currentTime)
            continue;

        $count++;

        $departureEntry['route_id'] =  $departure['route_id'];
        $departureEntry['run_id'] =  $departure['run_id'];
        $run = Runs($departure['run_id'])['runs'];

        if ($run == null)
            continue;

        $departureEntry['destination_name'] = $run[0]['destination_name'];
        $departureEntry['data'] = $departureData;
        array_push($departures, $departureEntry);
    }
    $data['departures'] = $departures;

    return $data;
}

# Checks if null so database doesn't get cluttered with null entities
if (isset($_POST['email'])) {
    # The kind for the new entity
    $kind = 'User';

    # The name/ID for the new entity
    $name = $_POST['email'];

    # The Cloud Datastore key for the new entity
    $taskKey = $datastore->key($kind, $name);

    # Prepares the new entity
    $task = $datastore->entity(
        $taskKey,
        [
            'Last Login' => new DateTime(),
            'Given Name' => $_POST['givenname'],
            'Family Name' => $_POST['familyname'],
            'Email' => $_POST['email'],
            'Full Name' => $_POST['fullname'],
            'IMG URL' => $_POST['imgurl'],
            'FavouritesID' => $_COOKIE['FavouriteStopID'],
            'TestID' => $_COOKIE['id'],
            'FavouritesType' => $_SESSION['favourite_stopType']
        ]

    );
    # Saves the entity
    $datastore->upsert($task);

    // Generate Favourite Data
    $favourite = OrganiseSpecific($_COOKIE['favourite_stopID'], $_COOKIE['favourite_stopType']);
    print_r($favourite);
}

?>
<!DOCTYPE html>
<html>

<head>
    <link rel="icon" href="data:,">

    <!-- Bootstap CSS -->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css" integrity="sha384-9aIt2nRpC12Uk9gS9baDl411NQApFmC26EwAOH8WgZl5MYYxFfc+NcPb1dKGj7Sk" crossorigin="anonymous">
    <link href="https://stackpath.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" rel="stylesheet" integrity="sha384-wvfXpqpZZVQGK6TAh5PVlGOfQNHSoD2xbE+QkPxCAFlNEevoEH3Sl0sibVcOQVnN" crossorigin="anonymous">

    <!-- JS, Popper.js, and jQuery -->
    <script src="https://code.jquery.com/jquery-3.5.1.min.js" integrity="sha256-9/aliU8dGd2tb6OSsuzixeV4y/faTqgFtohetphbbj0=" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js" integrity="sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/js/bootstrap.min.js" integrity="sha384-OgVRvuATP1z7JjHLkuOU7Xw704+h835Lr+6QL9UvYjZE3Ipu6Tp75j7Bh/kR0JKI" crossorigin="anonymous"></script>

    <!-- Google Login -->
    <meta name="google-signin-scope" content="profile email">
    <meta name="google-signin-client_id" content="323390293985-4o5gi4ubgmtndac68q6bul5litms6qpv.apps.googleusercontent.com">
    <script src="https://apis.google.com/js/platform.js" async defer></script>
</head>

<body>
    <!-- Retrieving data from Google Login -->
    <script>
        function signOut() {
            let auth2 = gapi.auth2.getAuthInstance();
            auth2.signOut().then(function() {
                sessionStorage.clear();
                document.cookie = "id=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;";
                document.cookie = "FavouriteStopID=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;";
                console.log('User signed out.');
            });
        }

        function delete_cookie(name) {
            document.cookie = name + '=; expires=Thu, 01 Jan 2012 00:00:01 GMT;';
        }

        function onSignIn(googleUser) {
            let auth2 = gapi.auth2.getAuthInstance();
            if (auth2.isSignedIn.get()) {
                // Useful data for your client-side scripts:
                let profile = googleUser.getBasicProfile();
                let myUserEntity = {}

                document.cookie = "id=" + profile.getId();

                myUserEntity.Id = profile.getId();
                sessionStorage.setItem('myUserEntity', JSON.stringify(myUserEntity));

                $.post("/", {
                    id: profile.getId(),
                    givenname: profile.getGivenName(),
                    familyname: profile.getFamilyName(),
                    email: profile.getEmail(),
                    fullname: profile.getName(),
                    imgurl: profile.getImageUrl(),
                });

                // $(document).ready(function() {
                //     // Check if the current URL contains '#'
                //     if (document.URL.indexOf("#") == -1) {
                //         // Set the URL to whatever it was plus "#".
                //         url = document.URL + "#";
                //         location = "#";

                //         //Reload the page
                //         location.reload(true);
                //     }
                // });
            }
        }

        function checkIfLoggedIn() {
            if (sessionStorage.getItem('myUserEntity') == null) {
                document.getElementById("gsignin").style.visibility = "visible";
                document.getElementById("gsignout").style.visibility = "hidden";
                //document.getElementById("favourites").style.visibility = "hidden";
            } else {
                var userEntity = {};
                userEntity = JSON.parse(sessionStorage.getItem('myUserEntity'));
                document.getElementById("gsignin").style.visibility = "visible";
                document.getElementById("gsignout").style.visibility = "visible";
                //document.getElementById("favourites").style.visibility = "visible";
            }
        }
        // window.onload = function() {
        //     var u = getCookie();
        //     document.getElementById("usr").innerHTML = u;
        // }

        // function getCookie(cname) {
        //     var name = "FavouriteStopID" + "=";
        //     var decodedCookie = decodeURIComponent(document.cookie);
        //     var ca = decodedCookie.split(';');
        //     for (var i = 0; i < ca.length; i++) {
        //         var c = ca[i];
        //         while (c.charAt(0) == ' ') {
        //             c = c.substring(1);
        //         }
        //         if (c.indexOf(name) == 0) {
        //             return c.substring(name.length, c.length);
        //         }
        //     }
        //     return "";
        // }
    </script>

    <!-- Navigation -->
    <nav class="navbar navbar-expand-lg navbar-dark bg-dark static-top" id="nav">
        <div class="container" id="nav">
            <a class="navbar-brand" href="/">PTV Planner</a>
            <ul class="navbar-nav ml-auto">
                <li class="nav-item active">
                    <div id="gsignin" class="g-signin2" data-onsuccess="onSignIn" data-theme="dark"></div>
                    <a href="/" id='gsignout' onclick="signOut();">Sign out</a>
                </li>
            </ul>
        </div>
    </nav>

    <!-- Twitter Feed -->
    <div class="float-right">
        <a class="twitter-timeline" data-height="1400" data-width="400" data-theme="dark" href="https://twitter.com/ptv_official?ref_src=twsrc%5Etfw">Tweets by ptv_official</a>
        <script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>
    </div>

    <!-- Favourites -->
    <?php
    if (isset($_COOKIE["id"])) {
        echo <<< EOT
        <div class="float-left mx-5 my-5">
            <div class="card">
                <div class="card-header">
                    <h3>Favourites</h3>
                </div>
                <div class="card-body">
EOT;
        foreach ($favourite as $departure) {
            $name = $departure['destination_name'];
            $platform = $departure['platform_number'];
            $id = $departure['run_id'];
            $time = $departure['data']['scheduled_departure_utc'];
            $convertedTime =  new \DateTime($time);
            $convertedTime->setTimezone(new DateTimeZone("Australia/Melbourne"));
            $stringConvert = $convertedTime->format('h:i:s A');

    echo <<< EOT
                <div class="card col-lg-4 px-0">
                    <div class="card-header">
                        <h4> To $name </h4>
                    </div>
                    <div class="card-body">
                        <p>On Platform $platform at Time: $stringConvert</p>
                    </div>
                </div>
            echo <<< EOT
                <p id="usr">
                </p>
                </div>
            </div>
        </div>
    
EOT;
}
    }
    ?>

    <!-- Page Content -->
    <div class="container text-center">

        <!-- Clock -->
        <div class="row">
            <div class="col-lg-10 text-center">
                <h1>
                    <div id="time"></div>
                </h1>
                <script>
                    function checkTime(i) {
                        return (i < 10) ? "0" + i : i;
                    }

                    function startTime() {
                        var today = new Date(),
                            h = checkTime(today.getHours()),
                            m = checkTime(today.getMinutes()),
                            s = checkTime(today.getSeconds());
                        document.getElementById('time').innerHTML = h + ":" + m + ":" + s;
                        t = setTimeout(function() {
                            startTime()
                        }, 500);
                    }
                    startTime();
                </script>

            </div>
        </div>


        <!-- Search Functionality -->
        <div class="row">
            <div class="col-lg-10 text-center">
                <h1 class="mt-5">Search</h1>
                <!-- Source: Licensed from Public Transport Victoria under a Creative Commons Attribution 4.0 International Licence." -->
                <form action="/" method="post">
                    <div class="row">
                        <div class="col-10">
                            <input class="form-control" type="text" name="search" id="search">
                        </div>
                        <div class="col-2">
                            <select class="form-control" name="search-filter" id="search-filter">
                                <option value=0>Metro</option>
                                <option value=3>V/line</option>
                            </select>
                        </div>
                    </div>
                </form>
                </ul>
            </div>
        </div>

        <!-- Showing All Stops -->
        <div class="row pt-2" id="accordion">
            <?php
            if ($showMap) {
                $organisedData = OrganiseData();
                $stopCount = 0;

                foreach ($organisedData as $stop) {
                    $stopName = $stop['stop_name'];
                    $stopID = $stop['stop_id'];
                    $stopType = $stop['route_type'];
                    $mapLat = $stop['stop_latitude'];
                    $mapLon = $stop['stop_longitude'];

                    echo <<< EOT

                    <div class="card col-lg-9 px-0">
                        <div class="card-header" id="heading$stopCount">
                            <h3 class="mb-0"> 
                                <button type="submit" form="$stopName" class="btn">
                                    <i class="fa fa-heart" aria-hidden="true">
                                        <form action="/" method="post" id="$stopName">
                                            <input class="hide" type="hidden" id="add_stopID" name="add_stopID" value="$stopID">
                                            <input class="hide" type="hidden" id="add_stopRoute" name="add_stopRoute" value="$stopType">
                                        </form>
                                    </i>
                                </button>
                                <button class="btn btn-default collapsed" data-toggle="collapse" data-target="#collapse$stopCount" aria-expanded="false" aria-controls="collapse$stopCount">
                                    $stopName
                                    <i class="fa fa-chevron-down"></i>
                                </button>
                            </h3>
                        </div>
                        <div id="collapse$stopCount" class="collapse" aria-labelledby="heading$stopCount" data-parent="#accordion">
                            <div class="card-body">
                                <div class="row" id="map">
                                <iframe src="https://www.google.com/maps/embed/v1/view?key=AIzaSyBMZN4xPoana_n56KXuglxFhflKOMZDB64&center=$mapLat,$mapLon&zoom=16"
                                    frameborder="0" width=600 height=600></iframe>
                                </div>
                                <div class="row">
                                    <h3 class="col-lg-12 text-center"><u> Upcoming </u></h3>
                                </div>
                                <div class="row">

EOT;

                    foreach ($stop['departures'] as $departure) {

                        $name = $departure['destination_name'];
                        $platform = $departure['platform_number'];
                        $id = $departure['run_id'];
                        $time = $departure['data']['scheduled_departure_utc'];
                        $convertedTime =  new \DateTime($time);
                        $convertedTime->setTimezone(new DateTimeZone("Australia/Melbourne"));
                        $stringConvert = $convertedTime->format('h:i:s A');

                        echo <<< EOT
                                    <div class="card col-lg-4 px-0">
                                        <div class="card-header">
                                            <h4> To $name </h4>
                                        </div>
                                        <div class="card-body">
                                            <p>On Platform $platform at Time: $stringConvert</p>
                                        </div>
                                    </div>

EOT;
                    }

                    echo <<< EOT
                                </div>
                            </div>
                        </div>
                    </div>
                    
EOT;
                    $stopCount++;
                }
            }

            ?>

        </div>
    </div>

</body>

</html>