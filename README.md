# Controle-Estoque
 
# Controle de Estoque para Equipe de Manutenção

Este é um projeto de controle de estoque desenvolvido para a equipe de manutenção, utilizando o framework Qt Creator. O backend foi implementado em C++, e o banco de dados escolhido foi o SQLite.

## Funcionalidades Principais

### Cadastro de Materiais

Na página de cadastro de materiais, o usuário pode realizar as seguintes ações:

- Escolher o armário e a linha através de combobox.
- Preencher informações como nome do componente, quantidade, desenho, normal e observação.
- Ao tentar inserir um componente já existente no banco de dados, uma janela popup informará sobre a duplicidade, permitindo ao usuário decidir se deseja prosseguir com a inserção.

### Inventario

Nesta página, o usuário pode:

- Visualizar todos os componentes na tabela de acordo com a escolha do armário e linha.
- Utilizar um campo de pesquisa para encontrar um componente específico, filtrando por nome do componente, desenho ou normal.
- Atualizar a tabela.
- Editar uma linha selecionada, abrindo um popup para a edição do registro.
- Exportar a tabela para um arquivo .xlsx.
- Deletar o registro selecionado na tabela.

### Mapa

Na janela do mapa, o usuário pode visualizar:

- A quantidade de componentes registrados em cada linha, separada por componente eletrônico e mecânico.
- O total de componentes (mecânico + eletrônico).

### Importar/Exportar

Nesta janela, o usuário pode:

- Selecionar um arquivo .xlsx do computador e visualizar na tabela.
- Salvar os dados importados para o banco de dados do SQLite após confirmar o nome do armário e a senha através do combobox.


## Requisitos do Sistema

Certifique-se de ter as seguintes dependências instaladas:

- Qt Creator
- Biblioteca SQLite
- Outras dependências específicas do seu projeto

## Contribuição

Contribuições são bem-vindas! Sinta-se à vontade para abrir problemas ou enviar solicitações de pull.

## Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE).