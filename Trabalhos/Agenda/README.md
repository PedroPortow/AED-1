# Trabalho Agenda
**Nome**: Pedro Luís Rodrigues Porto
**Discord**: Pedro Porto #2950

**Regras de código**: [https://fabiensanglard.net/fd_proxy/doom3/CodeStyleConventions.pdf](https://fabiensanglard.net/fd_proxy/doom3/CodeStyleConventions.pdf)

**Proposta** : Continuar a sua implementação da agenda (exercício 3) semana 1 dentro dos mesmo parâmetros, mas incluir o seguinte.Nenhuma variável pode ser declarada em todo o programa, somente ponteiros. Todos os dados do programa devem ser guardados dentro do pBuffer.
Nem mesmo como parâmetro de função. Só ponteiros que apontam para dentro do pBuffer.Exemplo do que não pode: int c; char a; int v[10];  void Funcao(int parametro)
Não pode usar struct em todo o programa.Usar fila ordenada (heap) para armazenar as pessoas em ordem alfabética sempre que o usuário incluir uma nova pessoa.
Implementar a base de dados da agenda usando lista duplamente ligada
Somente essa base de dados pode ficar fora do buffer principal, ou seja, pode usar um malloc para cada nodo.

**Para compilar:** 
-  gcc ./agenda.c -o agenda 
- ./agenda

**Funcionamento**: A agenda está funcionando como esperado
**Dificuldades**: Tive bastante dificuldade no início, fiquei um tempo travado tentando implementar e sem sair do lugar. Porém, depois de algumas tentivas consegui chegar num raciocínio e implementar no código
**Observações**: Deixei alguns comentários no código que usei pra me guiar durante a implementação, acho que é legal pra ver o raciocínio que usei pra chegar na implementação.
