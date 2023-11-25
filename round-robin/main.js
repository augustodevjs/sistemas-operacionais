import Process from "./process.js";
import roundRobin from "./round-robin.js";

window.show = function () {
  const chartContainer = document.getElementById("chartContainer");
  chartContainer.innerHTML = "";

  const numProcessos = 5;
  const processos = Array.from(
      { length: numProcessos },
      (_, i) => new Process(i, Math.floor(Math.random() * 5) + 1)
    );

  for (let quantum = 1; quantum <= 5; quantum++) {
    const innerDiv = document.createElement("div");
    const canvas = document.createElement("canvas");
    const quantumTitle = document.createElement("h1");
    const quantumContainer = document.createElement("div");
    const processCodeContainer = document.createElement("pre");
    
    quantumTitle.innerText = `Quantum ${quantum}`;
    processCodeContainer.className = "process-code";
    quantumContainer.className = "quantum-container";

    innerDiv.appendChild(quantumTitle);
    quantumContainer.appendChild(innerDiv);
    innerDiv.appendChild(processCodeContainer);
    chartContainer.appendChild(quantumContainer);

    const processCode = processos
      .map(
        (process) => `Processo ${process.id + 1}: Burst Time: ${process.burstTime}s, Tempo de espera: ${process.tempoEspera}s, Tempo de retorno: ${process.tempoRetorno}s, Tempo restante: ${process.tempoRestante}s`
      )
      .join("\n");

    processCodeContainer.innerText = processCode;

    const valores = roundRobin(processos, quantum);

    canvas.className = "chart";
    canvas.width = 500;
    canvas.height = 150;
    quantumContainer.appendChild(canvas);

    const ctx = canvas.getContext("2d");

    new Chart(ctx, {
      type: "bar",
      data: {
        labels: [
          "Tempo de execução (s)",
          "Tempo médio de espera (s)",
          "Tempo médio de retorno (s)",
          "Vazão processos/s",
        ],
        datasets: [
          {
            backgroundColor: ["#ff6f61", "#5d9cec", "#66c060", "#ffb74d"],
            data: [
              valores.time,
              valores.mediaEspera.toFixed(2),
              valores.mediaRetorno.toFixed(2),
              valores.vazao.toFixed(4),
            ],
          },
        ],
      },
      options: {
        scales: {
          y: {
            beginAtZero: true,
            ticks: {
              color: "#cbd5e0",
            },
          },
          x: {
            ticks: {
              color: "#cbd5e0",
            },
          },
        },
        plugins: {
          legend: {
            display: false,
          },
        },
      },
    });
  }
};