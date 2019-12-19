<html>
<meta name="viewport" content="width=device-width, initial-scale=1.5">
<head>
<title>Light System Controls</title>
<style>
label {
    font: 1rem 'Fira Sans', sans-serif;
}

input {
    margin: .4rem;
}
</style>
</head>
<body>
<h1><u>Light System Controls</u></h1>

<form action="projecttest.php" method="post">
        <input type="checkbox" id="lamp1" name="Lamp1" value="Lamp1"/><label for="lamp1">Lamp1</label></br>
        <input type="checkbox" id="lamp2" name="Lamp2" value="Lamp2"/><label for="lamp2">Lamp2</label></br>
        <input type="checkbox" id="lamp3" name="Lamp3" value="Lamp3"/><label for="lamp3">Lamp3</label></br>
        <input type="checkbox" id="lamp4" name="Lamp4" value="Lamp4"/><label for="lamp4">Lamp4</label></br>
        <input type="checkbox" id="lamp5" name="Lamp5" value="Lamp5"/><label for="lamp5">Lamp5</label></br>
        <input type="checkbox" id="lamp6" name="Lamp6" value="Lamp6"/><label for="lamp6">Lamp6</label></br>
        <input type="checkbox" id="lamp7" name="Lamp7" value="Lamp7"/><label for="lamp7">Lamp7</label></br>
        <input type="checkbox" id="lamp8" name="Lamp8" value="Lamp8"/><label for="lamp8">Lamp8</label></br>
        <input type="checkbox" id="lamp9" name="Lamp9" value="Lamp9"/><label for="lamp9">Lamp9</label></br>
        <input type="checkbox" id="lamp10" name="Lamp10" value="Lamp10"/><label for="lamp10">Lamp10</label></br>
        <input type="submit" name="submit" value="Submit" />
</form>
</body>
</html>

<?php
if(isset($_POST['submit'])){
        checkLamp1();
        checkLamp2();
        checkLamp3();
        checkLamp4();
        checkLamp5();
        checkLamp6();
        checkLamp7();
        checkLamp8();
        checkLamp9();
        checkLamp10();
}

function checkLamp1(){
         if(isset($_POST['Lamp1'])){
                $output = shell_exec("/home/pi/Documents/testsend.py 1 3 2>&1");
                echo $output;
                echo "Lamp1 aan, ";
        }
        elseif(!isset($_POST['Lamp1'])){
                echo "Lamp1 uit, ";
        }
}

function checkLamp2(){
         if(isset($_POST['Lamp2'])){
                $output = shell_exec("/home/pi/Documents/testsend.py 2 3 2>&1");
                echo $output;
                echo "Lamp2 aan, ";
        }
        elseif(!isset($_POST['Lamp2'])){
                echo "Lamp2 uit, ";
        }
}

function checkLamp3(){
         if(isset($_POST['Lamp3'])){
                $output = shell_exec("/home/pi/Documents/testsend.py 3 3 2>&1");
                echo $output;
                echo "Lamp3 aan, ";
        }
        elseif(!isset($_POST['Lamp3'])){
                echo "Lamp3 uit, ";
        }
}

function checkLamp4(){
         if(isset($_POST['Lamp4'])){
                $output = shell_exec("/home/pi/Documents/testsend.py 4 3 2>&1");
                echo $output;
                echo "Lamp4 aan, ";
        }
        elseif(!isset($_POST['Lamp4'])){
                echo "Lamp4 uit, ";
        }
}

function checkLamp5(){
         if(isset($_POST['Lamp5'])){
                $output = shell_exec("/home/pi/Documents/testsend.py 5 3 2>&1");
                echo $output;
                echo "Lamp5 aan, ";
        }
        elseif(!isset($_POST['Lamp5'])){
                echo "Lamp5 uit, ";
        }
}

function checkLamp6(){
         if(isset($_POST['Lamp6'])){
                $output = shell_exec("/home/pi/Documents/testsend.py 6 3 2>&1");
                echo $output;
                echo "Lamp6 aan, ";
        }
        elseif(!isset($_POST['Lamp6'])){
                echo "Lamp6 uit, ";
        }
}

function checkLamp7(){
         if(isset($_POST['Lamp7'])){
                $output = shell_exec("/home/pi/Documents/testsend.py 7 3 2>&1");
                echo $output;
                echo "Lamp7 aan, ";
        }
        elseif(!isset($_POST['Lamp7'])){
                echo "Lamp7 uit, ";
        }
}

function checkLamp8(){
         if(isset($_POST['Lamp8'])){
                $output = shell_exec("/home/pi/Documents/testsend.py 8 3 2>&1");
                echo $output;
                echo "Lamp8 aan, ";
        }
        elseif(!isset($_POST['Lamp8'])){
                echo "Lamp8 uit, ";
        }
}

function checkLamp9(){
         if(isset($_POST['Lamp9'])){
                $output = shell_exec("/home/pi/Documents/testsend.py 9 3 2>&1");
                echo $output;
                echo "Lamp9 aan, ";
        }
        elseif(!isset($_POST['Lamp9'])){
                echo "Lamp9 uit, ";
        }
}

function checkLamp10(){
         if(isset($_POST['Lamp10'])){
                $output = shell_exec("/home/pi/Documents/testsend.py 10 3 2>&1");
                echo $output;
                echo "Lamp10 aan, ";
        }
        elseif(!isset($_POST['Lamp10'])){
                echo "Lamp10 uit, ";
        }
}

?>