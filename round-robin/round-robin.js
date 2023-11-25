import Process from "./process.js";

/**
 * Escalonador Round Robin
 *
 * Esta função implementa o algoritmo de escalonamento Round Robin para alocar tempo de CPU
 * a um conjunto de processos, considerando um intervalo de tempo especificado.
 *
 * @param {Array} processes - Um array de objetos de processo com propriedades 'id' e 'burstTime'.
 * @param {Number} quantum - O quantum de tempo alocado a cada processo para execução.
 * @returns {Object} - Um objeto contendo várias métricas de desempenho após a execução.
 *
 * @example
 * const processes = [
 *   { id: 1, burstTime: 5 },
 *   { id: 2, burstTime: 8 },
 *   // Adicione mais processos conforme necessário
 * ];
 * const quantum = 2;
 * const results = roundRobin(processes, quantum);
 * console.log(results);
 */

export default function roundRobin(processes, quantum) {
  // Cópia da lista de processos para evitar alterações indesejadas na lista original.
  const processList = processes.map(process => new Process(process.id, process.burstTime));

  let time = 0;
  let fila = [...processList]; // Fila de processos prontos para execução
  let filaEncerrados = []; // Fila de processos concluídos

  while (fila.length > 0) {
    const process = fila.shift(); // Em cada iteração do loop, o próximo processo é retirado da fila, simulando sua execução.
    time += 1; 

    /**
     * Se o tempo restante do processo for menor ou igual ao quantum, o 
     * processo é executado completamente. O tempo restante do processo é 
     * adicionado ao tempo de execução global, e as métricas como tempo de 
     * espera, tempo de retorno e tempo restante são atualizadas.
     */
    if (process.tempoRestante <= quantum) {
      time += process.tempoRestante; 
      process.tempoRestante = 0; 
      process.tempoEspera = time - process.burstTime; 
      process.tempoRetorno = time; 
      filaEncerrados.push(process); 
    } 
    /**
     * Se o tempo restante do processo for maior que o quantum, o processo é 
     * executado pelo quantum. O quantum é adicionado ao tempo de execução 
     * global, e o tempo restante do processo é reduzido pelo quantum. O 
     * processo é então adicionado de volta à fila de prontos para execução 
     * futura.
     */
    else {
      time += quantum; 
      process.tempoRestante -= quantum; 
      fila.push(process); 
    }
  }

  const mediaEspera =
    filaEncerrados.reduce((soma, process) => soma + process.tempoEspera, 0) /
    filaEncerrados.length;

  const mediaRetorno =
    filaEncerrados.reduce((soma, process) => soma + process.tempoRetorno, 0) /
    filaEncerrados.length;

  const vazao = filaEncerrados.length / time;

  return {
    time,
    mediaEspera,
    mediaRetorno,
    vazao,
  };
};
