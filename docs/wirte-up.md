Claro! Abaixo está o conteúdo do `write-up.pdf` convertido para **Markdown**, mantendo a estrutura e formatação original adaptada ao estilo Markdown.

---

# Parallelization of a Radix Sort Algorithm

**Calebe de Paula Bianchini**
[calebe.bianchini@mackenzie.br](mailto:calebe.bianchini@mackenzie.br)

---

## 1. The Problem Description

Dado um conjunto de itens não ordenados com chaves representadas em binário, os bits dessas chaves podem ser usados para ordenar os itens. Esse método de ordenação é conhecido como **Radix Sort**.

Seu programa deve incluir uma **versão paralela do algoritmo Radix Sort** com threads, que ordena as chaves lidas de um arquivo de entrada e grava o resultado em um arquivo de saída.

* **Entrada**: Arquivo texto, primeira linha com o número total de chaves (N), seguido por N chaves (uma por linha), cada uma com 7 caracteres imprimíveis (exceto espaço ASCII 0x20).
* **Saída**: Arquivo texto com as chaves ordenadas (uma por linha).
* **Temporização**: O tempo de ordenação (não de leitura/escrita) será usado para avaliação. Se não houver temporização, todo o tempo de execução será considerado.

---

## 2. The Serial Solution

Existem duas variantes principais do Radix Sort:

* **LSD (Least Significant Digit)**: percorre os dígitos da direita para a esquerda.
* **MSD (Most Significant Digit)**: percorre os dígitos da esquerda para a direita.

A solução serial usa o **Radix Sort com abordagem MSD** e utiliza um **quicksort com partição em três partes (fat-pivot)** para ordenação interna, aproveitando dígitos repetidos.

---

## 3. The First Parallel Solution Attempt

A partir da ordenação pelo primeiro dígito significativo, é possível **criar partições independentes**, que se tornam **trabalhos (jobs)** atribuídos a diferentes processadores.

* Usa **OpenMP** para controle de threads.
* Utiliza **mutexes e semáforos POSIX** para seções críticas.
* Modelo **produtor/consumidor** para gerenciamento de jobs.

### Limitações:

* A seção crítica se torna gargalo.
* Para menos de 1.000.000 de chaves, a versão paralela é **mais lenta** que a serial.

### Exemplo de comparação:

| Nº de Chaves | Serial       | Paralelo (2 threads)    |
| ------------ | ------------ | ----------------------- |
| 1.000        | 0.000487 s   | 0.010744 s (0.000369)   |
| 100.000      | 0.063586 s   | 0.525342 s (0.025772)   |
| 500.000      | 0.389194 s   | 73.858603 s (0.120917)  |
| 1.000.000    | 0.832710 s   | 879.922349 s (0.218579) |
| 50.000.000   | 47.611455 s  | ω (11.061750)           |
| 100.000.000  | 104.441001 s | ω (23.215623)           |

---

## 4. The Final Parallel Solution

Melhorias:

* Threads paralelas + uma thread adicional para **sincronização**.
* Após a 1ª partição, há **94 partições possíveis** (ASCII 0x21 a 0x7E).
* Cada thread assume uma partição (±22 milhões de chaves por partição).
* **Thresholds** determinam quando criar novos jobs com base na carga.
* Uso de **checkpoints** no quicksort para melhor balanceamento e uso de memória.

### Comparação com 8 processadores:

| Nº de Chaves  | Serial        | Paralelo 2-proc | 4-proc       | 8-proc       |
| ------------- | ------------- | --------------- | ------------ | ------------ |
| 1.000         | 0.000487 s    | 0.008024 s      | 0.008484 s   | 0.105758 s   |
| 100.000       | 0.063586 s    | 0.041309 s      | 0.031875 s   | 0.104594 s   |
| 500.000       | 0.389194 s    | 0.225825 s      | 0.135147 s   | 0.128708 s   |
| 1.000.000     | 0.832710 s    | 0.502728 s      | 0.289878 s   | 0.236469 s   |
| 50.000.000    | 47.611455 s   | 27.055081 s     | 15.870333 s  | 11.025388 s  |
| 100.000.000   | 104.441001 s  | 59.439492 s     | 33.920247 s  | 23.915724 s  |
| 500.000.000   | 511.607666 s  | 287.287585 s    | 166.408876 s | 122.619186 s |
| 1.000.000.000 | 1174.523109 s | 595.044868 s    | 355.776813 s | 263.528890 s |

---

## 5. Conclusion

Ordenação é uma das tarefas mais comuns na computação. Embora seja fácil projetar um algoritmo paralelo, **obter ganho linear de performance é difícil**. Para conjuntos pequenos de dados, a execução serial tende a ser mais eficiente. O melhor caminho é **avaliar o volume de dados** para decidir entre solução sequencial ou paralela.

---

## 6. Referências

1. Sedgewick, R. *Algorithms in Java: Parts 1-4*. 3ª ed., Addison-Wesley, 2002.
2. [Wikipedia – Radix Sort](http://en.wikipedia.org/wiki/Radix_sort)
3. [Figura: RadixSort](http://www.strchr.com/_media/radixsort.png)
4. [Wikipedia – Quicksort](http://pt.wikipedia.org/wiki/Quicksort)
5. Tanenbaum, A. *Modern Operating Systems*. Prentice-Hall, 2007.
6. [Wikipedia – ASCII](http://en.wikipedia.org/wiki/ASCII)
7. Grama, A., Gupta, A., Karypis, G., Kumar, V. *Introduction to Parallel Computing*. Addison-Wesley, 2003.

---

Se quiser, posso transformar esse conteúdo em um modelo base de relatório `.md` com os tópicos exigidos no enunciado da sua disciplina. Deseja isso?
