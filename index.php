<!DOCTYPE html>

<?php
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
        // echo "Nothing";
    } else {
        // echo "Something";
        // print_r($result);
        $showMap = true;
        $mapLat = $result['stops'][0]['stop_latitude'];
        $mapLon = $result['stops'][0]['stop_longitude'];
        $mapName = $result['stops'][0]['stop_name'];
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

?>

<html>

<head>
    <!-- Bootstap CSS -->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css" integrity="sha384-9aIt2nRpC12Uk9gS9baDl411NQApFmC26EwAOH8WgZl5MYYxFfc+NcPb1dKGj7Sk" crossorigin="anonymous">

    <!-- JS, Popper.js, and jQuery -->
    <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js" integrity="sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js" integrity="sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/js/bootstrap.min.js" integrity="sha384-OgVRvuATP1z7JjHLkuOU7Xw704+h835Lr+6QL9UvYjZE3Ipu6Tp75j7Bh/kR0JKI" crossorigin="anonymous"></script>
</head>

<body>

    <!-- Navigation -->
    <nav class="navbar navbar-expand-lg navbar-dark bg-dark static-top">
        <div class="container">
            <a class="navbar-brand" href="#">PTV Planner</a>
            <ul class="navbar-nav ml-auto">
                <li class="nav-item active">
                    <a class="nav-link" href="#">Login</a>
                </li>
            </ul>
        </div>
    </nav>



    <!-- Twitter Feed -->
    <div class="float-right">
        <a class="twitter-timeline" data-height="1400" data-width="400" data-theme="dark" href="https://twitter.com/ptv_official?ref_src=twsrc%5Etfw">Tweets by ptv_official</a>
        <script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>
    </div>

    <!-- Page Content -->
    <div class="container">
        <!-- Search Functionality -->
        <div class="row">
            <div class="col-lg-12 text-center">
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

        <!-- Embeded Maps API -->
        <?php
        if ($showMap){
            echo <<<END
                <div class="row">
                    <div class="row col-12 text-center">
                        <h3>$mapName</h3>
                    </div>
                    <!--The div element for the map -->
                    <div class="row col-12">
                        <div id="map">
                            <iframe src="https://www.google.com/maps/embed/v1/view?key=AIzaSyBMZN4xPoana_n56KXuglxFhflKOMZDB64&center=$mapLat,$mapLon&zoom=16"
                                frameborder="0" width=600 height=600></iframe>
                        </div>
                    </div>
                </div>

            END;
        }
            

        ?>

    </div>



</body>

</html>