<?php
include 'db_config.php';

/*************************************/
//Teste para a entidade Meliponicultor
/*************************************/

$meliponicultor_id = 1; // Substitua com um ID apropriado
$nome = "Nome do Meliponicultor";
$endereco_rua = "Rua do Meliponicultor";
$endereco_bairro = "Bairro do Meliponicultor";
$endereco_cep = "12345-678";
$cpf = "123.456.789-00";
$data_nascimento = "1980-01-01"; // Formato YYYY-MM-DD
$telefone = "(11) 91234-5678";
$whatsapp = "(11) 98765-4321";
$email = "email@exemplo.com";
$usuario_id = 1; // Substitua com o ID de usuário correspondente

// Preparando a consulta SQL
$stmt = $conn->prepare("INSERT INTO Meliponicultor (meliponicultor_id, nome, endereco_rua, endereco_bairro, endereco_cep, cpf, data_nascimento, telefone, whatsapp, email, fk_Usuario_usuario_id) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

// Vinculando parâmetros
$stmt->bind_param("isssssssssi", $meliponicultor_id, $nome, $endereco_rua, $endereco_bairro, $endereco_cep, $cpf, $data_nascimento, $telefone, $whatsapp, $email, $usuario_id);

// Executando a consulta e verificando se foi bem-sucedida
if ($stmt->execute()) {
    echo "Meliponicultor cadastrado com sucesso!";
} else {
    echo "Erro ao cadastrar meliponicultor: " . $stmt->error;
}

// Fechando a declaração e a conexão
$stmt->close();
$conn->close();

/**********************************/
//Teste para a entidade Meliponario
/**********************************/

$meliponario_id = 1; // Substitua com um ID apropriado
$meliponicultor_id = 1; // Substitua com o ID do meliponicultor correspondente
$nome_meliponario = "Nome do Meliponário";
$localizacao = "Localização do Meliponário";
$qtd_ninhos = 10; // Substitua com a quantidade de ninhos
$informacoes = "Informações adicionais";
$usuario_id = 1; // Substitua com o ID de usuário correspondente

// Preparando a consulta SQL
$stmt = $conn->prepare("INSERT INTO Meliponario (meliponario_id, meliponicultor_id, nome_meliponario, localizacao, qtd_ninhos, informacoes, fk_Meliponicultor_meliponicultor_id) VALUES (?, ?, ?, ?, ?, ?, ?)");

// Vinculando parâmetros
$stmt->bind_param("iisisii", $meliponario_id, $meliponicultor_id, $nome_meliponario, $localizacao, $qtd_ninhos, $informacoes, $usuario_id);

// Executando a consulta e verificando se foi bem-sucedida
if ($stmt->execute()) {
    echo "Meliponário cadastrado com sucesso!";
} else {
    echo "Erro ao cadastrar meliponário: " . $stmt->error;
}

// Fechando a declaração e a conexão
$stmt->close();
$conn->close();

/******************************/
//Teste para a entidade Colmeia
/******************************/

$nome_colmeia = "Nome da Colmeia";
$especie = "Espécie";
$data_instalacao = "2024-01-01"; // Formato YYYY-MM-DD
$status_colmeia = "Ativa";
$informacoes_colmeia = "Informações adicionais";

// Preparando a consulta SQL
$stmt = $conn->prepare("INSERT INTO Colmeia (nome_colmeia, especie, data_instalacao, status_colmeia, informacoes_colmeia) VALUES (?, ?, ?, ?, ?)");

// Vinculando parâmetros
$stmt->bind_param("sssss", $nome_colmeia, $especie, $data_instalacao, $status_colmeia, $informacoes_colmeia);

// Executando a consulta e verificando se foi bem-sucedida
if ($stmt->execute()) {
    echo "Nova colmeia adicionada com sucesso!";
} else {
    echo "Erro: " . $stmt->error;
}

// Fechando a declaração e a conexão
$stmt->close();
$conn->close();

/************************************/
//Teste para a entidade Monitoramento
/************************************/

$monitoramento_id = 1; // Substitua com um ID apropriado
$colmeia_id = 1; // Substitua com o ID da colmeia correspondente
$data_hora_coleta = "2024-01-01 10:00:00"; // Formato YYYY-MM-DD HH:MM:SS
$umidade_interna = 50.0;
$umidade_externa = 55.0;
$temperatura_interna = 35.0;
$temperatura_externa = 30.0;
$pressao_barometrica_interna = 1.0;
$pressao_barometrica_externa = 1.0;
$sensor_gas_1 = 0.1;
$sensor_gas_2 = 0.2;
$sensor_gas_3 = 0.3;
$sensor_luminosidade = 100.0;
$sensor_som = 50.0;
$peso_ninho = 5.0;

// Preparando a consulta SQL
$stmt = $conn->prepare("INSERT INTO Monitoramento (monitoramento_id, colmeia_id, data_hora_coleta, umidade_interna, umidade_externa, temperatura_interna, temperatura_externa, pressao_barometrica_interna, pressao_barometrica_externa, sensor_gas_1, sensor_gas_2, sensor_gas_3, sensor_luminosidade, sensor_som, peso_ninho) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

// Vinculando parâmetros
$stmt->bind_param("iisdddddddddddd", $monitoramento_id, $colmeia_id, $data_hora_coleta, $umidade_interna, $umidade_externa, $temperatura_interna, $temperatura_externa, $pressao_barometrica_interna, $pressao_barometrica_externa, $sensor_gas_1, $sensor_gas_2, $sensor_gas_3, $sensor_luminosidade, $sensor_som, $peso_ninho);

// Executando a consulta e verificando se foi bem-sucedida
if ($stmt->execute()) {
    echo "Registro de monitoramento adicionado com sucesso!";
} else {
    echo "Erro ao adicionar registro de monitoramento: " . $stmt->error;
}

// Fechando a declaração e a conexão
$stmt->close();
$conn->close();

/*******************************/
//Teste para a entidade Producao
/*******************************/

$producao_id = 1; // Substitua com um ID apropriado
$colmeia_id = 1; // Substitua com o ID da colmeia correspondente
$data_hora_coleta = "2024-01-01 10:00:00"; // Formato YYYY-MM-DD HH:MM:SS
$quantidade = 10.0; // Substitua com a quantidade produzida
$qualidade = "Alta"; // Substitua com a qualidade da produção

// Preparando a consulta SQL
$stmt = $conn->prepare("INSERT INTO Producao (producao_id, colmeia_id, data_hora_coleta, quantidade, qualidade) VALUES (?, ?, ?, ?, ?)");

// Vinculando parâmetros
$stmt->bind_param("iisds", $producao_id, $colmeia_id, $data_hora_coleta, $quantidade, $qualidade);

// Executando a consulta e verificando se foi bem-sucedida
if ($stmt->execute()) {
    echo "Registro de produção adicionado com sucesso!";
} else {
    echo "Erro ao adicionar registro de produção: " . $stmt->error;
}

// Fechando a declaração e a conexão
$stmt->close();
$conn->close();

/*****************************/
//Teste para a entidade Evento
/*****************************/

$evento_id = 1; // Substitua com um ID apropriado
$colmeia_id = 1; // Substitua com o ID da colmeia correspondente
$tipo_evento = "Tipo do Evento"; // Substitua com o tipo do evento
$informacoes_evento = "Informações sobre o evento";
$data_hora_evento = "2024-01-01 10:00:00"; // Formato YYYY-MM-DD HH:MM:SS

// Preparando a consulta SQL
$stmt = $conn->prepare("INSERT INTO Evento (evento_id, colmeia_id, tipo_evento, informacoes_evento, data_hora_evento) VALUES (?, ?, ?, ?, ?)");

// Vinculando parâmetros
$stmt->bind_param("iisss", $evento_id, $colmeia_id, $tipo_evento, $informacoes_evento, $data_hora_evento);

// Executando a consulta e verificando se foi bem-sucedida
if ($stmt->execute()) {
    echo "Registro de evento adicionado com sucesso!";
} else {
    echo "Erro ao adicionar registro de evento: " . $stmt->error;
}

// Fechando a declaração e a conexão
$stmt->close();
$conn->close();

/******************************/
//Teste para a entidade Usuario
/******************************/

$usuario_id = 1; // Substitua com um ID apropriado
$nome_usuario = "Nome do Usuário";
$email_usuario = "email@exemplo.com";
$senha_usuario = "senha123"; // Substitua com a senha real
$permissoes_usuario = "permissao"; // Substitua com as permissões do usuário

// Hashing da senha para segurança
$senha_hash = password_hash($senha_usuario, PASSWORD_DEFAULT);

// Preparando a consulta SQL
$stmt = $conn->prepare("INSERT INTO Usuario (usuario_id, nome_usuario, email_usuario, senha_usuario, permissoes_usuario) VALUES (?, ?, ?, ?, ?)");

// Vinculando parâmetros
$stmt->bind_param("issss", $usuario_id, $nome_usuario, $email_usuario, $senha_hash, $permissoes_usuario);

// Executando a consulta e verificando se foi bem-sucedida
if ($stmt->execute()) {
    echo "Usuário cadastrado com sucesso!";
} else {
    echo "Erro ao cadastrar usuário: " . $stmt->error;
}

// Fechando a declaração e a conexão
$stmt->close();
$conn->close();

/************************************/
//Teste para a entidade Log de Acesso
/************************************/

$log_acesso_id = 1; // Substitua com um ID apropriado
$usuario_id = 1; // Substitua com o ID do usuário correspondente
$data_hora_acesso = date("Y-m-d H:i:s"); // Data e hora atual
$tipo_acesso = "Login"; // Substitua com o tipo de acesso

// Preparando a consulta SQL
$stmt = $conn->prepare("INSERT INTO Log_de_Acesso (log_acesso_id, usuario_id, data_hora_acesso, tipo_acesso) VALUES (?, ?, ?, ?)");

// Vinculando parâmetros
$stmt->bind_param("iiss", $log_acesso_id, $usuario_id, $data_hora_acesso, $tipo_acesso);

// Executando a consulta e verificando se foi bem-sucedida
if ($stmt->execute()) {
    echo "Registro de log de acesso adicionado com sucesso!";
} else {
    echo "Erro ao adicionar registro de log de acesso: " . $stmt->error;
}

// Fechando a declaração e a conexão
$stmt->close();
$conn->close();

?>