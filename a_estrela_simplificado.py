class No:
    def __init__(self, nome, vizinho=None, G=0, H=0, pai=None):
        self.nome = nome
        self.vizinho = vizinho
        self.G = G
        self.H = H
        if self.G is not None and self.H is not None:
            self.F = G+H
        else:
            self.F = 0
        self.pai = pai

    def __str__(self):
        return f"X: {self.nome} -> F:{self.F} "
        
def mostraMapa():
    print("-" * 50)
    for i in range(3):
        for j in range(3):
            print(f" {mapa[i][j]} ", end='')
        print()
    print("-" * 50)
    print()
    

def calcula_custos(vizinho, no_atual):
    vizinho.pai = no_atual
    vizinho.G = no_atual.G + 1 
    vizinho.H = no_atual.H - 1  # heuristica inventada onde a distancia ao objetivo é a do pai - 1 
    vizinho.F = vizinho.G + vizinho.H 

# criacao dos nós
a = No("a")
b = No("b")
c = No("c")
d = No("d") # player
f = No("f") # objetivo
g = No("g")
h = No("h")
i = No("i")
block = No("block")

# definicao dos vizinhos
a.vizinhos = [b, c, d]
d.vizinhos = [a, g, block]
b.vizinhos = [a, c, block]
g.vizinhos = [d, h]
h.vizinhos = [i, g, block]
c.vizinhos = [b, f]
i.vizinhos = [h, f]
f.vizinhos = [c, block, i]

# criacao do mapa 
mapa = [[a, b, c],[d, block, f],[g, h, i]]

# exibicao do mapa inicial
mostraMapa()

# listas de controle, a aberta indica caminhos possiveis, a fechada por onde ja passou.
lista_aberta = [d]
lista_fechada = []

# distancia do no atual ate o destino:
d.H = 4

# até ter algo na lista aberta
while lista_aberta:
    no_atual = lista_aberta.pop(0)
    print(no_atual)
    
    # verifica se o no atual é o destino
    if no_atual.nome == "f":
        mostraMapa()
        print("Encontrou")
        break
    
    # calcula custo dos vizinhos
    for vizinho in no_atual.vizinhos:
        if vizinho.nome != "block":
            calcula_custos(vizinho, no_atual)

    # ordena a lista de vizinhos do menor custo F para o maior 
    no_atual.vizinhos = sorted(no_atual.vizinhos, key=lambda x: x.F)
    # adiciona os vizinhos a lista aberta
    for vizinho in no_atual.vizinhos:
        if vizinho not in lista_aberta and vizinho not in lista_fechada and vizinho.nome != "block":
            lista_aberta.append(vizinho)
    # adiciona o no atual a lista fechada
    lista_fechada.append(no_atual)
    # no atual é o de menor F 
    lista_aberta = sorted(lista_aberta, key=lambda x: x.F)
    mostraMapa()
