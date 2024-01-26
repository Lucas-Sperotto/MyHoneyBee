<?php
$servername = "localhost"; // padrão do hostinger
$username = "u341345076_teste";
$password = "Teste12345678";
$dbname = "u341345076_Abelha_teste";

// Criar conexão
$conn = new mysqli($servername, $username, $password, $dbname);

// Checar conexão
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
?>