Configuração da plataforma:
    - 1x barramento
    - 1x CPU ARM
    - Memória -- parte baixa do espaço de endereçamento
    - Memória -- parte alta do espaço de endereçamento
    - 1x periférico -- MMRs na parte intermediária do espaço de endereçamento

Config.h:
    - Define as macros comum ao periférico e aplicação
    - Pode-se alterar o tamanho da matriz

Periférico:
    - Multiplica duas matrizes termo por termo
    - Parâmetros recebidos por 5 MMRs
        - Status do periférico (IDLE, REQUEST, READY...)
        - Endereço da matriz 1
        - Endereço da matriz 2
        - Endereço da matriz resultado
        - Tamanho das matrizes (na prática não é utilizado)
    - Operação é ativada ao alterar o valor de Status para REQUEST

Aplicação:
    - Define as duas matrizes iniciais
    - Transcreve as matrizes para um buffer
    - Espera que o periférico esteja livre
    - Configura os MMRs para solicitar a operação ao periférico
    - Espera que a operação esteja finalizada
    - Lê a matriz a matriz resultado

Comandos para rodar:
    - source source_ovp
    - ./run.sh
