# Monitor de Frequência Cardíaca com Displays

## Projeto da Mauá

**Autores:**  
Aline Nunes Watanabe¹, Rafaela Oliveira de Andrade Mar²  
¹ Instituto Mauá de Tecnologia (IMT)  
² Instituto Mauá de Tecnologia (IMT)  

## Resumo

Este projeto teve como objetivo desenvolver um monitor de frequência cardíaca utilizando o microcontrolador **PIC16F628A** e um **sensor piezoelétrico**. Foram aplicados conhecimentos adquiridos em **microcontroladores e instrumentação** na criação do dispositivo.

O sensor piezoelétrico inicial foi substituído por um de maior diâmetro para melhorar a leitura. Foi necessária a amplificação do sinal, inicialmente utilizando um **amplificador operacional LM358**, posteriormente substituído por um **comparador de tensão LM339** para maior estabilidade.

O circuito final incluiu **três displays de sete segmentos** para exibir a frequência cardíaca. Testes em protoboard e simulação no Proteus mostraram resultados satisfatórios, embora a necessidade de calibrar o potenciômetro e manter a área de medição imóvel tenha sido um empecilho. 

Apesar dessa limitação, o projeto demonstrou a aplicação prática dos conceitos estudados e sugeriu melhorias futuras, como a **compensação de movimento e o uso de sensores adicionais** para aumentar a robustez do sistema.

---

## Introdução

As disciplinas de **Microcontroladores e Sistemas Controlados** e **Instrumentação** forneceram a base teórica para este projeto. O objetivo era desenvolver um **monitor de frequência cardíaca** utilizando o **PIC16F628A**, processando os sinais de um sensor piezoelétrico e exibindo os valores medidos em **displays de 7 segmentos**.

## Material e Métodos

### Escolha e Análise do Sensor

Inicialmente, foi testado um sensor **piezoelétrico de 0,002m**, mas apresentou dificuldades de soldagem e gerou um sinal ruidoso. Foi substituído por um **piezoelétrico de 0,003m**, que melhorou a leitura e reduziu o ruído.

### Amplificação do Sinal

O sinal gerado pelo sensor era fraco, exigindo amplificação. O circuito passou por duas versões:
1. **Amplificador LM358** – apresentou problemas de estabilidade.
2. **Comparador LM339** – forneceu uma saída digital mais confiável para detecção dos batimentos cardíacos.

O comparador **detecta a variação de tensão gerada pelo sensor** e converte essa informação em pulsos digitais, que são processados pelo **PIC16F628A**.

### Exibição dos Dados

Os batimentos cardíacos por minuto são exibidos em **três displays de sete segmentos**, utilizando **decodificadores BCD**.

## Testes e Simulações

### Simulação no Proteus

O circuito foi inicialmente testado no **Proteus**, confirmando que a amplificação e a digitalização funcionavam conforme o esperado.

### Testes na Protoboard

Durante os testes físicos, verificou-se que:
- O **LM358** não era adequado devido à instabilidade do sinal.
- O **LM339** solucionou o problema, fornecendo uma saída digital mais precisa.
- A medição da frequência exigia calibragem manual do **potenciômetro**.

## Código do Projeto

O código foi desenvolvido para:
1. Ativar a **interrupção do Timer0** do PIC16F628A para contar o tempo.
2. Contar as transições de nível do comparador LM339.
3. Exibir a **frequência cardíaca** nos displays de sete segmentos.

## Projeto da Placa de Circuito Impresso (PCB)

Com base no circuito testado, foi projetada uma **placa de circuito impresso (PCB)** para organizar os componentes e melhorar a confiabilidade do sistema.

## Resultados e Discussões

O sistema funcionou conforme esperado, mas apresentou um problema de usabilidade: a necessidade de **manter o sensor imóvel** para medições precisas. Melhorias futuras podem incluir:
- Algoritmos de **compensação de movimento**.
- Uso de **sensores adicionais** para maior precisão.

## Conclusão

O projeto demonstrou o uso do **PIC16F628A e do sensor piezoelétrico** para monitoramento cardíaco, aplicando conhecimentos de **instrumentação e microcontroladores**. Apesar da limitação relacionada à estabilidade da medição, o sistema comprovou a viabilidade da tecnologia e sugeriu caminhos para aprimoramentos futuros.

## Referências

1. **BRAGA, Newton.** Comparador de tensão com o LM339 (NE191). Disponível em: [Newton Braga](https://www.newtoncbraga.com.br/banco-de-circuitos/2655-ne191.html).
2. **CEPEDA, Eduardo et al.** Heart Rate Detection using a Piezoelectric Ceramic Sensor. *Revista Bionatura, 2022*. Disponível em: [Artigo](https://acrobat.adobe.com/link/review?uri=urn%3Aaaid%3Ascds%3AUS%3A8a11b6e6-869d-3460-b9a6-d9fcfd5503fd).
3. **WATANABE, Aline.** Vídeos do projeto:
   - [Simulação no Proteus](https://www.youtube.com/watch?v=pMG_TDfExLI)
   - [Testes na protoboard](https://www.youtube.com/shorts/GSwDxtFUEWs)
   - [Circuito final soldado](https://youtu.be/IlRUklzx5iE)

---

📌 **Projeto desenvolvido por Aline Nunes Watanabe e Rafaela Oliveira de Andrade Mar no Instituto Mauá de Tecnologia.**
