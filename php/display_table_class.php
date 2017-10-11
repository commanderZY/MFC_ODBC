<?php 
   echo"学生成绩信息表</br>";      
     $conn = mysqli_connect('127.0.0.1','root','123','MFC_ODBC') or die('unable to connect ');
    if(!$conn)
    {
        echo "error could not connect to database";
        exit;
    }
    echo '<br>';
    mysqli_query($conn,"set names 'UTF8'");
    $query = "select * from class";
    $result = mysqli_query($conn,$query);
    $row=mysqli_fetch_row ($result);     
          
    echo '<font face="verdana">';     
    echo '<table border="1" cellpadding="1" cellspacing="2">';

    echo "<table style='border-color: #efefef;' border='1px' cellpadding='5px' cellspacing='0px'>";

    echo "<table border=1;table align='center';table width=800 height=40>";
    mysqli_data_seek($result, 0);

$row=mysqli_fetch_row ($result);     
          
    echo '<font face="verdana">';     
    echo '<table border="1" cellpadding="1" cellspacing="2">';

    echo "<table style='border-color: #efefef;' border='1px' cellpadding='5px' cellspacing='0px'>";

    echo "<table border=1;table align='center';table width=800 height=40>";
    mysqli_data_seek($result, 0);


    while($field = mysqli_fetch_field($result))
    {
        echo '<td bgcolor="#F0F8FF">';
        echo "<p align=center>$field->name</p>";
    }

    while ($row=mysqli_fetch_row($result))
    {     
        echo '<tr></b>';     
        for($i=0;$i<mysqli_num_fields($result);$i++)     
        {     
            echo '<td bgcolor="#808080">';
            echo "<p align=center>$row[$i]</p>";     
            echo '</td>';     
        }     
        echo '</tr></b>';     
    }
    mysqli_free_result($result);

    mysqli_close($conn);
?>
