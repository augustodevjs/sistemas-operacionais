/**
 * Representa um processo em um sistema operacional.
 * Responsável por armazenar informações sobre o processo, como identificador único,
 * tempo de espera, tempo de retorno, tempo total de execução (burst time) e
 * tempo restante de execução durante a simulação de escalonamento Round Robin.
 * @class
 */
export default class Process {
  /**
   * Cria uma instância da classe Process.
   * @constructor
   * @param {number} id - Identificador único do processo.
   * @param {number} burstTime - Tempo total de execução do processo (burst time).
   */
  constructor(id, burstTime) {
    this.id = id;
    this.tempoEspera = 0;
    this.tempoRetorno = 0;
    this.burstTime = burstTime;
    this.tempoRestante = burstTime;
  }
}