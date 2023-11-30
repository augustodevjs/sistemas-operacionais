import random
import matplotlib.pyplot as plt

def fifo(page_references, num_frames):
    """
    Implementação do algoritmo FIFO (First-In-First-Out) para simulação de substituição de página.

    Parâmetros:
    - page_references: Lista de referências de página.
    - num_frames: Número máximo de molduras de página.

    Retorna:
    - Número total de faltas de página.
    """

    """ 
    Inicializa uma lista vazia chamada frames para representar as molduras de página e uma variável page_faults para contar as faltas de página.
    """
    frames = []
    page_faults = 0

    for page in page_references:
        # Se a página não estiver presente nas molduras (frames), ocorre uma falta de página:
        if page not in frames:
            # Se o número de molduras ainda não atingiu o máximo (len(frames) < num_frames), a página é simplesmente adicionada às molduras.
            if len(frames) < num_frames:
                frames.append(page)
            # Caso contrário, a página mais antiga é removida, e a nova página é adicionada ao final da lista.
            else:   
                frames.pop(0)
                frames.append(page)
            #Incrementa o contador de faltas de página.
            page_faults += 1

    return page_faults

def aging(page_references, num_frames, aging_bits):
    """
    Implementação do algoritmo de envelhecimento para simulação de substituição de página.

    Parâmetros:
    - page_references: Lista de referências de página.
    - num_frames: Número máximo de molduras de página.
    - aging_bits: Número de bits para os bits de envelhecimento.

    Retorna:
    - Número total de faltas de página.
    """
    frames = {}
    page_faults = 0

    for page in page_references:
        if page not in frames:
            if len(frames) < num_frames:
                frames[page] = aging_bits
            else:
                min_page = min(frames, key=frames.get)
                frames.pop(min_page)
                frames[page] = aging_bits
            page_faults += 1

        for p in frames:
            frames[p] >>= 1
            if p == page:
                frames[p] |= (1 << (aging_bits - 1))

    return page_faults

def simulate_page_replacement_algorithm(algorithm, page_references, num_frames, *args):
    """
    Simula a execução de um algoritmo de substituição de página.

    Parâmetros:
    - algorithm: Função representando o algoritmo.
    - page_references: Lista de referências de página.
    - num_frames: Número máximo de molduras de página.
    - *args: Argumentos adicionais para a função do algoritmo.

    Retorna:
    - Lista de números de molduras e total de faltas de página para cada configuração de molduras.
    """
    frames = []  # Adicionado para redefinir os frames para cada simulação
    page_faults = 0
    page_faults_per_num_frames = []

    for num_frames in range(1, num_frames + 1):
        page_faults = algorithm(page_references, num_frames, *args)
        page_faults_per_num_frames.append(page_faults)
        print(f"Num. Molduras: {num_frames} | Faltas de Página: {page_faults}")

    return page_faults_per_num_frames

def plot_results(num_frames_range, page_faults_fifo, page_faults_aging):
    """
    Gera um gráfico com os resultados da simulação.

    Parâmetros:
    - num_frames_range: Lista de números de molduras.
    - page_faults_fifo: Lista de faltas de página para o algoritmo FIFO.
    - page_faults_aging: Lista de faltas de página para o algoritmo de envelhecimento.
    """
    plt.plot(num_frames_range, page_faults_fifo, label='FIFO')
    plt.plot(num_frames_range, page_faults_aging, label='Aging')
    plt.xlabel('Número de Molduras de Página')
    plt.ylabel('Faltas de Página')
    plt.legend()
    plt.show()

def generate_page_references(num_references, num_pages):
    """
    Gera uma sequência aleatória de referências de página.

    Parâmetros:
    - num_references: Número de referências a serem geradas.
    - num_pages: Número total de páginas possíveis.

    Retorna:
    - Lista de referências de página.
    """
    return [random.randint(0, num_pages - 1) for _ in range(num_references)]

def main():
    num_references = 10000
    num_pages = 100
    aging_bits = 8
    num_frames = 10  # Número máximo de molduras

    page_references = generate_page_references(num_references, num_pages)

    page_faults_fifo = simulate_page_replacement_algorithm(fifo, page_references, num_frames)
    page_faults_aging = simulate_page_replacement_algorithm(aging, page_references, num_frames, aging_bits)

    plot_results(range(1, num_frames + 1), page_faults_fifo, page_faults_aging)

if __name__ == "__main__":
    main()
