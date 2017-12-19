import pandas as pd

class CongruenteLinear():
	"""
		Criação do objeto. Recebe como argumentos o valor do modulo, a e c.
		Cria também um dataframe com pandas, com as colunas pré definidas
		Esse dataframe é criado para facilitar o plot do gráfico pelo seaborn
	"""
	def __init__(self, modulo, a, c):
		self.mod = modulo
		self.a = a
		self.c = c
		self.df = pd.DataFrame(columns=['Valor agrupado', 'Quantidade'])

	"""
		Essa é a função principal. Dado a semente e um valor n, ele gera 
		n valores aleatórios pelo Método Congruente Linear.
	"""
	def gerandoValores(self, n, semente):
		self.anterior = semente
		values = []
		for _ in range(n):
			num = (self.anterior * self.a + self.c)%self.mod
			self.anterior = num
			values.append(num/self.mod)
		return values


	"""
		Essa função foi criada apenas para facilitar a visualização. Dado um valor n e uma semente,
		ele chama a função 'gerandoValores', e após isso ele agrupa esses valores em intervalos e
		adiciona ao dataframe (seaborn le o dataframe e plota o gráfico já com as barras de erro).
	"""
	def gerandoValoresAgrupados(self, n, semente):
		lista = ['[ 0,0.1 )','[ 0.1,0.2 )','[ 0.2,0.3 )','[ 0.3,0.4 )','[ 0.4,0.5 )','[ 0.5,0.6 )','[ 0.6,0.7 )','[ 0.7,0.8 )', 
		'[ 0.8,0.9 )','[ 0.9,1 )']
		results = self.gerandoValores(n, semente)
		resp = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
		for i in results:
			resp[int(i*10)] += 1
		for i in range(10):
			self.df.loc[len(self.df)] = [lista[i], resp[i]]
		return self.df

"""
	Essa é uma função fora do escopo do objeto. Ela recebe uma matriz, onde cada linha é um vetor com números
	aleatórios. Esses valores são concatenados em um dataframe, que é retornado pela função.
	Também foi implementado com o intuito de facilitar o plot do gráfico.
"""
def gerandoValoresAgrupadosOutClass(matriz):
	lista = ['[ 0,0.1 )','[ 0.1,0.2 )','[ 0.2,0.3 )','[ 0.3,0.4 )','[ 0.4,0.5 )','[ 0.5,0.6 )','[ 0.6,0.7 )','[ 0.7,0.8 )', 
		'[ 0.8,0.9 )','[ 0.9,1 )']
	df = pd.DataFrame(columns=['Valor agrupado', 'Quantidade'])
	for results in matriz:
		resp = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
		for i in results:
		    resp[int(i*10)] += 1
		for i in range(10):
			df.loc[len(df)] = [lista[i], resp[i]]
	return df