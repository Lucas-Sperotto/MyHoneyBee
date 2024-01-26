<?php
include 'db_config.php';

function cadastrarUsuario($nome_usuario, $email_usuario, $senha_usuario, $permissoes_usuario) {
    global $conn;

    // Hashing da senha para segurança
    $senha_hash = password_hash($senha_usuario, PASSWORD_DEFAULT);

    // Preparando a consulta SQL para evitar injeção de SQL
    $stmt = $conn->prepare("INSERT INTO Usuario (nome_usuario, email_usuario, senha_usuario, permissoes_usuario) VALUES (?, ?, ?, ?)");
    $stmt->bind_param("ssss", $nome_usuario, $email_usuario, $senha_hash, $permissoes_usuario);

    // Executando a consulta e verificando se foi bem-sucedida
    if ($stmt->execute()) {
        echo "Usuário cadastrado com sucesso!";
    } else {
        echo "Erro ao cadastrar usuário: " . $stmt->error;
    }

    $stmt->close();
}

// Exemplo de uso da função
cadastrarUsuario("Nome do Usuário", "email@exemplo.com", "senha123", "permissao");
?>