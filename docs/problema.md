Esse problema está no **documento `22.pdf`**, correspondente à **17ª Maratona de Programação Paralela (SBAC-PAD & WSCAD – 2022)**. Ele é o **Problema C – N-Body Simulation**.

Aqui está a versão em **Markdown**, formatada para facilitar a leitura:

---

## 🪐 Problema C – N-Body Simulation

### Descrição

Uma simulação de N corpos modela um sistema dinâmico de partículas, normalmente sob a influência de forças físicas, prevendo seus movimentos individuais. Uma aplicação bem conhecida é na astrofísica, onde partículas representam corpos celestes que interagem gravitacionalmente.

O código fornecido (sequencial) simula um sistema simples em 3D. Seu trabalho é criar uma **versão paralela** da simulação, mantendo a **correção dos resultados**.

---

### 📥 Entrada

O programa recebe um **arquivo binário**, contendo a estrutura com **6 valores do tipo `float`** para cada partícula no sistema:

* `x, y, z`: posição da partícula
* `vx, vy, vz`: velocidade da partícula

A entrada deve ser lida da **entrada padrão (stdin)**.

---

### 📤 Saída

O programa deve gerar um **arquivo binário de saída**, com o **mesmo formato** da entrada, contendo as **posições e velocidades atualizadas** de cada partícula após a simulação.

A saída deve ser escrita na **saída padrão (stdout)**.

---

### 🧪 Exemplo (em string, apenas para fins ilustrativos)

#### Entrada:

```
0.680375 -0.211234 0.566198
0.596880 0.823295 -0.604897
...
```

#### Saída:

```
22.627201 -1.267884 -5.422720
283.039612 -15.879736 ...
```