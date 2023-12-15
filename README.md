# Controle-Estoque
 
# Controle de Estoque para Equipe de Manutenção
![0](https://github.com/IgorGomes22/Controle-Estoque/assets/88172222/3410cd34-4237-4bb1-9963-864b21ed5948)
Este é um projeto de controle de estoque desenvolvido para a equipe de manutenção, utilizando o framework Qt Creator. O backend foi implementado em C++, e o banco de dados escolhido foi o SQLite.

## Funcionalidades Principais

### Cadastro de Materiais

Na página de cadastro de materiais, o usuário pode realizar as seguintes ações:
![2](https://github.com/IgorGomes22/Controle-Estoque/assets/88172222/e8b7ee2b-023c-4205-90a0-0d5ff2732bf1)
- Escolher o armário e a linha através de combobox.
- Preencher informações como nome do componente, quantidade, desenho, normal e observação.
- Ao tentar inserir um componente já existente no banco de dados, uma janela popup informará sobre a duplicidade, permitindo ao usuário decidir se deseja prosseguir com a inserção.

### Inventario
![3](https://github.com/IgorGomes22/Controle-Estoque/assets/88172222/2bb7dc67-bc57-48b4-a422-7baa49ba72e2)
Nesta página, o usuário pode:

- Visualizar todos os componentes na tabela de acordo com a escolha do armário e linha.
- Utilizar um campo de pesquisa para encontrar um componente específico, filtrando por nome do componente, desenho ou normal.
- Atualizar a tabela.
- Editar uma linha selecionada, abrindo um popup para a edição do registro.
- ![4](https://github.com/IgorGomes22/Controle-Estoque/assets/88172222/596ffc54-36be-4548-a86d-c651983d5e24)
- Exportar a tabela para um arquivo .xlsx.
- ![5](https://github.com/IgorGomes22/Controle-Estoque/assets/88172222/c501093d-4ea3-4bcc-8438-bee07984ce38)
- Deletar o registro selecionado na tabela.

### Mapa
![6](https://github.com/IgorGomes22/Controle-Estoque/assets/88172222/8e38f7f8-f414-4fad-8cdb-51d75be10efc)
Na janela do mapa, o usuário pode visualizar:

- A quantidade de componentes registrados em cada linha, separada por componente eletrônico e mecânico.
- O total de componentes (mecânico + eletrônico).

### Importar/Exportar
![7](https://github.com/IgorGomes22/Controle-Estoque/assets/88172222/67c2d9a9-60e7-4500-8ff5-0d1cab47a7db)
Nesta janela, o usuário pode:

- Selecionar um arquivo .xlsx do computador e visualizar na tabela.
- Salvar os dados importados para o banco de dados do SQLite após confirmar o nome do armário e a senha através do combobox.
![8](https://github.com/IgorGomes22/Controle-Estoque/assets/88172222/f820e0ec-ee3f-4680-8e29-a4a78a91fda1)

## Requisitos do Sistema

Certifique-se de ter as seguintes dependências instaladas:

- Qt Creator
- Biblioteca SQLite
- Outras dependências específicas do seu projeto

## Contribuição

Contribuições são bem-vindas! Sinta-se à vontade para abrir problemas ou enviar solicitações de pull.

## Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE).
