Essa é uma implementação em c do algoritmo de dijkstra.
Uma matriz de inteiro 20x20, estatica, foi criada para guardar as conexoes das arestas. 
nVertices é uma variável global que guarda o numero de vertices. 
Qualquer vertice podera ser o ponto de origem como tambem o ponto de destino.
Toda vertice sera identificada por um id, que é um inteiro.
Toda vertice nova criada recebera o id "n" (n é o numero de vertice ja estabelecido).
O primeiro id é 0, o segundo é 1, o terceiro 3 e assim sucessivamente.
Ao se excluir um vertice, por fim de facilidade, o ultimo vertice recebera o id do vertice retirado.
Ao se perguntar se uma nova vertice "recebe" a aresta, significa que a aresta tera o sentido
voltado para si, enquanto que "leva" a aresta, o sentido sera para a outra vertice de conexao.
