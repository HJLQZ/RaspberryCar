<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
        <title>小车控制</title>
    </head>
    <body>
        <form action="" method="GET">
            <h2>小车控制</h2>
            向前左转<input type="radio" name="radio" value="1">
            前行<input type="radio" name="radio" value="2">
            向前右转<input type="radio" name="radio" value="3">
            <br />
            停车<input type="radio" name="radio" value="0" checked="checked">
            向后左转<input type="radio" name="radio" value="4">
            后退<input type="radio" name="radio" value="5">
            向后右转<input type="radio" name="radio" value="6">
            <br />
            <input type="submit" name="submit" value="OK">
        </form>
        <?PHP
        $var=$_GET["radio"] ;
        switch ($var)
        {
        case "0":
        exec ("sudo ./main stop");
        break;
        case "1":
        exec ("sudo ./main leftFront") ;
        break;
        case "2":
        exec ("sudo ./main front") ;
        break;
        case "3" :
        exec ("sudo ./main rightFront") ;
        break;
        case "4":
        exec ("sudo ./main leftRear") ;
        break;
        case "5":
        exec ("sudo ./main rear") ;
        break;
        case "6":
        exec("sudo ./main rightRear") ;
        break;
        }
        ?>
    </body>
</html>
