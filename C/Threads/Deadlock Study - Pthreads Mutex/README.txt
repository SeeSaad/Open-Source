Existem três arquivos disponiveis:

IncorrectImplementation1.c -> Não tem exclusão mútua na área crítica, a escrita concorrente no mesmo arquivo, ao mesmo tempo, e por threads diferentes gera comportamento imprevisível.
IncorrectImplementation2.c -> Têm exclusão mútua da área crítica, porém é implementada de maneira errada e gera deadlock.
CorrectImplementation.c -> O controle da área crítica é implementado de maneira correta.

IMPORTANTE:
Para obter resultados encontrados no relatório, verificar se os arquivos "saldoA.txt" e 
"saldoB.txt" têm armazenados somente o valor 100 dentro deles.
