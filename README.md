# CAL-Proj
Smart Delivery: empresa de distribui��o de mercadorias

> Compila��o:  
 * "t04/XXXXXX"(nome da pasta do distrito)
 * "obj/file_with_trucks.txt"
 * "obj/file_with_items.txt"

> Tarefas:  
* Process route -- Atraves dos algoritmos processar as rotas e fazer display ao mesmos por retorno a grafos  
* talvez adicionar uma op�ao para vizualizar main_map?? q � o grafo q � recolhido das pastas
* criar ficheiros de items para cada mapa  
* em extracting points controlar erros de inputs baseados nos todo  
* tentar centrar os mapas aquando da abertura  
* Algoritmos implementados:  a fazer, dijkstra consegue processar o caminha mais curto, mas so entre dois pontos (origem, destino) e e preciso apagar do grafo vertices que n tem arestas, senao o algoritmo vai falhar pq vai parar no node solitario.
* A ideia seria usar o algorotimo de caminh mais proximo para processar o trajeto dos items, mas agr que penso n sei como conjugar com dijkstra, ja q so calcula dois pontos. Checkar vizinho mais proximo duvido q estaj correto !!
* (sugest�o)criar agoritmos de pesquisa mais efecientes para andar nos vetores, pricipalmente qd se criam o grafo atraves da leitura do file, pq as vzes dempra bue qd � o porto ou lisboa ou assim. Pensei em binary search mas os vetores nao justificam ser ordenados  
 
 * n liguem aos typos pf...

 >Brainstormzito:  
  E se a gente fizer antes assim! usa-se vizinho mais proximo para fazer sort aos items, logo eles vao estar o melhor organizados possiveis, e depois usam-mos sucessivamente dijsktra para calcular path entre item ig:  
  * 5 items, sorted com closesnt neighbour. Processa grafo com dijkstra. Itera-se o vetor de items do genro 0-1, get path + 1-2 get path+2-3 get path..... 5+extract point e ta feito!


