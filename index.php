<!DOCTYPE html>

<?php
require __DIR__ . '/vendor/autoload.php';

use Google\Cloud\Datastore\DatastoreClient;

# Your Google Cloud Platform project ID
$projectId = 'cc-ptv-planner';

# Instantiates a client
$datastore = new DatastoreClient([
    'projectId' => $projectId
]);

$devid = "3001608";
$apikey = "751a9dd5-9e2e-4f2a-b87d-009a45729806";
$searchurl = "http://timetableapi.ptv.vic.gov.au";

// Map
$showMap = false;
$mapLat = 0;
$mapLon = 0;
$mapName = "No Results";

// On Search Post
if (isset($_POST['search'])) {
    $result = SearchAndFilter();

    if (count($result['stops']) == 0) {
        // Found no stops near this search result
        // echo "Nothing";
    } else {
        // echo "Something";
        // print_r($result);
        $showMap = true;
        // $mapLat = $result['stops'][0]['stop_latitude'];
        // $mapLon = $result['stops'][0]['stop_longitude'];
        // $mapName = $result['stops'][0]['stop_name'];
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

    // Organise the data 
    // [Stops] -> []
    // $stop['route_type'], $stop['stop_id'], $stop['stop_name']

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
        // Grouped by route_id(run id), each element having scheduled time
        // departures['departures'][0]['run_id'] ... [0]['scheduled_departure_utc'] ... [0]['platform_number']
        $dToSort = Departures($stopInfo['route_type'], $stopInfo['stop_id']);
        $count = 0;
        foreach ($dToSort['departures'] as $departure) {
            // Arbitray limit to not spam the api or freeze it
            if ($count > 10)
                break;

            // Collect departure data
            $departureData['scheduled_departure_utc'] = $departure['scheduled_departure_utc'];
            $departureData['platform_number'] = $departure['platform_number'];

            // Check if already exists
            // $foundKey = array_search($departure['route_id'], array_column($departures, 'route_id'));
            // if ($foundKey != false) {
            //     // Run already exists.. add another platform, time
            //     array_push($departures[$foundKey]['data'], $departureData);
            // } else {
                $count++;
                // Call Run on each new Departure entry
                // Get name of each destination
                // runs[0]['destination_name']
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

?>

<html>

<head>
    <link rel="icon" href="data:,">

    <!-- Bootstap CSS -->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css" integrity="sha384-9aIt2nRpC12Uk9gS9baDl411NQApFmC26EwAOH8WgZl5MYYxFfc+NcPb1dKGj7Sk" crossorigin="anonymous">

    <!-- JS, Popper.js, and jQuery -->
    <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js" integrity="sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js" integrity="sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/js/bootstrap.min.js" integrity="sha384-OgVRvuATP1z7JjHLkuOU7Xw704+h835Lr+6QL9UvYjZE3Ipu6Tp75j7Bh/kR0JKI" crossorigin="anonymous"></script>

    <!-- Google Login -->
    <meta name="google-signin-scope" content="profile email">
    <meta name="google-signin-client_id" content="323390293985-4o5gi4ubgmtndac68q6bul5litms6qpv.apps.googleusercontent.com">
    <script src="https://apis.google.com/js/platform.js" async defer></script>
    <script>
        function onSignIn(googleUser) {
            // Useful data for your client-side scripts:
            var profile = googleUser.getBasicProfile();
            var id_token = googleUser.getAuthResponse().id_token;
            console.log("ID: " + profile.getId()); // Don't send this directly to your server!
            console.log('Full Name: ' + profile.getName());
            console.log('Given Name: ' + profile.getGivenName());
            console.log('Family Name: ' + profile.getFamilyName());
            console.log("Image URL: " + profile.getImageUrl());
            console.log("Email: " + profile.getEmail());
        }
    </script>
</head>

<body>
    <!-- Navigation -->
    <nav class="navbar navbar-expand-lg navbar-dark bg-dark static-top">
        <div class="container">
            <a class="navbar-brand" href="#">PTV Planner</a>
            <ul class="navbar-nav ml-auto">
                <li class="nav-item active">
                    <div class="g-signin2" data-onsuccess="onSignIn"></div>
                    <a href="#" onclick="signOut();">Sign out</a>
                </li>
            </ul>
        </div>
    </nav>

    <script>
        function signOut() {
            var auth2 = gapi.auth2.getAuthInstance();
            auth2.signOut().then(function() {
                console.log('User signed out.');
            });
        }
    </script>


    <!-- Twitter Feed -->
    <div class="float-right">
        <a class="twitter-timeline" data-height="1400" data-width="400" data-theme="dark" href="https://twitter.com/ptv_official?ref_src=twsrc%5Etfw">Tweets by ptv_official</a>
        <script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>
    </div>

    <!-- Page Content -->
    <div class="container">
        <!-- Clock -->
        <div class="container-fluid text-center">
            <script>
                function startTime() {
                    var today = new Date();
                    var h = today.getHours();
                    var m = today.getMinutes();
                    var s = today.getSeconds();
                    m = checkTime(m);
                    s = checkTime(s);
                    document.getElementById('txt').innerHTML =
                        h + ":" + m + ":" + s;
                    var t = setTimeout(startTime, 500);
                }

                function checkTime(i) {
                    if (i < 10) {
                        i = "0" + i
                    }; // add zero in front of numbers < 10
                    return i;
                }
            </script>
            <script>
                $.post
            </script>

            <body onload="startTime()">
                <h1>
                    <div id="txt"></div>
                </h1>
        </div>

        <!-- Search Functionality -->
        <div class="row">
            <div class="col-lg-9 text-center">
                <h1 class="mt-5">Search</h1>
                <!-- Source: Licensed from Public Transport Victoria under a Creative Commons Attribution 4.0 International Licence." -->
                <form action="/" method="post">
                    <div class="row">
                        <div class="col-10">
                            <input class="form-control" type="text" name="search" id="search">
                        </div>
                        <div class="col-2">
                            <select class="form-control" name="search-filter" id="search-filter">
                                <option value=0>Trains</option>
                                <option value=1>Trams</option>
                                <option value=2>Buses</option>
                                <option value=3>Vline</option>
                                <option value=4>Night Bus</option>
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

                    echo <<< EOT

                    <div class="card col-lg-9 px-0">
                        <div class="card-header" id="heading$stopCount">
                            <h3 class="mb-0"> 
                                <button class="btn btn-link collapsed" data-toggle="collapse" data-target="#collapse$stopCount" aria-expanded="false" aria-controls="collapse$stopCount">
                                    $stopName ▼
                                </button>
                            </h3>
                        </div>
                        <div id="collapse$stopCount" class="collapse" aria-labelledby="heading$stopCount" data-parent="#accordion">
                            <div class="card-body">
                                <div class="row">
                                    <h3 class="col-lg-12 text-center"><u> Upcoming Trains </u></h3>
                                </div>
                                <div class="row">

EOT;
                    foreach ($stop['departures'] as $departure) {

                        $name = $departure['destination_name'];
                        $id = $departure['run_id'];
                        $time = $departure['data']['scheduled_departure_utc'];

                        echo <<< EOT
                                    <div class="card col-lg-4 px-0">
                                        <div class="card-header">
                                            <h4> To $name </h4>
                                        </div>
                                        <div class="card-body">
                                            <p>Time: $time</p>
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

        <!-- Embeded Maps API -->
        <!-- 
        <?php
        //         if ($showMap)
        //             echo <<< EOT
        //                         <div class="row">
        //                             <div class="row col-12 text-center">
        //                                 <h3>$mapName</h3>
        //                             </div>
        //                             <!--The div element for the map -->
        //                             <div class="row col-12">
        //                                 <div id="map">
        //                                     <iframe src="https://www.google.com/maps/embed/v1/view?key=AIzaSyBMZN4xPoana_n56KXuglxFhflKOMZDB64&center=$mapLat,$mapLon&zoom=16"
        //                                         frameborder="0" width=600 height=600></iframe>
        //                                 </div>
        //                             </div>
        //                         </div>
        // EOT;

        ?>

    </div>

</body>

</html>