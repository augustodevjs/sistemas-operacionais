import random
import matplotlib.pyplot as plt

def fifo(page_references, num_frames):
    frames = []
    page_faults = 0

    for page in page_references:
        if page not in frames:
            if len(frames) < num_frames:
                frames.append(page)
            else:
                frames.pop(0)
                frames.append(page)
            page_faults += 1

    return page_faults

def aging(page_references, num_frames, aging_bits):
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

        # Atualiza os bits de envelhecimento
        for p in frames:
            frames[p] >>= 1
            if p == page:
                frames[p] |= (1 << (aging_bits - 1))

    return page_faults

def generate_page_references(num_references, num_pages):
    return [random.randint(0, num_pages - 1) for _ in range(num_references)]

def main():
    num_references = 10000
    num_pages = 100
    aging_bits = 8
    num_frames_range = range(1, 11)  # Testa com 1 a 10 molduras de página

    fifo_page_faults = []
    aging_page_faults = []

    page_references = generate_page_references(num_references, num_pages)

    for num_frames in num_frames_range:
        fifo_faults = fifo(page_references, num_frames)
        aging_faults = aging(page_references, num_frames, aging_bits)

        fifo_page_faults.append(fifo_faults)
        aging_page_faults.append(aging_faults)

    # Plota os resultados
    plt.plot(num_frames_range, fifo_page_faults, label='FIFO')
    plt.plot(num_frames_range, aging_page_faults, label='Aging')
    plt.xlabel('Número de Molduras de Página')
    plt.ylabel('Faltas de Página por 1000 Referências')
    plt.legend()
    plt.show()

if __name__ == "__main__":
    main()
